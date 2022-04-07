#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

int update = 0;
string waste;

void DatePlusDays( struct tm* date, int days )
{
    const time_t ONE_DAY = 24 * 60 * 60 ;

    time_t date_seconds = mktime( date ) + (days * ONE_DAY) ;

    *date = *localtime( &date_seconds ) ; ;
}

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

int Book::Book_Request(string username, int id){
    if (get_issued_to() != "None")
    {
        cout << "Book is not Available to Issue!!!\n";
        return 0;
    }
    else
    {
        set_issued_to(username);
        time_t now = time(0);

        tm *date = localtime(&now);
        if (id == 1)
        DatePlusDays( date, 30 ) ; 
        else
        DatePlusDays( date, 60 ) ;
        int year = 1900 + date->tm_year ;
        int day =  date->tm_mday ;
        int month = 1 + date->tm_mon ;

        string d,m,y,duedate;

        stringstream dd;

        dd << day;
        dd >> d;

        stringstream mm;

        mm << month;
        mm >> m;

        stringstream yy;

        yy << year;
        yy >> y;

        duedate = d + "-" + m + "-" + y ;

        set_duedate(duedate);
        cout << "Book has been Successfully Issued...\n";
        return 1;
    }
}

void Book::set_title(string title){
    Title = title;
    return ;
}

void Book::set_author(string author){
    Author = author;
    return ;
}

void Book::set_publication(string publication){
    Publication = publication;
    return ;
}

void Book::set_isbn(string isbn){
    ISBN = isbn;
    return ;
}

void Book::set_issued_to(string issued_to){
    IssuedTo = issued_to;
    return ;
}

void Book::set_duedate(string duedate){
    DueDate = duedate;
    return ;
}

string Book::get_title(){
    return Title;
}

string Book::get_author(){
    return Author;
}

string Book::get_publication(){
    return Publication;
}

string Book::get_isbn(){
    return ISBN;
}

string Book::get_issued_to(){
    return IssuedTo;
}

string Book::Show_duedate(){
    return DueDate;
}

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

void Book_Database::Add(Book book){

    Book_list.push_back(book);

    return ;
}

void Book_Database::Display(){
    for(int i=0; i < Book_list.size(); i++)
    {
        cout << i+1 << ". Book Title: " << Book_list[i].get_title() << endl;
        cout << "   Book Author: " << Book_list[i].get_author() << endl;
        cout << "   Book Publication: " << Book_list[i].get_publication() << endl;
        cout << "   Book ISBN: " << Book_list[i].get_isbn() << endl;
    }

    return;
}

void Book_Database::Update(int i, Book new_book){
    if( 0 < i && i <= Book_list.size() )
    {
        Book_list[i-1].set_title(new_book.get_title()) ;
        Book_list[i-1].set_author(new_book.get_author());
        Book_list[i-1].set_publication(new_book.get_publication());
        Book_list[i-1].set_isbn(new_book.get_isbn());
        Book_list[i-1].set_issued_to(new_book.get_issued_to());
        Book_list[i-1].set_duedate(new_book.Show_duedate());
        cout << "Database Updated Successfully...\n";
        update = 1;
    }
    else
    {
        cout << "Inavlid Index!!!";
    }

    return ;
}

void Book_Database::Delete(int i){
    if( 0 < i && i <= Book_list.size() )
    {
        Book_list.erase(Book_list.begin() + i -1);
        cout << "Book Deleted Successfully...\n";
        update = 1;
    }
    else
    {
        cout << "INVALID INDEX!!!\n";
    }
    return ;
}

int Book_Database::Search(string book_isbn){

    for(int i=1; i <= Book_list.size(); i++)
    {
        if(Book_list[i-1].get_isbn() == book_isbn)
        return i;
    }

    return 0;
}

Book Book_Database::get_book(int i){
    return Book_list[i-1];
}

vector <Book> Book_Database::get_book_list(){
    return Book_list;
}

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

string User::get_name(){
    return Name;
}

string User::get_password(){
    return Password;
}

string User::get_id(){
    return Id;
}

void User::set_name(string name){
        Name = name;
}

void User::set_password(string password){
        Password = password;
}

