// calcul_meilleur_traj.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//


#include <iostream>
#include <winsock.h>
#include <mysql.h>
using namespace std;
int qstate;
int main(int n, char* params[])  /* Fonction principale. */
{
    int i;

    /* Affiche la ligne de commande : */
    for (i = 1; i < n; ++i)
        printf("Argument %d : %s.\n", i, params[i]);

	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "90.50.189.186", "root", "kwak", "atlantic_shipping_master", 3306, NULL, 0);

	if (conn) {
		puts("Successful connection to database!");

		string query = "SELECT * FROM port";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("ID: %s, Name: %s, Value: %s\n", row[0], row[1], row[2]);
			}
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("Connection to database has failed!");
	}

    return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
