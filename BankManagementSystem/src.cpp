#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

bool checkacountNumExist(unsigned int acno);
bool validateAccountNumber(string acno_str, unsigned int &acno);

class Bank_account
{
    unsigned int acno;
    char name[50];
    int deposit;
    char type;

   public:
    void create_account();
    void show_account() const;
    void modify();
    void dep(int);
    void draw(int);
    void report() const;
    int retacno() const;
    int retdeposit() const;
    char rettype() const;
};

void clearScreen()
{
    std::cout << std::string(100, '\n');
}

void Bank_account::create_account()
{
    string acno_str;
    // clearScreen();
    system("CLS");

    cout << "\n\t\t\tEnter the Account No. : ";
    cin >> acno_str;

    // ifstream inFile("account.dat", ios::binary);
    cin.ignore();  // Clear the newline character from the input buffer

    while ((validateAccountNumber(acno_str, acno)) ==
           false)  // Assuming validateAccountNumber is a function that
    {
        cout << "\n\t\t\tInvalid Account No. Please enter a valid number: ";
        cin >> acno_str;
        cin.ignore();  // Clear the newline character from the input buffer
    }

    // check if the account number is already taken
    while (checkacountNumExist(acno))
    {
        cout << "\n\t\t\tEnter a different Account No. : ";
        cin >> acno_str;
        cin.ignore();  // Clear the newline character from the input buffer
        while ((validateAccountNumber(acno_str, acno)) ==
               false)  // Assuming validateAccountNumber is a function that
        {
            cout << "\n\t\t\tInvalid Account No. Please enter a valid number: ";
            cin >> acno_str;
            cin.ignore();  // Clear the newline character from the input buffer
        }
    }
    // checkacountNumExist(acno);

    cout << "\n\n\t\t\tEnter the Name of the Account holder : ";
    /// cin.ignore();  // Clear the newline character from the input buffer
    cin.getline(name, 50);
    cout << "\n\t\t\tEnter Type of the Account (C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\n\t\t\tEnter The Initial amount : ";
    cin >> deposit;
    cout << "\n\n\t\t\tAccount Created..";
}
void Bank_account::show_account() const
{
    cout << "\n\t\t\tAccount No. : " << acno;
    cout << "\n\t\t\tAccount Holder Name : ";
    cout << name;
    cout << "\n\t\t\tType of Account : " << type;
    cout << "\n\t\t\tBalance amount : " << deposit;
}
void Bank_account::modify()
{
    cout << "\n\t\t\tAccount No. : " << acno;
    cout << "\n\t\t\tModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\n\t\t\tModify Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\n\t\t\tModify Balance amount : ";
    cin >> deposit;
}
void Bank_account::dep(int x)
{
    deposit += x;
}
void Bank_account::draw(int x)
{
    deposit -= x;
}
void Bank_account::report() const
{
    cout << left << setw(20) << acno << setw(20) << name << setw(20) << type << setw(20) << deposit
         << endl;
}
int Bank_account::retacno() const
{
    return acno;
}
int Bank_account::retdeposit() const
{
    return deposit;
}
char Bank_account::rettype() const
{
    return type;
}
void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);

