#include "FileManager.h"

void saveProductFile(Product* product)
{
    ofstream product_file("Products.txt", ios::app);
    try {
        if (!product_file.is_open())
        {
            throw " Could not open file to save Products.\n";
        }
        else
        {
            if (ElectronicsProduct*EP=dynamic_cast<ElectronicsProduct*>(product))
            {
             
                product_file << "Product ID: " << product->getID()
                    << "\nSeller ID: " << product->getSellerID()
                    << "\nProduct Name: " << product->getProductname()
                    << "\nCategory: " << product->getcateg()
                    << "\nPrice: " << product->getPrice()
                    << "\nQuantity: " << product->getQuantity()
                  
                    << "\nStatus: " << product->getStatus()
                    << "\nProduct Warranty: " << EP->getwarranty()<<" Months"
                << "\n--------------------------------\n";
                product_file.close();
                cout << "\nElectronicsProduct saved to file successfully.\n";
                delete EP;
            }
            
            else if (BookProduct* BP = dynamic_cast<BookProduct*>(product))
            {
                product_file << "Product ID: " << product->getID()
                    << "\nSeller ID: " << product->getSellerID()
                    << "\nProduct Name: " << product->getProductname()
                    << "\nCategory: " << product->getcateg()
                    << "\nPrice: " << product->getPrice()
                    << "\nQuantity: " << product->getQuantity()
                    
                    << "\nStatus: " << product->getStatus()
                    << "\nAuthor Name: " << BP->getAuthorName()
                << "\n--------------------------------\n";
                product_file.close();
                cout << "\nBookProduct saved to file successfully.\n";
                delete BP;
            }

            else if (ClothingProduct* CP = dynamic_cast<ClothingProduct*>(product))
            {
                product_file << "Product ID: " << product->getID()
                    << "\nSeller ID: " << product->getSellerID()
                    << "\nProduct Name: " << product->getProductname()
                    << "\nCategory: " << product->getcateg()
                    << "\nPrice: " << product->getPrice()
                    << "\nQuantity: " << product->getQuantity()
                    
                    << "\nStatus: " << product->getStatus()
                    << "\nSize: " << CP->getSize()
                    << "\n--------------------------------\n";
                product_file.close();
                cout << "\nClothingProduct saved to file successfully.\n";
                delete CP;
            }

        }
    }
    catch (const char* c)
    {
        cout << "\nError! " << c << endl;
    }
}

void deleteProductFile(Product* product)
{
    try
    {
        ifstream in("Products.txt");
        if (!in) {
            throw "Error opening Products.txt.";
        }

        vector<string> lines;
        string line;

        while (getline(in, line)) {
            lines.push_back(line);
        }

        in.close();

        vector<string> updatedLines;
        bool found = false;

        for (int i = 0; i < lines.size(); i++)
        {
            if (lines[i] == "Product ID: " + to_string(product->getID()))
            {
                found = true;

                int start = i;
                // Move to the end of block ("--------------------------------")
                while (i < lines.size() && lines[i] != "--------------------------------") {
                    i++;
                }
                if (i < lines.size())
                    i++; // Skip the separator too

                // Now, i is at the line after the block. Skip block completely.
                continue;
            }

            // Copy non-deleted lines
            updatedLines.push_back(lines[i]);
        }

        if (!found) {
            throw "Product ID not found.";
        }

        ofstream out("Products.txt");
        if (!out) {
            throw "Error opening Products.txt for writing.";
        }

        for (int i = 0;i < updatedLines.size();i++) {
            out << updatedLines[i] << endl;
        }

        out.close();
        cout << "Product deleted successfully.\n";

    }
    catch (const char* msg) {
        cout << "ERROR: " << msg << endl;
    }
}


Product* FindProductFile(int ID, string name, int currentSellerID) 
{
    ifstream file("Products.txt");
    if (!file.is_open()) {
        cout << "Error opening Products.txt\n";
        return nullptr;
    }

    string line;
    int prod_id = -1;
    int price = 0;
    int quantity = 0;
    int seller_id = -1;
    string product_name = "";
    string category = "";
    string warranty = "";
    string author = "";
    string size = "";
    string status_str = "";
    bool status = false;

    while (getline(file, line)) 
    {
        if (line.find("Product ID: ") == 0)
        {
            prod_id = stoi(line.substr(12));
        }   
        else if (line.find("Seller ID: ") == 0)
        {
            seller_id = stoi(line.substr(11));
        }
        else if (line.find("Product Name: ") == 0)
        {
            product_name = line.substr(14);
        }
        else if (line.find("Category: ") == 0)
        {
            category = line.substr(10);
        }
        else if (line.find("Price: ") == 0)
        {
            price = stoi(line.substr(7));
        }
        else if (line.find("Quantity: ") == 0)
        {
            quantity = stoi(line.substr(10));
        }
        else if (line.find("Status: ") == 0)
        {
            status = (line.substr(7) == "Approved");
        }
        else if (line.find("Product Warranty: ") == 0)
        {
            warranty = line.substr(18);
        }
        else if (line.find("Author Name: ") == 0)
        {
            author = line.substr(13);
        }
        else if (line.find("Size: ") == 0)
        {
            size = line.substr(6);
        }

        else if (line.find("----------------------") == 0)
        {
            // DEBUG: Show what was collected
           /* cout << "\nDEBUG CHECK:"
                << "\nEntered ID: " << ID
                << "\nEntered Name: " << name
                << "\nFile ID: " << prod_id
                << "\nFile Name: " << product_name
                << "\nSeller ID (expected): " << currentSellerID
                << "\nSeller ID (file): " << seller_id << endl;*/

            // Case-insensitive match
            bool nameMatch = false;
            if (name == product_name)
            {
                nameMatch = true;
            }
            else {
                /*for (int i = 0; i < name.length(); i++) {
                    if (tolower(name[i]) != tolower(product_name[i])) {
                        nameMatch = false;
                        break;
                    }
                }*/
            }

            if (prod_id == ID && nameMatch && seller_id == currentSellerID)
            {/*
                string cleanCategory = trim(category);*/

                if (category == "Electronics") {
                    return new ElectronicsProduct(warranty, prod_id, product_name, category, price, quantity, seller_id, status);
                }
                else if (category == "Books") {
                    return new BookProduct(author, prod_id, product_name, category, price, quantity, seller_id, status);
                }
                else if (category == "Clothes") {
                    return new ClothingProduct(size, prod_id, product_name, category, price, quantity, seller_id, status);
                }
                else {
                    cout << "Product matched but unknown category: [" << category << "]" << endl;
                }

            }

            // Reset for next block
            prod_id = price = quantity = seller_id = -1;
            product_name = category = warranty = author = size = "";
            status = false;
        }
    }

    cout << "Error! Product not found or seller mismatch.\n";
    return nullptr;
}

