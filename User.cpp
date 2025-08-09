#include "User.h"
#include "FileManager.h"    
#include <conio.h>
using namespace std;

Buyer::Buyer(string name, string pass, string dob, string email):User(name,pass,dob, email){
	ROLE = BUYER;
}
int Buyer::BrowseProducts()
{
    Product* pro = nullptr;
    int choose;
        browseproductsfromfile();
        cout << "\nPress 1 to get a Cart\nPress 2 for Main Menu: ";
        int choice;
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(); // Discard invalid input
            cout <<"Invalid input. Please enter a number.";
        }
        if (choice == 2)
        {
            return 1;
        }
        else if (choice == 1)
        {

            cout << "\nCart Activated...";



            do {
                cout << "\n--------------------------";
                cout << "\n1. Add Item to Cart";
                cout << "\n2. Remove Item from Cart";
                cout << "\n3. Display Cart Items";
                cout << "\n4. Save & Exit";
                cout << "\nChoose: ";
                cin >> choose;

                switch (choose)
                {
                case 1:
                {
                    cout << "\nEnter Product ID: ";
                    int id;
                    cin >> id;

                    Product* original = FindProductFile(id);
                    if (!original) {
                        cout << "\nProduct not found. Please check the ID and try again.\n";
                        break;
                    }

                    Product* oneItem = nullptr;

                    try {
                        string category = original->getcateg();

                        if (category == "Electronics") {
                            ElectronicsProduct* ep = dynamic_cast<ElectronicsProduct*>(original);
                            if (ep == nullptr) throw "Invalid Electronics Product.";

                            oneItem = new ElectronicsProduct(
                                ep->getwarranty(),
                                ep->getID(), ep->getProductname(), ep->getcateg(),
                                ep->getPrice(), 1, ep->getSellerID(), true
                            );
                        }
                        else if (category == "Books") {
                            BookProduct* bp = dynamic_cast<BookProduct*>(original);
                            if (bp == nullptr) throw "Invalid Book Product.";

                            oneItem = new BookProduct(
                                bp->getAuthorName(),
                                bp->getID(), bp->getProductname(), bp->getcateg(),
                                bp->getPrice(), 1, bp->getSellerID(), true
                            );
                        }
                        else if (category == "Clothes") {
                            ClothingProduct* cp = dynamic_cast<ClothingProduct*>(original);
                            if (cp == nullptr) throw "Invalid Clothing Product.";

                            oneItem = new ClothingProduct(
                                cp->getSize(),
                                cp->getID(), cp->getProductname(), cp->getcateg(),
                                cp->getPrice(), 1, cp->getSellerID(), true
                            );
                        }
                        else {
                            throw "Unsupported product category.";
                        }

                        if (oneItem != nullptr) {
                            C += oneItem;
                            cout << "\n 1 unit of the product added to your cart.\n";
                        }

                    }
                    catch (const char* err) {
                        cout << "\nError: " << err << endl;
                    }

                    delete original;
                    break;
                }


                case 2:
                {
                    cout << "\nEnter Product ID to remove: ";
                    int id;
                    cin >> id;

                    bool removed = false;
                    vector<Product*> items = C.getItems();

                    for (Product* item : items) {
                        if (item->getID() == id) {
                            C -= item;
                            removed = true;
                            cout << "\nProduct removed from your cart.\n";
                            break;
                        }
                    }

                    if (!removed) {
                        cout << "\nProduct not found in your cart.\n";
                    }

                    break;
                }


                case 3:
                {
                    cout << C;
                    break;
                }

                case 4:
                {
                    cout << "\nSaving your cart and exiting...\n";
                    this->Checkout(C); // pass the cart
                    break;
                }

                default:
                    cout << "\nInvalid option. Try again.\n";
                }

            } while (choose != 4);
        }
}

