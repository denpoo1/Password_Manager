/**
 * @file FileEncryptor.h
 *
 * @brief This file contains the declaration of the FileEncryptor class.
 */

#ifndef FILEENCRYPTOR_H
#define FILEENCRYPTOR_H

#include <string>

/**
 * @class FileEncryptor
 *
 * @brief The FileEncryptor class provides methods for file encryption and decryption.
 */
class FileEncryptor {
public:
    /**
     * @brief Constructs a FileEncryptor object with the specified key.
     *
     * @param key The encryption key to be used.
     */
    FileEncryptor(const std::string& key);

    /**
     * @brief Encrypts the contents of the input file and writes the encrypted data to the output file.
     *
     * @param inputFile The path to the input file.
     * @param outputFile The path to the output file.
     *
     * @return True if the file was encrypted successfully, false otherwise.
     */
    bool encryptFile(const std::string& inputFile, const std::string& outputFile);

    /**
     * @brief Decrypts the contents of the input file using the specified key and writes the decrypted data to the output file.
     *
     * @param inputFile The path to the input file.
     * @param outputFile The path to the output file.
     * @param key The encryption key used for decryption.
     *
     * @return True if the file was decrypted successfully, false otherwise.
     */
    bool decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);

private:
    std::string key_; /**< The encryption key. */

    /**
     * @brief Encrypts a single character using the Caesar cipher algorithm.
     *
     * @param ch The character to be encrypted.
     *
     * @return The encrypted character.
     */
    char encryptCaesar(char ch);

    /**
     * @brief Decrypts a single character using the Caesar cipher algorithm.
     *
     * @param ch The character to be decrypted.
     *
     * @return The decrypted character.
     */
    char decryptCaesar(char ch);
};

#endif  // FILEENCRYPTOR_H
