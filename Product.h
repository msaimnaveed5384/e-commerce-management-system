#pragma once
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<string>
using namespace std;
//Base and specialized product types
class Product {
protected:
	int ID;
	string product_name;
	string category;
	int price;
	int quantity;
	int SellerID;
	bool status; //for checking by admina
public:
	Product();
	Product(int id, string name, string categ, int pric, int quant, int sell_id, bool stat);
	virtual void displayDetails();
	int getID();
	string getProductname();
	string getcateg();
	int getPrice();
	int getQuantity();
	int getSellerID();
	string getStatus();
	virtual void applyDiscount();
	void setProductname(string pro_name);
	void setcateg(string cat);
	void setPrice(int pr);
	void setQuantity(int quant);
};


class ElectronicsProduct :public Product {
	string Warranty;
public:
	ElectronicsProduct(string warranty, int id, string name, string categ, int pric, int quant, int sell_id, bool stat);
	void displayDetails() override;
	void applyDiscount() override;
	string getwarranty();
	void setwarranty(string warr);
};
class BookProduct :public Product {
	string Author;
public:
	BookProduct(string author, int id, string name, string categ, int pric, int quant, int sell_id, bool stat);
	void displayDetails() override;
	void applyDiscount() override;
	string getAuthorName();
	void setAuthorName(string aut_name);
};
class ClothingProduct :public Product {
	string size;  //S,M,L,XL
	
public:
	ClothingProduct(string s, int id, string name, string categ, int pric, int quant, int sell_id, bool stat);
	void displayDetails() override;
	void applyDiscount() override;
	string getSize();
	void setSize(string size);
};