void User::set_id(string id){
        Id = id;
}

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
    // void Submit_book();
};

void Student::Add_book(Book book){
    My_Books.push_back(book);
    return ;
}

vector <Book> Student::get_my_books(){
    return My_Books;
}

void Student::set_fields(User *user, vector <Book> my_books, int fine){
    set_name(user->get_name());
    set_password(user->get_password());
    set_id(user->get_id());
    My_Books = my_books;
    Fine_amount = fine;
    
    return ;
}

void Student::Calculate_fine(){
    time_t now = time(0);

    tm *date = localtime(&now);

    int y1 = 1900 + date->tm_year ;
    int d1 =  date->tm_mday ;
    int m1 = 1 + date->tm_mon ;

    // cout << "current date: " << d1 << "-" << m1 << "-" << y1 << endl;
    string p, y="",d="",m="";
    int a=1,fine=0;

    for( int i=0 ; i<My_Books.size() ; i++)
    {
        d="";
        m="";
        y="";
        a=1;
        // cout << d << m << y << "yep" << endl;
        p = My_Books[i].Show_duedate() ;
        for(int j=0 ; j<p.size() ; j++)
        {
            if(p[j] != '-')
            {
                if(a==1)
                {
                    // cout << p[j] << endl;
                    d = d + p[j];
                }
                else if(a==2)
                {
                    m = m + p[j];
                }
                else if(a==3)
                {
                    y = y + p[j];
                }
            }
            else
            {
                a = a+1;
            }
        }
        int d2,m2,y2;
        stringstream dd;
        dd << d;
        dd >> d2;
        stringstream mm;
        mm << m;
        mm >> m2;
        stringstream yy;
        yy << y;
        yy >> y2;

        // cout << "date: " << d2 << "-" << m2 << "-" << y2 << endl; 
        
        int diff = ((y1*365) + (m1*30) + (d1)) - ((y2*365) + (m2*30) + (d2));

        // cout << diff << endl;

        if( diff > 0)
        fine = fine + (2*diff);
    }

    Fine_amount = fine;

    return ;
}

int Student::get_fine(){
    return Fine_amount;
}

void Student::Clear_fine_amount(Book_Database *books){
    Fine_amount = 0;
    time_t now = time(0);

    tm *date = localtime(&now);

    int y1 = 1900 + date->tm_year ;
    int d1 =  date->tm_mday ;
    int m1 = 1 + date->tm_mon ;

    // cout << "current date: " << d1 << "-" << m1 << "-" << y1 << endl;
    string p, y="",d="",m="";
    int a=1,fine=0,i=0;

    while( i<My_Books.size() )
    {
        d="";
        m="";
        y="";
        a=1;
        // cout << d << m << y << "yep" << endl;
        p = My_Books[i].Show_duedate() ;
        for(int j=0 ; j<p.size() ; j++)
        {
            if(p[j] != '-')
            {
                if(a==1)
                {
                    // cout << p[j] << endl;
                    d = d + p[j];
                }
                else if(a==2)
                {
                    m = m + p[j];
                }
                else if(a==3)
                {
                    y = y + p[j];
                }
            }
            else
            {
                a = a+1;
            }
        }
        int d2,m2,y2;
        stringstream dd;
        dd << d;
        dd >> d2;
        stringstream mm;
        mm << m;
        mm >> m2;
        stringstream yy;
        yy << y;
        yy >> y2;

        // cout << "date: " << d2 << "-" << m2 << "-" << y2 << endl; 
        
        int diff = ((y1*365) + (m1*30) + (d1)) - ((y2*365) + (m2*30) + (d2));

        // cout << diff << endl;

        if( diff > 0)
        {
            int index = books->Search(My_Books[i].get_isbn());
            My_Books[i].set_issued_to("None");
            My_Books[i].set_duedate("NA");
            books->Update(index, My_Books[i]);
            update = 1;
            My_Books.erase(My_Books.begin() + i);
            continue;
        }
        i = i+1;
    }

    return ;
}

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
};

void Professor::Add_book(Book book){
    My_Books.push_back(book);
    return ;
}

vector <Book> Professor::get_my_books(){
    return My_Books;
}

