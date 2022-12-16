/**
 * @file app.cpp
 * @author Uvaish Bakaliya
 * @brief The program lets user add, search, and displays the companies the use have added
 * @date 2022-12-15
 * @copyright Copyright (c)UB 2022
 */
#include "prog.h"

int main()
{
    system("clear");
    cout << ("\033[1;36m") << "*** Welcome to \"Applied Tracker\"! ***" << endl;
    Prog runProg;
    string companyName, date, month, day, year;
    while (true)
    {
        char menuOptions;
        cout << "\nMenu Options:\n"
             << " 1. [A]dd companies\n"
             << " 2. [S]earch company\n"
             << " 3. [D]isplay\n"
             << " 4. [Q]uit\n"
             << "Your Option--> ";
        cin >> menuOptions;
        menuOptions = toupper(menuOptions);
        cin.ignore();
        switch (menuOptions)
        {

        case 'A':
            cout << "\nEnter company 'name': ";
            getline(cin, companyName);
            cout << "Enter 'Month' (i.e 1..12): ";
            cin >> month;
            if (month.length() < 1 || month.length() > 2)
            {
                cout << "Invalid 'Month'" << endl;
                month.clear();
                continue;
            }
            cout << "Enter 'Day' (i.e 1..30): ";
            cin >> day;
            if (day.length() < 1 || day.length() > 2)
            {
                cout << "Invalid 'Day'" << endl;
                day.clear();
                continue;
            }
            cout << "Enter 'Year' (i.e 1..30): ";
            cin >> year;
            if (year.length() < 4 || year.length() > 4)
            {
                cout << "Invalid 'Year'" << endl;
                year.clear();
                continue;
            }
            date = month + day + year;
            runProg.addCompany(companyName, stoi(date));
            date.clear();
            break;
        case 'S':
            cout << "\nEnter company name: ";
            getline(cin, companyName);
            cout << endl;
            runProg.searchCompany(companyName);
            break;
        case 'D':
            cout << endl;
            runProg.displayDB();
            break;
        case 'Q':
            cout << "\nExiting..." << endl;
            exit(0);
            break;
        default:
            cout << "\nInvalid entry. Try again!" << endl;
            break;
        }
    }
    return 0;
}