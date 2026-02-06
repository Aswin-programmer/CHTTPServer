#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "Utils/Allocator.h"
#include "Utils/Utils.h"

#define PORT 10000
#define BUFFER_SIZE 1024

int main() {
	int a = 0;
	int server_ft;
	int new_socket;

	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buffer[BUFFER_SIZE];

	server_ft = socket(
		AF_INET,
		SOCK_STREAM,
		0);
	if (server_ft == 0) {
		perror("Socket Failed!");
		return -1;
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if (bind(
			server_ft,
			(struct sockaddr *)&address,
			sizeof(address)) < 0) {
		printf("Binding Failed!");
		return -1;
	}

	if (listen(
			server_ft,
			5) < 0) {
		printf("Listening Failed!");
		return -1;
	}

	printf("Server is running on http://localhost:%d\n", PORT);

	new_socket = accept(
		server_ft,
		(struct sockaddr *)&address,
		(socklen_t *)&addrlen);
	if (new_socket < 0) {
		printf("Accept Failed!");
		return -1;
	}

	read(new_socket,
		 buffer,
		 BUFFER_SIZE);

	printf("Client Request:\n%s\n", buffer);

	size_t htmlSize;
	Memory *htmlRead = ReadHTMLFile(
		RESOURCES_PATH
		"/"
		"index.html",
		&htmlSize);

	const char *http_responce =
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html\r\n"
		"Connection: close\r\n"
		"\r\n";

	write(
		new_socket,
		http_responce,
		strlen(http_responce));
	write(
		new_socket,
		htmlRead->ptr,
		htmlSize);

	FreeMemory(htmlRead);

	printf("Response sent to client\n");

	close(new_socket);
	close(server_ft);

	if (!CheckIsAllMemoryFreed()) {
		printf("There is some memeory leak within the program!");
	}

	return 0;
}
