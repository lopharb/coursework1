#pragma once
#include <iostream>
#include "users.h"

using namespace std;
class Vehicle
{
protected:
    User holdingUser;
    double price;
    string adress;
    bool isNowTaken;

public:
    Vehicle(double price = 0, string adress = "")
    {
        this->price = price;
        this->adress = adress;
        this->isNowTaken = false;
    }
    virtual void Print() = 0;

    void SetOwnership(User user)
    {
        holdingUser = user;
        isNowTaken = true;
    }

    void ReturnToOffice()
    {
        holdingUser = User();
        isNowTaken = false;
    }
};

class Bicycle : public Vehicle
{
private:
    bool hasBaggage;
    short modesAmount;

public:
    static vector<Bicycle> allBicycles;
    Bicycle(double price = 0, string adress = "", bool IsNt = true, bool baggage = false, short modesAmount = 0)
    {
        this->price = price;
        this->adress = adress;
        this->isNowTaken = false;
        this->hasBaggage = baggage;
        this->modesAmount = modesAmount;
        if (this->adress != "")
        {
            allBicycles.push_back(*this);
        }
    }

    virtual void Print()
    {
        cout << price << endl;
        char *buffer = new char;
        itoa(modesAmount, buffer, 10);
        cout << "Amount of modes: " << (modesAmount ? buffer : "unspecified") << endl;
        cout << "Baggage carrier: " << (hasBaggage ? "yes" : "no");
        if (isNowTaken)
            cout << "Held by " << holdingUser.GetName() << endl;
        else
            cout << "Stored at " << adress;
    }
};

class Car : public Vehicle
{
private:
    enum Transmission
    {
        automatic, // 0
        manual     // 1
    } transmission;
    double engineVolume;

public:
    static vector<Car> allCars;
    Car(short transmission = 0, double price = 0, string adress = "", bool IsNt = true)
    {
        this->price = price;
        this->adress = adress;
        this->isNowTaken = false;
        this->transmission = Transmission(transmission);
        if (this->adress != "")
        {
            allCars.push_back(*this);
        }
    }
    virtual void Print()
    {
        cout << price << endl;
        string buffer;

        switch (transmission)
        {
        case automatic:
            buffer = "automatic";
            break;
        case manual:
            buffer = manual;
            break;
        default:
            break;
        }
        cout << "Transmission type: " << buffer << endl;
        if (isNowTaken)
            cout << "Held by " << holdingUser.GetName() << endl;
        else
            cout << "Stored at " << adress;
    }
};