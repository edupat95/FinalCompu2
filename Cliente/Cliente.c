#include "AllIncludes.h"

int fd;
void handler(int nro);

int main(void){
  struct sockaddr_in direccionServidor;

  int fdSrv = socket(AF_INET, SOCK_STREAM, 0);

  memset(&direccionServidor,0,sizeof(direccionServidor));

  direccionServidor.sin_family = AF_INET;
  direccionServidor.sin_addr.s_addr = inet_addr("127.0.0.1"); // direccion a la que se va a conectar
  direccionServidor.sin_port = htons(22000);

  char buffSend[100];//buffer de escritura;
  char buffRecived[100];//buffer de recepcion;
  bzero(buffSend,100);
  bzero(buffRecived,100);

  if(connect(fdSrv, (void*)&direccionServidor, sizeof(direccionServidor)) != 0){
    perror("No se pudo conectar");
    return 1;
  }
  fd=fdSrv;

  while(1){
    printf("1)Empleado\n2)Cliente\n");

    read(1,buffSend,sizeof(buffSend)); //leemos lo que vamos a enviar
    write(fdSrv,buffSend,strlen(buffSend));
    printf("La peticion enviada fue-> %s",buffSend);

    if(!strcmp(buffSend,"1\n")){
      printf("deberia pedir usuario y clave\n");
      return 0;
    } else if(!strcmp(buffSend,"2\n")){
      printf("Deberia conectar con el empleado\n");
      return 0;
    }else{
      printf("Opcion incorrecta\n");
    }

    bzero(buffSend,100);
  }

  signal(SIGINT, handler);

  printf("FIN\n");
  return 0;
}

void handler(int nro){
  char buffSend[100];//buffer de escritura;
  bzero(buffSend,100);
  printf("handle ejecutado le escribiremos a fd->%d ",fd);
  char *comando="exit\n\0";
  strncpy(buffSend,comando,strlen(comando));
  read(1,buffSend,sizeof(buffSend)); //leemos lo que vamos a enviar
  write(fd,buffSend,strlen(buffSend));

}
