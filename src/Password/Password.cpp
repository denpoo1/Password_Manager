#include "Password.h"
#include <iostream>
#include <string>
#include "../Password_Strength_Checker/Password_Strength_Checker.h"
#include <ctime>
#include <sstream>
#include <iomanip>

Password::Password() {
    // Input password name
    std::cout << "Enter password name: ";
    std::cin >> passwordName;

    // Input username
    std::cout << "Enter username: ";
    std::cin >> username;

    password = Password::passwordGenerationWithChoice();

    // Input website
    std::cout << "Enter website: ";
    std::getline(std::cin, website);

    // Validate website
    if (!Password::isWebsiteValid(website)) {
        std::cerr << "Invalid website format. Aborting." << std::endl;
        return;
    }

    // Input additional notes
    std::cout << "Enter additional notes: ";
    std::getline(std::cin, additionalNotes);

    createTime = Password::getTimeNow();
    modificationTime = Password::getTimeNow();

    // Output entered data
    std::cout << "Password created: " << createTime << std::endl;
    std::cout << "Password modification: " << modificationTime << std::endl;
    std::cout << "Password Name: " << passwordName << std::endl;
    std::cout << "Username: " << username << std::endl;
    std::cout << "Password: " << password << std::endl;
    std::cout << "Website: " << website << std::endl;
    std::cout << "Additional Notes: " << additionalNotes << std::endl;
}

Password::Password(std::string defaultKostruktor) {}

bool Password::isWebsiteValid(std::string &website) {
    // Validate website
    // Implement your validation rules here
    // Example: Check if the website starts with "http://" or "https://"
    if (website.substr(0, 7) == "http://" || website.substr(0, 8) == "https://") {
        return true;
    }

    std::cerr << "Invalid website format. Please enter a valid website: ";
    std::getline(std::cin, website);

    // Recursive call to re-validate the updated website
    return isWebsiteValid(website);
}

std::string Password::generatePassword() {
    std::string password;

    // Prompt user for password criteria
    std::cout << "Password Generation:" << std::endl;

    // Include lowercase characters?
    char includeLowercase;
    do {
        std::cout << "Include lowercase characters? (y/n): ";
        std::cin >> includeLowercase;
        // Ignore any remaining characters in the input buffer up to the newline character ('\n')
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (includeLowercase != 'y' && includeLowercase != 'n');

    // Include uppercase characters?
    char includeUppercase;
    do {
        std::cout << "Include uppercase characters? (y/n): ";
        std::cin >> includeUppercase;
        // Ignore any remaining characters in the input buffer up to the newline character ('\n')
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (includeUppercase != 'y' && includeUppercase != 'n');

    // Include digits?
    char includeDigits;
    do {
        std::cout << "Include digits? (y/n): ";
        std::cin >> includeDigits;
        // Ignore any remaining characters in the input buffer up to the newline character ('\n')
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (includeDigits != 'y' && includeDigits != 'n');

    // Include special characters?
    char includeSpecialChars;
    do {
        std::cout << "Include special characters? (y/n): ";
        std::cin >> includeSpecialChars;
        // Ignore any remaining characters in the input buffer up to the newline character ('\n')
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (includeSpecialChars != 'y' && includeSpecialChars != 'n');

    // Password length
    std::cout << "Password length: ";
    int passwordLength;
    while (!(std::cin >> passwordLength)) {
        std::cout << "Invalid input. Please enter a valid number: ";
        std::cin.clear();
        // Ignore any remaining characters in the input buffer up to the newline character ('\n')
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Generate password based on selected criteria
    std::string allowedChars;
    if (includeLowercase == 'y') {
        allowedChars += "abcdefghijklmnopqrstuvwxyz";
    }
    if (includeUppercase == 'y') {
        allowedChars += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }
    if (includeDigits == 'y') {
        allowedChars += "0123456789";
    }
    if (includeSpecialChars == 'y') {
        allowedChars += "!@#$%^&*()";
    }

    // Check if at least one type of character is allowed
    if (!allowedChars.empty()) {
        for (int i = 0; i < passwordLength; ++i) {
            int randomIndex = rand() % allowedChars.length();
            password += allowedChars[randomIndex];
        }
    }

    return password;
}


std::string Password::userPassword() {
    std::string password;
    Password_Strength_Checker passwordStrengthChecker;
    bool keepPassword = false;

    while (!keepPassword) {
        std::cout << "Enter password: ";
        std::cin >> password;

        passwordStrengthChecker.checkStrength(password);

        char answer;
        std::cout << "\nDo you want to keep this password? (y/n): ";
        std::cin >> answer;

        if (answer == 'y') {
            keepPassword = true;
        } else if (answer != 'n') {
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }

    return password;
}


std::string Password::passwordGenerationWithChoice() {
    // Password entry or generation
    std::cout << "Do you want to enter your own password or generate one? (enter/generate): ";
    std::string choice;
    std::cin >> choice;
    if (choice == "enter") {
        return Password::userPassword();
    } else if (choice == "generate") {
        return Password::generatePassword();
    } else {
        std::cerr << "Invalid choice. Aborting." << std::endl;
        return passwordGenerationWithChoice();
    }
}

std::string Password::passwordGenerationWithChoice(std::string defaultFunction) {
    // Password entry or generation
    std::cout << "Do you want to enter your own password or generate one? (enter/generate): ";
    std::string choice;
    std::cin >> choice;
    if (choice == "enter") {
        return Password::userPassword();
    } else if (choice == "generate") {
        return Password::generatePassword();
    } else {
        std::cerr << "Invalid choice. Aborting." << std::endl;
        //Recursive
        passwordGenerationWithChoice();
    }
}

std::string Password::toString() {
    std::string result;
    result += "Creation Date: " + createTime + "\n";
    result += "Modification Date: " + modificationTime + "\n";
    result += "Password Name: " + passwordName + "\n";
    result += "Username: " + username + "\n";
    result += "Password: " + password + "\n";
    result += "Website: " + website + "\n";
    result += "Additional Notes: " + additionalNotes + "\n\n";
    return result;
}


std::string Password::getTimeNow() {
    // Get the current system time
    std::time_t currentTime = std::time(nullptr);

    // Convert the current time to a local time representation
    std::tm *timeinfo = std::localtime(&currentTime);

    // Create an output string stream to format the time
    std::ostringstream oss;

    // Format the time using strftime and store it in the output string stream
    oss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");

    // Convert the output string stream to a string and return it
    return oss.str();
}


void Password::change_Modification_Time() {
    modificationTime = getTimeNow();
}
