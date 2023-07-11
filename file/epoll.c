#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>

#define MAX_WATING_QUEUE 5
#define MAX_SOCKET_SIZE 5

struct server_info {
    int fd;
    int port;
};

int main(void)
{
    int server_sockets[MAX_SOCKET_SIZE] = { 0, };
    int client_socket = 0;
    int ports[MAX_SOCKET_SIZE] = { 1234, 2345, 3456, 4567, 5678 }; /* test command : telnet 127.0.0.1 1234 */
    struct server_info server_infos[MAX_SOCKET_SIZE] = { 0, };
    struct server_info *server_info_ptr = NULL;
    char write_buf[256] = { 0, };
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    struct epoll_event *events = NULL;
    struct epoll_event event = { 0, };
    socklen_t client_addr_len;
    int epfd;
    int alive = MAX_SOCKET_SIZE;
    int ret;
    int i;
    epfd = epoll_create1(0);
    if (epfd == -1) {
        perror("failed to create epoll instance ");
        exit(1);
    }
    events = malloc(sizeof(struct epoll_event) * MAX_SOCKET_SIZE);
    if (events == NULL) {
        perror("failed to allocate epoll event pointer ");
        exit(1);
    }
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
        server_infos[i].fd = server_sockets[i];
        server_infos[i].port = ports[i];
        event.data.ptr = &server_infos[i];
        event.events = EPOLLIN | EPOLLOUT;
        ret = epoll_ctl(epfd, EPOLL_CTL_ADD, server_sockets[i], &event);
    }
    while (alive > 0) {
        ret = epoll_wait(epfd, events, MAX_SOCKET_SIZE, 3000);
        if (ret == -1) {
            perror("failed to epoll_wait() ");
            break;
        }
        printf("%d sockets are awaken, %d sockets are alive.\n", ret, alive);
        for (i = 0; i < ret; ++i) {
            server_info_ptr = ((struct server_info *)events[i].data.ptr);
            client_addr_len = sizeof(client_addr);
            client_socket = accept(server_info_ptr->fd, (struct sockaddr *)&client_addr, &client_addr_len);
            if (client_socket == -1) {
                perror("failed to accept socket ");
                break;
            }
            printf("server has been connected!\n"
                   "fd : %d, port : %d\n",
                   server_info_ptr->fd, server_info_ptr->port);
            sprintf(write_buf, "hello from server %d!\n", server_info_ptr->port);
            if (send(client_socket, write_buf, strlen(write_buf), 0) == -1)
                perror("failed to send data to client ");
            if (close(client_socket) == -1)
                perror("failed to close server\'s socket ");
            client_socket = 0;
            if (epoll_ctl(epfd, EPOLL_CTL_DEL, server_info_ptr->fd, NULL) == -1)
                perror("failed to epoll_ctl() ");
            --alive;
        }
    }
    return 0;
}