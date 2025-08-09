// main.cpp
#include "AuthSystem.h"
#include "FileManager.h"
#include "User.h"
#include <iostream>
#include <conio.h>  //or colors
#include <cstdlib> //for random numbers and other utilities
#include <ctime>  //provides time related functions
using namespace std;

int main() {

    bool program_Continue = true;
    do {
        //srand seeds a value for rand()
        srand(time(0)); //time(0) or time(NULL) gives current time in seconds
        system("cls");
        system("Color F");
        cout << "+--------------------------------------------------------+\n";
        cout << "|             WELCOME TO SAIM'S SHOPPING CENTRE          |\n";
        cout << "+--------------------------------------------------------+\n";

        cout << "1. Login\n"
            << "2. Register\n"
            << "3. Info\n"
            << "4. Exit\n";

        cout << "----------------------------------------------------------\n";
        cout << "Enter your choice: ";
        int choice; cin >> choice;
        try {
            switch (choice) {
            case 1: {
                int press;
                int user_choice;
                do {
                    system("cls");
                    system("Color 3F");
                    User* user = Login(); // Call Login() ONCE

                    if (Admin* admin = dynamic_cast<Admin*>(user)) {
                        cout << "\nPress Any Key to continue.....";
                        _getch();
                        do
                        {
                            system("Color CF");
                            system("cls");
                            cout << "--------------------\n"
                                << "       ADMIN         \n"
                                << "--------------------\n";
                            cout << "----------------------------------------------------------\n";
                            cout << "\n1.Manage (Buyers/Sellers)"
                                << "\n2.View Reports"
                                << "\n3.Approve Products"
                                << "\n4.Total Revenue"
                                << "\n5.Most Active Users"
                                << "\n6.Log Out";
                            cout << "\nChoice: ";
                            cin >> user_choice;
							if (cin.fail())
							{
								cin.clear(); // Clear the error flag
								cin.ignore(); // Discard invalid input
								cout << "Invalid input. Please enter a number.\n";
							}
                            if (user_choice == 6)
                            {
                                delete admin;
                                admin = nullptr;
                            }
                            else if (user_choice == 3)
                            {
                                admin->ApproveProducts();
                            }
                            else if (user_choice == 1)
                            {
                                admin->Manage();
                            }
                            else if (user_choice == 2)
                            {
                                admin->viewReports();
                                cout << "\nPress Any Key to continue.....";
                                _getch();
                            }
                            else if (user_choice == 4)
                            {
                                admin->viewTotalRevenue();
                                cout << "\nPress Any Key to continue.....";
                                _getch();
                            }
                            else if (user_choice == 5)
                            {
                                admin->viewMostActiveUsers();
                                cout << "\nPress Any Key to continue.....";
                                _getch();
                            }

                        } while (user_choice != 6);

                    }
                    else if (Seller* seller = dynamic_cast<Seller*>(user)) {
                        do {
                            cout << "\nPress Any Key to continue.....";
                            _getch();
                            system("Color E0");
                            system("cls");
                            cout << "--------------------\n"
                                << "       SELLER         \n"
                                << "--------------------\n";
                            cout << "----------------------------------------------------------\n";
                            cout << "\n1. Add Product"
                                << "\n2. Update Product"
                                << "\n3. Delete Product"
                                << "\n4. Revenue Per Product"
                                << "\n5. View Products"
                                << "\n6. Log Out";
                            cout << "\nChoice: "; cin >> user_choice;
                            if (cin.fail())
                            {
								cin.clear(); // Clear the error flag
								cin.ignore(); // Discard invalid input
								cout << "Invalid input. Please enter a number.\n";
                            }
                            if (user_choice == 6)
                            {
                                delete seller;
                                seller = nullptr;
                            }
                            else if (user_choice == 1)
                            {
                                seller->AddProduct();
                            }
                            else if (user_choice == 2)
                            {
                                seller->updateProduct();
                            }
                            else if (user_choice == 3)
                            {
                                seller->deleteProduct();
                            }
                            else if (user_choice == 4)
                            {
                                seller->RevenuePerProduct();
                            }
                            else if (user_choice == 5)
                            {
                                seller->viewProducts();
                            }
                        } while (user_choice != 6);
                    }

                    else if (Buyer* buyer = dynamic_cast<Buyer*>(user)) {

                        bool cont = true;
                        do {
                            cout << "\nPress Any Key to continue.....";
                            _getch();
                            system("Color 9F");
                            system("cls");
                            cout << "--------------------\n"
                                << "         BUYER        \n"
                                << "--------------------\n";
                            cout << "----------------------------------------------------------\n";
                            cout << "\n1.Browse Product"
                                << "\n2.Search Product"
                                << "\n3.View My Orders"
                                << "\n6.Log Out";
                            cout << "\nChoice: "; cin >> user_choice;
							if (cin.fail())
							{
								cin.clear(); // Clear the error flag
								cin.ignore(); // Discard invalid input
								cout << "Invalid input. Please enter a number.\n";
							}
                            if (user_choice == 6)
                            {
                                delete buyer;
                                buyer = nullptr;
                                cont = false;
                            }
                            if (user_choice == 1)
                            {
                                buyer->BrowseProducts();

                            }
                            else if (user_choice == 2)
                            {
                                buyer->searchProducts();
                            }
                            else if (user_choice == 3)
                            {
                                buyer->viewOrders();
                            }
                        } while (cont);
                    }
                    else if (User* use = dynamic_cast<User*>(user)) {
                        delete use;
                        break;
                    }
                    if (user_choice == 6 && user != nullptr)
                    {
                        user = nullptr;
                    }
                } while (user_choice != 6);
                break;
            }

            case 2:
                system("cls");
                system("Color 6F");

                Registration();  //Check Through Authentication
                break;

            case 3:
                system("cls");
                system("Color 2F");
                cout << "--------------------\n"
                    << "       INFO          \n"
                    << "--------------------\n";
                cout << "----------------------------------------------------------\n";
                cout << "This is a simple shopping management system.\n"
                    << "It allows users to register as buyers or sellers.\n"
                    << "Admins can manage users and approve products.\n"
                    << "Buyers can browse products, add to cart, and place orders.\n"
                    << "Sellers can add, update, and delete their products.\n"
                    << "The system uses file-based persistence for user data.\n"
                    << "Developed by SAIM.\n"
                    << "Version 1.0\n"
                    << "Date: 02-08-2025\n";

                break;

            case 4:
                program_Continue = false;
                break;
            default:
                
            {
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(); // Discard invalid input
                    throw "Invalid input. Please enter a number.";
                }
                cout << "Invalid Input";
            }
            }

            cout << "\nPress Any Key to continue.....";
            _getch();
		}
        catch (const char* msg) 
        {
            cout << "Error: " << msg << endl;
            cout << "\nPress Any Key to continue.....";
            _getch();
        }
    } while (program_Continue);

    return 0;
}