Product* FindProductFile(int ID)
{
    bool pro_found = false;
    string line = "";
    ifstream product_file("Products.txt"); // fixed typo
    try {
        if (!product_file.is_open()) {
            throw "Product File can't open.";
        }
        else {
            string product_name = "", category = "", warranty = "", author = "", size = "";
            int price, quantity, seller_id;
            bool status = false;

            while (getline(product_file, line)) 
            {
                if (line.find("Product ID: ") == 0) 
                {
                    int id = stoi(line.substr(12));
                    if (id == ID) 
                    {
                        pro_found = true;

                        getline(product_file, line);
                        seller_id = stoi(line.substr(11));
                        
                        getline(product_file, line);
                        product_name = line.substr(14);
                        
                        getline(product_file, line);
                        category = line.substr(10);

                        getline(product_file, line);
                        price = stoi(line.substr(7));
                        
                        getline(product_file, line); 
                        quantity = stoi(line.substr(10));
                        
                        getline(product_file, line);
                        status = (line.substr(8) == "Approved");
                        getline(product_file, line); 

                        if (category == "Electronics") 
                        {
                            warranty = line.substr(18);
                            return new ElectronicsProduct(warranty, ID, product_name, category, price, quantity, seller_id, status);
                        }
                        else if (category == "Books")
                        {
                            author = line.substr(13);
                            return new BookProduct(author, ID, product_name, category, price, quantity, seller_id, status);
                        }
                        else if (category == "Clothes")
                        {
                            size = line.substr(6);
                            return new ClothingProduct(size, ID, product_name, category, price, quantity, seller_id, status);
                        }
                        else {
                            throw "Unknown category found.";
                        }
                    }
                }
            }
            if (!pro_found) 
            {
                throw "Product not found.";
            }
        }
    }
    catch (const char* msg)
    {
        cout << "Error! " << msg << endl;
    }
    return nullptr;
}

bool FindProductFile(string name)
{
    string pro_id;
    string line;
    string pro_name;
    bool name_find=false;
    bool found=false;
    ifstream product_file("Products.txt");
    try {
        if (!product_file.is_open())
        {
            throw"Product File is note opening";
        }
        else {
            line = "";
            while (getline(product_file, line))
            {
                if (line.find("Product Name: ")==0)
                {
                    pro_name = line.substr(14);
                    if (pro_name == name)
                    {
                        name_find = true; 
                        found = true;
                        cout <<"\n---------------------------"<< endl;
                        cout << line<< "   ";
                        cout <<"Product ID: "<< pro_id << "   ";
                    }
                }
                if (line.find("Category: ") == 0)
                {
             
                    if (name_find)
                    cout << line << "   ";
                }
                else if (line.find("Product Warranty: ") == 0)
                {
      
                    if (name_find)
                    {
                        cout << line;
                        name_find = false;
                    }
                        
                }
                else if (line.find("Size: ") == 0)
                {
                 
                    if (name_find)
                    {
                        cout << line;
                        name_find = false;
                    }
                }
                else if (line.find("Author Name: ") == 0)
                {
  
                    if (name_find)
                    {
                        cout << line;
                        name_find = false;
                    }
                }
                else if (line.find("Price: ") == 0)
                {
                   
                    if (name_find)
                        cout << line <<endl;
                }
                else if (line.find("Quantity: ") == 0)
                {
                   
                    if (name_find)
                        cout << line<< "   ";
                }
                else if (line.find("Product ID: ") == 0)
                {
                    pro_id = line.substr(12);
                    if (name_find)
                        cout << line << "   ";
                }
                
            }
            if (!found)
            {
                throw"No Product Found";
                return false;
            }
            return true;
        }
    }
    catch (const char* msg)
    {
        cout << "Error! " << msg << endl;
        return false;
    }
}


