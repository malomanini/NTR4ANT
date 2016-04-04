
#include "struct.h"

#ifndef INITIALISATION_H
#define INITIALISATION_H

Packet* createPacket();
User* initUser();
void initAntenne(Antenne *antenne, int nb_users);

void initMatriceDebits(Antenne *antenne, int nb_users);
void produceBit(Antenne *antenne, int actualTime, int nb_users);
int consumeBit(Antenne *antenne, int currentUser, int subCarrier);
int MaxUser(Antenne *antenne, int subCarrier, int nb_users);
int empty(Antenne *antenne, int currentUser, int nb_users);

#endif 

