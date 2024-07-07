#ifndef PASSWORDMANAGER_UI_H
#define PASSWORDMANAGER_UI_H
#include "PasswordList.h"
/**
* @brief Class representing the user interface of the PasswordManager program.
* The UI class provides a user interface for interacting with the PasswordManager program.
* It manages various operations such as adding, deleting, and editing password entries,
* as well as displaying options, listing entries, and performing searches and sorting.
*/

class UI {
private:
    /**
     * Pointer to the PasswordList object used by the application.
     * */
    PasswordList* passwordList;
    /**
    @brief Prints the available options to the console.
     */
    auto printOptions() -> void;
    /**
    @brief Handles adding new categories to the password list.
     */
    auto addCategory() -> void;
    /**
    @brief Handles adding new entries to the password list.
     */
    auto addEntry() -> void;
    /**
    @brief Handles deleting entries from the password list.*/
    auto deleteEntry() -> void;
    /**
    @brief Prompts the user to choose a category.
    @return The selected category as a string.
    */
    auto chooseCategory() -> std::string;
    /**
    @brief Prompts the user to choose a file containing passwords (either by choosing a file from the program directory
     or by providing the absolute path to a file).
    @return The file name as a string.
    */
    std::string getFileName() const;
    /**
    @brief Handles deleting categories from the password list.\
    */
    void deleteCategory();
    /**
    @brief Handles modifying existing entries. Name, category, password, login and website can be modified.
     */
    void editPassword();
    /**
    @brief Searches for entries that match specific parameters (name, login or website) in the password list
     and displays them.
    **/
    void searchPassword();
    /**
    @brief Prints a list of entries sorted by 2 different parameters. Possible parameters to choose from are name,
     category, login and website.
    */
    void sortPasswords();
    /**
    @brief Lists password entries in a specific category.
    @param cat The category to display.
    */
    void listInCategory(const std::string& cat);

    /**
    @brief Prompts the user for confirmation in yes/no format.
    @param message The confirmation message to display.
    @return True if the user confirms, false otherwise.
    */
    bool confirm(const string& message) const;
    /**
    @brief Handles generating random passwords. The user can choose the length of the password, also if capital letters
    and special symbols should be included.
    @return The generated password as a string.
    */
    std::string generatePassword();

public:
    /**
     *@brief Displays the user interface and starts the interaction with the PasswordManager program.
     **/
    auto show() -> void;
};

#endif //PASSWORDMANAGER_UI_H