void ApproveProductByID(int product_id)
{
    ifstream file_in("Products.txt");
    ofstream file_out("Temp.txt");

    string line;
    int found = 0; // 0 = not found, 1 = unapproved found, 2 = already approved
    int match_id = 0;

    try {
        if (!file_in.is_open() || !file_out.is_open())
        {
            throw "File can't be opened";
        }

        while (getline(file_in, line))
        {
            if (line.find("Product ID: ") == 0) 
            {
                int id = 0;
                for (int i = 12; i < line.length(); i++) 
                {
                        id = id * 10 + (line[i] - '0');
                }

                if (id == product_id)
                {
                    match_id = 1;
                }
                else
                {
                    match_id = 0;
                }
            }

            if (match_id == 1 && line == "Status: Unapproved") 
            {
                line = "Status: Approved";
                found = 1;
                match_id = 0;
            }
            else if (match_id == 1 && line == "Status: Approved")
            {
                found = 2;
                match_id = 0;
            }

            file_out << line << endl;
        }
        file_in.close();
        file_out.close();
        remove("Products.txt");
        rename("Temp.txt", "Products.txt");
        if (found == 1) 
        {
            cout << "Product ID " << product_id << " has been approved.\n";
        }
        else if (found == 2)
        {
            cout << "Product ID " << product_id << " is already approved.\n";
        }
        else
        {
            cout << "Invalid Product ID.\n";
        }
    }
    catch (const char* error) 
    {
        cout << "Error: " << error << endl;
    }
}


void UpdateProductFile(Product* product)
{
    try
    {
        ifstream infile("Products.txt");
        if (!infile) {
            throw "Error: Cannot open Products.txt for reading.";
        }

        vector<string> lines;
        string line;
        while (getline(infile, line))
        {
            lines.push_back(line);
        }
        infile.close();

        vector<string> updatedLines;
        bool found = false;

        for (int i = 0; i < lines.size(); i++)
        {
            if (lines[i] == "Product ID: " + to_string(product->getID()))
            {
                found = true;

                // Add lines before this product
                for (int j = 0; j < i; j++)
                {
                    updatedLines.push_back(lines[j]);
                }

                // Add updated product block
                updatedLines.push_back("Product ID: " + to_string(product->getID()));
                updatedLines.push_back("Seller ID: " + to_string(product->getSellerID()));
                updatedLines.push_back("Product Name: " + product->getProductname());
                updatedLines.push_back("Category: " + product->getcateg());
                updatedLines.push_back("Price: " + to_string(product->getPrice()));
                updatedLines.push_back("Quantity: " + to_string(product->getQuantity()));
                updatedLines.push_back("Status: " + product->getStatus());

               
                if (ElectronicsProduct* ep = dynamic_cast<ElectronicsProduct*>(product)) {
                    updatedLines.push_back("Product Warranty: " + (ep->getwarranty()) + " Months");
                }
                else if (BookProduct* bp = dynamic_cast<BookProduct*>(product)) {
                    updatedLines.push_back("Author Name: " + bp->getAuthorName());
                }
                else if (ClothingProduct* cp = dynamic_cast<ClothingProduct*>(product)) {
                    updatedLines.push_back("Size: " + cp->getSize());
                }

                updatedLines.push_back("--------------------------------");

                while (i < lines.size() && lines[i] != "--------------------------------") 
                {
                    i++;
                }

                continue;
            }

          
            updatedLines.push_back(lines[i]);
        }

        if (!found) {
            throw "Product ID not found.";
        }

        ofstream outfile("Products.txt");
        if (!outfile) {
            throw "Error: Cannot open Products.txt for writing.";
        }

        for (int i = 0;i < updatedLines.size();i++) {
            outfile << updatedLines[i] << endl;
        }

        outfile.close();
        cout << "Product updated successfully.\n";

    }
    catch (const char* msg) {
        cout << "ERROR: " << msg << endl;
    }
}



void SaveRegisterUsers(User& user)
{
	if (Seller* s = dynamic_cast<Seller*>(&user))
	{
		if (s->getstatus() == "Unapproved")
		{
			ofstream userFile("Seller.txt", ios::app); 
			try {
				if (!userFile.is_open())
				{
					throw " Could not open file to save user data.\n";
				}
				else
				{
					userFile << "User Name: " << s->getusername()
						<< "\nEmail: " << s->getEmail()
						<< "\nDate Of Birth: " << s->getDOB()
						<< "\nPassword: " << s->getpassword()
						<< "\nRole: Seller"
						<< "\nSeller ID: " << s->getsellerId()
						<< "\nSeller Status: " << s->getstatus();
					userFile << "\n-----------------------------" << endl;
					userFile.close();
					cout << "\nUnapproved seller saved to file successfully.\n";
				}
			}
			catch (const char* msg) {
				cout << "\nError! " << msg << endl;
			}
		}
	}
	else if (Buyer* b = dynamic_cast<Buyer*>(&user))
	{
		ofstream userFile("Buyer.txt", ios::app); 
		try {
			if (!userFile.is_open())
			{
				throw " Could not open file to save user data.\n";
			}
			else
			{
				userFile << "User Name: " << b->getusername()
					<< "\nEmail: " << b->getEmail()
					<< "\nDate Of Birth: " << b->getDOB()
					<< "\nPassword: " << b->getpassword()
					<< "\nRole: Buyer";
				userFile << "\n-----------------------------" << endl;
				userFile.close();
				cout << "\nBuyer saved to file successfully.\n";
			}
		}
		catch (const char* msg) {
			cout << "\nError! " << msg << endl;
		}
	}

	else if (Admin* a = dynamic_cast<Admin*>(&user))
	{
		ofstream userFile("Admins.txt", ios::app); 
		try {
			if (!userFile.is_open())
			{
				throw " Could not open file to save user data.\n";
			}
			else
			{
				userFile << "User Name: " << a->getusername()
					<< "\nEmail: " << a->getEmail()
					<< "\nDate Of Birth: " << a->getDOB()
					<< "\nPassword: " << a->getpassword()
					<< "\nRole: Admin" ;
				userFile << "\n-----------------------------" << endl;
				userFile.close();
				cout << "\nAdmin saved to file successfully.\n";
			}
		}
		catch (const char* msg) {
			cout << "\nError! " << msg << endl; 
		}
	}
}

