#ifndef USER_INCLUDE
#define USER_INCLUDE
#include<iostream>
#include<string>
#include<vector>
#include"book.h"
#include <time.h>
using namespace std;

// findbook should be a function instead of member function because both librarian and students could use this

class borrowBook:public Book
{
    private:
    string borrowdate;//yyyy.mm.dd
    string duedate;
    public:
    string getborrowdate();
    string getduedate();
    void setborrowedate(string value);
    void setduedate(string value);
};
class Person
{
    private:
    string fullname;
    string id;
    string dateofbirth;
    string email;
    string account;
    string password;
    string phone;
    public:
    Person();
    string getphone();
    string getfullname();
    string getid();
    string getdateofbirth();
    string getmail();
    string getaccount();
    string getpassword();
    void setphone(string value);
    void setfullname(string value);
    void setid(string value);
    void setdateofbirth(string value);
    void setemail(string value);
    void setaccount(string value);
    void setpassword(string value);
     void changepassword(); // this will update password (require to confirm old one)
     virtual void Print()
     {
        std::cout<<getaccount()<<endl;
        std::cout<<getdateofbirth()<<endl;
        std::cout<<getfullname()<<endl;
        std::cout<<getid()<<endl;
        std::cout<<getphone()<<endl;
     }
};

class Student:public Person
{
    private:
    string student_id;
    string class_name;
    int cohort;
    string school;
    string department;
    vector<borrowBook> borrowed;
    public:
    Student();
    borrowBook getborrowbook(int i)
    {
        return borrowed[i];
    }
    void createborrowed(borrowBook book)
    {
        borrowed.push_back(book);
    }
    int getnumberborrow()
    {
        return borrowed.size();
    }
    string getstudentid();
    string getclassname();
    int getcohort();
    string getschool();
    string getdepartment();
    void setstudentid(string value);
    void setclassname(string value);
    void setcohort(int value);
    void setschool(string value);
    void setdepartment(string value);
    void updateinformation(); // this will update information (not include account,password) base on user's keyboard input
    void borrowedBook(BookLibrary& b); // this will update borrowed (+)
    void returnBook(BookLibrary& b); // this will update borrowed (-)
    void checkBook();
    void Print()
    {
      std::cout<<"Student account is "<<getaccount()<<endl;
      std::cout<<"Student id is: "<<student_id<<endl;
      std::cout<<"Student fullname is: "<<getfullname()<<endl;
      std::cout<<"Borrowed books are: "<<endl;
      checkBook();
    }
};

class Librarian: public Person
{
   public:
   Librarian()
   {
     setpassword("123");
     setaccount("Librarian");
   };
};
class Studentlist
{
    private:
    vector<Student> u;
    public:
    Student getstudent(int i)
    {
        return u[i];
    }
    void adduser(Student value);
    void deleteuserbyaccount(string value);
    void deleteuserbyid(string studentid);
    vector<Student*> finduserbyname(string student_name);
    vector<Student*> finduserbyid(string id);
    Student* finduserbyaccount(string value);
    int getnumb();
    void Print();
};

string Person::getaccount()
{
    return account;
}
string Person ::getdateofbirth()
{
   return dateofbirth;
}
string Person::getfullname()
{
    return fullname;
}
string Person::getid()
{
    return id;
}
string Person::getpassword()
{
    return password;
}
string Person::getmail()
{
    return email;
}
string Person::getphone()
{
    return phone;
}
Person::Person():account(""),password(""),fullname(""),id(""),email(""),phone(""),dateofbirth("")
{}
void Person::setaccount(string value)
{
    account=value;
}
void Person::setdateofbirth(string value)
{
    dateofbirth=value;
}
void Person::setemail(string value)
{
    email=value;
}
void Person::setfullname(string value)
{
    fullname=value;
}
void Person::setid(string value)
{
    id=value;
}
void Person::setpassword(string value)
{
    password=value;
}
void Person::setphone(string value)
{
    phone=value;
}


