makefile:

clean: clay_ftp_server clay_ftp_client
	rm clay_ftp_server
	rm clay_ftp_client

build: clay_ftp_server.c clay_ftp_client.c
	gcc clay_ftp_server.c -o clay_ftp_server
	gcc clay_ftp_client.c -o clay_ftp_client