User* FindUser(string name, string pass)
{
    ifstream file;
    string line, username, password;
    string DOB;
    string Email;
    string Role;
    string seller_status;
    string seller_id;
    // ----------------- Admin -----------------
    file.open("Admins.txt");
    try {
        if (!file.is_open())
            throw "Could not open Admins.txt file.\n";
        while (getline(file, line)) {
            if (line.find("User Name: ") == 0) {
                username = "";
                for (int i = 11; i < line.length(); i++)
                {
                    username += line[i];
                }
                    
            }
            else if (line.find("Email: ") == 0)
            {
                Email = "";
                for (int i = 7;i < line.length();i++)
                {
                    Email += line[i];
                }
            }
            else if (line.find("Date Of Birth: ") == 0)
            {
                DOB = "";
                for (int i = 15;i < line.length();i++)
                {
                    DOB += line[i];
                }
            }
            else if (line.find("Password: ") == 0) {
                password = "";
                for (int i = 10; i < line.length(); i++)
                    password += line[i];
            }

            else if (line.find("Role: ") == 0)
            {
                Role = "";
                for (int i = 6;i < line.length();i++)
                {
                    Role += line[i];
                }
            }
            if (username == name && password == pass && line.find("------")==0)
            { 
                  file.close();
                 User* user= new Admin(username, password, DOB, Email);
                  return user;
            }
        }
        file.close();
    }
    catch (const char* msg) {
        cout << "\nError! " << msg << endl;
    }

    // ----------------- Buyer -----------------
    file.open("Buyer.txt");
    try {
        if (!file.is_open())
            throw "Could not open Buyer.txt file.\n";
        username; password;
        while (getline(file, line)) 
        {
            if (line.find("User Name: ") == 0) 
            {
                username = "";
                for (int i = 11; i < line.length(); i++)
                {
                    username += line[i];
                }

            }
            else if (line.find("Email: ") == 0)
            {
                Email = "";
                for (int i = 7;i < line.length();i++)
                {
                    Email += line[i];
                }
            }
            else if (line.find("Date Of Birth: ") == 0)
            {
                DOB = "";
                for (int i = 15;i < line.length();i++)
                {
                    DOB += line[i];
                }
            }
            else if (line.find("Password: ") == 0) {
                password = "";
                for (int i = 10; i < line.length(); i++)
                    password += line[i];
            }

            else if (line.find("Role: ") == 0)
            {
                Role = "";
                for (int i = 6;i < line.length();i++)
                {
                    Role += line[i];
                }
            }
            if (username == name && password == pass && line.find("------") == 0)
            {
                file.close();
                User* user = new Buyer(username, password, DOB, Email);
                return user;
            }
        }
        file.close();
    }
    catch (const char* msg) {
        cout << "\nError! " << msg << endl;
    }

    // ----------------- Approved Seller -----------------
    file.open("Seller.txt");
    try {
        if (!file.is_open())
            throw "Could not open Seller.txt file.\n";
        while (getline(file, line)) {
            if (line.find("User Name: ") == 0)
            {
                username = "";
                for (int i = 11; i < line.length(); i++)
                {
                    username += line[i];
                }

            }
            else if (line.find("Email: ") == 0)
            {
                Email = "";
                for (int i = 7;i < line.length();i++)
                {
                    Email += line[i];
                }
            }
            else if (line.find("Date Of Birth: ") == 0)
            {
                DOB = "";
                for (int i = 15;i < line.length();i++)
                {
                    DOB += line[i];
                }
            }
            else if (line.find("Password: ") == 0) {
                password = "";
                for (int i = 10; i < line.length(); i++)
                    password += line[i];
            }

            else if (line.find("Role: ") == 0)
            {
                Role = "";
                for (int i = 6;i < line.length();i++)
                {
                    Role += line[i];
                }
            }
            
            else if (line.find("Seller ID: ") == 0)
            {
                seller_id = "";
                for (int i = 11;i < line.length();i++)
                {
                    seller_id += line[i];
                }
            }
            else if (line.find("Seller Status: ") == 0)
            {
                seller_status = line.substr(15);
            }
            if (username == name && password == pass && line.find("------") == 0)
            {
                int sell_id=0;
                for (int i = 0;i < seller_id.length();i++)
                {
                    sell_id = (seller_id[i] - '0')+(10*sell_id);
                }
                bool sell_status;
                if (seller_status == "Approved")
                    sell_status = true;
                else
                    sell_status = false;
                file.close();
                User* user = new Seller(username, password, DOB, Email, sell_id, sell_status);
                return user;
            }
        }
        file.close();
    }
    catch (const char* msg) {
        cout << "\nError! " << msg << endl;
    }

    // ----------------- Pending Seller -----------------
    /*file.open("PendingSeller.txt");
    try {
        if (!file.is_open())
            throw "Could not open PendingSeller.txt file.\n";
        username = ""; password = "";
        while (getline(file, line)) {
            if (line.find("User Name: ") == 0)
            {
                username = "";
                for (int i = 11; i < line.length(); i++)
                {
                    username += line[i];
                }

            }
            else if (line.find("Email: ") == 0)
            {
                Email = "";
                for (int i = 7;i < line.length();i++)
                {
                    Email += line[i];
                }
            }
            else if (line.find("Date Of Birth: ") == 0)
            {
                DOB = "";
                for (int i = 15;i < line.length();i++)
                {
                    DOB += line[i];
                }
            }
            else if (line.find("Password: ") == 0) {
                password = "";
                for (int i = 10; i < line.length(); i++)
                    password += line[i];
            }

            else if (line.find("Role: ") == 0)
            {
                Role = "";
                for (int i = 6;i < line.length();i++)
                {
                    Role += line[i];
                }
            }

            else if (line.find("Seller ID: ") == 0)
            {
                seller_id = "";
                for (int i = 11;i < line.length();i++)
                {
                    seller_id += line[i];
                }
            }
            else if (line.find("Seller Status: ") == 0)
            {
                seller_status = "";
                for (int i = 15;i < line.length();i++)
                {
                    seller_status += line[i];
                }
            }
            if (username == name && password == pass && line.find("------") == 0)
            {
                int sell_id = 0;
                for (int i = 0;i < seller_id.length();i++)
                {
                    sell_id = (seller_id[i] - '0') + (10 * sell_id);
                }
                bool sell_status;
                    sell_status = false;
                file.close();
                User* user = new Seller(username, password, DOB, Email, sell_id, sell_status);
                return user;
            }
        }
        file.close();
    }
    catch (const char* msg) {
        cout << "\nError! " << msg << endl;
    }*/
    User* user=new User;
    return user; 
}

