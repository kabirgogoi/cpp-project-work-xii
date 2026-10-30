#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

struct Product {
    int productId;
    char name[50];
    float price;
};

const char FILE_NAME[] = "records.dat";

void showRecord(Product record) {
    cout << "Product ID: " << record.productId << endl;
    cout << "Product Name: " << record.name << endl;
    cout << "Price: " << record.price << endl;
}

void addRecord() {
    Product record;
    cout << "Enter Product ID: ";
    cin >> record.productId;
    cin.ignore(1000, '\n');
    cout << "Enter Product Name: ";
    cin.getline(record.name, 50);
    cout << "Enter Price: ";
    cin >> record.price;
    ofstream file(FILE_NAME, ios::binary | ios::app);
    if (!file) {
        cout << "Cannot open file.\n";
        return;
    }
    file.write((char*)&record, sizeof(record));
    file.close();
    cout << "Record added successfully.\n";
}

void displayRecords() {
    Product record;
    ifstream file(FILE_NAME, ios::binary);
    if (!file) {
        cout << "No records found.\n";
        return;
    }
    bool found = false;
    while (file.read((char*)&record, sizeof(record))) {
        showRecord(record);
        cout << "--------------------\n";
        found = true;
    }
    if (!found) cout << "No records found.\n";
    file.close();
}

void searchRecord() {
    int id;
    Product record;
    cout << "Enter Product ID to search: ";
    cin >> id;
    ifstream file(FILE_NAME, ios::binary);
    if (!file) {
        cout << "No records found.\n";
        return;
    }
    bool found = false;
    while (file.read((char*)&record, sizeof(record))) {
        if (record.productId == id) {
            showRecord(record);
            found = true;
            break;
        }
    }
    if (!found) cout << "Record not found.\n";
    file.close();
}

void deleteRecord() {
    int id;
    Product record;
    cout << "Enter Product ID to delete: ";
    cin >> id;
    ifstream file(FILE_NAME, ios::binary);
    if (!file) {
        cout << "No records found.\n";
        return;
    }
    ofstream temp("temp.dat", ios::binary);
    if (!temp) {
        cout << "Cannot create temporary file.\n";
        file.close();
        return;
    }
    bool found = false;
    while (file.read((char*)&record, sizeof(record))) {
        if (record.productId == id) {
            found = true;
        } else {
            temp.write((char*)&record, sizeof(record));
        }
    }
    file.close();
    temp.close();
    if (found) {
        remove(FILE_NAME);
        rename("temp.dat", FILE_NAME);
        cout << "Record deleted successfully.\n";
    } else {
        remove("temp.dat");
        cout << "Record not found.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n--- Product Record Management ---\n";
        cout << "1. Add Record\n";
        cout << "2. Display Records\n";
        cout << "3. Search Record\n";
        cout << "4. Delete Record\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addRecord(); break;
            case 2: displayRecords(); break;
            case 3: searchRecord(); break;
            case 4: deleteRecord(); break;
            case 5: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);
    return 0;
}
