#pragma once
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
class Product {
public:
    string name;
    double price;
    int quantity;
    Product(string n = "", double p = 0.0, int q = 0) : name(n), price(p), quantity(q) {}
    void display() const {
        cout << left << setw(20) << name << setw(10) << price << setw(10) << quantity << endl;
    }
};