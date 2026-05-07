//Including standard library
#include<iostream>
#include<stdlib.h>
#include<stdexcept>
#include<string>
#include<conio.h>
#include<windows.h>

// Time Libraries
#include<chrono>
#include<thread>

/*
//Including MySQL Libraries 
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_driver.h>
*/

using namespace std;

// Clear Screen Function
void clearscreen() {
    system("cls");
}

//EXIT SCREEN
void exitscr() {
    auto start = chrono::high_resolution_clock::now();
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << "ooooooooooooo ooooo   ooooo       .o.       ooooo      ooo oooo    oooo      oooooo   oooo   .oooooo.   ooooo     ooo \n";
    cout << "8'   888   `8 `888'   `888'      .888.      `888b.     `8' `888   .8P'        `888.   .8'   d8P'  `Y8b  `888'     `8' \n";
    cout << "     888       888     888      .8\"888.      8 `88b.    8   888  d8'           `888. .8'   888      888  888       8  \n";
    cout << "     888       888ooooo888     .8' `888.     8   `88b.  8   88888[              `888.8'    888      888  888       8  \n";
    cout << "     888       888     888    .88ooo8888.    8     `88b.8   888`88b.             `888'     888      888  888       8  \n";
    cout << "     888       888     888   .8'     `888.   8       `888   888  `88b.            888      `88b    d88'  `88.    .8'  \n";
    cout << "    o888o     o888o   o888o o88o     o8888o o8o        `8  o888o  o888o          o888o      `Y8bood8P'     `YbodP'\n";
    cout << "                         oooooooooooo   .oooooo.   ooooooooo.        ooooo     ooo  .oooooo..o ooooo ooooo      ooo   .oooooo.    \n";
    cout << "                         `888'     `8  d8P'  `Y8b  `888   `Y88.      `888'     `8' d8P'    `Y8 `888' `888b.     `8'  d8P'  `Y8b   \n";
    cout << "                          888         888      888  888   .d88'       888       8  Y88bo.       888   8 `88b.    8  888           \n";
    cout << "                          888oooo8    888      888  888ooo88P'        888       8   `\"Y8888o.   888   8   `88b.  8  888           \n";
    cout << "                          888    \"    888      888  888`88b.          888       8       `\"Y88b  888   8     `88b.8  888     ooooo \n";
    cout << "                          888         `88b    d88'  888  `88b.        `88.    .8'  oo     .d8P  888   8       `888  `88.    .88'  \n";
    cout << "                         o888o         `Y8bood8P'  o888o  o888o         `YbodP'    8\"\"88888P'  o888o o8o        `8   `Y8bood8P'\n";
    while (true) {
        // Get the current time
        auto end = chrono::high_resolution_clock::now();

        // Calculate the difference in time
        auto duration = chrono::duration_cast<chrono::seconds>(end - start).count();

        if (duration >= 3) {
            system("cls");
            break;
        }

        // Sleep for a while to prevent high CPU usage
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    clearscreen();
    intro();
    exit(0);
}

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

    transaction()
    {
        flag = 0;
    }
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

int suddenSpikeInSpending();                          // Segment Tree / Sliding Window
int detectOverlappingTransactions();                  // Interval Tree
int transactionValueAnomalies();                      // Binary Search / BST
int fraudLoopInTransactionHistory();                  // DFS / BFS (Cycle Detection)
int shortestFraudPathBetweenTransactions();           // Dijkstra
int clusterFraudlentTransactionsTogether();           // Union-Find / Kruskal
int merchantBasedFraudPatterns();                     // Trie
int trackFraudelentTransactionHistory();              // BST
int identifyTopSuspiciousTransactions();              // Priority Queue
int graduallyIncreasingFraudelentTransactionAmount(); // Dynamic Programming (LIS)
int unusualSpendingPatterns();                        // Knapsack

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

int main(){
    return 0;
}
