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
		const char * message_bienvenue = "L'Audi RS5 est la concurrente directe de la BMW M3 ou de la Mercedes C63 AMG. Contrairement aux premières rumeurs qui laissaient supposer la présence du V10 bi-turbo de l'actuelle RS6 sous son capot, la RS5 propose un moteur bien connu de la marque aux anneaux puisqu'il s'agit du V8 de 4,2 L atmosphérique, dérivé de l'actuel Audi RS4 mais porté pour l'occasion à 450 ch et 460 Nm de couple (au lieu des 420 ch et 430 Nm de couple de l'RS4) afin de respecter la hiérarchie1. La Twingo III est un modèle d'automobile du constructeur Renault présentée le 13 février 2014 et exposée au public le 4 mars au salon de l'automobile de Genève, puis commercialisée à partir du premier septembre 2014. Elle remplace la seconde génération de Twingo, commercialisée de 2007 à 2014 qui est la mini citadine la plus vendue en France. Uniquement disponible en 5 portes (les deux précédentes générations n'étaient que des 3 portes) et motorisée par des blocs essence. Elle est basée sur la même plateforme technique que la Smart Forfour et smart fortwo II. L'Alfa Romeo Brera est à l'origine apparue comme un Concept Car à l'exposition automobile de Genève de 2002. Il a été conçu par Giorgetto Giugiaro chez Italdesign Giugiaro. La version concept était actionnée par un moteur de Maserati V8 développant une puissance avoisinant les 400 ch. La Brera a été largement acclamée, et des plans de production ont été plus tard annoncés pour 2005.\n";
		write(socket_client,message_bienvenue,strlen(message_bienvenue));

			while(1) {
				
				if ((fp = fdopen(socket_client, "w+")) == NULL) {
		    		fprintf(stdout,"Problème socket client.\n");
		   			exit(1);
	   			 }
				puts("<pawnee>\n");
				while (fgets(words,50,fp) != NULL  && words[0] != '\0') {
						if(verifGET(words) ==0 && compterMot(words) == 3){
							puts(words); 
						}
		    			//fprintf(fp, "%s", words);
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


