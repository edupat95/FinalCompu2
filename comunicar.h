#ifndef COMUNICARH
#define COMUNICARH
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void comunicar(int fd, char *op, char *fd_empleados_on);

#endif
