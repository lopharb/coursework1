#include <iostream>
#include "users.h"
#include "vehicles.h"
#include "FSmanager.h"
#include "guinotreally.h"
#include <string>

using namespace std;

string Admin::AdminKey = Admin::GenerateAdminKey();
vector<User> User::allUsers = vector<User>();
vector<Admin> Admin::allAdmins = vector<Admin>();
vector<Vehicle> Vehicle::allVehicles = vector<Vehicle>();
/*int main(){
    cout<<fioop::CheckType<User>();
}*/