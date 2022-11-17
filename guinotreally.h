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
        cout << "1. Search vehicles" << endl;
        if (isInAdminList)
            cout << "2. Search users" << endl;
        cout << "E. Exit" << endl;
        cout << "Action: ";
        cin >> controller;

        switch (tolower(controller))
        {
        case '0':
            LogOut();
            break;
        case '1':
            cout << "To be done" << endl;
            break;
        case '2':
            if (isInAdminList)
            {
                cout << "To be done" << endl;
            }
            else
            {
                cout << "This option is avaliable only for administrators." << endl;
            }
            break;
        case 'e':
            fioop::SaveData(User::allUsers);
            fioop::SaveData(Admin::allAdmins);
            // save vehicles data
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
        cout << "2. Search vehicles" << endl;
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
            cout << "To be done" << endl;
            break;
        case 'e':
            fioop::SaveData(User::allUsers);
            fioop::SaveData(Admin::allAdmins);
            // save vehicles data
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
        bool isAdmin = (tolower(type) == 'a'); // equals true if type is a or A
        string login;
        cout << "Enter login: ";
        cin >> login;

        // checking if login is taken needs a better implementation for sure :D
        for (int i = 0; i < User::allUsers.size(); i++)
        {
            if (login == User::allUsers[i].GetLogin())
            {
                cout << "This username is already taken." << endl;
                system("pause");
                return;
            }
        }
        for (int i = 0; i < Admin::allAdmins.size(); i++)
        {
            if (login == Admin::allAdmins[i].GetLogin())
            {
                cout << "This username is already taken." << endl;
                system("pause");
                return;
            }
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
            if (newPerson.GetLogin() != "EMPTY")
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
        for (int i = 0; i < User::allUsers.size(); i++)
        {
            if (login == User::allUsers[i].GetLogin())
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
        }
        for (int i = 0; i < Admin::allAdmins.size(); i++)
        {
            if (login == Admin::allAdmins[i].GetLogin())
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