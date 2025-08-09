#pragma once
//Base and derived classes for user roles
#define _CRT_SECURE_NO_WARNINGS
#include "Cart.h"
#include "Order.h"
#include "Product.h"
#include <cstdlib>
#include<iostream>
#include<string>
#include "FileManager.h"
#include <ctime> // for date
using namespace std;
class User {
protected:
	string username;
	string password;
	string DOB;
	string Email;
public:
	User();
	User(string name, string pass, string dob, string email);
	enum role { ADMIN=1, SELLER=2, BUYER=3 }ROLE;
	string getusername();
	string getpassword();
	string getDOB();
	string getEmail();
	virtual ~User();
};
class Admin:public User {
	string admin_key = "Cfd$304324";
public:
	//o Manage platform users (sellers/buyers)
	//o View reports
	//o Approve products
	Admin(string name, string pass, string dob, string email);
	void ApproveProducts();
	void Manage();
	void approveSellers();
	void viewReports();
	void viewTotalRevenue();       // NEW FUNCTION for option 4
	void viewMostActiveUsers();    // NEW FUNCTION for option 5
	~Admin();
};

class Seller:public User {
	int sellerid;
	bool status;
	//Order associated with Buyer and relevant Sellers
public:
	Seller(string name, string pass, string dob, string email);
	Seller(string name, string pass, string dob, string email,int sell_id,bool stat);
	void AddProduct();
	void updateProduct();
	void deleteProduct();
	void viewProducts();
	//View orders placed for their products
	void viewOrders();
	void RevenuePerProduct();
	string getstatus();
	int getsellerId();
	~Seller();
};

class Buyer:public User 
{
	//Buyer has a Cart
	Cart<int> C;

	//Order associated with Buyer and relevant Sellers
public:
	Buyer(string name, string pass, string dob, string email);
	//Register / login
	//o Browse / search products
	//o Add to cart, checkout, view orders
	int BrowseProducts();
	void searchProducts();
	void viewOrders();
	void Checkout(Cart<int>& cart);
	~Buyer();
};
