#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <regex>
#include <vector>
using namespace std;

class User
{
protected:
    string login;
    string password;
    string name;
    string phoneNumber;

public:
    static vector<User> allUsers;
    User(string login = "EMPTY", string password = "EMPTY", string name = "EMPTY")
    {
        this->login = login;
        this->password = password;
        this->name = name;
        if (this->login != "EMPTY")
            allUsers.push_back(*this);
    }

    void Print()
    {
        cout << "Login: " << setw(23) << login << endl;
        cout << "Password: " << setw(20) << password << endl;
        cout << "Phone number: " << setw(16) << phoneNumber << endl;
    }

    static int SearchFor(string login)
    {
        for (int i = 0; i < User::allUsers.size(); i++)
        {
            if (login == User::allUsers[i].login)
                return i;
        }
        return -1;
    }

    bool CheckLogIn(string password)
    {
        if (this->password == password)
            return true;
        cout << "Wrong password!" << endl;
        return false;
    }

    void SetPhoneNumber(string pn)
    {
        if (pn == "-")
        {
            phoneNumber = "unknown";
            return;
        }
        regex VALIDATOR("\\+375\\-[0-9]{2}\\-[0-9]{3}\\-[0-9]{2}\\-[0-9]{2}");
        if (regex_match(pn, VALIDATOR))
        {
            phoneNumber = pn;
        }
        else
        {
            cout << "Invalid phone number format!" << endl;
        }
    }

    string GetLogin()
    {
        return login;
    }

    string GetName()
    {
        return name;
    }
};

class Admin : public User
{
public:
    bool verified = true;
    static vector<Admin> allAdmins;
    static string AdminKey;
    static string GenerateAdminKey()
    {
        setlocale(LC_ALL, "Russian");
        srand(time(NULL));
        cout << "Key generating..." << endl;
        string generated = "";
        const short LENGTH = 12;
        const string SOURCE = "1234567890QWERTYUIOPASDFGHJKLZXCVBNM";
        const short LIMIT = SOURCE.length();
        for (short i = 0; i < LENGTH; i++)
        {
            generated += SOURCE[rand() % LIMIT];
        }
        cout << generated << endl;
        cout << "Key created successfully" << endl;
        return generated;
    }

    Admin() {}
    Admin(string login, string password = "EMPTY", string name = "EMPTY")
    {
        this->login = login;
        this->password = password;
        this->name = name;
        cout << "Enter admin validation key:" << endl;
        string tmp;
        cin >> tmp;
        if (tmp != AdminKey)
        {
            cout << "Invalid verification key! Administrator account was not created." << endl;
            verified = false;
        }
        else
            cout << "Administrator key check passed." << endl;
        if (verified)
            Admin::allAdmins.push_back(*this);
    }

    static int SearchFor(string login)
    {
        for (int i = 0; i < Admin::allAdmins.size(); i++)
        {
            if (login == Admin::allAdmins[i].login)
                return i;
        }
        return -1;
    }
};
