#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

class Book
{
public:
    string title;
    string author;
    stack<string> availability;

    Book(string title, string author)
    {
        this->title = title;
        this->author = author;
        // Initial availability should not include the title itself
    }

    // Default constructor for reading from file
    Book() {}
};
class Member
{
public:
    string name;
    string department;
    string id;
    string phn;
    queue<string> borrow;
    Member(string name, string department, string id, string phn)
    {
        this->name = name;
        this->department = department;
        this->id = id;
        this->phn = phn;
    }
    Member() {}
};
vector<Book> Book_list;
list<Member> Member_list;
// File Functions
void writeBookListToFile(vector<Book> &myList, string fileName)
{
    ofstream file(fileName, ios::out); // Use ios::out to truncate the file and write afresh
    if (!file)
    {
        cout << "Error opening file" << endl;
        return;
    }

    for (auto &book : myList)
    {
        file << book.title << "," << book.author << ",";
        stack<string> tempStack = book.availability;
        while (!tempStack.empty())
        {
            file << tempStack.top() << ",";
            tempStack.pop();
        }
        file << '\n';
    }

    file.close();
}

void readBookListFromFile(vector<Book> &myList, string filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Error opening file: " << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);

        string title, author;
        getline(ss, title, ',');  // Read until the next quote
        getline(ss, author, ','); // Read until the next quote
        Book book(title, author);

        string availability;
        stack<string> tempStack;
        while (getline(ss, availability, ','))
        {
            tempStack.push(availability);
        }

        while (!tempStack.empty())
        {
            book.availability.push(tempStack.top());
            tempStack.pop();
        }

        myList.push_back(book);
    }

    file.close();
}
// for member
void writeMemberListToFile(list<Member> &myList, string fileName)
{
    ofstream file(fileName, ios::out); // Use ios::out to truncate the file and write afresh
    if (!file)
    {
        cout << "Error opening file" << endl;
        return;
    }

    for (auto &member : myList)
    {
        file << member.name << "," << member.department << "," << member.id << "," << member.phn << ",";
        queue<string> tempQueue = member.borrow;
        while (!tempQueue.empty())
        {
            file << tempQueue.front() << ",";
            tempQueue.pop();
        }
        file << '\n';
    }

    file.close();
}
void readMemberListFromFile(list<Member> &myList, string filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Error opening file: " << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string name, department, id_str, phn_str;
        // ss >> name >> department;
        getline(ss, name, ',');
        getline(ss, department, ',');
        getline(ss, id_str, ',');
        getline(ss, phn_str, ',');

        // cout<<id_str<<endl<<phn_str<<endl;

        Member member(name, department, id_str, phn_str);

        string availability;
        queue<string> tempQueue;
        while (getline(ss, availability, ','))
        {
            tempQueue.push(availability);
        }

        while (!tempQueue.empty())
        {
            member.borrow.push(tempQueue.front());
            tempQueue.pop();
        }

        myList.push_back(member);
    }

    file.close();
}
void add_book()
{
    cout << "\t\t\t\t\t\t====================\n";
    cout << "\t\t\t\t\t\tAdd Book Information\n";
    cout << "\t\t\t\t\t\t====================\n";
    cout << "\n\t\t\t\t\tEnter Book Name: ";
    cin.ignore();
    string name, writer;
    getline(cin, name);
    cout << "\t\t\t\t\tEnter Book Author: ";
    getline(cin, writer);

    bool found = false;
    for (auto &book : Book_list)
    {
        if (book.title == name)
        {
            book.availability.push(name);
            found = true;
            break;
        }
    }

    if (!found)
    {
        Book newBook(name, writer);
        newBook.availability.push("Available"); // Only the availability status, not the title itself
        Book_list.push_back(newBook);
    }

    cout << "\t\t\t\t\t=======================\n";
    cout << "\t\t\t\t\tBook added Successfully\n";
}

void search_book()
{
    if (Book_list.empty())
    {
        cout << "\n\t\t\t\t\t=======================================\n";
        cout << "\t\t\t\t\tThere are No books Available for search\n";
        cout << "\t\t\t\t\t=======================================\n";
    }
    else
    {
        cout << "\n\t\t\t\t\tPlease enter book title: ";
        string need;
        cin.ignore();
        getline(cin, need);

        for (auto &book : Book_list)
        {
            if (book.title == need)
            {
                cout << "\t\t\t\t\tBook information:\n";
                cout << "\t\t\t\t\t-----------------\n";
                cout << "\t\t\t\t\tBook title: " << book.title << endl;
                cout << "\t\t\t\t\tBook author: " << book.author << endl;
                cout << "\t\t\t\t\tBook availability: " << (book.availability.empty() ? "Not available" : "Available") << endl;
                cout << "\t\t\t\t\t---------------------------\n";
                return;
            }
        }
        cout << "\t\t\t\t\tSorry, this book is not available in the library\n";
    }
}
void addMember()
{
    cout << "\t\t\t\t\t\t====================\n";
    cout << "\t\t\t\t\t\tAdd Member Information\n";
    cout << "\t\t\t\t\t\t====================\n";
    cout << "\n\t\t\t\t\tEnter Member Name: ";
    string name, department;
    string id, phn;
    cin.ignore();
    getline(cin, name);
    cout << "\t\t\t\t\tEnter Member Department: ";
    getline(cin, department);

    cout << "\t\t\t\t\tEnter Member id: ";
    getline(cin, id);
    cout << "\t\t\t\t\tEnter Member Phone Number: ";
    getline(cin, phn);

    Member newMember(name, department, id, phn);

    Member_list.push_back(newMember);

    cout << "\t\t\t\t\t=======================\n";
    cout << "\t\t\t\t\tMember added Successfully\n";
}

int main()
{
    readBookListFromFile(Book_list, "book.txt");
    readMemberListFromFile(Member_list, "member.txt");
    int ch = 0;
    while (ch != 6)
    {
        cout << "\t\t\t\t\t=====================================================\n\t\t\t\t\tLibrary management system of Sheikh Hasina University\n\t\t\t\t\t=====================================================\n"
             << endl;
        cout << "\t\t\t\t\t   For Adding New Books select____________________1" << endl;
        cout << "\t\t\t\t\t   For Searching Books select_____________________2" << endl;
        cout << "\t\t\t\t\t   For Adding new member select___________________3" << endl;
        cout << "\t\t\t\t\t   For Borrowing Books____________________________4" << endl;
        cout << "\t\t\t\t\t   For Member Reports_____________________________5" << endl;
        cout << "\t\t\t\t\t   For Exit_______________________________________6" << endl;
        cout << "\t\t\t\t\t   Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            system("cls");
            add_book();
            getch();
            system("cls");
            break;
        case 2:
            system("cls");
            search_book();
            getch();
            system("cls");
            break;
        case 3:
            system("cls");
            addMember();
            getch();
            system("cls");
            break;
        case 4:
            system("cls");
            // Borrow book function (not implemented)
            // Borrow_Book();
            getch();
            system("cls");
            break;
        case 5:
            system("cls");
            // Member report function (not implemented)
            getch();
            system("cls");
            break;
        case 6:
            writeBookListToFile(Book_list, "book.txt");
            writeMemberListToFile(Member_list, "member.txt");
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice! Please enter a number between 1 and 6." << endl;
            getch();
            system("cls");
            break;
        }
    }

    return 0;
}
