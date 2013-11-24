#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include "Tcp.h"
#include "Log.h"

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

	Log *log = new Log();
	Tcp *tcp = new Tcp();

	log->init(false, true, "inspir3_thread.log");

	log->info("Init thread OK");
	
	log->info("Connecting to serveur...");
	tcp->open("127.0.0.1", 8124);
	log->info("Connecting to serveur... OK");

	for(;;){

		if (strlen(message) > 0){

			log->info("Sending '%s'...", message);
			tcp->write(message);
			//strcpy(message, "");			
		}

		log->debug("Sleeping...");
		Sleep(1000);

		if (!strcmp(message, "exit")) break;
	}

	log->debug("Closing connection...");
	
	tcp->close();

	log->debug("Exiting thread... Bye!");
	log->close();

	return 0;
}

/*
 * Point de communication entre Arma et la dll
 */
void __stdcall RVExtension(char *output, int outputSize, const char *function){

	Log *log = new Log();

	log->init(false, true, "inspir3.log");
	
	log->info("RVExtension(outputSize: %d, function: '%s')", outputSize, function);
	
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
			
			log->info("Init thread success");
			strcpy_s(output, outputSize, "OK");

		}else{

			log->error("Init thread failed");
			strcpy_s(output, outputSize, "KO");

		}	
	}else	if (!strcmp(function, "exitThread")){		                   //Function initThread()

		strcpy(message, "exit");
		strcpy_s(output, outputSize, "OK");		

  }else	if (!strcmp(function, "gna")){                            //Function gna()
		strcpy(message, "gna");
		strcpy_s(output, outputSize, "OK");
	}

	log->info("RVExtension() End");

	log->close();
}
