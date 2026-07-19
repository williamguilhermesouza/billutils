#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void checkerr(int status, char *callname) {
  if (status == -1) {
    perror(callname);
    exit(-1);
  }
}

int main(int argc, char *argv[]) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if (argc != 3) {
      printf("Wrong args count. Usage: ./tcpclient [serveraddress] [server_port]\n");
      return 1;
  }
  char *server_address = argv[argc-2];
  char *server_port = argv[argc-1];

  int status;
  struct addrinfo *servinfo;
  if ((status = getaddrinfo(server_address, server_port, &hints, &servinfo)) != 0) {
    fprintf(stderr, "gai error: %s\n", gai_strerror(status));
    return 1;
  }

  // verify servinfo first

  int sockfd =
      socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

  printf("Connecting to: %s:%s\n", server_address, server_port);
  status = connect(sockfd, (struct sockaddr *)servinfo->ai_addr,
                   servinfo->ai_addrlen);
  checkerr(status, "connect");
  printf("Connected!\n");

  char rcv_buff[100];
  char send_buff[100];
  int bytes_rcv;
  int bytes_sent;
  do {
    memset(&send_buff, 0, sizeof(send_buff));
    memset(&rcv_buff, 0, sizeof(rcv_buff));

    // send request
    printf("[client]: ");
    scanf("%s", send_buff);

    bytes_sent = send(sockfd, &send_buff, strlen(send_buff), 0);
    checkerr(bytes_sent, "send");

    // wait for response
    bytes_rcv = recv(sockfd, &rcv_buff, sizeof rcv_buff, 0);
    checkerr(bytes_rcv, "recv");
    printf("[server]: %s\n", rcv_buff);

  } while (bytes_rcv != 0);

  close(sockfd);
  freeaddrinfo(servinfo);
  printf("Connection closed");
  return 0;
}
