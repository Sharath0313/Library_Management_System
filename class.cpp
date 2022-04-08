#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "class.h"
#include "common.h"
using namespace std;

int update = 0;
string waste;

void DatePlusDays( struct tm* date, int days )
{
    const time_t ONE_DAY = 24 * 60 * 60 ;

    time_t date_seconds = mktime( date ) + (days * ONE_DAY) ;

    *date = *localtime( &date_seconds ) ; ;
}

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

void Student::Submit_book(string isbn, Book_Database *books){
    int index = books->Search(isbn);
    int found = 0;
    if (index)
    {
        int i=0;
        while ( i<My_Books.size() )
        {
            if (My_Books[i].get_isbn() == isbn)
            {
                found = 1;
                time_t now = time(0);

                tm *date = localtime(&now);

                int y1 = 1900 + date->tm_year ;
                int d1 =  date->tm_mday ;
                int m1 = 1 + date->tm_mon ;

                string p, y="",d="",m="";
                int a=1;

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

                if (diff > 0)
                {
                    cout << "DueDate of the Book is Over.\nPlease Clear Fine to Submit the Book...\n";
                }

                else
                {
                    My_Books[i].set_issued_to("None");
                    My_Books[i].set_duedate("NA");
                    books->Update(index, My_Books[i]);
                    My_Books.erase(My_Books.begin() + i);
                    update = 1;
                    found = 1;
                    cout << "Book Submitted Successfully...\n" ;
                    continue;
                }
            }
            i = i+1;
        }
        if( found == 0)
        {
            cout << "You Don't Have that Book...\n" ;
        }
    }
    else
    {
        cout << "BOOK NOT FOUND!!!\n" ;
    }

    return;
}

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
        fine = fine + (5*diff);
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

void Professor::Submit_book(string isbn, Book_Database *books){
    int index = books->Search(isbn);
    int found = 0;
    if (index)
    {
        int i=0;
        while ( i<My_Books.size() )
        {
            if (My_Books[i].get_isbn() == isbn)
            {
                found = 1;
                time_t now = time(0);

                tm *date = localtime(&now);

                int y1 = 1900 + date->tm_year ;
                int d1 =  date->tm_mday ;
                int m1 = 1 + date->tm_mon ;

                string p, y="",d="",m="";
                int a=1;

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

                if (diff > 0)
                {
                    cout << "DueDate of the Book is Over.\nPlease Clear Fine to Submit the Book...\n";
                }

                else
                {
                    My_Books[i].set_issued_to("None");
                    My_Books[i].set_duedate("NA");
                    books->Update(index, My_Books[i]);
                    My_Books.erase(My_Books.begin() + i);
                    update = 1;
                    cout << "Book Submitted Successfully...\n" ;
                    continue;
                }
            }
            i = i+1;
        }
        if( found == 0)
        {
            cout << "You Don't Have that Book...\n" ;
        }
    }
    else
    {
        cout << "BOOK NOT FOUND!!!\n" ;
    }

    return;
}

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