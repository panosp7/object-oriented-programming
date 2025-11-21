#include "Admin.h"
#include "Helper.h"
#include "Customer.h"
#include <iostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

Customer::Customer(string username, string password) : User(username, password, false){}

void save_products(const vector<Product>& products, const string& products_file);

void Customer::options(){ //display customer menu
    cout << "---Customer Menu--- " << endl;
    cout << "1. Search for a product " << endl;
    cout << "2. Add product to cart " << endl;
    cout << "3. Update product from cart " << endl;
    cout << "4. Remove product from cart " << endl;
    cout << "5. Complete order " << endl;
    cout << "6. View order history " << endl;
    cout << "7. View cart " << endl;
    cout << "8. Exit " << endl;
}
//search for any product with different ways
void Customer::search_product(const vector<Product> &products) const{
    int choice;
    cout << endl << "Product Search Options:" << endl;
    cout << "1. Search for a specific product (by title)." << endl;
    cout << "2. View the products of a specific category." << endl;
    cout << "3. Show all the available products." << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cout << choice << endl;

    if (choice == 1){ //by title
        string title;
        cout << "Enter product title you wish to search: ";
        cin.ignore();
        getline(cin, title);
        title = trim(title);
        cout << title << endl;

        bool found = false; //search for the product
        for (vector<Product>::const_iterator iter = products.begin(); iter != products.end(); iter++){
            if (trim(iter->get_title()) == title){
                iter->show_product();
                found = true;
                break;
            }
        }
        if (!found){
            cout << "This product not found" << endl;
        }
    } 
    else if (choice == 2){ //by category 
        string category;
        cout << "Enter category you wish to search: ";
        cin.ignore();
        getline(cin, category);
        category = trim(category);
        cout << category << endl;

        bool found = false;
        for (vector<Product>::const_iterator iter = products.begin(); iter != products.end(); iter++){
            if (trim(iter->get_category()) == category){
                iter->show_product();
                found = true;
            }
        }
        if (!found){
            cout << "This category includes no products" << endl;
        }
    }
    else if (choice == 3){ //by availability
        cout << "Results: ";
        for (vector<Product>::const_iterator iter = products.begin(); iter != products.end(); iter++){
            if (iter->get_quantity() > 0){
                cout << " \"" << trim(iter->get_title()) << "\" ";
            }
        }
        cout << endl;

        string title;
        cout << "Select a product title: ";
        cin.ignore();
        getline(cin, title);
        title = trim(title);
        cout << title << endl;

        bool found = false;
        for (vector<Product>::const_iterator iter = products.begin(); iter != products.end(); iter++){
            if (trim(iter->get_title()) == title){
                iter->show_product();
                found = true;
                break;
            }
        }
        if (!found){
            cout << "This product not found" << endl;
        }
    }
    else {
        cout << "Invalid choice" << endl;
    }
}

void Customer::add_product_to_cart(const vector<Product> &products){
    string title;
    int quantity;
    Product selection;

    cout << "Which product do you want to add? ";
    cin.ignore();
    getline(cin, title);
    title = trim(title); 
    cout << title << endl;

    bool found = false; //search if the product is available
    for (vector<Product>::const_iterator iter = products.begin(); iter != products.end(); iter++){
        if (trim(iter->get_title()) == title){
            iter->show_product();
            found = true;
            selection = *iter;
            break;
        }
    }
    if (!found){
        cout << "This product not found" << endl;
    }

    cout << endl << "Enter quantity: ";
    cin >> quantity;
    cout << quantity << endl;
//we check if there is enough 
    if (quantity > 0 && quantity <= selection.get_quantity()){
        cart[title] += quantity; //push product to cart       
    }
}

