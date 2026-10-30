#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

const char FILE_NAME[] = "records.dat";

class Product
{
private:
    int productId;
    char name[50];
    float price;

public:
    void input()
    {
        cout << "Enter Product ID: ";
        cin >> productId;
        cout << "Enter Product Name: ";
        cin.ignore(1000, '\n');
        cin.getline(name, 50);
        cout << "Enter Price: ";
        cin >> price;
    }

    void display()
    {
        cout << "Product ID: " << productId << endl;
        cout << "Product Name: " << name << endl;
        cout << "Price: " << price << endl;
    }

    int getId()
    {
        return productId;
    }
};

class ProductManagement
{
public:
    void addRecord()
    {
        Product record;
        record.input();

        ofstream file(FILE_NAME, ios::binary | ios::app);
        if (!file)
        {
            cout << "Cannot open file.\n";
            return;
        }
        file.write((char *)&record, sizeof(record));
        file.close();
        cout << "Record added successfully.\n";
    }

    void displayRecords()
    {
        Product record;
        ifstream file(FILE_NAME, ios::binary);
        if (!file)
        {
            cout << "No records found.\n";
            return;
        }

        bool found = false;
        while (file.read((char *)&record, sizeof(record)))
        {
            record.display();
            cout << "--------------------\n";
            found = true;
        }
        if (!found)
            cout << "No records found.\n";
        file.close();
    }

    void searchRecord()
    {
        int id;
        Product record;
        cout << "Enter Product ID to search: ";
        cin >> id;
        ifstream file(FILE_NAME, ios::binary);
        if (!file)
        {
            cout << "No records found.\n";
            return;
        }

        bool found = false;
        while (file.read((char *)&record, sizeof(record)))
        {
            if (record.getId() == id)
            {
                record.display();
                found = true;
                break;
            }
        }
        if (!found)
            cout << "Record not found.\n";
        file.close();
    }

    void deleteRecord()
    {
        int id;
        Product record;
        cout << "Enter Product ID to delete: ";
        cin >> id;
        ifstream file(FILE_NAME, ios::binary);
        if (!file)
        {
            cout << "No records found.\n";
            return;
        }
        ofstream temp("temp.dat", ios::binary);
        if (!temp)
        {
            cout << "Cannot create temporary file.\n";
            file.close();
            return;
        }

        bool found = false;
        while (file.read((char *)&record, sizeof(record)))
        {
            if (record.getId() == id)
                found = true;
            else
                temp.write((char *)&record, sizeof(record));
        }
        file.close();
        temp.close();

        if (found)
        {
            remove(FILE_NAME);
            rename("temp.dat", FILE_NAME);
            cout << "Record deleted successfully.\n";
        }
        else
        {
            remove("temp.dat");
            cout << "Record not found.\n";
        }
    }

    void menu()
    {
        int choice;
        do
        {
            cout << "\n--- Product Record Management ---\n";
            cout << "1. Add Record\n";
            cout << "2. Display Records\n";
            cout << "3. Search Record\n";
            cout << "4. Delete Record\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                addRecord();
                break;
            case 2:
                displayRecords();
                break;
            case 3:
                searchRecord();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 5);
    }
};

int main()
{
    ProductManagement manager;
    manager.menu();
    return 0;
}
