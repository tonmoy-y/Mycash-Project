#include <bits/stdc++.h>
#include <conio.h>


using namespace std;
int getPin();
int main_menu();
int menu1(void);
int OTP();
int search(string m);
int select();
int trxID();

string getTime();

int fin;

class MyCash
{
private:
    string mobile;
    string name;
    int pin;
    float balance = 0;
    int cnt = 0;

public:
    pair<int, string> his[100];
    tuple<float, float, string> hist[100];

    friend void insertFile();

    void setData(string m, string n, int p, float bal)
    {
        mobile = m;
        name = n;
        pin = p;
    }

    int mpass(string m, int p)
    {
        if (m == mobile && p == pin)
        {
            return 1;
        }
        else
            return 0;
    }

    string getMobile()
    {
        return (mobile);
    }

    void update();
    void remove();
    void send();
    void cash_in();
    void cash_out();
    void paybill();
    void check();
    void history();
};

MyCash mem[1000];
int total = -1;

void insertFile()
{

    ofstream outputFile("MyCash.txt", ios::app);

    for (int i = 0; i <= total; i++)
    {
        if (outputFile.is_open())
        {
            outputFile << mem[i].name << " " << mem[i].mobile << " " << mem[i].pin << " " << mem[i].balance << endl;
        }
    }
    outputFile.close();
}

string getTime()
{

    time_t now = time(0);
    char *dt = ctime(&now);
    return string(dt);
}

int trxID()
{
    srand(time(0));
    int x = +rand();
    return x;
}

int OTP()
{
    srand(time(0));
    int x = 1000 + rand() % 9000;

    cout << "\033[33mmyCash OTP: " << x << "\033[0m" << endl;
    cout << "Your OTP is valid for only 2 mins .....\nHurry up!....." << endl;
    return x;
}

int getPin()
{
    string s;
    char c;
    int i = 0;
    c = getch();

    if (c == 13)
        return 1;
    while (c != 13)
    {
        s[i] = c;
        cout << "*";
        i++;
        c = getch();
    }
    return (stoi(s));
}

int search(string m)
{
    int i = 0, pos = -1;
    for (; i <= total; i++)
    {
        if (mem[i].getMobile() == m)
        {
            pos = i;
            break;
        }
    }
    return pos;
}

void MyCash ::update()
{
    string n;
    int p;
    char s[100];
    int a, c, d, e, x;
    cin.ignore();
    cout << "Old name: " << name << endl;
    ;
    cout << "New name: ";
    cin.getline(s, 100);
    cout << "Old PIN(enter to ignore): ";
    a = getPin();
    cout << endl;
    if (a != 1)
        do
        {
            cout << "New PIN: ";
            c = getPin();
            cout << endl;
            cout << "Confirm new pin: ";
            p = getPin();
            cout << endl;
        } while (c != p);
    clock_t start = clock();
otp:
    x = OTP();
    clock_t end = clock();
    cout << (end - start) / 1000 << endl;
    cout << "Enter OTP: ";
    cin >> d;
    if (((end - start) / 1000) > 120)
    {
        cout << "OTP time has expired" << endl;
        goto otp;
    }

    if (x == d)
    {
        mem[fin].setData(mobile, s, p, balance);
        cout << "Member update succesfully" << endl;
    }
    else
        cout << "Invalid OTP...." << endl;
    cout << "Press any key go to main menu....." << endl;
    getch();
    system("cls");

    select();
}

void MyCash ::remove()
{
    int p, s;
    do
    {
        cout << "Enter PIN: ";

        p = getPin();
        if (p != pin)
            cout << "Invalid PIN." << endl;
    } while (p != pin);

    cout << endl;
otp:
    int x = OTP();
    clock_t start = clock();

    cout << "Enter OTP: ";
    cin >> s;
    clock_t end = clock();
    if (((end - start) / 1000) > 120)
    {
        cout << "OTP time has expired" << endl;
        goto otp;
    }
    if (x == s)
    {
        mem[0].setData(" ", " ", 0, 0.0);
        cout << "Remove is succesful" << endl;
    }
    else
        cout << "Invalid OTP...." << endl;
    cout << "Press any key go to main menu....." << endl;
    getch();
    system("cls");

    menu1();
}

