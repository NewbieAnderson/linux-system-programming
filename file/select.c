#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_WATING_QUEUE 5
#define MAX_SOCKET_SIZE 5

int main(void)
{
	int server_sockets[MAX_SOCKET_SIZE] = { 0, };
    int client_sockets[MAX_SOCKET_SIZE] = { 0, };
    int ports[MAX_SOCKET_SIZE] = { 1234, 2345, 3456, 4567, 5678 }; /* test command : telnet 127.0.0.1 1234 */
    int alive = MAX_SOCKET_SIZE;
    int max_fd_value = -1;
    int ret;
    int i;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len;
    fd_set server_fdset;
    struct timeval tv;
    char write_buf[256] = { 0, };
    char ip[] = "127.0.0.1";
    FD_ZERO(&server_fdset);
    for (i = 0; i < MAX_SOCKET_SIZE; ++i) {
        server_sockets[i] = socket(PF_INET, SOCK_STREAM, 0);
        if (server_sockets[i] == -1) {
            perror("failed to initialize socket ");
            exit(1);
        }
        if (server_sockets[i] > max_fd_value)
            max_fd_value = server_sockets[i];
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        server_addr.sin_port = htons(ports[i]);
        if (bind(server_sockets[i], (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
            perror("failed to bind socket ");
            exit(1);
        }
        if (listen(server_sockets[i], MAX_WATING_QUEUE) == -1) {
            perror("failed to listen socket ");
            exit(1);
        }
        FD_SET(server_sockets[i], &server_fdset);
    }
    while (alive > 0) {
        fd_set temp_fdset = server_fdset;
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        ret = select(max_fd_value + 1, &temp_fdset, NULL, NULL, &tv);
        if (ret == -1) {
            perror("failed to select ");
            break;
        }
        printf("%d sockets are awaken, %d sockets are alive.\n", ret, alive);
        for (i = 0; i < MAX_SOCKET_SIZE; ++i) {
            if (!FD_ISSET(server_sockets[i], &temp_fdset))
                continue;
            client_addr_len = sizeof(client_addr);
            client_sockets[i] = accept(server_sockets[i], (struct sockaddr *)&client_addr, &client_addr_len);
            if (client_sockets[i] == -1) {
                perror("failed to accept socket ");
                exit(1);
            }
            printf("server has been connected!\n"
                    "fd : %d, port : %d\n", server_sockets[i], ports[i]);
            sprintf(write_buf, "hello from server %d!\n", ports[i]);
            if (send(client_sockets[i], write_buf, strlen(write_buf), 0) == -1)
                perror("failed to send data to client ");
            if (close(client_sockets[i]) == -1)
                perror("failed to close server\'s socket ");
            FD_CLR(server_sockets[i], &server_fdset);
            server_sockets[i] = 0;
            client_sockets[i] = 0;
            --alive;
        }
        max_fd_value = 0;
        for (i = 0; i < MAX_SOCKET_SIZE; ++i) {
            if (server_sockets[i] > 0 && server_sockets[i] > max_fd_value)
                max_fd_value = server_sockets[i];
        }
    }
    return 0;
}