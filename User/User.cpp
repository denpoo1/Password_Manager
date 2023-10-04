#include "User.h"
#include <iostream>
#include <string>
#include <regex>

using namespace std;

string User::checkNumber() {
    int iteracja = 0;
    while (true) {
        string phoneNumber;

        if (iteracja == 1) {
            cout << "Enter your phone number (e.g., +48 514 615 968): ";
        }
        getline(cin, phoneNumber);
        regex pattern("^\\+48\\s\\d{3}\\s\\d{3}\\s\\d{3}$");

        if (iteracja == 0) {
            iteracja = 1;
        } else if (regex_match(phoneNumber, pattern)) {
            return phoneNumber;
        } else {
            cout << "Invalid phone number format. Please try again." << endl;
        }
    }
}


    string User::checkMail() {
        string mail;

        cout << "Enter your email address (e.g., example@example.com): ";
        cin >> mail;

        regex pattern("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");

        if (regex_match(mail, pattern)) {
            return mail;
        } else {
            cout << "Invalid email address format. Please try again." << endl;
            return checkMail();
        }
    }

    string User::checkName() {
        string name;

        cout << "Enter your first name: ";
        cin >> name;

        // Your name validation logic
        // ...

        // Example validation: Name should consist of only letters
        regex pattern("^[a-zA-Z]+$");

        if (regex_match(name, pattern)) {
            return name;
        } else {
            cout << "Invalid name format. Please try again." << endl;
        }
        //Recursive
        return checkName();
    }

    string User::checkLastName() {
        string lastName;

        cout << "Enter your last name: ";
        cin >> lastName;

        // Your last name validation logic
        // ...

        // Example validation: Last name should consist of only letters
        regex pattern("^[a-zA-Z]+$");

        if (regex_match(lastName, pattern)) {
            return lastName;
        } else {
            cout << "Invalid last name format. Please try again." << endl;
        }
        //Recursive
        return checkLastName();
    }

    string User::createUser() {
        string username;
        cout << "Enter your username: ";
        cin >> username;
        return username;
    }

    string User::getUserName() {
        return username;
    }

    string User::toString() {
        return "Username: " + username +
               "\nFirst Name: " + firstName +
               "\nLast Name: " + lastName +
               "\nMail: " + mail +
               "\nPhone Number: " + phoneNumber +
               "\nPassword: " + passwordFromPersonalAccount;
    }
