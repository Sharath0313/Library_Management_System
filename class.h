#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

class Book{
    private:
    string Title;
    string Author;
    string ISBN;
    string Publication;
    string IssuedTo;
    string DueDate;
    public:
    void set_title(string title);
    void set_author(string author);
    void set_isbn(string isbn);
    void set_publication(string publication);
    void set_issued_to(string issued_to);
    void set_duedate(string duedate);
    string get_title();
    string get_author();
    string get_isbn();
    string get_publication();
    string get_issued_to();
    int Book_Request(string username, int id);
    string Show_duedate();
};

class Book_Database{
    private:
    vector <Book> Book_list;
    public:
    void Add(Book book);
    void Display();
    void Update(int i, Book new_book);
    void Delete(int i);
    int Search(string book_isbn);
    Book get_book(int i);
    vector <Book> get_book_list();
};

class User{
    private:
    string Name;
    string Password;
    string Id;
    public:
    void set_name(string name);
    void set_password(string password);
    void set_id(string id);
    string get_name();
    string get_password();
    string get_id();
};

class Student: public User{
    private:
    vector <Book> My_Books;
    int Fine_amount;
    public:
    void Add_book(Book book);
    vector <Book> get_my_books();
    void set_fields(User *user, vector <Book> my_books, int fine);
    void Calculate_fine();
    int get_fine();
    void Clear_fine_amount(Book_Database *books);
    void Submit_book(string isbn, Book_Database *books);
};

class Professor: public User{
    private:
    vector <Book> My_Books;
    int Fine_amount;
    public:
    void Add_book(Book book);
    vector <Book> get_my_books();
    void set_fields(User *user, vector <Book> my_books, int fine);
    void Calculate_fine();
    int get_fine();
    void Clear_fine_amount(Book_Database *books);
    void Submit_book(string isbn, Book_Database *books);
};

class User_Database{
    private:
    vector <User> User_list ;

    public:
    void Add( User user);
    void Update(int i, User new_user);
    void Delete(int i);
    int Search(User user);
    void Display();
    int Unique_Username(string username);
    vector <User> get_user_list();
};