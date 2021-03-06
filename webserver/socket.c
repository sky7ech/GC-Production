#include "socket.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include<stdlib.h>
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
			if (cpt == 3){
				if(verifHTTP(buffer,i) != 0){
					return -1;
				}
			}
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
	
int verifHTTP(char * buffer,int entierdeb){
	if (buffer[entierdeb] == 'H' && buffer[entierdeb +1] == 'T' && buffer[entierdeb + 2] =='T' && buffer[entierdeb +3] == 'P' &&  buffer[entierdeb +4] =='/' && buffer[entierdeb + 5] == 1 && buffer[entierdeb + 6] == '.' &&( buffer[entierdeb + 7] =='1' || buffer[entierdeb + 7] == '0')){
		return 0;
	}
	return -1;
}

void afficherBienvenue(int socket_client){
		const char * message_bienvenue = "L'Audi RS5 est la concurrente directe de la BMW M3 ou de la Mercedes C63 AMG. Contrairement aux premières rumeurs qui laissaient supposer la présence du V10 bi-turbo de l'actuelle RS6 sous son capot, la RS5 propose un moteur bien connu de la marque aux anneaux puisqu'il s'agit du V8 de 4,2 L atmosphérique, dérivé de l'actuel Audi RS4 mais porté pour l'occasion à 450 ch et 460 Nm de couple (au lieu des 420 ch et 430 Nm de couple de l'RS4) afin de respecter la hiérarchie1. La Twingo III est un modèle d'automobile du constructeur Renault présentée le 13 février 2014 et exposée au public le 4 mars au salon de l'automobile de Genève, puis commercialisée à partir du premier septembre 2014. Elle remplace la seconde génération de Twingo, commercialisée de 2007 à 2014 qui est la mini citadine la plus vendue en France. Uniquement disponible en 5 portes (les deux précédentes générations n'étaient que des 3 portes) et motorisée par des blocs essence. Elle est basée sur la même plateforme technique que la Smart Forfour et smart fortwo II. L'Alfa Romeo Brera est à l'origine apparue comme un Concept Car à l'exposition automobile de Genève de 2002. Il a été conçu par Giorgetto Giugiaro chez Italdesign Giugiaro. La version concept était actionnée par un moteur de Maserati V8 développant une puissance avoisinant les 400 ch. La Brera a été largement acclamée, et des plans de production ont été plus tard annoncés pour 2005.\n";
		write(socket_client,message_bienvenue,strlen(message_bienvenue));
}

void afficherErreur400(int socket_client){
	const char * message_bienvenue = "HTTP/1.1 400 Bad Request\nConnection: close\nContent-Length: 17\n400 Bad request";
	write(socket_client,message_bienvenue,strlen(message_bienvenue));
}

void afficherReussite200(int socket_client){
	const char * message_bienvenue = "HTTP/1.1 200 OK";
	write(socket_client,message_bienvenue,strlen(message_bienvenue));
}

