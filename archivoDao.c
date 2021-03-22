
#include "archivoDao.h"

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
				strncat(empleado,"/",1);
				strncat(empleado,usuario,strlen(usuario));
				strncat(empleado,"/",1);
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