void ApproveProductfromFile()
{
    ifstream product_file("Products.txt");
    string l1, l2, l3, l4, l5, l6, l7;
    try 
    {
        if (!product_file.is_open()) 
        {
            throw "Cannot open the file!";
        }

        while (getline(product_file, l7)) 
        {
            bool match = true;
            string check = "Status: Unapproved";

            if (l7.length() != check.length())
            {
                match = false;
            }
            else {
                for (int i = 0; i < check.length(); i++)
                {
                    if (l7[i] != check[i]) {
                        match = false;
                        break;
                    }
                }
            }
            if (match == true) 
            {
                cout << "\n--- Unapproved Product Found ---\n";
                cout << l1 << endl<< l2 << endl<< l3 << endl<< l4 << endl<< l5 << endl<< l6 << endl<< l7 << endl
                 << "-------------------------------\n";
            }
            l1 = l2, l2 = l3, l3 = l4;l4 = l5;  l5 = l6;
            l6 = l7;
        }
    }
    catch (const char* error) {
        cout << "Error: " << error << endl;
    }
}

void browseproductsfromfile() {
    try {
        ifstream file("Products.txt");
        if (!file) {
            throw "File can't be opened.";
        }

        vector<string> lines;
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                lines.push_back(line);
            }
        }
        file.close();

        cout << "\n------ Approved Products ------\n";
        cout << "ID      | Name               | Category       | Price        | Qty  | Seller | Info\n";
        cout << "--------|--------------------|----------------|--------------|------|--------|----------\n";

        for (int i = 6; i < (int)lines.size() - 2; i++) {
            if (lines[i] == "Status: Approved") {
                string pro_id = lines[i - 6].substr(12);
                string name = lines[i - 4].substr(14);
                string categ = lines[i - 3].substr(10);
                string price = lines[i - 2].substr(7);
                string quanti = lines[i - 1].substr(10);
                string seller_id = lines[i - 5].substr(11);
                string info = "N/A";
                string inf_line = lines[i + 1];
                if (categ == "Electronics" && inf_line.find("Product Warranty: ") == 0) {
                    info = inf_line.substr(18);
                }
                else if (categ == "Books" && inf_line.find("Author Name: ") == 0) {
                    info = inf_line.substr(13);
                }
                else if (categ == "Clothing" && inf_line.find("Size: ") == 0) {
                    info = inf_line.substr(6);
                }

                // Print row
                cout << left
                    << setw(8) << pro_id << "| "
                    << setw(20) << name << "| "
                    << setw(16) << categ << "| "
                    << setw(14) << price << "| "
                    << setw(6) << quanti << "| "
                    << setw(8) << seller_id << "| "
                    << info << "\n";
            }
        }

        cout << "----------------------------------------------------------------------------\n";
    }
    catch (const char* err) {
        cout << "Error: " << err << endl;
    }
}



