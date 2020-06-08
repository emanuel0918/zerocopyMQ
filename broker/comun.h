#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <sys/uio.h>
#define TAM_LONG 10
#define TAM_PAQUETE 256
int obtenerSocket();
char * scan();
char* subString (const char* input, int offset, int len, char* dest);
int stringToInt(char * s);
char * intToString(long n);
char * reverseString(char *s,int l);
char rand_char();

