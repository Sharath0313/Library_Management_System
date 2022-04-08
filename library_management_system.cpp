#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "class.h"
#include "common.h"
using namespace std;

User_Database create_user_database(){
    User_Database users;

    fstream fin;
    string name, password, id;

    fin.open("./Database/user_database.txt", ios::in | ios::out);

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

    fin.open("./Database/book_database.txt",ios::in | ios::out);

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

    fin.open("./Database/book_database.txt",ios::in | ios::out);

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

    fin.open("./Database/book_database.txt",ios::in | ios::out);

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
    
    printf("Choose Your Action:\n1. Show all the Books\n2. Show all the Books issued to me\n3. Issue a Book \n4. Submit Book\n5. Show Fine Amount\n6. Clear Fine Amount\n7. Logout\n8. Exit\n>>Enter Your Action: ");
    cin >> act;
    getline(cin,waste);
    
    return act;
}

int professor_action(){
    int act;

    printf("Choose Your Action:\n1. Show all the Books\n2. Show all the Books issued to me\n3. Issue a Book \n4. Submit Book\n5. Show Fine Amount\n6. Clear Fine Amount\n7. Logout\n8. Exit\n>>Enter Your Action: ");
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

    fout.open("./Database/book_database.txt",ios::trunc | ios::out | ios::in);

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

    fout.open("./Database/user_database.txt",ios::trunc | ios::out | ios::in);

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
            string isbn;
            cout << ">>Enter Book ISBN: " ;
            getline(cin,isbn);
            user_student.Submit_book(isbn,&books);
            goto student;
        }

        else if(act == 5)
        {
            user_student.Calculate_fine();
            cout << "Your Fine_Amount: " << user_student.get_fine() << endl;
            goto student;
        }

        else if(act == 6)
        {
            user_student.Clear_fine_amount(&books);
            cout << "Your Fines are now Cleared...\n" ;
            goto student;
        }

        else if(act == 7)
        {
            cout << "Logged Out..\n";
            if(update)
            update_databases(books, users);
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
            if( i == 0 )
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
            string isbn;
            cout << ">>Enter Book ISBN: " ;
            getline(cin,isbn);
            user_professor.Submit_book(isbn,&books);
            goto professor;
        }

        else if(act == 5)
        {
            user_professor.Calculate_fine();
            cout << "Your Fine_Amount: " << user_professor.get_fine() << endl;
            goto professor;
        }

        else if(act == 6)
        {
            user_professor.Clear_fine_amount(&books);
            cout << "Your Fines are now Cleared...\n" ;
            goto professor;
        }

        else if(act == 7)
        {
            cout << "Logged Out..\n";
            if(update)
            update_databases(books, users);
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

        else if(act == 2)
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

        else if(act == 4)
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

        else if(act == 5)
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

        else if(act == 7)
        {
            int index;
            cout << ">>Enter Book Index: " ;
            cin >> index;
            getline(cin,waste);

            books.Delete(index);

            goto librarian;
        }

        else if(act == 8)
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

        else if(act == 10)
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
            if(update)
            update_databases(books, users);
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