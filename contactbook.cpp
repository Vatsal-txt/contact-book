#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Simple Contact structure
struct Contact
{
    string name;
    string phone;
    string email;
};

// Global arrays - simple storage
Contact contacts[100];    // Array to store contacts (max 100)
Contact deletedStack[50]; // Stack for undo (max 50)
int contactCount = 0;     // How many contacts we have
int stackTop = -1;        // Top of stack (-1 means empty)

// Function to add a contact
void addContact()
{
    if (contactCount >= 100)
    {
        cout << "Contact book is full!\n";
        return;
    }

    Contact newContact;
    cout << "\nEnter Name: ";
    cin.ignore();
    getline(cin, newContact.name);
    cout << "Enter Phone: ";
    getline(cin, newContact.phone);
    cout << "Enter Email: ";
    getline(cin, newContact.email);

    contacts[contactCount] = newContact;
    contactCount++;

    cout << "✓ Contact added successfully!\n";
}

// Function to display all contacts
void displayAll()
{
    if (contactCount == 0)
    {
        cout << "\nNo contacts found!\n";
        return;
    }

    cout << "\n===== ALL CONTACTS =====\n";
    for (int i = 0; i < contactCount; i++)
    {
        cout << "\nContact #" << (i + 1) << endl;
        cout << "Name: " << contacts[i].name << endl;
        cout << "Phone: " << contacts[i].phone << endl;
        cout << "Email: " << contacts[i].email << endl;
        cout << "------------------------\n";
    }
}

// Function to search contact by name
void searchContact()
{
    string searchName;
    cout << "\nEnter name to search: ";
    cin.ignore();
    getline(cin, searchName);

    bool found = false;
    for (int i = 0; i < contactCount; i++)
    {
        if (contacts[i].name == searchName)
        {
            cout << "\n✓ Contact Found!\n";
            cout << "Name: " << contacts[i].name << endl;
            cout << "Phone: " << contacts[i].phone << endl;
            cout << "Email: " << contacts[i].email << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "✗ Contact not found!\n";
    }
}

// Function to delete a contact
void deleteContact()
{
    if (contactCount == 0)
    {
        cout << "\nNo contacts to delete!\n";
        return;
    }

    displayAll();
    int index;
    cout << "\nEnter contact number to delete: ";
    cin >> index;
    index--; // Convert to 0-based index

    if (index < 0 || index >= contactCount)
    {
        cout << "✗ Invalid contact number!\n";
        return;
    }

    // Push to stack for undo (STACK PUSH operation)
    if (stackTop < 49)
    {
        stackTop++;
        deletedStack[stackTop] = contacts[index];
    }

    // Shift all contacts left to fill the gap
    for (int i = index; i < contactCount - 1; i++)
    {
        contacts[i] = contacts[i + 1];
    }
    contactCount--;

    cout << "✓ Contact deleted! (You can undo this)\n";
}

// Function to undo last delete (STACK POP operation)
void undoDelete()
{
    if (stackTop < 0)
    {
        cout << "\n✗ Nothing to undo!\n";
        return;
    }

    if (contactCount >= 100)
    {
        cout << "✗ Contact book is full!\n";
        return;
    }

    // Pop from stack and add back to contacts
    contacts[contactCount] = deletedStack[stackTop];
    stackTop--;
    contactCount++;

    cout << "✓ Last deleted contact restored!\n";
}

// Function to export contacts to JSON file
void exportToJSON()
{
    ofstream file("contacts.json");

    if (!file.is_open())
    {
        cout << "✗ Error creating file!\n";
        return;
    }

    file << "[\n";
    for (int i = 0; i < contactCount; i++)
    {
        file << "  {\n";
        file << "    \"name\": \"" << contacts[i].name << "\",\n";
        file << "    \"phone\": \"" << contacts[i].phone << "\",\n";
        file << "    \"email\": \"" << contacts[i].email << "\"\n";
        file << "  }";
        if (i < contactCount - 1)
            file << ",";
        file << "\n";
    }
    file << "]\n";

    file.close();
    cout << "✓ Contacts exported to contacts.json!\n";
}

// Main menu
void showMenu()
{
    cout << "\n╔════════════════════════════╗\n";
    cout << "║   CONTACT BOOK MENU        ║\n";
    cout << "╚════════════════════════════╝\n";
    cout << "1. Add Contact\n";
    cout << "2. Display All Contacts\n";
    cout << "3. Search Contact\n";
    cout << "4. Delete Contact\n";
    cout << "5. Undo Last Delete\n";
    cout << "6. Export to JSON\n";
    cout << "7. Exit\n";
    cout << "\nEnter your choice: ";
}

// Main function
int main()
{
    int choice;

    cout << "\n╔════════════════════════════════╗\n";
    cout << "║  Welcome to Contact Book! 📇   ║\n";
    cout << "╚════════════════════════════════╝\n";

    while (true)
    {
        showMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            addContact();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            searchContact();
            break;
        case 4:
            deleteContact();
            break;
        case 5:
            undoDelete();
            break;
        case 6:
            exportToJSON();
            break;
        case 7:
            cout << "\nThank you for using Contact Book! 👋\n";
            return 0;
        default:
            cout << "\n✗ Invalid choice! Please try again.\n";
        }
    }

    return 0;
}