//borrowBook
string borrowBook::getborrowdate()
{
    return borrowdate;
}
string borrowBook::getduedate()
{
    return duedate;
}
void borrowBook::setborrowedate(string value)
{
    borrowdate=value;
}
void borrowBook::setduedate(string value)
{
    duedate=value;
}



//Student
Student::Student()  
    {   
        class_name="";
        student_id = "";
        class_name = "";
        
    }
string Student::getclassname()
{
    return class_name;
}
string Student::getschool()
{
    return school;
}
int Student::getcohort()
{
    return cohort;
}
string Student::getdepartment()
{
    return department;
}
string Student::getstudentid()
{
    return student_id;
}
void Student::setclassname(string value)
{
    class_name=value;
}
void Student::setcohort(int value)
{
    cohort=value;
}
void Student::setdepartment(string value)
{
    department=value;
}
void Student::setschool(string value)
{
    school=value;
}
void Student::setstudentid(string value)
{
    student_id=value;
}
void Student::updateinformation()
{
    string value;
    std::cout<<"Enter new name: ";
    std::getline(std::cin,value);
    setfullname(value);
    std::cout<<"Enter new email: ";
    std::getline(std::cin,value);
    setemail(value);
    std::cout<<"Enter new phone: ";
    std::getline(std::cin,value);
    setphone(value);
    std::cout<<"Enter new date of birth (yyyy.mm.dd): ";
    std::getline(std::cin,value);
    setdateofbirth(value);
    
}
void Student::borrowedBook(BookLibrary& b)
{
    time_t curtime;
    vector<Book*> booklist;
    borrowBook newbook;
    Book bb;
    string value;
    int c;
    int choice;
    std::cout<<"Choose method"<<endl;
    std::cout<<"1.By name"<<endl;
    std::cout<<"2.By author"<<endl;
    choice=getValidInput(1,2);
    switch (choice)
    {
    case 1:
        std::cout<<"Enter book name: ";
        std::getline(std::cin,value);
        booklist=b.findbookbyname(value);
        if(booklist.size()==0)
         {
           std::cout<<"Book does not exist"<<endl;
         }
        else
        {
        std::cout<<"Result is:"<<endl;
        for(int i=0;i<booklist.size();i++)
        {
            std::cout<<i+1<<"."<<(*booklist[i]).getbookname()<<" by "<<(*booklist[i]).getauthor()<<" Published year: "<<(*booklist[i]).getyear()<<endl;
        }
        std::cout<<"Choose your book by enter index: ";
        c=getValidInput(1,booklist.size());
        bb=(*booklist[c-1]);
        if(bb.getquatity()<1)
         {
            std::cout<<"Run out of book"<<endl;
            break;
         }
        (*booklist[c-1]).setquantity(bb.getquatity()-1);
        newbook.setauthor(bb.getauthor());
        newbook.setbook(bb.getbookname());
        newbook.setid(bb.getid());
        newbook.setPublisher(bb.getpublisher());
        newbook.setyear(bb.getyear());
        time(&curtime);
        string t=ctime(&curtime);
        t[t.size()-1]='.';

        newbook.setborrowedate(t);
        curtime=curtime+1814400;
        t=ctime(&curtime);
        t[t.size()-1]='.';
        newbook.setduedate(t);
        borrowed.push_back(newbook);
        std::cout<<"Borrow succesfully"<<endl;
        }
        break;
    case 2:
        std::cout<<"Enter name of author: ";
        std::getline(std::cin,value);
        booklist=b.findbookbyauthor(value);
        if(booklist.size()==0)
        {
            std::cout<<"Book does not exist"<<endl;
        }
        else
        {
        std::cout<<"Result is:"<<endl;
        for(int i=0;i<booklist.size();i++)
        {
            std::cout<<i+1<<"."<<(*booklist[i]).getbookname()<<" by "<<(*booklist[i]).getauthor()<<" Published year: "<<(*booklist[i]).getyear()<<endl;
        }
        std::cout<<"Choose your book by enter index: ";
        c=getValidInput(1,booklist.size());
        bb=(*booklist[c-1]);
        if(bb.getquatity()<1)
         {
            std::cout<<"Run out of book"<<endl;
            break;
         }
         (*booklist[c-1]).setquantity(bb.getquatity()-1);
        newbook.setauthor(bb.getauthor());
        newbook.setbook(bb.getbookname());
        newbook.setid(bb.getid());
        newbook.setPublisher(bb.getpublisher());
        newbook.setyear(bb.getyear());
         time(&curtime);
         string t=ctime(&curtime);
          t[t.size()-1]='.';
        newbook.setborrowedate(t);
        curtime=curtime+1814400;
        t=ctime(&curtime);
        t[t.size()-1]='.';
        newbook.setduedate(t);
        borrowed.push_back(newbook);
        break;
        }
    default:
        break;
    }
}
void Student::checkBook()
{
    if(borrowed.size()==0)
    {
        std::cout<<"No borrowed book"<<endl;
    }
    for(int i=0;i<borrowed.size();i++)
    {
        std::cout<<i+1<<". "<<borrowed[i].getbookname()<<" by "<<borrowed[i].getauthor()<<endl;
        std::cout<<" Date of borrowing: "<<borrowed[i].getborrowdate()<<endl;
        std::cout<<" Due date: "<<borrowed[i].getduedate()<<endl;
    }
}
void  Student::returnBook(BookLibrary& b)//should implement search by id
{
     if(borrowed.size()==0)
   {
    std::cout<<"No book to return"<<endl;
    return;
   }
   checkBook();
   vector<Book*> booklist;
   int c;
   do
   {
    std::cout<<"Choose book to return: ";
    c=getValidInput(1,borrowed.size());
    c=c-1;
    booklist=b.findbookbyname(borrowed[c].getbookname());
    (*booklist[0]).setquantity((*booklist[0]).getquatity()+1);
    vector<borrowBook>::iterator it;
    int count=0;
    for(it=borrowed.begin();it<borrowed.end();it++)
    {
        if(count=c-1)
        borrowed.erase(it);
        else
        count++;
    }
    std::cout<<"Return sucessfully"<<endl;
   } while (c>borrowed.size()||c<0);
}
void Person::changepassword()
{
    string newpass;
    std::cout<<"Enter new password: ";
    std::getline(std::cin,newpass);
    password=newpass;
    std::cout<<"Your new password is "<<password<<endl;
}
//
int Studentlist::getnumb()
{
    return u.size();
}
void Studentlist::Print()
{
    for(int i=0;i<u.size();i++)
    {
        u[i].Print();
        std::cout<<endl;
    }
}
void Studentlist::adduser(Student value)
{
    u.push_back(value);
}

