#include "menuCliente.h"

void* menuCliente(int connfd, char *fd_empleados_on) {
	int fds, leido; // por este file descriptor le voy a hablar al cliente
	bool bucle = 1;
	char *op;
	op = malloc(sizeof(char));
	fds = (int) (intptr_t) connfd;

	write(fds, "1) Ventas\n", 10);
	write(fds, "2) Consultas\n", 13);
	write(fds, "3) Reclamos\n", 12);
	write(fds, "4) Volver\n", 10);
	//ACA PODEMOS AGREGAR UNA OPCION MAS QUE SEA DE RECLAMOS
	fflush(stdin);
	fflush(stdin);
	leido = recv(fds, op, 1, 0); // PONGO 2 PORQUE AL PARECER VIENE EL SALTO DE LINEA COMO MUGRE
	 // EN EL BUFFER ENTONCES HAGO 2 LLAMADOS, NO SE DE QUE OTRA FORMA CORREGIRLO

	while (bucle) {
		leido = recv(fds, op, 1, 0);
		printf("menuCliente-> tam = %d lo que el cleinte manda op = -%s- \n", leido, op);

		if (op[0] == '1' || op[0] == '2' || op[0] == '3') {
			bucle = 0; //PARA SALIR DEL BUCLE
			comunicar(fds, op, fd_empleados_on); //FUNCION PARA COMUNICAR AL CLIENTE CON VENTAS
		} else if(op[0]=='4'){
			bucle=0;
			printf("ACA ME PASA LO MISMO, VA EL BUFFER CON MUGER Y COLOCA UN SALTO DE LINEA EN MENU EN VEZ DE PERMITIR AL CLIENTE ENVIAR EL TADO\n");
			//menu((void*) (intptr_t) connfd);
		} else {
			leido = read(fds, op, sizeof(char));
			printf("Opcion incorrecta vuelva a intentarlo\n");
		}
	}

	return 0;
}
