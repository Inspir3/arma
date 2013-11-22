
#include <winsock2.h>

int iResult;
WSADATA wsaData;
SOCKET ConnectSocket = INVALID_SOCKET;
struct sockaddr_in clientService; 

/*
 * tcp_init
 */
int tcp_init(){

	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != NO_ERROR) {
		return 1;
  }

  ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (ConnectSocket == INVALID_SOCKET) {
		WSACleanup();
		return 2;
  }

	return 0;
}

/*
 * tcp_connect
 */
int tcp_connect(char *Addr, unsigned short Port){

  clientService.sin_family = AF_INET;
  clientService.sin_addr.s_addr = inet_addr(Addr);
  clientService.sin_port = htons(Port);

  iResult = connect( ConnectSocket, (SOCKADDR*) &clientService, sizeof(clientService) );
  if (iResult == SOCKET_ERROR) {		
    closesocket(ConnectSocket);
    WSACleanup();
    return 1;
  }

	return 0;
}

/*
 * tcp_send
 */
int tcp_send(char *Text){

  iResult = send( ConnectSocket, Text, (int)strlen(Text), 0 );
  
	if (iResult == SOCKET_ERROR) {
      closesocket(ConnectSocket);
      WSACleanup();
      return 1;
  }

	return 0;
}

/*
 * tcp_close
 */
int tcp_close(){

  iResult = shutdown(ConnectSocket, SD_SEND);
  if (iResult == SOCKET_ERROR) {
      closesocket(ConnectSocket);
      WSACleanup();
      return 1;
  }

  iResult = closesocket(ConnectSocket);
  if (iResult == SOCKET_ERROR) {
      WSACleanup();
      return 2;
  }

  WSACleanup();
  return 0;
}
