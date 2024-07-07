#include <iostream>
#include <fstream>
#include "UI.h"
#include "FileEncryptor.h"
#include <random>
#include <filesystem>
#include "DecryptionException.h"

using std::string, std::cout, std::cin;


auto UI::show() -> void {
    string file_name = getFileName();
    string password;
    while (true) {
        try {
            cout << "Enter the password: ";
            cin >> password;
            passwordList = new PasswordList(file_name, password);
            break;
        } catch (DecryptionException e) {
            cout << e.what();
        }
    }
    while (true) {
        cout << "\n";
        printOptions();
        int input;
        cin >> input;
        switch (input) {
            case 1 : {
                passwordList->saveData();
                break;
            }
            case 2 : {
                addEntry();
                passwordList->saveData();
                continue;
            }
            case 3 : {
                deleteEntry();
                passwordList->saveData();
                continue;
            }
            case 4 : {
                addCategory();
                passwordList->saveData();
                continue;
            }
            case 5 : {
                deleteCategory();
                passwordList->saveData();
                continue;
            }
            case 6 : {
                editPassword();
                passwordList->saveData();
                continue;
            }
            case 7 : {
                searchPassword();
                continue;
            }
            case 8 : {
                sortPasswords();
                continue;
            }
        }
        break;
    }
}

string UI::getFileName() const {
    string file_name;
    std::ifstream file;
    if (!std::filesystem::exists("Files")) {
        std::filesystem::create_directory("Files");
    }
    int input;
    while (true) {
        cout << "1.Choose from the program's folder.\n2.Provide absolute path.\n3.Create new file.\n";
        cin >> input;
        switch (input) {
            case 1: {
                int count = 1;
                vector<string> files;
                if (std::filesystem::is_empty("Files")){
                    cout << "No files found.\n";
                    continue;
                }
                for (const auto &entry: std::filesystem::directory_iterator("Files")) {
                    std::cout << count++ << ". " << relative(entry.path()) << std::endl;
                    files.push_back(entry.path().string());
                }
                while (true) {
                    cin >> input;
                    if (input >= 1 && input <= files.size()) break;
                    cout << "Enter a valid number";
                }
                file_name = files.at(input-1);
                break;
            }
            case 2 : {
                cin.ignore();
                while(true) {
                    cout << "Provide an absolute path: ";
                    string line;
                    std::getline(std::cin, line);
                    file_name = line;
                    file = std::ifstream(file_name, std::ios::binary);
                    if(file.is_open()) return file_name;
                    cout << "Specified file does not exist.\n";
                }
            }
            case 3 : {
                while (true) {
                    cout << "Enter file name: ";
                    string name;
                    cin >> name;
                    std::ofstream newFile("Files\\" + name + ".txt");
                    if(newFile.is_open()) return "Files\\" + name + ".txt";
                    cout << "Failed to create the file.";
                }
            }
            default : {
                cout << "Enter a valid number\n";
                continue;
            }
        }
        break;
    }
    return file_name;
}

auto UI::addEntry() -> void {
    do {
        cout << "Enter the category: ";
        string category;
        cin >> category;
        if (!passwordList->categoryExists(category)) {
            if (confirm("There is no such category. Do you wish to add it?")) {
                passwordList->addCategory(category);
            } else if (confirm("Do you wish to choose from existing categories?")) {
                category = chooseCategory();
            } else return;
        }
        string name;
        while (true) {
            cout << "Enter the name: ";
            cin >> name;
            if(!passwordList->entryExists(name, category)) break;
            cout << "Entry with such name already exists in this category.\n";
        }
        cin.ignore();
        cout << "Enter the password (ENTER to generate automatically): ";
        string password;
        std::getline(cin, password);
        if (password.empty()) {
            password = generatePassword();
            cin.ignore();
        }
        cout << "Enter the login (ENTER to skip): ";
        string login;
        std::getline(cin, login);
        cout << "Enter the website (ENTER to skip): ";
        string website;
        std::getline(cin, website);
        passwordList->addEntry(Entry(category, name, password, login, website));
    } while(confirm("Add another entry?"));
}

