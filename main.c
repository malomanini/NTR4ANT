#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "distribution.h"
#include "RR.h"
#include "maxSNR.h"
#include "initialisation.h"


int main(){

	long actualTime = 0;
	int debitTotal = 0;
	int nb_tours = 1000;
	int i, indice = 0, temp;
	int nb_users1, nb_users2, nb_users3, nb_users4;
	int nb_sub1, nb_sub2, nb_sub3, nb_sub4;
	int userSwitch[4];
	int subSwitch[4];


	/*	Users *Antenne1 = malloc(sizeof(Users)*nb_users);
	Users *Antenne2 = malloc(sizeof(Users)*nb_users);
	Users *Antenne3 = malloc(sizeof(Users)*nb_users);
	Users *Antenne4 = malloc(sizeof(Users)*nb_users);*/
	Antenne Antenne1;
	Antenne Antenne2;
	Antenne Antenne3;
	Antenne Antenne4;

	//nombre d'utilisateurs possible
	userSwitch[0] = 1;
	userSwitch[1] = 4;
 	userSwitch[2] = 5;
	userSwitch[3] = 2;
	//valeur de fréquences possible
	subSwitch[0] = 11;
	subSwitch[1] = 43;
 	subSwitch[2] = 53;
	subSwitch[3] = 21;

	nb_users1 = 6;
	nb_users2 = 6;
	nb_users3 = 6;
	nb_users4 = 6 ;
	nb_sub1 = 32;
	nb_sub2 = 32;
	nb_sub3 = 32;
	nb_sub4 = 32;


	/*---INITIALISATIONS---*/
	printf("\nSIMULATION NTR\n");
	/*printf("Nombre de tours pour la simulation: ");
	scanf("%d", &nb_tours);*/


	initAntenne(&Antenne1, nb_users1);
	initAntenne(&Antenne2, nb_users2);
	initAntenne(&Antenne3, nb_users3);
	initAntenne(&Antenne4, nb_users4);

	/*---BOUCLE PRINCIPALE---*/
	for(i = 0; i < nb_tours; i++){
		/*Initialisation des paquets utilisateurs et debits utilisateurs*/
		
		/*Application de l'algorithme et ôtage des bits envoyés avec RR
		debitTotal += RR(&monAntenne);*/

		/*Application de l'algorithme et ôtage des bits envoyés avec maxSNR*/

		produceBit(&Antenne1, actualTime, nb_users1);
		initMatriceDebits(&Antenne1, nb_users1);
		temp = RR(&Antenne1, nb_users1, nb_sub1);
		debitTotal += temp;
		produceBit(&Antenne2, actualTime, nb_users2);
		initMatriceDebits(&Antenne2, nb_users2);
		temp = RR(&Antenne2, nb_users2, nb_sub2);
		debitTotal += temp;
		produceBit(&Antenne3, actualTime, nb_users3);
		initMatriceDebits(&Antenne3, nb_users3);
		temp = RR(&Antenne3, nb_users3, nb_sub3);
		debitTotal += temp;
		produceBit(&Antenne4, actualTime, nb_users4);
		initMatriceDebits(&Antenne4, nb_users4);
		temp = RR(&Antenne4, nb_users4, nb_sub4);
		debitTotal += temp;


		/*ENVOI DE LA TRAME */

		/*Changement du nombre d'utilisateur*/
		nb_users1 = userSwitch[(indice)%4];
		nb_users2 = userSwitch[(indice+1)%4];
		nb_users3 = userSwitch[(indice+2)%4];
		nb_users4 = userSwitch[(indice+3)%4];

		/*Allocation du nombre de frequences*/
		nb_sub1 = subSwitch[(indice)%4];
		nb_sub2 = subSwitch[(indice+1)%4];
		nb_sub3 = subSwitch[(indice+2)%4];
		nb_sub4 = subSwitch[(indice+3)%4];

		/*Mise à jours des délais*/


		/*Incrémentation du temps*/
		actualTime += 2;
		indice = (indice + 1) % 4;

	}
	
	printf("\nStatistiques : \n\n");
	printf("Débit total de la simulation: %d bits/ms\n", (int)(debitTotal/actualTime));

	return 0;
}