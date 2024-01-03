//----------------------------------------------------------------------
//
//						TP3 mini projet: gestion de course SKI
//
// Cet Agorithme permet la gestion d'une course de SKI, on entre le nom,le num dossard, le temps d'un joueur
//     l'algo fait le classement des joeurs en deux listes: abandonnés et non abandonnés
//
// 04/12/2019
//
// Channel NIANGA
// Licence SPI-EEAPR - UniversitŽ de Lorraine
//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100 // N est une constante qui represent la taille max que prend le nom du joueur

// Déclaration des types composés
// type temps
typedef struct Temps Temps; // cette ligne me permet de remplacer struct temps par temps
struct Temps
{
	int min; // la minute que fait le joeur
	int sec; // la seconde que fait le joeur
	int centSec; // la centième de seconde
};

// La structure joueur qui caracterise les infos du joueurs
typedef struct Skieur Skieur;
struct Skieur
{
	char nom[N];  // nom du joueur
	int numero_dossard;// le numero de dossard du joeur
	Temps temps_1er_manche; // le temps de premier manche de type temps;
	Temps temps_2e_manche;
	Temps temps_total;

};

typedef struct Liste Liste;
struct Liste
{
	Skieur premier;
	Liste *suivant;
};

int main()
{
	Liste *players; // la liste des coureurs qui ont réussi
	Liste *abandonnes; // la liste des joueurs qui ont abandonné
	Liste *newplayer; // on crée un maillon pour chaque enregistrement d'un nouveau joueur
	int continuer;// permet de rentrer une nouvelle info tant que l'utilisateur le veut
	int joueurReussi; // définit si le joueur qui a reussi la premiere a aussi réussi la 2eme
	int joueurAban; // définit si le joeur a abandonné ou pas la premiere manche
	int ancienNum; // memorise les  numero dossard des joeurs pour eviter des numeros identiques
	int compareNom; // evite les noms identiques
	int convertTemps; // on fait la converssion et on garge dans cette variable
	int maillon;
	Liste *p, *a, *tmp, *w, *copieListe, *ecartTemp, *mini, *q, *tempsMoy;

	/* Initialisation des variables*/
	continuer = 1; // on initialise continuer pour faire la repetition
	ancienNum = -1;
	players = NULL, abandonnes = NULL; // on suppose qu'au début les deux listes sont vides

	printf("********      *   *   ********* \n");
	printf("*             *  *        *     \n");
	printf("********      * *         *     \n");
	printf("       *      *   *       *     \n");
	printf("********      *    *  ********* \n");

	printf("\n\n");
	printf("Cette Alplication vous permet de gerer une course de Ski en entrant les infos de chaque joeurs\n");
	printf("\n\n");
	printf(">>>>>>>>>>>>>>>>PREMIERE MANCHE<<<<<<<<<<<<<<<\n");
	printf("\n");
	do
	{
		newplayer = (Liste *)malloc(sizeof(Liste)); // on crée un maillon pour chaque nouveau joueur


		printf("Entrez les infos d'un nouveau joueur\n");
		printf("\n\n");
		//saisi nom skieur

		printf("Entrez le nom du joueur:\t");
		scanf("%s", &newplayer->premier.nom);
		
	
		printf("\n\n");
		//saisi  numero dossard  du joueur
		do
		{
			printf("Entrez le numero dossard du joeur sup a 0:\t");
			scanf("%d", &newplayer->premier.numero_dossard);
			if (newplayer->premier.numero_dossard == ancienNum || newplayer->premier.numero_dossard < 1)
			{
				printf("Verifiez que le numero entre n'est pas identique a un autre joeur ou inf a 1\n");
			}

		} while (newplayer->premier.numero_dossard == ancienNum || newplayer->premier.numero_dossard < 1); // on verifie si un joeur porte le meme num ou si le numero est inf à 1
		ancienNum = newplayer->premier.numero_dossard; // on fait une copie du numero saisi pour eviter un numero identique
		printf("\n\n");

		do
		{
			printf("Situation du joeur:\n");
			printf("\n>> Tapez 1 si le joeur a abandonne\n");
			printf("\n>> Tapez 0 si le joeur n'a pas abandonne\n");
			printf("\n>> Faites votre choix:\t");
			scanf("%d", &joueurAban);
			printf("\n");

		} while (joueurAban != 1 && joueurAban != 0); // on oblige l'ulisateur à tapez 1 ou 0

		if (joueurAban == 1) // Si le joeur a abandonné la course
		{
			/* on ne compte pas son temps et on l'ajoute alors dans la liste de ceux qui ont abandonnés*/
			newplayer->premier.temps_1er_manche.min = 0;
			newplayer->premier.temps_1er_manche.sec = 0;
			newplayer->premier.temps_1er_manche.centSec = 0;
			newplayer->premier.temps_total.min = 0;
			newplayer->premier.temps_total.sec = 0;
			newplayer->premier.temps_total.centSec = 0;
			newplayer->suivant = abandonnes;
			abandonnes = newplayer;
		}
		else
		{
			/* Si le joueur n'a pas abandonné la course , on demande le temps qu'il a fait et on l'ajoute dans la liste des players*/
			/* On fait une boucle pour eviter que le temps soit nul c'est a dire la min la seconde et centieme de seconde ne peuvent pas etre à la fois nul */
			/* car l'utilisateur a dit que le joueur a réussi*/
			do
			{
				printf("La min, seconde et centieme seconde ne peuvent pas etre a la fois nuls\n");
				printf("\n\n");
				// saisi de la minute faite par le skieur
				do
				{
					printf("Entrez la min qu'a fait le joueur (entre 0 et 60):\t");
					scanf("%d", &newplayer->premier.temps_1er_manche.min);

				} while (newplayer->premier.temps_1er_manche.min < 0 || newplayer->premier.temps_1er_manche.min>60);
				printf("\n\n");

				// saisi de la seconde faite par le skieur
				do
				{
					printf("Entrez la seconde qu'a fait le joueur (entre 0 et 60):\t");
					scanf("%d", &newplayer->premier.temps_1er_manche.sec);

				} while (newplayer->premier.temps_1er_manche.sec < 0 || newplayer->premier.temps_1er_manche.sec>60);
				printf("\n\n");

				// saisi de la centieme seconde faite par le skieur
				do
				{
					printf("Entrez la centieme de seconde  (entre 0 et 100):\t");
					scanf("%d", &newplayer->premier.temps_1er_manche.centSec);

				} while (newplayer->premier.temps_1er_manche.centSec < 0 || newplayer->premier.temps_1er_manche.centSec>100);
				printf("\n\n");

			} while ((newplayer->premier.temps_1er_manche.min || newplayer->premier.temps_1er_manche.sec || newplayer->premier.temps_1er_manche.centSec) == 0);
			// On ajoute l'information du joueur dans la liste de ceux qui ont reuissi
			newplayer->suivant = players;// on garde d'abord la liste d'avant
			players = newplayer;  // le nouveau joueur est ajouté en debut de la liste
		}

		do
		{
			// On demande l'utilisateur s'il veut saisir une nouvelle info
			printf("Fin de l'enregistrement\n");
			printf("\n>> Tapez 1 pour un nouveau enregistrement\n");
			printf("\n>> Tapez 0 si vous voulez arreter\n");
			printf("\n>> choix:\t");
			scanf("%d", &continuer);
			printf("\n");

		} while (continuer != 0 && continuer != 1);

	} while (continuer == 1);

	printf("**********AFICHAGE PREMIERE MANCHE************\n");
	printf("\n\n");

	printf("la liste des coureurs \n");
	printf("\n");
	p = players;

	while (p != NULL)
	{
		printf("%s\tnumero\t%d\ta fait\t%dmin %ds %dcs\n", p->premier.nom, p->premier.numero_dossard, p->premier.temps_1er_manche.min, p->premier.temps_1er_manche.sec, p->premier.temps_1er_manche.centSec);
		p = p->suivant;
	}
	//Affichage de la liste des abandons
	printf("\n\n");
	printf("la liste de ceux qui ont abandonnes \n");
	printf("\n");
	a = abandonnes;

	while (a != NULL)
	{
		printf("%s\tnumero\t%d\ta fait\t%dmin %ds %dcs\n", a->premier.nom, a->premier.numero_dossard, a->premier.temps_1er_manche.min, a->premier.temps_1er_manche.sec, a->premier.temps_1er_manche.centSec);
		a = a->suivant;
	}
	printf("\n**************FIN DE LA PREMIERE MANCHE***************\n");
	printf("\n\n");
	/* pendant la deuxieme on verifie pour chaque joueur qui a reussi la premiere,s'il a aussi réussi la 2eme */
	/*  si c'est le cas on cumul les deux temps sinon on met le joeur dans la liste de ceux qui ont abandonné*/

	printf(">>>>>>>>>>>>>>>>  2EME MANCHE<<<<<<<<<<<<<<<\n");

	p = players; // on utilise p pour ne pas perdre les données de la liste players
	copieListe = NULL; // cette variable nous permettra de copier les données de tous les joueurs qui ont réussi

	while (p != NULL)
	{
		// on demande l'utilisateur si le Skieur a reussi la 2eme manche
		// en affichant son nom et son numero dossard
		printf("\n\n");
		printf("%s numero %d a t il reussi la 2eme manche ?\n", p->premier.nom, p->premier.numero_dossard);
		do
		{
			printf("\n>> Tapez 1 Si oui\n");
			printf("\n>> Tapez 0 sinon\n");
			printf("\nVotre choix:\t");
			scanf("%d", &joueurReussi);

		} while (joueurReussi != 0 && joueurReussi != 1);
		if (joueurReussi == 1)
		{
			/* Si le skieur a réussi on demande le temps realisé comme à la premiere manche*/
			do
			{
				printf("\nLa min, seconde et centieme seconde ne peuvent pas etre a la fois nuls\n");
				printf("\n\n");
				// saisi de la minute faite par le skieur
				do
				{
					printf("Entrez la min qu'a fait le joueur (entre 0 et 60):\t");
					scanf("%d", &p->premier.temps_2e_manche.min);

				} while (p->premier.temps_2e_manche.min < 0 || p->premier.temps_2e_manche.min>60);
				printf("\n\n");

				// saisi de la seconde faite par le skieur
				do
				{
					printf("Entrez la seconde qu'a fait le joueur (entre 0 et 60):\t");

					scanf("%d", &p->premier.temps_2e_manche.sec);

				} while (p->premier.temps_2e_manche.sec < 0 || p->premier.temps_2e_manche.sec > 60);
				printf("\n\n");

				// saisi de la centieme seconde  faite par le skieur
				do
				{
					printf("Entrez la centieme de seconde  (entre 0 et 100):\t");
					scanf("%d", &p->premier.temps_2e_manche.centSec);

				} while (p->premier.temps_2e_manche.centSec < 0 || p->premier.temps_2e_manche.centSec>100);
				printf("\n\n");

			} while ((p->premier.temps_2e_manche.min || p->premier.temps_2e_manche.sec || p->premier.temps_2e_manche.centSec) == 0);


			/*on crée un nouvelle liste pour copier les données des joueurs qui ont réussi*/
			/* on fait la copie dans liste copieListe*/

			tmp = (Liste *)malloc(sizeof(Liste));
			strcpy(tmp->premier.nom, p->premier.nom);
			tmp->premier.numero_dossard = p->premier.numero_dossard;

			tmp->premier.temps_1er_manche.min = p->premier.temps_1er_manche.min;
			tmp->premier.temps_1er_manche.sec = p->premier.temps_1er_manche.sec;
			tmp->premier.temps_1er_manche.centSec = p->premier.temps_1er_manche.centSec;

			tmp->premier.temps_2e_manche.min = p->premier.temps_2e_manche.min;
			tmp->premier.temps_2e_manche.sec = p->premier.temps_2e_manche.sec;
			tmp->premier.temps_2e_manche.centSec = p->premier.temps_2e_manche.centSec;

			/* on fait le cumul des temps de la premiere et deuxieme manche*/
			tmp->premier.temps_total.min = tmp->premier.temps_1er_manche.min + tmp->premier.temps_2e_manche.min;
			tmp->premier.temps_total.sec = tmp->premier.temps_1er_manche.sec + tmp->premier.temps_2e_manche.sec;
			tmp->premier.temps_total.centSec = tmp->premier.temps_1er_manche.centSec + tmp->premier.temps_2e_manche.centSec;

			tmp->suivant = copieListe;
			copieListe = tmp;
		}
		else
		{
			/* Si le joeur a abandonné la deuxieme manche on le met dans la liste de ceux qui ont abandonné*/
			q = (Liste*)malloc(sizeof(Liste));
			/* on ramène le temps du joeurs a 0*/
			p->premier.temps_total.min = 0;
			p->premier.temps_total.sec = 0;
			p->premier.temps_total.centSec = 0;
			/* on memorise ses infos dans la variable intermediarie q*/
			strcpy(q->premier.nom, p->premier.nom);
			q->premier.numero_dossard = p->premier.numero_dossard;
			q->premier.temps_total.min = p->premier.temps_total.min;
			q->premier.temps_total.sec = p->premier.temps_total.sec;
			q->premier.temps_total.centSec = p->premier.temps_total.centSec;
			/* on ajoute ensuite q dans la liste abandonnes*/
			q->suivant = abandonnes;
			abandonnes = q;
		}
		p = p->suivant;

	}
	printf("\n");
	printf("**********AFFICHAGE 2EME MANCHE************\n");
	printf("\n");
	players = copieListe; // on remet les données de ceux qui ont réussi dans la liste des players
	p = players;
	printf("Liste des coureurs\n");
	printf("\n");
	while (p != NULL)
	{
		printf("%s\tnumero\t%d\ta fait\t%dmin %ds %dcs\n", p->premier.nom, p->premier.numero_dossard, p->premier.temps_total.min, p->premier.temps_total.sec, p->premier.temps_total.centSec);
		p = p->suivant;
	}
	//Affichage de la liste des abandons
	printf("\n\n");
	printf("la liste de ceux qui ont abandonnes \n");
	printf("\n");
	a = abandonnes;

	while (a != NULL)
	{
		printf("%s\tnumero\t%d\ta fait\t%dmin %ds %dcs\n", a->premier.nom, a->premier.numero_dossard, a->premier.temps_total.min, a->premier.temps_total.sec, a->premier.temps_total.centSec);
		a = a->suivant;
	}
	printf("\n\n");
	// Trie de la liste des players
	/* on va parcourir la liste des players et on fait un trie croissant du temps par recherche du minimum */

	p = players;

	if (p != NULL)  // on verie que la liste n'est pas vide
	{
		/* la variable mini contient le temps minimum*/
		/* mini nous permettra de faire le trie par recherche du minimum*/

		mini = (Liste *)malloc(sizeof(Liste));
		while (p != NULL)
		{
			/* a chaque tour de la boucle, on suppose que le premier maillon c'est le minimum*/

			strcpy(mini->premier.nom, p->premier.nom);
			mini->premier.numero_dossard = p->premier.numero_dossard;
			mini->premier.temps_total.min = p->premier.temps_total.min;
			mini->premier.temps_total.sec = p->premier.temps_total.sec;
			mini->premier.temps_total.centSec = p->premier.temps_total.centSec;
			w = NULL; // cette variable va nous confirmer si on est rentré dans la condition
			tmp = p; // tmp nous permet de faire un second parcourt de la liste
			while (tmp != NULL)
			{

				if ((mini->premier.temps_total.min * 6000 + mini->premier.temps_total.sec * 100 + mini->premier.temps_total.centSec)>(tmp->premier.temps_total.min * 6000 + tmp->premier.temps_total.sec * 100 + tmp->premier.temps_total.centSec))
				{
					/* Si on a un temps inferieur au temps de début, on copie sa valeur dans mini*/
					strcpy(mini->premier.nom, tmp->premier.nom);
					mini->premier.numero_dossard = tmp->premier.numero_dossard;
					mini->premier.temps_total.min = tmp->premier.temps_total.min;
					mini->premier.temps_total.sec = tmp->premier.temps_total.sec;
					mini->premier.temps_total.centSec = tmp->premier.temps_total.centSec;
					w = tmp; // on memorise l'adresse du temps qui inferieur au temps de debut
				}
				tmp = tmp->suivant;

			}
			/* A la sortie de la boucle deux cas peuvent se produire, soit on a trouvé un minimum ou pas*/
			/* si on a trouvé un autre minimum, w contient donc une adresse, sinon w sera vide */

			if (w != NULL)
			{
				/*si w n'est pas vide, on echange son contenu au continu du premier maillon de la liste*/

				/* on memorise le contenu du premier maillon dans une variable intermediaire q*/
				q = (Liste *)malloc(sizeof(Liste));
				strcpy(q->premier.nom, p->premier.nom);
				q->premier.numero_dossard = p->premier.numero_dossard;
				q->premier.temps_total.min = p->premier.temps_total.min;
				q->premier.temps_total.sec = p->premier.temps_total.sec;
				q->premier.temps_total.centSec = p->premier.temps_total.centSec;

				/* on met le contenu le minumum au debut de la liste*/
				strcpy(p->premier.nom, mini->premier.nom);
				p->premier.numero_dossard = mini->premier.numero_dossard;
				p->premier.temps_total.min = mini->premier.temps_total.min;
				p->premier.temps_total.sec = mini->premier.temps_total.sec;
				p->premier.temps_total.centSec = mini->premier.temps_total.centSec;

				/*on deplace le contenu p dans w qui contenait le minimum*/
				strcpy(w->premier.nom, q->premier.nom);
				w->premier.numero_dossard = q->premier.numero_dossard;
				w->premier.temps_total.min = q->premier.temps_total.min;
				w->premier.temps_total.sec = q->premier.temps_total.sec;
				w->premier.temps_total.centSec = q->premier.temps_total.centSec;

			}
			p = p->suivant;


		}
	}

	/* Tri de la liste des abandonnés par ordre alphabetique */
	/*  on fait la même methode que pour le trie des temps  */
	a = abandonnes;
	if (a != NULL)
	{
		mini = (Liste *)malloc(sizeof(Liste));
		while (a != NULL)
		{
			strcpy(mini->premier.nom, a->premier.nom);
			tmp = a;
			w = NULL;

			while (tmp != NULL)
			{
				/* strcmp sert a comparé deux chaines, elle renvoit 0 si les chaines sont identique, un nombre positif si la premiere chaine*/
				/* est superieure au deuxième, un nombre negatif sino*/

				if (strcmp(mini->premier.nom, tmp->premier.nom)>0)
				{
					//si strcmp renvoit un positif, on change donc le minimum
					// et on memorise l'adresse du maillon

					strcpy(mini->premier.nom, tmp->premier.nom);
					w = tmp;
				}
				tmp = tmp->suivant;

			}
			if (w != NULL)
			{
				q = (Liste *)malloc(sizeof(Liste));
				strcpy(q->premier.nom, a->premier.nom);
				strcpy(a->premier.nom, mini->premier.nom);
				strcpy(w->premier.nom, q->premier.nom);
			}
			a = a->suivant;
		}
	}
	printf("**********AFICHAGE LISTE TRIE ************\n");
	printf("\n");
	p = players;
	printf("Liste des coureurs\n");
	printf("\n");
	while (p != NULL)
	{
		printf("%s\tnumero\t%d\ta fait\t%dmin %ds %dcs\n", p->premier.nom, p->premier.numero_dossard, p->premier.temps_total.min, p->premier.temps_total.sec, p->premier.temps_total.centSec);
		p = p->suivant;
	}
	printf("\n");
	a = abandonnes;
	printf("Liste des abandones\n");
	printf("\n");
	while (a != NULL)
	{
		printf("%s\tnumero\t%d\n", a->premier.nom, a->premier.numero_dossard);
		a = a->suivant;
	}



	// Ecart du temps entre le premier et les autres joueur
	// diii
	p = players;

	if (p != NULL)
	{
		ecartTemp = p;// on memorise le temps du premier joueur pour faire la difference de temps
		tmp = p->suivant;
		while (tmp != NULL)
		{
			/* on fait la difference de temps entre le premier et les autres joueurs en convertissant le temps en centieme de seconde*/
			convertTemps = ((tmp->premier.temps_total.min * 60 + tmp->premier.temps_total.sec) * 100 + tmp->premier.temps_total.centSec - ((ecartTemp->premier.temps_total.min * 60 + ecartTemp->premier.temps_total.sec) * 100 + ecartTemp->premier.temps_total.centSec));
			p = tmp;
			p->premier.temps_total.centSec = convertTemps % 100; // on ecrit le temps en centieme de seconde
			p->premier.temps_total.sec = (convertTemps / 100) % 60; // puis on vient en seconde
			p->premier.temps_total.min = (convertTemps / 6000) % 60; // En fin en min
			tmp = tmp->suivant;
		}


	}
	printf("\n\n");

	printf("**********AFFICHAGE ECART DE TEMPS************\n");
	printf("\n");
	p = players;
	printf("Liste des coureurs\n");
	printf("\n");
	
	maillon = 1;
	while (p != NULL)
	{
		if (maillon == 1)
		{
			printf("%der\t%s\tnumero %d\t%dmin %ds %dcs\n", maillon, p->premier.nom, p->premier.numero_dossard, p->premier.temps_total.min, p->premier.temps_total.sec, p->premier.temps_total.centSec);
		}
		else
		{
			printf("%deme\t%s\tnumero %d\t+%dmin %ds %dcs\n", maillon, p->premier.nom, p->premier.numero_dossard, p->premier.temps_total.min, p->premier.temps_total.sec, p->premier.temps_total.centSec);
		}
		maillon++;
		p = p->suivant;
	}

	// calcul du temps moyen qu'a fait le joueur
	p = players;
	while (p != NULL)
	{
		/*on refait le cumul du temps car on a déja utilisé temps_total pour le calcul de l'ecart de temps*/
		p->premier.temps_total.min = p->premier.temps_1er_manche.min + p->premier.temps_2e_manche.min;
		p->premier.temps_total.sec = p->premier.temps_1er_manche.min + p->premier.temps_2e_manche.sec;
		p->premier.temps_total.centSec = p->premier.temps_1er_manche.min + p->premier.temps_2e_manche.centSec;
		p = p->suivant;

	}

	/* on fait l'ensuite l'affichage mais en convertissant le temps en seconde*/
	printf("\n\n");
	printf("**********AFFICHAGE TEMPS MOYEN************\n");
	printf("\n");
	p = players;
	while (p != NULL)
	{
		printf("%s\tnumero\t%d\ta fait un temps moyen de\t%fmin %fs %fcs\n", p->premier.nom, p->premier.numero_dossard, p->premier.temps_total.min/2.0, p->premier.temps_total.sec/2.0, p->premier.temps_total.centSec/2.0);
			
		p = p->suivant;
	}
	printf("\n");
	// liberation 

	free(abandonnes);
	free(players);
	return 0;

}