void saveOrderToFile(const Order& order)
{
    ofstream outFile("Order.txt", ios::app);

    if (!outFile.is_open())
    {
        cout << "Error: Could not open Order.txt to save order.\n";
        return;
    }

    outFile << "Order ID: " << order.getOrderID() << "\n";
    outFile << "Buyer: " << order.getBuyerName() << "\n";
    outFile << "Date: " << order.getDate() << "\n";
    outFile << "Products:\n";

    vector<Product> products = order.getItems();
    float total = 0;

    for (Product& p : products)
    {
        int subtotal = p.getPrice() * p.getQuantity();
        total += subtotal;

        outFile << "- Product ID: " << p.getID()
            << ", Seller ID: " << p.getSellerID()
            << ", Name: " << p.getProductname()
            << ", Category: " << p.getcateg()
            << ", Price: " << p.getPrice()
            << ", Quantity: " << p.getQuantity() << "\n";
    }

    outFile << "Shipping Status: " << (order.getShippingStatus() ? "Delivered" : "Pending") << "\n";
    outFile << "Total Amount: " << total << " PKR\n";
    outFile << "--------------------------------------\n";

    outFile.close();
}


void vieworders(const string& buyerName)
{
    ifstream file("Order.txt");
    if (!file.is_open())
    {
        cout << "Error! Could not open Order.txt.\n";
        return;
    }

    string line;
    bool match_found = false;
    bool print_block = false;

    while (getline(file, line))
    {
        if (line.find("Buyer: ") == 0)
        {
            string extract_buyer = line.substr(7);
            if (extract_buyer == buyerName)
            {
                match_found = true;
                print_block = true;
                cout << "\n=================================\n";
            }
            else
            {
                print_block = false;
            }
        }

        if (print_block)
        {
            cout << line << endl;
        }

        if (line.find("--------------------------------------") == 0 && print_block)
        {
            cout << "=================================\n";
            print_block = false;
        }
    }

    if (!match_found)
    {
        cout << "No orders found for buyer: " << buyerName << endl;
    }

    file.close();
}


void displayPendingSellers() {
    try
    {
        ifstream file("Seller.txt");
        if (!file) 
        {
            throw "Error: Could not open Seller.txt";
        }

        vector<string> lines;
        string line;

        while (getline(file, line))
        {
            lines.push_back(line);
        }

        file.close();

        bool found = false;

        for (int i = 0; i < lines.size(); i++) {
            if (lines[i] == "Seller Status: Unapproved")
            {
                found = true;

                cout << "\n------------------------\n";

                cout << lines[i - 6] << endl;
				cout << lines[i - 5] << endl;
				cout << lines[i - 1] << endl;
                cout << lines[i] << endl;
            }
        }

        if (!found) {
            cout << "\nNo pending sellers found.\n";
        }

    }
    catch (const char* msg) {
        cout << "ERROR: " << msg << endl;
    }
}


void updateSellerStatusByID(int sellerID, const string& newstat) {
    try {
        ifstream sellerfile("Seller.txt");

        if (!sellerfile) 
        {
            throw "File could not be opened.";
        }

        string line;
        bool found = false;
        vector<string> taper;

        while (getline(sellerfile, line))
        {
            taper.push_back(line);
        }

        sellerfile.close();

        for (int i = 0; i < taper.size(); i++) 
        {
            if (taper[i] == "Seller ID: " + to_string(sellerID)) 
            {
                found = true;

                
                    taper[i + 1] = "Seller Status: " + newstat;
                    cout << "Seller status updated successfully.\n";

                break; 
            }
        }

        if (!found) {
            throw "Seller ID not found.";
        }

        ofstream filer("Seller.txt");
        if (!filer) {
            throw "File could not be opened for writing.";
        }

        for (int i = 0; i < taper.size(); i++) 
        {
            filer << taper[i] << endl;
        }

        filer.close();
    }
    catch (const char* error)
    {
        cout << "ERROR: " << error << endl;
    }
}
//void viewSellerProducts(int sellerID)
//{
//    ifstream file("Products.txt");
//
//    if (!file.is_open())
//    {
//        cout << "Error: Could not open Products.txt\n";
//        return;
//    }
//
//    bool found = false;
//    string line;
//
//    while (true)
//    {
//        string productID;
//        string sellerIDLine;
//        string name;
//        string category;
//        string price;
//        string quantity;
//        string status;
//        string warranty;
//        string separator;
//
//        if (!getline(file, productID) ||
//            !getline(file, sellerIDLine) ||
//            !getline(file, name) ||
//            !getline(file, category) ||
//            !getline(file, price) ||
//            !getline(file, quantity) ||
//            !getline(file, status) ||
//            !getline(file, warranty) ||
//            !getline(file, separator))
//        {
//            break;
//        }
//
//        if (sellerIDLine.find("Seller ID: ") == 0)
//        {
//            int fileSellerID = stoi(sellerIDLine.substr(11));
//
//            if (fileSellerID == sellerID)
//            {
//                cout << "Product ID     : " << productID.substr(12) << "\n";
//                cout << "Product Name   : " << name.substr(14) << "\n";
//                cout << "Category       : " << category.substr(10) << "\n";
//                cout << "Price          : " << price.substr(7) << "\n";
//                cout << "Quantity       : " << quantity.substr(10) << "\n";
//                cout << "Status         : " << status.substr(8) << "\n";
//                cout << "Product Warranty: " << warranty.substr(18) << "\n";
//                cout << "--------------------------------------------\n";
//                found = true;
//            }
//        }
//    }
//
//    if (!found)
//    {
//        cout << "No products found for Seller ID: " << sellerID << "\n";
//    }
//
//    file.close();
//}

