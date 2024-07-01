#ifndef LinkedList_hpp
#define LinkedList_hpp
#include "Node.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
enum errorCode {success, fail};

template <class listEntry>
class LinkedList {
public:
    // Constructors
    LinkedList();
    ~LinkedList();
    // Functions
    errorCode addSubscriber(const listEntry &newUser);
    errorCode removePhoneNumber(const string &surname, const string &name, const string &phoneNumber);
    errorCode addPhoneNumber(const string &surname, const string &name, const string &additionalPhoneNumber);
    void displayPhoneNumbers(const string &surname, const string &name) const;
    errorCode deleteSubscriber(const string &surname, const string &name);
    void displaySortedDirectory() const;
    void saveToFile(const string &fileName) const;
    void loadFromFile(const string &fileName);
private:
    // Data fields
    Node<listEntry> *head;
};

// Definitions

// Constructor
template <class listEntry>
LinkedList<listEntry>::LinkedList() : head(nullptr) {}

// Destructor
template <class listEntry>
LinkedList<listEntry>::~LinkedList() {
    Node<listEntry> *current = head;
    while (current) {
        Node<listEntry> *next = current->next;
        delete current;
        current = next;
    }
}

// Add new subscriber function
template <class listEntry>
errorCode LinkedList<listEntry>::addSubscriber(const listEntry &newUser) {
    Node<listEntry> *newNode = new Node(newUser);
    if (newNode == nullptr) {
        cout << "Not enough memory. Operation failed." << endl;
        return fail;
    }
    if (!head || (newNode->data.surname + newNode->data.name) < (head->data.surname + head->data.name)) {
        newNode->next = head;
        head = newNode;
        cout << "New subscriber added." << endl;
        return success;
    }
    else {
        Node<listEntry> *current = head;
        while (current->next && (newNode->data.surname + newNode->data.name) > (current->next->data.surname + current->next->data.name)) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        cout << "New subscriber added." << endl;
        return success;
    }
}

// Remove a phone number from a subscriber function
template <class listEntry>
errorCode LinkedList<listEntry>::removePhoneNumber(const string &surname, const string &name, const string &phoneNumberToRemove) {
    Node<listEntry> *current = head;
    Node<listEntry> *previous = nullptr;

    while (current && (current->data.surname != surname || current->data.name != name)) {
        previous = current;
        current = current->next;
    }

    if (current) {
        // Subscriber found
        string currentPhoneNumber = current->data.phoneNumber;
        int pos = currentPhoneNumber.find(phoneNumberToRemove);

        if (pos != -1) {
            // Remove the requested number from the string
            currentPhoneNumber.erase(pos, phoneNumberToRemove.length());

            // Remove leading spaces and commas from the string
            int leadingSpaces = currentPhoneNumber.find_first_not_of(" ,");
            if (leadingSpaces != -1) {
                currentPhoneNumber.erase(0, leadingSpaces);
            }

            // Remove trailing spaces and commas from the string
            int trailingSpaces = currentPhoneNumber.find_last_not_of(" ,");
            if (trailingSpaces != -1) {
                currentPhoneNumber.erase(trailingSpaces + 1);
            }

            // Pass the new string back to the phone number
            current->data.phoneNumber = currentPhoneNumber;

            // Remove the user if no phone numbers are left
            if (currentPhoneNumber.empty()) {
                if (previous) {
                    previous->next = current->next;
                } else {
                    head = current->next;
                }
                delete current;
            }
            cout << "Phone number removed successfully." << endl;
            return success;
        } 
        else {
            cout << "Phone number not found." << endl;
            return fail;
        }
    } 
    else {
        cout << "Subscriber not found." << endl;
        return fail;
    }
}


// Add a phone number to a subscriber function
template <class listEntry>
errorCode LinkedList<listEntry>::addPhoneNumber(const string &surname, const string &name, const string &additionalPhoneNumber) {
    Node<listEntry> *current = head;
    
    while (current && (current->data.surname != surname || current->data.name != name)) {
        current = current->next;
    }
    
    if (current) {
        // Subscriber found
        // Remove leading spaces before adding the new phone number
        string currentPhoneNumber = current->data.phoneNumber;
        int pos = currentPhoneNumber.find_first_not_of(' ');
        if (pos != -1) {
            currentPhoneNumber.erase(0, pos);
        }

        // Add the new phone number
        current->data.phoneNumber += ", " + additionalPhoneNumber;
        cout << "Phone number added successfully." << endl;
        return success;
    }
    else {
        cout << "Subscriber not found." << endl;
        return fail;
    }
}

