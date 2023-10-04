#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>

/**
 * @brief The Password class represents a password entity.
 */
class Password {
public:
    /**
     * @brief Generates a password with user-specified criteria.
     * @return The generated password.
     */
    std::string passwordGenerationWithChoice();

    /**
     * @brief Generates a password with user-specified criteria or uses a default function.
     * @param defaultFunction The default function to use if user chooses "generate" option.
     * @return The generated or entered password.
     */
    std::string passwordGenerationWithChoice(std::string defaultFunction);

    /**
     * @brief Gets the current time as a string.
     * @return The current time in the format "YYYY-MM-DD HH:MM:SS".
     */
    std::string getTimeNow();

    /**
     * @brief Converts the Password object to a string representation.
     * @return The string representation of the Password object.
     */
    std::string toString();

    /**
     * @brief Changes the modification time of the password to the current time.
     */
    void change_Modification_Time();

    /**
     * @brief Default constructor for the Password class.
     */
    Password();

    /**
     * @brief Constructor for the Password class with a default parameter.
     * @param defaultKostruktor The default parameter for the constructor.
     */
    Password(std::string defaultKostruktor);

private:
    /**
     * @brief Generates a random password based on user-specified criteria.
     * @return The generated password.
     */
    std::string generatePassword();

    /**
     * @brief Prompts the user to enter a password.
     * @return The entered password.
     */
    std::string userPassword();

    /**
     * @brief Checks if a website has a valid format.
     * @param website The website to validate.
     * @return True if the website has a valid format, false otherwise.
     */
    bool isWebsiteValid(std::string& website);

    std::string passwordName;        /**< The name of the password. */
    std::string username;            /**< The username associated with the password. */
    std::string password;            /**< The password string. */
    std::string website;             /**< The website associated with the password. */
    std::string additionalNotes;     /**< Additional notes about the password. */
    std::string createTime;          /**< The creation time of the password. */
    std::string modificationTime;    /**< The modification time of the password. */
};

#endif  // PASSWORD_H