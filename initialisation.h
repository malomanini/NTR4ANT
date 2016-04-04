
#include "struct.h"

#ifndef INITIALISATION_H
#define INITIALISATION_H

Packet* createPacket();
User* initUser();
void initAntenne(Antenne *antenne);

void initMatriceDebits(Antenne *antenne);
void produceBit(Antenne *antenne, int actualTime);
int consumeBit(Antenne *antenne, int currentUser, int subCarrier);
int MaxUser(Antenne *antenne, int subCarrier);
int empty(Antenne *antenne, int currentUser);

#endif 

