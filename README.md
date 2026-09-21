# Address Book Management System

A menu-driven command-line address book in C. Contacts are saved to `contact.txt` so they persist between runs.

**Author:** Sarojani Mutnale | **Date:** 29/12/2025

## Features

- Create, search, edit, delete, and list contacts
- Search by name, phone, or email
- Input validation for name, phone, and email
- Contacts load automatically on startup and save on exit

## Files

| File | Purpose |
|---|---|
| `main.c` | Entry point and menu loop |
| `contact.c` / `contact.h` | Contact operations and data structures |
| `file.c` / `file.h` | Save to and load from `contact.txt` |
| `contact.txt` | Saved contacts (sample data included) |

## Build and Run

    gcc *.c -o addressbook
    ./addressbook

Run it from the project folder, since `contact.txt` is read from the current directory.

## Menu

    1. Create contact
    2. Search contact
    3. Edit contact
    4. Delete contact
    5. List all contacts
    6. Save and Exit

Changes are written to disk only when you choose **6**.

## Validation

- **Name:** letters and spaces only
- **Phone:** exactly 10 digits
- **Email:** must contain `@` and `.com`, no spaces

## Data Format

    12
    John Doe,1234567890,john@example.com
    Alice Smith,0987654321,alice@example.com

The first line is the contact count, followed by one `name,phone,email` line per contact. The book holds up to 100 contacts.

## Known Limitations

- No check for the 100-contact limit when creating a contact
- Name search is case-sensitive
- Delete removes only the first match
