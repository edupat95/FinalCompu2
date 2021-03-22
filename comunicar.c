#include "comunicar.h"

void comunicar(int fd, char *op, char *fd_empleados_on){

	printf("EN comunicar.c \n%s",fd_empleados_on); // el arcivo se puede leer, ahora hay que procesarlo

	if(op[0]=='1'){
		printf("Demandamos un empleado en ventas\n");
	} else if(op[0]=='2'){
		printf("Demandamos un empleado en consultas\n");
	} else if(op[0]=='3'){
		printf("Demandamos un empleado en reclamos\n");
	} else {
		write(1,"ERROR\n",6);
		write(fd,"ERROR\n",6);
	}
}
