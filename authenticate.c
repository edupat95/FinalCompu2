#include "authenticate.h"

char *authenticate(int fd) {
	//---------------- VARIABLES --------------------------
	int leido=0;
	char *usr="", *pass="";
	usr = (malloc(1000));
	pass = (malloc(1000));

	//--------------------PEDIMOS DATOS AL EMPLEADO--------------
	printf("Un empleado esta intentando autenticarse\n");
	write(fd, "Ingrese usuario y clave\n", 24);

	write(fd, "Usuario:", 8);
	fflush(stdin);
	fflush(stdin);
	leido = recv(fd, usr, 1, 0); //HAY 2 funciones recv porque llega basura de alguna lado y impide escribir al empleado y es envia la basura
	//entonces luego de recibir la basura llamamos otra vez a la fc recv y el empleado puede escribir
	leido = recv(fd, usr, 20, 0);//DATO INTERESANTE, EL FLAG MSG_WAITALL IMPIDE QUE EL MENSAJE SE ENVIE HASTA QUE EL CLIENTE COMPLETE LOS BYTS pedidos (4)
	usr[leido] = '\0'; // nc manda streams no strings, y se nesecita un string para imprimir el mensaje

	write(fd, "Clave:", 6);
	leido = recv(fd, pass, 20, 0);
	pass[leido] = '\0';

	printf("authenticate.c->autenticate-> DATOS QUE RECIBE: %s - %s\n",usr,pass);

	//------------------ENVIAMOS LOS DATOS PARA SER COMPARADOS----------------
	return authenticate_ok(usr, pass, fd);
}

char *authenticate_ok(char *usr, char *pass, int fd) {

	printf("authenticate_ok -> DATOS QUE RECIBE: %ld/%s - %ld/%s\n",strlen(usr),usr,strlen(pass),pass);
	char *auxusr=NULL,*auxpass=NULL;
	char *empleado=NULL,*auxempleado=NULL;
	char *vacio="";
	char *auxfd=NULL;
	auxusr=malloc(1000);
	auxpass=malloc(1000);
	auxfd=malloc(sizeof(char));
	empleado=malloc(sizeof(char));
	auxempleado=malloc(sizeof(char));


	auxusr = strtok( usr, "\n\0" );
	printf("---->primer token (%s)\n",auxusr); //ESTO LO HACEMOS PARA QUITAR EL SALTO DE LINEA QUE VIENE EN usr y passs
	auxpass = strtok( pass, "\n\0" );
	printf("---->segundo token (%s)\n",auxpass);

	printf("authenticate_ok---> auxusr->%s auxpass->%s",auxusr,auxpass);

	sprintf(auxfd, "%d", fd);
	//pasamos el fd a char para poder meterlo en los datos del empleado

	strcpy(empleado,comparar(auxusr,auxpass));
	//la funcion comparar pertenece a archivoDao.h

	free(usr);
	free(pass);
	free(auxusr); //liberamos la memoria porque los datos ya fueron reconstruidos
	free(auxpass);

	if(strcmp(empleado,vacio)){
		printf("El usuario existe y sus datos son --> %s \n\n",empleado);
		printf("ACA TENEMOS QUE BUSCAR LA FORMA DE CARGAR AL EMPLEADO COMO DISPONIBLE PARA SER DEMANDADO POR EL CLIENTE\n");
		strncpy(auxempleado,auxfd,strlen(auxfd));
		strncat(auxempleado,"/",1);
		strncat(auxempleado,empleado,strlen(empleado));
		printf("\nEl usuario reconstruido en authenticate_ok -> %s\n",auxempleado);
		free(empleado);
		return auxempleado;
	}else{
		printf("ERROR AL AUTENTICARSE\n");
		free(empleado);
		free(auxempleado);
		authenticate(fd);
		//menu((void*) (intptr_t) fd);
	}

	return vacio;
}
