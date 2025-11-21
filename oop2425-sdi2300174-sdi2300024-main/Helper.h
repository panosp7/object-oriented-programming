#ifndef HELPER_H
#define HELPER_H

#include "User.h"
#include "Product.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

string trim(const string &str);
void save_products(const vector<Product> &products, const string &products_file);
void save_users(const map<string, User*> &users, const string &users_file);

#endif