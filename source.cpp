#include "Order.h"
void printMenu() {
    cout << "\n--- MENU ---\n";
    cout << "1. List of products available to buy\n";
    cout << "2. Add product to cart\n";
    cout << "3. Remove product from cart\n";
    cout << "4. Change quantity\n";
    cout << "5. Set order date\n";
    cout << "6. Update order status\n";
    cout << "7. View my order\n";
    cout << "8. Export order to file\n";
    cout << "0. Exit\n";
    cout << "---------------------------\n";
    cout << "Your choice: ";
}
int main() {
    Order myOrder;
    ofstream file("stock.txt");
    if (file.is_open()) {
        file << "Laptop 70000\n";
        file << "Phone 15000\n";
        file << "Mouse 750\n";
        file << "Monitor 1350\n";
        file << "Keyboard 900\n";
        file << "Headphones 2000\n";
        file << "Webcam 600\n";
        file << "Power_Bank 999\n";
        file << "Table 700\n";
        file << "Chair 550\n";
        file << "Lamp 350\n";
        file.close();
    }
    vector<Product> stock = Order::loadAvailableProducts("stock.txt");
    cout << "--- WELCOME TO THE SHOP ---" << endl;
    int choice;
    do {
        printMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        switch (choice) {
        case 1:
            cout << "\nAvailable items:\n";
            for (int i = 0; i < (int)stock.size(); ++i) {
                cout << i + 1 << ". ";
                stock[i].display();
            }
            break;
        case 2: {
            int id, q;
            cout << "Enter product number: "; cin >> id;
            if (id > 0 && id <= (int)stock.size()) {
                cout << "Quantity: "; cin >> q;
                Product p = stock[id - 1];
                p.quantity = q;
                myOrder.addProduct(p);
                cout << ">> Added!\n";
            }
            break;
        }
        case 3: {
            string name;
            cout << "Enter product name: "; cin >> name;
            myOrder.removeProduct(name);
            break;
        }
        case 4: {
            string name;
            int q;
            cout << "Product name: "; cin >> name;
            cout << "New quantity: "; cin >> q;
            myOrder.updateQuantity(name, q);
            break;
        }
        case 5: {
            string d;
            cout << "Enter date: "; cin >> d;
            myOrder.setDate(d);
            break;
        }
        case 6: {
            int s;
            cout << "Status (1-Pending, 2-Completed, 3-Cancelled): "; cin >> s;
            myOrder.setStatus(s);
            break;
        }
        case 7:
            myOrder.showOrder();
            break;
        case 8:
            myOrder.saveOrderToFile("order_output.txt");
            break;
        case 0:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } 
    while (choice != 0);
    return 0;
}