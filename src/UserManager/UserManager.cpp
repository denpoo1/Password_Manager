#include "usermanager.h"
#include <iostream>
#include "../User/User.h"

// Register a new user
void UserManager::registerUser() {
    User user;

    std::cout << "Enter your username: ";
    std::cin >> user.username;

    // Check if the username is already taken
    if (isUsernameTaken(user.username)) {
        std::cout << "Username is already taken. Please choose a different username." << std::endl;
        return;
    }

    std::cout << "Enter your first name: ";
    std::cin >> user.firstName;

    std::cout << "Enter your last name: ";
    std::cin >> user.lastName;

    std::cout << "Enter your email: ";
    std::cin >> user.mail;

    std::cout << "Enter your phone number: ";
    std::cin >> user.phoneNumber;

    std::cout << "Enter your password: ";
    std::cin >> user.passwordFromPersonalAccount;

    // Additional logic for generating password with Password class

    // Save the user
    saveUser(user);

    std::cout << "User registration successful." << std::endl;
}

// Login a user
bool UserManager::loginUser(const std::string& username, const std::string& password) {
    // Get the user with the provided username
    User* user = getUser(username);

    if (user == nullptr) {
        std::cout << "User not found." << std::endl;
        return false;
    }

    // Check if the provided password matches the user's password
    if (user->passwordFromPersonalAccount != password) {
        std::cout << "Incorrect password." << std::endl;
        return false;
    }

    std::cout << "Login successful." << std::endl;
    return true;
}

// Get a user by username
User* UserManager::getUser(const std::string& username) {
    for (User& user : users) {
        if (user.username == username) {
            return &user;
        }
    }
    return nullptr;
}

// Save a user
void UserManager::saveUser(const User& user) {
    users.push_back(user);
}

// Check if a username is already taken
bool UserManager::isUsernameTaken(const std::string& username) {
    for (const User& user : users) {
        if (user.username == username) {
            return true;
        }
    }
    return false;
}

// Get the last user in the list
User UserManager::getLastUser() {
    if (!users.empty()) {
        return users[users.size() - 1];
    }
    return User();
}
