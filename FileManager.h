#pragma once
class User;
#include <ctime> // for time-related functions
#include "Order.h"
#include "User.h"
#include<string>
#include<vector>
#include<fstream>  // For file handling
#include <iomanip>

//string trim(const string& str);
//Read/write user/product/order data

void browseproductsfromfile();

void saveOrderToFile(const Order& order);


void vieworders(const string& buyerName);
User* FindUser(string name, string pass); //for finding user for login



Product* FindProductFile(int ID);
bool FindProductFile(string name);

void UpdateProductFile(Product* product);
void SaveRegisterUsers(User& user);

void ApproveProductfromFile();

void getSellerRevenueFromOrders(int sellerID, int& totalUnitsSold, int& totalRevenue);
void CalculateTotalRevenue();
void  DisplayMostActiveUsers();

//Admin Management
void updateSeller();     //updated
void removeSeller();    //updated
void displayPendingSellers();   //updated before approving sellers

void updateSellerStatusByID(int sellerID, const string& newstat);  //updated

void ApproveProductByID(int target_id);   //updated

void removeBuyer();//updated

void ShowAllSellersFromFile(); //done thorugh id
void ShowAllBuyersFromFile();  //done through username and email

void deleteProductByAdmin();
//void viewSellerProducts(int sellerID);




//Seller
void saveProductFile(Product* product);//main seller case 1/2
void ShowProductsBySellerID(int sellerID);//main seller case 2
Product* FindProductFile(int ID, string name, int currentSellerID);   //main seller case 2/3
void deleteProductFile(Product* product);  //main seller case 3
