#ifndef PASSWORDMANAGER_ENTRY_H
#define PASSWORDMANAGER_ENTRY_H

#include <string>
#include <vector>

using std::string;
/**
* @brief Class representing a password entry.
* The Entry class represents a password entry and contains attributes such as the category, name, password, login, and website.
* It provides methods to retrieve and modify these attributes.
* The class also defines comparison functions for sorting and equality checks.
*/
class Entry {
    /**
     * The name of the entry
     */
    string name;
    /**
     * The password of the entry
     */
    string password;
    /**
     * The category of the entry
     */
    string category;
    /**
     * The login of the entry
     */
    string login;
    /**
     * The website of the entry
     */
    string website;
public:
    /**
    @brief Constructs an Entry object with the specified attributes.
    @param category The category of the entry.
    @param name The name of the entry.
    @param password The password of the entry.
    @param login The login associated with the entry.
    @param website The website associated with the entry.
    */
    Entry(const string &category, const string &name, const string &password, const string &login,
          const string &website);
    /**
    @brief Retrieves a formatted string representation of the entry with parameters separated by comas,
     intended to be encrypted and written to a file.
    @return A string representing the entry.
    */
    auto getFileString() const -> string;
    /**
    @brief Retrieves a formatted string representation of the entry in user readable format
     intended to be displayed on screen.
    @return A string representing the entry.
    */
    string getDisplayString() const;
    /**
    @brief Retrieves the category of the entry.
    @return The category of the entry.
    */
    auto getCategory() const ->  string;
    /**
    @brief Retrieves the name of the entry.
    @return The name of the entry.
    */
    const string &getName() const;
    /**
    @brief Retrieves the password of the entry.
    @return The password of the entry.
    */
    const string &getPassword() const;
    /**
    @brief Retrieves the login associated with the entry.
    @return The login associated with the entry.
    */
    const string &getLogin() const;
    /**
    @brief Retrieves the website associated with the entry.
    @return The website associated with the entry.
    */
    const string &getWebsite() const;
    /**
    @brief Sets the name of the entry.
    @param newName The new name to set.
    */
    void setName(const string& newName);
    /**
    @brief Sets the category of the entry.
    @param cat The new category to set.
    */
    void setCategory(const string &cat);
    /**
    @brief Sets the password of the entry.
    @param password The new password to set.
    */
    void setPassword(const string &password);
    /**
    @brief Sets the login associated with the entry.
    @param login The new login to set.
    */
    void setLogin(const string &login);
    /**
    @brief Sets the website associated with the entry.
    @param website The new website to set.
    */
    void setWebsite(const string &website);
    /**
    @brief Checks if this entry is equal to another entry.
    @param other The other entry to compare.
    @return True if the entries are equal, false otherwise.
    */
    bool operator==(const Entry& other) const {
        return this->name == other.name && this->category == other.category;
    }
    /**
    @brief Compares two entries based on specified parameters.
    @param a The first entry to compare.
    @param b The second entry to compare.
    @param param1 The first parameter to compare (1 for name, 2 for category, 3 for login, 4 for password).
    @param param2 The second parameter to compare (1 for name, 2 for category, 3 for login, 4 for password).
    @return True if the first entry is less than the second entry, false otherwise.
*/
    static bool compareEntries(const Entry& a, const Entry& b, int param1, int param2);
};

#endif //PASSWORDMANAGER_ENTRY_H