void MyCash ::send()
{
    float b = 0;
    int a;
    string m;
    char s;
    cout << "Enter Destination no. (11-digit): ";
    cin >> m;
    int d = search(m);
    if (m.length() == 11 and mem[d].mobile == m)
    {
        cout << "Enter Amount: ";
        cin >> b;
    }
    else
    {
        cout << "Destination Mobile no. is invalid" << endl;
        goto c;
    }
    if (b <= balance)
    {

        cout << "Sending " << b << " to " << m << endl;
        mem[d].balance = mem[d].balance + b;

        cout << "Are you sure(Y/N)? ";
        cin >> s;
        int x;
        if (s == 'Y')

        {
        m:

            x = OTP();
            clock_t start = clock();

            cout << "Enter OTP: ";
            cin >> a;
            clock_t end = clock();
            if (((end - start) / 1000) > 120)
            {
                cout << "OTP time has expired" << endl;
                goto m;
            }
            if (a == x)
            {
                balance = balance - b;
                cout << "Send Money is Successful" << endl;

                his[cnt] = make_pair(trxID(), "Send Money");
                hist[cnt] = make_tuple(b, balance, getTime());
                cnt++;
            }
            else
                goto m;
        }
        else
            goto c;
    }
    else
        cout << "Insufficient Fund" << endl;
c:

    cout << "Press any key go to main menu....." << endl;
    getch();
    system("cls");

    select();
}

void MyCash ::cash_in()
{
    float b;
    char s;
    cout << "Enter Amount: ";
    cin >> b;
    cout << "Cash-in " << b << endl;

    cout << "Are you sure(Y/N)? ";
    cin >> s;
    if (s == 'Y' || s == 'y')
    {
        balance = balance + b;
        cout << "Cash-in is Successful" << endl;

        his[cnt] = make_pair(trxID(), "Cash-in");
        hist[cnt] = make_tuple(b, balance, getTime());
        cnt++;
    }

c:
    cout << "Press any key go to main menu....." << endl;
    getch();
    system("cls");

    select();
}

void MyCash ::cash_out()
{
    float b;
    int a;
    int x;
    char s;
    cout << "Enter Amount: ";
    cin >> b;
    cout << "Cash_out " << b << endl;

    if (balance >= b)
    {
        cout << "Are you sure(Y/N)? ";
        cin >> s;
        if (s == 'Y')
        {

        g:

            x = OTP();
            clock_t start = clock();

            cout << "Enter OTP: ";
            cin >> a;
            clock_t end = clock();
            if (((end - start) / 1000) > 120)
            {
                cout << "OTP time has expired" << endl;
                goto g;
            }
            if (a == x)
            {
                balance = balance - b;
                cout << "Cash-out is Successful" << endl;
                his[cnt] = make_pair(trxID(), "Cash Out");
                hist[cnt] = make_tuple(b, balance, getTime());
                cnt++;
            }
            else
                goto g;
        }
    }
    else
    {
        cout << "Insufficient Fund" << endl;
    }
    cout << "Press any key go to main menu....." << endl;
    getch();
    system("cls");

    select();
}

void MyCash ::paybill()
{
    int a, tk, x, f;
    char d;
    string s;
    cout << "Enter Bill Type (Gas/Electricity/Water/Internet-1/2/3/4):";
    cin >> a;
    if (a == 1)
        s = "Gas bill";
    else if (a == 2)
        s = "Electricity bill";
    else if (a == 3)
        s = "Water bill";
    else
        s = "Internet bill";

    cout << "Your " << s << ": ";
    cin >> tk;

    if (tk <= balance)
    {
        cout << "Are you sure(Y/N)? ";
        cin >> d;
        if (d == 'Y')
        {

        otp:
            x = OTP();
            clock_t start = clock();

            cout << "Enter OTP: ";
            cin >> f;
            clock_t end = clock();
            if (((end - start) / 1000) > 120)
            {
                cout << "OTP time has expired" << endl;
                goto otp;
            }
            if (f == x)
            {

                balance = balance - tk;
                cout << "Bill payment is Successful" << endl;
                his[cnt] = make_pair(trxID(), s);
                hist[cnt] = make_tuple(tk, balance, getTime());
                cnt++;
            }
            else
                cout << "Invalid OTP....";
        }
    }
    else
        cout << "Insufficient balance..." << endl;
    cout << "Press any key go to main menu....." << endl;
    getch();
    system("cls");

    select();
}

void MyCash ::check()
{
    cout << "Balance: " << balance << endl;

    cout << "Press any key go to main menu....." << endl;
    getch();
    system("cls");

    select();
}

