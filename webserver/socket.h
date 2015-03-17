#include <sys/types.h>
#include <sys/socket.h>
# ifndef __SOCKET_H__
# define __SOCKET_H__
/** Crée une socket serveur qui écoute sur toute les interfaces IPv4
de la machine sur le port passé en paramètre . La socket retournée
doit pouvoir être utilisée directement par un appel à accept .
La fonction retourne -1 en cas d ’ erreur ou le descripteur de la
socket créée . */
int creer_serveur(int port);
void initialiser_signaux (void);
void traitement_signal (int sig);
int verif(char* buffer);
int verifGET(char* buffer);
int compterMot(char* buffer);
int verifHTTP(char * buffer,int entierdeb);
int ignorerLigne(char * buffer);
void afficherBienvenue(int socket_client);
void afficherErreur400(int socket_client);
#endif
