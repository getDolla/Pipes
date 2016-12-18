#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "pipe_networking.h"

int server_handshake(int * from_client) {
  // make the named pipe
  mkfifo("luigi",0644);
  printf("[SERVER] WPK created\n");
  // open (connect) to it
  printf("[SERVER] connection attempt\n");
  *from_client = open("luigi",O_RDONLY);

  //attempt to read
  char buffer[512];//gets client fifo name
  read(*from_client, buffer, sizeof(buffer));
  printf("[SERVER] recieved: %s\n", );

  //remove pipe
  execlp("rm", "rm", "-f", "luigi", NULL);

  //connect to client pipe
  int clientPipe = open(buffer, O_WRONLY);
  printf("[SERVER] connected to client FIFO\n", );

  //write to client
  char * message = "Hello, client!";
  write(clientPipe, message, strlen(message));

  //recieve confirmation of connection
  read(*from_client, buffer, sizeof(buffer));
  printf("[SERVER] recieved: %s\n", buffer);

  return clientPipe;
}

int client_handshake(int * to_server ) {
  // make the named pipe
  char clientPipe[512];
  sprintf(clientPipe, "%d", getpid());
  mkfifo(clientPipe,0644);
  printf("[CLIENT] fifo created created: %s\n", clientPipe );

  // open (connect) to it
  *to_server = open("luigi",O_WRONLY);
  printf("[CLIENT] connected to WKP\n" );

  // write a string literal to it
  write(*to_server, clientPipe, strlen(clientPipe));
  printf("[CLIENT] sent message\n" );

  //connect to server fifo
  int 

  return 0;
}