void Studentlist::deleteuserbyid(string value)
{
   vector<Student>::iterator it;
   int index=-1;
   int count=0;
   for(it=u.begin();it<u.end();it++)
   {
    index++;
    if(u[index].getstudentid()==value)
    {
       u.erase(it);
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
void Studentlist::deleteuserbyaccount(string value)
{
  vector<Student>::iterator it;
   int index=-1;
   int count=0;
   for(it=u.begin();it<u.end();it++)
   {
    index++;
    if(u[index].getaccount()==value)
    {
       u.erase(it);
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
vector<Student*> Studentlist::finduserbyid(string value)
{
    vector<Student*> liststudent;
    for(int i=0;i<u.size();i++)
    {
        if(u[i].getstudentid()==value)
        {
            liststudent.push_back(&u[i]);
        }
    }
    return liststudent;
}
Student* Studentlist::finduserbyaccount(string value)
{
    Student* liststudent;
    int count=0;
    for(int i=0;i<u.size();i++)
    {
        if(u[i].getaccount()==value)
        {
            liststudent=&u[i];
            count++;
        }
    }
    if(count!=0)
    return liststudent;
    else
    return NULL;
}
vector<Student*> Studentlist::finduserbyname(string value)
{
    vector<Student*> liststudent;
    for(int i=0;i<u.size();i++)
    {
        if(u[i].getfullname()==value)
        {
            liststudent.push_back(&u[i]);
        }
    }
    return liststudent;
}
#endif