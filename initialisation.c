#include <stdio.h>
#include <stdlib.h>

#include "initialisation.h"
#include "struct.h"

int randDist = 0;

Packet* createPacket(){
	
	Packet *packet = malloc(sizeof(Packet));
	packet->dateCreation=0;
	packet->bitsRestants=0;
	packet->nextPacket = NULL;
	return packet;
}

User* initUser(){
	int i = 0 ;
	User *user = malloc(sizeof(User));

	user->distance=5;
	user->bufferVide=0;
	user->SNRmoyen=0;
	user->sommeDelai=0;
	for(i = 0; i<NB_SUBCARRIERS; i++)
	{
		user->SNRActuels[i]=0;
	}

	user->lePaquet = createPacket();
	randDist++;
	return user;
}

void initAntenne(Antenne *antenne, int nb_users){
	int i = 0;
	for(i = 0; i < nb_users; i++)
	{	
		antenne->users[i]=initUser();
	}
}



void initMatriceDebits(Antenne *antenne, int nb_users){
	int i = 0;
	int j = 0;

	for(i = 0; i<nb_users; i++)
	{
		for(j = 0; j<NB_SUBCARRIERS; j++){
			antenne->users[i]->SNRActuels[j] = getSNR(antenne->users[i]->distance);
		}
	}
}


//!!! Amélioration possible en ajoutant un LastPacket 
void produceBit(Antenne *antenne, int actualTime, int nb_users){
	int i = 0;
	int bitsGeneres ;
	int debordement = 0;
	int resteARemplir = 0;
	int continuer = 1;


	// Création d'un nouveau packet 
	Packet *packet;
	
	for(i = 0; i < (nb_users); i++){
		continuer = 1;
		packet=NULL;
		bitsGeneres=getNbBit();
		packet = antenne->users[i]->lePaquet;
		//recupere le dernier paquet
		while(packet->nextPacket != NULL)
		{
            packet = packet->nextPacket;
        }
        //Remplissage des paquets 
        while(continuer){
        	//Si il reste de quoi remplir le paquet
        	if(bitsGeneres > (100 - packet->bitsRestants)){
        		bitsGeneres -= 100 - packet->bitsRestants;
        		packet->bitsRestants = 100;
        		packet->nextPacket = createPacket();
        		packet = packet->nextPacket;
        	}
        	else{
        		packet->bitsRestants += bitsGeneres;
        		continuer = 0;
        	}   		     	
        }
		
	}


}


int consumeBit(Antenne *antenne, int currentUser, int subCarrier){
	int debordement;
	User *theUser = antenne->users[currentUser];
	Packet *tmpPacket;
/*
	printf("\n bits restants : %d\n", theUser->lePaquet->bitsRestants);
	printf(" SNR actuel: %d\n", theUser->SNRActuels[subCarrier]);*/
	//Si on consomme plus de bits que le paquet en contient
	if(theUser->lePaquet->bitsRestants < theUser->SNRActuels[subCarrier]){
		if(theUser->lePaquet->nextPacket != NULL){
	/*		printf(" Suppression du paquet courant \n Le prochain paquet contient: %d", theUser->lePaquet->nextPacket->bitsRestants);
			printf(" \n on lui ote %d\n", theUser->SNRActuels[subCarrier] - theUser->lePaquet->bitsRestants);
	*/		
			//On soustrait au prochain paquet le SNR moins le contenu du paquet actuel 
			theUser->lePaquet->nextPacket->bitsRestants -= theUser->SNRActuels[subCarrier] - theUser->lePaquet->bitsRestants;
			//Puis on supprime le paquet 
			tmpPacket = theUser->lePaquet;
			theUser->lePaquet = theUser->lePaquet->nextPacket;
		}
		else{
			theUser->lePaquet->bitsRestants = 0;
			theUser->bufferVide = 1;
		}
		// TODO TODO TODO
		//free(tmpPacket);
	}
	//Si il y a assez de bits dans ce paquet
	else{
		theUser->lePaquet->bitsRestants -= theUser->SNRActuels[subCarrier];
	}

	//printf(" bits restants Apres: %d\n", theUser->lePaquet->bitsRestants);
	// On retourne le nombre de bits côtés 
	return antenne->users[currentUser]->SNRActuels[subCarrier];
}



int MaxUser (Antenne *antenne, int subCarrier, int nb_users){
	int i = 0;
	int res = 0;


	for (i = 0; i < nb_users; i++){
		if((antenne->users[i]->SNRActuels[subCarrier] > antenne->users[res]->SNRActuels[subCarrier]) && (antenne->users[i]->bufferVide == 0)){
			// si l'User a un meilleur debit, et que son buffer n'est pas vide: il devient le MaxUser 
			res = i;
			}
	}

	return res;
}

int empty(Antenne *antenne, int currentUser, int nb_users){
	if(currentUser < nb_users){
		return antenne->users[currentUser]->bufferVide;
	}
	else{
		return 1;
	}
}