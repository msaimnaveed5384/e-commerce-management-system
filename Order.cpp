#include "Order.h"
#define _CRT_SECURE_NO_WARNINGS
Order::Order() : orderID(0), day(0), month(0), year(0), Total_Amount(0.0), Shipping_Status(false) {}

void Order::setOrderID(int id) {
    orderID = id;
}

void Order::setDate(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
}

void Order::setTotalAmount(float amount) {
    Total_Amount = amount;
}

void Order::setShippingStatus(bool status) {
    Shipping_Status = status;
}

void Order::addItem(const Product& p) {
    Items.push_back(p);
}

int Order::getOrderID() const {
    return orderID;
}

void Order::setBuyerName(const string& name) {
    buyerName = name;
}


void Order::displayOrder() const {
    cout << "\nOrder ID: " << orderID;
    cout << "\nDate: " << day << "/" << month << "/" << year;
    cout << "\nShipping Status: " << (Shipping_Status ? "Shipped" : "Pending");
    cout << "\nProducts:";
    for ( Product p : Items) {
        cout << "\n - " << p.getProductname()
             << " | Category: " << p.getcateg()
             << " | Price: " << p.getPrice()
             << " | Qty: " << p.getQuantity();
    }
    cout << "\nTotal Amount: " << Total_Amount << " PKR\n";
    cout << "-------------------------------------------\n";
}

string Order::getBuyerName() const {
    return buyerName;
}

string Order::getDate() const {
    return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}

vector<Product> Order::getItems() const {
    return Items;
}

bool Order::getShippingStatus() const {
    return Shipping_Status;
}

float Order::getTotalAmount() const
{
    return Total_Amount;
}
