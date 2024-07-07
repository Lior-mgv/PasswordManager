#ifndef PASSWORDMANAGER_PASSWORDLIST_H
#define PASSWORDMANAGER_PASSWORDLIST_H

#include <string>
#include <vector>
#include <iostream>
#include "Entry.h"
#include <map>

using std::string, std::vector;

/**
* @class PasswordList
* @brief Class representing a list of password entries.
* The PasswordList class manages a collection of password entries.
* It provides functionality to read and write entries from/to a file,
* add and remove entries, organize entries by categories, retrieve entries based on categories,
* and manipulate entries within categories.
*/
class PasswordList {
    /** The file name associated with the password list.
    **/
    string fileName;
    /**
     *The password used to decrypt the password list file.
     */
    string password;
    /**
     * Map of category names to lists of Entry objects.
     */
    std::map<string, vector<Entry>> entriesMap;
    /**
    @brief Reads the password list from the associated file.
    */
    string read();
    /**
    @brief Writes the data to the associated file.
    */
    auto write(std::string data) -> void;
    /**
    @brief Splits a string into multiple substrings using the specified delimiter.
    @param str The string to be split.
    @param delimiter The delimiter used to split the string.
    @return A vector of substrings.
    */
    static vector<string> split(string& str, const string& delimiter);
    /**
    @brief Encrypts data stored in password list.
    @return A string representation of encrypted data.
    */
    string encryptData();
    /**
    @brief Decrypts the passed data and saves it in password list.
    @param data Data to decrypt
    */
    void decryptData(std::string data);
    /**
    @brief Gets current date and time, converts it to a string and ciphers it.
    @return A string representation of a timestamp.
    */
    string getTimestamp();
public:
    /**
     * @brief Constructs a PasswordList object with the specified file name and password.
     * @param fileName The file name associated with the password list.
     * @param password The password used to decrypt the password list file.
     */
    explicit PasswordList(const string &fileName, const string& password);
    /**
    @brief Retrieves the categories in the password list.
    @return A vector of category names.
    */
    auto getCategories() -> vector<string>;
    /**
    @brief Adds an entry to the password list.
    @param entry The entry to be added.
    */
    auto addEntry(const Entry& entry) -> void;
    /**
    @brief Removes an entry from the password list based on its category and index.
    @param category The category of the entry.
    @param index The index of the entry within its category.
    */
    auto removeEntry(const string& category, int index) -> void;
    /**
    @brief Removes an entry from the password list based on its category and iterator.
    @param category The category of the entry.
    @param iterator The iterator pointing to the entry in its category.
    */
    auto removeEntry(const string& category, const std::vector<Entry>::iterator& iterator) -> void;
    /**
    @brief Checks if a category exists in the password list.
    @param cat The category name to check.
    @return True if the category exists, false otherwise.
    */
    auto categoryExists(const string& cat) -> bool;
    /**
    @brief Adds a category to the password list.
    @param cat The category name to add.
    */
    auto addCategory(const string& cat) -> void;
    /**
    @brief Checks if the password list is empty.
    @return True if the password list is empty, false otherwise.
    */
    auto empty() -> bool;
    /**
    @brief Retrieves all the password entries in the password list.
    @return A vector of all password entries.
    */
    vector<Entry> getAllEntries();
    /**
    @brief Removes a category from the password list.
    @param category The category name to remove.
    */
    void removeCategory(const string& category);
    /**
    @brief Moves an entry to a new category.
    @param newCat The new category for the entry.
    @param entry The entry to be moved.
    */
    void moveEntry(string& newCat, Entry& entry);
    /**
    @brief Retrieves the entries in a specific category.
    @param cat The category name.
    @return A reference to the vector of entries in the category.
    */
    vector<Entry>& getEntriesInCategory(string cat);
    /**
    @brief Saves data from password list to a file.
    */
    void saveData();
    /**
    @brief Checks if an entry with the given name exists in a given category.
    @param name The name of the entry to check.
    @param cat The category in which to search for the entry.
    @return True if the entry exists in the category, false otherwise.
    */
    bool entryExists(const string& name, const string& cat);
    /**
    @brief Checks if a given category is empty.
    @return True if the category is empty, false otherwise.
    */
    bool categoryIsEmpty(const string& cat);
};


#endif //PASSWORDMANAGER_PASSWORDLIST_H
