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
	int nb_tours = 10;
	int i, temp, j;
	int nbAntenne = 4;

	Antenne *lesAntennes = malloc(sizeof(Antenne)*nbAntenne);


	/*---INITIALISATIONS---*/
	printf("\nSIMULATION NTR\n");
	/*printf("Nombre de tours pour la simulation: ");
	scanf("%d", &nb_tours);*/

	/*---BOUCLE PRINCIPALE---*/
	for(i = 0; i < nb_tours; i++){
		/*Initialisation des paquets utilisateurs et debits utilisateurs*/
		for(j = 0; j<nbAntenne; j++){
			initAntenne(&lesAntennes[j]);

		}

		/*Application de l'algorithme et ôtage des bits envoyés avec RR
		debitTotal += RR(&monAntenne);*/

		/*Application de l'algorithme et ôtage des bits envoyés avec maxSNR*/

		for(j = 0; j<nbAntenne; j++){
			produceBit(&lesAntennes[j], actualTime);
			initMatriceDebits(&lesAntennes[j]);
			temp = RR(&lesAntennes[j]);
			printf("temp : %d\n", temp);
			debitTotal += temp;
		}


		/*ENVOI DE LA TRAME */

		/*Mise à jours des délais*/


		/*Incrémentation du temps*/
		actualTime += 2;

	}
	
	printf("\nStatistiques : \n\n");
	printf("Débit total de la simulation: %d bits/ms\n", (int)(debitTotal/actualTime));




	return 0;
}