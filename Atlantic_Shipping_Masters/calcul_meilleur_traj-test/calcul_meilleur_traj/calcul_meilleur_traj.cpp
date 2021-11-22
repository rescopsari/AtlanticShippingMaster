#include <iostream>
#include <string>
#include <winsock.h>
#include <mysql.h>
#include <vector>
#include <algorithm>
#include <bitset>
using namespace std;

/**
    \brief Given a complete, undirected, weighted graph in the form of an adjacency matrix,
           returns the smallest tour that visits all nodes and starts and ends at the same
           node. This dynamic programming solution runs in O(n * 2^n).
    \return the minimum cost to complete the tour
*/
vector<vector<int>> tsp(const vector<vector<int>>& map, int pos, int visited, vector<vector<int>>& state, vector<int>& path)
{
	//cout << visited << endl;
	if (visited == ((1 << map.size()) - 1)) {
		//cout << "Distance : " << state[pos][0] << endl;
		//cout << "Visited : " << bitset<32>(visited).to_string().substr(32 - map.size()) << endl;
		//cout << "Pos : " << pos << endl;
		path.push_back(0);
		return { { map[pos][0], visited, pos }, path }; // return to starting city
	}

	if (state[pos][visited] != INT_MAX) {
		//cout << "Distance : " << state[pos][visited] << endl;
		//cout << "Visited : " << bitset<32>(visited).to_string().substr(32 - map.size()) << endl;
		//cout << "Pos : " << pos << endl;
		//path.push_back(pos);
		return { { state[pos][visited], visited, pos }, path };
	}

    for (int i = 0; i < map.size(); ++i)
    {
        // can't visit ourselves unless we're ending & skip if already visited
        if (i == pos || (visited & (1 << i)))
            continue;

        int distance = map[pos][i] + tsp(map, i, visited | (1 << i), state, path)[0][0];
		if (distance < state[pos][visited]) {
			state[pos][visited] = distance;
			path.push_back(pos);
		}
    }
	/*cout << "Distance : " << state[pos][visited] << endl;
	cout << "Visited : " << bitset<32>(visited).to_string().substr(32-map.size()) << endl;
	cout << "Pos : " << pos << endl;*/
	return { { state[pos][visited], visited, pos }, path };
}






// create Graph from Pulled request
vector<vector<int>> makeGraph(vector<vector<string>> data, int n) {
    vector<vector<int>> myGraph;
    float lineSize = data.size() / n;

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

int qStateDistance, qStatePort;
int main(const int n, char* params[])
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

	vector<vector<int>> map = makeGraph(distanceList, n - 1);

	vector<vector<int>> state(map.size());
	for (auto& neighbors : state)
		neighbors = vector<int>((1 << map.size()) - 1, INT_MAX);

	vector<int> path = { 0 };
	vector<vector<int>> resultTSP = tsp(map, 0, 1, state, path);
	int distPath = resultTSP[0][0];
	string visited = bitset<32>(resultTSP[0][1]).to_string().substr(32 - map.size());
	int pos = resultTSP[0][2];


	cout << "==============================================" << endl;
	cout << "Distance du trajet : " << distPath << endl;
	cout << "==============================================" << endl;
	/*cout << portList[0] << endl;
	for (int id : travllingSalesmanProblem(map, distPath)) {
		cout << portList[id] << endl;
	}
	cout << portList[0] << endl;*/

    return 0;
}
