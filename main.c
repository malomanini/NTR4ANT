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
	int i, temp;
	int nb_users1, nb_users2, nb_users3, nb_users4;
	int nb_sub1, nb_sub2, nb_sub3, nb_sub4;

	/*	Users *Antenne1 = malloc(sizeof(Users)*nb_users);
	Users *Antenne2 = malloc(sizeof(Users)*nb_users);
	Users *Antenne3 = malloc(sizeof(Users)*nb_users);
	Users *Antenne4 = malloc(sizeof(Users)*nb_users);*/
	Antenne Antenne1;
	Antenne Antenne2;
	Antenne Antenne3;
	Antenne Antenne4;


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
		temp = maxSNR(&Antenne1, nb_users1, nb_sub1);
		debitTotal += temp;
		produceBit(&Antenne2, actualTime, nb_users2);
		initMatriceDebits(&Antenne2, nb_users2);
		temp = maxSNR(&Antenne2, nb_users2, nb_sub2);
		debitTotal += temp;
		produceBit(&Antenne3, actualTime, nb_users3);
		initMatriceDebits(&Antenne3, nb_users3);
		temp = maxSNR(&Antenne3, nb_users3, nb_sub3);
		debitTotal += temp;
		produceBit(&Antenne4, actualTime, nb_users4);
		initMatriceDebits(&Antenne4, nb_users4);
		temp = maxSNR(&Antenne4, nb_users4, nb_sub4);
		debitTotal += temp;


		/*ENVOI DE LA TRAME */

		/*Mise à jours des délais*/


		/*Incrémentation du temps*/
		actualTime += 2;

	}
	
	printf("\nStatistiques : \n\n");
	printf("Débit total de la simulation: %d bits/ms\n", (int)(debitTotal/actualTime));

	return 0;
}