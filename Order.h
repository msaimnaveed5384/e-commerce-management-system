#pragma once
#include <iostream>
#include <vector>
#include "Product.h"
using namespace std;

class Order {
    int orderID;
    int day, month, year;
    float Total_Amount;
    bool Shipping_Status;
    vector<Product> Items;
    string buyerName;
public:
    Order();

    // Setters
    void setOrderID(int id);
    void setDate(int d, int m, int y);
    void setTotalAmount(float amount);
    void setShippingStatus(bool status);
    void addItem(const Product& p);
    void setBuyerName(const string& name);

    

    // Display
    void displayOrder() const;

    // Getters
    int getOrderID() const;
    // Inside public section of Order class
    string getBuyerName() const;
    string getDate() const;
    vector<Product> getItems() const;
    bool getShippingStatus() const;
    float getTotalAmount() const;
};
