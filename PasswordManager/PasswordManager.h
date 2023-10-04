#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "../FileEncryptor/FileEncryptor.h"
#include "../Password/Password.h"

namespace fs = std::filesystem;

/**
 * @class PasswordManager
 * @brief Class for managing user passwords.
 */
class PasswordManager {
private:
    std::string username; /**< User name */
    std::filesystem::path userDirectory; /**< Path to user directory */
    std::filesystem::path passwordFile; /**< Path to the password file */
    std::ofstream filePassword; /**< Output stream for the password file */

    std::filesystem::path importFile; /**< Path to the import file */
    std::ofstream importfilePassword; /**< Output stream for the import file */

    FileEncryptor fileEncryptor; /**< Object for file encryption and decryption */

public:
    /**
     * @brief Constructor for the PasswordManager class.
     * @param username The username.
     */
    PasswordManager(const std::string &username);

    /**
     * @brief Runs the password management menu.
     */
    void runMenu();

    /**
     * @brief Displays the password management menu.
     */
    void displayMenu();

    /**
     * @brief Processes the menu choice.
     * @param choice The user's choice.
     */
    void processMenuChoice(int choice);

    /**
     * @brief Adds a new password.
     */
    void addPassword();

    /**
     * @brief Removes a password.
     */
    void removePassword();

    /**
     * @brief Searches for a password by name.
     */
    void searchByPasswordName();

    /**
     * @brief Searches for a password by username.
     */
    void searchByUserName();

    /**
     * @brief Searches for a password by website.
     */
    void searchByWebsite();

    /**
     * @brief Changes a password.
     */
    void changePassword();

    /**
     * @brief Exports passwords.
     */
    void exportPasswords();

    /**
     * @brief Imports passwords.
     */
    void importPasswords();

    /**
     * @brief Exits the account.
     */
    void exitAccount();

    /**
     * @brief Clears the console.
     */
    void clearConsole();

/**
 * @brief Extracts the creation date from a line of text.
 *
 * @param line The line of text containing the creation date.
 * @return The extracted creation date.
 */
    static std::string extractCreationDate(const std::string& line);

/**
 * @brief Compares two lines of text based on their creation dates.
 *
 * @param line1 The first line of text.
 * @param line2 The second line of text.
 * @return True if line1 comes before line2 based on creation dates, False otherwise.
 */
    static bool compareLines(const std::string& line1, const std::string& line2);

/**
 * @brief Sorts password blocks in a file based on their creation dates.
 *
 * @param filePath The path to the file containing password blocks.
 */
    static void sortPasswordsInFile(const std::string& filePath);

};

#endif // PASSWORDMANAGER_H