#include "User.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;
//using constructor to initialize user with username password and the 1 or 0 to see if the user is admin or customer
User::User(string in_username, string in_password, bool in_isAdmin) : username(in_username), password(in_password), isAdmin(in_isAdmin){}
//we get the username the password and the 1,0
string User::get_username() const{
    return username;
}
string User::get_password() const{
    return password;
}
bool User::get_isAdmin() const{
    return isAdmin;
} //check if the username and password match
bool User::check_user(string in_username, string in_password) const{
    return username == in_username && password == in_password;
}