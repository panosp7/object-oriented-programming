#include "Helper.h"
#include "Product.h"
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

string trim(const string &str){ //trims spaces at the begining and at the end of the strings
    //consider multiple types of spaces to handle diffrent string inputs
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    if (first == string::npos || last == string::npos){
        return "";
    }
    return str.substr(first, (last - first + 1)); //return string without the spaces
}
//we save the list of products
void save_products(const vector<Product> &products, const string &products_file){
    ofstream pfile(products_file); //oren file for writing
    //write the details of the products the way it is needed
    //price should be written with precision .00 and quantity as it is
    for (vector<Product>::const_iterator iter = products.begin(); iter != products.end(); iter++){
        pfile << iter->get_title() << " @ " << iter->get_description() << " @ " << iter->get_category() << " @ " << iter->get_subcategory() << " @ " 
              << fixed << setprecision(2) << iter->get_price() << " @ " << iter->get_measurement() << " @ ";

        double quantity = iter->get_quantity();
        if (quantity == (int)quantity) {
            pfile << (int)quantity << endl;
        } else {
            pfile << fixed << setprecision(2) << quantity << endl;
        }
    }
    pfile.close();
}
//we keep the user
void save_users(const map<string, User*> &users, const string &users_file){
    //open file for writing and put cursor at the end 
    ofstream ufile(users_file, ios::app);
    for (map<string, User*>::const_iterator iter = users.begin(); iter != users.end(); iter++){
        ufile << iter->first << "," << iter->second->get_password() << "," << (iter->second->get_isAdmin() ? "1" : "0") << endl;
    } //we write the credentials of the users the way it is needed 
    ufile.close();
}