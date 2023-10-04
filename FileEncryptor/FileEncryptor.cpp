#include "FileEncryptor.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

FileEncryptor::FileEncryptor(const std::string& key) : key_(key) {}

bool FileEncryptor::encryptFile(const std::string& inputFile, const std::string& outputFile) {
    // Open input and output files
    std::ifstream ifs(inputFile, std::ios::binary);
    std::ofstream ofs(outputFile, std::ios::binary);

    if (!ifs || !ofs) {
        // Check if file opening failed
        std::cerr << "Failed to open files." << std::endl;
        return false;
    }

    // Read input file into a vector<char>
    std::vector<char> buffer(std::istreambuf_iterator<char>(ifs), {});
    ifs.close();

    // XOR encryption
    for (std::size_t i = 0; i < buffer.size(); ++i) {
        // Get the corresponding character from the encryption key
        char keyChar = key_[i % key_.size()];
        // XOR the buffer character with the key character
        buffer[i] = buffer[i] ^ keyChar;
    }

    // Transposition
    std::reverse(buffer.begin(), buffer.end());

    // Write the encrypted buffer to the output file
    ofs.write(&buffer[0], buffer.size());
    ofs.close();

    std::cout << "Encryption completed successfully." << std::endl;
    return true;
}

bool FileEncryptor::decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key_deskrypt_) {
    // Open input and output files
    std::ifstream ifs(inputFile, std::ios::binary);
    std::ofstream ofs(outputFile, std::ios::binary);

    if (!ifs || !ofs) {
        // Check if file opening failed
        std::cerr << "Failed to open files." << std::endl;
        return false;
    }

    // Read input file into a vector<char>
    std::vector<char> buffer(std::istreambuf_iterator<char>(ifs), {});
    ifs.close();

    // Transposition
    std::reverse(buffer.begin(), buffer.end());

    // XOR decryption
    for (std::size_t i = 0; i < buffer.size(); ++i) {
        // Get the corresponding character from the decryption key
        char keyChar = key_deskrypt_[i % key_deskrypt_.size()];
        // XOR the buffer character with the key character
        buffer[i] = buffer[i] ^ keyChar;
    }

    // Write the decrypted buffer to the output file
    ofs.write(&buffer[0], buffer.size());
    ofs.close();

    std::cout << "Decryption completed successfully." << std::endl;
    return true;
}
