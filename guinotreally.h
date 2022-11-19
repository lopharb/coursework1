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

    void LoggedInMenu()
    {
        system("cls");
        char controller;
        cout << "Logged in as " << (isInAdminList ? Admin::allAdmins[currentUserIndex].GetLogin() + " (administrator)" : User::allUsers[currentUserIndex].GetLogin()) << endl;
        cout << "Admin key: " << Admin::AdminKey << endl;
        cout << "0. Log out" << endl;
        cout << "1. List vehicles" << endl;
        if (isInAdminList)
            cout << "2. List users" << endl;
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
            for (Bicycle cur : Bicycle::allBicycles)
                cur.Print();
            cout << "Cars:" << endl;
            for (Car cur : Car::allCars)
                cur.Print();
            system("pause");
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
            system("pause");
            break;
        case 'e':
            fioop::SaveAllData();
            exit(0);
            break;
        default:
            cout << "No such option. Try again." << endl;
            system("pause");
        }
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
            for (Bicycle cur : Bicycle::allBicycles)
                cur.Print();
            cout << "Cars:" << endl;
            for (Car cur : Car::allCars)
                cur.Print();
            system("pause");
            break;
        case 'e':
            fioop::SaveAllData();
            exit(0);
            break;
        default:
            cout << "No such option. Try again." << endl;
            system("pause");
        }
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
            system("pause");
        }
        else if (Admin::SearchFor(login) != -1)
        {
            cout << "This username is already taken." << endl;
            system("pause");
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
        system("pause");
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
            else
            {
                cout << "WrongPassword!" << endl;
                system("pause");
            }
            return;
        }
        else
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
            else
            {
                cout << "WrongPassword!" << endl;
                system("pause");
            }
            return;
        }
        cout << "Login not found!" << endl;
        system("pause");
    }

    void LogOut()
    {
        isLoggedIn = false;
        isInAdminList = false;
        currentUserIndex = -1;
    }
}