auto UI::addCategory() -> void {
    do {
        string cat;
        auto categories = passwordList->getCategories();
        do {
            cout << "Enter the name of the category: ";
            cin >> cat;
            if (passwordList->categoryExists(cat)) {
                cout << "Such category already exists.\n";
            }
        } while (passwordList->categoryExists(cat));
        passwordList->addCategory(cat);
    } while (confirm("Add another category?"));
}

auto UI::printOptions() -> void {
    int count = 1;
    cout << count++ << ". Save and exit\n" << count++ << ". Add password\n" << count++
    << ". Delete password\n" << count++ << ". Add category\n" << count++ << ". Delete category\n" <<
    count++ << ". Change password\n" << count++ << ". Search passwords\n" << count++ << ". Sort passwords\n";
}

auto UI::chooseCategory() -> std::string {
    int count = 1;
    cout << "Choose the category: \n";
    auto categories = passwordList->getCategories();
    for (auto cat : categories) {
        cout << count << ". " << cat << "\n";
        count++;
    }
    string category;
    int input;
    while(true){
        cin >> input;
        if(input >= 1 && input <= categories.size()){
            return categories[input-1];
        }
        cout << "Enter a valid number.\n Choose the category:\n";
    }
}

auto UI::deleteEntry() -> void {
    do {
        while (true) {
            std::string category = chooseCategory();
            if(passwordList->categoryIsEmpty(category)){
                cout << "Chosen category is empty.";
                continue;
            }
            listInCategory(category);
            int input;
            cin >> input;
            auto entries = passwordList->getEntriesInCategory(category);
            if (input >= 1 && input <= entries.size()) {
                if (confirm("Are you sure you want to delete " + entries[input - 1].getName() + "?")) {
                    passwordList->removeEntry(category, input - 1);
                    cout << "Password successfully deleted.\n";
                }
                break;
            }
            cout << "Enter a valid number.\n";
        }
    } while (confirm("Delete another entry?"));
}

bool UI::confirm(const std::string& message) const {
    cout << message << "(y/n)\n";
    std::string answer;
    cin >> answer;
    return answer == "y";
}

void UI::deleteCategory() {
    auto cat = chooseCategory();
    passwordList->removeCategory(cat);
}

void UI::editPassword() {
    string category;
    while (true) {
        category = chooseCategory();
        if (!passwordList->categoryIsEmpty(category)) {
            break;
        }
        cout << "Chosen category is empty.";
    }
    listInCategory(category);
    auto & entries = passwordList->getEntriesInCategory(category);
    while (true) {
        int index;
        cin >> index;
        if(index < 1 || index > entries.size()){
            cout << "Enter a valid number\n";
            continue;
        }
        cout << "1.Change name\n2.Change category\n3.Change password\n4.Change login\n5.Change website\n";
        int option;
        cin >> option;
        std::string newValue;
        Entry & entry = entries[index-1];
        switch (option) {
            case 1 : {
                while (true) {
                    cout << "Enter new name: ";
                    cin >> newValue;
                    if(!passwordList->entryExists(newValue, entry.getCategory())){
                        entry.setName(newValue);
                        break;
                    }
                    cout << "Entry with such name already exists in this category.\n";
                }
                break;
            }
            case 2 : {
                cout << "Enter new category: ";
                cin >> newValue;
                if(!passwordList->categoryExists(newValue) &&
                    !confirm("There is no such category. Do you wish to add it?")) {
                    return;
                }
                passwordList->moveEntry(newValue, entry);
                break;
            }
            case 3 : {
                cout << "Enter new password: ";
                cin >> newValue;
                entry.setPassword(newValue);
                break;
            }
            case 4 : {
                cout << "Enter new login: ";
                cin >> newValue;
                entry.setLogin(newValue);
                break;
            }
            case 5 : {
                cout << "Enter new website: ";
                cin >> newValue;
                entry.setWebsite(newValue);
                break;
            }
            default : {
                cout << "Invalid option.\n";
                continue;
            }
        }
        cout << "Information successfully changed.\n\n";
        break;
    }
}

