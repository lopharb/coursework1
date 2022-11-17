#include <iostream>
#include "users.h"
#include "vehicles.h"
#include "FSmanager.h"
#include "guinotreally.h"
#include <string>

using namespace std;
// static variables initialization
string Admin::AdminKey = Admin::GenerateAdminKey();
vector<User> User::allUsers = vector<User>();
vector<Admin> Admin::allAdmins = vector<Admin>();
vector<Vehicle> Vehicle::allVehicles = vector<Vehicle>();

// need to drag that into another file to clean up main (DONE)
// maybe rewrite the file IO using newer methods (but they don't work good with strings so prob no) (no need so DONE)
// finish the vehicle class and we're done i think (DONE)
// also need to clean up the code ie remove unused methods etc
// also need to split up headers and implementations

int main()
{
    User::allUsers = fioop::ReadUsersData<User>();
    Admin::allAdmins = fioop::ReadUsersData<Admin>();
    cout << User::allUsers.size() << " users imported from local storage." << endl;
    for (User cur : User::allUsers)
    {
        cur.Print();
    }
    cout << Admin::allAdmins.size() << " admins imported from local storage." << endl;
    for (Admin cur : Admin::allAdmins)
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
    fioop::SaveData(User::allUsers); // overwrite the storage
}
