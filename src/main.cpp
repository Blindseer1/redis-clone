#include <arpa/inet.h>
#include <cstdio>
#include <fcntl.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/epoll.h>

#define MAX_EVENTS 64

int main(int argc, char **argv) {
  // Flush after every std::cout / std::cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    std::cerr << "Failed to create server socket\n";
    return 1;
  }

  int reuse = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) <
      0) {
    std::cerr << "setsockopt failed\n";
    return 1;
  }

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(6379);

  int flags = fcntl(server_fd, F_GETFL);
  if(flags<0){
    std::cerr<<"flag server err";
    return 1;
  }
  int s=fcntl(server_fd, F_SETFL,flags | O_NONBLOCK);
  if(flags<0){
    std::cerr<<"set non blocking server err";
    return 1;
  }


  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) !=
      0) {
    std::cerr << "Failed to bind to port 6379\n";
    return 1;
  }

  int connection_backlog = 5;
  if (listen(server_fd, connection_backlog) != 0) {
    std::cerr << "listen failed\n";
    return 1;
  }

  struct sockaddr_in client_addr;
  int client_addr_len = sizeof(client_addr);
  std::cout << "Waiting for a client to connect...\n";

  std::cout << "Logs from your program will appear here!\n";

  const char *response = "+PONG\r\n";
   char buf[1024];
  
  int efd = epoll_create1(0);
  if(efd<0){
    std::cerr << "listen failed\n";
    return 1;
  }

  struct epoll_event ev, events[MAX_EVENTS];
  ev.events=EPOLLIN;
  ev.data.fd=server_fd;

  if(epoll_ctl(efd,EPOLL_CTL_ADD,server_fd,&ev)<0){
    std::cerr<<"ctl_add error";
    return 1;
  }

  while(true){
    int nfds=epoll_wait(efd, events, MAX_EVENTS, -1);
    if (nfds<0){
      std::cerr<<"wait err";
      return 1;
    }
    
    for (int i=0;i<nfds;i++){
      if (events[i].data.fd == server_fd){
           int client=accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len);
      if(client<0){
          std::cerr<<"client error";
          return 1;
        }

      int flags = fcntl(client, F_GETFL);
      if(flags<0){
        std::cerr<<"flag client err";
        return 1;
      }
      int s=fcntl(client, F_SETFL,flags | O_NONBLOCK);
      if(flags<0){
        std::cerr<<"set non blocking client err";
        return 1;
      }
      ev.events=EPOLLIN;
      ev.data.fd = client;
      if(epoll_ctl(efd, EPOLL_CTL_ADD, client, &ev)<0){
          std::cerr<<"error adding client fd";
          return 1;
        }



      }
      else {
          int client=events[i].data.fd;
          int r = recv(client,buf,BUFSIZ,0);
          if(r<=0){
            epoll_ctl(efd, EPOLL_CTL_DEL, client, &ev);
            close(client);
        }
          else {
           send(client,response,strlen(response),0);
          }

        }


    }


  }

  std::cout << "Client connected\n";
  close(server_fd);

}