void Professor::set_fields(User *user, vector <Book> my_books, int fine){
    set_name(user->get_name());
    set_password(user->get_password());
    set_id(user->get_id());
    My_Books = my_books;
    Fine_amount = fine;
    return ;
}

void Professor::Calculate_fine(){
    time_t now = time(0);

    tm *date = localtime(&now);

    int y1 = 1900 + date->tm_year ;
    int d1 =  date->tm_mday ;
    int m1 = 1 + date->tm_mon ;

    // cout << "current date: " << d1 << "-" << m1 << "-" << y1 << endl;
    string p, y="",d="",m="";
    int a=1,fine=0;

    for( int i=0 ; i<My_Books.size() ; i++)
    {
        d="";
        m="";
        y="";
        a=1;
        // cout << d << m << y << "yep" << endl;
        p = My_Books[i].Show_duedate() ;
        for(int j=0 ; j<p.size() ; j++)
        {
            if(p[j] != '-')
            {
                if(a==1)
                {
                    // cout << p[j] << endl;
                    d = d + p[j];
                }
                else if(a==2)
                {
                    m = m + p[j];
                }
                else if(a==3)
                {
                    y = y + p[j];
                }
            }
            else
            {
                a = a+1;
            }
        }
        int d2,m2,y2;
        stringstream dd;
        dd << d;
        dd >> d2;
        stringstream mm;
        mm << m;
        mm >> m2;
        stringstream yy;
        yy << y;
        yy >> y2;

        // cout << "date: " << d2 << "-" << m2 << "-" << y2 << endl; 
        
        int diff = ((y1*365) + (m1*30) + (d1)) - ((y2*365) + (m2*30) + (d2));

        // cout << diff << endl;

        if( diff > 0)
        fine = fine + (2*diff);
    }

    Fine_amount = fine;

    return ;
}

int Professor::get_fine(){
    return Fine_amount;
}

void Professor::Clear_fine_amount(Book_Database *books){
    Fine_amount = 0;
    time_t now = time(0);

    tm *date = localtime(&now);

    int y1 = 1900 + date->tm_year ;
    int d1 =  date->tm_mday ;
    int m1 = 1 + date->tm_mon ;

    // cout << "current date: " << d1 << "-" << m1 << "-" << y1 << endl;
    string p, y="",d="",m="";
    int a=1,fine=0,i=0;

    while( i<My_Books.size() )
    {
        d="";
        m="";
        y="";
        a=1;
        // cout << d << m << y << "yep" << endl;
        p = My_Books[i].Show_duedate() ;
        for(int j=0 ; j<p.size() ; j++)
        {
            if(p[j] != '-')
            {
                if(a==1)
                {
                    // cout << p[j] << endl;
                    d = d + p[j];
                }
                else if(a==2)
                {
                    m = m + p[j];
                }
                else if(a==3)
                {
                    y = y + p[j];
                }
            }
            else
            {
                a = a+1;
            }
        }
        int d2,m2,y2;
        stringstream dd;
        dd << d;
        dd >> d2;
        stringstream mm;
        mm << m;
        mm >> m2;
        stringstream yy;
        yy << y;
        yy >> y2;

        // cout << "date: " << d2 << "-" << m2 << "-" << y2 << endl; 
        
        int diff = ((y1*365) + (m1*30) + (d1)) - ((y2*365) + (m2*30) + (d2));

        // cout << diff << endl;

        if( diff > 0)
        {
            int index = books->Search(My_Books[i].get_isbn());
            My_Books[i].set_issued_to("None");
            My_Books[i].set_duedate("NA");
            books->Update(index, My_Books[i]);
            update = 1;
            My_Books.erase(My_Books.begin() + i);
            continue;
        }
        i = i+1;
    }

    return ;
}

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

void User_Database::Add( User user){

    User_list.push_back(user);

    return ;
}

void User_Database::Update(int i, User new_user){
    if ( 0 < i &&  i <= User_list.size() )
    {
        User_list[i-1].set_name(new_user.get_name());
        User_list[i-1].set_password(new_user.get_password());
        User_list[i-1].set_id(new_user.get_id());

        cout << "User Updated Successfully...\n";
        update = 1;
    }
    else
    {
        cout << "INVAILD INDEX!!!\n";
    }
    return ;
}

