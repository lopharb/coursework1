#pragma once
#include <iostream>
#include "vehicles.h"
#include "users.h"
#include "FSmanager.h"

using namespace std;
namespace iosorg
{
    extern bool isLoggedIn = false;
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
        cout << "Logged in as " << User::allUsers[currentUserIndex].GetLogin() << (typeid(User::allUsers[currentUserIndex]) == typeid(Admin) ? " (Administrator)\n" : "\n") << endl;
        cout << "Admin key: " << Admin::GetAdminKey() << endl;
        cout << "0. Log out" << endl;
        cout << "1. Search vehicles" << endl;
        if (typeid(User::allUsers[currentUserIndex]) == typeid(Admin))
        {
            cout << "2. Search users" << endl;
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
            cout << "To be done" << endl;
            break;
        case '2':
            if (typeid(User::allUsers[currentUserIndex]) == typeid(Admin))
            {
                cout << "To be done" << endl;
            }
            else
            {
                cout << "This option is avaliable only for administrators." << endl;
            }
            break;
        case 'e':
            SaveData(User::allUsers);
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
        cout << "Admin key: " << Admin::GetAdminKey() << endl;
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
            SaveData(User::allUsers);
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
        for (int i = 0; i < User::allUsers.size(); i++)
        {
            if (login == User::allUsers[i].GetLogin())
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

        User newUser; // is not pushed in the vector bc is empty
        // should be admin depending on the stuff above
        if (name == "-")
            newUser = isAdmin ? Admin(login, password) : User(login, password);
        else
            newUser = isAdmin ? Admin(login, password, name) : User(login, password, name);
        if (pn != "-")
            newUser.SetPhoneNumber(pn);
        if (newUser.GetLogin() != "EMPTY")
        {
            cout << "User " << newUser.GetLogin() << " created successfully." << endl;
            isLoggedIn = true;
            currentUserIndex = User::allUsers.size() - 1;
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
                    currentUserIndex = i;
                }
                return;
            }
        }
    }

    void LogOut()
    {
        isLoggedIn = false;
        currentUserIndex = -1;
    }
}