/*
 * <author>Andice Rupen</author>
 * <email>andice.rupen@gmail.com</email>
 * <date>2013-11-23</date>
 * <summary>A minimal library to log messages into file or console</summary>
 */

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

typedef enum {DEBUG, INFO, ERROR} log_level;

#define log_bufferSize 4000

char log_buffertext[log_bufferSize] = "";
char log_bufferdatetime[20] = "";
FILE *log_f;
bool log_console;
bool log_file;

/*
 * Init logging
 */
void log_init(bool Console, bool File, char *Filename){
	log_console = Console;
	log_file = File;

	if (log_file) {
		fopen_s(&log_f, Filename, "a+");
	}
}

/*
 *
 */
void log_close(){
	if (log_file) {
		fclose(log_f);
	}
}

/*
 * Get datetime
 */
char *log_datetime(){
	
	time_t timer;
	struct tm tm_info;

	time(&timer);
	localtime_s(&tm_info, &timer);

	strftime(log_bufferdatetime, 20, "%d/%m/%Y %H:%M:%S", &tm_info);
	
	return log_bufferdatetime;
}

/*
 * Main function
 */
void log_text(log_level Level, char* Text){

		char header[30] = "";
		char buffer[4000] = "";

		strcpy_s(header, log_datetime());

		switch(Level){
			case DEBUG:
				strcat_s(header, " [DEBUG] ");
				break;
			case INFO:
				strcat_s(header, " [INFO]  ");
				break;
			case ERROR:
				strcat_s(header, " [ERROR] ");
				break;
		}

		strcat_s(buffer, header);
		strcat_s(buffer, Text);
		strcat_s(buffer, "\n");

		if (log_console) {
				printf(buffer);
		}

		if (log_file){
			fwrite(buffer, sizeof(char), strlen(buffer), log_f);
		}
}

/*
 *
 */
void log_debug(const char* Format, ...){

	va_list arglist;

	va_start(arglist, Format);
	vsnprintf_s(log_buffertext, log_bufferSize, Format, arglist);
	va_end(arglist);

	log_text(DEBUG, log_buffertext);
}

/*
 *
 */
void log_info(const char* Format, ...){

	va_list arglist;

	va_start(arglist, Format);
	vsnprintf_s(log_buffertext, log_bufferSize, Format, arglist);
	va_end(arglist);

	log_text(INFO, log_buffertext);
}

/*
 *
 */
void log_error(const char* Format, ...){

	va_list arglist;

	va_start(arglist, Format);
	vsnprintf_s(log_buffertext, log_bufferSize, Format, arglist);
	va_end(arglist);

	log_text(ERROR, log_buffertext);
}
