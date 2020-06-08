#include <stdint.h>
#include "zerocopyMQ.h"
#include "comun.h"
int create_destroy(const char * cola, char opc){

	int s=obtenerSocket();
	//int i;
	char respuesta[4];
	respuesta[0]='-';respuesta[1]='1';respuesta[2]='\0';
	//int leido;
	char *opcion=(char*)malloc(2*sizeof(char));
	char *sizeof_cola_s=intToString(strlen(cola));
	opcion[0]=opc;opcion[1]='\0';
	ssize_t nwritten;
	struct iovec iov[3];
	iov[0].iov_base=opcion;
	iov[0].iov_len=2;
	iov[1].iov_base=sizeof_cola_s;
	iov[1].iov_len=TAM_LONG;
	/*
	 AQUI EL TAMANIO VARIABLE DE LA COLA
	*/
	iov[2].iov_base=cola;
	iov[2].iov_len=atoi(sizeof_cola_s)+1;
	/*
	AQUI SOLAMENTE HE ENVIADO UNA TRANSMISION
	*/
	/*
	iov[3].iov_base="0\0";
	iov[3].iov_len=2;
	*/
	while((nwritten=writev(s,iov,3))>0){
		if(read(s,respuesta,sizeof(respuesta))>0){
			close(s);
			return atoi(respuesta);
		}
	}
	return atoi(respuesta);
}
int createMQ(const char *cola) {
	return create_destroy(cola,'c');
}

int destroyMQ(const char *cola){
	return create_destroy(cola,'d');
}
int put(const char *cola, const void *mensaje, uint32_t tam) {

	int s=obtenerSocket();
	char *opcion=(char*)malloc(2*sizeof(char));
	char *sizeof_cola_s=intToString(strlen(cola));
	opcion[0]='p';opcion[1]='\0';
	char respuesta[4];
	respuesta[0]='-';respuesta[1]='1';respuesta[2]='\0';ssize_t nwritten;
	struct iovec iov[5];
	iov[0].iov_base=opcion;
	iov[0].iov_len=2;
	iov[1].iov_base=sizeof_cola_s;
	iov[1].iov_len=TAM_LONG;
	/*
	 AQUI EL TAMANIO VARIABLE DE LA COLA
	*/
	iov[2].iov_base=cola;
	iov[2].iov_len=atoi(sizeof_cola_s)+1;
	/*
	AQUI SOLAMENTE HE ENVIADO UNA TRANSMISION
	*/
	/*
	iov[3].iov_base="0\0";
	iov[3].iov_len=2;
	*/
	char * sizeof_mensaje_s;
	sizeof_mensaje_s=intToString((long)tam);
	iov[3].iov_base=sizeof_mensaje_s;
	iov[3].iov_len=TAM_LONG;
	iov[4].iov_base=mensaje;
	iov[4].iov_len=((int)tam);
	while((nwritten=writev(s,iov,5))>0){
		if(read(s,respuesta,sizeof(respuesta))>0){
			//close(s);
			return atoi(respuesta);
		}
	}
	return atoi(respuesta);
}
int get(const char *cola, void **mensaje, uint32_t *tam, bool blocking) {

	int s=obtenerSocket();
	//int i;
	char sizeof_mensaje_s[TAM_LONG];
	char respuesta[4];
	respuesta[0]='-';respuesta[1]='1';respuesta[2]='\0';
	int leido;
	char *opcion=(char*)malloc(2*sizeof(char));
	char *sizeof_cola_s=intToString(strlen(cola));
	if(blocking){
		opcion[0]='b';
	}else{
		opcion[0]='g';
	}
	opcion[1]='\0';
	ssize_t nwritten;
	struct iovec iov[3];
	iov[0].iov_base=opcion;
	iov[0].iov_len=2;
	iov[1].iov_base=sizeof_cola_s;
	iov[1].iov_len=TAM_LONG;
	/*
	 AQUI EL TAMANIO VARIABLE DE LA COLA
	*/
	iov[2].iov_base=cola;
	iov[2].iov_len=atoi(sizeof_cola_s)+1;
	/*
	AQUI SOLAMENTE HE ENVIADO UNA TRANSMISION
	*/
	/*
	iov[3].iov_base="0\0";
	iov[3].iov_len=2;
	*/
	while((nwritten=writev(s,iov,3))>0){

    	while((leido=read(s, sizeof_mensaje_s,TAM_LONG))>0) {
			if(sizeof_mensaje_s[0]!='\000'){ 
				uint32_t sizeof_mensaje= atoi(sizeof_mensaje_s);
				
				/*
				char mensaje_s[sizeof_mensaje];
				for( i=0;i<sizeof_mensaje;i++){
					mensaje_s[i]='\0';
				}
				*/
				//*mensaje=(  char*)malloc(sizeof_mensaje*sizeof( char));
				*mensaje=( void*)malloc(sizeof_mensaje);
				//printf("sizeof_mensaje : %d\n",sizeof_mensaje);
				if((leido=recv(s,*mensaje,sizeof_mensaje,MSG_WAITALL)>0)){
					//printf("cadena : %s\n",mensaje_s);
					//strcpy(*mensaje,mensaje_s);
					/*
					for(i=0;i<sizeof_mensaje-2;i++){
						((char*)*mensaje)[i]=mensaje_s[i];
					}
					*/
								FILE * archivo;

								system ("rm uwu.txt");
								system ("echo > uwu.txt");
								archivo = fopen ("uwu.txt", "w");
								fprintf (archivo, "%s", (( char*)*mensaje));
								fclose (archivo);
								/* lo de arriba es para probar que se obtiene y
								 se imprime en un fichero con fprintf */
					sprintf(*mensaje,"%s",(char*)*mensaje);
					*tam=sizeof_mensaje-2;
					respuesta[0]='0';respuesta[1]='\0';
					return atoi(respuesta);
					//mensaje=(void **)&mensaje_s;
				}
				if (leido<0) {
					respuesta[0]='-';respuesta[1]='1';respuesta[2]='\0';
						close(s);
						return atoi(respuesta);
				}
			}else{
				//
				respuesta[0]='-';respuesta[1]='1';respuesta[2]='\0';
				close(s);
				return atoi(respuesta);
			}
		}
	}
	return atoi(respuesta);
}
