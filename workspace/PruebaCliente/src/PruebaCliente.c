#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

typedef enum{ID_NUCLEO,ID_CPU,ID_CONSOLA,ID_UMC,ID_SWAP}identificadores;
typedef struct{
	int PID;
	int orden;  //0=INICIAR, 1=LEER, 2=ESCRIBIR, 3=FINALIZAR
	int cantPaginas;
	int nroPagina;
	char* contenido;
}OrdenProceso;

int sendAll(int socket, void *buffer, size_t length) {
	char *ptr = (char*) buffer;
	int j=5;
	while (j > 0) {
		int i = send(socket, buffer, length,0);
		if (i < 1) return 0;
			buffer+= sizeof(i);
			j--;
		}
	return 1;
}

int main(void) {
	void* buffer = malloc(25);
	struct sockaddr_in direccionServidor;
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_addr.s_addr = inet_addr("127.0.0.1");
	direccionServidor.sin_port = htons(8200);

	int cliente = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(cliente, (void*) &direccionServidor, sizeof(direccionServidor)) != 0) {
		perror("No se pudo conectannnr");
		return 1;
	}
	uint8_t id=ID_UMC;
	memcpy(buffer,(void*)&id,sizeof(uint8_t));
	send(cliente,buffer,sizeof(uint8_t),0);
	OrdenProceso* micaMiau=malloc(sizeof(OrdenProceso));
	micaMiau->PID=1;
	micaMiau->orden=0;
	micaMiau->cantPaginas=3;
	micaMiau->nroPagina=1;
	char* hola="Hola como estas loco?";
	micaMiau->contenido=hola;
	void* BUFFER=malloc(37);
	int tamanio=0;

	memcpy(BUFFER,&micaMiau->PID,sizeof(int));
	tamanio+=sizeof(int);
	printf("%d\n",tamanio);
	memcpy(BUFFER+tamanio,&micaMiau->orden,sizeof(int));
	tamanio+=sizeof(int);
	printf("%d\n",tamanio);
	memcpy(BUFFER+tamanio,&micaMiau->cantPaginas,sizeof(int));
	tamanio+=sizeof(int);
	printf("%d\n",tamanio);
	memcpy(BUFFER+tamanio,&micaMiau->nroPagina,sizeof(int));
	tamanio+=sizeof(int);
	printf("%d\n",tamanio);
	memcpy(BUFFER+tamanio,&micaMiau->contenido,strlen(hola));
	tamanio+=strlen(hola);


	printf("%d\n",sizeof(OrdenProceso));
	printf("%d\n",tamanio);
	send(cliente,&tamanio,sizeof(int),0);
	send(cliente,BUFFER,tamanio,0);

	//strcpy(micaMiau->contenido,hola);
	//memcpy((void*)(micaMiau->contenido),(void*)hola,sizeof(strlen(hola)));
	//printf("%s\n",micaMiau->contenido);
	//sendAll(cliente,micaMiau,sizeof(micaMiau));
	//send(cliente,micaMiau,sizeof(micaMiau),0);
		/*uint8_t id=ID_CPU;
		int n=1;
		int tamano=0;
		tamano+=sizeof(uint8_t);
		memcpy(buffer,(void*)n,sizeof(int));
		tamano+=sizeof(int);

		send(cliente, buffer, tamano, 0);*/
		/*int bytes=recv(cliente,buffer,1000,0);
		printf("%d",bytes);
		buffer[bytes]='\0';
		printf("%s",buffer);*/
	while(1);
		free(buffer);
	return 0;
}