void MyCash ::history()
{
    cout << "History is under construction " << endl;
    cout << left << setw(10) << "Tran ID" << setw(20) << "Description" << setw(10) << "Amount" << setw(10) << "Balance"
         << "Date & Time" << endl;
    for (int i = 0; i < cnt; i++)
    {
        cout << left << setw(10) << his[i].first << setw(20) << his[i].second;
        cout << fixed << setprecision(2) << setw(10) << get<0>(hist[i]) << setw(10) << get<1>(hist[i]) << get<2>(hist[i]) << endl;
    }

    cout << "Press any key go to main menu....." << endl;
    getch();
    system("cls");
    select();
}

// Register -------->

void Register()
{
    string a;
    char b[100];
    int c, d, x, f, h;
    do
    {
        cout << "Enter Mobile No. (11-digit): ";
        cin >> a;
        if (a.length() != 11)
            cout << "Mobile number must be 11 digits.." << endl;
    } while (a.length() != 11);
    cin.ignore();
    h = search(a);
    if (h < 0)
    {
        cout << "Enter your name: ";
        cin.getline(b, 100);
        do
        {
            cout << "Enter pin no(5-dgit): ";
            c = getPin();
            cout << endl;
            cout << "Reconfirm your pin: ";
            d = getPin();
            cout << endl;
            if (c != d)
                cout << "Pins must be same" << endl;
        } while (c != d);

    otp:
        x = OTP();
        clock_t start = clock();

        cout << "Enter OTP: ";
        cin >> f;
        clock_t end = clock();
        if (((end - start) / 1000) > 120)
        {
            cout << "OTP time has expired" << endl;
            goto otp;
        }
        if (x == f)
        {
            total++;
            mem[total].setData(a, b, d, 0.0);
            cout << "Your Registration is successful " << endl;
        }
        else
        {
            cout << "Invalid OTP...." << endl;
        }
    }
    else
        cout << "Member is already exists..." << endl
             << endl;
    ;
    cout << "Press any key go to main menu....." << endl;
    getch();
    system("cls");
}

int menu1(void)
{
    cout << "\033[0m\t*** MyCash Login***" << endl;
    cout << "\t\t1. Log in" << endl;
    cout << "\t\t2. Register" << endl;
    cout << "\t\t3. exit" << endl;
    cout << "Enter your choice: ";
    int op;
    cin >> op;
    return op;
}

int login()
{
    int p;
    string m;
    cout << "Enter mobile no: ";
    cin >> m;
    cout << "Enter PIN: ";
    p = getPin();
    cout << endl;
    int b = search(m);
    fin = b;
    int a = mem[b].mpass(m, p);
    if (a == 1)
    {
        cout << "Login is Successful" << endl;
        select();
        return b;
    }
    else
    {
        cout << "Invalid login" << endl;
    }
    cout << "Press any key go to myCash menu...." << endl;
    getch();
    system("cls");
    return 0;
}

int select()
{
    int a = main_menu();
    //  int b = login();
    if (a == 0 || a >= 10)
    {
        cout << "Invalid Option" << endl
             << endl;
        ;
        cout << "Press any key go to myCash menu...." << endl;
        getch();
        system("cls");
        select();
    }
    else
        switch (a)
        {
        case 1:
            mem[fin].update();
            break;
        case 2:
            mem[fin].remove();
            break;
        case 3:
            mem[fin].send();
            break;
        case 4:
            mem[fin].cash_in();
            break;
        case 5:
            mem[fin].cash_out();
            break;
        case 6:
            mem[fin].paybill();
            break;
        case 7:
            mem[fin].check();
            break;
        case 8:
            mem[fin].history();
            break;
        case 9:
            system("cls");
            return 0;
        }
    return 0;
}

int main_menu()
{
    cout << "\t********** MyCash Menu ********" << endl;
    cout << "\t\t1. Update Me" << endl;
    cout << "\t\t2. Remove Me" << endl;
    cout << "\t\t3. Send Money" << endl;
    cout << "\t\t4. Cash-in" << endl;
    cout << "\t\t5. Cash-out" << endl;
    cout << "\t\t6. Pay Bill" << endl;
    cout << "\t\t7. Check Balance" << endl;
    cout << "\t\t8. History" << endl;
    cout << "\t\t9. Logout" << endl;
    cout << "Enter Your Option (1-9): ";
    int s;
    cin >> s;
    system("cls");
    return s;
}

int main()
{
    int num;

    for (;;)
    {
        num = menu1();
        if (num == 3)
        {
            insertFile();
            break;
        }

        switch (num)
        {
        case 1:
            login();
            break;
        case 2:
            Register();
            break;
        default:
            cout << "Invalid option" << endl;
        }
    }
    return 0;
}

// 01521788253
// Tonmoy
// 12345

// 01557773452
// Sourav
// 23456