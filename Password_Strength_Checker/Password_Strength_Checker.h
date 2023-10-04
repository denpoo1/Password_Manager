#ifndef PASSWORD_STRENGTH_CHECKER_H
#define PASSWORD_STRENGTH_CHECKER_H

#include <string>

/**
 * @class Password_Strength_Checker
 * @brief Class for checking the strength of a password.
 */
class Password_Strength_Checker {
public:
    /**
     * @brief Default constructor for Password_Strength_Checker.
     */
    Password_Strength_Checker();

    /**
     * @brief Checks the strength of the given password.
     * @param password The password to check.
     * @return The strength rating of the password (a value between 1 and 5).
     */
    int checkStrength(const std::string &password);

private:
    /**
     * @brief Checks if the password contains lowercase letters.
     * @param password The password to check.
     * @return True if the password has lowercase letters, false otherwise.
     */
    bool hasLowerCase(const std::string &password);

    /**
     * @brief Checks if the password contains uppercase letters.
     * @param password The password to check.
     * @return True if the password has uppercase letters, false otherwise.
     */
    bool hasUpperCase(const std::string &password);

    /**
     * @brief Checks if the password contains digits.
     * @param password The password to check.
     * @return True if the password has digits, false otherwise.
     */
    bool hasDigit(const std::string &password);

    /**
     * @brief Checks if the password contains special characters.
     * @param password The password to check.
     * @return True if the password has special characters, false otherwise.
     */
    bool hasSpecialChar(const std::string &password);

    /**
     * @brief Checks if the password is long enough.
     * @param password The password to check.
     * @return True if the password is long enough, false otherwise.
     */
    bool isLongEnough(const std::string &password);

    std::string writeErrors(const bool hasLowerCase,
                            const bool hasUpperCase,
                            const bool hasDigit,
                            const bool hasSpecialChar,
                            const bool isLongEnough);

    std::string namePasswordRatings(const int levelSecurity);


};

#endif  // PASSWORD_STRENGTH_CHECKER_H