void User_Database::Delete(int i){
    if ( 0 < i && i <= User_list.size() )
    {
        User_list.erase(User_list.begin() + i - 1);
        cout << "User Deleted Successfully...\n";

        update = 1;
    }
    else
    {
        cout << "INVALID INDEX!!!\n";
    }
    return ;
}

int User_Database::Search(User user){
    
    for(int i=1; i <= User_list.size(); i++)
    {
        if( ( User_list[i-1].get_name() == user.get_name() ) && ( User_list[i-1].get_password() == user.get_password() ) && ( User_list[i-1].get_id() == user.get_id() ))
        {
            return i;
        }
    }
    return 0;
}

void User_Database::Display(){
    for( int i=0; i<User_list.size() ; i++)
    {
        cout << i+1 << ". UserName: " << User_list[i].get_name() << endl;
        cout << "   UserId: " << User_list[i].get_id() << endl;
    }

    return ;
}

int User_Database::Unique_Username(string username){
    for(int i=0; i < User_list.size(); i++)
    {
        if(User_list[i].get_name() == username)
        return 0; 
    }
    return 1;
}

vector <User> User_Database::get_user_list(){
    return User_list;
}

User_Database create_user_database(){
    User_Database users;

    fstream fin;
    string name, password, id;

    fin.open("user_database.txt", ios::in | ios::out);

    while ( fin )
    {
        getline(fin,name);
        if(name == "-1")
        break;
        getline(fin,password);
        getline(fin,id);

        User user;
        user.set_name(name);
        user.set_password(password);
        user.set_id(id);

        users.Add(user);
    }

    fin.close();
    fin.clear();
    
    return users;
}

Book_Database create_book_database_student(User *user, Student *user_student){
    Book_Database books;

    vector <Book> my_books;

    fstream fin;
    string title, author, publication, isbn, issued_to, duedate;

    fin.open("book_database.txt",ios::in | ios::out);

    while ( fin )
    {
        getline(fin,title);
        if(title == "-1")
        break;
        getline(fin,author);
        getline(fin,publication);
        getline(fin,isbn);
        getline(fin,issued_to);
        getline(fin,duedate);

        Book book;

        book.set_title(title);
        book.set_author(author);
        book.set_publication(publication);
        book.set_isbn(isbn);
        book.set_issued_to(issued_to);
        book.set_duedate(duedate);

        books.Add(book);

        if(issued_to == user->get_name())
        {
            my_books.push_back(book);
        }

    }

    fin.close();
    fin.clear();

    user_student->set_fields(user, my_books, 0);

    return books;    
}

Book_Database create_book_database_professor(User *user, Professor *user_professor){
    Book_Database books;

    vector <Book> my_books;

    fstream fin;
    string title, author, publication, isbn, issued_to, duedate;

    fin.open("book_database.txt",ios::in | ios::out);

    while ( fin )
    {
        getline(fin,title);
        if(title == "-1")
        break;
        getline(fin,author);
        getline(fin,publication);
        getline(fin,isbn);
        getline(fin,issued_to);
        getline(fin,duedate);

        Book book;

        book.set_title(title);
        book.set_author(author);
        book.set_publication(publication);
        book.set_isbn(isbn);
        book.set_issued_to(issued_to);
        book.set_duedate(duedate);

        books.Add(book);

        if(issued_to == user->get_name())
        {
            my_books.push_back(book);
        }

    }

    fin.close();
    fin.clear();

    user_professor->set_fields(user, my_books, 0);

    return books;    
}

Book_Database create_book_database_librarian(){
    Book_Database books;

    fstream fin;
    string title, author, publication, isbn, issued_to, duedate;

    fin.open("book_database.txt",ios::in | ios::out);

    while ( fin )
    {
        getline(fin,title);
        if(title == "-1")
        break;
        getline(fin,author);
        getline(fin,publication);
        getline(fin,isbn);
        getline(fin,issued_to);
        getline(fin,duedate);

        Book book;

        book.set_title(title);
        book.set_author(author);
        book.set_publication(publication);
        book.set_isbn(isbn);
        book.set_issued_to(issued_to);
        book.set_duedate(duedate);

        books.Add(book);

    }

    fin.close();
    fin.clear();

    return books;    
}

