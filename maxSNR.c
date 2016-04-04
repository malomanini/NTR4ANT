#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "maxSNR.h"
#include "distribution.h"
#include "initialisation.h"

int maxSNR(Antenne *antenne, int nb_users, int nb_sub) {	
	int MaxU;
	int g, j, debitTotalTrame = 0;

	//A MODIFIERRRRRRRRRRRRRRR
	for(j = 0; j < nb_sub ; j++){ //parcourt les subcariers
		MaxU = MaxUser(antenne, j, nb_users);

		for(g = 0; g < NB_TIME_SLOTS ; g++){// parcours les timeslots, //tant que User.BufferVide > 0 ou que g<5, on transmet au debit actuel a cet user
			if(empty(antenne, MaxU, nb_users)){
				MaxU = MaxUser(antenne, j, nb_users);
			}
			debitTotalTrame += consumeBit(antenne, MaxU, j);
		}

	}
	return debitTotalTrame;
}
			
	
