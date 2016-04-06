#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "distribution.h"
#include "RR.h"
#include "maxSNR.h"
#include "initialisation.h"


int main(){
	FILE* fichier = NULL;
	long actualTime = 1;
	int debitTotal = 0;
	int nb_tours = 100;
	int i, indice = 0, temp;
	int nb_users1, nb_users2, nb_users3, nb_users4;
	int nb_sub1, nb_sub2, nb_sub3, nb_sub4;
	/*int choixAlgo = 0;*/
	int nb_user = 1;
	int nbBitsgenere = 20;
	int userSwitch[4];
	int subSwitch[5];


	/*	Users *Antenne1 = malloc(sizeof(Users)*nb_users);
	Users *Antenne2 = malloc(sizeof(Users)*nb_users);
	Users *Antenne3 = malloc(sizeof(Users)*nb_users);
	Users *Antenne4 = malloc(sizeof(Users)*nb_users);*/
	Antenne Antenne1;
	Antenne Antenne2;
	Antenne Antenne3;
	Antenne Antenne4;

	/*nombre d'utilisateurs possible*/
	userSwitch[0] = 4;
	userSwitch[1] = 16;
 	userSwitch[2] = 20;
	userSwitch[3] = 8;
	/*valeur de fréquences possible*/
	subSwitch[0] = 11;
	subSwitch[1] = 43;
 	subSwitch[2] = 53;
	subSwitch[3] = 21;
	subSwitch[4] = 32;

	nb_users1 = 6;
	nb_users2 = 6;
	nb_users3 = 6;
	nb_users4 = 6 ;
	nb_sub1 = 32;
	nb_sub2 = 32;
	nb_sub3 = 32;
	nb_sub4 = 32;


	/*---INITIALISATIONS---*/
	printf("\nSIMULATION NTR\n\n");
	/*printf("Nombre d'utilisateur pour la simulation: ");
	scanf("%d", &nb_user);
	printf("Nombre de tours pour la simulation: ");
	scanf("%d", &nb_tours);
	printf("Nombre de bits à générer (>100) :");
	scanf("%d", &nbBitsgenere);*/

	nb_user=1;
	nb_tours=1;
	nbBitsgenere=50;

	nb_users1 = userSwitch[0];
	nb_users2 = userSwitch[1];
	nb_users3 = userSwitch[2];
	nb_users4 = userSwitch[3];
	nb_sub1 = subSwitch[0];
	nb_sub2 = subSwitch[1];
	nb_sub3 = subSwitch[2];
	nb_sub4 = subSwitch[3];


	/*initAntenne(&Antenne1, nb_users1);
	initAntenne(&Antenne2, nb_users2);
	initAntenne(&Antenne3, nb_users3);
	initAntenne(&Antenne4, nb_users4);*/

	fichier = fopen("test.csv", "w+");
	 
	    if (fichier != NULL)
	    {
	 
	       fprintf(fichier,"%d\n", 0);
	 
		fclose(fichier);
	    }

	/*while(nb_user <= 40){*/


		initAntenne(&Antenne1, nb_users1);
		initAntenne(&Antenne2, nb_users2);
		initAntenne(&Antenne3, nb_users3);
		initAntenne(&Antenne4, nb_users4);
	/*---BOUCLE PRINCIPALE---*/
	for(i = 0; i < nb_tours; i++){

		/*Application de l'algorithme et ôtage des bits envoyés avec maxSNR*/
		
		/*Initialisation des paquets utilisateurs et debits utilisateurs*/
		
		/*Application de l'algorithme et ôtage des bits envoyés avec RR
		debitTotal += RR(&monAntenne);*/

		/*Application de l'algorithme et ôtage des bits envoyés avec maxSNR*/
		produceBit(&Antenne1, nbBitsgenere, nb_users1);
		initMatriceDebits(&Antenne1, nb_users1);
		temp = RR(&Antenne1, nb_users1, nb_sub1);
		printf("	Antenne 1 %d bits/ms\n", temp);
		debitTotal += temp;
		produceBit(&Antenne2, nbBitsgenere, nb_users2);
		initMatriceDebits(&Antenne2, nb_users2);
		temp = RR(&Antenne2, nb_users2, nb_sub2);
		printf("	Antenne 2 %d bits/ms\n", temp);
		debitTotal += temp;
		produceBit(&Antenne3, nbBitsgenere, nb_users3);
		initMatriceDebits(&Antenne3, nb_users3);
		temp = RR(&Antenne3, nb_users3, nb_sub3);
		printf("	Antenne 3 %d bits/ms\n", temp);
		debitTotal += temp;
		produceBit(&Antenne4, nbBitsgenere, nb_users4);
		initMatriceDebits(&Antenne4, nb_users4);
		temp = RR(&Antenne4, nb_users4, nb_sub4);
		printf("	Antenne 4 %d bits/ms\n", temp);
		debitTotal += temp;

		/*printf("\nStatistiques : \n");*/
		printf("	Débit total de la simulation: %d bits/ms\n", debitTotal);
		/*printf("Nombre d'utilisateur %d", nb_users1);
		printf("Nombre d'utilisateur %d", nb_users2);
		printf("Nombre d'utilisateur %d", nb_users3);
		printf("Nombre d'utilisateur %d", nb_users4);*/

		fichier = fopen("test.csv", "a");
	    if (fichier != NULL)
	    {
	 
	       /*fprintf(fichier,"%d\n", debitTotal/actualTime);*/
	 
		fclose(fichier);
	    }
		/*ENVOI DE LA TRAME */

		/*Changement du nombre d'utilisateur*/
		/*
		nb_users1 = userSwitch[(indice)%4];
		nb_users2 = userSwitch[(indice+1)%4];
		nb_users3 = userSwitch[(indice+2)%4];
		nb_users4 = userSwitch[(indice+3)%4];*/

		/*Allocation du nombre de frequences*/
		/*
		nb_sub1 = subSwitch[(indice)%4];
		nb_sub2 = subSwitch[(indice+1)%4];
		nb_sub3 = subSwitch[(indice+2)%4];
		nb_sub4 = subSwitch[(indice+3)%4];*/
		debitTotal=0;
		actualTime += 2;

		/*Mise à jours des délais*/

	}

	/*Incrémentation du temps*/
		
		indice = (indice + 1) % 4;
		nb_user=nb_user+2;
		/*debitTotal = 0;*/

		nb_users1 = nb_user;
		nb_users2 = nb_user;
		nb_users3 = nb_user;
		nb_users4 = nb_user;
	
	printf("\nStatistiques : \n\n");
	printf("Débit total de la simulation: %d bits/ms\n", (int)(debitTotal/actualTime));


	/*END WHILE*/
	/*}*/

	return 0;
}