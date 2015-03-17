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


int main (void)
{
    int socket_serveur = creer_serveur(8000);
    int socket_client ;
	char words[50];
	FILE *fp;
    
	while (1) {
		socket_client = accept(socket_serveur , NULL , NULL );
		traitement_signal(socket_client);
		int pid = fork();
		if(socket_client == -1){
			perror("accept");
			/* traitement d ’ erreur */
		}
		initialiser_signaux();
		/* On peut maintenant dialoguer avec le client */
		sleep(1);
		if (pid == 0) {
			while(1) {
				if ((fp = fdopen(socket_client, "w+")) == NULL) {
		    		fprintf(stdout,"Problème socket client.\n");
		   			exit(1);
	   			 }
				puts("<pawnee>\n");
				while (fgets(words,50,fp) != NULL  && words[0] != '\0') {
						int verifier = verif(words);
						while(strncmp("\r\n", fgets(words, sizeof(words), fp), 2) != 0){
						}
						if (verifier == -1){
							afficherErreur400(socket_client);
						}
						else {
							afficherBienvenue(socket_client);
						}
						
				}
				rewind(fp);  /* retour au début du fichier */
				while (fscanf(fp,"%s",words) > 0) {
		    		puts(words);
		    	}
	  			if (fclose(fp) != 0) {
		    		fprintf(stderr,"Erreur fermeture fichier\n");
				}

			}

	}	
	close(socket_client);
	}
	return 0;
}


