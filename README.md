# Prison Management System

## Overview

This project implements a simple **Prison Management System** designed for academic purposes. The system allows users to manage information about prisons and inmates, providing functionalities to add, search, delete, and display details.

## File Structure

- **final_project.cpp**: The main C++ source code file containing the implementation of the Prison Management System.
- **prisons.txt**: File storing details about prisons (ID, name, location).
- **inmates.txt**: File storing details about inmates (ID, name, prison ID).
- **prison_hash.txt**: File storing hash values and keys for prisons.
- **inmate_hash.txt**: File storing hash values and keys for inmates.
- **report.pdf**: A detailed report explaining the design, functionality, and implementation of the system. *(Attached in the project directory)*
- **presentation.ppt**: A PowerPoint presentation summarizing the key aspects of the project. *(Attached in the project directory)*

## Features

- Add a new prison, ensuring uniqueness of the prison ID.
- Add a new inmate, checking for duplicate inmate IDs and validating associated prison IDs.
- Search for prisons and inmates by their respective IDs.
- Delete prisons and associated inmates, updating the system and files accordingly.
- Display a list of all prisons and inmates.

## Additional Notes

- The system uses hash tables for efficient data storage and retrieval.
- Input validation is implemented to ensure data integrity.
- Limits are set for both hash table size and linked list length for effective management.
- The `deletePrison()` function has been enhanced to automatically delete associated inmates.

## Running the Code

1. Compile the source code using a C++ compiler.
   ```bash
   g++ final_project.cpp -o prison_management
