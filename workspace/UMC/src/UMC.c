#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <commons/config.h>

void crearServer(struct sockaddr_in* direccionServidor, int puerto) {
	direccionServidor->sin_family = AF_INET;
	direccionServidor->sin_addr.s_addr = INADDR_ANY;
	direccionServidor->sin_port = htons(puerto);
}

void crearCliente(struct sockaddr_in* direccionServidor, int puerto, char* ip) {

	direccionServidor->sin_family = AF_INET;
	direccionServidor->sin_addr.s_addr = inet_addr(ip);
	direccionServidor->sin_port = htons(puerto);
}

int main(void) {
	char* buffer = malloc(50);
	struct sockaddr_in unServer;

	struct sockaddr_in direccionServidor;
	t_config *umc = config_create("/home/utnso/tp-2016-1c-SO-2016-1C/umc/config");
	crearServer(&direccionServidor, config_get_int_value(umc,"PUERTO_UMC"));

	int servidor = socket(AF_INET, SOCK_STREAM, 0);

	int activado = 1;
	setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));

	if (bind(servidor, (void*) &direccionServidor, sizeof(direccionServidor))
			!= 0) {
		perror("Falló el bind");
		return 1;
	}

	printf("Estoy escuchando\n");
	listen(servidor, 100);

	//------------------------------

	struct sockaddr_in direccionCliente;
	unsigned int tamanioDireccion = sizeof(struct sockaddr_in);
	int cliente = accept(servidor, (void*) &direccionCliente,
			&tamanioDireccion);

	printf("Recibí una conexión del CPU de %d bytes \n", cliente);

	int bytesRecibidos = recv(cliente, buffer, 1000, 0);
	if (bytesRecibidos <= 0) {
		perror("Se ha perdido contacto con la CPU");
		return 1;
	} else {
		buffer[bytesRecibidos] = '\0';
		printf("Recibi de la CPU el mensaje: %s\n", buffer);
	}
	printf("Esperando que se conecte el swap\n");
	crearCliente(&unServer, 8200, "127.0.0.1");

	int umc_cliente = socket(AF_INET, SOCK_STREAM, 0);

	while (connect(umc_cliente, (void*) &unServer, sizeof(unServer)) != 0)
		;

	send(umc_cliente, buffer, strlen(buffer), 0);
	printf("Mensaje enviado\n");
	free(buffer);
	while (1)
		;
	//------------------------------------------------------------

	return 0;
}

