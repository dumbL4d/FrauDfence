#include <bits/stdc++.h>
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include <cfloat>
#include <unordered_set>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

using namespace std;

const string blue = "\033[1;34m";
const string black = "\033[30m";
const string red = "\033[31m";
const string green = "\033[32m";
const string yellow = "\033[33m";
const string magenta = "\033[35m";
const string cyan = "\033[36m";
const string white = "\033[37m";

// Clear Screen Function
void clearscreen()
{
	#ifdef _WIN32
    		system("cls");
	#else
    		system("clear");
	#endif
}

// INTRO SCR
void intro() {
	clearscreen();
	auto start = chrono::high_resolution_clock::now();

    	cout << "\033[1m"; // Bold text

    	cout << R"(
 	 	 _____                ____   __                     
 		|  ___| __ __ _ _   _|  _ \ / _| ___ _ __   ___ ___ 
 		| |_ | '__/ _` | | | | | | | |_ / _ \ '_ \ / __/ _ \
 		|  _|| | | (_| | |_| | |_| |  _|  __/ | | | (_|  __/
 		|_|  |_|  \__,_|\__,_|____/|_|  \___|_| |_|\___\___|
 	   )" << endl;

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
}

// EXIT SCR
void exitscr()
{
	clearscreen();
    	auto start = chrono::high_resolution_clock::now();

        cout << "\033[1m";
    	cout << yellow << R"(    
	     _   _                 _                             
            | | | |               | |                            
            | |_| |__   __ _ _ __ | | __   _   _  ___  _   _     
            | __| '_ \ / _` | '_ \| |/ /  | | | |/ _ \| | | |    
            | |_| | | | (_| | | | |   <   | |_| | (_) | |_| |    
             \__|_| |_|\__,_|_| |_|_|\_\   \__, |\___/ \__,_|    
                                            __/ |                
                                           |___/                 
                        __                        _              
                       / _|                      (_)             
                      | |_ ___  _ __    _   _ ___ _ _ __   __ _  
                      |  _/ _ \| '__|  | | | / __| | '_ \ / _` | 
                      | || (_) | |     | |_| \__ \ | | | | (_| | 
                      |_| \___/|_|      \__,_|___/_|_| |_|\__, | 
                                                           __/ | 
                                                          |___/  
	  )" << endl;
    	cout << endl;

    	while (true)
    	{
        	auto end = chrono::high_resolution_clock::now();
        	auto duration = chrono::duration_cast<chrono::seconds>(end - start).count();

        	if (duration >= 3)
        	{
            		clearscreen();
            		break;
        	}
        	this_thread::sleep_for(chrono::milliseconds(100));
    	}
    	clearscreen();
    	exit(0);
}

void getTerminalSize(int &rows, int &cols) {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    cols = w.ws_col;
    rows = w.ws_row;
#endif
}

// Function to display centered menu
void displayCenteredMenu(const vector<string> &menuItems) {
    int rows, cols;
    getTerminalSize(rows, cols);

    int menuHeight = menuItems.size();
    int maxLength = 0;
    for (const auto &item : menuItems)
        if (item.length() > maxLength)
            maxLength = item.length();

    int startRow = (rows - menuHeight) / 2;
    int startCol = (cols - maxLength) / 2;

    // Clear screen
    clearscreen();

    for (int i = 0; i < menuItems.size(); ++i) {
        cout << "\033[" << (startRow + i) << ";" << startCol << "H" << menuItems[i] << "\n";
    }
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

/*
int graduallyIncreasingFraudelentTransactionAmount(); // Dynamic Programming (LIS)
int suddenSpikeInSpending();                         // Segment Tree
int unusualSpendingPatterns();                       // Knapsack (Greedy)
int detectOverlappingTransactions();                 // Interval Tree
int fraudLoopInTransactionHistory();                 // DFS / BFS (Cycle Detection)
int shortestFraudPathBetweenTransactions();          // Djikstra Algorithm
int clusterFraudlentTransactionsTogether();          // Union-Find / Kruskal
*/

// Tree for Segment Tree
vector<int> tree;

// Segment Tree Builder
void buildTree(const vector<int> &transactions, int node, int start, int end)
{
        if (start == end)
        {
                tree[node] = transactions[start];
        }
        else
        {
                int mid = (start + end) / 2;
                buildTree(transactions, 2 * node + 1, start, mid);
                buildTree(transactions, 2 * node + 2, mid + 1, end);
                tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
}

// Segment Tree Query
int query(int node, int start, int end, int L, int R)
{
        if (R < start || L > end)
                return 0;
        if (L <= start && R >= end)
                return tree[node];

        int mid = (start + end) / 2;
        return max(query(2 * node + 1, start, mid, L, R),
                query(2 * node + 2, mid + 1, end, L, R));
}

// Gradual Fraud Detection (LIS)
int graduallyIncreasingFraudelentTransactionAmount(const vector<int> &spendings)
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

        int maxi = *max_element(dp.begin(), dp.end());
        return maxi > 7;
}

// Unusual Spending Pattern (Knapsack)
int unusualSpendingPatterns(const vector<transaction> &transactions)
{
        int n = transactions.size();
        int creditLimit = 200000; // Credit Limit set to 200000
        float totalSpending = 0.0;

        unordered_map<string, float> dailySpending;

        for (const auto &txn : transactions)
        {
                string date = txn.transactionDateTime.substr(0, 10);
                dailySpending[date] += txn.amount;
                if (dailySpending[date] > 500.00)
                        return 2;
                totalSpending += txn.amount;
        }

        if (totalSpending >= creditLimit)
                return 1;

        vector<bool> dp(creditLimit + 1, false);
        dp[0] = true;

        for (auto txn : transactions)
        {
                int amt = (int)(txn.amount + 0.5); // Rounding off the amount
                for (int j = creditLimit; j >= amt; j--)
                {
                        dp[j] = dp[j] || dp[j - amt];
                }
        }

        if (dp[creditLimit])
                return 1; // Alerts fraud if spending exactly reaches credit limit

        else
                return 0; // No fraud detected.
}

// Sudden Spike Detection (Segment Tree)
int suddenSpikeInSpending(const vector<int> &transactions)
{
        int n = transactions.size();
        if (n == 0)
                return 0;

        tree.clear();
        tree.resize(4 * n);
        buildTree(transactions, 0, 0, n - 1);

        for (int i = 5; i < n; i++)
        {
                int maxPrev5 = query(0, 0, n - 1, i - 5, i - 1);
                if (transactions[i] > 10 * maxPrev5)
                {
                        return 1;
                }
        }
        return 0;
}

// Structures of Interval Tree
struct Interval
{
        double start, end;
};

struct Node
{
        Interval *interval;
        double maxEnd;
        Node *left, *right;
};

// Functions for Interval Tree
Node *newNode(Interval i)
{
        Node *node = new Node();
        node->interval = new Interval(i);
        node->maxEnd = i.end;
        node->left = node->right = nullptr;
        return node;
}

Node *insert(Node *root, Interval i)
{
        if (!root)
                return newNode(i);

        int l = root->interval->start;
        if (i.start < l)
                root->left = insert(root->left, i);
        else
                root->right = insert(root->right, i);

        root->maxEnd = std::max(root->maxEnd, i.end);
        return root;
}

double extractTimeInMinutes(const string &dt)
{
        double hour = stod(dt.substr(11, 2));
        double minute = stod(dt.substr(14, 2));
        double second = stod(dt.substr(17, 2));
        return hour * 60 + minute + (second / 60.0); // fractional minute
}

bool doOverlap(Interval i1, Interval i2)
{
        return (i1.start < i2.end && i2.start < i1.end);
}

bool overlapSearch(Node *root, Interval i)
{
        if (!root)
                return false;
        if (doOverlap(*root->interval, i))
                return true;
        if (root->left && root->left->maxEnd >= i.start)
                return overlapSearch(root->left, i);
        return overlapSearch(root->right, i);
}

int detectOverlappingTransactions(const vector<transaction> &txns)
{
        Node *root = nullptr;
        double window = 1; // can be set to any fractional value

        for (const auto &t : txns)
        {
                double start = extractTimeInMinutes(t.transactionDateTime);
                Interval newTxn = {start, start + window};

                if (overlapSearch(root, newTxn))
                {
                        return 1;
                }

                root = insert(root, newTxn);
        }

        return 0;
}

struct UnionFind
{
        vector<int> parent, rank;
        UnionFind(int n)
        {
                parent.resize(n);
                rank.assign(n, 0);
                for (int i = 0; i < n; i++)
                {
                        parent[i] = i;
                }
        }

        int find(int x)
        {
                if (parent[x] != x)
                parent[x] = find(parent[x]);
                return parent[x];
        }

        void unite(int x, int y)
        {
                int rx = find(x);
                int ry = find(y);
                if (rx == ry)
                        return;
                if (rank[rx] < rank[ry])
                        parent[rx] = ry;
                else
                {
                        parent[ry] = rx;
                if (rank[rx] == rank[ry])
                        rank[rx]++;
                }
        }
};

int convertToMinutes(const string &dateTime)
{
        int hours = stoi(dateTime.substr(11, 2));
        int minutes = stoi(dateTime.substr(14, 2));
        return hours * 60 + minutes;
}

double haversine(double lat1, double lon1, double lat2, double lon2)
{
        const double R = 6371.0;
        double dLat = (lat2 - lat1) * M_PI / 180.0;
        double dLon = (lon2 - lon1) * M_PI / 180.0;
        lat1 *= M_PI / 180.0;
        lat2 *= M_PI / 180.0;

        double a = pow(sin(dLat / 2), 2) +
                pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        return R * c;
}

// Use of Union Find (Kruskal Algo to find count of cluster/rings of fraudelent transactions 
int clusterFraudlentTransactionsTogether(const vector<transaction> &transactions)
{
        vector<transaction> frauds;
        for (const auto &t : transactions)
                if (t.flag == 1)
                        frauds.push_back(t);
        int v = frauds.size();
        int n = frauds.size();
        cout << "Total Fraudulent Transactions in Country: " << n << endl;
        if (v <= 1)
                return v;
        float avgStateDiameter = 223.6;

        vector<tuple<double, int, int>> edges;

        for (int i = 0; i < n; ++i)
        {
                for (int j = i + 1; j < n; ++j)
                {
                        double dist = haversine(frauds[i].merchantLatitude, frauds[i].merchantLongitude,
                                        frauds[j].merchantLatitude, frauds[j].merchantLongitude);
                        int timeDiff = abs(convertToMinutes(frauds[i].transactionDateTime) -
                                        convertToMinutes(frauds[j].transactionDateTime));
                        if (dist < avgStateDiameter && timeDiff < 60)
                        {
                                edges.push_back({dist, i, j});
                        }
                }
        }
        sort(edges.begin(), edges.end());
        UnionFind uf(n);
        for (auto &[dist, u, v] : edges)
                uf.unite(u, v);

        set<int> clusters;
        for (int i = 0; i < n; ++i)
                clusters.insert(uf.find(i));

        return clusters.size();
}

// Djikstra Algorithm to detect immediate fraud connections that are not ususally discovered through fraudulent transactions clustering
int shortestFraudPathBetweenTransactions(const vector<transaction> &transactions)
{
    // Extract fraudulent transactions
        vector<transaction> frauds;
        for (const auto &t : transactions)
        {
                if (t.flag == 1)
                        frauds.push_back(t);
        }

        int n = frauds.size();
        if (n == 0)
                return 0;

    // Build adjacency list and record direct connections
        vector<vector<pair<int, double>>> adj(n);
        set<pair<int, int>> directEdges;

        for (int i = 0; i < n; ++i)
        {
                for (int j = 0; j < n; ++j)
                {
                        if (i == j)
                                continue;

                        double dist = haversine(
                                frauds[i].merchantLatitude, frauds[i].merchantLongitude,
                                frauds[j].merchantLatitude, frauds[j].merchantLongitude);

                        int timeDiff = abs(
                                convertToMinutes(frauds[i].transactionDateTime) -
                                convertToMinutes(frauds[j].transactionDateTime));

                        if (dist < 50 && timeDiff < 15)
                        {
                                adj[i].push_back({j, dist});
                                directEdges.insert({i, j});
                        }
                }
        }

        // Count indirect paths using Dijkstra
        int indirectPathCount = 0;

        for (int src = 0; src < n; ++src)
        {
                vector<double> dist(n, DBL_MAX);
                dist[src] = 0.0;
                priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
                pq.push({0.0, src});

                while (!pq.empty())
                {
                        auto [curDist, u] = pq.top();
                        pq.pop();
                        for (auto [v, weight] : adj[u])
                        {
                                if (dist[v] > curDist + weight)
                                {
                                        dist[v] = curDist + weight;
                                        pq.push({dist[v], v});
                                }
                        }
                }

                for (int dest = 0; dest < n; ++dest)
                {
                        if (src != dest && dist[dest] != DBL_MAX && !directEdges.count({src, dest}))
                        {
                                indirectPathCount++;
                        }
                }
        }

        return indirectPathCount;
}

const int MAX_CYCLE_LENGTH = 6;

string getCanonicalCycle(const vector<string>& cycle) {
    vector<string> temp = cycle;
    sort(temp.begin(), temp.end());
    string key;
    for (const string& s : temp) {
        key += s + "-";
    }
    return key;
}

void detectCyclesBFS(
    const string& startNode,
    const unordered_map<string, unordered_set<string>>& graph,
    unordered_set<string>& uniqueCycleHashes
) {
    queue<pair<string, vector<string>>> q;
    q.push(make_pair(startNode, vector<string>{startNode}));

    while (!q.empty()) {
        pair<string, vector<string>> front = q.front();
        q.pop();

        string current = front.first;
        vector<string> path = front.second;

        if (path.size() > MAX_CYCLE_LENGTH) continue;

        if (graph.find(current) != graph.end()) {
            const unordered_set<string>& neighbors = graph.at(current);
            for (unordered_set<string>::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it) {
                const string& neighbor = *it;

                if (neighbor == startNode && path.size() >= 3) {
                    string cycleKey = getCanonicalCycle(path);
                    uniqueCycleHashes.insert(cycleKey);
                } else if (find(path.begin(), path.end(), neighbor) == path.end()) {
                    vector<string> newPath = path;
                    newPath.push_back(neighbor);
                    q.push(make_pair(neighbor, newPath));
                }
            }
        }
    }
}

// Detect merchant cycles to uncover money laundering frauds 
int fraudLoopInTransactionHistory(const vector<transaction>& transactions) {
    unordered_map<string, unordered_set<string>> merchantToUsers;
    unordered_map<string, unordered_set<string>> graph;

    for (int i = 0; i < transactions.size(); ++i) {
        const transaction& tx = transactions[i];
        merchantToUsers[tx.merchantName].insert(tx.creditCardNumber);
    }

    for (unordered_map<string, unordered_set<string>>::const_iterator entry = merchantToUsers.begin(); entry != merchantToUsers.end(); ++entry) {
        const unordered_set<string>& users = entry->second;
        for (unordered_set<string>::const_iterator u1 = users.begin(); u1 != users.end(); ++u1) {
            for (unordered_set<string>::const_iterator u2 = users.begin(); u2 != users.end(); ++u2) {
                if (*u1 != *u2) {
                    graph[*u1].insert(*u2);
                }
            }
        }
    }

    unordered_set<string> uniqueCycleHashes;
    unordered_set<string> visited;

    for (unordered_map<string, unordered_set<string>>::const_iterator it = graph.begin(); it != graph.end(); ++it) {
        const string& startNode = it->first;
        if (visited.find(startNode) == visited.end()) {
            detectCyclesBFS(startNode, graph, uniqueCycleHashes);
            visited.insert(startNode);
        }
    }

    return static_cast<int>(uniqueCycleHashes.size());
}

// MAIN
int main()
{
	intro();
	cout << "Transaction Data is being imported..." << endl;
        string filename = "fraudTestCSV.csv";
        map<string, client> allClients = readCSVFile(filename);
        vector<transaction> allTransactions;
	for (auto &it : allClients)
	{
                string card = it.first;
                client &clientObj = it.second;
                // Sort transactions by date
                sort(clientObj.arr.begin(), clientObj.arr.end(), [](const transaction &a, const transaction &b)
                        { return a.transactionDateTime < b.transactionDateTime; });

                // Clear and rebuild spendings in sorted order
                clientObj.spendings.clear();
                for (const auto &t : clientObj.arr)
                {
                        clientObj.spendings.push_back((int)t.amount);
                        allTransactions.push_back(t); // Collect all transactions globally
                }
        }
	

	vector<string> menu = {
		"+-----------------------------------------------+",
        	"|                 FRAUD MENU                    |",
        	"+-----------------------------------------------+",
        	"| 1. Gradual Increase Fraud                     |",
        	"| 2. Sudden Spike in Spending Fraud             |",
        	"| 3. Overlapping Transactions Fraud             |",
		"| 4. Unusual Spending Pattern Fraud             |",
        	"| 5. Fraud Clusters                             |",
        	"| 6. Indirect Fraud Paths                       |",
        	"| 7. Exit                                       |",
        	"+-----------------------------------------------+"
    	};

	displayCenteredMenu(menu);
	int choice;
	do 
	{
		cout << "Enter your choice: ";
		cin >> choice;

		if (choice == 1)
		{
			int i = 1;
			for(const auto& [card, clientObj] : allClients)
			{
				cout << i++ << ". \n";
				cout << yellow << "Checking fraud on: " << white << clientObj.cardHolderName << endl;
				bool fraud1 = graduallyIncreasingFraudelentTransactionAmount(clientObj.spendings);
				cout << (fraud1 ? (red + "Gradual Increase Fraud Detected!!") : (green + "No Gradual Increase Fraud")) << endl;
				cout << blue << "----------------------------------------------------\n";
			}
		}
		else if(choice == 2)
		{
			int i = 1;
			for(const auto& [card, clientObj] : allClients)
			{
				cout << i++ << ". \n";
				cout << yellow << "Checking fraud on: " << white << clientObj.cardHolderName << endl;
				bool fraud2 = suddenSpikeInSpending(clientObj.spendings);
				cout << (fraud2 ? (red + "Sudden Spending Spike Detected!!") : (green + "No Sudden Spike")) << endl;
				cout << blue << "----------------------------------------------------\n";
			}
		}
		else if(choice == 3)
		{
			int i = 1;
			for(const auto& [card, clientObj] : allClients)
			{
				cout << i++ << ". \n";
				cout << yellow << "Checking fraud on: " << white << clientObj.cardHolderName << endl;
				int fraud3 = detectOverlappingTransactions(clientObj.arr);
				cout << (fraud3 ? (red + "Overlapping Transactions Detected !!") : (green + "No Overlapping Transactions")) << endl;
				cout << blue << "----------------------------------------------------\n";
			}
		}
		else if(choice == 4)
		{
			int i = 1;
			for (const auto& [card, clientObj] : allClients)
			{
				cout << i++ << ". \n";
				cout << yellow << "Checking fraud on: " << white << clientObj.cardHolderName << endl;
				int fraud4 = unusualSpendingPatterns(clientObj.arr);
				if (fraud4 == 2)
					cout << red << "Daily Spending Limit Exceeded!!" << endl;
				else if(fraud4 == 1)
					cout << yellow << "Transactions are optimized to max out the limit - Potential Fraud" << endl;
				else
					cout << green << "Transaction Pattern is normal" << endl;
				cout << blue << "----------------------------------------------------\n";
			}
		}
		else if(choice == 5)
		{
			int fraudClusters = clusterFraudlentTransactionsTogether(allTransactions);
			
			if (fraudClusters > 20)
			{
				cout << red << "Country Fraud Clusters Found: " << fraudClusters << endl;
			}
			else
				cout << green << "Country Fraud Clusters Found: " << fraudClusters << endl;
			cout << blue << "----------------------------------------------------\n";
		}
		else if(choice == 6)
		{
			int indirectPaths = shortestFraudPathBetweenTransactions(allTransactions);
        		cout << magenta << "Total Indirect Fraud Paths: " << white << indirectPaths << endl;
			cout << blue << "----------------------------------------------------\n";
		}
		else if(choice == 7)
		{
			exitscr();
		}
		else
		{
			cout << red << "INVALID CHOICE!!" << white << endl;
		}
		char f;
		cin >> f;
		displayCenteredMenu(menu);
		cout << white;
	}while(true);

        
        // Detecting money laundering cycles using DFS cycle detection
	// int count = fraudLoopInTransactionHistory(allTransactions);
        // cout << "Fraud cycles detected: " << count << endl;

    return 0;
}