void getSellerRevenueFromOrders(int sellerID, int& totalUnitsSold, int& totalRevenue)
{
    try
    {
        ifstream file("Order.txt");
        if (!file)
        {
            throw "Error: Could not open Order.txt";
        }

        vector<int> sellers;
        vector<int> prices;
        vector<int> quantities;
        string word;

        while (file >> word)
        {
            if (word == "-")
            {
                file >> word; // "Product"
                file >> word; // "ID:"
                file >> word; // product ID

                int tempSellerID = 0, tempPrice = 0, tempQuantity = 0;

                while (word != "Seller" && file >> word);
                file >> word; // "ID:"
                file >> tempSellerID;

                while (word != "Price:" && file >> word);
                file >> tempPrice;

                while (word != "Quantity:" && file >> word);
                file >> tempQuantity;

                sellers.push_back(tempSellerID);
                prices.push_back(tempPrice);
                quantities.push_back(tempQuantity);
            }
        }

        file.close();

        totalUnitsSold = 0;
        totalRevenue = 0;
        bool found = false;

        for (int i = 0; i < sellers.size(); i++) 
        {
            if (sellers[i] == sellerID) {
                totalUnitsSold += quantities[i];
                totalRevenue += prices[i] * quantities[i];
                found = true;
            }
        }

        if (!found) {
            cout << "\nNo orders found for seller ID: " << sellerID << endl;
        }
        else {

            cout << "\nSeller ID: " << sellerID << endl;
            cout << "Total Units Sold: " << totalUnitsSold << endl;
            cout << "Total Revenue: " << totalRevenue << endl;
        }

    }
    catch (const char* msg) {
        cout << "ERROR: " << msg << endl;
    }
}

//void getSellerRevenueFromOrders(int sellerID, int& totalUnitsSold, int& totalRevenue)
//{
//    ifstream file("Order.txt");
//    totalUnitsSold = 0;
//    totalRevenue = 0;
//
//    if (!file.is_open())
//    {
//        cout << "Error: Could not open Order.txt\n";
//        return;
//    }
//
//    string line;
//
//    while (getline(file, line))
//    {
//        if (line.find("- Product ID:") == 0)
//        {
//
//            size_t sellerPos = line.find("Seller ID:");
//            size_t pricePos = line.find("Price:");
//            size_t qtyPos = line.find("Quantity:");
//
//            if (sellerPos != string::npos && pricePos != string::npos && qtyPos != string::npos)
//            {
//                int fileSellerID = stoi(line.substr(sellerPos + 11, line.find(",", sellerPos) - (sellerPos + 11)));
//
//                if (fileSellerID == sellerID)
//                {
//                    int price = stoi(line.substr(pricePos + 7, line.find(",", pricePos) - (pricePos + 7)));
//                    int qty = stoi(line.substr(qtyPos + 9));
//
//                    totalUnitsSold += qty;
//                    totalRevenue += price * qty;
//                }
//            }
//        }
//    }
//
//    file.close();
//}

void CalculateTotalRevenue() 
{
    ifstream in("Order.txt");
    string line;
    int T_Revenue = 0;
    while (getline(in, line)) 
    {
        if (line.find("Total Amount: ") == 0) 
        {
            string amount = line.substr(14, line.find(" PKR") - 14);
            T_Revenue += stoi(amount);
        }
    }
    in.close();
    cout << "Total Revenue: " << T_Revenue << " PKR\n";
}

void DisplayMostActiveUsers() {
    ifstream in("Order.txt");
    string line;
    const int MAX = 100;
    string buyers[MAX];
    int orderCount[MAX] = { 0 };
    int index = 0;

    while (getline(in, line)) {
        if (line.find("Buyer: ") == 0) {
            string buyer = line.substr(7);
            bool found = false;
            for (int i = 0; i < index; i++) {
                if (buyers[i] == buyer) {
                    orderCount[i]++;
                    found = true;
                    break;
                }
            }
            if (!found && index < MAX) {
                buyers[index] = buyer;
                orderCount[index] = 1;
                index++;
            }
        }
    }
    in.close();

    cout << "\nBuyer\t\tOrders\n";
    for (int i = 0; i < index; i++) {
        cout << buyers[i] << "\t\t" << orderCount[i] << endl;
    }
}

void updateSeller() {
    try {
        string sellerID;
        cout << "Enter Seller ID to update: ";
        cin >> sellerID;

        ifstream sellerfile("Seller.txt");

        if (!sellerfile) {
            throw "File could not be opened.";
        }

        string line;
        bool found = false;
        bool sellerMatched = false;

        string newName, newPassword;
        vector<string> taper;
        while (getline(sellerfile, line)) {
            taper.push_back(line);
        }
        sellerfile.close();
			for (int i = 0;i < taper.size();i++)
			{
                if (taper[i] == ("Seller ID: " + sellerID)) {
                    found = true;
					cout << "Enter new Name: ";
					cin.ignore();  // flush newline
					getline(cin, newName);
					taper[i - 5] = "User Name: " + newName; // Update Name line
					cout << "Enter new Password: ";
					getline(cin, newPassword);
					taper[i -2] = "Password: " + newPassword; // Update Password line
                    cout << "Seller updated successfully.\n";
                }
			}
			if (!found) 
            {
				throw "Seller ID not found.";
			}
            ofstream filer;
			filer.open("Seller.txt");
			if (!filer) {
				throw "File could not be opened for writing.";
			}
            for (int i = 0; i < taper.size(); i++)
			{
				filer << taper[i] << endl;
			}
			filer.close();
    }
    catch (const char* error) {
        cout << "ERROR: " << error << endl;
    }
}


