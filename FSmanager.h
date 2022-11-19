#pragma once
#include <fstream>
#include <stdio.h>
#include <vector>
#include "users.h"
#include "vehicles.h"

class fioop
{
private:
    template <typename T>
    static string CheckType()
    {
        if (typeid(T) == typeid(User))
            return "Users";
        if (typeid(T) == typeid(Admin))
            return "Admins";
        if (typeid(T) == typeid(Bicycle))
            return "Bicycles";
        if (typeid(T) == typeid(Car))
            return "Cars";
        cout << "Invalid array type! Data was not written";
        return "ERROR";
    }

    template <typename T>
    static void SaveData(vector<T> artbw)
    {
        int length = artbw.size();
        if (!length)
        {
            cout << "Array contains no elements." << endl;
            return;
        }
        string filename = CheckType<T>();
        if (filename == "ERROR")
            return;
        filename += ".bin";
        FILE *file = fopen(filename.c_str(), "wb");
        if (!file)
        {
            cout << "Error in saving " + filename + " data!" << endl;
            return;
        }
        fwrite(&length, sizeof(int), 1, file);
        for (int i = 0; i < length; i++)
        {
            fwrite(&artbw[i], sizeof(T), 1, file);
        }
        fclose(file);
    }

    template <typename T>
    static vector<T> ReadData()
    {
        vector<T> arr;
        string filename = CheckType<T>();
        if (filename == "ERROR")
            return arr;
        filename += ".bin";
        FILE *file = fopen(filename.c_str(), "rb");
        if (!file)
        {
            cout << "Error in reading " + filename + " data!" << endl;
            return arr;
        }
        unsigned int length = 0;
        fread(&length, sizeof(unsigned int), 1, file);
        T tmp;
        for (int i = 0; i < length; i++)
        {
            fread(&tmp, sizeof(T), 1, file);
            arr.push_back(tmp);
        }
        fclose(file);
        return arr;
    }

public:
    static void SaveAllData()
    {
        SaveData(User::allUsers);
        SaveData(Admin::allAdmins);
        SaveData(Bicycle::allBicycles);
        SaveData(Car::allCars);
    }

    static void ReadAllData()
    {
        User::allUsers = ReadData<User>();
        Admin::allAdmins = ReadData<Admin>();
        Bicycle::allBicycles = ReadData<Bicycle>();
        Car::allCars = ReadData<Car>();
    }
};