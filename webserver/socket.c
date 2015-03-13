#include "socket.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


int creer_serveur(int port){

	int socket_serveur;
	socket_serveur = socket ( AF_INET , SOCK_STREAM , 0);
	if ( socket_serveur == -1)
	{
		perror("socket_serveur ");
		return -1;
	/* traitement de l ’ erreur */
	}
	int optval = 1;
	if (setsockopt(socket_serveur ,SOL_SOCKET,SO_REUSEADDR,& optval , sizeof ( int )) == -1)
		perror ( " Can not set SO_REUSEADDR option " );
	/* Utilisation de la socket serveur */
	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET; /* Socket ipv4 */
	saddr.sin_port = htons(port); /* Port d’écoute */
	saddr.sin_addr.s_addr = INADDR_ANY; /* écoute sur toutes les interfaces */
	if ( bind (socket_serveur,(struct sockaddr *)& saddr,sizeof(saddr))== -1)
	{
		perror("bind socker_serveur");
		/* traitement de l’erreur */
	}
	if (listen(socket_serveur,10)==-1)
	{
		perror ("listen socket_serveur");
		return -1;
		/* traitement d’erreur */
	}
	return socket_serveur;
}

void traitement_signal (int sig){
		printf ("Signal %d reçu \n" , sig);
		waitpid(-1,NULL,WNOHANG);
}

void initialiser_signaux (void) {
	
	struct sigaction sa;
	sa.sa_handler = traitement_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if(sigaction (SIGCHLD , &sa , NULL) == -1){
		perror ("sigaction(SIGCHLD)");
	}
	if (signal(SIGPIPE,SIG_IGN) == SIG_ERR) {
		perror ("signal");
	}
}


int compterMot(char* buffer){
	int i = 0;
	int cpt = 0;
	while(buffer[i] != '\0'){
		if(buffer[i] == ' '){
			i++;
		}
		else {
			cpt ++;
			i++;
			while (buffer[i] != ' ' && buffer[i] !='\0'){
				i++;
			}
		}
	}
	return cpt;	
}

int verifGET(char* buffer){
	if (buffer[0] =='G' && buffer[1] =='E' && buffer[2] == 'T'){
		return 0;
	}
	return -1;
}

int verif(char* buffer){
	if (verifGET(buffer)== 0 && (compterMot(buffer)==3)){
		return 0;
	}
	return -1;
	}



