#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
using namespace std;

class Product {
    public:
        Product();
        Product(string in_title, string in_description, string in_category, string in_subcategory, double in_price, int in_quantity, string in_measurement);
        void set_title(string in_title);
        void set_description(string in_description);
        void set_category(string in_category);
        void set_subcategory(string in_subcategory);
        void set_price(double in_price);
        void set_quantity(int in_quantity);
        string get_title() const;
        string get_description() const;
        string get_category() const;
        string get_subcategory() const;
        double get_price() const;
        int get_quantity() const;
        string get_measurement() const;
        void show_product() const;

    private:
        string title, description, category, subcategory, measurement;
        double price;
        int quantity;
};

#endif