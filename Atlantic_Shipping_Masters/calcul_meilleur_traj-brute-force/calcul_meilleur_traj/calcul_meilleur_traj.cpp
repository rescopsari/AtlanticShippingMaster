#include <iostream>
#include <string>
#include <winsock.h>
#include <mysql.h>
#include <vector>
#include <algorithm>
using namespace std;

// ==================================
//        Travelling Salesman
// ==================================

// create Graph from Pulled request
vector<vector<int>> makeGraph(vector<vector<string>> data, int n) {
	vector<vector<int>> myGraph;
	float lineSize = data.size() / n;

	for (int i = 0; i < data.size(); i += lineSize) {
		vector<int> graphLine = {};
		for (int j = 0; j < lineSize; j++) {
			graphLine.push_back(stoi(data[i+j][2]));
			// cout << data[i + j][0] << " : " << data[i + j][1] << " : " << data[i + j][2] << endl;
		}
		myGraph.push_back(graphLine);
	}
	return myGraph;
};

// Salesman Algorithm
vector<int> travllingSalesmanProblem(vector<vector<int>> graph, int s)
{
	// store all vertex apart from source vertex
	vector<int> vertex;
	for (int i = 0; i < graph.size(); i++)
		if (i != s)
			vertex.push_back(i);

	int min_path = INT_MAX;
	vector<int> trajet;
	do {
		// store current Path weight(cost)
		int current_pathweight = 0;
		
		// compute current path weight
		int k = s;
		for (int i = 0; i < vertex.size(); i++) {
			current_pathweight += graph[k][vertex[i]];
			k = vertex[i];
		}
		current_pathweight += graph[k][s];

		// update minimum
		if (min_path >= current_pathweight) {
			trajet = vertex;
			min_path = current_pathweight;
		}
		// min_path = min(min_path, current_pathweight);
	} while (next_permutation(vertex.begin(), vertex.end()));
	return trajet;
	//do {
	//	// store current Path weight(cost)
	//	int current_pathweight = 0;

	//	// compute current path weight
	//	int k = s;
	//	for (int i = 0; i < vertex.size(); i++) {
	//		current_pathweight += graph[k][vertex[i]];
	//		k = vertex[i];
	//	}
	//	current_pathweight += graph[k][s];

	//	if (current_pathweight == min_path) {
	//		//return vertex;
	//		printf("yes");
	//	}
	//} while (next_permutation(vertex.begin(), vertex.end()));
	//return trajet;
}





int qStateDistance, qStatePort;
int main(int n, char* params[])
{
	// ==================================
	//       Pull Data From DataBase
	// ==================================

	// Formating parameters for SQL request
	string ids = "(";
	for (int i = 1; i < n; i++) {
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
	
	// variables
	vector<string> portList;
	vector<vector<string>> distanceList;

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

	vector<vector<int>> myGraph = makeGraph(distanceList, n-1);
	cout << portList[0] << endl;
	for (int id : travllingSalesmanProblem(myGraph, 0)) {
		cout << portList[id] << endl;
	}
	cout << portList[0] << endl;

    return 0;
}
