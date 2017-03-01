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
	strtok(ressource, "\n");

	/**
		Récupérer l'adresse ip à partir d'un domaine
	**/
	struct hostent *pHostInfo =gethostbyname(domaine);
	ip =inet_ntoa(*( struct in_addr*)( pHostInfo -> h_addr));
	/**
		Configuration du socket
	**/
	int sock;
	char buffer[100];
	int byte_count;
	struct sockaddr_in sin;

	/* Creation de la socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);

	/* Configuration de la connexion */
	sin.sin_addr.s_addr = inet_addr(ip);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);

	connect(sock, (struct sockaddr*)&sin, sizeof(sin));

	/**
		Former le header pour l'envoyer au server
	**/
	char *header;
	header = malloc(sizeof(domaine)+sizeof(ressource));
	strcpy(header,"GET /");
	strcat(header,ressource);
	strcat(header," HTTP/1.1\r\nHost: ");
	strcat(header,domaine);
	strcat(header,"\r\n\r\n");
	//printf("%s\n", header);

	/**
		Communication avec le server et récupération du contenu
	**/
	int res =1;
	send(sock,header,strlen(header),0);
	char nameFile[256] = "";
	strcat(nameFile,ressource);
	/**
		Ecrire la commande 
	**/
	//char cmd[256] = "firefox ";//Dans le cas de linux
	char cmd[256] = "open -a safari ";//Dans le cas de OSX
	strcat(cmd,ressource);
	/**
		Creer fichier et le remplir avec la requete
	**/
	FILE *f;
	f=fopen("index.html","w");
	do{
		res=recv(sock,buffer, 99,0);
		strcat(buffer,"\0");
		fputs(buffer,f);
		fflush(stdout);
	}while(res>0);
	fclose(f);
	close(sock);
	system(cmd);
	return EXIT_SUCCESS;
}
