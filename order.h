#pragma once
#include "Product.h"
#include <vector>
#include <fstream>
#include <algorithm>
class Order {
private:
    vector<Product> items;
    string orderDate;
    string status;
public:
    Order() : orderDate("Not set"), status("Pending") {}
    void setDate(string date) { orderDate = date; }
    void setStatus(int choice) {
        if (choice == 1) status = "Pending";
        else if (choice == 2) status = "Completed";
        else if (choice == 3) status = "Cancelled";
        else status = "Unknown";
    }
    string getStatusString() const {
        return status;
    }
    void addProduct(Product p) {
        for (auto& item : items) {
            if (item.name == p.name) {
                item.quantity += p.quantity;
                return;
            }
        }
        items.push_back(p);
    }
    void removeProduct(string name) {
        items.erase(remove_if(items.begin(), items.end(),
            [&name](const Product& p) { return p.name == name; }), items.end());
    }
    void updateQuantity(string name, int newQty) {
        for (auto& item : items) {
            if (item.name == name) {
                item.quantity = newQty;
                return;
            }
        }
    }
    void showOrder() const {
        double totalPrice = 0;
        cout << "\n--- Current Order Details ---\n";
        cout << "Date: " << orderDate << " | Status: " << status << "\n";
        cout << "------------------------------------------\n";
        cout << left << setw(20) << "Product" << setw(10) << "Price" << setw(10) << "Qty" << endl;
        for (const auto& item : items) {
            item.display();
            totalPrice += item.price * item.quantity;
        }
        cout << "------------------------------------------\n";
        cout << right << setw(30) << "TOTAL PRICE: " << totalPrice << "\n";
        cout << "------------------------------------------\n";
    }
    static vector<Product> loadAvailableProducts(string filename) {
        vector<Product> available;
        ifstream file(filename);
        string name;
        double price;
        if (file.is_open()) {
            while (file >> name >> price) {
                available.push_back(Product(name, price, 0));
            }
            file.close();
        }
        return available;
    }
    void saveOrderToFile(string filename) {
        ofstream file(filename);
        if (file.is_open()) {
            double totalPrice = 0;
            file << "ORDER REPORT\nDate: " << orderDate << "\nStatus: " << status << "\n\n";
            for (const auto& item : items) {
                file << item.name << " | Qty: " << item.quantity << " | Total: " << item.price * item.quantity << "\n";
                totalPrice += item.price * item.quantity;
            }
            file << "\nGRAND TOTAL: " << totalPrice << "\n";
            file.close();
            cout << ">> Success: File created.\n";
        }
    }
};