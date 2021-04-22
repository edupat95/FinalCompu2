
#include "menu.h"

char *fd_empleados_on;
sem_t sem_empleados_on;

int main(int argc, char * argv[]){
	int fd, connfd;
	struct sockaddr_in procrem={};
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if  (fd < 0 ){
		perror ("socket");
		return -1;
	}

	procrem.sin_family = AF_INET;
	procrem.sin_port = htons(22000);
	procrem.sin_addr.s_addr = htonl(INADDR_ANY);

	int a=1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,&a, sizeof a);
	if (bind(fd,(struct sockaddr *)&procrem, sizeof procrem) < 0 ) {
		perror ("bind");
		return -1;
	}

	listen(fd, 50);
	//INICIALIZAMOS VARIABLES QUE COMPARTIRAN LOS PROCESOS
	fd_empleados_on=mmap(NULL,256,PROT_READ|PROT_WRITE,MAP_ANONYMOUS|MAP_SHARED,-1,0);
	sem_init(&sem_empleados_on,1,1); //PARA PROTEGER EL ARCHIVO Y QUE SOLO UN PROCESO ENTRE A EDITARLO A LA VEZ
	//FIN INICIALIZACION

	int pid=0; //para guardar el id del proceso

	struct sockaddr_in direccionCliente; //new
  unsigned int tam_direccion; //new

	/*
  int cliente = accept(servidor,(struct sockaddr *)&direccionCliente,&tam_direccion);
  struct in_addr clientIp = direccionCliente.sin_addr;
  char ipStr[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &clientIp, ipStr, INET_ADDRSTRLEN);
	*/
	//new, antes connfd = accept(fd,NULL, 0))
	while ((connfd = accept(fd,(struct sockaddr *)&direccionCliente,&tam_direccion)) > 0 ){

		struct in_addr clientIp = direccionCliente.sin_addr; //new
		char ipStr[INET_ADDRSTRLEN]; //new
	  inet_ntop(AF_INET, &clientIp, ipStr, INET_ADDRSTRLEN);
		printf("---> confd->%d ip->%s\n",connfd,ipStr); //connfd es el fd de la conexion, por este fd tiene que
		pid=fork();//responder el cliente
		if(pid==0){
			if(menu((void*) (intptr_t) connfd, ipStr,fd_empleados_on, sem_empleados_on)==0){
				printf("Cerramos conexion\n");
				close(connfd); //cerramos el fd de la conexion
			}
		}
	}
	kill(pid,SIGTERM); // matamos el proceso terminado

	return 0;
}