int student_action(){
    int act;
    
    printf("Choose Your Action:\n1. Show all the Books\n2. Show all the Books issued to me\n3. Issue a Book \n4. Show Fine Amount\n5. Clear Fine Amount\n6. Logout\n7. Exit\n>>Enter Your Action: ");
    cin >> act;
    getline(cin,waste);
    
    return act;
}

int professor_action(){
    int act;

    printf("Choose Your Action:\n1. Show all the Books\n2. Show all the Books issued to me\n3. Issue a Book \n4. Show Fine Amount\n5. Clear Fine Amount\n6. Logout\n7. Exit\n>>Enter Your Action: ");
    cin >> act;
    getline(cin,waste);

    return act;
}

int librarian_action(){
    int act;

    printf("Choose Your Action:\n1. Show all the Books\n2. Show all the Users\n3. Username of Book issued to\n4. Books issued to Username\n5. Add Book\n6. Update Book\n7. Delete Book\n8. Add User\n9. Update User\n10. Delete User\n11. Logout\n12. Exit\n>>Enter Your Action: ");
    cin >> act;

    getline(cin,waste);

    return act;
}

void update_databases(Book_Database books, User_Database users){
    fstream fout;

    fout.open("database/book_database.txt",ios::trunc | ios::out | ios::in);

    vector <Book> v = books.get_book_list();

    for(int i=0; i < v.size(); i++)
    {
        fout << v[i].get_title() << endl;
        fout << v[i].get_author() << endl;
        fout << v[i].get_publication() << endl;
        fout << v[i].get_isbn() << endl;
        fout << v[i].get_issued_to() << endl;
        fout << v[i].Show_duedate() << endl;
    }

    fout << "-1" << endl;

    fout.close();
    fout.clear();

    fout.open("database/user_database.txt",ios::trunc | ios::out | ios::in);

    vector <User> u = users.get_user_list();

    for(int i=0; i < u.size(); i++)
    {
        fout << u[i].get_name() << endl;
        fout << u[i].get_password() << endl;
        fout << u[i].get_id() << endl;
    }

    fout << "-1" << endl;

    fout.close();
    fout.clear();

    return;
}

