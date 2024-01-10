#include<iostream>
#include<vector>
#include<fstream>
#include"book.h"
#include"user.h"
#include<string>
#include<time.h>
using namespace std;
std::string joinStrings(const std::vector<std::string>& strings, char delimiter)
{
    string ans;

    for (int m = 0; m < strings.size() - 1; m++){
      ans += strings[m];
      ans += '+';
    }
    ans += strings[strings.size() - 1];
    return ans;
}
vector<string> split(string str, char del){
    //declaring temp string to store the curr "word" upto del
      string temp = "";
      vector<string> ans;
      for(int m=0; m<(int)str.size(); m++){
        // If cur char is not del, then append it to the cur "word", otherwise
          // you have completed the word, print it, and start a new word.
         if(str[m] != del){
            temp += str[m];
        }
          else{
            ans.push_back(temp);
              temp = "";
        }
    }
       
      ans.push_back(temp);
      return ans;
}
void getstudentdata(Studentlist& sl,ifstream& input)
{
    
    while(input.peek()!=EOF)
    {
      string str1;
    int value;
    borrowBook b;
    Student s;
    std::getline(input,str1);
      vector<string> temp=split(str1,'+');
      s.setfullname(temp[0]);
      s.setaccount(temp[1]);
      s.setpassword(temp[2]);
      s.setemail(temp[3]);
      s.setdateofbirth(temp[4]);
      s.setphone(temp[5]);
      s.setid(temp[6]);
      s.setstudentid(temp[7]);
      s.setclassname(temp[8]);
      value=stoi(temp[9]);
      if(value!=0)
      {
        int index=9;
        for(int i=0;i<value;i++)
        {
        int m=1;
        b.setauthor(temp[index+m]);
        m++;
        b.setbook(temp[index+m]);
        m++;
        b.setid(temp[index+m]);
        m++;
        b.setPublisher(temp[index+m]);
        m++;
        b.setyear(stoi(temp[index+m]));
        m++;
        b.setborrowedate(temp[index+m]);
        m++;
        b.setduedate(temp[index+m]);
        s.createborrowed(b);
        index=index+m;
        }
      }
      sl.adduser(s);
    }
}
void returnstudentdata(Studentlist& sl,ofstream& output)
{
    for(int i=0;i<sl.getnumb();i++)
    {
      vector<string> temp;
      Student s=sl.getstudent(i);
      temp.push_back(s.getfullname());
      temp.push_back(s.getaccount());
      temp.push_back(s.getpassword());
      temp.push_back(s.getmail());
      temp.push_back(s.getdateofbirth());
      temp.push_back(s.getphone());
      temp.push_back(s.getid());
      temp.push_back(s.getstudentid());
      temp.push_back(s.getclassname());
      temp.push_back(to_string(s.getnumberborrow()));
      if(s.getnumberborrow()!=0)
      {
        for(int i=0;i<s.getnumberborrow();i++)
        {
           borrowBook b=s.getborrowbook(i);
           temp.push_back(b.getauthor());
           temp.push_back(b.getbookname());
           temp.push_back(b.getid());
           temp.push_back(b.getpublisher());
           temp.push_back(to_string(b.getyear()));
           temp.push_back(b.getborrowdate());
           temp.push_back(b.getduedate());
        }
      }
       string str=joinStrings(temp,'+');
       output<<str<<endl;
    }
}
void getbookdata(BookLibrary& bl,ifstream& input)
{
  while(input.peek()!=EOF)
  {
    string str;
    Book b;
    std::getline(input,str);
    vector<string> temp=split(str,'+');
    b.setauthor(temp[0]);
    b.setbook(temp[1]);
    b.setPublisher(temp[2]);
    b.setid(temp[3]);
    b.setquantity(stoi(temp[4]));
    b.setyear(stoi(temp[5]));
    bl.addbook(b);
  }
}
void returnbookdata(BookLibrary& bl, ofstream& output)
{
  for(int i=0;i<bl.getnumb();i++)
  {
    vector<string> temp;
    Book b=bl.getbook(i);
    temp.push_back(b.getauthor());
    temp.push_back(b.getbookname());
    temp.push_back(b.getpublisher());
    temp.push_back(b.getid());
    temp.push_back(to_string(b.getquatity()));
    temp.push_back(to_string(b.getyear()));
    string str=joinStrings(temp,'+');
    output<<str<<endl;
  }
}
void displaymenu()
{
    std::cout<<"_______________________Welcome_______________________"<<endl;
    std::cout<<"Please choose option: "<<endl;
    std::cout<<"1.Student"<<endl;
    std::cout<<"2.Librarian"<<endl;
    std::cout<<"3.Escape"<<endl;
}
int main()
{    
    BookLibrary bl;
    Studentlist sl;
    ifstream input;
    ifstream input2;
    ofstream output;
    ofstream output2;
    
    input2.open("outputbookdata.txt");
    input.open("studentdata.txt");
    getstudentdata(sl,input);
    getbookdata(bl,input2);
    while(1)
    {
        int value;
        int quantityValue;
        vector<Book*> find;
        vector<Student*> findstudent;
        Student curr;
        Book currbook;
        Librarian currlibrarian;
        int choice;
        string str1;
        displaymenu();
        std::cout<<"Your choice is: ";
        choice=getValidInput(1,3);
        switch (choice)
        {
        case 1:/*Student menu*/
        while(1)
        {
            int choice;
            int check=0;
            std::cout<<"------------------Student menu------------------"<<endl;
            std::cout<<"1.Log into existing account"<<endl;
            std::cout<<"2.Create new account"<<endl;
            std::cout<<"3.Escape"<<endl;
            std::cout<<"Your choice is: ";
            choice=getValidInput(1,3);
            switch (choice)
               {
                 case 1:
                  std::cout<<"Enter your account: ";
                  std::getline(cin,str1);
                  if(sl.finduserbyaccount(str1)==NULL)
                  {
                    std::cout<<"Account does not exist"<<endl;
                    break;
                  }
                  curr=*(sl.finduserbyaccount(str1));
                     do
                    {
                     std::cout<<"Enter your password: ";
                     std::getline(cin,str1);
                     if(str1!=curr.getpassword())
                     {
                        std::cout<<"Incorrect password"<<endl;
                        std::cout<<"Continue? 1.Yes 2.No"<<endl;
                        std::cout<<"Your choice is: ";
                        choice=getValidInput(1,2);
                        if(choice==1)
                        {
                            check=0;
                            continue;
                        }
                        else
                        {
                            check=1;
                            break;
                        }
                     }
                   }while(str1!=curr.getpassword());
                  if(check==1)
                  break;
                  while(1)
                  {
                    std::cout<<"------------------Student menu------------------"<<endl;
                    std::cout<<"Choose your option: "<<endl;
                    std::cout<<"1. Borrow book"<<endl;
                    std::cout<<"2. Return book"<<endl;
                    std::cout<<"3. Show book id"<<endl;
                    std::cout<<"4. Search book"<<endl;
                    std::cout<<"5. Check borrowed book"<<endl;
                    std::cout<<"6. Update information"<<endl;
                    std::cout<<"7. Change password"<<endl;
                    std::cout<<"8. Log out"<<endl;
                    std::cout<<"Your option is: ";
                    choice=getValidInput(1,8);
                    switch (choice)
                    {
                    case 1:
                      curr.borrowedBook(bl);
                      std::cout<<"Your borrowed books are:"<<endl;
                      curr.checkBook();

                    break;
                    case 2:
                      curr.returnBook(bl);
                      curr.checkBook();
                      break;
                    case 3:
                       for(int i=0;i<bl.getnumb();i++)
                        {
                          Book t=(bl.getbook(i));
                          std::cout<<i+1<<". Book name: "<<t.getbookname()<<" ID is: "<<t.getid()<<endl;
                        }
                    case 4:
                        cout<<"Enter method: "<<endl;
                        cout<<"1. By book's name"<<endl;
                        cout<<"2. By author's name"<<endl;
                        cout<<"Your option is: ";
                        choice=getValidInput(1,2);
                        switch(choice)
                        {
                            case 1:
                            std::cout<<"Enter book's name: ";
                            std::getline(cin,str1);
                            find=bl.findbookbyname(str1);
                            if(find.size()==0)
                            std::cout<<"Book not exist"<<endl;
                            else
                           {
                            std::cout<<"Result:"<<endl;
                            for(int i=0;i<find.size();i++)
                           {
                             std::cout<<i+1<<". "<<(*find[i]).getbookname()<<" by "<<(*find[i]).getauthor()<<endl;
                            }
                            std::cout<<"Choose your book"<<endl;
                            choice=getValidInput(1,find.size());
                        
                            find[choice-1]->Print();
                            }
                            break;
                            case 2:
                            std::cout<<"Enter author's name: ";
                            std::getline(cin,str1);
                            find=bl.findbookbyauthor(str1);
                            if(find.size()==0)
                            std::cout<<"Author not exist"<<endl;
                            else
                           {
                            std::cout<<"Result:"<<endl;
                            for(int i=0;i<find.size();i++)
                            {
                             std::cout<<i+1<<". "<<(*find[i]).getbookname()<<" by "<<(*find[i]).getauthor()<<endl;
                            }
                            std::cout<<"Choose your book"<<endl;
                            choice=getValidInput(1,find.size());
                            find[choice-1]->Print();
                            break;
                          }
                        }
                        break;
                    case 5:
                    curr.checkBook();
                    break;
                    case 6:
                     curr.updateinformation();
                     break;
                    case 7:
                     curr.changepassword();
                     break;
                     default:
                    break;
                    }
                    if(choice==8)
                    break;
                  }
                  *(sl.finduserbyaccount(curr.getaccount()))=curr;
                  break;

                 case 2:
                    do
                {
                std::cout<<"Enter your account: ";
                std::getline(cin, str1);
                if(sl.finduserbyaccount(str1)!=NULL)
                {
                 std::cout<<endl<<"Student account already exist";
                }
                }while(sl.finduserbyaccount(str1)!=NULL);
                 
                curr.setaccount(str1);
                    std::cout<<endl<<"Enter your password: ";
                    std::getline(cin,str1);
                    curr.setpassword(str1);
                    do
                {
                std::cout << endl<<"Enter your student ID: ";
                std::getline(cin, str1);
                findstudent=sl.finduserbyid(str1);
                if(findstudent.size()!=0)
                {
                 std::cout<<endl<<"Student id already exist"<<endl;
                }
                 curr.setstudentid(str1);
                }while(findstudent.size()!=0);
                   std::cout<<endl<<"Enter your full name: ";
                   std::getline(cin,str1);
                    curr.setfullname(str1);
                    std::cout<<endl<<"Enter your phone number: ";
                    std::getline(cin,str1);
                    curr.setphone(str1);
                    std::cout<<endl<<"Enter your citizen id: ";
                    std::getline(cin,str1);
                    curr.setid(str1);
                    std::cout<<endl<<"Enter your email: ";
                    std::getline(cin,str1);
                    curr.setemail(str1);
                    std::cout<<endl<<"Enter your date of birth (yyyy.mm.dd): ";
                    std::getline(cin,str1);
                    curr.setdateofbirth(str1);
                    std::cout<<endl<<"Enter your class name: ";
                    std::getline(cin,str1);
                    curr.setclassname(str1);
                    
                   
                    
                    sl.adduser(curr);
                    std::cout<<"Create succucess"<<endl;
                    break;
                default:
                     break;
               }
            if(choice==3)
                break;
        }
        break;
       case 2: //librarian
       while(1)
       {
        int check=0;
        do
        {
          // login
        std::cout<<"------------------Librarian menu------------------"<<endl;
         std::cout<<"Enter Librarian account: ";
         std::getline(cin,str1);
         if(str1!="Librarian")
        {
         std::cout<<"Wrong account"<<endl;
         std::cout<<"Continue? 1.Yes 2.No"<<endl;
         std::cout<<"Your choice is: ";
         choice=getValidInput(1,2);
       
         if(choice==1)
        {
         check=0;
         continue;
        }
         else
        {
         check=1;
         break;
        }
        }
        }while(str1!="Librarian");
         if(check==1)
          break;       
        do
        {
         std::cout<<"Enter Librarian password: ";
         std::getline(cin,str1);
         if(str1!="123")
        {
         std::cout<<"Wrong password"<<endl;
         std::cout<<"Continue? 1.Yes 2.No"<<endl;
         std::cout<<"Your choice is: ";
         choice=getValidInput(1,2);
         
         if(choice==1)
        {
         check=0;
         continue;
        }
         else
        {
         check=1;
         break;
        }
        }
        }while(str1!=currlibrarian.getpassword());
         if(check==1)
          break;

          //Librarian menu
         while(1)
         {
            std::cout<<"------------------Librarian menu------------------"<<endl;
            std::cout<<"Choose your option:"<<endl;
            std::cout<<"1.Add student account"<<endl;
            std::cout<<"2.Delete student account"<<endl;
            std::cout<<"3.Add book"<<endl;
            std::cout<<"4.Delete book"<<endl;
            std::cout<<"5.Show student information"<<endl;
            std::cout<<"6.Show book information"<<endl;
            std::cout<<"7.Change book information"<<endl;
            std::cout<<"8.Change student information"<<endl;
            std::cout<<"9.Show total number of books"<<endl;
            std::cout<<"10.Log out"<<endl;
            std::cout<<"Your option is: ";
            choice=getValidInput(1,10);
           
            switch (choice)
            {
                case 1:

        // Get information from the user for the new student (including Person attributes)
                do
                {
                std::cout << "Enter student ID: ";
                std::getline(cin, str1);
                findstudent=sl.finduserbyid(str1);
                if(findstudent.size()!=0)
                {
                 std::cout<<"Student id already exist"<<endl;
                }
                 curr.setstudentid(str1);
                }while(findstudent.size()!=0);
                
               std::cout<<"Enter student's citizen id: ";
               std::getline(cin,str1);
               curr.setid(str1);
               std::cout << "Enter student full name: ";
               std::getline(cin, str1);
               curr.setfullname(str1);

               std::cout << "Enter student email: ";
               std::getline(cin, str1);
               curr.setemail(str1);

               std::cout << "Enter student phone: ";
               std::getline(cin, str1);
               curr.setphone(str1);

               std::cout << "Enter student date of birth (yyyy.mm.dd): ";
               std::getline(cin, str1);
               curr.setdateofbirth(str1);

               do
                {
                std::cout << "Enter student account: ";
                std::getline(cin, str1);
                if(sl.finduserbyaccount(str1)!=NULL)
                {
                 std::cout<<"Student account already exist"<<endl;
                }
                }while(sl.finduserbyaccount(str1)!=NULL);
                 
                curr.setaccount(str1);

               std::cout << "Enter student password: ";
               std::getline(cin, str1);
               curr.setpassword(str1);

               std::cout << "Enter student class name: ";
               std::getline(cin, str1);
               curr.setclassname(str1);

               
              // Clear the newline character from the input buffer
               
               

              

        // Add the new student to the list
               sl.adduser(curr);

               std::cout << "New student created successfully!" << endl;
                break;
            case 2:
                 std::cout<<"Choose method"<<endl;
                 std::cout<<"1.Delete by student id"<<endl;
                 std::cout<<"2.Delete by student account"<<endl;
                 choice=getValidInput(1,2);
               
                 switch (choice)
                 {
                 case 1/* constant-expression */:
                    std::cout<<"Enter student id: "<<endl;
                    std::getline(cin,str1);
                    findstudent=sl.finduserbyid(str1);
                    if(findstudent.size()==0)
                    {
                        std::cout<<"Student does not exist"<<endl;
                    }
                    else
                    {
                        sl.deleteuserbyid(str1);
                        std::cout<<"Delete success"<<endl;
                    }
                    break;
                 case 2:
                    std::cout<<"Enter student account: "<<endl;
                    std::getline(cin,str1);
                    if(sl.finduserbyaccount(str1)==NULL)
                    {
                        std::cout<<"Account does not exist"<<endl;
                    }
                    else
                    {
                        sl.deleteuserbyaccount(str1);
                        std::cout<<"Delete success"<<endl;
                    }
                    
                 
                 default:
                    break;
                 }
             break;
            case 3:
                do
                {
                std::cout << "Enter book ID: ";
                std::getline(cin, str1);
                find=bl.findbookbyid(str1);
                if(find.size()!=0)
                {
                 std::cout<<"Book already exist"<<endl;
                }
                }while(find.size()!=0);
                  currbook.setid(str1);
                  std::cout << "Enter book name: ";
                  std::getline(cin, str1);
                  currbook.setbook(str1);

                  std::cout << "Enter book author: ";
                  std::getline(cin, str1);
                  currbook.setauthor(str1);

                  std::cout << "Enter book publisher: ";
                  std::getline(cin, str1);
                  currbook.setPublisher(str1);

                  std::cout << "Enter book publication year: ";
                  value=getValidInput(1000,3000);
                  currbook.setyear(value);

                  std::cout << "Enter book quantity: ";
                  value=getValidInput(1,1000);
                    // Clear the newline character from the input buffer
                  currbook.setquantity(value);

                   // Add the new book to the library
                  bl.addbook(currbook);
             break;
            case 4:
             std::cout<<"Choose method"<<endl;
             std::cout<<"1.By book id"<<endl;
             std::cout<<"2.By book name"<<endl;
             std::cout<<"Your choice: ";
             choice=getValidInput(1,2);
             
             switch (choice)
             {
             case 1 /* constant-expression */:
                std::cout<<"Enter book id"<<endl;
                std::getline(cin,str1);
                find=bl.findbookbyid(str1);
                if(find.size()==0)
                {
                    std::cout<<"Book id does not exist"<<endl;
                }
                else
                {
                    bl.deletebookbyid(str1);
                }
                  /* code */
                break;
             case 2:
                std::cout<<"Enter book name"<<endl;
                std::getline(cin,str1);
                find=bl.findbookbyname(str1);
                if(find.size()==0)
                 std::cout<<"Book does not exist"<<endl;
                else
                {
                std::cout<<"Result is:"<<endl;
                for(int i=0;i<find.size();i++)
                {
                  std::cout<<i+1<<"."<<find[i]->getbookname()<<" ID:"<<find[i]->getid()<<endl;
                }
                 std::cout<<"Enter book index: ";
                 choice=getValidInput(1,find.size());
                 bl.deletebookbyid(find[choice-1]->getid());
                 std::cout<<"Delete success"<<endl;
                }
             default:
                break;
             }
             break;
            case 5:
              sl.Print();
              
             break;
            case 6:
             bl.Print();
             break;
            case 7:
             std::cout<<"Enter full name of student you want to update information: ";
             std::getline(cin,str1);
             findstudent=sl.finduserbyname(str1);
             if(findstudent.size()==0)
             {
                std::cout<<"Student not exist"<<endl;
             }
             else
             {
                for(int i=0;i<findstudent.size();i++)
                {
                    std::cout<<"1."<<endl;
                    findstudent[i]->Print();
                }
                std::cout<<"Enter index: ";
                choice=getValidInput(1,findstudent.size());
                
                findstudent[choice-1]->updateinformation();
             }
             break;
            case 8:
             std::cout<<"Enter name of the book you want to update information: ";
             std::getline(cin,str1);
             find=bl.findbookbyname(str1);
             if(find.size()==0)
             {
                std::cout<<"Book not exist"<<endl;
             }
             else
             {
                for(int i=0;i<find.size();i++)
                {
                    std::cout<<"1."<<endl;
                    find[i]->Print();
                }
                std::cout<<"Enter index: ";
                choice=getValidInput(1,find.size());
               
                find[choice-1]->updateBookInfo();
             }
             break;
            case 9:
             std::cout<<"Number of books: "<<bl.getnumb()<<endl;
             break;
            default:
                break;
            }
            if(choice==10)
             break;
         }
         break;   
       }
       break;
       default:
       break;
     }
     if(choice==3)
     break;
   } 
   output2.open("outputbookdata.txt");
   output.open("studentdata.txt");
   returnstudentdata(sl,output);
   returnbookdata(bl,output2);
     
    input.close();
    input2.close();
    output.close();
    output2.close();
}