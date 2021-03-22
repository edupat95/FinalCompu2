#ifndef AUTHENTICATEH
#define AUTHENTICATEH
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "archivoDao.h"
#include "menu.h"

char *authenticate(int fd);

char *authenticate_ok(char *usr, char *pass, int fd);

#endif
