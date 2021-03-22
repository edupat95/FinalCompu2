
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
	procrem.sin_port = htons(8080);
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

	int pid; //para guardar el id del proceso

	while ((connfd = accept(fd,NULL, 0)) > 0 ){
		printf("---> confd vale %d\n",connfd); //connfd es ek el fd de la conexion, por este fd tiene que
		pid=fork();															//responder el cliente
		if(pid==0){
			menu((void*) (intptr_t) connfd,fd_empleados_on, sem_empleados_on);
		}
	}
	kill(pid,SIGTERM); // matamos el proceso terminado
	close(connfd); //cerramos el fd de la conexion
	return 0;
}
