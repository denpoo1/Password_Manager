#include "PasswordManager.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "../LoginManager/LoginManager.h"
#include <algorithm>
#include <sstream>
#include <vector>
#include <regex>

namespace fs = std::filesystem;

void PasswordManager::runMenu() {
    bool validChoice = false;
    do {
        displayMenu(); // Display the menu options to the user
        int choice;
        cin >> choice; // Read the user's choice from input

        if (cin.fail()) { // If input extraction fails (invalid choice)
            cin.clear(); // Clear the error state of cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore any remaining characters in the input buffer
            cout << "Invalid choice. Please try again." << endl; // Display an error message
        } else {
            validChoice = true; // Set validChoice flag to true since a valid choice is obtained
            processMenuChoice(choice); // Process the user's choice
        }
    } while (!validChoice); // Repeat the loop until a valid choice is obtained
}

void PasswordManager::displayMenu() {
    cout << "Password Manager Menu:" << endl;
    cout << "1. Remove Password" << endl;
    cout << "2. Search by Password Name" << endl;
    cout << "3. Search by Username" << endl;
    cout << "4. Search by Website" << endl;
    cout << "5. Export Passwords" << endl;
    cout << "6. Import Passwords" << endl;
    cout << "7. Change Password" << endl;
    cout << "8. Exit Account" << endl;
    cout << "9. Add Password" << endl;
    cout << "10. Sorted Passwords" << endl;
    cout << "Enter your choice: ";
}

