#include "CargarEmpleado.h"

void cargarEmpleado(char *fd_empleados_on,sem_t sem_empleados_on){
  printf("Hola cargarEempleado\n");
  asignarPuerto(fd_empleados_on,sem_empleados_on);


  /*
  int fd_socket_empleado=0, chat_fd=0;
	struct sockaddr_in procrem={};
	fd_socket_empleado = socket(AF_INET, SOCK_STREAM, 0);
	if  (fd < 0 ){
		perror ("socket");
		return -1;
	}

	procrem.sin_family = AF_INET;
	procrem.sin_port = htons(8080);
	procrem.sin_addr.s_addr = htonl(INADDR_ANY);

	int a=1;
	setsockopt(fd_socket_empleado, SOL_SOCKET, SO_REUSEADDR,&a, sizeof a);
	if (bind(fd_socket_empleado,(struct sockaddr *)&procrem, sizeof procrem) < 0 ) {
		perror ("bind");
		return -1;
	}

  listen(fd, 50);
  */






  //ACA CREAMOS EL SOCKET DONDE VAMOS A REALIZAR LA CONECCION
}
int asignarPuerto(char *fd_empleados_on,sem_t sem_empleados_on){
  int puerto=22001;
  char *vacio="";
  printf("Imprimimos contenido de fd_empleados_on -> \n%s",fd_empleados_on);
  if(!strcmp(fd_empleados_on,vacio)){
    //char *aux_puerto=NULL;
    //aux_puerto=malloc(sizeof(char));
    printf("Nigun empleado usando puertos\n");
    printf("Deberiamos usar el puerto -> %d\n",puerto);
    //VAMOS A TRABAJAR CON LA MEMORIA POR ENDE TENEMOS QUE USAR SEMAFOROS PARA QUE LOS EMPLEADOS NO ENTREN A LA MISMA VEZ
    //sprintf(aux_puerto, "%d", puerto); //convertimos el puerto a char para poder cargarlo en la memoria
    sem_wait(&sem_empleados_on);
    strncpy(fd_empleados_on,"22001",5);
    //strncpy(fd_empleados_on,aux_puerto,strlen(aux_puerto)); //escribimos en la memoria el primer puerto "22001"
    strncat(fd_empleados_on,"\n",1); //agregamos un enter para que el nuevo puerto se escriba abajo

    sem_post(&sem_empleados_on);
    //TERMINAMOS DE TRABAJAR CON LA MEMORIA

  } else {

    printf("Archivo no vacio, hay puertos ocupados\n");
    printf("Deberiamos analizar la memoria y ver que puerto podemos utilizar\n");
    printf("Imprimimos contenido de fd_empleados_on ->\n+++\n%s \n+++\n",fd_empleados_on);

    /*
    sem_wait(&sem_empleados_on);
    strncpy(bufferAux,fd_empleados_on,strlen(fd_empleados_on)); //guardamos la lista de empleados
  	strncat(bufferAux,"\n",1);
  	strncat(bufferAux,empleado,strlen(empleado));//agregamos el empleado a la lista
    sem_post(&sem_empleados_on);
    */
  }
  return puerto;
}
