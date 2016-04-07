#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "maxSNR.h"
#include "distribution.h"
#include "initialisation.h"

int maxSNR(Antenne *antenne, int nb_users, int nb_sub) {	
	int MaxU = 0;
	int i, g, j, debitTotalTrame = 0;
	int count = 0;

	for(g = 0; g < 5 ; g++){// parcours les timeslots, //tant que User.BufferVide > 0 ou que g<5, on transmet au debit actuel a cet user
		for(j = 0; j < nb_sub ; j++){ //parcourt les subcariers

			for (i = 0; i < nb_users ; i++){

				if((antenne->users[i]->SNRActuels[j] >= antenne->users[MaxU]->SNRActuels[j]) && (antenne->users[i]->bufferVide == 0)){
					// si l'User a un meilleur debit, et que son buffer n'est pas vide: il devient le MaxUser 
					MaxU = i;
					
				}
			}
			/*printf("maxU = %d   ", MaxU);*/
			debitTotalTrame += consumeBit(antenne, MaxU, j);

		}

	}
	return debitTotalTrame;
}