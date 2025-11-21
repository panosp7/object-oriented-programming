#include "Product.h"
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
//initialize product details with starting values
Product::Product() : title(""), description(""), category(""), subcategory(""), price(0.0), quantity(0), measurement(""){}
Product::Product(string in_title, string in_description, string in_category, string in_subcategory, double in_price, int in_quantity, string in_measurement)
            : title(in_title), description(in_description), category(in_category), subcategory(in_subcategory), price(in_price), quantity(in_quantity), measurement(in_measurement){}
//we set the title, description, category, subcategory, price, quantity
void Product::set_title(string in_title){
    title = in_title;
}
void Product::set_description(string in_description){
    description = in_description;
}
void Product::set_category(string in_category){
    category = in_category;
}
void Product::set_subcategory(string in_subcategory){
    subcategory = in_subcategory;
}
void Product::set_price(double in_price){
    price = in_price;
}
void Product::set_quantity(int in_quantity){
    quantity = in_quantity;
}
//we get the title, description, category, subcategory, price, quantity and measurement type 
string Product::get_title() const{
    return title;
}
string Product::get_description() const{
    return description;
}
string Product::get_category() const{
    return category;
}
string Product::get_subcategory() const{
    return subcategory;
}
double Product::get_price() const{
    return price;
}
int Product::get_quantity() const{
    return quantity;
}
string Product::get_measurement() const{
    return measurement;
}

void Product::show_product() const{ //display the characteristics of the product
    cout << endl << "-----" << title << "-----" << endl;
    cout << "Description: " << description << "\nCategory: " << category << "\nSubcategory: " << subcategory << "\nPrice per " << measurement << ": " << price << "€" << endl;
    if (trim(measurement) == "Unit"){ //show the availability
        cout << "Total units Available: ";
    } else {
        cout << "Total kg Available: ";
    }
    cout << quantity << endl;
}