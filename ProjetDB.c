/*=============================================================================

  Name: ProjetBD.c
 
  Auth: 16/01/2018, Arthur Journ�, Pierre-Louis R�rolle, Nicolas Anciaux


=============================================================================*/

#include <ocilib.h>			// OCILIB (to call Oracle OCI)
#include <stdio.h>			
#include <stdlib.h>
#include <string.h>			// inclue pour strchr()
 
int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;
    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, stdin) != NULL)  // Si la saisie se fait sans erreur
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entr�e"
        if (positionEntree != NULL) // Si on a trouv� le retour � la ligne
            *positionEntree = '\0'; // On remplace ce caract�re par \0
        return 1; // On renvoie 1 si la fonction s'est d�roul�e sans erreur
    }
    else
        return 0; // On renvoie 0 s'il y a eu une erreur
}

int connect_dbms(OCI_Connection **cn, int affiche) { // L'entier affiche determine si on affiche les infos de connexion

	char* login = "system";		// login SGBD
	char* mdp = "oracle";	// mot de passe SGBD
	char* sgbd = "XE";		// nom SGBD pour la connection ODBC (voir doc du SGBD)

	// V�rification de l'initialisation de la librairie OCILIB:
	if ( !OCI_Initialize(NULL, NULL, OCI_ENV_DEFAULT) )
		return EXIT_FAILURE;

	// Creation d'une connection vers le SGBD source:
	//    /!\ indiquez un login/mdp correct
	*cn = OCI_ConnectionCreate(sgbd, login, mdp, OCI_SESSION_DEFAULT);
	
	// Si la connection a �t� �tablie corectement, afficher ses propri�t�s:
	if(cn != NULL && affiche == 1){
		printf(OCI_GetVersionServer(*cn));
		printf("Server major    version : %i\n", OCI_GetServerMajorVersion(*cn));
		printf("Server minor    version : %i\n", OCI_GetServerMinorVersion(*cn));
		printf("Server revision version : %i\n", OCI_GetServerRevisionVersion(*cn));
		printf("Connection      version : %i\n \n", OCI_GetVersionConnection(*cn));
	}
  
	return EXIT_SUCCESS;
}

int executeQuery(char* query, OCI_Connection* cn, int affiche) // L'entier affiche sert � indiquer si l'on souhaite afficher les r�sultats de la requete 
{
	
    OCI_Statement* st;
    OCI_Resultset* rs;
	int nb_col;
	int i=0;
	OCI_Column *col;
	int nb_row;

	// Cr�ation d'une requ�te � partir de la connexion:
    st = OCI_StatementCreate(cn);

	// Execution de la requ�te:
	OCI_ExecuteStmt(st, query);
 
	// Stockage du r�sultat de la requete dans un resultset:
    rs = OCI_GetResultset(st);

	// R�cup�ration du nombre de colonnes du r�sultat:
	nb_col = OCI_GetColumnCount (rs);

	if (affiche == 1) // En cas de connection, on n'a pas besoin d'afficher le tuple
	{
		// affichage des noms de colonnes:
		for(i=0; i<nb_col; i++)
		{
			col = OCI_GetColumn (rs, i+1);
			printf("%s | ", OCI_ColumnGetName (col));
		}
		printf("\n");
		
	}


	// Parcours et affichage des lignes du r�sultat:
    while (OCI_FetchNext(rs))
    {
		// r�cup�ration de chaque valeur de colonne sous forme de chaine
		// et affichage des valeurs: 
		for(i=0; i<nb_col; i++)
		{
			if (affiche == 1) printf("%s | ", OCI_GetString(rs,i+1));


		}
		printf("\n");
		
    }
    // On r�cup�re le nombre de colonnes fetched
    nb_row = OCI_GetRowCount(rs);

	// lib�ration des ressources de la librairie OCILIB:
    OCI_Cleanup();

	return nb_row;
}

int main( int argc, char *argv[] )
{
	char query[50];
	strcpy(query,"select * from id where login = '");	// 	D�but de la requ�te � ex�cuter
	OCI_Connection* cn;
	int exit_code;		
	char login[50];
	char pwd[50];
	int nb_row;

	// On se connecte � la base de donn�e:
	exit_code = connect_dbms(&cn, 1);


	// Lecture du login/pwd
	printf("Login ? ");
	lire(login, 50);
	strcat(query, login);
	strcat(query, "' and mdp = '");
	printf("Pwd ? ");
	lire(pwd, 50);
	strcat(query, pwd);
	strcat(query, "'");

	// On execute la requete, ici sans afficher le r�sultat
	nb_row = executeQuery(query, cn, 1);
	
	if (nb_row == 1) {	  // Si le resultat produit 1 seule ligne, c'est que le couple login/password est bon	
		printf("%s", "Connexion acceptee ! Quelle cat�gorie de voiture souhaitez-vous louer ? \n \n");
		printf("%s", "Les cat�gories sont : A, B,C, D, E. \n \n ");
		char cat[50];
		char query_cat[50];
		strcpy(query_cat, "select idvoit from voit where cat = '");
		lire(cat, 50);
		strcat(query_cat, cat);
		strcat(query_cat, "'");
		int nb_row_cat;
		int exit;
		OCI_Connection *cn2;
		exit = connect_dbms(&cn2, 0);
		nb_row_cat = executeQuery(query_cat, cn2, 1);
		
		
		if (nb_row_cat == 0) printf("Il n'y a pas de voitures correspondant � cette categorie. \n \n");
	}
	else
		{
			printf("Erreur : login ou mot de passe incorrect ! \n");
		}
		

    return exit_code;
}

