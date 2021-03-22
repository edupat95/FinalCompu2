CC = gcc
CFLAGS = -lrt -g -Wall
LDLIBS = -pthread
TARGETS = servidor
all: $(TARGETS)
#tp2: utils.c gestion_argumentos.c gestion_partes.c gestion_hijos.c
servidor	: menu.c servidor.c authenticate.c archivoDao.c comunicar.c menuCliente.c cargarEmpleado.c
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $^ -lrt
clean:
	$(RM) $(TARGETS) *.o *~ *.txt
