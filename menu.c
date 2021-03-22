#include "menu.h"

void* menu(void *connfd, char *fd_empleados_on, sem_t sem_empleados_on) {
	int fds=0, leido=0; // por este file descriptor le voy a hablar al cliente
	bool bucle = 1;
	char op='0';

	fds = (int) (intptr_t) connfd;
	write(fds, "1) Empleado\n", 12);
	write(fds, "2) Cliente\n", 11);

	while (bucle) {
		leido = read(fds, &op, sizeof(char));
		printf("menu.c-> tam = %d lo que el cleinte manda op = %c\n", leido, op);
		//printf("-> while bucle = %d \n",bucle);

		if (op == '1') {
			bucle = 0; //PARA SALIR DEL BUCLE

			//printf("Estods datos +++ %s +++ deberiamos enviarlos a la lista de disponibles\n",datos_empleado);

			//cargarEmpleado(authenticate(fds));

			if(cargarEmpleado(authenticate(fds),fd_empleados_on,sem_empleados_on)==0){
				perror("ERROR: funcion cargarEmpleado devolvio 0\n");
				menu(connfd,fd_empleados_on, sem_empleados_on);
			} else {
				printf("menu.c-> SE CARGO EL EMPLEADO CORRECTAMENTE\n");
			}

			//free(datos_empleado);
			break;
		} else if (op == '2') {
			bucle = 0; //PARA SALIR DEL BUCLE
			menuCliente(fds,fd_empleados_on);
			break;
		} else {
			perror("El cliente se desconecto");
			break;
		}
	}

	return 0;
}
