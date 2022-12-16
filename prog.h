#pragma once

#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
using namespace std;

class Prog
{
private:
    map<string, int> dataBase;

    void readFile()
    {
        ifstream inFile("database.txt");
        string companyName, date;
        if (inFile.fail())
        {
            cout << "Invalid File" << endl;
            exit(0);
        }
        getline(inFile, companyName, ':');
        getline(inFile, date, '\n');
        while (!inFile.eof())
        {
            this->dataBase[companyName] = stoi(date);
            getline(inFile, companyName, ':');
            getline(inFile, date, '\n');
        }
        inFile.close();
    }

    void writeInFile(string name, string date)
    {
        fstream outfile = fstream("database.txt", ios_base::app);
        outfile << name << ":" << date;
        outfile.close();
    }

public:
    Prog() { this->readFile(); }
    void displayDB();
    void addCompany(string companyName, int date);
    void searchCompany(string companyName);
};

void Prog::displayDB()
{
    cout << "* Total companies applied: " << this->dataBase.size() << endl;
    int totalC = 1;
    cout << "-------------------------" << endl;
    cout << " Company Name  |  [Date]      " << endl;
    cout << "-------------------------" << endl;
    for (const auto &i : this->dataBase)
    {
        string date = to_string(i.second);
        cout << totalC << "."
             << ": " << i.first << " [" << date[0] << date[1] << '-'
             << date[2] << date[3] << '-' << date[4] << date[5]
             << date[6] << date[7] << "]"
             << endl;
        totalC++;
    }
}

void Prog::addCompany(string companyName, int date)
{
    if (this->dataBase.find(companyName) != this->dataBase.end())
    {
        cout << "Company Is already in data base, are you sure you want to added it again?" << endl;
        cout << "[Y]es OR [N]o: ";
        char conf;
        cin >> conf;
        conf = toupper(conf);
        switch (conf)
        {
        case 'Y':
            cout << "\n*** NOTE: Company Won't be added again, but the date will be change. ***\n"
                 << endl;
            break;
        case 'N':
            return;
            break;
        default:
            cout << "Invalid Entry." << endl;
            break;
        }
    }
    this->dataBase[companyName] = date;
    this->writeInFile(companyName, to_string(date) + "\n");
    cout << "\n*** Successfully added! ***\n"
         << endl;
}

void Prog::searchCompany(string companyName)
{
    this->dataBase.clear();
    this->readFile();
    if (this->dataBase.find(companyName) == this->dataBase.end())
    {
        cout << "*** Non Found ***" << endl;
        return;
    }
    string date = to_string(dataBase[companyName]);
    cout << "Company name: " << companyName
         << "\nDate: "
         << " ["
         << date[0] << date[1] << '-' << date[2] << date[3] << '-'
         << date[4] << date[5] << date[6] << date[7]
         << ']'
         << endl;
}
