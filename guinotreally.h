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
    void TakeVehicle();
    bool ListCurrent();
    void Return();

    void LoggedInMenu()
    {
        system("cls");
        char controller;

        cout << "Logged in as " << (isInAdminList ? Admin::allAdmins[currentUserIndex].GetLogin() + " (administrator)" : User::allUsers[currentUserIndex].GetLogin()) << endl;
        cout << "Admin key: " << Admin::AdminKey << endl;
        cout << "0. Log out" << endl;
        cout << "1. Take vehicle" << endl;
        cout << "2. List my vehicles" << endl;
        cout << "3. Return Vehicle" << endl;
        if (isInAdminList)
        {
            cout << "4. List users" << endl;
            cout << "5. Add new vehicle" << endl;
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
            for (int i = 0; i < Bicycle::allBicycles.size(); i++)
            {
                cout << "ID: " << i + 1 << " (Bicycle)" << endl;
                Bicycle::allBicycles[i].Print();
            }
            for (int i = 0; i < Car::allCars.size(); i++)
            {
                cout << "ID: " << i + 1 << " (Car)" << endl;
                Car::allCars[i].Print();
            }
            TakeVehicle();
            break;

        case '2':
            ListCurrent();
            break;

        case '3':
            Return();
            break;

        case '4':
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

        case '5':
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
        if (User::SearchFor(login) != -1 || Admin::SearchFor(login) != -1)
        {
            cout << "This login is already taken." << endl;
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
        cout << "Enter vehicle type: (C)ar or (B)icycle: (Type 'O' to cancel)" << endl;
        char cnt;
        cin >> cnt;
        if (tolower(cnt) == 'o')
            return;
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
        else if (isBic)
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

    void TakeVehicle()
    {
        cout << endl;
        cout << "Do you need a (C)ar or a (B)icycle? (Type 'O' to cancel)";
        char cnt;
        cin >> cnt;
        if (tolower(cnt) == 'o')
            return;
        bool isCar = tolower(cnt) == 'c';
        bool isBic = tolower(cnt) == 'b';
        if (!isCar && !isBic)
        {
            cout << "Invalid option!" << endl;
            return;
        }
        int cup = isCar ? Car::allCars.size() : Bicycle::allBicycles.size();
        cout << "Enter vehicle number from 1 to " << cup << endl;
        int index;
        cin >> index;
        index--;
        if (index < 0 || index > cup)
        {
            cout << "Invalid index!" << endl;
            return;
        }
        if (isCar)
            Car::allCars[index].SetOwnership(isInAdminList ? Admin::allAdmins[currentUserIndex] : User::allUsers[currentUserIndex]);
        if (isBic)
            Bicycle::allBicycles[index].SetOwnership(isInAdminList ? Admin::allAdmins[currentUserIndex] : User::allUsers[currentUserIndex]);
    }

    bool ListCurrent()
    {
        bool isNotEmpty = false;
        for (int i = 0; i < Bicycle::allBicycles.size(); i++)
        {
            if (Bicycle::allBicycles[i].GetOwner() == (isInAdminList ? Admin::allAdmins[currentUserIndex] : User::allUsers[currentUserIndex]))
            {
                cout << "ID: " << i + 1 << " (Bicycle)" << endl;
                Bicycle::allBicycles[i].Print();
                isNotEmpty = true;
            }
        }
        for (int i = 0; i < Car::allCars.size(); i++)
        {
            if (Car::allCars[i].GetOwner() == (isInAdminList ? Admin::allAdmins[currentUserIndex] : User::allUsers[currentUserIndex]))
            {
                cout << "ID: " << i + 1 << " (Car)" << endl;
                Car::allCars[i].Print();
                isNotEmpty = true;
            }
        }
        return isNotEmpty;
    }

    void Return()
    {
        if (ListCurrent())
        {
            cout << endl;
            cout << "Are you returning a (C)ar or a (B)icycle? (Type 'O' to cancel)";
            char cnt;
            cin >> cnt;
            if (tolower(cnt) == 'o')
                return;
            bool isCar = tolower(cnt) == 'c';
            bool isBic = tolower(cnt) == 'b';
            if (!isCar && !isBic)
            {
                cout << "Invalid option!" << endl;
                return;
            }
            int cup = isCar ? Car::allCars.size() : Bicycle::allBicycles.size();
            cout << "Enter the ID of the vehicle you'd like to return: " << endl;
            int index;
            cin >> index;
            index--; // xddddddddddddddddddddddd
            if (index < 0 || index > cup)
            {
                cout << "Invalid index!" << endl;
                return;
            }
            if (isCar)
                Car::allCars[index].ReturnToOffice(isInAdminList ? Admin::allAdmins[currentUserIndex] : User::allUsers[currentUserIndex]);
            if (isBic)
                Bicycle::allBicycles[index].ReturnToOffice(isInAdminList ? Admin::allAdmins[currentUserIndex] : User::allUsers[currentUserIndex]);
        }
        else
            cout << "You have no vehicles to return." << endl;
    }
}