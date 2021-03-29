#include "Servidor.h"

void main(void){
  char cadena[100]; //no servira para guardar los mensajes que recivamos
  int listen_fd, conn_fd; //una es para crear al socket y la otra es para recibir a los clientes
  struct sockaddr_in servaddr; //
  FILE *myf = fopen("conversacion_servidor.txt", "a"); //para guardar la conversacion
  time_t t; // nos permite utilizar la hora
  struct tm *tm; //
  char hora[100]; //
  char *tmp;
  char sendline[100] = "Usando el puerto 22000 \n"; //Variable para guardar los mensajes que queremos enviar

  listen_fd = socket(AF_INET, SOCK_STREAM, 0); //abrimos el socket
  bzero (&servaddr, sizeof(servaddr)); // para asegurarnos que el socket esta vacio, lo llenamos de ceros con la fc bzero

  servaddr.sin_family = AF_INET; //BUROCRACIA CUANDO USAMOS SOCKETS
  servaddr.sin_addr.s_addr = htons (INADDR_ANY); //BUROCRACIA CUANDO USAMOS SOCKETS, para cualquier cliente que intente conectarse
  servaddr.sin_port = htons(22000); //BUROCRACIA CUANDO USAMOS SOCKETS, puerto que vamos a utilizar

  bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)); //La funcion bind, sirve para indicarle al sistema que ya esta abierto el socket

  listen(listen_fd, 10); // le indicamos que vamos a empezar a atender a los clientes, se soportara 10 clientes

  conn_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL); //

  printf("\n\n------Se inicio el chat-----\n\n");
  fputs("\n\n------Se inicio el chat-----\n\n",myf);

  while(!strstr(cadena, "adios") && !strstr(sendline, "adios")){ //COMENZAMOS EL CHAT, MIENTRAS NO ESCRIBAN LA PALABRA "adios", el chat no finalizara
    bzero(cadena, 100); //vaciamos la cadena recibida llenandola de ceros.
    t = time(NULL);
    tm = localtime (&t);
    strftime(hora, 100, "\n otro usuario (%H:%M) -> ", tm);//guardamos la hora en la variable hora

    read(conn_fd, cadena, 100); //leemos el mensaje
    tmp = strcat(hora, cadena);  // concatenamos la hora al mensaje
    printf("%s", tmp);
    fputs(tmp, myf); //guardamos la conversacion en el archivo de texto que creamos

    if(!strstr(cadena, "adios")){ //si el mensaje no es "adios" continuamos
      strftime(hora, 100, "\n yo (%H:%M) -> ",tm);
      printf("%s", hora); ////imprimimos la hora de envio del mensaje
      gets(sendline); //para enviar la cadena usamos la funcion gets, esta funcion enviara el mensaje al escribir la tecla enter
      tmp = strcat(hora, sendline); //mensaje concatenado con la hora
      write(conn_fd, sendline, strlen(sendline)+1); // para enviar el mensaje utilizaremos la funcion write, parametros: socket_donde_vamos_escribir/cadena_que_vamos_a_mandar/longitud_del_mensaje
      fputs(tmp, myf);//guardamos el mensaje en el archivo de texto
      }
  }
  printf("\n\n------Conversacion finalizada-----\n\n");
  printf("\n\n------Se genero el archivo-----\n\n");
  fclose(myf);
}
