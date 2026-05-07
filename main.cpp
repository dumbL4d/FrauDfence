#include <bits/stdc++.h>
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

// Clear Screen Function
void clearscreen() {
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
}

// EXIT SCREEN
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
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::seconds>(end - start).count();

            if (duration >= 3) {
                clearscreen();
                break;
            }
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        clearscreen();
        exit(0);
}

// Transaction Class
class transaction {
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

        transaction() {
            flag = 0;
        }
};

// Client Class
class client {
    public:
	string creditCardNumber;
        string cardHolderName;
        vector<transaction> arr;
        vector<int> spendings;
        int transactionsCompleted;
};

// READ CSV function
map<string, client> readCSVFile(const string& filename) {
        map<string, client> clients;
        ifstream file(filename);
        string line;
        getline(file, line); // Skip header

        while (getline(file, line)) {
            bool inQuotes = false;
            for (size_t i = 0; i < line.size(); ++i) {
                if (line[i] == '"') inQuotes = !inQuotes;
                else if (line[i] == ',' && inQuotes) line[i] = '|';
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

int graduallyIncreasingFraudelentTransactionAmount(); // Dynamic Programming (LIS)
int suddenSpikeInSpending();                          // Segment Tree / Sliding Window
int unusualSpendingPatterns();                        // Knapsack
int detectOverlappingTransactions();                  // Interval Tree
					      
// TO-DO List

int fraudLoopInTransactionHistory();		      // DFS / BFS (Cycle Detection)
int shortestFraudPathBetweenTransactions();	      // Djikstra
int clusterFraudlentTransactionsTogether();           // Union-Find / Kruskal
int trackFraudelentTransactionHistory();              // BST
int identifyTopSuspiciousTransactions();              // Priority Queue

// Tree for Segment Tree
vector<int> tree;

// Segment Tree Builder
void buildTree(const vector<int>& transactions, int node, int start, int end) {
	    if (start == end) {
		    tree[node] = transactions[start];
    	} else {
		int mid = (start + end) / 2;
        	buildTree(transactions, 2 * node + 1, start, mid);
        	buildTree(transactions, 2 * node + 2, mid + 1, end);
        	tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
    	}
}

// Segment Tree Query
int query(int node, int start, int end, int L, int R) {
    	if (R < start || L > end) return 0;
    	if (L <= start && R >= end) return tree[node];

    	int mid = (start + end) / 2;
    	return max(query(2 * node + 1, start, mid, L, R),
        	       query(2 * node + 2, mid + 1, end, L, R));
}

// Gradual Fraud Detection (LIS)
int graduallyIncreasingFraudelentTransactionAmount(const vector<int>& spendings) {
    	int n = spendings.size();
    	vector<int> dp(n, 1);

    	for (int i = 1; i < n; i++) {
        	for (int j = 0; j < i; j++) {
            		if (spendings[i] > spendings[j]) {
                		dp[i] = max(dp[i], dp[j] + 1);
        	   	}
        	}
    	}

    	int maxi = *max_element(dp.begin(), dp.end());
    	return maxi > 7;
}

// Sudden Spike Detection (Segment Tree)
int suddenSpikeInSpending(const vector<int>& transactions) {
	int n = transactions.size();
    	if (n == 0) return 0;

    	tree.clear();
    	tree.resize(4 * n);
    	buildTree(transactions, 0, 0, n - 1);

    	for (int i = 5; i < n; i++) {
        	int maxPrev5 = query(0, 0, n - 1, i - 5, i - 1);
        	if (transactions[i] > 10 * maxPrev5) {
            		return 1;
        	}
    	}
    	return 0;
}

// Structures of Interval Tree
struct Interval {
    double start, end;
};

struct Node {
    Interval *interval;
    double maxEnd;
    Node *left, *right;
};

// Functions for Interval Tree
Node* newNode(Interval i) {
    Node* node = new Node();
    node->interval = new Interval(i);
    node->maxEnd = i.end;
    node->left = node->right = nullptr;
    return node;
}

Node* insert(Node* root, Interval i) {
    if (!root) return newNode(i);
    
    int l = root->interval->start;
    if (i.start < l) root->left = insert(root->left, i);
    else root->right = insert(root->right, i);
    
    root->maxEnd = std::max(root->maxEnd, i.end);
    return root;
}

double extractTimeInMinutes(const string& dt) {
    double hour = stod(dt.substr(11, 2));
    double minute = stod(dt.substr(14, 2));
    double second = stod(dt.substr(17, 2));
    return hour * 60 + minute + (second / 60.0);  // fractional minute
}

bool doOverlap(Interval i1, Interval i2) {
    return (i1.start < i2.end && i2.start < i1.end);
}

bool overlapSearch(Node* root, Interval i) {
    if (!root) return false;
    if (doOverlap(*root->interval, i)) return true;
    if (root->left && root->left->maxEnd >= i.start)
        return overlapSearch(root->left, i);
    return overlapSearch(root->right, i);
}

int detectOverlappingTransactions(const vector<transaction>& txns) {
    Node* root = nullptr;
    double window = 1; // can be set to any fractional value

    for (const auto& t : txns) {
        double start = extractTimeInMinutes(t.transactionDateTime);
        Interval newTxn = {start, start + window};

        if (overlapSearch(root, newTxn)) {
            return 1;
        }

        root = insert(root, newTxn);
    }

    return 0;
}

// MAIN
int main() {
    	string filename = "fraudTestCSV.csv";
    	map<string, client> allClients = readCSVFile(filename);

	    for (auto& [card, clientObj] : allClients) {
		    // Sort transactions by date
    		sort(clientObj.arr.begin(), clientObj.arr.end(), [](const transaction& a, const transaction& b) {
        		return a.transactionDateTime < b.transactionDateTime;
    		});

    		// Clear and rebuild spendings in sorted order
    		clientObj.spendings.clear();
    		for (const auto& t : clientObj.arr) {
        		clientObj.spendings.push_back((int)t.amount);
    		}
	    }


    	for (const auto& [card, clientObj] : allClients) {
    		cout << "Checking for fraud on: " << clientObj.cardHolderName << endl;

    		bool fraud1 = graduallyIncreasingFraudelentTransactionAmount(clientObj.spendings);
    		cout << (fraud1 ? "Gradual Increase Fraud Detected!!" : "No Gradual Increase Fraud") << endl;

    		bool fraud2 = suddenSpikeInSpending(clientObj.spendings);
    		cout << (fraud2 ? "Sudden Spending Spike Detected!" : "No Sudden Spike") << endl;
		
		bool fraud3 = detectOverlappingTransactions(clientObj.arr);
		cout << (fraud3 ? "Overlapping Transactions Detected!" : "No Overlap Found") << endl;

    		cout << "----------------------------------------------------\n";
	    }

	    return 0;
}
