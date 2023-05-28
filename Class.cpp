#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include"Class.h"
//const int SCmaxrow = 100;
//const int MAX_PRODUCTS = 100;

using namespace std;

void ShoppingCart::AddProducttoSC() {
    string purchasedProductName, purchasedProductQuantity;

    cin.ignore();

    cout << "Enter the product's name you want to add to your shopping cart (or 'done' to finish): ";
    getline(cin, purchasedProductName);

    // Check if the user wants to finish adding products
    if (purchasedProductName == "done" || purchasedProductQuantity == "done") {
        return;
    }
    cout << "Enter the product's quantity you want to add to your shopping cart: ";
    getline(cin, purchasedProductQuantity);

    // Convert the product name to lowercase for case-insensitive comparison
    transform(purchasedProductName.begin(), purchasedProductName.end(), purchasedProductName.begin(), [](unsigned char c) {
        return tolower(c);
        });

    // Validate the product
    string validProducts[MAX_PRODUCTS];
    string validPrices[MAX_PRODUCTS];
    int validProductsCount = 0;

    ReadValidProductsFromFile("Text.txt", validProducts, validPrices, validProductsCount);

    string productPrice;
    if (!IsProductValid(purchasedProductName, validProducts, validPrices, validProductsCount, productPrice)) {
        cout << "Invalid product. Please enter a valid product." << endl;
        AddProducttoSC(); // Recursively ask for a valid product
        return;
    }

    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (purchased_product_name[i].empty()) {
            purchased_product_name[i] = purchasedProductName;
            purchased_product_price[i] = productPrice;
            purchased_product_quantity[i] = purchasedProductQuantity;
            break;
        }
    }

    // Open the file for writing and append the new product information
    ofstream file("shoppingcart.txt", ios::app);
    if (file.is_open()) {
        file << purchasedProductName << ", " << purchasedProductQuantity << "\n";
        file.close();
        cout << "Product added to shopping cart successfully!" << endl;
    }
    else {
        cout << "Error opening file for writing!" << endl;
    }

    // Recursive call to add more products
    AddProducttoSC();
}

void ShoppingCart::ReadValidProductsFromFile(const string& filename, string validProducts[], string validPrices[], int& validProductsCount) {
    ifstream file(filename);
    validProductsCount = 0;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string productName, productPrice;

            if (getline(ss, productName, ',') && getline(ss, productPrice, ',')) {
                // Remove leading and trailing spaces from the product name and price
                productName = TrimString(productName);
                productPrice = TrimString(productPrice);

                validProducts[validProductsCount] = productName;
                validPrices[validProductsCount] = productPrice;
                validProductsCount++;
            }
        }

        file.close();
    }
    else {
        cout << "Error opening file: " << filename << endl;
    }
}

bool ShoppingCart::IsProductValid(const string& productName, const string validProducts[], const string validPrices[], int validProductsCount, string& price) {
    // Convert the input product name to lowercase for case-insensitive comparison
    string lowercaseProductName = productName;
    transform(lowercaseProductName.begin(), lowercaseProductName.end(), lowercaseProductName.begin(), [](unsigned char c) {
        return tolower(c);
        });

    for (int i = 0; i < validProductsCount; i++) {
        string lowercaseValidProduct = validProducts[i];
        transform(lowercaseValidProduct.begin(), lowercaseValidProduct.end(), lowercaseValidProduct.begin(), [](unsigned char c) {
            return tolower(c);
            });

        if (lowercaseProductName == lowercaseValidProduct) {
            price = validPrices[i];
            return true; // Valid product found
        }
    }

    return false; // Product not found
}

string ShoppingCart::TrimString(const string& str) {
    string trimmed = str;
    size_t first = trimmed.find_first_not_of(" \t");
    size_t last = trimmed.find_last_not_of(" \t");

    if (first != string::npos && last != string::npos) {
        trimmed = trimmed.substr(first, (last - first + 1));
    }
    else {
        trimmed.clear();
    }

    return trimmed;
}

