#include <stdio.h>
#include <string.h>
#include "socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
int main (void)
{
    int socket_serveur = creer_serveur(8000);
    	int socket_client ;
    	printf("Ca marche");
		socket_client = accept(socket_serveur , NULL , NULL );
		if(socket_client == -1)
		{
			perror("accept");
			/* traitement d ’ erreur */
		}
		/* On peut maintenant dialoguer avec le client */
		const char * message_bienvenue = "Bonjour,bienvenue sur mon serveur\n " ;
		write(socket_client,message_bienvenue,strlen(message_bienvenue));
}	

