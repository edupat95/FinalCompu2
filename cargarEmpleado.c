#include "cargarEmpleado.h"


int cargarEmpleado(char *empleado, char *fd_empleados_on, sem_t sem_empleados_on) {
	//printf("cargarEmpleao.c -> Datos recibidos %s \n", empleado);
	char *bufferAux=NULL;
	bufferAux=malloc(256);

	sem_wait(&sem_empleados_on);
	strncpy(bufferAux,fd_empleados_on,strlen(fd_empleados_on)); //guardamos la lista de empleados
	strncat(bufferAux,"\n",1);
	strncat(bufferAux,empleado,strlen(empleado));//agregamos el empleado a la lista

	strncpy(fd_empleados_on,bufferAux,strlen(bufferAux));//volvemos a escribir en la memoria la lista de empleados modificada

	free(bufferAux); // liberamos

	printf("++++++++++++++PRUEBA++++++++++++++++++++\n");
	printf("imprimimos el archivo, como una matriz de caracteres\n");
	for(int i=0; i<strlen(fd_empleados_on); i++){
		printf("%c",fd_empleados_on[i]);
	}

	sem_post(&sem_empleados_on);
	printf("\n");



	//POSTERIORMENTE A LA CARGA DEL EMPLEADO EN EL ARCHIVO HABRA QUE PONER SEÑALES
	//POR LAS DUDAS DE UNA DESCONEXION.ESTA SEÑAL LLAMARA A UNA FUNCION QUE EDITARA LA MEMORIA COMPARTIDA

	return 1;
}

