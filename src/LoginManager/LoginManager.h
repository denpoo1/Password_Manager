#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <regex>
#include "../Password/Password.h"
#include "../User//User.h"
#include "../UserManager/UserManager.h"

using namespace std;

/**
 * @class LoginManager
 * @brief Manages the login and registration process for users.
 */
class LoginManager {
public:
    /**
     * @brief Runs the login manager.
     */
    void run();

private:
    /**
     * @brief Displays the main menu options.
     */
    void displayMainMenu();

    /**
     * @brief Processes the user's choice from the main menu.
     * @param choice The user's choice.
     */
    void processChoice(int choice);

    /**
     * @brief Performs the login process.
     */
    void performLogin();

    /**
     * @brief Performs the registration process.
     */
    void performRegistration();

    /**
     * @brief Saves the user's information to a file.
     * @param user The user to save.
     */
    void saveUserToFile(const User& user);

    /**
     * @brief Clears the console screen.
     */
    void clearConsole();

    /**
     * @brief Checks if the login credentials are valid.
     * @param username The username.
     * @param password The password.
     * @return True if the login is valid, false otherwise.
     */
    bool isLoginValid(const std::string& username, const std::string& password);

    UserManager userManager; /**< The user manager object. */
};

#endif // USER_H