void ShoppingCart::showSCproducts() {
    cout << "Shopping cart products:" << endl;

    int counter = 0;
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (!purchased_product_name[i].empty()) {
            counter++;
            cout << "Product " << counter << ":" << endl;
            cout << "Name: " << purchased_product_name[i] << endl;
            cout << "Price: " << purchased_product_price[i] << endl;
            cout << "Quantity: " << purchased_product_quantity[i] << endl;
            cout << endl;
        }
    }

    if (counter == 0) {
        cout << "No products found in the shopping cart." << endl;
    }
}

//---------------------------------------------------------------------------------------

void Receipt::GenerateReceipt(const ShoppingCart& cart) {
    cout << "------ Receipt ------" << endl;

    double totalPrice = 0.0;
    // total_orders = 0.0;
    // total_sales = 0.0;
    int counter = 0;
    for (int i = 0; i < SCmaxrow; i++) {
        if (!cart.purchased_product_name[i].empty()) {
            counter++;
            // Calculate the total price for the product
            double productPrice = stod(cart.purchased_product_price[i]);
            int productQuantity = stoi(cart.purchased_product_quantity[i]);
            double productTotalPrice = productPrice * productQuantity;
            totalPrice += productTotalPrice;

            cout << "Product " << counter << ":" << endl;
            cout << "Name: " << cart.purchased_product_name[i] << endl;
            cout << "Price: " << productPrice << endl;
            cout << "Quantity: " << productQuantity << endl;
            cout << "Total Price: " << productTotalPrice << endl;
            cout << endl;
        }
    }

    //total_orders = total_orders + 1;
   // total_sales = total_sales + totalPrice;
    cout << "---------------------" << endl;
    cout << "Total Price: " << totalPrice << endl;
}

Receipt::Receipt(double totalPrice)
{
    this->totalPrice = totalPrice;
}

Receipt::Receipt()
{
        totalPrice = 0.0;

}

double Receipt::gettotalPrice()const
{
    return totalPrice;
}

void Receipt::settotalPrice(double totalPrice) {
    this->totalPrice = totalPrice;
}

//-----------------------------------------------------------------------------------------

void Clock::displayCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &time);
    std::cout << buffer;
}

//-----------------------------------------------------------------------------------------

void shippingTracker::displayShippingDetails()
{
    std::cout << "Payment processed at: ";
    deliveryDate.displayCurrentTime();
    std::cout << "Your order will be delivered within a week." << std::endl;
}

//-----------------------------------------------------------------------------------------

void User::enter_data()
{
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, Name);

    // Email validation loop
    bool validEmail = false;
    while (!validEmail) {
        cout << "Enter your email: ";
        cin >> Email;

        // Email validation using regular expression
        std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        if (regex_match(Email, emailRegex)) {
            validEmail = true;
        }
        else {
            std::cout << "Invalid email format. Please enter a valid email." << std::endl;
        }
    }

    cout << "Enter your age: ";
    cin >> Age;

    cin.ignore();
    cout << "Enter your address: ";
    getline(std::cin, Address);

    cout << "Enter your gender: ";
    cin >> Gender;
}

void User::show_info() const
{
    cout << "Name: " << Name << endl;
    //cout << "Email: " << Email << endl;
    //cout << "Age: " << Age << endl;
    cout << "Address: " << Address << endl;
    //cout << "Gender: " << Gender << endl;
}

//-----------------------------------------------------------------------------------------

void Payment::processPayment()
{
    cout << "Enter the payment type:\n";
    cout << "1) Paypal\n";
    cout << "2) Credit Card\n";
    cout << "3) Apple Pay\n";
    cin >> pay;
    switch (pay) {
    case 1:
        cout << "Enter your email for Paypal payment: ";
        cin >> email;
        cout << "Enter your password for Paypal payment: ";
        cin >> password;
        cout << "Processing Paypal payment with email " << email << " and password " << password << endl;
        break;
    case 2:
        cout << "Enter your credit card number for payment: ";
        cin >> ccNumber;
        cout << "Enter your pin for payment: ";
        cin >> pin;
        cout << "Processing credit card payment with credit card number " << ccNumber << " and pin " << pin << endl;
        break;
    case 3:
        cout << "Processing Apple Pay payment" << endl;
        break;
    default:
        cout << "Invalid payment type." << endl;
        break;
    }
}

//-----------------------------------------------------------------------------------------

