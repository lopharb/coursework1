#include <iostream>
#include "users.h"
#include "vehicles.h"
#include "FSmanager.h"
#include "guinotreally.h"
#include <string>

using namespace std;
string Admin::AdminKey = Admin::GenerateAdminKey();
vector<User> User::allUsers = vector<User>();
vector<Vehicle> Vehicle::allVehicles = vector<Vehicle>();

// need to drag that into another file to clean up main (DONE)
// maybe rewrite the file IO using newer methods (but they don't work good with strings so prob no)
// finish the vehicle class and we're done i think
// also need to clean up the code ie remove unused methods etc
// also need to split up headers and implementations 
int main()
{
    User::allUsers = ReadUsersData();
    cout << User::allUsers.size() << " users imported from local storage." << endl;
    for (User cur : User::allUsers)
    {
        cur.Print();
    }
    system("pause");
    while (true)
    {
        if (iosorg::isLoggedIn)
            iosorg::LoggedInMenu();
        else
            iosorg::LoggedOutMenu();
    }
    SaveData(User::allUsers); // overwrite the storage
}
