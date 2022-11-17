#pragma once
#include <fstream>
#include <stdio.h>
#include <vector>
#include "users.h"
#include "vehicles.h"


void SaveData(vector<User> artbw)
{
    FILE *usersInf = fopen("Users.bin", "wb");
    if (!usersInf)
    {
        cout << "Error in saving data!" << endl;
        return;
    }

    int length = artbw.size();
    fwrite(&length, sizeof(int), 1, usersInf);
    for (int i = 0; i < length; i++)
    {
        if (typeid(artbw[i]) == typeid(User))
        {
            string tmp = "User";
            fwrite(&tmp, sizeof(string), 1, usersInf);
            fwrite(&artbw[i], sizeof(User), 1, usersInf);
        }
        else if (typeid(artbw[i]) == typeid(Admin))
        {
            string tmp = "Admin";
            fwrite(&tmp, sizeof(string), 1, usersInf);
            fwrite(&artbw[i], sizeof(Admin), 1, usersInf);
        }
    }
    fclose(usersInf);
}

void SaveData(Vehicle *artbw)
{
    // same here for all the vehicles
}

vector<User> ReadUsersData()
{
    FILE *usersInf = fopen("Users.bin", "rb");
    vector<User> arr;
    if (!usersInf)
    {
        cout << "Error in opening file!" << endl;
        return arr;
    }

    unsigned int length = 0;
    fread(&length, sizeof(unsigned int), 1, usersInf);

    User tmp;
    for (int i = 0; i < length; i++)
    {
        string type;
        fread(&type, sizeof(string), 1, usersInf);
        if (type == "User")
            fread(&tmp, sizeof(User), 1, usersInf);
        else if (type == "Admin")
            fread(&tmp, sizeof(Admin), 1, usersInf);
        arr.push_back(tmp);
    }
    fclose(usersInf);
    return arr;
}
