/**
 * @file Tracker.h
 * @author Uvaish Bakliya
 * @date 2022-12-16
 * @copyright Copyright (c)UB 2022
 */
#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Tracker
{
private:
    unordered_map<string, string> dataBase;

    void readFile()
    {
        ifstream inFile("database.csv");
        string companyName, date;
        if (inFile.fail())
        {
            cout << "Invalid File" << endl;
            exit(0);
        }
        getline(inFile, companyName, ',');
        getline(inFile, date, '\n');
        while (!inFile.eof())
        {
            dataBase[companyName] = date;
            getline(inFile, companyName, ',');
            getline(inFile, date, '\n');
        }
        inFile.close();
    }

    void writeInFile(string name, string date)
    {
        fstream outfile = fstream("database.csv", ios_base::app);
        outfile << name << "," << date;
        outfile.close();
    }

public:
    Tracker() { readFile(); }
    ~Tracker() { dataBase.clear(); }
    void displayDB();
    void addCompany(string companyName, string date);
    void searchCompany(string companyName);
    bool addCompanyFully();
};

void Tracker::displayDB()
{
    cout << "* Total companies applied: " << dataBase.size() << endl;
    cout << "--------------------------" << endl;
    cout << " Company Name  |  [Date]  " << endl;
    cout << "--------------------------" << endl;
    for (const auto &i : dataBase)
    {
        string date = i.second;
        cout << "> " << i.first << " ~ [" << date[0] << date[1]
             << '-' << date[2] << date[3] << '-' << date[4] << date[5]
             << date[6] << date[7] << "]"
             << endl;
    }
}

void Tracker::addCompany(string companyName, string date)
{
    if (dataBase.find(companyName) != dataBase.end())
    {
        cout << "\n* IMPORTANT: YOU HAVE ALREADY APPLIED FOR A JOB WITH THE COMPANY. YOU ARE INELIGIBLE TO REAPPLY." << endl;
        return;
    }
    dataBase[companyName] = date;
    writeInFile(companyName, date + "\n");
    cout << "\n*** Successfully added! ***" << endl;
}

void Tracker::searchCompany(string companyName)
{
    if (dataBase.find(companyName) == dataBase.end())
    {
        cout << "* NONE FOUND. YOU MAY APPLY." << endl;
        return;
    }
    string date = dataBase[companyName];
    cout << "Name: " << companyName
         << "\nDate: "
         << " ["
         << date[0] << date[1] << '-' << date[2] << date[3] << '-'
         << date[4] << date[5] << date[6] << date[7]
         << ']'
         << endl;
}

bool Tracker::addCompanyFully()
{
    string companyName, date, month, day, year;
    cout << "\nEnter company 'name': ";
    getline(cin, companyName);
    cout << "Enter 'Month' (i.e 1-12): ";
    cin >> month;
    if (stoi(month) < 1 || stoi(month) > 12)
    {
        cout << "Invalid Month" << endl;
        return false;
    }
    cout << "Enter 'Day' (i.e 1-31): ";
    cin >> day;
    if (stoi(day) < 1 || stoi(day) > 31)
    {
        cout << "Invalid Day" << endl;
        return false;
    }
    cout << "Enter 'Year' (i.e 2022): ";
    cin >> year;
    if (year.length() < 4 || year.length() > 4)
    {
        cout << "Invalid Year" << endl;
        return false;
    }
    if (day.length() == 1)
        day.insert(0, "0");
    if (month.length() == 1)
        month.insert(0, "0");
    date = (month + day + year);
    addCompany(companyName, date);
    return true;
}

int go()
{
    system("clear");
    Tracker runProg;
    cout << ("\033[1;36m") << "*** Welcome to 'Applied Tracker' ***" << endl;
    while (true)
    {
        char menuOptions;
        string companyName;
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
            if (!runProg.addCompanyFully())
                continue;
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
            cout << "Exiting..." << endl;
            exit(0);
            break;
        default:
            cout << "\nInvalid entry. Try again!" << endl;
            break;
        }
    }
    return 0;
}
