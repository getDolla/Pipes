#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int server_handshake(int * from_client) {
  // make the named pipe
  mkfifo("luigi",0644);
  printf("[SERVER] WPK created\n");
  // open (connect) to it
  int fd = open("luigi",O_WRONLY);
  printf("%s\n", );
  // write a string literal to it
  char buff[512];
  read(fd, &buff, sizeof(buff));
  printf("[SERVER] re%s\n", );

  return 0;
}

int client_handshake(int * to_client) {
  // make the named pipe
  mkfifo("peach",0644);
  // open (connect) to it
  int fd = open("peach",O_WRONLY);
  printf("[CLIENT] fifo created created: %d\n", getpid() );
  // write a string literal to it
  write(fd,"hello\n",13);

  return 0;
}
