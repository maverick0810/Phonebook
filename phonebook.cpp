#include <iostream>
#include <vector>
#include <algorithm>

// Contact class definition
class Contact {
public:
    std::string name;
    std::string phone;
    std::string address;
    std::string category;
    bool privateEntry;

    // Constructor to initialize contact attributes
    Contact(const std::string& n, const std::string& p, const std::string& a, const std::string& c, bool privacy)
        : name(n), phone(p), address(a), category(c), privateEntry(privacy) {}
};

// Phonebook class definition
class Phonebook {
private:
    std::vector<Contact> contacts;

public:
    // Function to add a new contact to the phonebook
    void addContact(const Contact& contact) {
        contacts.push_back(contact);
        std::cout << "Contact added successfully.\n";
    }

    // Function to search for a contact based on name or phone number
    void searchContact(const std::string& searchKey) {
        bool found = false;

        for (const auto& contact : contacts) {
            if (!contact.privateEntry && (contact.name.find(searchKey) != std::string::npos || contact.phone.find(searchKey) != std::string::npos)) {
                // Display contact details
                found = true;
            }
        }

        if (!found) {
            std::cout << "Contact not found.\n";
        }
    }

    // Function to update contact details
    void updateContact(const std::string& name, const std::string& newPhone, const std::string& newAddress, const std::string& newCategory) {
        auto it = std::find_if(contacts.begin(), contacts.end(), [&](const Contact& c) { return c.name == name; });

        if (it != contacts.end()) {
            it->phone = newPhone;
            it->address = newAddress;
            it->category = newCategory;
            std::cout << "Contact updated successfully.\n";
        } else {
            std::cout << "Contact not found.\n";
        }
    }

    // Additional functions for managing contacts

};

// Main function
int main() {
    Phonebook phonebook;

    int choice;
    do {
        // Display menu
        std::cout << "\nPhonebook Directory\n";
        std::cout << "1. Add Contact\n";
        std::cout << "2. Search Contact\n";
        std::cout << "3. Update Contact\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";

        // Get user choice
        std::cin >> choice;
        std::cin.ignore(); // Consume the newline character left in the buffer

        switch (choice) {
            case 1: {
                // Adding a new contact
                std::string name, phone, address, category;
                bool privacy;

                std::cout << "Enter Name: ";
                std::getline(std::cin, name);

                std::cout << "Enter Phone: ";
                std::getline(std::cin, phone);

                std::cout << "Enter Address: ";
                std::getline(std::cin, address);

                std::cout << "Enter Category: ";
                std::getline(std::cin, category);

                std::cout << "Is this a private entry? (1 for yes, 0 for no): ";
                std::cin >> privacy;
                std::cin.ignore(); // Consume the newline character left in the buffer

                phonebook.addContact(Contact(name, phone, address, category, privacy));
                break;
            }
            case 2: {
                // Searching for a contact
                std::string searchKey;
                std::cout << "Search for a contact (name or phone number): ";
                std::getline(std::cin, searchKey);
                phonebook.searchContact(searchKey);
                break;
            }
            case 3: {
                // Updating contact details
                std::string name, newPhone, newAddress, newCategory;

                std::cout << "Enter the name of the contact to update: ";
                std::getline(std::cin, name);

                std::cout << "Enter the new phone number: ";
                std::getline(std::cin, newPhone);

                std::cout << "Enter the new address: ";
                std::getline(std::cin, newAddress);

                std::cout << "Enter the new category: ";
                std::getline(std::cin, newCategory);

                phonebook.updateContact(name, newPhone, newAddress, newCategory);
                break;
            }
            case 4:
                // Exit the program
                std::cout << "Exiting the Phonebook Directory. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}