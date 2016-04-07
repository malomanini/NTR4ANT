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
	double debitTotal = 0;
	int debitTotalSimu = 0;
	int nb_tours = 100;
	int i, indice = 0, temp;
	int nb_users1, nb_users2, nb_users3, nb_users4;
	int nb_sub1, nb_sub2, nb_sub3, nb_sub4;
	int nbPaquetsTotal = 0;
	int nbPaquetsNonEnvoyes = 0;
	/*int choixAlgo = 0;*/
	int nb_user = 1;
	int nb_user_temp = 1;
	int nbBitsgenere = 20;
	double subSwitch[4];
	Packet *tmpPacket = NULL;
	double sommeDelais = 0;


	/*	Users *Antenne1 = malloc(sizeof(Users)*nb_users);
	Users *Antenne2 = malloc(sizeof(Users)*nb_users);
	Users *Antenne3 = malloc(sizeof(Users)*nb_users);
	Users *Antenne4 = malloc(sizeof(Users)*nb_users);*/
	Antenne Antenne1;
	Antenne Antenne2;
	Antenne Antenne3;
	Antenne Antenne4;

	nb_sub1 = 32;
	nb_sub2 = 32;
	nb_sub3 = 32;
	nb_sub4 = 32;


	/*---INITIALISATIONS---*/
	printf("\nSIMULATION NTR\n\n");
	/*printf("Nombre d'utilisateur pour la simulation: ");
	scanf("%d", &nb_user);
	printf("Nombre de tours pour la simulation: ");
	scanf("%d", &nb_tours);*/

	nb_tours=100;
	nbBitsgenere=150;


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

	while(nb_user <= 150){


		
	/*---BOUCLE PRINCIPALE---*/
	for(i = 0; i < nb_tours; i++){



		/*ALLOUE DYNAMIQUEMENT LES SUB*/
		/*nb_users1 = (rand() % (int)((nb_user / 2)-5)) + 5;
		nb_users2 = (rand() % (int)((nb_user / 2)-5)) + 5;
		nb_users3 = (rand() % (int)((nb_user / 2)-5)) + 5;

		nb_users4 = nb_user-nb_users1-nb_users2-nb_users3;*/

		nb_users1 = nb_user/3;
		nb_users2 = nb_user/4;
		nb_users3 = nb_user/4;
		nb_users4 = nb_user-nb_users1-nb_users2-nb_users3;


			nb_user_temp = nb_users1 + nb_users2 + nb_users3 + nb_users4;
			/*printf("\nnombre utilisateur : %.3f\n\n", nb_user_temp);*/

			subSwitch[0] = nb_users1/nb_user_temp*NB_SUBCARRIERS;
			subSwitch[1] = nb_users2/nb_user_temp*NB_SUBCARRIERS;
			subSwitch[2] = nb_users3/nb_user_temp*NB_SUBCARRIERS;
			subSwitch[3] = nb_users4/nb_user_temp*NB_SUBCARRIERS;
			/*
			printf("\nnombre sub 1 a allouer : %.0f\n\n", subSwitch[0]);
			printf("\nnombre sub 2 a allouer : %.0f\n\n", subSwitch[1]);
			printf("\nnombre sub 3 a allouer : %.0f\n\n", subSwitch[2]);
			printf("\nnombre sub 4 a allouer : %.0f\n\n", subSwitch[3]);*/

			nb_sub1 = subSwitch[0];
			nb_sub2 = subSwitch[1];
			nb_sub3 = subSwitch[2];
			nb_sub4 = subSwitch[3];

		/*FIN D'ALLOC DES SUB*/

		initAntenne(&Antenne1, nb_users1);
		initAntenne(&Antenne2, nb_users2);
		initAntenne(&Antenne3, nb_users3);
		initAntenne(&Antenne4, nb_users4);


		
		/*Application de l'algorithme et ôtage des bits envoyés avec RR
		debitTotal += RR(&monAntenne);*/

		/*Application de l'algorithme et ôtage des bits envoyés avec maxSNR*/
		produceBit(&Antenne1, nbBitsgenere, nb_users1);
		initMatriceDebits(&Antenne1, nb_users1);
		temp = maxSNR(&Antenne1, nb_users1, nb_sub1);
		debitTotal += temp;
		produceBit(&Antenne2, nbBitsgenere, nb_users2);
		initMatriceDebits(&Antenne2, nb_users2);
		temp = maxSNR(&Antenne2, nb_users2, nb_sub2);
		debitTotal += temp;
		produceBit(&Antenne3, nbBitsgenere, nb_users3);
		initMatriceDebits(&Antenne3, nb_users3);
		temp = maxSNR(&Antenne3, nb_users3, nb_sub3);
		debitTotal += temp;
		produceBit(&Antenne4, nbBitsgenere, nb_users4);
		initMatriceDebits(&Antenne4, nb_users4);
		temp = maxSNR(&Antenne4, nb_users4, nb_sub4);
		debitTotal += temp;

		/*printf("\nStatistiques : \n");*/
		debitTotalSimu += debitTotal;
		/*printf("Nombre d'utilisateur %d", nb_users1);
		printf("Nombre d'utilisateur %d", nb_users2);
		printf("Nombre d'utilisateur %d", nb_users3);
		printf("Nombre d'utilisateur %d", nb_users4);*/

		for(i = 0; i< nb_users1; i++){

			/* Récupération des délais et nb de paquets restants dans les paquets non envoyes */
			if(Antenne1.users[i]->lePaquet != NULL){

				tmpPacket = Antenne1.users[i]->lePaquet;
				while(tmpPacket->nextPacket != NULL){
					/* Stats globales */
					sommeDelais += (Antenne1.actualTime - tmpPacket->dateCreation);
					nbPaquetsNonEnvoyes++;
					nbPaquetsTotal++;
					tmpPacket = tmpPacket->nextPacket;
				}

			}

			/* Récupération des delais et paquets enregistrés */
			sommeDelais += Antenne1.users[i]->sommeDelais;
			nbPaquetsTotal += Antenne1.users[i]->sommePaquets;

		}
		for(i = 0; i< nb_users2; i++){

			/* Récupération des délais et nb de paquets restants dans les paquets non envoyes */
			if(Antenne2.users[i]->lePaquet != NULL){

				tmpPacket = Antenne2.users[i]->lePaquet;
				while(tmpPacket->nextPacket != NULL){
					/* Stats globales */
					sommeDelais += (Antenne2.actualTime - tmpPacket->dateCreation);
					nbPaquetsNonEnvoyes++;
					nbPaquetsTotal++;
					tmpPacket = tmpPacket->nextPacket;
				}

			}

			/* Récupération des delais et paquets enregistrés */
			sommeDelais += Antenne2.users[i]->sommeDelais;
			nbPaquetsTotal += Antenne2.users[i]->sommePaquets;

		}
		for(i = 0; i< nb_users3; i++){

			/* Récupération des délais et nb de paquets restants dans les paquets non envoyes */
			if(Antenne3.users[i]->lePaquet != NULL){

				tmpPacket = Antenne3.users[i]->lePaquet;
				while(tmpPacket->nextPacket != NULL){
					/* Stats globales */
					sommeDelais += (Antenne3.actualTime - tmpPacket->dateCreation);
					nbPaquetsNonEnvoyes++;
					nbPaquetsTotal++;
					tmpPacket = tmpPacket->nextPacket;
				}

			}

			/* Récupération des delais et paquets enregistrés */
			sommeDelais += Antenne3.users[i]->sommeDelais;
			nbPaquetsTotal += Antenne3.users[i]->sommePaquets;

		}
		for(i = 0; i< nb_users4; i++){

			/* Récupération des délais et nb de paquets restants dans les paquets non envoyes */
			if(Antenne4.users[i]->lePaquet != NULL){

				tmpPacket = Antenne4.users[i]->lePaquet;
				while(tmpPacket->nextPacket != NULL){
					/* Stats globales */
					sommeDelais += (Antenne4.actualTime - tmpPacket->dateCreation);
					nbPaquetsNonEnvoyes++;
					nbPaquetsTotal++;
					tmpPacket = tmpPacket->nextPacket;
				}

			}

			/* Récupération des delais et paquets enregistrés */
			sommeDelais += Antenne4.users[i]->sommeDelais;
			nbPaquetsTotal += Antenne4.users[i]->sommePaquets;

		}


		printf("--------------------------------------------------------------\n");
		printf("Statistiques pour %d utilisateurs: \n", nb_user);
		printf("	Débit total : %.0f bits\n", debitTotal);
		printf("	Somme des delais: : %.3f ms\n", sommeDelais);
		printf("	Débit total de la simulation: %.3f bits/ms\n", (double)(debitTotal/Antenne1.actualTime));
		printf("	Delai moyen : %.3f ms\n", (double)(sommeDelais/nbPaquetsTotal));
		printf("	nbPaquetsNonEnvoyes : %d || nbPaquetsTotal : %d \n", nbPaquetsNonEnvoyes, nbPaquetsTotal);
		

		fichier = fopen("test.csv", "a");
	    if (fichier != NULL)
	    {
	 
	    /*   fprintf(fichier,"%d;%.0f;%.0f\n", nb_user, debitTotal/Antenne1.actualTime, sommeDelais/nbPaquetsTotal);
	 */
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
		nb_user=nb_user+4;
		/*debitTotal = 0;*/

		nb_users1 = nb_user;
		nb_users2 = nb_user;
		nb_users3 = nb_user;
		nb_users4 = nb_user;
	
	printf("\nStatistiques : \n\n");
	printf("Débit total de la simulation: %d bits/ms\n", (int)(debitTotalSimu/actualTime*2));
	debitTotalSimu=0;
	actualTime=0;


	
	}

	return 0;
}