// Function to display a subscriber's phone numbers
template <class listEntry>
void LinkedList<listEntry>::displayPhoneNumbers(const string &surname, const string &name) const {
    Node<listEntry> *current = head;

    while (current && (current->data.surname != surname || current->data.name != name)) {
        current = current->next;
    }
    
    if (current) {
        cout << "Phone numbers for " << surname << ", " << name << ":\n";
        while (current && current->data.surname == surname && current->data.name == name) {
            cout << current->data.phoneNumber << "\n";
            current = current->next;
        }
    }
    else {
        cout << "Subscriber not found." << endl;
    }
}

// Delete a subscriber function
template <class listEntry>
errorCode LinkedList<listEntry>::deleteSubscriber(const string &surname, const string &name) {
    Node<listEntry> *current = head;
    Node<listEntry> *previous = nullptr;
    
    while (current && (current->data.surname != surname || current->data.name != name)) {
        previous = current;
        current = current->next;
    }
    
    if (current) {
        if (previous) {
            previous->next = current->next;
        }
        else {
            head = current->next;
        }
        delete current;
        cout << "Subscriber deleted." << endl;
        return success;
    }
    else {
        cout << "Subscriber not found." << endl;
        return fail;
    }
}

// Print sorted directory function
template <class listEntry>
void LinkedList<listEntry>::displaySortedDirectory() const {
    Node<listEntry> *current = head;
    if (current == nullptr) {
        cout << "Directory is currently empty." << endl;
    }
    else {
        while (current) {
            cout << current->data.surname << ", " << current->data.name << ": " << current->data.phoneNumber << "\n";
            current = current->next;
        }
    }
}

// Save to a txt file function
template <class listEntry>
void LinkedList<listEntry>::saveToFile(const string &fileName) const {
    ofstream output;
    output.open("teldir.txt"); // Name of the txt file that will be created, can be found in the project's directory
    
    Node<listEntry> *current = head;
    
    while (current) {
        output << "Surname: " << current->data.surname << endl
               << "Name: " << current->data.name << endl
        << "Phone number: " << current->data.phoneNumber << endl << endl;
        current = current->next;
    }
    output.close();
    cout << "All modifications made in this session have been exported to 'teldir.txt' in the project's directory. Program exiting..." << endl;
}

// Read from the txt file every time the program starts
template <class listEntry>
void LinkedList<listEntry>::loadFromFile(const string &fileName) {
    ifstream input(fileName);
    if (!input.is_open()) {
        cout << "Error opening file: " << fileName << endl;
        return;
    }

    string surname, name, phoneNumber;
        string label;

        while (getline(input, label, ':')) {
            // Remove spaces from before or after the labels
            label.erase(label.begin(), find_if(label.begin(), label.end(), [](unsigned char ch) {
                return !isspace(ch);
            }));
            label.erase(find_if(label.rbegin(), label.rend(), [](unsigned char ch) {
                return !isspace(ch);
            }).base(), label.end());

            if (label == "Surname") {
                getline(input, surname);
                // Remove spaces from before or after the surname
                surname.erase(surname.begin(), find_if(surname.begin(), surname.end(), [](unsigned char ch) {
                    return !isspace(ch);
                }));
                surname.erase(find_if(surname.rbegin(), surname.rend(), [](unsigned char ch) {
                    return !isspace(ch);
                }).base(), surname.end());
            } else if (label == "Name") {
                getline(input, name);
                // Remove spaces from before or after the name
                name.erase(name.begin(), find_if(name.begin(), name.end(), [](unsigned char ch) {
                    return !isspace(ch);
                }));
                name.erase(find_if(name.rbegin(), name.rend(), [](unsigned char ch) {
                    return !isspace(ch);
                }).base(), name.end());
            } else if (label == "Phone number") {
                getline(input, phoneNumber);
                // Remove spaces from before or after the phone number
                phoneNumber.erase(phoneNumber.begin(), find_if(phoneNumber.begin(), phoneNumber.end(), [](unsigned char ch) {
                    return !isspace(ch);
                }));
                phoneNumber.erase(find_if(phoneNumber.rbegin(), phoneNumber.rend(), [](unsigned char ch) {
                    return !isspace(ch);
                }).base(), phoneNumber.end());
                
                User newUser(surname, name, phoneNumber);
                addSubscriber(newUser);
            } else {
                // Handle wrong format in .txt file
                cout << "Error: Unrecognized label '" << label << "'" << endl;
                break;
            }
        }
        input.close();
        cout << "Data loaded from file: " << fileName << endl;
}
#endif /* LinkedList_hpp */
