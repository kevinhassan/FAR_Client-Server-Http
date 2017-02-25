// client.c

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>

int main(void) {
	int port = 0;
	char domaine [256]="";
	char ressource [256]="";
	char *ip;
	while(strlen(domaine)<=1){
		printf("%s\n", "Entrer le domaine désiré :");
		fgets(domaine,sizeof(domaine),stdin);

	}
	printf("%s\n", "Entrer la ressource désirée (par default : index.html):");
	fgets(ressource,sizeof(ressource),stdin);
	if(strlen(ressource) == 1){
		strcpy(ressource,"index.html");
	}
	while(port<=0){
		printf("%s\n", "Entrer le port (-1: pour le port 80) :");
		scanf("%d",&port);
		if(port == -1){
			port = 80;
		}
	}
	//supprimer les retours à la ligne
	strtok(domaine, "\n");
	/*strcat(domaine,"/");
	strtok(ressource, "\n");
	strcat(domaine,ressource);*/
	printf("%s\n",domaine);

	/**
		Récupérer l'adresse ip à partir d'un domaine
	**/
	struct hostent *pHostInfo =gethostbyname(domaine);
	ip =inet_ntoa(*( struct in_addr*)( pHostInfo -> h_addr));

	/**
		Configuration du socket
	**/
	int sock;
	struct sockaddr_in sin;

	/* Creation de la socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);

	/* Configuration de la connexion */
	sin.sin_addr.s_addr = inet_addr(ip);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);

	return EXIT_SUCCESS;
}
