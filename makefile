SERVER = server.c
CLIENT = client.c

CORE = statem.c

all: client server

client: $(CLIENT) $(CORE)
	gcc $(CLIENT) $(CORE) -o client_statem -g

server: $(SERVER) $(CORE)
	gcc $(SERVER) $(CORE) -o server_statem -g
