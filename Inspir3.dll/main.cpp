#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include "tcp.h"
#include "log.h"

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

	log_init(false, true, "inspir3.log");
	
	log_info("RVExtension(outputSize: %d, function: '%s')", outputSize, function);
	
	if (!strcmp(function, "version")){                       //Function version()

		strcpy_s(output, outputSize, "0.3");

  }else	if (!strcmp(function, "initThread")){              //Function initThread()

		strcpy(message, "");

		DWORD dwThreadId;

		if (CreateThread(NULL,																	//Choose default security
											0,																		//Default stack size
											(LPTHREAD_START_ROUTINE)&ThreadProc,	//Routine to execute
											NULL,																	//Thread parameter
											0,																		//Immediately run the thread
											&dwThreadId) != NULL) {								//Thread Id
			
			log_info("Init thread success");
			strcpy_s(output, outputSize, "OK");

		}else{

			log_error("Init thread failed");
			strcpy_s(output, outputSize, "KO");

		}	
	}else	if (!strcmp(function, "exitThread")){		                   //Function initThread()

		strcpy(message, "exit");
		strcpy_s(output, outputSize, "OK");		

  }else	if (!strcmp(function, "gna")){                            //Function gna()
		strcpy(message, "gna");
		strcpy_s(output, outputSize, "OK");
	}

	log_info("RVExtension() End");

	log_close();
}
