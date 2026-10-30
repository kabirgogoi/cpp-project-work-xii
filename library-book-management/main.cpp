#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

const char FILE_NAME[] = "records.dat";

class Book
{
private:
    int bookId;
    char title[50];
    char author[50];

public:
    void input()
    {
        cout << "Enter Book ID: ";
        cin >> bookId;
        cout << "Enter Book Title: ";
        cin.ignore(1000, '\n');
        cin.getline(title, 50);
        cout << "Enter Author Name: ";
        cin.getline(author, 50);
    }

    void display()
    {
        cout << "Book ID: " << bookId << endl;
        cout << "Book Title: " << title << endl;
        cout << "Author Name: " << author << endl;
    }

    int getId()
    {
        return bookId;
    }
};

class BookManagement
{
public:
    void addRecord()
    {
        Book record;
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
        Book record;
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
        Book record;
        cout << "Enter Book ID to search: ";
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
        Book record;
        cout << "Enter Book ID to delete: ";
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
            cout << "\n--- Book Record Management ---\n";
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
    BookManagement manager;
    manager.menu();
    return 0;
}
