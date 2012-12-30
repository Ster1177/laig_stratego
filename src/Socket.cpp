/*
 * Socket.cpp
 *
 *  Created on: Dec 28, 2012
 *      Author: ster
 */

#include "Socket.h"
#include <sstream>

Socket::Socket() {

	board = vector< vector<string> >();
	this->length = sizeof (struct sockaddr_in);
	this->createSocket();
//	this->createStaticBoard();
	string testB = "[['X','X','X','X','X','PB','X','X','X','X'],['X','X','X','X','X','X','X','X','X','X'],['X','X','X','X','X','X','PB','X','X','X'],['X','X','X','X','X','P6','X','X','X','X'],['_','_','L','L','_','_','L','L','_','_'],['_','_','L','L','_','_','L','L','_','_'],['7','B','5','2','9','1','9','8','9','B'],['B','7','9','S','4','5','8','5','3','9'],['7','B','4','8','6','4','3','8','7','6'],['B','F','B','5','9','6','6','9','9','8']].";
	getBoard(testB);
	this->printBoardVec();
	this->moverPeca(0,6,0,5);
	this->closeSocket();
	//	this->getBoard("[[a,b,c],"
	//			"[a,b,t],"
	//			"[a,b,t]]");
	//	this->printBoardVec();



//	cout << "\n\nBoard to string: ";
//	cout << boardToString() << endl;

}

Socket::~Socket() {

}

void Socket::createSocket() {
	/* Create socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("Opening stream socket");
		exit(1);
	}
	printf("Opened socket\n");
	/* Connect socket using server name indicated in the command line */
	server.sin_family = AF_INET;
	hp = gethostbyname("ster-K55VM");
	if (hp == NULL)
	{
		perror("Trying to get host by name");
		exit(2);
	}
	printf("Got host by name\n");

	memcpy((char *)&server.sin_addr, (char *)hp->h_addr, hp->h_length);
	//server.sin_port = htons(atoi(argv[2]));
	server.sin_port = ntohs(PORT);	/*port number */

	if (connect(sock, (struct sockaddr *)&server, sizeof server) < 0)
	{
		perror("Connecting stream socket");
		exit(1);
	}
	printf("Connected stream socket\n");


}


vector< vector<string> > Socket::getBoard(string buf) {
	unsigned int i = 1;
	int plica_counter = 0;
	string temp;

	cout << "Printing board\n";

	while(i < buf.length()) {
		switch(buf[i]) {
		case '[':
			board.push_back(vector<string>());
			break;

		case ']':
		case ',':
		case '.':
			break;

		case'\'':
			if( plica_counter == 0) {
				plica_counter++;
				temp.clear();
			} else {
				plica_counter--;
				board.back().push_back( temp );
			}
			break;

		default:
			temp += buf[i];
			break;
		}

		i++;
	}


	return this->board;
}

void Socket::printBoardVec() {

	for(unsigned int j = 0; j < board.size(); j++){
		for(unsigned int k = 0; k < board.front().size(); k++){
			cout << board[j][k] << " " ;
		}
		cout << endl;
	}
}

void Socket::closeSocket() {
	char res[20];
	write(sock,"quit.\n",6);
	memset(res,0,20);
	read(sock,res,20);
	cout << res << endl;
	close(sock);
}


char * Socket::moverPeca( int xfrom, int yfrom, int xto, int yto){
	stringstream temp;
	temp << "mover_pecaP1(";
	temp << boardToString();
	temp << ", BoardF, ";
	temp << xfrom << ", " << yfrom;
	temp << ", " << xto << ", " << yto << ").\n";

	string request = temp.str();

	char * res = new char[BUFS];
	write(sock,request.c_str(),request.length());
	memset(res,0,BUFS);
	read(sock,res,BUFS);
	cout << res << endl;
	return res;
}

char * Socket::createBoard() {
	char * res = new char[BUFS];
	write(sock,"create_board(X).\n",17);
	memset(res,0,BUFS);
	read(sock,res,BUFS);
	cout << res << endl;
	return res;
}


char * Socket::createStaticBoard() {
	char * res = new char[BUFS];
	write(sock,"create_Staticboard(X).\n",23);
	memset(res,0,BUFS);
	read(sock,res,BUFS);
	cout << res << endl;
	return res;
}

string Socket::boardToString(){
	string str;

	str ='[';

	for( int i = 0; i < board.size() ; i++){

		if(i>0)
			str += ',';

		str += '[';

		for( int j = 0; j < board[i].size() ; j++ ){
			if(j>0)
				str += ',';
			str += "'";
			str += board[i][j];
			str += "'";

		}

		str += ']';
	}

	str +=']';
	return str;
}