bool Wishlist::IsProductValid(const string& productName, const string validProducts[], int validProductsCount)
{
    // Convert the input product name to lowercase for case-insensitive comparison
    string lowercaseProductName = productName;
    transform(lowercaseProductName.begin(), lowercaseProductName.end(), lowercaseProductName.begin(), [](unsigned char c) {
        return std::tolower(c);
        });

    for (int i = 0; i < validProductsCount; i++)
    {
        string lowercaseValidProduct = validProducts[i];
        transform(lowercaseValidProduct.begin(), lowercaseValidProduct.end(), lowercaseValidProduct.begin(), [](unsigned char c) {
            return std::tolower(c);
            });

        if (lowercaseProductName == lowercaseValidProduct) {
            return true; // Valid product found
        }
    }

    return false; // Product not found
}

void Wishlist::ReadValidProductsFromFile(const std::string& filename, std::string validProducts[], int& validProductsCount)
{
    std::ifstream file(filename);
    validProductsCount = 0;

    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::size_t commaPos1 = line.find(',');

            if (commaPos1 != std::string::npos)
            {
                std::string productName = line.substr(0, commaPos1);

                // Remove leading and trailing spaces from the product name
                productName = productName.substr(productName.find_first_not_of(" \t"));
                productName = productName.substr(0, productName.find_last_not_of(" \t") + 1);

                validProducts[validProductsCount] = productName;
                validProductsCount++;

                if (validProductsCount >= MAX_PRODUCTS) {
                    break; // Reached the maximum number of products to read
                }
            }
        }
        file.close();
    }
    else
    {
        std::cout << "Error opening file: " << filename << std::endl;
    }
}

void Wishlist::AddProducttoWL()
{
    string wishlistProductName;

    cin.ignore();

    cout << "Enter the product's name you want to add to your wishlist (or 'done' to finish): ";
    getline(std::cin, wishlistProductName);

    // Check if the user wants to finish adding products
    if (wishlistProductName == "done") {
        return;
    }

    // Convert the product name to lowercase for case-insensitive comparison
    transform(wishlistProductName.begin(), wishlistProductName.end(), wishlistProductName.begin(), [](unsigned char c) {
        return std::tolower(c);
        });

    // Validate the product
    string validProducts[MAX_PRODUCTS];
    int validProductsCount = 0;
    ReadValidProductsFromFile("Text.txt", validProducts, validProductsCount);

    if (!IsProductValid(wishlistProductName, validProducts, validProductsCount)) {
        cout << "Invalid product. Please enter a valid product." << std::endl;
        AddProducttoWL(); // Recursively ask for a valid product
        return;
    }

    for (int i = 0; i < WLmaxrow; i++)
    {
        if (wishlist_product_name[i].empty())
        {
            wishlist_product_name[i] = wishlistProductName;
            break;
        }
    }

    // Open the file for writing and append the new product information
    ofstream file("wishlist.txt", ios::app);
    if (file.is_open())
    {
        file << wishlistProductName << "\n";
        file.close();
        cout << "Product added to wishlist successfully!" << std::endl;
    }
    else
    {
        cout << "Error opening file for writing!" << std::endl;
    }

    // Recursive call to add more products
    AddProducttoWL();
}

void Wishlist::showWLproducts()
{

    system("CLS");
    cout << "             Wishlist Products           " << endl;
    cout << "===========================================" << endl;

    int counter = 0;
    std::cout << "No.\t|\tProduct Name" << std::endl
        << "---------------------------------------------" << endl;
    for (int x = 0; x < WLmaxrow; x++)
    {
        if (!wishlist_product_name[x].empty())
        {
            counter++;
            std::cout << " " << counter << "\t" << wishlist_product_name[x] << endl;
        }
    }

    if (counter == 0)
    {
        cout << "\t\tNo products found in the wishlist" << endl;
    }

    cout << "========================================" << endl;
}

//------------------------------------------------------------------------------------------

