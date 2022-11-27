#pragma once
#include <iostream>
#include "vehicles.h"
#include "users.h"
#include "FSmanager.h"

using namespace std;
namespace iosorg
{
    extern bool isLoggedIn = false;
    extern bool isInAdminList = false;
    int currentUserIndex = -1;

    void LoggedInMenu();
    void LoggedOutMenu();
    void CreateAccount();
    void LogIn();
    void LogOut();
    void CreateVehicle();

    void LoggedInMenu()
    {
        system("cls");
        bool isCar = false, isBic = false;
        int cup = 0;
        char controller;
        cout << "Logged in as " << (isInAdminList ? Admin::allAdmins[currentUserIndex].GetLogin() + " (administrator)" : User::allUsers[currentUserIndex].GetLogin()) << endl;
        cout << "Admin key: " << Admin::AdminKey << endl;
        cout << "0. Log out" << endl;
        cout << "1. Take vehicle" << endl;
        if (isInAdminList)
        {
            cout << "2. List users" << endl;
            cout << "3. Add new vehicle" << endl;
        }
        cout << "E. Exit" << endl;
        cout << "Action: ";
        cin >> controller;
        switch (tolower(controller))
        {
        case '0':
            LogOut();
            break;
        case '1':
            cout << "Bicycles:" << endl;
            for (int i = 0; i < Bicycle::allBicycles.size(); i++)
            {
                cout << i + 1 << endl;
                Bicycle::allBicycles[i].Print();
            }
            cout << "Cars:" << endl;
            for (int i = 0; i < Car::allCars.size(); i++)
            {
                cout << i + 1 << endl;
                Car::allCars[i].Print();
            }
            cout << endl;
            cout << "Do you need a (C)ar or a (B)icycle?";
            char cnt;
            cin >> cnt;
            isCar = tolower(cnt) == 'c';
            isBic = tolower(cnt) == 'b';
            if (!isCar && !isBic)
            {
                cout << "Invalid option!" << endl;
                break;
            }
            cup = isCar ? Car::allCars.size() : Bicycle::allBicycles.size();
            cout << "Enter vehicle number from 1 to " << cup << endl;
            int index;
            cin >> index;
            index--;
            if (index < 0 || index > cup)
            {
                cout << "Invalid index!" << endl;
                break;
            }
            if (isCar)
                Car::allCars[index].SetOwnership(isInAdminList ? Admin::allAdmins[currentUserIndex] : User::allUsers[currentUserIndex]);
            if (isBic)
                Bicycle::allBicycles[index].SetOwnership(isInAdminList ? Admin::allAdmins[currentUserIndex] : User::allUsers[currentUserIndex]);
            break;
        case '2':
            if (isInAdminList)
            {
                for (User cur : User::allUsers)
                    cur.Print();
                for (Admin cur : Admin::allAdmins)
                    cur.Print();
            }
            else
                cout << "This option is avaliable only for administrators." << endl;
            break;
        case '3':
            if (isInAdminList)
                CreateVehicle();
            else
                cout << "This option is avaliable only for administrators." << endl;
            break;
        case 'e':
            fioop::SaveAllData();
            exit(0);
            break;
        default:
            cout << "No such option. Try again." << endl;
            break;
        }
        system("pause");
    }

    void LoggedOutMenu()
    {
        system("cls");
        char controller;
        cout << "Guest\n"
             << endl;
        cout << "Admin key: " << Admin::AdminKey << endl;
        cout << "0. Log in" << endl;
        cout << "1. Create account" << endl;
        cout << "2. List vehicles" << endl;
        cout << "E. Exit" << endl;
        cout << "Action: ";
        cin >> controller;
        switch (tolower(controller))
        {
        case '0':
            LogIn();
            break;
        case '1':
            CreateAccount();
            break;
        case '2':
            cout << "Bicycles:" << endl;
            for (int i = 0; i < Bicycle::allBicycles.size(); i++)
                Bicycle::allBicycles[i].Print();
            cout << "Cars:" << endl;
            for (int i = 0; i < Car::allCars.size(); i++)
                Car::allCars[i].Print();
            break;
        case 'e':
            fioop::SaveAllData();
            exit(0);
            break;
        default:
            cout << "No such option. Try again." << endl;
        }
        system("pause");
    }

