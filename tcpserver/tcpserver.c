#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BACKLOG 10

void checkerr(int status, char *callname) {
  if (status == -1) {
    perror(callname);
    exit(-1);
  }
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Wrong args count. Usage: ./tcpserver [listen_port]\n");
    return 1;
  }
  char *listen_port = argv[argc - 1];

  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  int status;
  struct addrinfo *servinfo;
  if ((status = getaddrinfo(NULL, listen_port, &hints, &servinfo)) != 0) {
    fprintf(stderr, "gai error: %s\n", gai_strerror(status));
    return 1;
  }
  // TODO verify servinfo first

  int sockfd;
  sockfd =
      socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
  status = bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
  checkerr(status, "bind");

  char ipstr[INET6_ADDRSTRLEN];
  struct sockaddr_in *ipv4 = (struct sockaddr_in *)servinfo->ai_addr;
  void *addr = &(ipv4->sin_addr);
  inet_ntop(servinfo->ai_family, addr, ipstr, sizeof(ipstr));
  printf("Now listening on: %s:%s\n", ipstr, listen_port);

  status = listen(sockfd, BACKLOG);
  checkerr(status, "listen");

  socklen_t addr_size;
  struct sockaddr_storage their_addr;
  addr_size = sizeof their_addr;
  int new_fd;
  new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
  checkerr(new_fd, "accept");

  char client_ipstr[INET6_ADDRSTRLEN];
  struct sockaddr_in *client_ipv4 = (struct sockaddr_in *)&their_addr;
  void *client_addr = &(client_ipv4->sin_addr);
  inet_ntop(servinfo->ai_family, client_addr, client_ipstr,
            sizeof(client_ipstr));
  printf("Accepted connection to: %s:%s\n", client_ipstr, listen_port);

  char rcv_buff[100];
  char send_buff[100];
  int bytes_rcv;
  int bytes_sent;
  do {
    memset(&rcv_buff, 0, sizeof(rcv_buff));
    memset(&send_buff, 0, sizeof(send_buff));

    // receiving requests
    bytes_rcv = recv(new_fd, &rcv_buff, sizeof rcv_buff, 0);
    checkerr(bytes_rcv, "recv");
    printf("[client]: %s\n", rcv_buff);

    // send response
    printf("[server]: ");
    scanf("%s", send_buff);

    bytes_sent = send(new_fd, &send_buff, strlen(send_buff), 0);
    checkerr(bytes_sent, "send");

  } while (bytes_rcv != 0);

  close(new_fd);
  close(sockfd);
  freeaddrinfo(servinfo);
  printf("Connection closed");
  return 0;
}
