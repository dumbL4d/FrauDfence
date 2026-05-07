#include <bits/stdc++.h>
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include <cfloat>

using namespace std;

const string blue = "\033[1;34m";
const string black = "\033[30m";
const string red = "\033[31m";
const string green = "\033[32m";
const string yellow = "\033[33m";
const string magenta = "\033[35m";
const string cyan = "\033[36m";
const string white = "\033[37m";

// Transaction Class
class transaction
{
public:
    string transactionDateTime;
    string creditCardNumber;
    string merchantName;
    string merchantCategory;
    float amount;
    string firstName;
    string lastName;
    string street;
    string city;
    string state;
    int zipcode;
    double clientLatitude;
    double clientLongitude;
    string clientJob;
    string transactionNumber;
    double merchantLatitude;
    double merchantLongitude;
    int flag;
};

// Client Class
class client
{
public:
    string creditCardNumber;
    string cardHolderName;
    vector<transaction> arr;
    vector<int> spendings;
    int transactionsCompleted;
};

// READ CSV function
map<string, client> readCSVFile(const string &filename)
{
    map<string, client> clients;
    ifstream file(filename);
    string line;
    getline(file, line); // Skip header

    while (getline(file, line))
    {
        bool inQuotes = false;
        for (size_t i = 0; i < line.size(); ++i)
        {
            if (line[i] == '"')
                inQuotes = !inQuotes;
            else if (line[i] == ',' && inQuotes)
                line[i] = '|';
        }

        stringstream ss(line);
        string field;
        transaction t;

        getline(ss, t.transactionDateTime, ',');
        getline(ss, t.creditCardNumber, ',');
        getline(ss, t.merchantName, ',');
        getline(ss, t.merchantCategory, ',');

        getline(ss, field, ',');
        replace(field.begin(), field.end(), '|', ',');
        t.amount = stof(field);
        getline(ss, t.firstName, ',');
        getline(ss, t.lastName, ',');
        getline(ss, t.street, ',');
        getline(ss, t.city, ',');
        getline(ss, t.state, ',');
        getline(ss, field, ',');
        t.zipcode = stoi(field);
        getline(ss, field, ',');
        t.clientLatitude = stod(field);
        getline(ss, field, ',');
        t.clientLongitude = stod(field);
        getline(ss, field, ',');
        replace(field.begin(), field.end(), '|', ',');
        t.clientJob = field;
        getline(ss, t.transactionNumber, ',');
        getline(ss, field, ',');
        t.merchantLatitude = stod(field);
        getline(ss, field, ',');
        t.merchantLongitude = stod(field);
        getline(ss, field, ',');
        t.flag = stoi(field);

        if (!clients.count(t.creditCardNumber))
        {
            client c;
            c.creditCardNumber = t.creditCardNumber;
            c.cardHolderName = t.firstName + " " + t.lastName;
            c.transactionsCompleted = 0;
            clients[t.creditCardNumber] = c;
        }

        clients[t.creditCardNumber].arr.push_back(t);
        clients[t.creditCardNumber].spendings.push_back((int)t.amount);
        clients[t.creditCardNumber].transactionsCompleted++;
    }

    return clients;
}

int unusualSpendingPatterns(const vector<transaction> &transactions)
{
    const double creditLimit = 10000.0; // Credit Limit set to 10000 #Change if required
    const double epsilon = 0.01; // Tolerance for floating point comparison
    double totalSpending = 0.0;

    unordered_map<string, double> dailySpending;

    for (const auto &txn : transactions)
    {
        string date = txn.transactionDateTime.substr(0, 10);
        dailySpending[date] += txn.amount;
        if (dailySpending[date] > 500.00) return 2;
        totalSpending += txn.amount;
    }

    if (totalSpending >= creditLimit - epsilon)
        return 1;

    // Use unordered_set to simulate subset sum with floats
    unordered_set<double> possibleSums;
    possibleSums.insert(0.0);

    for (const auto &txn : transactions)
    {
        unordered_set<double> newSums = possibleSums;
        for (auto sum : possibleSums)
        {
            double newSum = sum + txn.amount;
            if (fabs(newSum - creditLimit) <= epsilon)
                return 1;
            newSums.insert(newSum);
        }
        possibleSums = move(newSums);
    }

    return 0; // No fraud detected
}


// MAIN
int main()
{
    string filename = "fraudTestCSV.csv";
    map<string, client> allClients = readCSVFile(filename);
    vector<transaction> allTransactions;

    for (map<string, client>::iterator it = allClients.begin(); it != allClients.end(); ++it)
    {
        string card = it->first;
        client &clientObj = it->second;
        // Sort transactions by date
        sort(clientObj.arr.begin(), clientObj.arr.end(), [](const transaction &a, const transaction &b)
             { return a.transactionDateTime < b.transactionDateTime; });

        // Collect all transactions globally
        for (size_t i = 0; i < clientObj.arr.size(); ++i)
        {
            allTransactions.push_back(clientObj.arr[i]);
        }
    }

    int i = 1;
    for (const auto& it : allClients) 
    {
        cout << i++ << ". "<< endl;
        const auto& card = it.first;
        const auto& clientObj = it.second;
        int fraud = unusualSpendingPatterns(clientObj.arr);
        if (fraud == 2)
                cout << red << "Daily spending limit exceeded!" << endl;
        else if (fraud == 1)
                cout << yellow << "Transactions are optimized to max out the limit - Potential fraud!" << endl;
        else
                cout << green << "Transaction pattern is normal." << endl;
    }

    return 0;
}
