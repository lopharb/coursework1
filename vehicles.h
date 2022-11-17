#pragma once
#include <iostream>
#include "users.h"

using namespace std;
class Vehicle
{
protected:
    string name;
    User holdingUser;
    double price;
    string adress;
    bool isNowTaken;

public:
    static vector<Vehicle> allVehicles;
    Vehicle(double price = 0, string adress = "")
    {
        this->price = price;
        this->adress = adress;
        this->isNowTaken = false;
    }
    virtual void Print() ;

    void SetOwnership(User user)
    {
        holdingUser = user;
        isNowTaken = true;
    }

    void Return()
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
    Bicycle(double price = 0, string adress = "", bool IsNt = true, bool baggage = false, short modesAmount = 0)
    {
        this->price = price;
        this->adress = adress;
        this->isNowTaken = false;
        this->hasBaggage = baggage;
        this->modesAmount = modesAmount;
        if (this->adress != "")
        {
            Vehicle::allVehicles.push_back(*this);
        }
    }

    virtual void Print()
    {
        cout << name << endl;
        cout << price << endl;
        char *buffer;
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
    Car(short transmission, double price = 0, string adress = "", bool IsNt = true)
    {
        this->price = price;
        this->adress = adress;
        this->isNowTaken = false;
        this->transmission = Transmission(transmission);
        if (this->adress != "")
        {
            Vehicle::allVehicles.push_back(*this);
        }
    }
    virtual void Print(){
        cout<<"car"<<endl;
    }
};