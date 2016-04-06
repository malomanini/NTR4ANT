#ifndef STRUCT_H
#define STRUCT_H

#define NB_SUBCARRIERS 128
#define NB_MAX_USER 200
#define NB_USERS 3
#define NB_TIME_SLOTS 5 
#define BUFFERS_PER_USER 10
#define PACKETS_CREATION_RATIO 50

typedef struct Packet Packet;
struct Packet
{
	int dateCreation;
	/*Nombre de bits dans le paquet (MAX = 100) */
	int bitsRestants;
	Packet *nextPacket;
};

typedef struct User User;
struct User
{
	int distance;
	int bufferVide;
	int SNRmoyen;
	int SNRActuels[NB_SUBCARRIERS];
	int sommeDelai;
	int sommePaquets;
	Packet *lePaquet;
};

typedef struct Antenne Antenne;
struct Antenne
{
	User *users[NB_MAX_USER];
};

#endif