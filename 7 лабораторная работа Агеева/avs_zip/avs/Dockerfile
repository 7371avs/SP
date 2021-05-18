FROM debian

WORKDIR /lab

COPY tcp/server_tcp.c udp/server_udp.c /lab/

RUN apt update;                               \
	apt install gcc -y;                       

CMD gcc server_tcp.c -lpthread -o server_tcp;     \
	gcc server_udp.c -lpthread -o server_udp;     \
	/bin/bash

