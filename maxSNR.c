#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "maxSNR.h"
#include "distribution.h"
#include "initialisation.h"

int maxSNR(Antenne *antenne) {	
	int MaxU;
	int g, j, debitTotalTrame = 0;

	for(j = 0; j < 128 ; j++){ //parcourt les subcariers
		MaxU = MaxUser(antenne, j);

		for(g = 0; g < 5 ; g++){// parcours les timeslots, //tant que User.BufferVide > 0 ou que g<5, on transmet au debit actuel a cet user
			if(empty(antenne, MaxU)){
				MaxU = MaxUser(antenne, j);
			}
			debitTotalTrame += consumeBit(antenne, MaxU, j);
		}

	}
	return debitTotalTrame;
}
			
	
