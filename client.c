// client.c

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int port = 0;
	char domaine [256]="";
	char ressource [256]="";
	printf("%s\n", "Entrer le domaine désiré :");
	fgets(domaine,sizeof(domaine),stdin);
	if(strlen(domaine) == 1){
		return -1;
	}

	printf("%s\n", "Entrer la ressource désirée :");
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
	printf("%s /%s :%d\n", domaine,ressource,port);
	return EXIT_SUCCESS;
}