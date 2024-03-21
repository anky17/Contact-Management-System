//*******************************************************
//----------------CONTACT MANAGEMENT SYSTEM--------------
//*******************************************************
// � 2024 Ankit Diyal. All rights reserved.
// Trademark � 2024 Ankit Diyal.

#include <conio.h>

#include <fstream>
#include <iostream>

using namespace std;

class contact {
 private:
  char fullName[50], lastName[50], address[50], email[50];
  long long phoneNumber;

 public:
  // Function to create a new contact
  void createContact() {
    cout << "Enter your first name: ";
    cin >> fullName;
    cout << "Enter your last name: ";
    cin >> lastName;
    cout << "Enter phone: ";
    cin >> phoneNumber;
    cout << "Enter address: ";
    cin >> address;
    cout << "Enter email: ";
    cin >> email;
  }

  // Function to display contact details
  void showContact() {
    cout << "Name: " << fullName << " " << lastName << endl;
    cout << "Phone: " << phoneNumber << endl;
    cout << "Address: " << address << endl;
    cout << "Email: " << email << endl;
  }

  // Function to write contact information to file
  void writeOnFile() {
    char ch;
    ofstream f1;
    f1.open("CMS.dat", ios::binary | ios::app);

    do {
      createContact();
      f1.write(reinterpret_cast<char*>(this), sizeof(*this));
      cout << "Do you have next data?(y/n)";
      cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    cout << "Contact has been Successfully Created...";
    f1.close();
  }

  // Function to read contact information from file
  void readFromFile() {
    ifstream f2;
    f2.open("CMS.dat", ios::binary);

    cout << "\n================================\n";
    cout << "LIST OF CONTACTS";
    cout << "\n================================\n";

    while (f2.read(reinterpret_cast<char*>(this), sizeof(*this))) {
      showContact();
      cout << "\n================================\n";
    }
    f2.close();
  }

  // Function to search for a contact by phone number
  void searchOnFile() {
    ifstream f3;
    long long phone;
    cout << "Enter phone no.: ";
    cin >> phone;
    f3.open("CMS.dat", ios::binary);

    while (f3.read(reinterpret_cast<char*>(this), sizeof(*this))) {
      if (phone == phoneNumber) {
        showContact();
        return;
      }
    }
    cout << "\n\n No record not found";
    f3.close();
  }

  // Function to delete a contact by phone number
  void deleteFromFile() {
    long long phoneNum;
    int flag = 0;
    ofstream f4;
    ifstream f5;

    f5.open("CMS.dat", ios::binary);
    f4.open("temp.dat", ios::binary);

    cout << "Enter phone no. to delete: ";
    cin >> phoneNum;

    while (f5.read(reinterpret_cast<char*>(this), sizeof(*this))) {
      if (phoneNumber != phoneNum) {
        f4.write(reinterpret_cast<char*>(this), sizeof(*this));
      } else
        flag = 1;
    }
    f5.close();
    f4.close();
    remove("CMS.dat");
    rename("temp.dat", "CMS.dat");

    flag == 1 ? cout << endl
                     << endl
                     << "\tContact Deleted..."
              : cout << endl
                     << endl
                     << "\tContact Not Found...";
  }

  // Function to edit a contact
  void editContact() {
    long long phoneNum;
    fstream f6;

    cout << "Edit contact";
    cout << "\n===============================\n\n";
    cout << "Enter the phone number to be edited: ";
    cin >> phoneNum;

    f6.open("CMS.dat", ios::binary | ios::in | ios::out);

    while (f6.read(reinterpret_cast<char*>(this), sizeof(*this))) {
      if (phoneNumber == phoneNum) {
        cout << "Enter new record\n";
        createContact();
        int pos = -1 * static_cast<int>(sizeof(*this));
        f6.seekp(pos, ios::cur);
        f6.write(reinterpret_cast<char*>(this), sizeof(*this));
        cout << endl << endl << "\t Contact Successfully Updated...!!";
        f6.close();  // Close the file after updating the contact
        return;
      }
    }
    cout << "\n\n No record found for the given phone number";
    f6.close();
  }
};

int main() {
  system("cls");
  cout << "\n\n\n\n\n\n\n\n\t\t\t * WELCOME TO CONTACT MANAGEMENT SYSTEM *";
  getch();

  while (1) {
    contact c1;
    int choice;

    system("cls");
    system("Color 03");

    cout << "\nCONTACT MANAGEMENT SYSTEM";
    cout << "\n\nMAIN MENU";
    cout << "\n=====================\n";
    cout << "[1] Add a new Contact\n";
    cout << "[2] List all Contacts\n";
    cout << "[3] Search for contact\n";
    cout << "[4] Delete a Contact\n";
    cout << "[5] Edit a Contact\n";
    cout << "[0] Exit";
    cout << "\n=====================\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
      case 1:
        system("cls");
        c1.writeOnFile();
        break;

      case 2:
        system("cls");
        c1.readFromFile();
        break;

      case 3:
        system("cls");
        c1.searchOnFile();
        break;

      case 4:
        system("cls");
        c1.deleteFromFile();
        break;

      case 5:
        system("cls");
        c1.editContact();
        break;

      case 0:
        system("cls");
        cout << "\n\n\n\t\t\tThank you for using Contact Management System."
             << endl
             << endl;
        exit(0);
        break;

      default:
        continue;
    }

    int opt;
    cout << "\n\n..::Enter the Choice:\n[1] Main Menu\t\t[0] Exit\n";
    cin >> opt;

    switch (opt) {
      case 0:
        system("cls");
        cout << "\n\n\n\t\t\tThank you for using Contact Management System."
             << endl
             << endl;
        exit(0);
        break;

      default:
        continue;
    }
  }

  return 0;
}
