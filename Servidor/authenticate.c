#include "authenticate.h"
#include <stdio.h>
#include <stdio_ext.h>


char *authenticate(void *connfd) {
	//---------------- VARIABLES --------------------------
	int fd = (int) (intptr_t) connfd;
	char *usr, *pass;
	char buff_rx[100]; //buffer para recibir
	char buff_ex[100]; //buffer para escribir
	usr = (char*)malloc(30*(sizeof(char)));
	pass = (char*)malloc(30*(sizeof(char)));
	//--------------------PEDIMOS DATOS AL EMPLEADO--------------
	strncpy(buff_ex,"Usuario:\n",10);
	write(fd, buff_ex, strlen(buff_ex)); //Le mandamos "Usuario: " al cliente
	bzero(buff_ex, 100);

	bzero(buff_rx, 100);
	read(fd, buff_rx, sizeof(buff_rx)); //leemos el usuario que manda el cliente
	printf("buff_rx->-%s- tam->%ld \n",buff_rx,strlen(buff_rx));
	strncpy(usr,buff_rx,strlen(buff_rx)); //Copiamos el usuario en la variable usr

	strncpy(buff_ex,"Clave:\n",8);
	write(fd, buff_ex, strlen(buff_ex));//Le mandamos "Clave: " al cliente
	bzero(buff_ex, 100);

	bzero(buff_rx, 100);
	read(fd, buff_rx, sizeof(buff_rx)); //leemos la clave que manda el cliente
	printf("buff_rx->-%s- tam->%ld",buff_rx,strlen(buff_rx));
	strncpy(pass,buff_rx,strlen(buff_rx)); //Copiamos el usuario en la variable usr
	bzero(buff_rx, 100);

	usr = strtok(usr,"\n");
	pass = strtok(pass,"\n");

	printf("\nDatos que nos quedan para trabajar en el servidor:\n usr->-%s-\npass->-%s-\n",usr,pass);

	//------------------ENVIAMOS LOS DATOS PARA SER COMPARADOS----------------
	char *retorno=authenticate_ok(usr, pass, connfd);
	if(!strcmp(retorno,"")){
		strcpy(buff_ex,"0\n");
		write(fd, buff_ex, strlen(buff_ex));//Le mandamos "Clave: " al cliente
		bzero(buff_ex, 100);
	} else {
		strcpy(buff_ex,"1\n");
		write(fd, buff_ex, strlen(buff_ex));//Le mandamos "Clave: " al cliente
		bzero(buff_ex, 100);
	}
	return retorno;
	//return authenticate_ok(usr, pass, connfd);
}

char *authenticate_ok(char *usr, char *pass, void * connfd) { // retorna fd/id/usuario/tipo

	printf("authenticate_ok -> DATOS QUE RECIBE: %ld/%s - %ld/%s\n",strlen(usr),usr,strlen(pass),pass);
	int fd = (int) (intptr_t) connfd;

	char *empleado=NULL,*auxempleado=NULL;
	char *vacio="";
	char *auxfd=NULL;
	auxfd=(char*)malloc(10*sizeof(char));
	empleado=(char*)malloc(128*sizeof(char));
	auxempleado=(char*)malloc(128*sizeof(char));

	sprintf(auxfd, "%d", fd);
	//pasamos el fd a char para poder meterlo en los datos del empleado

	strcpy(empleado,usr);//LINEA A CAMBIAR//strcpy(empleado,comparar(auxusr,auxpass));
	strcat(empleado,"/");
	strcat(empleado,pass);

	strcpy(empleado,comparar(usr,pass)); //comparamos datos de logueo con los datos del archivo

	free(usr); //liberamos las variables que ya no utilizamos
	free(pass);//liberamos las variables que ya no utilizamos

	if(strcmp(empleado,vacio)){
		printf("El usuario existe y sus datos son --> %s \n\n",empleado);
		strncpy(auxempleado,auxfd,strlen(auxfd));
		strncat(auxempleado,"/",2);
		strncat(auxempleado,empleado,strlen(empleado));
		printf("\nEl usuario reconstruido en authenticate_ok -> %s\n",auxempleado);
		free(empleado);//liberamos las variables que ya no utilizamos
		free(auxfd);//liberamos las variables que ya no utilizamos
		return auxempleado;  // retorna fd/id/usuario/tipo
	}else{
		printf("ERROR AL AUTENTICARSE\n");
		free(empleado);//liberamos las variables que ya no utilizamos
		free(auxfd);//liberamos las variables que ya no utilizamos
		free(auxempleado);//liberamos las variables que ya no utilizamos
	}

	return vacio;
}

