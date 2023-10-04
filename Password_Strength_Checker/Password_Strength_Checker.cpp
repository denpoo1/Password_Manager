#include "Password_Strength_Checker.h"
#include <iostream>

Password_Strength_Checker::Password_Strength_Checker() {}

// Function to check the strength of a password
int Password_Strength_Checker::checkStrength(const std::string &password) {
    bool bool_hasLowerCase;
    bool bool_hasUpperCase;
    bool bool_hasDigit;
    bool bool_hasSpecialChar;
    bool bool_isLongEnough;
    std::string errorLines = "";

    int strength = 0;

    // Check if the password has lowercase letters and increment the strength level if true
    if (hasLowerCase(password)) {
        strength += 1;
        bool_hasLowerCase = true;
    }
    // Check if the password has uppercase letters and increment the strength level if true
    if (hasUpperCase(password)) {
        strength += 1;
        bool_hasUpperCase = true;
    }
    // Check if the password has digits and increment the strength level if true
    if (hasDigit(password)) {
        strength += 1;
        bool_hasDigit = true;
    }
    // Check if the password has special characters and increment the strength level if true
    if (hasSpecialChar(password)) {
        strength += 1;
        bool_hasSpecialChar = true;
    }
    // Check if the password is long enough and increment the strength level if true
    if (isLongEnough(password)) {
        strength += 1;
        bool_isLongEnough = true;
    }

    // Print the password rating and error messages
    std::cout << namePasswordRatings(strength) + writeErrors(bool_hasLowerCase,
                                                             bool_hasUpperCase,
                                                             bool_hasDigit,
                                                             bool_hasSpecialChar,
                                                             bool_isLongEnough);

    return strength;
}

// Function to check if the password contains lowercase letters
bool Password_Strength_Checker::hasLowerCase(const std::string &password) {
    for (char ch: password) {
        if (islower(ch)) {
            return true;
        }
    }
    return false;
}

// Function to check if the password contains uppercase letters
bool Password_Strength_Checker::hasUpperCase(const std::string &password) {
    for (char ch: password) {
        if (isupper(ch)) {
            return true;
        }
    }
    return false;
}

// Function to check if the password contains digits
bool Password_Strength_Checker::hasDigit(const std::string &password) {
    for (char ch: password) {
        if (isdigit(ch)) {
            return true;
        }
    }
    return false;
}

// Function to check if the password contains special characters
bool Password_Strength_Checker::hasSpecialChar(const std::string &password) {
    for (char ch: password) {
        if (!isalnum(ch)) {
            return true;
        }
    }
    return false;
}

// Function to check if the password is long enough
bool Password_Strength_Checker::isLongEnough(const std::string &password) {
    return password.length() >= 8;
}

// Function to generate the password rating message based on the security level
std::string Password_Strength_Checker::namePasswordRatings(const int levelSecurity) {
    switch (levelSecurity) {
        case 1:
            return "\nVery bad password (rating 1 out of 5)\n";
        case 2:
            return "\nBad password (score 2 out of 5)\n";
        case 3:
            return "\nNormal password (rating 3 out of 5)\n";
        case 4:
            return "\nGood password (rating 4 out of 5)\n";
        case 5:
            return "\nVery good password (rating 5 out of 5)\n";
    }
    return "null";
}

// Function to generate the error messages based on the password requirements not met
std::string Password_Strength_Checker::writeErrors(const bool hasLowerCase,
                                                   const bool hasUpperCase,
                                                   const bool hasDigit,
                                                   const bool hasSpecialChar,
                                                   const bool isLongEnough) {
    std::string errorLines = "";

    // Check if the password has lowercase letters and add error message if not
    if (!hasLowerCase) {
        errorLines += " * The password should contain lowercase letters.\n";
    }

    // Check if the password has uppercase letters and add error message if not
    if (!hasUpperCase) {
        errorLines += " * The password should contain uppercase letters.\n";
    }

    // Check if the password has digits and add error message if not
    if (!hasDigit) {
        errorLines += " * The password should contain digits.\n";
    }

    // Check if the password has special characters and add error message if not
    if (!hasSpecialChar) {
        errorLines += " * The password should contain special characters.\n";
    }

    // Check if the password is long enough and add error message if not
    if (!isLongEnough) {
        errorLines += " * The password should be long enough.\n";
    }

    return errorLines;
}

