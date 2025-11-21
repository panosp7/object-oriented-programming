#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "Category.h"
#include "Product.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

class Customer : public User {
    public:
        Customer(string username, string password);
        void options();
        void search_product(const vector<Product> &products) const;
        void add_product_to_cart(const vector<Product> &products);
        void update_product_from_cart(const vector<Product> &products);
        void remove_product_from_cart(const vector<Product> &products);
        void complete_order(const string &products_file, vector<Product> &products);
        void view_order_history(const vector<Product> &products) const;
        void view_cart(const vector<Product> &products) const;

    private:
        map<string, int> cart;
        vector<map<string, int>> order_history;
};

#endif