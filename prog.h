/**
 * @file prog.h
 * @author Uvaish Bakliya
 * @date 2022-12-16
 * @copyright Copyright (c)UB 2022
 */
#pragma once

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Prog
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
            this->dataBase[companyName] = date;
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
    void addCompany(string companyName, string date);

public:
    Prog() { this->readFile(); }
    ~Prog() { this->dataBase.clear(); }
    void displayDB();
    void searchCompany(string companyName);
    void addCompanyFully();
    int go();
};

void Prog::displayDB()
{
    cout << "* Total companies applied: " << this->dataBase.size() << endl;
    int totalC = 1;
    cout << "-------------------------" << endl;
    cout << " Company Name  |  [Date] " << endl;
    cout << "-------------------------" << endl;
    for (const auto &i : this->dataBase)
    {
        string date = i.second;
        cout << totalC << ": " << i.first << " [" << date[0] << date[1]
             << '-' << date[2] << date[3] << '-' << date[4] << date[5]
             << date[6] << date[7] << "]"
             << endl;
        totalC++;
    }
}

void Prog::addCompany(string companyName, string date)
{
    if (this->dataBase.find(companyName) != this->dataBase.end())
    {
        cout << "IMPORTANT: Company Is already in data base. You can't apply again." << endl;
        return;
    }
    this->dataBase[companyName] = date;
    this->writeInFile(companyName, date + "\n");
    cout << "\n*** Successfully added! ***" << endl;
}

void Prog::searchCompany(string companyName)
{
    if (this->dataBase.find(companyName) == this->dataBase.end())
    {
        cout << "*** Non Found ***" << endl;
        return;
    }
    string date = this->dataBase[companyName];
    cout << "Name: " << companyName
         << "\nDate: "
         << " ["
         << date[0] << date[1] << '-' << date[2] << date[3] << '-'
         << date[4] << date[5] << date[6] << date[7]
         << ']'
         << endl;
}

void Prog::addCompanyFully()
{
    string companyName, date, month = "00", day = "00", year;
    cout << "\nEnter company 'name': ";
    getline(cin, companyName);
    cout << "Enter 'Month' (i.e 1..12): ";
    cin >> month;
    if (month.length() < 1 || month.length() > 2)
    {
        cout << "Invalid 'Month'" << endl;
        return;
    }
    cout << "Enter 'Day' (i.e 1..30): ";
    cin >> day;
    if (day.length() < 1 || day.length() > 2)
    {
        cout << "Invalid 'Day'" << endl;
        return;
    }
    cout << "Enter 'Year' (i.e 1..30): ";
    cin >> year;
    if (year.length() < 4 || year.length() > 4)
    {
        cout << "Invalid 'Year'" << endl;
        return;
    }
    if (day.length() == 1)
        day.insert(0, "0");
    if (month.length() == 1)
        month.insert(0, "0");
    date = (month + day + year);
    this->addCompany(companyName, date);
}

int Prog::go()
{
    system("clear");
    cout << ("\033[1;36m") << "*** Welcome to \"Applied Tracker\"! ***" << endl;
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
            addCompanyFully();
            break;
        case 'S':
            cout << "\nEnter company name: ";
            getline(cin, companyName);
            cout << endl;
            searchCompany(companyName);
            break;
        case 'D':
            cout << endl;
            displayDB();
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
