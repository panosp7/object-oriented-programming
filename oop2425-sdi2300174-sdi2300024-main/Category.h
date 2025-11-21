#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
using namespace std;

//create this type for managing categories
struct Category{
    string category;
    vector<string> subcategories;
};

#endif