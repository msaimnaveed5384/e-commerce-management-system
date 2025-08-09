#pragma once
#include "Product.h"
#include <vector>
#include <iostream>
using namespace std;

template<typename T>
class Cart {
    vector<Product*> items;

public:
    Cart& operator+=(Product* P) 
    {
        items.push_back(P);
        cout << "\nProduct added to cart successfully.\n";
        return *this;
    }

    // Remove a product from the cart
    Cart& operator-=(Product* P) {
        for (auto it = items.begin(); it != items.end(); ++it)
        {
            if ((*it)->getID() == P->getID()) {
                items.erase(it);
                cout << "\nProduct removed from cart.\n";
                break;
            }
            else
                cout << "\nNO Product FOUND IN cart.\n";
        }
        return *this;
    }

    // Display cart contents
    friend ostream& operator<<(ostream& os, const Cart& cart)
    {
        os << "\n--- Cart Contents ---\n";
        for (Product* item : cart.items) {
            item->displayDetails();
            os << "--------------------\n";
        }
        return os;
    }

    vector<Product*> getItems() const 
    {
        return items;
    }
    void clearCart()
    {
        items.clear();
    }
};