void Buyer::searchProducts()
{
    int choose;
    bool repeat=false;
    do {
        cout << "Enter Product Name: ";
        string product_name;
        cin.ignore();
        getline(cin, product_name);
        if (FindProductFile(product_name))
        {
            Product* pro = nullptr;
           
            repeat = false;
            cout << "\nPress 1 to get a Cart\nPress 2 for Main Menu: ";
            int choice;
            cin >> choice;

            if (choice == 2)
            {
                return;
            }
            else if (choice == 1)
            {

                cout << "\nCart Activated...";


                    cout << "\n--------------------------";
                    cout << "\n1. Add Item to Cart";
                    cout << "\n2. Remove Item from Cart";
                    cout << "\n3. Display Cart Items";
                    cout << "\n5. Save & Exit";
                    cout << "\nChoose: ";
                    cin >> choose;

                    switch (choose)
                    {
                    case 1:
                    {
                        cout << "\nEnter Product ID: ";
                        int id;
                        cin >> id;

                        Product* original = FindProductFile(id);
                        if (!original) {
                            cout << "\nProduct not found. Please check the ID and try again.\n";
                            break;
                        }

                        Product* oneItem = nullptr;

                        try {
                            string category = original->getcateg();

                            if (category == "Electronics") {
                                ElectronicsProduct* ep = dynamic_cast<ElectronicsProduct*>(original);
                                if (ep == nullptr) throw "Invalid Electronics Product.";

                                oneItem = new ElectronicsProduct(
                                    ep->getwarranty(),
                                    ep->getID(), ep->getProductname(), ep->getcateg(),
                                    ep->getPrice(), 1, ep->getSellerID(), true
                                );
                            }
                            else if (category == "Books") {
                                BookProduct* bp = dynamic_cast<BookProduct*>(original);
                                if (bp == nullptr) throw "Invalid Book Product.";

                                oneItem = new BookProduct(
                                    bp->getAuthorName(),
                                    bp->getID(), bp->getProductname(), bp->getcateg(),
                                    bp->getPrice(), 1, bp->getSellerID(), true
                                );
                            }
                            else if (category == "Clothes") {
                                ClothingProduct* cp = dynamic_cast<ClothingProduct*>(original);
                                if (cp == nullptr) throw "Invalid Clothing Product.";

                                oneItem = new ClothingProduct(
                                    cp->getSize(),
                                    cp->getID(), cp->getProductname(), cp->getcateg(),
                                    cp->getPrice(), 1, cp->getSellerID(), true
                                );
                            }
                            else {
                                throw "Unsupported product category.";
                            }

                            if (oneItem != nullptr) {
                                C += oneItem;
                                cout << "\n1 unit of the product added to your cart.\n";
                            }

                        }
                        catch (const char* err) {
                            cout << "\nError: " << err << endl;
                        }

                        delete original;
                        break;
                    }


                    case 2:
                    {
                        cout << "\nEnter Product ID to remove: ";
                        int id;
                        cin >> id;

                        bool removed = false;
                        vector<Product*> items = C.getItems();

                        for (Product* item : items) {
                            if (item->getID() == id) {
                                C -= item;
                                removed = true;
                                cout << "\nProduct removed from your cart.\n";
                                break;
                            }
                        }

                        if (!removed) {
                            cout << "\nProduct not found in your cart.\n";
                        }

                        break;
                    }


                    case 3:
                    {
                        cout << C;
                        break;
                    }

                    case 5:
                    {
                        cout << "\nSaving your cart and exiting...\n";
                        this->Checkout(C); // pass the cart
                        return;
                    }
                    default:
                        cout << "\nInvalid option. Try again.\n";
                    }

            }
            else
            {
                repeat = true;
            }
        }
    } while (repeat||choose==4);
    
}



void Buyer::Checkout(Cart<int>& cart)
{
    if (cart.getItems().empty())
    {
        cout << "\nCart is empty. No order created.\n";
        return;
    }

    Order newOrder;
    int orderID = rand() % 9000 + 1000;

    newOrder.setOrderID(orderID);
    newOrder.setBuyerName(this->getusername());

    time_t now = time(0);
    tm* ltm = localtime(&now);
    newOrder.setDate(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);

    vector<Product*> items = cart.getItems();
    float total = 0;

    for (Product* p : items)
    {
        newOrder.addItem(*p);
        total += p->getPrice() * p->getQuantity();

        try {
            Product* original = FindProductFile(p->getID());
            if (!original)
                throw "Product not found in file.";

            int currentQty = original->getQuantity();
            int orderQty = p->getQuantity();

            if (orderQty > currentQty)
                throw "Not enough stock available to fulfill the order.";

            int newQty = currentQty - orderQty;
            original->setQuantity(newQty);

            UpdateProductFile(original);
            delete original;
        }
        catch (const char* msg) {
            cout << "\nError while updating product quantity: " << msg << "\n";
        }
    }

    newOrder.setTotalAmount(total);
    newOrder.setShippingStatus(false);

    saveOrderToFile(newOrder);
    cart.clearCart();

    cout << "\nOrder placed successfully. Order ID: " << orderID << "\n";
}

