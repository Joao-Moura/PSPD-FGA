CLIENT = tcpc
SERVER = tcps

CFLAGS = -Wall

all : $(CLIENT) $(SERVER)

$(CLIENT) : client.c
	gcc client.c -o $(CLIENT)

$(SERVER) : server.c
	gcc server.c -o $(SERVER)
