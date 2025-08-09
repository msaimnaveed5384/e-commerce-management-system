E-COMMERCE MANAGEMENT SYSTEM

A console-based C++ application that simulates a complete e-commerce platform with Admin, Seller, and Buyer roles. The system supports user management, product management, order processing, and reporting, with file-based data storage for persistence.

FEATURES:

1) AUTHENTICATION AND USER MANAGEMENT

Registration with validation for email, date of birth, password, and role selection.

Login with role-based access control.

Roles include:

Admin – Full platform control.

Seller – Manage products and track revenue.

Buyer – Browse, search, add to cart, and checkout.

2) ADMIN FEATURES

Approve or reject products before they are visible to buyers.

Manage buyers and sellers: approve sellers, update seller info, remove accounts.

View reports:

Total platform revenue.

Most active buyers by order count.

Delete products directly.

View all registered buyers/sellers and their products.

3) SELLER FEATURES

Add Products in three categories:

Electronics (with warranty)

Books (with author name)

Clothing (with size)

Update Products – name, category, price, quantity, and category-specific details.

Delete Products.

View only their listed products.

Track revenue per product based on orders.

4) BUYER FEATURES

Browse Products – View all approved products.

Search Products by name.

Shopping Cart:

Add items (quantity fixed to 1 per add).

Remove items.

View cart contents.

Checkout:

Generates an order with unique ID.

Updates product quantities in inventory.

View their order history.

5) ORDER MANAGEMENT

Orders are saved to Order.txt with details:

Order ID, buyer name, date.

Products purchased (ID, seller ID, name, category, price, quantity).

Shipping status (default: Pending).

Total order amount.

6) FILE BASED DATA PERSISTANCE
Data is stored and retrieved using text files:

Admins.txt – Admin accounts.

Seller.txt – Seller accounts.

Buyer.txt – Buyer accounts.

Products.txt – All products (with category-specific info).

Order.txt – Order records.

Project Structure
bash
Copy
Edit
├── main.cpp              # Application entry point
├── AuthSystem.h/.cpp     # Registration & Login logic
├── FileManager.h/.cpp    # File operations for products, users, and orders
├── User.h/.cpp           # User, Admin, Seller, Buyer classes
├── Product.h/.cpp        # Base and derived product classes
├── Cart.h/.cpp           # Shopping cart template
├── Order.h/.cpp          # Order management
├── *.txt                 # Data storage files

TECHNICAL HIGHLIGHTS
Object-Oriented Programming: Classes, inheritance, polymorphism.

Operator Overloading:

Cart::operator+= to add products to cart.

Cart::operator-= to remove products from cart.

File I/O: Persistent storage using standard C++ file streams.

Exception Handling: Input validation and error handling.

Dynamic Casting: Identify product category at runtime.

HOW TO RUN
Compile all .cpp files together in your C++ compiler (e.g., g++, Visual Studio, Code::Blocks).

Run the executable.

Use the main menu to Login, Register, or view Info.

Follow role-specific menus to interact with the system.

FUTURE IMPROVEMENTS
Add shipping status updates for orders.

Allow quantity selection for cart items.

Implement discounts and promotions.

Introduce a GUI interface for better user experience.
