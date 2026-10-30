#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

struct Employee
{
    int employeeId;
    char name[50];
    float salary;
};

const char FILE_NAME[] = "records.dat";

void showRecord(Employee record)
{
    cout << "Employee ID: " << record.employeeId << endl;
    cout << "Name: " << record.name << endl;
    cout << "Salary: " << record.salary << endl;
}

void addRecord()
{
    Employee record;
    cout << "Enter Employee ID: ";
    cin >> record.employeeId;
    cin.ignore(1000, '\n');
    cout << "Enter Name: ";
    cin.getline(record.name, 50);
    cout << "Enter Salary: ";
    cin >> record.salary;
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
    Employee record;
    ifstream file(FILE_NAME, ios::binary);
    if (!file)
    {
        cout << "No records found.\n";
        return;
    }
    bool found = false;
    while (file.read((char *)&record, sizeof(record)))
    {
        showRecord(record);
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
    Employee record;
    cout << "Enter Employee ID to search: ";
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
        if (record.employeeId == id)
        {
            showRecord(record);
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
    Employee record;
    cout << "Enter Employee ID to delete: ";
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
        if (record.employeeId == id)
        {
            found = true;
        }
        else
        {
            temp.write((char *)&record, sizeof(record));
        }
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

int main()
{
    int choice;
    do
    {
        cout << "\n--- Employee Record Management ---\n";
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
    return 0;
}