    void CreateAccount()
    {
        char type;
        cout << "Type 'A' if you want to create an administrator account, or any other symbol if not.";
        cin >> type;
        bool isAdmin = (tolower(type) == 'a');
        string login;
        cout << "Enter login: ";
        cin >> login;
        if (User::SearchFor(login) != -1)
        {
            cout << "This username is already taken." << endl;
            return;
        }
        else if (Admin::SearchFor(login) != -1)
        {
            cout << "This username is already taken." << endl;
            return;
        }
        string password;
        cout << "Enter password: ";
        cin >> password;
        string name;
        cout << "Enter your name (or '-' if you don't want to specify the name): ";
        cin >> name;
        string pn;
        cout << "Enter your phone number (or '-' if you don't want to specify the number): ";
        cin >> pn;
        if (isAdmin)
        {
            Admin newPerson(login, password, name);
            if (newPerson.verified)
            {
                isLoggedIn = true;
                isInAdminList = true;
                currentUserIndex = Admin::allAdmins.size() - 1;
                Admin::allAdmins[currentUserIndex].SetPhoneNumber(pn);
            }
        }
        else
        {
            User newPerson(login, password, name);
            isLoggedIn = true;
            isInAdminList = false;
            currentUserIndex = User::allUsers.size() - 1;
            User::allUsers[currentUserIndex].SetPhoneNumber(pn);
        }
    }

    void LogIn()
    {
        cout << "Enter your login: ";
        string login;
        cin >> login;
        int i = User::SearchFor(login);
        if (i != -1)
        {
            string password;
            cout << "Enter password: ";
            cin >> password;
            if (User::allUsers[i].CheckLogIn(password))
            {
                isLoggedIn = true;
                isInAdminList = false;
                currentUserIndex = i;
            }
            return;
        }
        i = Admin::SearchFor(login);
        if (i != -1)
        {
            string password;
            cout << "Enter password: ";
            cin >> password;
            if (Admin::allAdmins[i].CheckLogIn(password))
            {
                isLoggedIn = true;
                isInAdminList = true;
                currentUserIndex = i;
            }
            return;
        }
        cout << "Login not found!" << endl;
    }

    void LogOut()
    {
        isLoggedIn = false;
        isInAdminList = false;
        currentUserIndex = -1;
    }

    void CreateVehicle()
    {
        cout << "Enter vehicle type: (C)ar or (B)icycle: " << endl;
        char cnt;
        cin >> cnt;
        bool isCar = tolower(cnt) == 'c';
        bool isBic = tolower(cnt) == 'b';
        if (isCar)
        {
            cout << "Enter transmission type (0 for automatic, 1 for manual):" << endl;
            short trm;
            cin >> trm;
            while (trm != 0 && trm != 1)
            {
                cout << "Invalid value. Try again: " << endl;
                cin >> trm;
            }
            cout << "Enter price: " << endl;
            double price;
            cin >> price;
            cout << "Enter adress: " << endl;
            string adress;
            cin >> adress;
            Car newcar = Car(trm, price, adress);
            cout << "New car has been added." << endl;
        }
        if (isBic)
        {
            cout << "Does the bicycle have a baggage?[y/n]:" << endl;
            char cnt;
            cin >> cnt;
            bool hasBaggage = tolower(cnt) == 'y';
            cout << "Enter amount of modes:" << endl;
            short ma;
            cin >> ma;
            cout << "Enter price: " << endl;
            double price;
            cin >> price;
            cout << "Enter adress: " << endl;
            string adress;
            cin >> adress;
            Bicycle newbic = Bicycle(price, adress, hasBaggage, ma);
            cout << "New bicycle has been added." << endl;
        }
        else
            cout << "Invalid vehicle type!" << endl;
    }
}