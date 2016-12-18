compile: server client
clean:
	rm server
	rm client
	rm -f *~
fserver:
	gcc fserver.c pipe_networking.c -o  fserver
server:
	gcc server.c pipe_networking.c -o server
client:
	gcc client.c pipe_networking.c -o client