void Review::showReview()
{
   // cout << "Welcome to " << storeName << " Review Class!" << endl;
    cout << "Please rate our online store from 1 to 5. (1 = poor, 2 = fair, 3 = good, 4 = very good, 5 = excellent)" << endl;
    int rating;
    cin >> rating;
    if (rating <= 2) {
        cout << "We're sorry to hear that you didn't enjoy your experience. Could you please provide some feedback on what we could improve?" << endl;
        string feedback;
        getline(cin, feedback);
        cout << "Thank you for the feedback! We'll do our best to address your concerns." << endl;
    }

    else {
        cout << "We're glad to hear that you had a good experience! We'd love to hear more about what you enjoyed about our online store. Could you please provide some feedback?" << endl;
        string feedback;
        getline(cin, feedback);
        cout << "Thank you for the feedback! We appreciate your business and hope to see you again soon at " << storeName << "." << endl;
    }
    cout << "\n What is your review : ";
    cin >> review;

}

//------------------------------------------------------------------------------------------


void Employees::AddEmployee()
{
    std::cin.ignore();

    std::string employeename;
    std::string employeeposition;
    std::string employeesalary;
    std::string employeedepartment;

    std::cout << "Enter the employee's name: ";
    std::getline(std::cin, employeename);

    std::cout << "Enter employee's position: ";
    std::getline(std::cin, employeeposition);

    std::cout << "Enter employee's salary: ";
    std::getline(std::cin, employeesalary);

    std::cout << "Enter employee's department: ";
    std::getline(std::cin, employeedepartment);

    for (int i = 0; i < maxrow; i++)
    {
        if (employee_name[i].empty())
        {
            employee_name[i] = employeename;
            employee_position[i] = employeeposition;
            employee_salary[i] = employeesalary;
            employee_department[i] = employeedepartment;
            break;
        }
    }

    std::ofstream file("Employees.txt", std::ios::app);
    if (file.is_open())
    {
        file << employeename << "," << employeeposition << "," << employeesalary << "," << employeedepartment << "\n";
        file.close();
        std::cout << "Employee added successfully!" << std::endl;
    }
    else
    {
        std::cout << "Error opening file for writing!" << std::endl;
    }
}

void Employees::DeleteEmployee(std::string search)
{
    std::ifstream inFile("Employees.txt");
    if (!inFile)
    {
        std::cerr << "Error: Unable to open file for reading." << std::endl;
        return;
    }

    int i = 0;
    std::string line;
    while (std::getline(inFile, line) && i < maxrow)
    {
        std::stringstream input(line);
        std::getline(input, employee_name[i], ',');
        std::getline(input, employee_position[i], ',');
        std::getline(input, employee_salary[i], ',');
        std::getline(input, employee_department[i], ',');
        i++;
    }

    inFile.close();

    int index = -1;
    for (int i = 0; i < maxrow; i++)
    {
        if (employee_name[i] == search)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        std::cout << "Employee not found" << std::endl;
        return;
    }

    employee_name[index] = "";
    employee_position[index] = "";
    employee_salary[index] = "";
    employee_department[index] = "";

    std::ofstream outFile("Employees.txt");
    if (!outFile)
    {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    for (int i = 0; i < maxrow; i++)
    {
        if (employee_name[i] != "")
        {
            outFile << employee_name[i] << "," << employee_position[i] << "," << employee_salary[i] << "," << employee_department[i] << std::endl;
        }
    }

    outFile.close();

    std::cout << "Employee deleted successfully!" << std::endl;
}


void Employees::ListEmployees()
{
    std::ifstream file("Employees.txt");

    if (file.is_open())
    {
        std::string line;
        int i = 0;
        while (std::getline(file, line) && i < maxrow)
        {
            std::stringstream input(line);
            std::getline(input, employee_name[i], ',');
            std::getline(input, employee_position[i], ',');
            std::getline(input, employee_salary[i], ',');
            std::getline(input, employee_department[i]);

            i++;
        }

        file.close();

        for (int i = 0; i < maxrow; i++)
        {
            if (!employee_name[i].empty())
            {
                std::cout << "Name: " << employee_name[i] << std::endl;
                std::cout << "Position: " << employee_position[i] << std::endl;
                std::cout << "Salary: " << employee_salary[i] << std::endl;
                std::cout << "Department: " << employee_department[i] << std::endl;
                std::cout << std::endl;
            }
        }
    }
    else
    {
        std::cout << "Error opening file for reading!" << std::endl;
    }
}
