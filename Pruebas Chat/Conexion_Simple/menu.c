#include "menu.h"
#include "CargarEmpleado.h"
#include "BuscarEmpleado.h"


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
			printf("Se conecto un empleado\n"); //ACA DEBERIAMOS CARGAR LOS DATOS DEL EMPLEADO Y CARGAR LOS DATOS DEL SOCKET QUE VA A CREAR

			cargarEmpleado(fd_empleados_on, sem_empleados_on);
			//menu(connfd, fd_empleados_on, sem_empleados_on);
			//ACA DEBERIAMOS PONER UNA SEÑAL QUE CIERRE LA CONECCION SI LA PERSONA CIERRA EL PROGRAMA
			break;
		} else if (op == '2') {
			bucle = 0; //PARA SALIR DEL BUCLE
			buscarEmpleado(); // ACA DEBERIAMOS IR A BUSCAR AL EMPLEADO Y CONECTARNOS EN EL SOCKET QUE EL EMPLEADO CREA
			//menu(connfd, fd_empleados_on, sem_empleados_on);
			//ACA DEBERIAMOS PONER UNA SEÑAL QUE CIERRE LA CONECCION SI LA PERSONA CIERRA EL PROGRAMA
			break;
		} else {
			perror("El cliente se desconecto");
			break;
		}
	}

	return 0;
}