Buyer::~Buyer()
{
}



void Buyer::viewOrders()
{

    vieworders(this->getusername());
    cout << "Press any key for going back: ";
    _getch();
}

Admin::Admin(string name, string pass, string dob, string email) :User(name, pass, dob, email) {
	ROLE = ADMIN;
}
void Admin::ApproveProducts()
{
    int press;
    do {
     do {
        ApproveProductfromFile();
        cout << "\nEnter the Product ID for Approval: ";
        int product_id;cin >> product_id;
        ApproveProductByID(product_id);
      
        cout << "\nPress 1 to approve again\nPress 2 for admin portal.";
        cin >> press;
        if (press < 1 && press>2)
        {
            cout << "\nInvalid Choice";
        }
        }while (press < 1 && press>2);
    } while (press == 1);
    return;
}
void Admin::Manage()
{
   
    int choice;
    bool ischar = false;
    do {
        
        system("cls");
        cout << "------------------------ MANAGE ------------------------\n";
        cout << "1. Approve Pending Sellers          2. View Orders of a Buyer\n"
            << "3. Update Seller                    4. Remove a Buyer\n"
            << "5. Remove a Seller                  6. Delete Product \n"
            << "7. Show all Sellers                 8. Show all Buyers \n"

            << "9. Show Products of seller     10. Go back to Admin Portal\n";
        do
        {
            try {
                cout << "Select: ";cin >> choice;
                if (cin.fail())
                {
                    cin.clear(); // Clear the error flag
                    cin.ignore(); // Discard invalid input
                    ischar = true;
                    throw "Invalid input. Please enter a number.";
                }
                else
                {
                    ischar = false;
                    switch (choice)
                    {
                    case 1:
                    {
                        approveSellers();

                        cout << "\nPress Any Key to continue.....";
                        _getch();
                        break;
                    }
                    case 2:
                    {
                        string buyer;
                        cout << "Enter Buyer Username: ";
                        cin >> buyer;
                        vieworders(buyer);

                        cout << "\nPress Any Key to continue.....";
                        _getch();
                        break;
                    }

                    case 3:
                    {
                        updateSeller();

                        cout << "\nPress Any Key to continue.....";
                        _getch();
                        break;
                    }

                    case 4:
                    {
                        removeBuyer();
                        cout << "\nPress Any Key to continue.....";
                        _getch();
                        break;
                    }


                    case 5:
                    {
                        removeSeller();
                        cout << "\nPress Any Key to continue.....";
                        _getch();
                        break;
                    }

                    case 6:
                    {
                        deleteProductByAdmin();
                        cout << "\nPress Any Key to continue.....";
                        _getch();
                        break;
                    }

                    case 7:
                    {
                        cout << "\n----- All Sellers -----\n";
                        ShowAllSellersFromFile();  // Helper function in FileManager
                        cout << "\nPress Any Key to continue.....";
                        _getch();
                        break;
                    }

                    case 8:
                    {
                        cout << "\n----- All Buyers -----\n";
                        ShowAllBuyersFromFile();   // Helper function in FileManager
                        cout << "\nPress Any Key to continue.....";
                        _getch();
                        break;
                    }

                    case 9:
                    {
                        int sellerID;
                        cout << "Enter Seller ID: ";
                        cin >> sellerID;
                        ShowProductsBySellerID(sellerID);  // Helper function in FileManager
                        cout << "\nPress Any Key to continue.....";
                        _getch();
                        break;
                    }
                    case 10:
                    {
                        cout << "\nExiting Admin Portal...\n";
                    }
                    default:
                    {

                        throw "Invalid choice.\n";
                    }
                    }
                }
            }
            catch (const char* msg)
            {
                cout << "ERROR! " << msg << endl;
            }
		} while (ischar);
    } while (choice != 10);
}
   