void UI::listInCategory(const string &cat) {
    int count = 1;
    auto entries = passwordList->getEntriesInCategory(cat);
    for(auto entry : entries){
        cout << count << ". " << entry.getDisplayString() << "\n";
        count++;
    }
}

void UI::searchPassword() {
    auto cat = chooseCategory();
    while (true) {
        cout << "1.Search by name\n2.Search by login\n3.Search by website\n";
        int option;
        cin >> option;
        std::string val;
        bool found = false;
        switch (option) {
            case 1 : {
                cout << "Enter the name: ";
                cin >> val;
                for (auto entry : passwordList->getEntriesInCategory(cat)) {
                    if(entry.getName() == val){
                        cout << entry.getDisplayString() << "\n";
                        found = true;
                    }
                }
                break;
            }
            case 2 : {
                cout << "Enter the login: ";
                cin >> val;
                for (auto entry : passwordList->getEntriesInCategory(cat)) {
                    if(entry.getLogin() == val){
                        cout << entry.getDisplayString() << "\n";
                        found = true;
                    }
                }
                break;
            }
            case 3 : {
                cout << "Enter the website: ";
                cin >> val;
                for (auto entry : passwordList->getEntriesInCategory(cat)) {
                    if(entry.getWebsite() == val){
                        cout << entry.getDisplayString() << "\n";
                        found = true;
                    }
                }
                break;
            }
            default : {
                cout << "Invalid option.\n\n";
                continue;
            }
        }
        if(!found) cout << "No records found.\n\n";
        if(!confirm("Search by other parameters?")) break;
    }
}
string UI::generatePassword() {
    int number;
    while (true) {
        cout << "Enter the number of characters(5-100): ";
        cin >> number;
        if(number >= 5 && number <= 100) break;
        cout << "The number has to be between 5 and 50.\n";
    }
    vector<string> sets = {"abcdefghijklmnopqrstuvwxyz", "0123456789"};
    if(confirm("Include uppercase letters?")) sets.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    if(confirm("Include special symbols?")) sets.push_back("!@#$%&");
    string password = std::string();
    while (true) {
        password = "";
        std::random_device rd;
        std::default_random_engine defEngine(rd());
        for (int i = 0; i < number; ++i) {
            string set = sets[std::uniform_int_distribution<int>(0, sets.size() - 1)(defEngine)];
            password += set.at(std::uniform_int_distribution<int>(0, set.size() - 1)(defEngine));
        }
        cout << password << "\n";
        if (confirm("Generate another password?")) continue;
        else break;
    }
    return password;
}

void UI::sortPasswords() {
    while (true) {
        int parameters[2];
        for (int i = 0; i < 2; i++) {
            cout << (i == 0 ? "Pick first parameter: " : "Pick second parameter: ") << "\n";
            cout << "1. Name\n2. Category\n3. Login\n4. Website\n";
            int input;
            while (true) {
                cin >> input;
                if (input >= 1 && input <= 4) break;
                cout << "Enter a valid number.\n";
            }
            parameters[i] = input;
        }
        cout << "\n";
        vector<Entry> entries(passwordList->getAllEntries());
        std::sort(entries.begin(), entries.end(), [&](const Entry &entry1, const Entry &entry2) -> bool {
            return Entry::compareEntries(entry1, entry2, parameters[0], parameters[1]);
        });
        for (int i = 0; i < entries.size(); ++i) {
            cout << i + 1 << ". " << entries[i].getDisplayString() << "\n";
        }
        cout << "\n";
        if(!confirm("Sort by different parameters?")) break;
    }
}