void removeSeller() {
    try {
        string sellerID;
        cout << "Enter Seller ID to remove: ";
        cin >> sellerID;

        ifstream in("Seller.txt");
        if (!in) {
            throw "File could not be opened.";
        }

        vector<string> lines, tempLines;
        string line;
        while (getline(in, line)) {
            lines.push_back(line);
        }
        in.close();

        bool found = false;

        for (int i = 0; i < lines.size(); i++)
        {
            if (lines[i] == "Seller ID: " + sellerID)
            {
                found = true;
                for (int j = 0; j < i - 5; j++)
                {
                    tempLines.push_back(lines[j]);
                }


                for (int j = i + 3; j < lines.size(); j++)
                {
                    tempLines.push_back(lines[j]);
                }

                cout << "Seller removed successfully.\n";
                break;
            }
        }

        if (!found)
        {
            throw "Seller ID not found.";
        }

        ofstream out("Seller.txt");
        if (!out) {
            throw "Error opening file for writing.";
        }

        for (int i = 0;i < tempLines.size();i++) 
        {
            out << tempLines[i] << endl;
        }

        out.close();
    }
    catch (const char* msg) {
        cout << "ERROR: " << msg << endl;
    }
}


void removeBuyer() {
    try {
        string inputUsername, inputEmail;
        cout << "Enter Buyer User Name to remove: ";
        cin >> inputUsername;
        cout << "Enter Buyer Email to remove: ";
        cin >> inputEmail;

        ifstream in("Buyer.txt");
        if (!in) {
            throw "Error opening Buyer.txt.";
        }

        vector<string> lines;
        string line;

        while (getline(in, line)) 
        {
            lines.push_back(line);
        }
        in.close();

        vector<string> tempLines;
        bool found = false;

        for (int i = 0; i < lines.size(); i++) 
        {
            if (lines[i] == "User Name: " + inputUsername &&
                i + 1 < lines.size() &&
                lines[i + 1] == "Email: " + inputEmail)
            {

                found = true;
                int start = i;
                int end = i + 5;

                for (int j = 0; j < start; j++) 
                {
                    tempLines.push_back(lines[j]);
                }

                for (int j = end + 1; j < lines.size(); j++) 
                {
                    tempLines.push_back(lines[j]);
                }

                cout << "Buyer removed successfully.\n";
                break;
            }
        }

        if (!found)
        {
            throw "Buyer with given name and email not found.";
        }

        ofstream out("Buyer.txt");
        if (!out) {
            throw "Error writing to Buyer.txt.";
        }

        for (int i=0;i< tempLines.size();i++)
        {
            out << tempLines[i] << endl;
        }

        out.close();
    }
    catch (const char* msg) {
        cout << "ERROR: " << msg << endl;
    }
}


void deleteProductByAdmin() {
    int productID;
    cout << "Enter Product ID to delete: ";
    cin >> productID;

    ifstream in("Products.txt");
    ofstream temp("temp.txt");

    if (!in || !temp) {
        cout << "Error opening Products.txt\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(in, line)) {
        if (line == "Product ID: " + to_string(productID)) {
            found = true;
            for (int i = 0; i < 8; ++i)
                getline(in, line);
            continue;
        }
        temp << line << endl;
    }

    in.close();
    temp.close();

    if (found) {
        remove("Products.txt");
        rename("temp.txt", "Products.txt");
        cout << "Product deleted successfully.\n";
    }
    else {
        remove("temp.txt");
        cout << "Product not found.\n";
    }
}

void ShowAllSellersFromFile() {
    ifstream file("Seller.txt");
    if (!file) {
        cout << "Error opening Seller.txt\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void ShowAllBuyersFromFile() {
    ifstream file("Buyer.txt");
    if (!file) {
        cout << "Error opening Buyer.txt\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void ShowProductsBySellerID(int sellerID)
{
    try 
    {
        ifstream file("Products.txt");
        if (!file) 
        {
            throw "Error opening Products.txt.";
        }

        vector<string> lines;
        string line;

        while (getline(file, line))
        {
            lines.push_back(line);
        }

        file.close();

        bool found = false;

        for (int i = 0; i < lines.size(); i++) 
        {
            if (lines[i] == "Seller ID: " + to_string(sellerID)) 
            {
                found = true;
                cout << "--------------------------------\n";
				cout << lines[i - 1] << endl; // Product ID
				cout << lines[i] << endl; // Seller ID
				cout << lines[i + 1] << endl; // Product Name
				cout << lines[i + 2] << endl; // Category
				cout << lines[i + 3] << endl; // Price
				cout << lines[i + 4] << endl; // Quantity
                cout << lines[i + 5] << endl;
                cout << lines[i + 6] << endl;
				cout << "--------------------------------\n";
            }
        }

        if (!found) {
            throw "No products found for the given Seller ID.";
        }

    }
    catch (const char* msg) {
        cout << "\n[ERROR] " << msg << endl;
    }
}
