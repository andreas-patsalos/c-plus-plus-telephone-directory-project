/*
 Programmer name: Andreas Patsalos
 Program title: Telephony directory by implementing a linked list data structure
 Date: 23/12/2023
 Program goals: The user should be presented with a menu with the options of:
                1. Adding a new subscriber to the directory
                2. Deleting a subscriber from the directory
                3. Adding additional phone numbers to a subscriber
                4. Deleting a phone number from a subscriber
                5. Display all the phone numbers of a subscriber
                6. Sorted display of all the subscribers by Surname-Name
                7. Exporting the directory to a .txt file named "teldir.txt" (Can be found in the project's directory)
 */
#include "LinkedList.hpp"
#include <iostream>
using namespace std;

// Display the menu to the user function
void displayMenu() {
    cout << "1. Add a new subscriber\n"
         << "2. Remove a phone number from a subscriber\n"
         << "3. Add a phone number to a subscriber\n"
         << "4. Display a subscriber’s phone numbers\n"
         << "5. Delete a subscriber\n"
         << "6. Sorted display of directory items by Surname-Name\n"
         << "7. Save and exit\n";
}

int main(int argc, const char * argv[]) {
    
    LinkedList<User> directory;
    
    // Load data from .txt file
    directory.loadFromFile("teldir.txt");
    
    // The menu will keep appearing to the user until they select case 7: Exit
    while (true) {
        displayMenu();
        
        int menuSelection;
        
        cout << "Enter menu selection: ";
        cin >> menuSelection;
        cout << endl;
        
        switch (menuSelection) {
            case 1: {
                string surname, name, phoneNumber;
                cout << "Enter subscriber's surname: ";
                cin >> surname;
                cout<< "Enter subscriber's name: ";
                cin >> name;
                cout << "Enter subscriber's phone number: ";
                cin >> phoneNumber;
                
                User newUser(surname, name, phoneNumber);
                directory.addSubscriber(newUser);
                break;
            }
            case 2: {
                string surname, name, phoneNumber;
                cout << "Enter subscriber's surname: ";
                cin >> surname;
                cout<< "Enter subscriber's name: ";
                cin >> name;
                cout << "Enter subscriber's phone number: ";
                cin >> phoneNumber;
                
                directory.removePhoneNumber(surname, name, phoneNumber);
                break;
            }
            case 3: {
                string surname, name, phoneNumber;
                cout << "Enter subscriber's surname: ";
                cin >> surname;
                cout<< "Enter subscriber's name: ";
                cin >> name;
                cout << "Enter phone number to add: ";
                cin >> phoneNumber;
                
                directory.addPhoneNumber(surname, name, phoneNumber);
                break;
            }
            case 4: {
                string surname, name;
                cout << "Enter subscriber's surname: ";
                cin >> surname;
                cout<< "Enter subscriber's name: ";
                cin >> name;
                
                directory.displayPhoneNumbers(surname, name);
                break;
            }
            case 5: {
                string surname, name;
                cout << "Enter subscriber's surname: ";
                cin >> surname;
                cout<< "Enter subscriber's name: ";
                cin >> name;
                
                directory.deleteSubscriber(surname, name);
                break;
            }
            case 6: {
                directory.displaySortedDirectory();
                break;
            }
            case 7: {
                directory.saveToFile("teldir.txt");
                return 0;
            }
        }
    }
    return 0;
}
