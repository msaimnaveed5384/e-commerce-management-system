#include "Product.h"

Product::Product()
{
	ID=0;
	product_name = "";
	category = "";
	price = 0;
	quantity = 0;
	SellerID = 0;
	status = false;
}

Product::Product(int id, string name, string categ, int pric, int quant, int sell_id, bool stat)
{
	ID=id;
	product_name = name;
	category = categ;
	price = pric;
	quantity = quant;
	SellerID = sell_id;
	status = stat;
}

void Product::displayDetails()
{
}


void Product::applyDiscount()
{
}

int Product::getID()
{
	return ID;
}

string Product::getProductname()
{
	return product_name;
}

string Product::getcateg()
{
	return category;
}

int Product::getPrice()
{
	return price;
}

int Product::getQuantity()
{
	return quantity;
}

int Product::getSellerID()
{
	return SellerID;
}

string Product::getStatus()
{
	if (status)
	{
		return "Approved";
	}
	return "Unapproved";
}

void Product::setProductname(string pro_name)
{
	product_name = pro_name;
}

void Product::setcateg(string cat)
{
	category = cat;
}

void Product::setPrice(int pr)
{
	price = pr;
}

void Product::setQuantity(int quant)
{
	quantity = quant;
}

ElectronicsProduct::ElectronicsProduct(string warranty, int id, string name, string categ, int pric, int quant, int sell_id, bool stat):Product(id,name,categ,pric,quant,sell_id,stat)
{
	Warranty = warranty;
}

void ElectronicsProduct::displayDetails()
{
	cout << "\nProduct ID: " << ID
		<< "\nProduct Name: " << product_name
		<< "\nProduct Category: " << category
		<< "\nProduct Price: " << price << " PKR"
		<< "\nProduct Quantity: " << quantity
		<< "\nSeller ID: " << SellerID
		<< "\nProduct Status: ";
	if (status == true)
	{
		cout << "Approved";
	}
	else
	{
		cout << "UnApproved";
	}
	cout << "\nWarranty: " << Warranty<<" Months\n";
}

void ElectronicsProduct::applyDiscount()
{
   
}

string ElectronicsProduct::getwarranty()
{
	return Warranty;
}

void ElectronicsProduct::setwarranty(string warr)
{
	Warranty = warr;
}

BookProduct::BookProduct(string author, int id, string name, string categ, int pric, int quant, int sell_id, bool stat):Product(id, name, categ, pric, quant, sell_id, stat)
{
	Author = author;
}

void BookProduct::displayDetails()
{
	cout << "\nProduct ID: " << ID
		<< "\nProduct Name: " << product_name
		<< "\nProduct Category: " << category
		<< "\nProduct Price: " << price << " PKR"
		<< "\nProduct Quantity: " << quantity
		<< "\nSeller ID: " << SellerID
		<< "\nProduct Status: ";
	if (status == true)
	{
		cout << "Approved";
	}
	else
	{
		cout << "UnApproved";
	}
	cout << "\nAuthor Name: " << Author<<endl;
}

void BookProduct::applyDiscount()
{
}

string BookProduct::getAuthorName()
{
	return Author;
}

void BookProduct::setAuthorName(string aut_name)
{
	Author = aut_name;
}

ClothingProduct::ClothingProduct(string s, int id, string name, string categ, int pric, int quant, int sell_id, bool stat):Product(id, name, categ, pric, quant, sell_id, stat)
{
	size = s;
}

void ClothingProduct::displayDetails()
{
	cout << "\nProduct ID: " << ID
		<< "\nProduct Name: " << product_name
		<< "\nProduct Category: " << category
		<< "\nProduct Price: " << price<<" PKR"
		<< "\nProduct Quantity: " << quantity
		<< "\nSeller ID: " << SellerID
		<< "\nProduct Status: ";
	if (status == true)
	{
		cout << "Approved";
	}
	else
	{
		cout << "UnApproved";
	}
	cout << "\nSize: " << size<<endl;
}

void ClothingProduct::applyDiscount()
{
}

string ClothingProduct::getSize()
{
	return size;
}

void ClothingProduct::setSize(string size)
{
	this->size = size;
}