char *comparar(char *usr, char *pass) {
	printf("A COMPARAR LE LLEGA %s - %s \n",usr,pass);
	int fda = 0, leido = 0;
	//char buffer[1024];
	char *buff=NULL,*id=NULL,*usuario=NULL,*clave=NULL,*tipo=NULL;
	char *vacio="";
	char *empleado=NULL;

	buff = (malloc(sizeof(char)));
	empleado=malloc(sizeof(char));
	id = (malloc(sizeof(char)));
	usuario = (malloc(sizeof(char)));
	clave = (malloc(sizeof(char)));
	tipo = (malloc(sizeof(char)));

	//------------------------ABRIMOS EL ARCHIVO PARA VER SU CONTENIDO--------------------

	fda = open("Archivos/Empleados.txt", O_RDONLY, 0666); //abro archivo de empleados
	if (fda == -1){
	    char* mensaje="Error al abrrir el archivo que contiene a los empreados";
	    write(1,mensaje,strlen(mensaje));
	  }
	int i=0;
	while ((leido = read(fda, buff, sizeof(char))) > 0) { // muestro lo que tiene el archivo empleados

		//--------------ANALIZAMOS EL CONTENIDO DEL ARCHIVO-------------------------
		//write(1,buff,sizeof(char));
		if(i==0){ //VIENE EL ID
			//printf("SIGNIFICA QUE EL DATO QUE VIENE ES EL ID DE LA PERSONA \n\n\n");
			strncat(id,buff,strlen(buff));
			//printf("->%s\n",buff);
			i=1;
		}else if(*buff=='/'){ //VIENE OTRA PALABRA
			//printf("VIENE OTRA PALABRA \n\n\n");
			i=i+1;
		}  else if (*buff=='\n'){ //VIENE OTRO EMPLEADO
			//printf("DATOS DE LA PERSONA RESCONSTRUIDOS: \n ID->%s\n USR->%s\n PASS->%s\n TIPO->%s\n ",id,usuario,clave,tipo);
			printf("#### %s - %s and %s - %s ####\n",usr,usuario,clave,pass);
			if((!strcmp(usuario,usr)) && (!strcmp(clave,pass))){
				//printf("$$$###!!!Coincide usuario y contraseña\n %s _ %s",clave,pass);

				strncpy(empleado,id,strlen(id));
				strncat(empleado,"/",2);
				strncat(empleado,usuario,strlen(usuario));
				strncat(empleado,"/",2);
				strncat(empleado,tipo,strlen(tipo));

				return empleado;
			}
			strcpy(id,vacio); //RECETEAMOS TODOS LOS VALORES
			strcpy(usuario,vacio); //SOLO QUIERO DEJARLOS VACIO
			strcpy(clave,vacio); //POR ESO NO USO strncpy
			strcpy(tipo,vacio);

			//printf("VIENEN LOS DATOS DE OTRA PERSONA \n\n\n");
			i=0;
		} else if(*buff=='\0'){
			printf("FIN ARCHIVO \n\n\n");
		} else {
			if(i==1){
				//printf("->Dato perteneciente al id ");
				strncat(id,buff,strlen(buff));
			} else if(i==2){
				//printf("->Dato perteneciente al usr ");
				strncat(usuario,buff,strlen(buff));
			} else if(i==3){
				//printf("->Dato perteneciente a la clave ");
				strncat(clave,buff,strlen(buff));
			} else if(i==4){
				//printf("->Dato perteneciente al tipo de empleado ");
				strncat(tipo,buff,strlen(buff));
			}
			//printf("->%s\n",buff);
		}
	}


	return vacio;
}
