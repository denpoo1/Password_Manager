#include <iostream>
#include <string>
#include <regex>
#include "../Password/Password.h"
#include "../User//User.h"
#include "../UserManager/UserManager.h"
#include "LoginManager.h"
#include <fstream>
#include "../PasswordManager/PasswordManager.h"
#include <fstream>
#include <sstream>
#include "../FileEncryptor/FileEncryptor.h"

void LoginManager::run() {
    bool validChoice = false;
    do {
        displayMainMenu();
        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            clearConsole();
            cout << "Invalid choice. Please try again." << endl;
        } else {
            validChoice = true;
            processChoice(choice);
        }
    } while (!validChoice);
}

void LoginManager::displayMainMenu() {
    cout << "Personal Account Login:" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "Enter your choice: ";
}

void LoginManager::processChoice(int choice) {
    switch (choice) {
        case 1:
            performLogin();
            break;
        case 2:
            performRegistration();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
}

void LoginManager::performLogin() {
    std::string username, password;
    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;

    if (isLoginValid(username, password)) {
        std::cout << "Login successful. Welcome, " << username << "!" << std::endl;
        PasswordManager passwordMeneger(username);
        clearConsole();
        passwordMeneger.runMenu();
    } else {
        clearConsole();
        std::cout << "Login failed. Invalid username or password." << std::endl;
        run();
    }
}

bool LoginManager::isLoginValid(const std::string &username, const std::string &password) {
    // File paths
    string fileDeskrypt = "../Admin/fileDeskrypt.txt";
    string fileEncrypt = "../Admin/user_repository.txt";
//    /Users/denpool/CLionProjects/Password_Manager/Admin/fileDeskrypt.txt
//    /Users/denpool/CLionProjects/Password_Manager/Admin/user_repository.txt
    string encryptionKey = "123";

    // Decrypt the encrypted file
    FileEncryptor fileEncryptor(encryptionKey);
    fileEncryptor.decryptFile(fileEncrypt, fileDeskrypt, encryptionKey);

    // Open the decrypted file
    std::ifstream fileDeskrypt1(fileDeskrypt);
    if (!fileDeskrypt1.is_open()) {
        std::cout << "Error opening fileDeskrypt." << std::endl;
        return false;
    }

    std::string line;
    std::string currentUsername;
    std::string currentPassword;

// Read each line from the file
    while (std::getline(fileDeskrypt1, line)) {
        std::istringstream iss(line);
        std::string key;
        std::string value;

        // Split the line into key and value using ':' as the delimiter
        if (std::getline(iss, key, ':') && std::getline(iss, value)) {
            if (key == "Username") {
                // Store the value as the current username
                currentUsername = value;
                currentUsername.erase(0, 1); // Remove leading whitespace
            } else if (key == "Password") {
                // Store the value as the current password
                currentPassword = value;
                currentPassword.erase(0, 1); // Remove leading whitespace
            }
        }

        // Check if the current username and password match the provided values
        if (currentUsername == username && currentPassword == password) {
            // Close the file since the match is found
            fileDeskrypt1.close();

            // Delete the decrypted file
            if (std::remove(fileDeskrypt.c_str()) != 0) {
                std::cout << "Error deleting fileDeskrypt." << std::endl;
            } else {
                std::cout << "File fileDeskrypt.txt deleted successfully." << std::endl;
            }

            return true;
        }
    }
    fileDeskrypt1.close();
    return false;
}

void LoginManager::performRegistration() {
    User user;
    saveUserToFile(user);
    clearConsole();
    cout << "Registration successful. Welcome, " << user.getUserName() << "!" << endl;
    // Perform actions after successful registration
    PasswordManager passwordmanager(user.getUserName());
    passwordmanager.runMenu();
}

void LoginManager::saveUserToFile(const User &user) {
    string fileDeskrypt = "../Admin/fileDeskrypt.txt";
    string fileEncrypt = "../Admin/user_repository.txt";
    string encryptionKey = "123";

    // Decrypt the encrypted file
    FileEncryptor fileEncryptor(encryptionKey);
    fileEncryptor.decryptFile(fileEncrypt, fileDeskrypt, encryptionKey);

    // Open the decrypted file in append mode
    std::ofstream fileDeskrypt1(fileDeskrypt, std::ios::app);

    // Save the user to the user manager
    userManager.saveUser(user);

    if (fileDeskrypt1.is_open()) {
        // Append the user details to the file
        fileDeskrypt1 << userManager.getLastUser().toString() << "\n";
        fileDeskrypt1.close();
    } else {
        std::cout << "Error opening fileDeskrypt." << std::endl;
        return;
    }

    // Encrypt the decrypted file
    fileEncryptor.encryptFile(fileDeskrypt, fileEncrypt);

    // Clear the contents of the encrypted file
    std::ofstream fileEncrypt1(fileEncrypt, std::ofstream::out | std::ofstream::trunc);

    if (fileEncrypt1.is_open()) {
        fileEncrypt1.close();
        std::cout << "Encryption completed successfully." << std::endl;
    } else {
        std::cout << "Error opening fileEncrypt." << std::endl;
    }

    // Encrypt the decrypted file again
    fileEncryptor.encryptFile(fileDeskrypt, fileEncrypt);

    // Delete the decrypted file
    if (std::remove(fileDeskrypt.c_str()) != 0) {
        std::cout << "Error deleting fileDeskrypt." << std::endl;
    } else {
        std::cout << "File fileDeskrypt.txt deleted successfully." << std::endl;
    }
}

void LoginManager::clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
