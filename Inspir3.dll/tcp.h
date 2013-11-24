/*
 * <author>Andice Rupen</author>
 * <email>andice.rupen@gmail.com</email>
 * <date>2013-11-24</date>
 * <summary>A minimal library to send string over tcp/ip</summary>
 */

#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

class Tcp{

	protected:				
		SOCKET connectSocket;

	public:

		Tcp();
		int open(char *Addr, unsigned short Port);
		int write(char *Text);
		int close();
};
