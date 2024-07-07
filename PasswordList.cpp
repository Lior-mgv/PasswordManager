#include "PasswordList.h"
#include "FileEncryptor.h"
#include <fstream>
#include <chrono>
#include "DecryptionException.h"

using std::vector, std::string, std::cout, std::cin;

PasswordList::PasswordList(const string &fileName, const string &password) : fileName(fileName), password(password) {
    auto file = std::ifstream(fileName, std::ios::binary);
    if(file.is_open()) {
        string content = read();
        write(content);
        try{
            decryptData(read());
        } catch(DecryptionException& e){
            throw DecryptionException();
        }
    }
}

auto PasswordList::split(string& str, const string& delimiter) -> vector<string> {
    vector<string> result;
    string part;
    int pos;
    while((pos = str.find(delimiter)) != string::npos){
        part = str.substr(0,pos);
        result.push_back(part);
        str.erase(0, pos+delimiter.length());
    }
    result.push_back(str);
    return result;
}

string PasswordList::read() {
    auto file = std::ifstream(fileName, std::ios::binary);
    if (file.is_open()) {
        std::string content((std::istreambuf_iterator<char>(file)),
                            (std::istreambuf_iterator<char>()));
        if(!content.empty()) content.erase(content.size() - 12);
        return content;
    }
    return "";
}

auto PasswordList::write(std::string data) -> void {
    std::ofstream os = std::ofstream(fileName, std::ios::binary);
    data += getTimestamp();
    os << data;
}

void PasswordList::saveData() {
    write(encryptData());
}

auto PasswordList::getCategories() -> vector<string> {
    vector<string> categories;
    for (const auto& pair : entriesMap) {
        categories.push_back(pair.first);
    }
    return categories;
}

auto PasswordList::addEntry(const Entry& entry) -> void {
    auto cat = entry.getCategory();
    if(!entriesMap.contains(cat)){
        addCategory(cat);
    }
    entriesMap[cat].push_back(entry);
}

auto PasswordList::categoryExists(const string &cat) -> bool {
    return entriesMap.contains(cat);
}

auto PasswordList::addCategory(const string &cat) -> void {
    entriesMap.insert(std::pair<string, vector<Entry>>(cat,vector<Entry>()));
}

auto PasswordList::empty() -> bool {
    if(entriesMap.empty()) return true;
    bool empty = true;
    for(const auto& pair : entriesMap){
        if(!pair.second.empty()) empty = false;
    }
    return empty;
}

auto PasswordList::removeEntry(const string& category, int index) -> void {
    entriesMap[category].erase(entriesMap[category].begin() + index);
}

auto PasswordList::removeEntry(const string &category, const std::vector<Entry>::iterator &iterator) -> void {
    entriesMap[category].erase(iterator);
}

void PasswordList::removeCategory(const string& category) {
    entriesMap.erase(category);
}

void PasswordList::moveEntry(string &newCat, Entry &entry) {
    auto& vectorCopy = entriesMap[entry.getCategory()];
    removeEntry(entry.getCategory(),std::find(vectorCopy.begin(),vectorCopy.end(), entry));
    entry.setCategory(newCat);
    addEntry(entry);
}

vector<Entry> &PasswordList::getEntriesInCategory(string cat) {
    return entriesMap[cat];
}

vector<Entry> PasswordList::getAllEntries() {
    vector<Entry> entries;
    for (const auto& pair : entriesMap) {
        for (auto entry : pair.second) {
            entries.push_back(entry);
        }
    }
    return entries;
}

string PasswordList::encryptData() {
    auto fe = FileEncryptor();
    string content;
    for (const auto &pair: entriesMap) {
        for (int i = 0; i < pair.second.size(); ++i) {
            content += pair.second.at(i).getFileString() + "\n";
        }
    }
    if (!content.empty()) {
        content.pop_back();
    }
    content = fe.encrypt(content, password);
    return content;
}

void PasswordList::decryptData(std::string data) {
    auto fe = FileEncryptor();
    if(!data.empty()) {
        data = fe.decrypt(data, password);
        auto entries = split(data, "\n");
        for (auto entry: entries) {
            auto parts = split(entry, ",");
            if(parts.size() != 5) throw DecryptionException();
            auto newEntry = Entry(parts.at(0), parts.at(1), parts.at(2),
                                  parts.at(3), parts.at(4));
            addEntry(newEntry);
        }
    }
}

string PasswordList::getTimestamp() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&currentTime);
    std::string timestamp = std::to_string(timeInfo->tm_year - 100) +
                            (timeInfo->tm_hour < 10 ? "0" : "") + std::to_string(timeInfo->tm_hour) +
                            (timeInfo->tm_mon + 1 < 10 ? "0" : "") + std::to_string(timeInfo->tm_mon + 1) +
                            (timeInfo->tm_min < 10 ? "0" : "") + std::to_string(timeInfo->tm_min) +
                            (timeInfo->tm_mday < 10 ? "0" : "") + std::to_string(timeInfo->tm_mday) +
                            (timeInfo->tm_sec < 10 ? "0" : "") + std::to_string(timeInfo->tm_sec);
    return timestamp;
}

bool PasswordList::entryExists(const string& name, const string& cat) {
    auto entry = Entry(cat, name, "", "", "");
    for(auto e : getAllEntries()){
        if(e == entry) return true;
    }
    return false;
}

bool PasswordList::categoryIsEmpty(const string &cat) {
    return getEntriesInCategory(cat).empty();
}

