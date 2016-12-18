compile: server client fserver
clean:
	rm fserver
	rm server
	rm client
	rm pipe_networking
	rm -f *~
fserver:
	gcc fserver.c pipe_networking.c -o  fserver
server:
	gcc server.c pipe_networking.c -o server
client:
	gcc client.c pipe_networking.c -o client
