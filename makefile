compile: server client pipe fserver
clean:
	rm fserver
	rm server
	rm client
	rm pipe_networking
	rm -f *~
fserver:
	gcc fserver.c -o  fserver
server:
	gcc server.c -o server
client:
	gcc client.c -o client
pipe:
	gcc pipe_networking.c -o pipe_networking
