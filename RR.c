#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "RR.h"
#include "distribution.h"
#include "initialisation.h"

int RR(Antenne *antenne, int nb_users, int nb_sub){
	int i = 0;
	int j = 0;
	int currentUser = 0;
	int debitTotalTrame = 0;
	int count = 0;

	for(i = 0; i < NB_TIME_SLOTS ; i++){
		for(j = 0; j< nb_sub ; j++){
			while(empty(antenne, currentUser, nb_users)){
				currentUser = (currentUser+1) % nb_users;
				count++;
				if(count>nb_users){
					return debitTotalTrame;
				}
			}
			debitTotalTrame += consumeBit(antenne, currentUser, j);
			currentUser = (currentUser+1) % nb_users;
		}
	}
	return debitTotalTrame;

}
