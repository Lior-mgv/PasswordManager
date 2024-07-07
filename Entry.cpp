#include "Entry.h"

Entry::Entry(const string &category, const string &name, const string &password, const string &login,
             const string &website) : category(category), name(name), password(password), login(login),
                                      website(website) {}

auto Entry::getFileString() const -> std::string {
    return category + "," + name + "," + password + "," + login + "," + website;
}

string Entry::getDisplayString() const {
    return "Category: " + category + "; Name: " + name + "; Password: " + password +
    (login.empty() ? "" : "; Login: " + login) +
    (website.empty() ? "" : "; Website: " + website);
}

const std::string & Entry::getName() const {
    return name;
}

auto Entry::getCategory() const -> std::string {
    return category;
}

const string &Entry::getPassword() const {
    return password;
}

const string &Entry::getLogin() const {
    return login;
}

const string &Entry::getWebsite() const {
    return website;
}

void Entry::setName(const std::string& name) {
    Entry::name = name;
}

void Entry::setCategory(const std::string &category) {
    Entry::category = category;
}

void Entry::setPassword(const std::string &password) {
    Entry::password = password;
}

void Entry::setLogin(const std::string &login) {
    Entry::login = login;
}

void Entry::setWebsite(const std::string &website) {
    Entry::website = website;
}

bool Entry::compareEntries(const Entry &a, const Entry &b, int param1, int param2) {
    switch (param1) {
        case 1 : {
            if(a.name != b.name){
                return a.name < b.name;
            }
            break;
        }
        case 2: {
            if(a.category != b.category){
                return a.category < b.category;
            }
            break;
        }
        case 3 : {
            if(a.login != b.login){
                return a.login < b.login;
            }
            break;
        }
        case 4 : {
            if(a.website != b.website){
                return a.website < b.website;
            }
            break;
        }
    }
    switch (param2) {
        case 1 : {
            if (a.name != b.name) {
                return a.name < b.name;
            }
            break;
        }
        case 2 : {
            if (a.category != b.category) {
                return a.category < b.category;
            }
            break;
        }
        case 3 : {
            if (a.login != b.login) {
                return a.login < b.login;
            }
            break;
        }
        case 4 : {
            if (a.website != b.website) {
                return a.website < b.website;
            }
            break;
        }
    }
    return false;
}