void Admin::approveSellers()
{
  
        cout << "\n--- Pending Sellers ---\n";

    displayPendingSellers();
    int sellerID;
    do {
    
        cout << "\nEnter Seller ID to approve (0 to cancel): ";
        cin >> sellerID;

        if (sellerID == 0)
        {
            cout << "Approval cancelled.\n";
            return;
        }

        // Call FileManager function to approve seller
        updateSellerStatusByID(sellerID, "Approved");
    } while (sellerID != 0);
}

User::User() :username(""), password(""), DOB(""), Email("") {}
User::User(string name, string pass, string dob, string email):username(name),password(pass),DOB(dob),Email(email){}

string User::getusername()
{
	return username;
}

string User::getpassword()
{
	return password;
}

string User::getDOB()
{
	return DOB;
}

string User::getEmail()
{
	return Email;
}

User::~User()
{
}

Seller::Seller(string name, string pass, string dob, string email) :sellerid(rand() % 10000+1),status(false), User(name, pass, dob, email) {
	ROLE = SELLER;
}

Seller::Seller(string name, string pass, string dob, string email, int sell_id, bool stat):sellerid(sell_id), status(stat), User(name, pass, dob, email) {
	ROLE = SELLER;
}

void Seller::updateProduct() 
{
    bool repeat;
    do 
    {
        repeat = false;

        int product_id;
        string product_name;
        cout << "Enter Your Product ID (Confirmation): ";
        cin >> product_id;
        cout << "Enter Your Product Name (Confirmation): ";
        cin.ignore();
        getline(cin, product_name);

        Product* pro = FindProductFile(product_id, product_name, this->getsellerId());

        try {
            if (!pro)
                throw "Product not found or unauthorized access.";

            int choice;
            do {
                system("cls");
                cout << "\n---------Current Product Info---------\n";
                pro->displayDetails();

                cout << "\nWhat do you want to update?\n";
                cout << "1. Name\n2. Category\n3. Price\n4. Quantity\n";
                if (dynamic_cast<ElectronicsProduct*>(pro)) 
                {
                    cout << "5. Warranty\n";
                }
                else if (dynamic_cast<BookProduct*>(pro))
                {
                    cout << "5. Author\n";
                }
                else if (dynamic_cast<ClothingProduct*>(pro)) 
                {
                    cout << "5. Size\n";
                }
                cout << "6. Save & Exit\nEnter: ";

                cin >> choice;
                cin.ignore();

                string newInput;
                int intInput;

                switch (choice) {
                case 1:
                    {
                      cout << "New Name: "; getline(cin, newInput); pro->setProductname(newInput);
                      break;
                    }
                    
                case 2: 
                    {
                        cout << "New Category: ";
                        getline(cin, newInput);
                        pro->setcateg(newInput);
                        break;
                    }
                case 3: 
                {
                    cout << "New Price: ";
                    cin >> intInput;
                    pro->setPrice(intInput);
                    break;
                }
                case 4: 
                {
                    cout << "New Quantity: ";
                    cin >> intInput;
                    pro->setQuantity(intInput);
                    break;
                }
                case 5:
                    if (ElectronicsProduct* ep = dynamic_cast<ElectronicsProduct*>(pro))
                    {
                        cout << "New Warranty: "; 
                        getline(cin, newInput); 
                        ep->setwarranty(newInput);
                    }
                    else if (BookProduct* bp = dynamic_cast<BookProduct*>(pro))
                    {
                        cout << "New Author: "; 
                        getline(cin, newInput);
                        bp->setAuthorName(newInput);
                    }
                    else if (ClothingProduct* cp = dynamic_cast<ClothingProduct*>(pro))
                    {
                        cout << "New Size: "; 
                        getline(cin, newInput);
                        cp->setSize(newInput);
                    }
                    break;
                case 6:
                    UpdateProductFile(pro);
                    return;
                default:
                    throw "Invalid input. Please select from 1 to 6.";
                }

            } while (true);
        }
        catch (const char* msg) 
        {
            cout << "Error! " << msg << endl;
            repeat = true;
        }
    }while(repeat);
}

