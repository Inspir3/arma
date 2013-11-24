/*
 * <author>Andice Rupen</author>
 * <email>andice.rupen@gmail.com</email>
 * <date>2013-11-24</date>
 * <summary>A minimal library to send string over tcp/ip</summary>
 */

#include "Tcp.h"

/*
 * Constructor
 */
Tcp::Tcp(){
	this->connectSocket = INVALID_SOCKET;
}

/*
 * Open connection
 */
int Tcp::open(char *Addr, unsigned short Port){

	WSADATA wsaData;

	int ret = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (ret != NO_ERROR) {
		return 1;
  }

  this->connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (this->connectSocket == INVALID_SOCKET) {
		WSACleanup();
		return 2;
  }

	struct sockaddr_in clientService;

  clientService.sin_family = AF_INET;
  clientService.sin_addr.s_addr = inet_addr(Addr);
  clientService.sin_port = htons(Port);

	ret = connect(this->connectSocket, (SOCKADDR*) &clientService, sizeof(clientService) );
  if (ret == SOCKET_ERROR) {		
    closesocket(this->connectSocket);
    WSACleanup();
    return 3;
  }

	return 0;
}

/*
 * Send string data into socket
 */
int Tcp::write(char *Text){

  int ret = send(this->connectSocket, Text, (int)strlen(Text), 0 );
  
	if (ret == SOCKET_ERROR) {
      closesocket(this->connectSocket);
      WSACleanup();
      return 1;
  }

	return 0;
}

/*
 * Close connection
 */
int Tcp::close(){

  int ret = shutdown(this->connectSocket, SD_SEND);
  
	if (ret == SOCKET_ERROR) {
      closesocket(this->connectSocket);
      WSACleanup();
      return 1;
  }

  ret = closesocket(this->connectSocket);
  
	if (ret == SOCKET_ERROR) {
      WSACleanup();
      return 2;
  }

  WSACleanup();
  return 0;
}
