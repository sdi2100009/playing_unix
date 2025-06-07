// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>


#define PORT 5555
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <server_ip>\n", argv[0]);
        return 1;
    }

    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation error");
        return 1;
    }

    // Server address setup
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    //Convert IP from text to binary
     if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
         printf("Invalid address/Address not supported\n");
        return 1;
    }

    // struct hostent *he = gethostbyname(argv[1]);
    // if (he == NULL) {
    //     herror("gethostbyname");
    //     return 1;
    // }
    //memcpy(&serv_addr.sin_addr, he->h_addr_list[0], he->h_length);

    // Connect
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return 1;
    }

    // Send message
    char *msg = "Hello from client!";
    send(sock, msg, strlen(msg), 0);

    // Receive reply
    read(sock, buffer, BUFFER_SIZE);
    printf("Client received: %s\n", buffer);

    close(sock);
    return 0;
}
