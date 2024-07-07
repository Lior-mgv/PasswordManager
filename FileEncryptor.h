#ifndef PASSWORDMANAGER_FILEENCRYPTOR_H
#define PASSWORDMANAGER_FILEENCRYPTOR_H


#include <string>

/**
* @brief Class representing a file encryptor.
* The FileEncryptor class provides encryption and decryption functionality for files.
* It contains functions to encrypt and decrypt data using a specified key.
*/

class FileEncryptor {
public:
    /**
    @brief Encrypts the provided data using the specified key.
    @param data The data to be encrypted.
    @param key The encryption key.
    @return The encrypted data as a string.
    */
    auto encrypt(const std::string& data, const std::string& key) -> std::string;
    /**
    @brief Decrypts the provided data using the specified key.
    @param data The data to be decrypted.
    @param key The decryption key.
    @return The decrypted data as a string.
    */
    auto decrypt(const std::string& data, const std::string& key) -> std::string;
    /**
    @brief Applies the XOR operation between the data and the key.
    @param data The data to be XORed.
    @param key The XOR key.
    @return The result of the XOR operation as a string.
    */
    std::string apply_xor(const std::string& data, const std::string& key);
};


#endif //PASSWORDMANAGER_FILEENCRYPTOR_H
