#include "CargarEmpleado.h"

void cargarEmpleado(char *fd_empleados_on,sem_t sem_empleados_on){
  printf("Hola cargarEempleado\n");
  int puerto = asignarPuerto(fd_empleados_on,sem_empleados_on);

  //Aca deberiamos levantar el socket del empleado


}

int asignarPuerto(char *fd_empleados_on,sem_t sem_empleados_on){
  char *vacio="";

  int puerto=0;

  if(!strcmp(fd_empleados_on,vacio)){

    printf("Nigun empleado usando puertos\n");
    puerto = 22001;
    printf("Deberiamos usar el puerto -> 22001\n");
    //VAMOS A TRABAJAR CON LA MEMORIA POR ENDE TENEMOS QUE USAR SEMAFOROS PARA QUE LOS EMPLEADOS NO ENTREN A LA MISMA VEZ
    //sprintf(aux_puerto, "%d", puerto); //convertimos el puerto a char para poder cargarlo en la memoria
    sem_wait(&sem_empleados_on); // Editamos fd_empleados_on
    strncpy(fd_empleados_on,"22001",5);
    //strncpy(fd_empleados_on,aux_puerto,strlen(aux_puerto)); //escribimos en la memoria el primer puerto "22001"
    strncat(fd_empleados_on,"\n",1); //agregamos un enter para que el nuevo puerto se escriba abajo
    sem_post(&sem_empleados_on); // Liberamos fd_empleados_on
    //TERMINAMOS DE TRABAJAR CON LA MEMORIA
  } else {
    char *puerto_string=NULL;
    puerto_string=malloc(64);

    printf("Archivo no vacio, hay puertos ocupados\n");
    printf("Deberiamos analizar la memoria y ver que puerto podemos utilizar\n");
    printf("Imprimimos contenido de fd_empleados_on: \n+++\n%s \n+++\n",fd_empleados_on);

    //----------------------------------------------------
    puerto=22001;
    sem_wait(&sem_empleados_on); // Editamos fd_empleados_on
    while(identificarPuerto(fd_empleados_on,sem_empleados_on,puerto)==1){
      puerto++;
    }

    sprintf(puerto_string,"%d",puerto);
    strncat(fd_empleados_on,puerto_string,strlen(puerto_string));
    strncat(fd_empleados_on,"\n",2);
    sem_post(&sem_empleados_on); // Liberamos fd_empleados_on
  }
  printf("El puerto asignado fue -> %d\n",puerto);
  return puerto;
}

int identificarPuerto(char *fd_empleados_on,sem_t sem_empleados_on, int puerto){
  char letra;
  char *aux_puerto=NULL;
  aux_puerto=malloc(sizeof(char));

  while (*fd_empleados_on != '\0') {
    //printf("->%c",*p);
    letra=*fd_empleados_on;
    printf("->%c",letra);
    if (*fd_empleados_on == '\n') {
      printf("\nvalor formado en aux_puerto -> +%s+\n",aux_puerto);
      printf("\nSalto de linea encontrado\n");
      if(atoi(aux_puerto)==puerto){
        printf("\nPUERO EN USO!!\n");
        return 1;
      }
      strncpy(aux_puerto,"",1);
    } else {
      strncat(aux_puerto,&letra,1);
    }
    fd_empleados_on++;
  }
  //----------------------------------------------------
  printf("Archivo-> cargarEmpleado fc->identificarPuerto msj-> El puerto %d no esta ocupado\n",puerto);

  return 0;
}
