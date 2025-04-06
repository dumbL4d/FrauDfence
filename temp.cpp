#include<bits/stdc++.h>
#include<stdlib.h>
#include<stdexcept>
#include<string>
using namespace std;
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

    transaction()
    {
        flag = 0;
    }
};

class client
{

public:
    string creditCardNumber;
    string cardHolderName;
    vector<transaction> arr;
    vector<int> spendings;
    int transactionsCompleted;
};

int graduallyIncreasingFraudelentTransactionAmount(vector<int> &spendings)
{
    int n = spendings.size();
    vector<int> dp(n, 1);

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (spendings[i] > spendings[j])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    int maxi = dp[0];

    for (int i = 1; i < n; i++)
    {
        maxi = max(maxi, dp[i]);
    }
    return maxi > 7; // Increasing spending sequence limit set to 7. Change if required.
}

map<string, client> readCSVFile(const string& filename) {
    map<string, client> clients;
    ifstream file(filename);
    string line;

    // Skip header
    getline(file, line);

    while (getline(file, line)) {
        // Handle quoted commas
        bool inQuotes = false;
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] == '"') inQuotes = !inQuotes;
            else if (line[i] == ',' && inQuotes) line[i] = '|';  // Temporarily replace
        }

        stringstream ss(line);
        string field;
        transaction t;

        getline(ss, t.transactionDateTime, ',');
        getline(ss, t.creditCardNumber, ',');
        getline(ss, t.merchantName, ',');
        getline(ss, t.merchantCategory, ',');

        getline(ss, field, ','); replace(field.begin(), field.end(), '|', ','); t.amount = stof(field);
        getline(ss, t.firstName, ',');
        getline(ss, t.lastName, ',');
        getline(ss, t.street, ',');
        getline(ss, t.city, ',');
        getline(ss, t.state, ',');

        getline(ss, field, ','); t.zipcode = stoi(field);
        getline(ss, field, ','); t.clientLatitude = stod(field);
        getline(ss, field, ','); t.clientLongitude = stod(field);

        getline(ss, field, ','); replace(field.begin(), field.end(), '|', ','); t.clientJob = field;
        getline(ss, t.transactionNumber, ',');

        getline(ss, field, ','); t.merchantLatitude = stod(field);
        getline(ss, field, ','); t.merchantLongitude = stod(field);
        getline(ss, field, ','); t.flag = stoi(field);

        // Create client if needed
        if (!clients.count(t.creditCardNumber)) {
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

/*

map<string, client> readCSVFile(const string& filename) {
    map<string, client> clients;
    ifstream file(filename);
    string line;

    // Skip the header
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        transaction t;

        // Read each field
        getline(ss, t.transactionDateTime, ',');
        getline(ss, t.creditCardNumber, ',');
        getline(ss, t.merchantName, ',');
        getline(ss, t.merchantCategory, ',');
        
        getline(ss, field, ','); t.amount = stof(field);
        getline(ss, t.firstName, ',');
        getline(ss, t.lastName, ',');
        getline(ss, t.street, ',');
        getline(ss, t.city, ',');
        getline(ss, t.state, ',');
        
        getline(ss, field, ','); t.zipcode = stoi(field);
        getline(ss, field, ','); t.clientLatitude = stod(field);
        getline(ss, field, ','); t.clientLongitude = stod(field);
        getline(ss, t.clientJob, ',');
        getline(ss, t.transactionNumber, ',');
        getline(ss, field, ','); t.merchantLatitude = stod(field);
        getline(ss, field, ','); t.merchantLongitude = stod(field);
        getline(ss, field, ','); t.flag = stoi(field);

        // Add transaction to the right client
        if (!clients.count(t.creditCardNumber)) {
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
*/


int main() {
    string filename = "fraudTestCSV.csv";
    map<string, client> allClients = readCSVFile(filename);

    // Example: Print number of clients and their transaction count
    cout << "Total Clients: " << allClients.size() << endl;
    for (const auto& [card, c] : allClients) {
        cout << "Client: " << c.cardHolderName
             << ", Transactions: " << c.transactionsCompleted << endl;
    }

    // Example: Run analysis on first client
    if (!allClients.empty()) {
        auto it = allClients.begin();
        cout << "Checking for gradual fraud pattern on: " << it->second.cardHolderName << endl;
        bool fraud = graduallyIncreasingFraudelentTransactionAmount(it->second.spendings);
        cout << (fraud ? "Potential Fraud Detected!" : "No Fraud Pattern Detected") << endl;
    }

    return 0;
}
