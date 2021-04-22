#include "menuComprador.h"

bool menuComprador(int sockfd){
  char buff_ex[100]; //buffer de escritura
  char buff_rx[100];  //buffer de lectura
  bzero(buff_rx, 100); //limpiamos
  bzero(buff_ex, 100); //limpiamos

  read(sockfd, buff_rx,sizeof(buff_rx)); // Recibe: Usuario
  printf("%s",buff_rx); // mostramos por la pantalla del cliente "Usuario:"
  bzero(buff_rx, 100); //limpiamos

  bzero(buff_ex,100);
  read(1,buff_ex,sizeof(buff_ex)); //Pedimos al cliente que ingrese el dato por pantalla
  //printf("Vamos a enviar \nbuff_ex-> -%s- tam->%ld\n",buff_ex,strlen(buff_ex));
  write(sockfd,buff_ex,strlen(buff_ex));

  read(sockfd, buff_rx, sizeof(buff_rx)); // Recibe: Clave:
  printf("%s",buff_rx); //mostramos por la pantalla del cliente "Clave:"
  bzero(buff_rx, 100); //limpiamos

  bzero(buff_ex,100);
  read(1,buff_ex,sizeof(buff_ex));
  //printf("Vamos a enviar \nbuff_ex-> -%s- tam->%ld\n",buff_ex,strlen(buff_ex));
  write(sockfd,buff_ex,strlen(buff_ex));

  read(sockfd, buff_rx, sizeof(buff_rx)); // Recibe: la respuesta de autenticacion ("0" o "1");
  printf("La respuesta del servidor con respecto a la autenticacion es -> -%s-\n",buff_rx); //mostramos por la pantalla del cliente la respuesta del servidor


  if(!strcmp(buff_rx,"0\n")){
    bzero(buff_rx, 100); //limpiamos
    return false;
  }else if(!strcmp(buff_rx,"1\n")){
    bzero(buff_rx, 100); //limpiamos
    return true;
  } else {
    printf("La respuesta del servidor no es ni -0\n- ni -1\n-");
    bzero(buff_rx, 100); //limpiamos
    return false;
  }
}
