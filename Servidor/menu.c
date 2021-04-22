#include "menu.h"

void* menu(void *connfd, char ipStr[] ,char *fd_empleados_on, sem_t sem_empleados_on) {
	int fdClient=0;
	fdClient= (int) (intptr_t) connfd;

	char buffSend[100];//buffer de escritura;
	char buffRecived[100];//buffer de recepcion;
	bzero(buffSend,100); //limpiamos
	bzero(buffRecived, 100); //limpiamos

	while(1){
		//printf("Escuchando...\n");

		read(fdClient, buffRecived, sizeof(buffRecived)); // Esperamos por alguna peticion
		printf("comando recibido-->-%s- tam->%ld",buffRecived,strlen(buffRecived));

		if(!strcmp(buffRecived,"")){
			return 0;
		}else if(!strcmp(buffRecived,"1\n")){ //El cliente es un Empleado
			printf("Llamamos a la funcion para pedirle los datos al empleado\n");
		}else if(!strcmp(buffRecived,"2\n")){ // El cliente es un comprador
			printf("Llamamos a la funcion que le envie los datos al comprador\n");
		}


		bzero(buffRecived, 100); //vaciamos buffer

	}
	return 0;
}
