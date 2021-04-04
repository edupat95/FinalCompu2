#ifndef CARGAREMPLEADOH
#define CARGAREMPLEADOH
#include "AllIncludes.h"

void cargarEmpleado(char *fd_empleados_on, sem_t sem_empleados_on);

int asignarPuerto(char *fd_empleados_on, sem_t sem_empleados_on);

int quitarEmpleado(char *fd_empleados_on, sem_t sem_empleados_on);

int identificarPuerto(char *fd_empleados_on, sem_t sem_empleados_on, int puerto);
#endif
