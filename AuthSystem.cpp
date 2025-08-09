#include "AuthSystem.h"

void Registration()
{
    cout << "--------------------\n"
        << " REGISTRATION FIELD \n"
        << "--------------------\n";
        cout << "Enter your Name: ";
        string username;

        cin.ignore();
        getline(cin, username);
        string Email;
        bool exist = false;
        do 
        {
            try
            {
                cout << "\nEnter your Email: ";
                cin >> Email;
                for (int i = 0; Email[i] != '\0'; i++) 
                {
                    if (Email[i] == '@') 
                    {
                        exist = true;
                        break;
                    }
                }
                if (!exist) 
                {
                    throw "Invalid email: Missing '@' symbol.";
                }
            }
            catch (const char* msg) 
            {
                cout << "Error: " << msg << endl;
            }
        } while (!exist);

        string DOB;
        do {
            try {
                cout << "Enter Your DOB (ex: 11/09/2001): ";
                cin >> DOB;

                if (DOB.length() != 10 || DOB[2] != '/' || DOB[5] != '/') {
                    throw "Incorrect format. Use DD/MM/YYYY with slashes at correct positions.";
                }
                for (int i = 0; i < DOB.length(); i++)
                {
                    if (i == 2 || i == 5) continue;
                    if (DOB[i] < '0' || DOB[i] > '9')
                    {
                        throw "Date components must contain only digits.";
                    }
                }

                int d = (DOB[0] - '0') * 10 + (DOB[1] - '0');
                int m = (DOB[3] - '0') * 10 + (DOB[4] - '0');
                int y = (DOB[6] - '0') * 1000 + (DOB[7] - '0') * 100 + (DOB[8] - '0') * 10 + (DOB[9] - '0');

                if (y < 1900 || y > 2025) 
                {
                    throw "Invalid year. Must be between 1900 and 2025.";
                }

                if (m < 1 || m > 12) 
                {
                    throw "Invalid month. Must be between 01 and 12.";
                }

                int maxDay = 31;
                if (m == 4 || m == 6 || m == 9 || m == 11)
                    maxDay = 30;
                else if (m == 2) 
                {
                    maxDay = 29;
                }

                if (d < 1 || d > maxDay)
                {
                    throw "Invalid day for the given month.";
                }

                break; 
            }
            catch (const char* msg) {
                cout << "\nError! " << msg << endl;
            }

        } while (true);

        string password;
        do {
            try {
                cout << "\nEnter Password(must be 8 characters long): ";
                cin.ignore();
                cin >> password;
                if (password.length() < 8) {
                    throw ("Password Too Short! Must be Atleast 8 characters Long.");
                }
            }
            catch (const char* msg) {
                cout << "\nError! " << msg << endl;
            }
        } while (password.length() < 8);

        string confirm_password;
        do {
            try {
                cout << "\nConfirm Password: ";
                cin.ignore();
                cin >> confirm_password;
                if (confirm_password != password) {
                    throw ("Password Didn't Matched.");
                }
            }
            catch (const char* msg) {
                cout << "\nError! " << msg << endl;
            }
        } while (confirm_password != password);

        cout << "\nEnter Your Role: \n1.ADMIN 2.SELLER 3.BUYER";
        int role;
        do {
            cout << "\nRole: ";
            try {
                cin >> role;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(); // Discard invalid input
                    throw"Input must be a number";
                }
                if (role < 1 || role > 3) {
                    throw "Invalid Choice....";
                }
            }
            catch (const char* msg) {
                cout << "\nError! " << msg << endl;
            }
        } while (role < 1 || role > 3);

        int chance = 1;
        string key;
        do {
            try {
                if (role == 1) {
                    cout << "Enter the Admin Key (Confirmation): ";
                    cin >> key;
                    if (key != "admin@fast" && chance == 1) {
                        chance--;
                        throw ("Invalid Admin Key...Last Try");
                    }
                    else if (key != "admin@fast" && chance == 0) {
                        chance--;
                        throw ("Invalid Admin Key Again...Registration Not Possible");
                    }
                    else {
                        cout << "\nContratulations! You are now an ADMIN";
                        Admin admin(username, password, DOB, Email);
                        SaveRegisterUsers(admin);  //File Saving
                        break;
                    }
                }
                else if (role == 2) {
                    cout << "\nContratulations! You are now an unapproved SELLER";
                    cout << "\nNote: Your Products Must be Approved by the Admin before Selling";
                    Seller seller(username, password, DOB, Email);
                    SaveRegisterUsers(seller);  //File Saving
                    break;
                }
                else {
                    cout << "\nContratulations! You are now a BUYER";
                    Buyer buyer(username, password, DOB, Email);
                    SaveRegisterUsers(buyer);  //File Saving
                    break;
                }
            }
            catch (const char* msg) {
                cout << "\nError! " << msg << endl;
                if(chance==-1)
                break;
            }
        } while (key != "Cfd$304324" && chance > -1);
}

User* Login()
{
    cout << "--------------------\n"
        << "        LOGIN       \n"
        << "--------------------\n";
    string username;
    string Password;
    int choice;
    do {
        cout << "\nUser Name: ";


        cin.ignore();
        getline(cin, username);
        cout << "\nPassword: ";

        cin >> Password;
        try {
            if (Admin* admin=dynamic_cast<Admin*>(FindUser(username, Password)))
            {
                cout << "\Successfully Login";

                return admin;
            }
            else if (Buyer* buyer = dynamic_cast<Buyer*>(FindUser(username, Password)))
            {
                cout << "\Successfully Login";
                return buyer;
            }
            else if (Seller* seller = dynamic_cast<Seller*>(FindUser(username, Password)))
            {
                if (seller->getstatus()=="Approved")
                {
                    cout << "\Successfully Login";
                    return seller;
                }
                else
                {
                    throw "\nYou Can Login after Admin Approval!";
                }
            }
            
            else if(User* user = dynamic_cast<User*>(FindUser(username, Password)))
                throw "\nNo User Credentials Found";
        }
        catch (const char* msg)
          {
            cout << "Error! " << msg << endl;
          }
        cout << "\n\nPress 1 for Main Menu"
            << "\nPress 2 for Login Again"
			<< "\nChoice: ";
      do{  cin >> choice;
        try 
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(); // Discard invalid input
                throw "Invalid input. Please enter a number.";
            }
            if (choice != 1 && choice != 2)
            {
                throw "Invalid Choice... ";
            }
            else if (choice == 1)
            {
                User* user=new User;
                return user; 
            }
           
                
        }
        catch (const char* msg)
        {
            cout << "Error! " << msg << endl;
            cout << "Choice: ";
        }
      } while (choice != 1 && choice != 2);

    } while (choice==2);
}
