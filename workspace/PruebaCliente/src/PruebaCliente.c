#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
typedef enum{ID_NUCLEO,ID_CPU,ID_CONSOLA,ID_UMC,ID_SWAP}identificadores;
int main(void) {
	void* buffer = malloc(25);
	struct sockaddr_in direccionServidor;
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_addr.s_addr = inet_addr("127.0.0.1");
	direccionServidor.sin_port = htons(8100);

	int cliente = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(cliente, (void*) &direccionServidor, sizeof(direccionServidor)) != 0) {
		perror("No se pudo conectar");
		return 1;
	}
		/*uint8_t id=ID_CPU;
		int n=1;
		int tamano=0;
		memcpy(buffer,(void*)&id,sizeof(uint8_t));
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