void Seller::deleteProduct()
{
    int product_id;
    string product_name;
    cout << "Enter Your Product ID (Confirmation): ";
    cin >> product_id;
    cout << "Enter Your Product Name (Confirmation): ";
    cin.ignore();
    getline(cin, product_name);

    Product* pro = FindProductFile(product_id, product_name, this->getsellerId());
    if (dynamic_cast<ElectronicsProduct*>(pro))
    {
        deleteProductFile(pro);
        cout << "\nElectronic Product deleted Successfully...";
    }
    else if (dynamic_cast<BookProduct*>(pro))
    {
      deleteProductFile(pro);
        cout << "\nBook Product deleted Successfully...";
    }
    else if (dynamic_cast<ClothingProduct*>(pro))
    {
        deleteProductFile(pro);
        cout << "\nClothing Product deleted Successfully...";
    }

}

void Seller::viewProducts()
{
    cout << "\nProducts listed for Seller("<<getusername()<< ") ID: " << getsellerId() << "\n";
    cout << "--------------------------------------------\n";
    ShowProductsBySellerID(this->getsellerId());
}



void Seller::AddProduct()
{
   
    srand(time(0));
    int ID = rand() % 10000;
    bool loop=false;
    do {
    try {
        cout << "Enter Product Name: ";
        string product_name;cin.ignore();getline(cin, product_name);

        cout << "Enter Product Price: ";
        int product_price;cin >> product_price;
        cout << "Enter Product Quantity: ";
        int product_quantity;cin >> product_quantity;
        int seller_id = sellerid;
        
            cout << "Enter Product Category(Electronics/Books/Clothes): ";
            string product_category;cin.ignore();getline(cin, product_category);
            Product* P;
            if (product_category == "Electronics")
            {
                string Warranty;
                cout << "Enter Warranty(months): ";
                cin >> Warranty;

                cout << "Your Product ID: " << ID;
                P = new ElectronicsProduct(Warranty, ID, product_name, product_category, product_price, product_quantity, seller_id, false);
                saveProductFile(P);
            }

            else if (product_category == "Books")
            {
                string Author;
                cout << "Enter Author Name: ";
                cin.ignore();
                getline(cin, Author);
                cout << "Your Product ID: " << ID;
                P = new BookProduct(Author, ID, product_name, product_category, product_price, product_quantity, seller_id, false);
                saveProductFile(P);
            }
            else if (product_category == "Clothes")
            {
                string size;
                cout << "Enter Size(S,M,L,XL): ";
                cin >> size;
                cout << "Your Product ID: " << ID;
                P = new ClothingProduct(size, ID, product_name, product_category, product_price, product_quantity, seller_id, false);
                saveProductFile(P);
            }
            else
            {
				loop = true;
                throw "Invalid Category...";
            }
		
    }
    catch (const string msg)
    {
		cout << "Error! " << msg << endl;
    }
    } while (false);

}


int Seller::getsellerId()
{
	return sellerid;
}

Seller::~Seller()
{
}

void Seller::viewOrders()
{
}

void Seller::RevenuePerProduct()
{
    
    int units = 0;
    int revenue = 0;
    cout << "\nRevenue Summary (Based on Orders)\n";
    cout << "----------------------------------------\n";
    getSellerRevenueFromOrders(this->getsellerId(), units, revenue);

   
}

string Seller::getstatus()
{
	if (status)
		return "Approved";
	return "Unapproved";
}



void Admin::viewReports() {
    cout << "\n------ REPORT SUMMARY ------\n";
    viewTotalRevenue();
    viewMostActiveUsers();
    cout << "-----------------------------\n";
}

void Admin::viewTotalRevenue() {
    cout << "\nTotal Revenue Across All Orders:\n";
    CalculateTotalRevenue();
}

void Admin::viewMostActiveUsers() {
    cout << "\nMost Active Users Based on Order Count:\n";
    DisplayMostActiveUsers();
}

Admin::~Admin()
{
}




