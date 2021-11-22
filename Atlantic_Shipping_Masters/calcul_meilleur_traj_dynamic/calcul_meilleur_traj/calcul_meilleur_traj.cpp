#include <iostream>
#include <string>
#include <winsock.h>
#include <mysql.h>
#include <vector>
#include <algorithm>
#include<limits.h>
using namespace std;


#define sizeP 20 //maximum 20 ports
#define min(a,b) a>b?b:a
#define sizePOW 1048576 // 2^20
//Space complexity: O(n * 2^n)
//Time complexity: O(n^2 * 2^n)
int n, npow, g[sizeP][sizePOW], p[sizeP][sizePOW];
vector<vector<int>> adj;
int qStateDistance, qStatePort;
vector<string> portList;
vector<vector<string>> distanceList;

int compute(int start, int set)
{
	int masked, mask, result = INT_MAX, temp, i;//result stores the minimum 
	if (g[start][set] != -1)//memoization DP top-down,check for repeated subproblem
		return g[start][set];
	for (i = 0; i < n; i++)
	{	//npow-1 because we always exclude "home" vertex from our set
		mask = (npow - 1) - (1 << i);//remove ith vertex from this set
		masked = set & mask;
		if (masked != set)//in case same set is generated(because ith vertex was not present in the set hence we get the same set on removal) eg 12&13=12
		{
			temp = adj[start][i] + compute(i, masked);//compute the removed set
			if (temp < result)
				result = temp, p[start][set] = i;//removing ith vertex gave us minimum
		}
	}
	return g[start][set] = result;//return minimum
}


void getpath(int start, int set)
{
	if (p[start][set] == -1) return;//reached null set
	int x = p[start][set];
	int mask = (npow - 1) - (1 << x);
	int masked = set & mask;//remove p from set
	cout << portList[x] << endl;
	getpath(x, masked);
}


void TSP()
{
	int i, j;
	//g(i,S) is length of shortest path starting at i visiting all vertices in S and ending at 1
	for (i = 0; i < n; i++)
		for (j = 0; j < npow; j++)
			g[i][j] = p[i][j] = -1;
	for (i = 0; i < n; i++)g[i][0] = adj[i][0];//g(i,nullset)= direct edge between (i,1)
	int result = compute(0, npow - 2);//npow-2 to exclude our "home" vertex
	// printf("%d\n", result);
	cout << portList[0] << endl;
	getpath(0, npow - 2);
	cout << portList[0] << endl;
}


// create Graph from Pulled request
vector<vector<int>> makeGraph(vector<vector<string>> data, int a) {
	vector<vector<int>> myGraph;
	float lineSize = data.size() / a;

	for (int i = 0; i < data.size(); i += lineSize) {
		vector<int> graphLine = {};
		for (int j = 0; j < lineSize; j++) {
			graphLine.push_back(stoi(data[i + j][2]));
			// cout << data[i + j][0] << " : " << data[i + j][1] << " : " << data[i + j][2] << endl;
		}
		myGraph.push_back(graphLine);
	}
	return myGraph;
};


int main(const int a, char* params[])
{
	// ==================================
	//       Pull Data From DataBase
	// ==================================

	// Formating parameters for SQL request
	string ids = "(";
	for (int i = 1; i < a; i++) {
		string id = params[i];
		ids += id + ",";
	}
	ids[ids.size() - 1] = ')';

	// SQL variables
	MYSQL* conn;
	MYSQL_ROW rowD;
	MYSQL_ROW rowP;
	MYSQL_RES* distances;
	MYSQL_RES* ports;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "atlantic_shipping_master", 3306, NULL, 0);

	// SQL request
	if (conn) {
		// puts("Successful connection to database!");

		// request for selected ports
		string queryPort = "SELECT name FROM port WHERE id IN " + ids;
		const char* qP = queryPort.c_str();
		qStatePort = mysql_query(conn, qP);

		// Stocking returned values
		string portSql = "(";
		if (!qStatePort) {
			ports = mysql_store_result(conn);
			while (rowP = mysql_fetch_row(ports)) {
				string port = rowP[0];
				portList.push_back(port); // Stocking returned ports
				portSql += "\"" + port + "\","; // Formating returned port for SQL request
			}
			portSql[portSql.size() - 1] = ')';
		}
		else {
			cout << "Query failed: " << mysql_error(conn) << endl;
		}

		// request for distances between selected ports
		string queryDistance = "SELECT * FROM distances WHERE port_dep IN " + portSql + " AND port_arr IN " + portSql;
		const char* qD = queryDistance.c_str();
		qStateDistance = mysql_query(conn, qD);

		// Stocking returned values
		if (!qStateDistance) {
			distances = mysql_store_result(conn);
			while (rowD = mysql_fetch_row(distances)) {
				distanceList.push_back({ rowD[1], rowD[2], rowD[3] });
			}
		}
		else {
			cout << "Query failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("Connection to database has failed!");
	}
	n = a - 1;
	adj = makeGraph(distanceList, n);
	npow = (int)pow(2, n);
	TSP();
	return 0;
}