/*
 * Socket.h
 *
 *  Created on: Dec 28, 2012
 *      Author: ster
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>	// for gethostname()..
#include <string.h>	// for memcpy()...
#include <ctype.h>	// for tolower()...
#include <stdlib.h>	// for exit()...
#include <fcntl.h>	// for fcntl()...
#include <errno.h>	// for errno...
#include <iostream>
#include <vector>


using namespace std;

#define BUFS	1024
#define NAMS	64
#define IPADDRESS "127.0.0.1"
#define PORT 60070

class Socket {
public:
	char nserver[NAMS];
	int sock;
	struct sockaddr_in server, client;
	unsigned int length;	//unsigned int length = sizeof (struct sockaddr_in);
	int msgsock;
	char buf[BUFS];
	char bufRead[BUFS];
	char bufReply[BUFS];
	int nread;
	struct hostent *hp;

	//Read socket
	int sockRead;
	vector< vector<string> > board;

	Socket();
	void createSocket();
	void closeSocket();
	char * createBoard();
	char * createStaticBoard();
	void printBoardVec();
	char * moverPeca( int xfrom, int yfrom, int xto, int yto);
	string boardToString();
	vector< vector<string> > getBoard(string buf);
	virtual ~Socket();
};

#endif /* SOCKET_H_ */
