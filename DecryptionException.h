#ifndef PASSWORDMANAGER_DECRYPTIONEXCEPTION_H
#define PASSWORDMANAGER_DECRYPTIONEXCEPTION_H


#include <exception>
#include <string>

/**
@brief Class representing an exception that occurs during decryption.
*/
class DecryptionException : public std::exception {
private:
    /**
     * The message to display.
     */
    std::string message;

public:
    /**
    * @brief Constructs a DecryptionException object with a default error message.
    */
    DecryptionException()
            : message("Decryption error occurred.\n") {}
    /**
    * @brief Retrieves the error message associated with the exception.
    * @return The error message.
    */
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //PASSWORDMANAGER_DECRYPTIONEXCEPTION_H
