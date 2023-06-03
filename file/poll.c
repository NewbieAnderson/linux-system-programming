#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_WATING_QUEUE 5
#define MAX_SOCKET_SIZE 5

int main(void)
{
    int server_sockets[MAX_SOCKET_SIZE] = { 0, };
    int client_sockets[MAX_SOCKET_SIZE] = { 0, };
    int ports[MAX_SOCKET_SIZE] = { 1234, 2345, 3456, 4567, 5678 }; /* test command : telnet 127.0.0.1 1234 */
    char write_buf[256] = { 0, };
    struct pollfd poll_fds[MAX_SOCKET_SIZE] = { 0, };
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len;
    int alive = MAX_SOCKET_SIZE;
    int ret;
    int i;
    for (i = 0; i < MAX_SOCKET_SIZE; ++i) {
        server_sockets[i] = socket(PF_INET, SOCK_STREAM, 0);
        if (server_sockets[i] == -1) {
            perror("failed to initialize socket ");
            exit(1);
        }
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
        poll_fds[i].fd = server_sockets[i];
        poll_fds[i].events = POLLIN | POLLPRI | POLLOUT;
    }
    while (alive > 0) {
        ret = poll(poll_fds, MAX_SOCKET_SIZE, 3000);
        if (ret == -1) {
            perror("failed to poll ");
            break;
        }
        printf("%d sockets are awaken, %d sockets are alive.\n", ret, alive);
        for (i = 0; i < MAX_SOCKET_SIZE; ++i) {
            if (!(poll_fds[i].revents & POLLIN) || poll_fds[i].fd <= 0 || server_sockets[i] <= 0)
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
            server_sockets[i] = 0;
            client_sockets[i] = 0;
            poll_fds[i].fd = 0;
            poll_fds[i].events = 0;
            poll_fds[i].revents = 0;
            --alive;
        }
    }
    return 0;
}