void Customer::update_product_from_cart(const vector<Product> &products){
    string title;
    int quantity;

    cout << "Which product do you want to update? ";
    cin.ignore();
    getline(cin, title);
    title = trim(title);
    cout << title << endl;
//see if the product exists
    bool found1 = false;
    bool found2 = false;
    for (map<string, int>::const_iterator itr = cart.begin(); itr != cart.end(); itr++){
        if (itr->first == title){
            found1 = true;
            cout << "Enter new quantity: ";
            cin >> quantity;
            cout << quantity << endl;
            if (quantity == 0){ //remove product from cart
                cart.erase(title);
                return;
            }
            //update quantity in cart
            for (vector<Product>::const_iterator iter = products.begin(); iter != products.end(); iter++){
                if (trim(iter->get_title()) == title){
                    found2 = true;
                    if (quantity <= iter->get_quantity()){
                        cart[title] = quantity; 
                    }
                    break;              
                }
            }
            return;                   
        }
    }
    if (!found1){
        cout << "This product not found in cart" << endl;
    }        
}

void Customer::remove_product_from_cart(const vector<Product> &products){
    string title;
    cout << "Which product do you want to remove from your cart? ";
    cin.ignore();
    getline(cin, title);
    title = trim(title);
    cout << title << endl;
//if the product exists it gets removed from cart
    map<string, int>::const_iterator itr = cart.find(title);
    if (itr != cart.end()){
        cart.erase(itr);
    } else {
        cout << "This product not found in cart" << endl;
    }
}

void Customer::complete_order(const string &products_file, vector<Product> &products){
    if (cart.empty()){
        cout << "Cart is empty" << endl;
        return;
    }
    //open user's order history file
    string file= "files/order_history/" + get_username() + "_history.txt";
    ifstream hfile1(file); //open file for reading

    int counter = 1;  //cart number
    if (hfile1){
        string line;
        while (getline(hfile1, line)){ //read file line by line
            if (line.find("---CART ") != string::npos){
                size_t x = line.find("CART ") + 5;
                size_t y = line.find(" ", x);
                counter = stoi(line.substr(x, y - x)) + 1;
            }
        }
        hfile1.close();
    }

    ofstream hfile2(file, ios::app); //open same file for writing
    hfile2 << endl << endl << "---CART " << counter << " START---" << endl;

    double sum = 0.0; //calculate total cost
    for (map<string, int>::const_iterator itr = cart.begin(); itr != cart.end(); itr++){
        string title = trim(itr->first);  
        int quantity = itr->second;

        bool found = false; //search the product in the catalog
        for (vector<Product>::iterator iter = products.begin(); iter != products.end(); iter++){
            if (trim(iter->get_title()) == title){  
                if (iter->get_quantity() >= quantity){  
                    iter->set_quantity(iter->get_quantity() - quantity);  
                    sum += quantity * iter->get_price();
                    found = true; //reduce the stock and add the cost to the total
                    break;
                }
            }
        }//update order history
        if (found){
            hfile2 << quantity << " " << title << endl;
        } else {
            hfile2 << quantity << " " << title << " This product not foud in cart" << endl;
        }
    }
    //write to order history file the cart
    hfile2 << "---CART " << counter << " END---" << endl;
    hfile2 << "Total Cost: " << fixed << setprecision(2) << sum << endl;
    hfile2.close();
//add to history and clear the cart
    order_history.push_back(cart);
    cart.clear();

    cout << "Order Completed!" << endl;
    save_products(products, products_file); //save reduced quantities in products.txt
}

void Customer::view_order_history(const vector<Product> &products) const{
    string file = "files/order_history/" + get_username() +"_history.txt";             
    ifstream hifile(file); //open file for reading
//show previous orders 
    if (!hifile){
        cout << endl << "No orders found in history" << endl;
    }

    string line;
    while (getline(hifile, line)){ //read user's order history file
        cout << line << endl;
    }
    
    hifile.close();
}

void Customer::view_cart(const vector<Product> &products) const{
    cout << endl << "---CART START---" << endl;

    double sum = 0.0; //calculate total cost

    for (map<string, int>::const_iterator iter = cart.begin(); iter != cart.end(); iter++){
        cout << iter->second << " " << iter->first << endl; //show quantity and title of the product
        bool found = false; //search product in the cart
        for (vector<Product>::const_iterator itr = products.begin(); itr != products.end(); itr++){
            if (trim(itr->get_title()) == trim(iter->first)){ //add the cost to the total
                sum += iter->second * itr->get_price();
                found = true;
                break;
            }
        }
        if (!found){
            cout << "This product not found in cart.\n";
        }
    }
    cout << "---CART END---" << endl;
    cout << "Total Cost: " << sum << endl;
}