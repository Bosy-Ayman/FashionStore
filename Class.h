#pragma once
#include<iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <chrono>
#include <regex>

const int MAX_PRODUCTS = 100;
const int SCmaxrow = 100;
const int WLmaxrow = 30;


//class User:public Person {
//private:
//    string Name;
//    string Email;
//    double Age;
//    string Address;
//    string Gender;
//
//public:
//    User():Age(0) {}
//
//    User(const std::string& N, const std::string& em, double ag, const std::string& address, const std::string& gen)
//        : Name(N), Email(em), Age(ag), Address(address), Gender(gen) {}
//
//    // Function to enter user data
//    void enter_data();
//
//    // Function to display user information
//    void show_info() const;
//};


class Wishlist {
private:
    string wishlist_product_name[WLmaxrow];

    bool IsProductValid(const string& productName, const string validProducts[], int validProductsCount);

    void ReadValidProductsFromFile(const std::string& filename, std::string validProducts[], int& validProductsCount);

public:
    void AddProducttoWL();

    void showWLproducts();
};


class Review {
private:
    string storeName = "Fashion store";
    string review;
public:
    //Ask the user to enter his review
    void showReview();
};


class ShoppingCart {
private:
    string purchased_product_name[SCmaxrow];
    string purchased_product_quantity[SCmaxrow];
    string purchased_product_price[SCmaxrow];

public:
    void AddProducttoSC();
    void ReadValidProductsFromFile(const string& filename, string validProducts[], string validPrices[], int& validProductsCount);
    bool IsProductValid(const string& productName, const string validProducts[], const string validPrices[], int validProductsCount, string& price);
    string TrimString(const string& str);
    void showSCproducts();

    friend class Receipt;
};


class Receipt {
protected:
    double totalPrice;

public:
    void GenerateReceipt(const ShoppingCart& cart);
    double gettotalPrice()const;
    void settotalPrice(double price);
    Receipt(double totalPrice);
    Receipt();
    friend class Promotion;

};


//class promotion
//{
//private:
//    string discount_code;
//    char answ;
//    double new_totalprice;
//public:
//    void discount();
//
//};

class Promotion {
private:
    std::string discount_code;
    char answ;
    double new_totalprice;
    

public:
    void discount(Receipt receipt) {
        cout << "Enter discount code: ";
        cin >> discount_code;


        cout << "Do you want to apply the discount? (y/n): ";
        cin >> answ;

        if (answ == 'y' || answ == 'Y') {
            double discount_percentage = 0.25; 
            double discount_amount = receipt.totalPrice * discount_percentage;
            new_totalprice = receipt.totalPrice - discount_amount;

            cout << "Discount applied! New total price: " << new_totalprice << endl;
            receipt.totalPrice = new_totalprice;
        }
        else {
            cout << "Discount not applied. Total price remains the same." << endl;
        }
    }
};
class Payment {
private:
    int pay = 0;
    string email, password;
    string ccNumber, pin;

public:
    void processPayment();

};


//class Person {
//protected:
//    string name;
//    int age;
//
//public:
//    Person(){}
//    Person(const std::string& name, int age) : name(name), age(age) {}
//
//   /* void displayPerson() {
//        cout << "Name: " << name << endl;
//        cout << "Age: " << age << endl;
//    }*/
//};
//

class Employees
{
private:
    const static int maxrow = 100; 
    string employee_name[maxrow];
    string employee_position[maxrow];
    string employee_salary[maxrow];
    string employee_department[maxrow];
    string email;
    string password;

public:
    void AddEmployee();
    void DeleteEmployee(string search);
    void ListEmployees();
    void loginAsAdministrator() {
      

        do {
            cout << "Enter email: ";
            cin >> email;

            cout << "Enter password: ";
            cin >> password;

            if (email == "administrator@gmail.com" && password == "2023") {
                cout << "Login successful. You are now logged in as an administrator." << endl;
                break; // Exit the loop if login is successful
            }
            else {
                cout << "Invalid email or password. Login failed." << endl;
                cout << "Please try again." << endl;
            }
        } while (true);
    }
};


class Clock {
public:
    void displayCurrentTime();
};


class shippingTracker
{
private:
    Clock deliveryDate;

public:
    void displayShippingDetails();
};


class giftcard {
private:
    double giftcard_amount;

public:
    giftcard(double amount) {
        giftcard_amount = amount;
    }

    double applyDiscount(const Receipt& receipt) const {
        double totalPrice = receipt.gettotalPrice();
        double discountedPrice = totalPrice - giftcard_amount;
        return discountedPrice;
    }
};



class Person {
protected:
    string name;
    int age = 0;

public:
    Person() {}
    Person(const std::string& name, int age) : name(name), age(age) {}
};

class User : public Person {
private:
    string Name;
    string Email;
    double Age;
    string Address;
    std::string Gender;

public:
    User() : Age(0) {}
    User(const std::string& N, const string& em, double ag, const string& address, const string& gen)
        : Name(N), Email(em), Age(ag), Address(address), Gender(gen) {}

    void enter_data();
    void show_info() const;
};
