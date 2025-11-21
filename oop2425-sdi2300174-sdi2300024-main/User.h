#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
    public:
        User(string in_username, string in_password, bool in_isAdmin);
        virtual ~User(){}
        virtual void options() = 0; //pure virtual function        
        string get_username() const;
        string get_password() const;
        bool get_isAdmin() const;
        bool check_user(string in_username, string in_password) const;

    protected:
        string username, password;
        bool isAdmin;
};

#endif 