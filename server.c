// tcp_serveur.c

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
  char *token;
  char *nameFile;
  char buffer[256]; 
  while(port<=0){
    printf("%s\n", "Entrer le port (-1: pour le port 80) :");
    scanf("%d",&port);
    if(port == -1){
      port = 80;
    }
  }

  /* Socket et contexte d'adressage du serveur */
  struct sockaddr_in sin;
  int sock;
  socklen_t recsize = sizeof(sin);

  /* Socket et contexte d'adressage du client */
  struct sockaddr_in csin;
  int csock;
  socklen_t crecsize = sizeof(csin);

  /* Creation d'une socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);

  /* Configuration */
  sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
  sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
  sin.sin_port = htons(port);               /* Listage du port */
  bind(sock, (struct sockaddr*)&sin, recsize);

  /* Demarrage du listage (mode server) */
  listen(sock, 5);

  /* Attente d'une connexion client */
	while(1){
	  csock = accept(sock, (struct sockaddr*)&csin, &crecsize);
	  int pid = fork();
	  if(pid == 0){
   	  char buffer[256]="";
      //Attendre de recevoir la requête du client
		  recv(csock, buffer, sizeof(buffer), 0);
      //char *tok = strtok(ma_chaine, " ");
		  printf("%s\n", buffer);
      //Si la requête est de type GET on envoie la ressource demandée
      char *tok = strtok(buffer, " ");
      if(strcmp(tok,"GET") == 0){
        tok = strtok(NULL, " ");

        FILE *f;
        nameFile = tok;
        tok = strtok(nameFile, "/");
        nameFile = tok;
        printf("%s\n", nameFile);
        f=fopen(nameFile,"r");
        char buffer2[256]="";
        if(f != NULL){
          while(fgets(buffer2,256,f)!=NULL){
            printf("%s\n", buffer2);
            send(csock,buffer2,256,0);
          }
          fclose(f);
        }else{
          printf("%s\n", "fichier introuvable");
        }
      }
	  }
	}
  /* Fermeture de la socket client et de la socket serveur */
  shutdown(csock,2);
  close(csock);
  close(sock);

  return EXIT_SUCCESS;

}//main
