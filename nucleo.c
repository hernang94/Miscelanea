
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../Libraries/sockets.h"

/**
void crearServer(struct sockaddr_in* direccionServidor, int puerto) {
	direccionServidor->sin_family = AF_INET;
	direccionServidor->sin_addr.s_addr = INADDR_ANY;
	direccionServidor->sin_port = htons(puerto);
}**/

int main(int argc,char* argv[]) {
	if(argc!=2){
		printf("Cantidad Invalida de argumentos\n");
	return 1;
	}
	char* buffer = malloc(50);
	t_config* cfgNUCLEO= config_create(argv[1]);
	struct sockaddr_in direccionServidorCPU;
	struct sockaddr_in direccionServidorCONSOLA;
	int servidor_CPU=socket(AF_INET, SOCK_STREAM, 0);
	int servidor_CONSOLA=socket(AF_INET, SOCK_STREAM, 0);
	crearServer(&direccionServidorCONSOLA, config_get_int_value(cfgNUCLEO,"PUERTO_CONSOLA"));
	crearServer(&direccionServidorCPU, config_get_int_value(cfgNUCLEO,"PUERTO_CPU") );
	int activado = 1;
	setsockopt(servidor_CONSOLA, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));
	if (bind(servidor_CONSOLA, (void*) &direccionServidorCONSOLA, sizeof(direccionServidorCONSOLA))!= 0) {
		perror("Falló el bind");
		return 1;
	}
	setsockopt(servidor_CPU, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));
	if (bind(servidor_CPU, (void*) &direccionServidorCPU, sizeof(direccionServidorCPU))!= 0) {
		perror("Falló el bind");
		return 1;
	}
	printf("Estoy escuchando\n");
	listen(servidor_CONSOLA, 100);
	//-------------CONSOLA--------------

	struct sockaddr_in direccionCliente;
	unsigned int tamanioDireccion=sizeof(struct sockaddr_in);
	int cliente = accept(servidor_CONSOLA, (void*) &direccionCliente, &tamanioDireccion);
	printf("Recibí una conexión en %d!!\n", cliente);
	send(cliente, "Hola Bienvenido al Nucleo!", 27, 0);

	int bytesRecibidos = recv(cliente, buffer, 50, 0);
	if (bytesRecibidos <= 0) {
		perror("El cliente se desconectó o tuvo un problema.");
		return 1;
	}else{
		buffer[bytesRecibidos] = '\0';
		printf("Recibi el programa Ansisop: %s . Lo envío a la CPU...\n", buffer);
	}


	//-------------CPU-----------------


	printf("Espero a la CPU\n");
	listen(servidor_CPU,100);
	struct sockaddr_in direccionCliente2;
	unsigned int tamanioDireccion2=sizeof(struct sockaddr_in);
	int cliente2 = accept(servidor_CPU, (void*) &direccionCliente2, &tamanioDireccion2);
	printf("Recibí una conexión en %d!!\n", cliente2);
	send(cliente2, buffer, 50, 0);
	while(1);
	free(buffer);
	return 0;
}

