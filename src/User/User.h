#include <iostream>
#include <string>
#include "../Password/Password.h"

#ifndef UNTITLED3_USER_H
#define UNTITLED3_USER_H

using namespace std;

/**
 * @class User
 * @brief Represents a user with personal information.
 */
class User {
public:
    string username; /**< User's username */
    string mail; /**< User's email address */
    string firstName; /**< User's first name */
    string lastName; /**< User's last name */
    string phoneNumber; /**< User's phone number */
    string passwordFromPersonalAccount; /**< User's password from the personal account */
    Password password = Password("null"); /**< User's password object */

    /**
     * @brief Default constructor for the User class.
     * Prompts the user to enter personal information and generates a password.
     */
    User() {
        username = createUser();
        firstName = checkName();
        lastName = checkLastName();
        mail = checkMail();
        phoneNumber = checkNumber();
        passwordFromPersonalAccount = password.passwordGenerationWithChoice("null");

        cout << "First Name: " << firstName << endl;
        cout << "Last Name: " << lastName << endl;
        cout << "Email: " << mail << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Password: " << passwordFromPersonalAccount << endl;
    }

    /**
     * @brief Validates and retrieves the user's first name.
     * @return The user's first name.
     */
    string checkName();

    /**
     * @brief Validates and retrieves the user's phone number.
     * @return The user's phone number.
     */
    string checkNumber();

    /**
     * @brief Creates the user's username.
     * @return The user's username.
     */
    string createUser();

    /**
     * @brief Gets the user's username.
     * @return The user's username.
     */
    string getUserName();

    /**
     * @brief Validates and retrieves the user's email address.
     * @return The user's email address.
     */
    string checkMail();

    /**
     * @brief Validates and retrieves the user's last name.
     * @return The user's last name.
     */
    string checkLastName();

    /**
     * @brief Converts the user object to a string representation.
     * @return The string representation of the user object.
     */
    string toString();
};

#endif //UNTITLED3_USER_H