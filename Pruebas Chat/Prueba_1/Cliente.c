#include "Servidor.h"


void main(void){
  char cadena[100]; //no servira para guardar los mensajes que recivamos
  int sockfd; //esta variable contendra el socket del servidor
  struct sockaddr_in servaddr;
  FILE *myf = fopen("conversacion_cliente.txt", "a");
  time_t t; // nos permite utilizar la hora
  struct tm *tm;
  char hora[100];
  char *tmp;
  char sendline[100] = "Usando el puerto 22000 \n";

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(22000);

  inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr)); //tenemos que tener el ip con el cual nos vamos a comunicar, en este caso con nuestra propia compu
  connect(sockfd,(struct sockaddr*)&servaddr, sizeof(servaddr)); //Nos conectamos al servidor, esto deberiamos hacerlo con netcat

  printf("\n\n------Se inicio el chat-----\n\n");
  fputs("\n\n------Se inicio el chat-----\n\n", myf);

  while(!strstr(cadena, "adios") && !strstr(sendline, "adios")){
    bzero(cadena, 100);   //mismo codigo que en el servidor
    t = time(NULL); //mismo codigo que en el servidor
    tm = localtime(&t); //mismo codigo que en el servidor
    strftime(hora, 100, "\n yo (%H:%M) -> ", tm); //mismo codigo que en el servidor
    printf("%s", hora); //mismo codigo que en el servidor
    gets(sendline); //mismo codigo que en el servidor
    tmp = strcat(hora, sendline); //mismo codigo que en el servidor
    fputs(tmp,myf); //mismo codigo que en el servidor
    write(sockfd, sendline, strlen(sendline));
    if(!strstr(cadena, "adios")){ //si el mensaje es adios finaliza el chat
      strftime(hora, 100, "\n otro usuario (%H:%M) -> ",tm);
      read(sockfd, cadena, 100);
      tmp = strcat(hora, cadena);
      printf("%s", tmp);
      fputs(tmp,myf);
    }
  }
  printf("\n\n------Conversacion finalizada-----\n\n");
  printf("\n\n------Se genero el archivo con la conversacion-----\n\n");
  fclose(myf);

}
