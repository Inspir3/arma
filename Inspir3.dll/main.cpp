#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include "tcp.h"

#pragma comment(lib, "Ws2_32.lib")

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved){
	switch (ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}

	return TRUE;
}

extern "C"{
  __declspec(dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *function); 
};

char message[255];

/*
 * Main thread
 */
DWORD ThreadProc(LPVOID lpdwThreadParam){

	FILE *f;
	
	fopen_s(&f, "thread.txt", "a");

	char *msg1 = "Init thread OK\n";
	fwrite(msg1, sizeof(char), strlen(msg1), f);

	tcp_init();
	tcp_connect("127.0.0.1", 8124);

	for(;;){

		if (strlen(message) > 0){
			fwrite(message, sizeof(char), strlen(message), f);
			tcp_send(message);
			//strcpy(message, "");			
		}

		Sleep(1000);

		if (!strcmp(message, "exit")) break;
	}

	char *msg2 = "Bye !\n";

	fwrite(msg2, sizeof(char), strlen(msg2), f);

	fclose(f);
	tcp_close();

	return 0;
}

/*
 * Point de communication entre Arma et la dll
 */
void __stdcall RVExtension(char *output, int outputSize, const char *function){

	FILE *f;
	fopen_s(&f, "inspir3.log", "a");
	
	char *msg1 = "RVExtension()\n";
	fwrite(msg1, sizeof(char), strlen(msg1), f);

	fclose(f);

	/*
	 * version
	 */
	if (!strcmp(function, "version")){
		strcpy_s(output, outputSize, "0.3");return;
  }

	/*
	 * initThread
	 */
	if (!strcmp(function, "initThread")){

		strcpy(message, "");

		DWORD dwThreadId;

		if (CreateThread(NULL,																	//Choose default security
											0,																		//Default stack size
											(LPTHREAD_START_ROUTINE)&ThreadProc,	//Routine to execute
											NULL,																	//Thread parameter
											0,																		//Immediately run the thread
											&dwThreadId) != NULL) {								//Thread Id
			strcpy_s(output, outputSize, "OK");return;
		}else{
			strcpy_s(output, outputSize, "KO");return;
		}	
	}

	/*
	 * Other ? Send to thread
	 */
	if (!strcmp(function, "exitThread")){		
		strcpy(message, "exit");
		strcpy_s(output, outputSize, "OK");return;		
  }

	if (!strcmp(function, "gna")){		
		strcpy(message, "gna");
		strcpy_s(output, outputSize, "OK");return;
	}

	//strcpy_s(message, strlen(function), function);
  
}
