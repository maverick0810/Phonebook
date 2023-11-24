#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>    

struct Contact {
    std::string name;
    std::string phoneNumber;
    std::string address;
};

class User {
public:
    User() = default;

    User(std::string username) : username(std::move(username)) {}

    bool addContact(const Contact& contact) {
       
        if (!isValidPhoneNumber(contact.phoneNumber)) {
            std::cout << "Invalid phone number. Phone number must have exactly 10 digits.\n";
            return false;
        }

      
            for (const auto& pair : contacts) {
                const Contact& existingContact = pair.second;
                if (existingContact.name == contact.name &&
                    existingContact.phoneNumber == contact.phoneNumber &&
                    existingContact.address == contact.address) {
                    std::cout << "Contact with the same attributes already exists.\n";
                    return false;
                }
            }

        contacts[contact.phoneNumber] = contact;
        uniquePhoneNumbers.insert(contact.phoneNumber);
        std::cout << "Contact added successfully.\n";
        return true;
    }

    void viewContacts() const {
        if (contacts.empty()) {
            std::cout << "No contacts available.\n";
            return;
        }

        for (const auto& pair : contacts) {
            displayContact(pair.second);
        }
    }

    void viewUniqueContacts() const {
        if (uniquePhoneNumbers.empty()) {
            std::cout << "No unique contacts available.\n";
            return;
        }

        std::cout << "Unique Contacts (Phone Numbers):\n";
        for (const auto& phoneNumber : uniquePhoneNumbers) {
            std::cout << phoneNumber << "\n";
        }
    }

    void viewContactByPhoneNumber(const std::string& phoneNumber) const {
        auto it = contacts.find(phoneNumber);
        if (it != contacts.end()) {
            displayContact(it->second);
        } else {
            std::cout << "Contact not found.\n";
        }
    }

    void viewContactsByName(const std::string& name) const {
        bool found = false;
        for (const auto& pair : contacts) {
            const Contact& contact = pair.second;
            if (contact.name == name) {
                displayContact(contact);
                found = true;
            }
        }

        if (!found) {
            std::cout << "No contacts found with the given name.\n";
        }
    }

    void modifyContact(const std::string& phoneNumber, const Contact& modifiedContact) {
        auto it = contacts.find(phoneNumber);
        if (it != contacts.end()) {
            it->second = modifiedContact;
            std::cout << "Contact modified successfully.\n";
        } else {
            std::cout << "Contact not found.\n";
        }
    }

    void deleteContact(const std::string& phoneNumber) {
        auto it = contacts.find(phoneNumber);
        if (it != contacts.end()) {
            contacts.erase(it);
            uniquePhoneNumbers.erase(phoneNumber);
            std::cout << "Contact deleted successfully.\n";
        } else {
            std::cout << "Contact not found.\n";
        }   
    }

    std::string getUsername() const {
        return username;
    }

private:
    std::string username;
    std::unordered_map<std::string, Contact> contacts;
    std::unordered_set<std::string> uniquePhoneNumbers;

    void displayContact(const Contact& contact) const {
        std::cout << "Name: " << contact.name << "\n";
        std::cout << "Phone Number: " << contact.phoneNumber << "\n";
        std::cout << "Address: " << contact.address << "\n\n";
    }

    static bool isValidPhoneNumber(const std::string& phoneNumber) {
        return phoneNumber.length() == 10 && std::all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit);
    }
};

class Administrator {
public:
    void viewAllContacts(const std::unordered_map<std::string, User>& users) const {
        if (users.empty()) {
            std::cout << "No users available.\n";
            return;
        }

        for (const auto& pair : users) {
            std::cout << "User: " << pair.first << "\n";
            pair.second.viewContacts();
        }
    }
};

void printMenu() {
    std::cout << "\n1. Add Contact\n"
              << "2. View Contacts\n"
              << "3. View Unique Contacts\n"
              << "4. View Contact by Phone Number\n"
              << "5. View Contacts by Name\n"
              << "6. Modify Contact\n"
              << "7. Delete Contact\n"
              << "8. View All Contacts (Admin)\n"
              << "9. Exit\n";
}

int main() {
    std::unordered_map<std::string, User> users;
    Administrator admin;

    while (true) {
        std::cout << "\nEnter username or type 'admin' for admin access: ";
        std::string username;
        std::cin >> username;

        if (username == "admin") {
            std::cout << "\nAdmin View:\n";
            admin.viewAllContacts(users);
            continue;
        }

        auto userIt = users.find(username);
        User* currentUser = nullptr;

        if (userIt == users.end()) {
            users[username] = User(username);
            currentUser = &users[username];
        } else {
            currentUser = &userIt->second;
        }

        printMenu();

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Contact newContact;
                std::cout << "Enter Name: ";
                std::cin.ignore(); 
                std::getline(std::cin, newContact.name);
                std::cout << "Enter Phone Number: ";
                std::cin >> newContact.phoneNumber;
                std::cout << "Enter Address: ";
                std::cin.ignore();
                std::getline(std::cin, newContact.address);

                if (!currentUser->addContact(newContact)) {
                    
                    continue;
                }
                break;
            }
            case 2:
                currentUser->viewContacts();
                break;
            case 3:
                currentUser->viewUniqueContacts();
                break;
            case 4: {
                std::string phoneNumber;
                std::cout << "Enter Phone Number to View: ";
                std::cin >> phoneNumber;
                currentUser->viewContactByPhoneNumber(phoneNumber);
                break;
            }
            case 5: {
                std::string name;
                std::cout << "Enter Name to View Contacts: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                currentUser->viewContactsByName(name);
                break;
            }
            case 6: {
                std::string phoneNumber;
                std::cout << "Enter Phone Number to Modify: ";
                std::cin >> phoneNumber;

                Contact modifiedContact;
                std::cout << "Enter Modified Name: ";
                std::cin.ignore();
                std::getline(std::cin, modifiedContact.name);
                std::cout << "Enter Modified Phone Number: ";
                std::cin >> modifiedContact.phoneNumber;
                std::cout << "Enter Modified Address: ";
                std::cin.ignore();
                std::getline(std::cin, modifiedContact.address);

                currentUser->modifyContact(phoneNumber, modifiedContact);
                break;
            }
            case 7: {
                std::string phoneNumber;
                std::cout << "Enter Phone Number to Delete: ";
                std::cin >> phoneNumber;

                currentUser->deleteContact(phoneNumber);
                break;
            }
            case 8:
               
                break;
            case 9:
                std::cout << "Exiting the program.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
