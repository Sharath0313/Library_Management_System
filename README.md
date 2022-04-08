# Library_Management_System
A Library Management System using C++ on Command Line Interface.

## Setup and Installation

Make sure you have a working [MinGW](https://www.mingw-w64.org/) installation.

## Functionalities

Students:
* Can see all the books.
* Can see list of books s/he has.
* Can issue at max 5 books.
* Can issue a book for 30 days.
* Fine is 2 rupees/day after due date.

Professor:
* Can see all the books.
* Can see list of books s/he has.
* Can issue infinite number of books.
* Can issue a book for 60 days.
* Fine is 5 rupees/day after due date.

Librarian:
* Can list down all books/users.
* Can check which book is issued to which user.
* Can check list of books issue to user.
* Can add/update/delete user or book.

## Database

The existing database already contains,

Users

```bash
  1. Username: Student
     Password: student
     Role: student
```
```bash
  2. Username: Professor
     Password: professor
     Role: professor
```
```bash
  3. Username: Librarian
     Password: librarian
     Role: librarian
```

Books

```bash
  1. Book Title: Half Girlfriend
     Book Author: Chetan Bhagat
     Book Publication: Rupa & Co.
     Book ISBN: 978-81-291-3572-8
```
```bash
  2. Book Title: The Girl in Room 105
     Book Author: Chetan Bhagat
     Book Publication: Westland Books
     Book ISBN: 978-1542040464
```

## Run Locally

Download the repository in your local directory and open a terminal in the folder. Run the command 

```bash
  g++ library_management_system.cpp class.cpp
```

Followed by

```bash
  .\a.exe
```
Login and Enjoy.