int main()
{
    char ch;
    int num;
    do
    {
        system("CLS");
        cout << "\n\n\t\t\t\t======================\n";
        cout << "\t\t\t\tBANK MANAGEMENT SYSTEM";
        cout << "\n\t\t\t\t======================\n";
        cout << "\t\t\t\t ::MAIN MENU::\n";
        cout << "\n\t\t\t\t1. NEW ACCOUNT";
        cout << "\n\t\t\t\t2. DEPOSIT AMOUNT";
        cout << "\n\t\t\t\t3. WITHDRAW AMOUNT";
        cout << "\n\t\t\t\t4. BALANCE ENQUIRY";
        cout << "\n\t\t\t\t5. ALL ACCOUNT HOLDER LIST";
        cout << "\n\t\t\t\t6. CLOSE AN ACCOUNT";
        cout << "\n\t\t\t\t7. MODIFY AN ACCOUNT";
        cout << "\n\t\t\t\t8. EXIT";
        cout << "\n\n\t\t\t\tSelect Your Option (1-8): ";
        cin >> ch;
        switch (ch)
        {
            case '1':
                write_account();
                break;
            case '2':
                system("CLS");
                cout << "\n\n\t\t\tEnter The account No. : ";
                cin >> num;
                deposit_withdraw(num, 1);
                break;
            case '3':
                system("CLS");
                cout << "\n\n\t\t\tEnter The account No. : ";
                cin >> num;
                deposit_withdraw(num, 2);
                break;
            case '4':
                system("CLS");
                cout << "\n\n\t\t\tEnter The account No. : ";
                cin >> num;
                display_sp(num);
                break;
            case '5':
                display_all();
                break;
            case '6':
                system("CLS");
                cout << "\n\n\t\t\tEnter The account No. : ";
                cin >> num;
                delete_account(num);
                break;
            case '7':
                system("CLS");
                cout << "\n\n\t\t\tEnter The account No. : ";
                cin >> num;
                modify_account(num);
                break;
            case '8':
                system("CLS");
                cout << "\n\n\t\t\tThanks for using bank management system 'Author: Mahmoud Elkot'";
                break;
            default:
                cout << "\a";
        }
        cin.ignore();
        cin.get();
    } while (ch != '8');
    return 0;
}
void write_account()
{
    Bank_account ac;
    ofstream outFile;

    ac.create_account();
    outFile.open("account.dat", ios::binary | ios::app);
    outFile.write(reinterpret_cast<char *>(&ac), sizeof(Bank_account));
    outFile.close();
}
void display_sp(int n)
{
    Bank_account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\t\t\tBALANCE DETAILS\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Bank_account)))
    {
        if (ac.retacno() == n)
        {
            ac.show_account();
            flag = true;
            break;
        }
    }
    inFile.close();
    if (flag == false) cout << "\n\n\t\t\tAccount number does not exist";
}
void modify_account(int n)
{
    bool found = false;
    Bank_account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(Bank_account));
        if (ac.retacno() == n)
        {
            ac.show_account();
            cout << "\n\n\t\t\tEnter The New Details of account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(Bank_account));
            File.seekp(pos, ios::cur);  // fncallat1353
            File.write(reinterpret_cast<char *>(&ac), sizeof(Bank_account));
            cout << "\n\n\t\t\tRecord Updated";
            found = true;
        }
    }
    File.close();
    if (found == false) cout << "\n\n\t\t\tRecord Not Found ";
}
void delete_account(int n)
{
    Bank_account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Bank_account)))
    {
        if (ac.retacno() != n)
        {
            outFile.write(reinterpret_cast<char *>(&ac), sizeof(Bank_account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\nRecord Deleted ..";
}
void display_all()
{
    system("CLS");
    Bank_account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no. NAME Type Balance\n";
    cout << "====================================================\n";
    cout << left << setw(20) << "acount num" << setw(20) << "Name" << setw(20) << "Acount Type"
         << setw(20) << "deposit" << endl;
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Bank_account)))
    {
        ac.report();
    }
    inFile.close();
}
void deposit_withdraw(int n, int option)
{
    int amt;
    bool found = false;
    Bank_account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(Bank_account));
        if (ac.retacno() == n)
        {
            ac.show_account();
            if (option == 1)
            {
                cout << "\n\n\t\t\tTO DEPOSITSS AMOUNT";
                cout << "\n\n\t\t\tEnter The amount to be deposited: ";
                cin >> amt;
                ac.dep(amt);
            }
            if (option == 2)
            {
                cout << "\n\n\t\t\tTO WITHDRAW AMOUNT";
                cout << "\n\n\t\t\tEnter The amount to be withdraw: ";
                cin >> amt;
                int bal = ac.retdeposit() - amt;
                if (bal < 0)
                    cout << "Insufficience balance";
                else
                    ac.draw(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);  // fn1353
            File.write(reinterpret_cast<char *>(&ac), sizeof(Bank_account));
            cout << "\n\n\t\t\tRecord Updated";
            found = true;
        }
    }
    File.close();
    if (found == false) cout << "\n\n\t\t\tRecord Not Found ";
}

bool checkacountNumExist(unsigned int acno)
{
    Bank_account ac;
    ifstream inFile("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return false;
    }

    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Bank_account)))
    {
        if (ac.retacno() == acno)
        {
            cout << "\n\n\t\t\tAccount number already exists. Please try again.";
            cout << "\n\t\t\t acno =  " << acno << endl;
            cout << "ac.retacno =  " << ac.retacno();
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}

bool validateAccountNumber(string acno_str, unsigned int &acno)
{
    // Check if the string is empty
    if (acno_str.empty())
    {
        cout << "\n\t\t\tAccount number cannot be empty.";
        return false;
    }

    // Check if the string contains only digits
    for (char c : acno_str)
    {
        if (!isdigit(c))
        {
            cout << "\n\t\t\tAccount number must contain only digits.";
            return false;
        }
    }

    // Convert string to integer
    try
    {
        acno = stoi(acno_str);
        cout << "\n\t\t\tAccount number is valid: " << acno;
    }
    catch (const std::invalid_argument &)
    {
        cout << "\n\t\t\tInvalid account number format.";
        return false;
    }

    return true;
}