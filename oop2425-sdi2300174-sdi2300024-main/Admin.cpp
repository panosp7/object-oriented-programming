#include "User.h"
#include "Admin.h"
#include "Helper.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

//constructor for Admin 
Admin::Admin(string username, string password) : User(username, password, true){}

//define the prototype of save_products, so that is can be used later by functions
void save_products(const vector<Product>& products, const string& products_file);

//display Admin choices
void Admin::options(){
    cout << "---Admin Menu--- " << endl;
    cout << "1. Add Product " << endl;
    cout << "2. Edit Product " << endl;
    cout << "3. Remove Product " << endl;
    cout << "4. Search Product " << endl;
    cout << "5. Show Unavailable Products " << endl;
    cout << "6. Show Top 5 Products " << endl;
    cout << "7. Exit " << endl;
}

//add a product in products.txt
void Admin::add_product(const string &products_file, vector<Product> &products, vector<Category> &categories){
    string title, description, category, subcategory, measurement;
    double price;
    int quantity;

    //give as inputs the charachteristics of the product we want to add
    cout << "Give product title: ";
    cin.ignore(); //use this function all the time to clear buffer
    getline(cin, title);
    cout << title << endl;
    cout << "Give product description: ";
    getline(cin, description);
    cout << description << endl;

    //show the categories included in categories.txt
    cout << "Give one of the following categories: ";
    for (vector<Category>::iterator iter = categories.begin(); iter != categories.end(); iter++){
        cout << iter->category << " ";
    }
    cout << endl;
    getline(cin, category);
    cout << category << endl;

    //show the subcategories of the selected catgory
    vector<Category>::iterator iter = categories.begin();
    while (iter != categories.end() && iter->category != category){
        iter++;
    }
    if (iter != categories.end()){
        cout << "Give one of the following subcategories: ";
        for (const auto &itr : iter->subcategories){
            cout << itr << " ";
        }
        cout << endl;
    }
    getline(cin, subcategory);
    cout << subcategory << endl; 

    cout << "Give product price: "; //take the other inputs
    cin >> price;
    cin.ignore();
    cout << price << endl;
    cout << "Give measurement type[Kg/Unit]: ";
    getline(cin, measurement);
    cout << measurement << endl;
    cout << "Give amount of Unit: ";
    cin >> quantity;
    cin.ignore();
    cout << quantity << endl;

    //push the characteristics into products.txt and save the changes
    products.emplace_back(title, description, category, subcategory, price, quantity, measurement);
    save_products(products, products_file);
    
    cout << "Product added successfully!" << endl;
}

//edit a specific product
void Admin::edit_product(const string &products_file, vector<Product> &products){           
    string title;
    cin.ignore();
    cout << "Enter the product title you wish to edit: "; //take input the product title
    getline(cin, title);
    title = trim(title); 
    cout << title << endl;

    //seearch through products.txt and select which chracteristic to change
    for (vector<Product>::iterator iter = products.begin(); iter != products.end(); iter++){
        if (trim(iter->get_title()) == title){
            int choice;
            cout << "Enter number of field you want to edit: 1.Title 2.Description 3.Category and Subcategory 4.Price 5.Available Kg 6.Nothing " << endl;
            cin >> choice;
            cin.ignore();
            cout << choice << endl;

            switch(choice){
            case 1: { 
                string x;
                cout << "Enter new title: ";
                getline(cin, x);
                cout << x << endl;
                iter->set_title(x); //edit the title
                cout << "Product updated!" << endl;
                break;
            }
            case 2: { 
                string x;
                cout << "Enter new description: ";
                getline(cin, x);
                cout << x << endl;
                iter->set_description(x); //edit the description
                cout << "Product updated!" << endl;
                break;
            }
            case 3: { 
                string x, y;
                cout << "Enter new category: ";
                cin >> x;
                cout << x << endl;
                cout << "Enter new subcategory: ";
                cin >> y;
                cout << y << endl;
                iter->set_category(x); //edit the category and subcategory
                iter->set_subcategory(y);
                cout << "Product updated!" << endl;
                break;
            }
            case 4: { 
                double x;
                cout << "Enter new price: ";
                cin >> x;
                cout << x << endl;
                iter->set_price(x); //edit the price
                cout << "Product updated!" << endl;
                break;
            }
            case 5: { 
                int x;
                cout << "Enter new available quantity: ";
                cin >> x;
                cout << x << endl;
                iter->set_quantity(x); //edit the quantity
                cout << "Product updated!" << endl;
                break;
            }
            case 6: 
                cout << "Nothing edited" << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
            }
            save_products(products, products_file); //save the changs to product.txt
            return;
        }
    }
    cout << "This product not found" << endl;
}

//remove a specific product from products.txt
void Admin::remove_product(const string &products_file, vector<Product> &products){
    string title;
    bool found = false;
    cout << "Enter product title you wish to remove: "; //take input the title
    cin.ignore();
    getline(cin, title);
    title = trim(title); 
    cout << title << endl;

    //search through products
    for (vector<Product>::iterator iter = products.begin(); iter != products.end(); iter++){
        if (trim(iter->get_title()) == title) {
            products.erase(iter); //delete this product from the file
            found = true;
            save_products(products, products_file); //save the changes
            cout << "Product removed!" << endl;
            break; 
        }
    }

    if (!found){
        cout << "This product not found" << endl;
    }
}

//search a specific product and give its characteristics if found
void Admin::search_product(const vector<Product> &products) const{
    cout << "Enter product title you wish to search: ";
    string title;
    cin.ignore();
    getline(cin, title);
    cout << title << endl;

    //sarch through products
    bool found = false;
    for (vector<Product>::const_iterator iter = products.begin(); iter != products.end(); iter++){
        if (iter->get_title() == title){
            iter->show_product();
            found = true;
            break;
        }
    }
    if (!found){
        cout << "This product not found" << endl;
    }
}

//show all products that have run out of stock
void Admin::show_unavailable_products(const vector<Product> &products)const {
    cout << "Unavailable Products:\n";
    for (vector<Product>::const_iterator iter = products.begin(); iter != products.end(); iter++){
        if (iter->get_quantity() == 0){
            iter->show_product();
            cout << "----------------" << endl;
        }
    }
}

bool Admin::compare(const Product &a, const Product &b){
    return a.get_quantity() > b.get_quantity();
}

void Admin::show_top5_products(const vector<Product> &products) const{
    cout << "Top 5 Products:\n";

    vector <Product> sorted_products = products;
    sort(sorted_products.begin(), sorted_products.end(), Admin::compare);

    for (int i = 0; i < 5 && i < sorted_products.size(); i++){
        sorted_products[i].show_product();
    }           
}