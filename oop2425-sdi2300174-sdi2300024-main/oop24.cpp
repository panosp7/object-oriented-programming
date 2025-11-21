#include "Product.h"
#include "Admin.h"
#include "Customer.h"
#include "Category.h"
#include "Helper.h"
#include "User.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <memory>

using namespace std;

int main(int argc, char* argv[]){
    if (argc != 4){
        cerr << "Usage: ./oop24 files/categories.txt files/products.txt files/users.txt" << endl;
        return 1;
    } 

    //store categories, products and users
    vector<Category> categories;
    vector<Product> products;
    map<string, User*> users;

    ifstream file1(argv[1]); //initialize categories file

    string line1;
    while (getline(file1, line1)){ //read the whole file (categories) line by line 
        string category, subcategory;
        
        stringstream ss1(line1);
        getline(ss1, category, '(');
        getline(ss1, subcategory, ')');
        category = trim(category);

        vector<string> subcategories;
        stringstream sub_ss1(subcategory);
        string sub;
        while(getline(sub_ss1, sub, '@')){
            sub = trim(sub);
            subcategories.push_back(sub);
        }
        categories.push_back({category, subcategories}); //push read into categories svector
    }
    file1.close();

    ifstream file2(argv[2]); //initialize products file
    
    string line2;
    while (getline(file2, line2)){  //read the whole file (products) line by line 
        string title, description, category, subcategory, measurement;
        double price;
        int quantity;

        stringstream ss2(line2);
        getline(ss2, title, '@');
        getline(ss2, description, '@');
        getline(ss2, category, '@');
        getline(ss2, subcategory, '@');

        string s_price, s_quantity;
        getline(ss2, s_price, '@');
        getline(ss2, measurement, '@');
        getline(ss2, s_quantity, '@');
        
        price = stod(s_price); //convert string to double
        quantity = stoi(s_quantity); //convert string to integer
        
        //push read into products vector
        products.emplace_back(trim(title), trim(description), trim(category), trim(subcategory), price, quantity, trim(measurement));
    }  
    file2.close(); 

    string line3;
    ifstream data(argv[3]); //initialize users file
    while (getline(data, line3)){ //read the whole file (users) line by line
        string name, pass, role;
        stringstream ss3(line3);
        getline(ss3, name, ',');
        getline(ss3, pass, ',');
        getline(ss3, role, ',');
        bool isAdmin = (role == "1");
        if (isAdmin){ //create new admin
            users[name] = new Admin(name, pass);
        } else { //create new customer
            users[name] = new Customer(name, pass);
        }
    }
    data.close();

    string command;
    cout << "Welcome to the e-shop!!!" << endl << "Do you want to login or register? (enter option): ";
    cin >> command;
    cout << command << endl; //note in ReadMe for the reason we print the input in a lot of cases
    if (command == "login"){
        string username, password;
        cout << "Please enter your username: ";
        cin >> username;
        cout << username << endl;
        cout << "Please enter your password: ";
        cin >> password;
        cout << password << endl;
        
        map<string, User*>::iterator iter = users.find(username); //checking if the user exists and if his password is correct
        if (iter != users.end() && iter->second->check_user(username, password)) {
            cout << "Welcome " << username << "!" << endl;
            User* user = iter->second;
          
            while (1) {
                cout << endl;
                user->options();
                int choice;
                cout << "Enter your choice: ";
                cin >> choice; //user chooses action
                cout << choice << endl;
                if (user->get_isAdmin()){ //check if user is an admin  
                    Admin *admin = dynamic_cast<Admin*>(user);
                    if (choice == 1) {
                        admin->add_product(argv[2], products, categories);
                    } else if (choice == 2) {
                        admin->edit_product(argv[2], products);
                    }  else if (choice == 3) {
                        admin->remove_product(argv[2], products);
                    } else if (choice == 4) {
                        admin->search_product(products);
                    } else if (choice == 5) {
                        admin->show_unavailable_products(products);
                    } else if (choice == 6) {
                        admin->show_top5_products(products);
                    } else if (choice == 7) {
                        cout << "Goodbye!" << endl;
                       break;
                    }
                } else { //user is a customer
                    Customer *customer = dynamic_cast<Customer*>(user);
                    if (choice == 1) {
                        customer->search_product(products);
                    } else if (choice == 2) {
                        customer->add_product_to_cart(products);
                    }  else if (choice == 3) {
                        customer->update_product_from_cart(products);
                    } else if (choice == 4) {
                        customer->remove_product_from_cart(products);
                    } else if (choice == 5) {
                        customer->complete_order(argv[2], products);
                    } else if (choice == 6) {
                        customer->view_order_history(products);
                    } else if (choice == 7) {
                        customer->view_cart(products);
                    } else if (choice == 8) {
                        cout << "Goodbye!" << endl;
                        break;
                    }
                }   
            }
        } else {
            cout << "This user not found" << endl;
        }   
    } else if (command == "register"){
        string username, password;
        char yn;
        cout << "Please enter your username: ";
        cin >> username;
        cout << username << endl;
        cout << "Please enter your password: ";
        cin >> password;
        cout << password << endl;
        cout << "Are you an admin user? (Y/N): ";
        cin >> yn;
        cout << yn << endl;
        if (users.find(username) == users.end()){ //checking if this username is already in use
            if (yn == 'y') {
                users[username] = new Admin(username, password);
                cout << "Thanks for signing up! You are automatically logged-in as " << username << endl;
            } else {
                users[username] = new Customer(username, password);
                cout << "Thanks for signing up! You are automatically logged-in as " << username << endl;
            }       
            save_users(users, argv[3]); //keep the new user's credentials in history
            while (1) {
                cout << endl;
                users[username]->options(); //show the user the options that correspond to him
                int choice;
                cout << "Enter your choice: ";
                cin >> choice;
                cout << choice << endl;
                if (users[username]->get_isAdmin()){
                    Admin *user1 = dynamic_cast<Admin*>(users[username]);
                    if (choice == 1) {
                        user1->add_product(argv[2], products, categories);
                    } else if (choice == 2) {
                        user1->edit_product(argv[2], products);
                    } else if (choice == 3) {
                        user1->remove_product(argv[2], products);
                    } else if (choice == 4) {
                        user1->search_product(products);
                    } else if (choice == 5) {
                        user1->show_unavailable_products(products);
                    } else if (choice == 6) {
                        user1->show_top5_products(products);
                    } else if (choice == 7) {
                        cout << "Goodbye!" << endl;
                        break;
                    }
                } else {
                    Customer* user2 = dynamic_cast<Customer*>(users[username]);
                    if (choice == 1) {
                        user2->search_product(products);
                    } else if (choice == 2) {
                        user2->add_product_to_cart(products);
                    }  else if (choice == 3) {
                        user2->update_product_from_cart(products);
                    } else if (choice == 4) {
                        user2->remove_product_from_cart(products);
                    } else if (choice == 5) {
                        user2->complete_order(argv[2], products);
                    } else if (choice == 6) {
                        user2->view_order_history(products);
                    } else if (choice == 7) {
                        user2->view_cart(products);
                    } else if (choice == 8) {
                        cout << "Goodbye!" << endl;
                        break;
                    }
                }
            }   
        } else {
            cout << "There is a user with this username" << endl;
        }
    }
    for (map<string, User*>::const_iterator iter = users.begin(); iter != users.end(); iter++) {
        delete iter->second; //dealocation
    }

    return 0;
}