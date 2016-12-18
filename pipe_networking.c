#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include "pipe_networking.h"

int server_handshake(int * from_client) {
  // make the named pipe
  mkfifo("luigi",0644);
  printf("[SERVER] WPK created\n");

  // open (connect) to it
  printf("[SERVER] connection attempt\n");
  *from_client = open("luigi",O_RDONLY);

  //attempt to read
  char buffer[MESSAGE_BUFFER_SIZE] = { 0 };//gets client fifo name
  read(*from_client, buffer, sizeof(buffer));
  printf("[SERVER] recieved: %s\n", buffer);

  //remove pipe
  execlp("rm", "rm", "-f", "luigi", NULL);

  //connect to client pipe
  int clientPipe = open(buffer, O_WRONLY);
  printf("[SERVER] connected to client FIFO\n");

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
  char clientPipe[512]= { 0 };
  sprintf(clientPipe, "%d", getpid());
  mkfifo(clientPipe,0644);
  printf("[CLIENT] fifo created created: %s\n", clientPipe );

  // open (connect) to it
  *to_server = open("luigi",O_WRONLY);
  printf("[CLIENT] connected to WKP\n" );

  // write a string literal to it
  write(*to_server, clientPipe, strlen(clientPipe));
  printf("[CLIENT] sent message\n" );

  //checks connection to server fifo
  int serverFD = open(clientPipe, O_RDONLY);
  char message[MESSAGE_BUFFER_SIZE] = { 0 };
  read(serverFD, message, sizeof(message));
  printf("[CLIENT] recieved: %s\n",  message);

  //remove pipe
  execlp("rm", "rm", "-f", clientPipe, NULL);

  //write confirmation message to server
  strcpy(message, "Word, nice to meet you too!");
  write(*to_server, message, strlen(message));
  printf("[CLIENT] sent message\n" );

  return serverFD;
}
