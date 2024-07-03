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
    queue<pair<string, string>> borrow;
    int fin = 0;
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
        queue<pair<string, string>> tempQueue = member.borrow;
        while (!tempQueue.empty())
        {
            file << tempQueue.front().first << "-" << tempQueue.front().second << ",";
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
        queue<pair<string, string>> tempQueue;
        while (getline(ss, availability, ','))
        {
            stringstream ss2(availability);
            string x, y;
            getline(ss2, x, '-');
            getline(ss2, y);
            tempQueue.push({x, y});
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
        newBook.availability.push(newBook.title); // Only the availability status, not the title itself
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
    cout << "\t\t\t\t\t\t======================\n";
    cout << "\t\t\t\t\t\tAdd Member Information\n";
    cout << "\t\t\t\t\t\t======================\n";
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
void borrowBook()
{

    cout << "\t\t\t\t\t\t============\n";
    cout << "\t\t\t\t\t\tBorrow Books\n";
    cout << "\t\t\t\t\t\t============\n";

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
        bool flag = false;
        bool flag2 = false;
        for (auto &book : Book_list)
        {
            if (book.title == need)
            {
                flag2 = true;
                cout << "\t\t\t\t\tBook information:\n";
                cout << "\t\t\t\t\t-----------------\n";
                cout << "\t\t\t\t\tBook title: " << book.title << endl;
                cout << "\t\t\t\t\tBook author: " << book.author << endl;
                cout << "\t\t\t\t\tBook availability: " << (book.availability.empty() ? "Not available" : "Available") << endl;
                cout << "\t\t\t\t\t---------------------------\n";
                if (book.availability.empty())
                {
                    cout << "\t\t\t\t\tSorry, this book is not available in the library now\n";
                }
                else
                {

                    cout << "\t\t\t\t\tIf you want to borrow this book Please enter your ID:";
                    string id, todaysDate;
                    getline(cin, id);
                    cout << "\t\t\t\t\tPlease enter todays date:";
                    getline(cin, todaysDate);
                    for (auto &member : Member_list)
                    {
                        if (member.id == id)
                        {
                            member.borrow.push({book.title, todaysDate});
                            book.availability.pop();
                            flag = true;
                            break;
                        }
                    }
                }

                break;
            }
        }
        if (flag2 == false)
        {
            cout << "\t\t\t\t\tSorry, this book is not available in the library\n";
        }
        if (flag == true)
        {
            cout << "\t\t\t\t\t==========================\n";
            cout << "\t\t\t\t\tBook Borrowed Successfully\n";
            cout << "\t\t\t\t\t==========================\n";
        }
    }
    // if (search_book().second)
    // {

    // }
}
void return_book()
{
    cout << "\t\t\t\t\t\t============\n";
    cout << "\t\t\t\t\t\tReturn Books\n";
    cout << "\t\t\t\t\t\t============\n";
    cout << "\n\t\t\t\t\tPlease enter member id: ";
    string id;
    cin.ignore();
    getline(cin, id);
    cout << "\n\t\t\t\t\tPlease enter today's date (dd-mm-yyyy): ";
    string current_date_str;
    getline(cin, current_date_str);

    // Function to convert date string to tm structure
    auto str_to_tm = [](const string &date_str) -> tm
    {
        tm t = {};
        stringstream ss(date_str);
        ss >> get_time(&t, "%d-%m-%Y");
        return t;
    };

    // Function to calculate the difference in days between two tm structures
    auto days_diff = [](const tm &start, const tm &end) -> int
    {
        time_t start_time = mktime(const_cast<tm *>(&start));
        time_t end_time = mktime(const_cast<tm *>(&end));
        return difftime(end_time, start_time) / (60 * 60 * 24);
    };

    bool flag = false;
    for (auto &member : Member_list)
    {
        if (member.id == id)
        {
            flag = true;
            if (member.borrow.empty())
            {
                cout << "\t\t\t\t\t=================\n";
                cout << "\t\t\t\t\tNo books Borrowed\n";
                cout << "\t\t\t\t\t=================\n";
            }
            else
            {
                cout << "\t\t\t\t\tBorrowed Books:\n";
                cout << "\t\t\t\t\t-----------------\n";
                queue<pair<string, string>> tempQueue = member.borrow;
                while (!tempQueue.empty())
                {
                    auto borrow_info = tempQueue.front();
                    tempQueue.pop();

                    tm borrow_date = str_to_tm(borrow_info.second);
                    tm current_date = str_to_tm(current_date_str);
                    int days = days_diff(borrow_date, current_date);
                    int fine = 0;
                    if (days > 5)
                    {
                        fine = (days - 5) * 10;
                    }
                    cout << "\t\t\t\t\tBook title: " << borrow_info.first << ", Borrow date: " << borrow_info.second << ", Fine: " << fine << " taka" << endl;
                }
                cout << "\t\t\t\t\t-----------------\n";
                cout << "\t\t\t\t\tPlease enter the title of the book to return: ";
                string book_title;
                getline(cin, book_title);

                queue<pair<string, string>> newQueue;
                bool book_found = false;
                while (!member.borrow.empty())
                {
                    auto borrow_info = member.borrow.front();
                    member.borrow.pop();

                    if (borrow_info.first == book_title && !book_found)
                    {
                        book_found = true;
                        // Calculate fine if book is returned late
                        tm borrow_date = str_to_tm(borrow_info.second);
                        tm current_date = str_to_tm(current_date_str);
                        int days = days_diff(borrow_date, current_date);
                        if (days > 5)
                        {
                            int fine = (days - 5) * 10;
                            member.fin += fine;
                            cout << "\t\t\t\t\tYou have kept the book for " << days << " days.\n";
                            cout << "\t\t\t\t\tFine: " << fine << " taka\n";
                        }

                        for (auto &book : Book_list)
                        {
                            if (book.title == book_title)
                            {
                                book.availability.push("Available");
                                break;
                            }
                        }
                    }
                    else
                    {
                        newQueue.push(borrow_info);
                    }
                }

                member.borrow = newQueue;

                if (book_found)
                {
                    cout << "\t\t\t\t\t==========================\n";
                    cout << "\t\t\t\t\tBook Returned Successfully\n";
                    cout << "\t\t\t\t\t==========================\n";
                }
                else
                {
                    cout << "\t\t\t\t\tBook not found in your borrowed list.\n";
                }
            }
            break;
        }
    }
    if (!flag)
    {
        cout << "\t\t\t\t\tMember ID not found.\n";
    }
}

int main()
{
    readBookListFromFile(Book_list, "book.txt");
    readMemberListFromFile(Member_list, "member.txt");
    int ch = 0;
    while (ch != 7)
    {
        cout << "\t\t\t\t\t=====================================================\n\t\t\t\t\tLibrary management system of Sheikh Hasina University\n\t\t\t\t\t=====================================================\n"
             << endl;
        cout << "\t\t\t\t\t   For Adding New Books select____________________1" << endl;
        cout << "\t\t\t\t\t   For Searching Books select_____________________2" << endl;
        cout << "\t\t\t\t\t   For Adding new member select___________________3" << endl;
        cout << "\t\t\t\t\t   For Book issue_________________________________4" << endl;
        cout << "\t\t\t\t\t   For Book return________________________________5" << endl;
        cout << "\t\t\t\t\t   For Member Reports_____________________________6" << endl;
        cout << "\t\t\t\t\t   For Exit_______________________________________7" << endl;
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

            borrowBook();
            getch();
            system("cls");
            break;
        case 5:
            system("cls");
            return_book();
            getch();
            system("cls");
            break;
        case 7:
            writeBookListToFile(Book_list, "book.txt");
            writeMemberListToFile(Member_list, "member.txt");
            cout << "\t\t\t\t\t   Exiting the system. Goodbye!" << endl;
            break;
        default:
            cout << "\t\t\t\t\t   Invalid choice! Please enter a number between 1 and 6." << endl;
            getch();
            system("cls");
            break;
        }
    }

    return 0;
}
