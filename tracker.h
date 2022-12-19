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
        ifstream outFile("database.csv");
        string companyName, date;
        if (outFile.fail())
        {
            cout << "Invalid File" << endl;
            exit(0);
        }
        getline(outFile, companyName, ',');
        getline(outFile, date, '\n');
        while (!outFile.eof())
        {
            dataBase[companyName] = date;
            getline(outFile, companyName, ',');
            getline(outFile, date, '\n');
        }
        outFile.close();
    }

    void writeInFile(string name, string date)
    {
        fstream inFile("database.csv", ios_base::app);
        inFile << name << ',' << date << '\n';
        inFile.close();
    }

public:
    Tracker() { readFile(); }
    ~Tracker() { dataBase.clear(); }
    void displayDB();
    void addCompany();
    void searchCompany(string companyName);
};

void Tracker::displayDB()
{
    cout << "* Total companies applied: " << dataBase.size() << endl;
    cout << "--------------------------" << endl;
    cout << " Company Name  |  [Date]  " << endl;
    cout << "--------------------------" << endl;
    for (const auto &i : dataBase)
        cout << "> " << i.first << " - [" << i.second << "]" << endl;
}

void Tracker::addCompany()
{
    string companyName;
    cout << "\nEnter company 'name': ";
    getline(cin, companyName);
    if (dataBase.find(companyName) != dataBase.end())
    {
        cout << "\n* IMPORTANT: YOU HAVE ALREADY APPLIED FOR A JOB WITH THE COMPANY. YOU ARE INELIGIBLE TO REAPPLY." << endl;
        return;
    }
    time_t now = time(0);
    // convert now to tm struct for UTC
    tm *gmtm = gmtime(&now);
    string date = asctime(gmtm);
    date.pop_back();
    dataBase[companyName] = date;
    writeInFile(companyName, date);
    cout << "\n* Successfully Added! *" << endl;
}

void Tracker::searchCompany(string companyName)
{
    if (dataBase.find(companyName) == dataBase.end())
    {
        cout << "* NONE FOUND. YOU MAY APPLY." << endl;
        return;
    }
    string date = dataBase[companyName];
    cout << "Name: " << companyName << "\nDate: "
         << " [" << dataBase[companyName] << ']' << endl;
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
            runProg.addCompany();
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
