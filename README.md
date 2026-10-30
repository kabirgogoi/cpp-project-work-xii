# Class XII C++ Project Work

Five simple menu-driven C++ programs using binary files, `read()` and `write()`.

## Projects

- `student-record-management/main.cpp` — roll number, name and marks
- `library-book-management/main.cpp` — book ID, title and author
- `employee-record-management/main.cpp` — employee ID, name and salary
- `product-record-management/main.cpp` — product ID, name and price
- `patient-record-management/main.cpp` — patient ID, name and age

Each program provides exactly five options: Add Record, Display Records, Search Record, Delete Record and Exit.

## Compile and run

From a project folder, run:

```sh
g++ main.cpp -o program
./program
```

Each program stores records in `records.dat` in the current working directory. Run the programs from their own folders to keep their data separate.

Deletion copies retained records into `temp.dat`, then replaces the original file.

Enter valid numbers for numeric fields. Use unique IDs for each record.