int main(){
    string username, password, id;

    User user;

    User_Database users;
    users = create_user_database();

    printf("*******LIBRARY MANAGEMENT SYSTEM*******\n");
login: 
    printf(">>Enter Username: ");
    getline(cin,username);
    printf(">>Enter Password: ");
    getline(cin,password);
    printf("Choose Your Role To Login:\n1. Student\n2. Professor\n3. Librarian\n>>Enter Your Choice: ");
    getline(cin,id);

    user.set_name(username);
    user.set_password(password);
    user.set_id(id);

    if(users.Search(user))
    cout << "Logged In Successfully...\n";
    else
    {
        cout << "INVALID LOGIN CREDENTIALS!!!\n";
        goto login;
    }
    
    if( user.get_id() == "1")
    {
        Student user_student;
        
        Book_Database books;
        books = create_book_database_student(&user, &user_student);

    student:
        int act = student_action();
        if(act == 1)
        {
            books.Display();
            goto student;
        }
        else if(act == 2)
        {
            vector <Book> v = user_student.get_my_books();
            if(v.size() == 0)
            cout << "No Books are Issued to You...\n";
            else
            {
                for(int i=0; i < v.size(); i++)
                {
                    cout << i+1 << ". Book Title: " << v[i].get_title() << endl;
                    cout << "   Book Author: " << v[i].get_author() << endl;
                    cout << "   Book Publication: " << v[i].get_publication() << endl;
                    cout << "   Book ISBN: " << v[i].get_isbn() << endl;
                    cout << "   Book DueDate: " << v[i].Show_duedate() << endl;
                }
            }
            goto student;
        }
        else if(act == 3)
        {
            if(user_student.get_my_books().size() < 5)
            {
                string book_isbn;
                Book book;
                cout << "Enter Book ISBN: ";
                getline(cin,book_isbn);
                int i=books.Search(book_isbn);
                if( i == 0)
                {
                    cout << "Book Not Found!!!\n";
                    goto student;
                }
                else
                {
                    book = books.get_book(i);
                    if( book.Book_Request(user_student.get_name(), 1) )
                    {
                        user_student.Add_book(book);
                        books.Update(i,book);
                        update = 1;
                    }
                    goto student;
                }
            }
            else
            {
                cout << "Maximum Number of Books have already been Issued!!!\n";
            }
        }
        else if(act == 4)
        {
            user_student.Calculate_fine();
            cout << "Your Fine_Amount: " << user_student.get_fine() << endl;
            goto student;
        }
        else if(act == 5)
        {
            user_student.Clear_fine_amount(&books);
            cout << "Your Fines are now Cleared...\n" ;
            goto student;
        }
        else if(act == 6)
        {
            cout << "Logged Out..\n";
            goto login;
        }
        else
        {
            if (update)
            update_databases(books, users);
        }
    }

    else if( user.get_id() == "2" )
    {
        Professor user_professor;
        
        Book_Database books;
        books = create_book_database_professor(&user, &user_professor);

    professor:
        int act = professor_action();
        if(act == 1)
        {
            books.Display();
            goto professor;
        }
        else if(act == 2)
        {
            vector <Book> v = user_professor.get_my_books();
            if(v.size() == 0)
            cout << "No Books are Issued to You...\n";
            else
            {
                for(int i=0; i < v.size(); i++)
                {
                    cout << i+1 << ". Book Title: " << v[i].get_title() << endl;
                    cout << "   Book Author: " << v[i].get_author() << endl;
                    cout << "   Book Publication: " << v[i].get_publication() << endl;
                    cout << "   Book ISBN: " << v[i].get_isbn() << endl;
                    cout << "   Book DueDate: " << v[i].Show_duedate() << endl;
                }
            }
            goto professor;
        }
        else if(act == 3)
        {
            string book_isbn;
            Book book;
            cout << "Enter Book ISBN: ";
            getline(cin,book_isbn);
            int i=books.Search(book_isbn);
            if( i == 0)
            {
                cout << "Book Not Found!!!\n";
                goto professor;
            }
            else
            {
                book = books.get_book(i);
                if( book.Book_Request(user_professor.get_name(), 2) )
                {
                    user_professor.Add_book(book);
                    books.Update(i,book);
                    update = 1;
                }
                goto professor;
            }
        }
        else if(act == 4)
        {
            user_professor.Calculate_fine();
            cout << "Your Fine_Amount: " << user_professor.get_fine() << endl;
            goto professor;
        }
        else if(act == 6)
        {
            cout << "Logged Out..\n";
            goto login;
        }
        else
        {
            if(update)
            update_databases(books, users);
        }
    }

    else
    {
        Book_Database books;
        books = create_book_database_librarian();

    librarian:
        int act = librarian_action();
        if (act == 1)
        {
            books.Display();
            goto librarian;
        }
        else if (act == 2)
        {
            users.Display();
            goto librarian;
        }
        else if(act == 3)
        {
            string isbn;
            cout << ">>Enter Book ISBN: " ;
            getline(cin,isbn);
            int index = books.Search(isbn);
            if ( index )
            {
                Book book = books.get_book(index);
                cout << "This Book is Issued to: " << book.get_issued_to() << endl ;
                cout << "DueDate: " << book.Show_duedate() << endl;
                goto librarian;
            }
            else
            {
                cout << "BOOK NOT FOUND!!!\n" ;
                goto librarian;
            }
        }
        else if (act == 4)
        {
            string n;
            
            cout << ">>Enter Username: " ;
            getline(cin,n);

            if ( users.Unique_Username(n) )
            {
                cout << "USERNAME DOES NOT EXISTS!!!\n" ;
                goto librarian;
            }

            else
            {
                vector <Book> bl ;
                bl = books.get_book_list();
                int j=1;
                for (int i=0; i<bl.size(); i++)
                {
                    if(bl[i].get_issued_to() == n)
                    {
                        cout << j << ". Book Title: " << bl[i].get_title() << endl;
                        cout << "   Book Author: " << bl[i].get_author() << endl;
                        cout << "   Book Publication: " << bl[i].get_publication() << endl;
                        cout << "   Book ISBN: " << bl[i].get_isbn() << endl;
                        cout << "   DueDate: " << bl[i].Show_duedate() << endl;
                        j++;
                    }
                }
                if( j == 1)
                {
                    cout << "No Book has been Issued to this User...\n" ;
                }
                goto librarian;
            }
        }
        else if (act == 5)
        {
            string title, author, publication, isbn, issued_to, duedate;
            cout << ">>Enter Book Title: " ;
            getline(cin,title);
            cout << ">>Enter Book Author: " ;
            getline(cin,author);
            cout << ">>Enter Book Publication: " ;
            getline(cin,publication);
            cout << ">>Enter Book ISBN: " ;
            getline(cin,isbn);
            if( (books.Search(isbn)) )
            {
                cout << "Book Already Exist!!!\n" ;
                goto librarian;
            }
            else
            {
                Book book;
                cout << ">>Book Issed To: " ;
                getline(cin,issued_to);
                cout << ">>Book DueDate: " ;
                getline(cin,duedate);

                book.set_title(title);
                book.set_author(author);
                book.set_publication(publication);
                book.set_isbn(isbn);
                book.set_issued_to(issued_to);
                book.set_duedate(duedate);

                books.Add(book);

                cout << "Book Added Successfully...\n";

                update = 1;

                goto librarian;
            }
        }
        else if(act == 6)
        {
            int index;
            string title, author, publication, isbn, issued_to, duedate;
            cout << ">>Enter Book Index: " ;
            cin >> index;
            getline(cin,waste);
            cout << ">>Enter Update_Book Title: " ;
            getline(cin,title);
            cout << ">>Enter Update_Book Author: " ;
            getline(cin,author);
            cout << ">>Enter Update_Book Publication: " ;
            getline(cin,publication);
            cout << ">>Enter Update_Book ISBN: " ;
            getline(cin,isbn);
            cout << ">>Book Issed To: " ;
            getline(cin,issued_to);
            cout << ">>Book DueDate: " ;
            getline(cin,duedate);

            Book book;

            book.set_title(title);
            book.set_author(author);
            book.set_publication(publication);
            book.set_isbn(isbn);
            book.set_issued_to(issued_to);
            book.set_duedate(duedate);

            books.Update(index, book);

            goto librarian;
        }
        else if (act == 7)
        {
            int index;
            cout << ">>Enter Book Index: " ;
            cin >> index;
            getline(cin,waste);

            books.Delete(index);

            goto librarian;
        }
        else if (act == 8)
        {
            string n, i, p;
            cout << ">>Enter Username: ";
            getline(cin,n);
            if ( !(users.Unique_Username(n)) )
            {
                cout << "User Already Exists!!!" <<  endl;
                goto librarian;
            }
            else
            {
                cout << ">>Enter Password: ";
                getline(cin,p);
                cout << ">>Enter Id: ";
                getline(cin,i);

                User us;
                us.set_name(n);
                us.set_password(p);
                us.set_id(i);

                users.Add(us);
                update = 1;
                cout << "User Added Successfully...\n";

                goto librarian;
            }
        }
        else if(act == 9)
        {
            int index;
            string n, p, i;
            cout << ">>Enter User Index: " ;
            cin >> index;
            getline(cin,waste);
            cout << ">>Enter Updated UserName: " ;
            getline(cin,n);
            cout << ">>Enter Updated Password: " ;
            getline(cin,p);
            cout << ">>Enter Updated Id: " ;
            getline(cin,i);

            User us ;
            us.set_name(n);
            us.set_password(p);
            us.set_id(i);

            users.Update(index, us);

            goto librarian;

        }
        else if (act == 10)
        {
            int index;
            cout << ">>Enter User Index: " ;
            cin >> index;
            getline(cin,waste);

            users.Delete(index);

            goto librarian;
        }
        else if(act == 11)
        {
            cout << "Logged Out..\n";
            goto login;
        }
        else
        {
            if (update)
            update_databases(books, users);
        }
    }

    return 0;
}