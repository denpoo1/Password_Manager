#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <vector>
#include "../User//User.h"

/**
 * @class UserManager
 * @brief Manages user registration, login, and retrieval.
 */
class UserManager {
public:
    /**
     * @brief Registers a new user.
     */
    void registerUser();

    /**
     * @brief Logs in a user with the provided username and password.
     * @param username The username of the user.
     * @param password The password of the user.
     * @return True if the login is successful, false otherwise.
     */
    bool loginUser(const std::string& username, const std::string& password);

    /**
     * @brief Retrieves a user with the provided username.
     * @param username The username of the user.
     * @return A pointer to the User object if found, nullptr otherwise.
     */
    User* getUser(const std::string& username);

    /**
     * @brief Saves a user to the user database.
     * @param user The User object to save.
     */
    void saveUser(const User& user);

    /**
     * @brief Retrieves the last registered user.
     * @return The last registered User object, or a default User object if no users are registered.
     */
    User getLastUser();

private:
    std::vector<User> users; /**< The collection of registered users */

    /**
     * @brief Checks if a username is already taken.
     * @param username The username to check.
     * @return True if the username is already taken, false otherwise.
     */
    bool isUsernameTaken(const std::string& username);
};

#endif // USERMANAGER_H