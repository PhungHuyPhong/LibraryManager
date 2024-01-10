#ifndef BOOK_INCLUDE
#define BOOK_INCLUDE
#include <iostream>
#include <string>
#include<vector>
#include <fstream>
using namespace std;
#include <ctype.h> 
#include<string>
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
int getValidInput(int low,int high)
{
    int value;
    int cond=1;
    do
    {
    string c;
    std::getline(std::cin,c);
    if(is_number(c))
    {
        value=stoi(c,0,10);
        if(value>=low&&value<=high)
         cond=0;
        else
         std::cout<<"out of range\n";
    }
    else
    std::cout<<"Invalid input\n";
    }while(cond);
    return value;
}


class Book
{
    private:
    string author;
    string book_name;
    string publisher;
    string bookid;
    int quantity;
    int yearPublisher;

    public:
    Book();
    string getnames();
    void setauthor(string value);
    void setbook(string value);
    void setyear(int value);
    void setPublisher(string value);
    void setquantity(int value);
    void setid(string value);
    void updateBookInfo();
    string getbookname();
    string getauthor();
    string getid();
    string getpublisher();
    int getquatity();
    int getyear();
    void Print();

};
class BookLibrary
{
    private:
    vector<Book> b;
    public:
    Book getbook(int i)
    {
        return b[i];
    }
    void addbook(Book existbook);
    void deletebookbyname(string book_name);
    void deletebookbyid(string bookid);
    vector<Book*> findbookbyname(string book_name);
    vector<Book*> findbookbyauthor(string author);
    vector<Book*> findbookbyid(string id);
    int getnumb();
    void Print();
};
Book::Book():author("No data"),book_name("No data"),publisher("No data"),bookid("No data"),quantity(0),yearPublisher(0)
{

}
// Class Book member function
 string Book::getnames()
 {
    return book_name+' '+author;
 }

 //class Book's mutator
void Book::setyear(int value)
{
   yearPublisher=value;
}
void Book::setquantity(int value)
{
    quantity=value;
}
void Book::setPublisher(string value)
{
    publisher=value;
}
void Book::setid(string value)
{
     bookid=value;
}
void Book::setbook(string value)
{
    book_name=value;
}
void Book::setauthor(string value)
{
    author=value;
}

//class Book's accesor
string Book::getauthor()
{
    return author;
}
string Book::getbookname()
{
    return book_name;
}
string Book::getid()
{
    return bookid;
}
string Book::getpublisher()
{
    return publisher;
}
int Book:: getquatity()
{   
    return quantity;
}
int Book::getyear()
{
    return yearPublisher;
}
void Book::Print()
{
    std::cout<<"Book name is "<<book_name<<endl;
    std::cout<<"Author is "<<author<<endl;
    std::cout<<"Publisher is "<<publisher<<endl;
    std::cout<<"Year of publisher is "<<yearPublisher<<endl;
    std::cout<<"Book id is "<<bookid<<endl;
    std::cout<<"The number of book is "<<quantity<<endl;
}
void Book::updateBookInfo() {
    string newValue;

    std::cout << "Enter new author: ";
    std::getline(std::cin, newValue);
    setauthor(newValue);

    std::cout << "Enter new book name: ";
    std::getline(std::cin, newValue);
    setbook(newValue);

    std::cout << "Enter new publisher: ";
    std::getline(std::cin, newValue);
    setPublisher(newValue);

    std::cout << "Enter new publication year: ";
    int newYear;
    newYear=getValidInput(0,3000);
 // Clear the newline character from the input buffer
    setyear(newYear);

    std::cout << "Enter new quantity: ";
    int newQuantity;
    newQuantity=getValidInput(1,1000);
    setquantity(newQuantity);

    std::cout << "Book information updated successfully!" << endl;
}

//Book library member function
int BookLibrary::getnumb()
{
    return b.size();
}
void BookLibrary::Print()
{
    for(int i=0;i<b.size();i++)
    {
        std::cout<<i+1<<"."<<endl;
        b[i].Print();
        std::cout<<endl;
    }
}
void BookLibrary::addbook(Book existbook)
{
    b.push_back(existbook);
}
void BookLibrary::deletebookbyid(string value)
{
   vector<Book>::iterator it;
   int index=-1;
   int count=0;
   for(it=b.begin();it<b.end();it++)
   {
    index++;
    if(b[index].getid()==value)
    {
       b.erase(it);
       std::cout<<"Delete successful"<<endl;
       count++;
       break;
    }
   }
   if(count==0)
   {
    std::cout<<"Not Found"<<endl;
   }
}
void BookLibrary::deletebookbyname(string value)
{
   vector<Book>::iterator it;
   int index=0;
   for(it=b.begin();it<b.end();it++)
   {
    index++;
    if(b[index].getbookname()==value)
    {
       b.erase(it);
       std::cout<<"Delete successful"<<endl;
       break;
    }
   else
   {
    std::cout<<"Not found"<<endl;
   }
   }
}
vector<Book*> BookLibrary::findbookbyauthor(string value)
{
    vector<Book*> booklist;
    for(int i=0;i<b.size();i++)
    {
        if(b[i].getauthor()==value)
        {
            booklist.push_back(&b[i]);
        }
    }
    return booklist;
}
vector<Book*> BookLibrary::findbookbyname(string value)
{
     vector<Book*> booklist;
    for(int i=0;i<b.size();i++)
    {
        if(b[i].getbookname()==value)
        {
            booklist.push_back(&b[i]);
        }
    }
    return booklist;
}
vector<Book*> BookLibrary::findbookbyid(string value)
{
    vector<Book*> booklist;
    for(int i=0;i<b.size();i++)
    {
        if(b[i].getid()==value)
        {
            booklist.push_back(&b[i]);
        }
    }
    return booklist;
}
#endif