void PasswordManager::processMenuChoice(int choice) {
    switch (choice) {
        case 1:
            removePassword();
            runMenu();
            break;
        case 2:
            searchByPasswordName();
            runMenu();
            break;
        case 3:
            searchByUserName();
            runMenu();
            break;
        case 4:
            searchByWebsite();
            runMenu();
            break;
        case 5:
            exportPasswords();
            runMenu();
            break;
        case 6:
            importPasswords();
            runMenu();
            break;
        case 7:
            changePassword();
            runMenu();
            break;
        case 8:
            exitAccount();
            runMenu();
            break;
        case 9:
            addPassword();
            runMenu();
            break;
        case 10:
            sortPasswordsInFile(passwordFile);
            runMenu();
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
}

PasswordManager::PasswordManager(const std::string &username)
        : username(username),
          userDirectory("../User_archive/" + username),
          passwordFile(userDirectory / (username + "_password.txt")),
          filePassword(),
          importFile(userDirectory / "import_file.txt"),
          importfilePassword(importFile.string(), std::ios::out | std::ios::app),
          fileEncryptor("null") {

    // Check if the user directory exists, and create it if it doesn't
    if (!std::filesystem::exists(userDirectory)) {
        std::filesystem::create_directory(userDirectory);
    }

    // Open the password file in append mode
    filePassword.open(passwordFile, std::ios::out | std::ios::app);
    if (!filePassword.is_open()) {
        std::cerr << "Failed to open password file: " << passwordFile.string() << std::endl;
    }

    // Set the path for the encrypted password file
    std::string encryptFileName =
            "../User_archive/" + username + "/" + username + "Encrypt_password.txt";

    // Check if the encrypted password file exists
    if (std::filesystem::exists(encryptFileName)) {
        std::cout << "Enter the decryption key: ";
        std::string decryptionKey;
        std::cin >> decryptionKey;

        // Create a FileEncryptor object with the decryption key
        FileEncryptor fileEncryptor(decryptionKey);

        // Decrypt the encrypted password file
        if (fileEncryptor.decryptFile(encryptFileName, passwordFile, decryptionKey)) {
            std::cout << "File decrypted successfully." << std::endl;

            // Delete the encrypted file after decryption
            if (std::filesystem::remove(encryptFileName)) {
                std::cout << "Encrypted file deleted successfully." << std::endl;
            } else {
                std::cerr << "Failed to delete encrypted file." << std::endl;
            }
        } else {
            std::cerr << "Failed to decrypt the file." << std::endl;
        }
    } else {
        // If the encrypted password file doesn't exist
        std::cout
                << "Generate the decryption code. Please remember it, as it will be deleted after this operation and cannot be recovered."
                << std::endl;

        // Create a Password object with a default value of "null"
        Password password("null");

        // Generate a decryption code using the password generation function
        fileEncryptor = FileEncryptor(password.passwordGenerationWithChoice("null"));
    }
}

void PasswordManager::removePassword() {
    // Print the password file path for debugging purposes
    std::cout << passwordFile << std::endl;

    // Open the password file for reading
    std::ifstream inputFile(passwordFile);
    if (inputFile.is_open()) {
        // Store each password line in a vector
        std::vector<std::string> passwordLines;
        std::string line;
        while (std::getline(inputFile, line)) {
            // Check if the line contains the "Creation Date" string
            if (line.find("Creation Date: ") != std::string::npos) {
                passwordLines.push_back(line);
            } else {
                // Append the line to the previous password line
                passwordLines.back() += "\n" + line;
            }
        }

        // Check if there are any passwords in the file
        if (passwordLines.empty()) {
            std::cout << "No passwords found." << std::endl;
            inputFile.close();
            return;
        }

        // Print the list of passwords with their indices
        for (size_t i = 0; i < passwordLines.size(); ++i) {
            std::cout << (i + 1) << ". " << passwordLines[i] << std::endl;
        }

        // Prompt the user to enter the index of the password to delete
        int selectedPasswordIndex;
        std::cout << "Enter the index of the password to delete (1-" << passwordLines.size() << "): ";
        std::cin >> selectedPasswordIndex;

        // Check if the selected index is valid
        if (selectedPasswordIndex < 1 || selectedPasswordIndex > passwordLines.size()) {
            std::cerr << "Invalid password index." << std::endl;
            inputFile.close();
            return;
        }

        inputFile.close();

        // Open the password file for writing
        std::ofstream outputFile(passwordFile);

        if (outputFile.is_open()) {
            // Write all passwords except the one to be deleted to the file
            for (size_t i = 0; i < passwordLines.size(); ++i) {
                if (i + 1 != selectedPasswordIndex) {
                    outputFile << passwordLines[i] << std::endl;
                }
            }

            outputFile.close();
            std::cout << "Password removed successfully." << std::endl;
        } else {
            std::cerr << "Error opening password file for writing." << std::endl;
        }
    } else {
        std::cerr << "Error opening password file for reading." << std::endl;
    }
}


void PasswordManager::searchByPasswordName() {
    std::string searchName;
    std::cout << "Enter the name of the password to search: ";
    std::cin >> searchName;

    // Open the password file for reading
    std::ifstream inputFile(passwordFile);
    if (inputFile.is_open()) {
        std::string line;
        bool found = false;
        bool printPassword = false;
        std::string passwordContent;
        std::vector<std::string> previousLines;

        // Read each line from the password file
        while (std::getline(inputFile, line)) {
            // Check if the line contains the search name
            if (line.find("Password Name: " + searchName) != std::string::npos) {
                found = true;
                std::cout << line << std::endl;

                // Print the two lines before the Password Name line
                for (const auto &previousLine: previousLines) {
                    std::cout << previousLine << std::endl;
                }

                // Print the rest of the password information until an empty line is encountered
                while (std::getline(inputFile, line)) {
                    if (line.empty())
                        break;
                    std::cout << line << std::endl;
                }

                std::cout << std::endl; // Add extra empty line between passwords
            }

            if (!printPassword) {
                // Store the previous lines for printing
                previousLines.push_back(line);

                // Maintain only the last two lines
                if (previousLines.size() > 2) {
                    previousLines.erase(previousLines.begin());
                }
            }
        }

        inputFile.close();

        if (!found) {
            std::cout << "No passwords found with the name: " << searchName << std::endl;
        }
    } else {
        std::cerr << "Error opening password file for reading." << std::endl;
    }
}

void PasswordManager::searchByUserName() {
    std::string searchUserName;
    std::cout << "Enter the username to search for: ";
    std::cin >> searchUserName;

    // Open the password file for reading
    std::ifstream inputFile(passwordFile);
    if (inputFile.is_open()) {
        std::string line;
        bool found = false;
        bool printPassword = false;
        std::string passwordContent;
        std::vector<std::string> previousLines;

        // Read each line from the password file
        while (std::getline(inputFile, line)) {
            // Check if the line contains the search username
            if (line.find("Username: " + searchUserName) != std::string::npos) {
                found = true;
                std::cout << line << std::endl;

                // Print the three lines before the Username line
                for (const auto &previousLine: previousLines) {
                    std::cout << previousLine << std::endl;
                }

                // Print the rest of the password information until an empty line is encountered
                while (std::getline(inputFile, line)) {
                    if (line.empty())
                        break;
                    std::cout << line << std::endl;
                }

                std::cout << std::endl; // Add extra empty line between passwords
            }

            if (!printPassword) {
                // Store the previous lines for printing
                previousLines.push_back(line);

                // Maintain only the last three lines
                if (previousLines.size() > 3) {
                    previousLines.erase(previousLines.begin());
                }
            }
        }

        inputFile.close();

        if (!found) {
            std::cout << "No passwords found for the username: " << searchUserName << std::endl;
        }
    } else {
        std::cerr << "Error opening password file for reading." << std::endl;
    }
}

void PasswordManager::searchByWebsite() {
    std::string searchWebsite;
    std::cout << "Enter the website to search for: ";
    std::cin >> searchWebsite;

    // Open the password file for reading
    std::ifstream inputFile(passwordFile);
    if (inputFile.is_open()) {
        std::string line;
        bool found = false;
        bool printPassword = false;
        std::string passwordContent;
        std::vector<std::string> previousLines;

        // Read each line from the password file
        while (std::getline(inputFile, line)) {
            // Check if the line starts with "Website: "
            if (line.substr(0, 9) == "Website: ") {
                std::string website = line.substr(9);
                // Check if the website matches the search website
                if (website == searchWebsite) {
                    found = true;
                    printPassword = true;

                    // Print the previous lines before the matching website
                    for (const auto &previousLine: previousLines) {
                        std::cout << previousLine << std::endl;
                    }
                }
            }

            // Store the previous lines for printing
            previousLines.push_back(line);

            // Maintain only the last five lines
            if (previousLines.size() > 5) {
                previousLines.erase(previousLines.begin());
            }

            if (printPassword) {
                // Append the line to the password content
                passwordContent += line + "\n";
            }

            if (line.empty() && printPassword) {
                // Print the password content when an empty line is encountered
                std::cout << passwordContent << std::endl;
                passwordContent.clear();
                printPassword = false;
            }
        }

        inputFile.close();

        if (!found) {
            std::cout << "No passwords found for the website: " << searchWebsite << std::endl;
        }
    } else {
        std::cerr << "Error opening password file for reading." << std::endl;
    }
}

void PasswordManager::exportPasswords() {
    std::string exportFilePath;
    std::cout << "Enter the export file path: ";
    std::cin >> exportFilePath;

    // Open the export file for writing
    std::ofstream outputFile(exportFilePath);

    if (outputFile.is_open()) {
        // Open the password file for reading
        std::ifstream inputFile(passwordFile);
        if (inputFile.is_open()) {
            // Copy the contents of the password file to the export file
            outputFile << inputFile.rdbuf();
            inputFile.close();
            outputFile.close();
            std::cout << "Passwords exported successfully to: " << exportFilePath << std::endl;
        } else {
            std::cerr << "Error opening password file for reading." << std::endl;
        }
    } else {
        std::cerr << "Error opening export file for writing." << std::endl;
    }
}

void PasswordManager::importPasswords() {
    std::string importFilePath;
    std::cout << "Enter the absolute file path to import from: ";
    std::cin >> importFilePath;

    // Open the import file for reading
    std::ifstream inputFile(importFilePath);

    if (inputFile.is_open()) {
        // Open the password file for writing and appending
        std::ofstream outputFile(importFile, std::ios::out | std::ios::app);
        if (outputFile.is_open()) {
            // Append the contents of the import file to the password file
            outputFile << inputFile.rdbuf();
            inputFile.close();
            outputFile.close();
            std::cout << "Passwords imported successfully from: " << importFilePath << std::endl;
        } else {
            std::cerr << "Error opening password file for writing." << std::endl;
        }
    } else {
        std::cerr << "Error opening import file for reading." << std::endl;
    }
}

void PasswordManager::changePassword() {
    // Create a Password object with a placeholder value
    Password password("null");
    std::ifstream inputFile(passwordFile);
    if (inputFile.is_open()) {
        // Read all lines from the password file
        std::vector<std::string> passwordLines;
        std::string line;
        while (std::getline(inputFile, line)) {
            passwordLines.push_back(line);
        }
        if (passwordLines.empty()) {
            std::cout << "No passwords found." << std::endl;
            inputFile.close();
            return;
        }

        // Count the number of passwords and display them to the user
        int passwordCount = 0;
        for (size_t i = 0; i < passwordLines.size(); ++i) {
            if (passwordLines[i].find("Password: ") != std::string::npos) {
                passwordCount++;
                std::cout << passwordCount << ". " << passwordLines[i] << std::endl;
            } else {
                std::cout << passwordLines[i] << std::endl;
            }
        }

        // Prompt the user to select a password to change
        int selectedPasswordIndex;
        std::cout << "Enter the index of the password to change (1-" << passwordCount << "): ";
        std::cin >> selectedPasswordIndex;

        // Validate the selected password index
        if (selectedPasswordIndex < 1 || selectedPasswordIndex > passwordCount) {
            std::cerr << "Invalid password index." << std::endl;
            inputFile.close();
            return;
        }

        // Generate a new password
        std::string newPassword;
        newPassword = password.passwordGenerationWithChoice("null");

        // Update the selected password with the new password and modification date
        int passwordIndex = 0;
        for (size_t i = 0; i < passwordLines.size(); ++i) {
            if (passwordLines[i].find("Password: ") != std::string::npos) {
                passwordIndex++;
                if (passwordIndex == selectedPasswordIndex) {
                    passwordLines[i] = "Password: " + newPassword;
                    if (i >= 3) {
                        std::string &modificationDateLine = passwordLines[i - 3];
                        modificationDateLine = "Modification Date: " + password.getTimeNow();
                    }
                }
            }
        }

        inputFile.close();

        // Open the password file for writing and overwrite its contents
        std::ofstream outputFile(passwordFile);

        if (outputFile.is_open()) {
            // Write the updated password lines to the file
            for (const std::string &passwordLine: passwordLines) {
                outputFile << passwordLine << std::endl;
            }

            outputFile.close();
            std::cout << "Password changed successfully." << std::endl;
        } else {
            std::cerr << "Error opening password file for writing." << std::endl;
        }
    } else {
        std::cerr << "Error opening password file for reading." << std::endl;
    }
}

void PasswordManager::exitAccount() {
    // Create a copy of the password file with encrypted content
    std::filesystem::path passwordFileCopy(userDirectory / (username + "Encrypt_password.txt"));
    fileEncryptor.encryptFile(passwordFile, passwordFileCopy);

    // Remove the original unencrypted password file
    std::filesystem::remove(userDirectory / (username + "_password.txt"));

    // Start the LoginManager to log in with another account
    LoginManager loginManager;
    clearConsole();
    loginManager.run();
}

void PasswordManager::addPassword() {
    // Open the password file for appending
    std::ofstream filePassword(passwordFile, std::ios::app);
    if (!filePassword) {
        std::cout << "Error opening password file.\n";
        return;
    }

    // Create a Password object and generate a new password
    Password password;
    std::string passwordString = password.toString();

    if (passwordString.empty()) {
        std::cout << "Error generating password.\n";
        filePassword.close();
        return;
    }

    // Write the new password to the file
    filePassword << passwordString << std::endl;

    if (filePassword.fail()) {
        std::cout << "Error writing password to file.\n";
        filePassword.close();
        return;
    }

    filePassword.close();
    std::cout << "Password added successfully!\n";
}

void PasswordManager::clearConsole() {
    // Clear the console screen based on the operating system
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

std::string PasswordManager::extractCreationDate(const std::string &line) {
    // Extracts the creation date from a line of text
    std::regex dateRegex(R"(Creation Date: (\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}))");
    std::smatch match;
    if (std::regex_search(line, match, dateRegex)) {
        return match[1].str();
    }
    return "";
}

bool PasswordManager::compareLines(const std::string &line1, const std::string &line2) {
    // Compares two lines of text based on their creation dates
    std::string date1 = extractCreationDate(line1);
    std::string date2 = extractCreationDate(line2);
    return date1 < date2;
}

void PasswordManager::sortPasswordsInFile(const std::string &filePath) {
    // Sorts password blocks in a file based on their creation dates
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file: " << filePath << std::endl;
        return;
    }

    std::vector<std::string> passwordBlocks;
    std::string line;
    std::string currentPasswordBlock;

    // Read the file and store each password block in a vector
    while (std::getline(inputFile, line)) {
        if (line.empty() && !currentPasswordBlock.empty()) {
            passwordBlocks.push_back(currentPasswordBlock);
            currentPasswordBlock.clear();
        } else {
            currentPasswordBlock += line + '\n';
        }
    }

    if (!currentPasswordBlock.empty()) {
        passwordBlocks.push_back(currentPasswordBlock);
    }

    inputFile.close();

    // Sort the password blocks based on creation dates
    std::sort(passwordBlocks.begin(), passwordBlocks.end(), compareLines);

    std::ofstream outputFile(filePath);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open the file for writing: " << filePath << std::endl;
        return;
    }

    // Write the sorted password blocks to the file
    for (const auto &sortedPasswordBlock: passwordBlocks) {
        outputFile << sortedPasswordBlock << '\n';
    }

    outputFile.close();

    std::cout << "Passwords sorted and saved successfully." << std::endl;
}




