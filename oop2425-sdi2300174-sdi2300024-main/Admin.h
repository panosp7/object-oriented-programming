#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Category.h"
#include "Product.h"
#include <string>
#include <vector>
using namespace std;

class Admin : public User {
    public:
        Admin(string username, string password);
        void options();
        void add_product(const string &products_file, vector<Product> &products, vector<Category> &categories);
        void edit_product(const string &products_file, vector<Product> &products);
        void remove_product(const string &products_file, vector<Product> &products);
        void search_product(const vector<Product> &products) const;
        void show_unavailable_products(const vector<Product> &products) const;
        static bool compare(const Product &a, const Product &b);
        void show_top5_products(const vector<Product> &products) const;
};

#endif