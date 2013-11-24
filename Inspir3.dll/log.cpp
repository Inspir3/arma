/*
 * <author>Andice Rupen</author>
 * <email>andice.rupen@gmail.com</email>
 * <date>2013-11-24</date>
 * <summary>A minimal library to log messages into file or console</summary>
 */

#include "Log.h"

/*
 *
 */
Log::Log(){
	strcpy_s(this->buffertext, log_bufferSize, "");
	strcpy_s(this->bufferdatetime, 20, "");
}

/*
 * Init logging
 */
void Log::init(bool Console, bool File, char *Filename){
	this->console = Console;
	this->file = File;

	if (this->file) {
		fopen_s(&this->f, Filename, "a+");
	}
}

/*
 *
 */
void Log::close(){
	if (this->file) {
		fclose(this->f);
	}
}

/*
 * Get datetime
 */
char *Log::datetime(){
	
	time_t timer;
	struct tm tm_info;

	time(&timer);
	localtime_s(&tm_info, &timer);

	strftime(this->bufferdatetime, 20, "%d/%m/%Y %H:%M:%S", &tm_info);
	
	return this->bufferdatetime;
}

/*
 * Main function
 */
void Log::text(log_level Level, char* Text){

		char header[30] = "";
		char buffer[4000] = "";

		strcpy_s(header, this->datetime());

		switch(Level){
			case log_DEBUG:
				strcat_s(header, " [DEBUG] ");
				break;
			case log_INFO:
				strcat_s(header, " [INFO]  ");
				break;
			case log_ERROR:
				strcat_s(header, " [ERROR] ");
				break;
		}

		strcat_s(buffer, header);
		strcat_s(buffer, Text);
		strcat_s(buffer, "\n");

		if (this->console) {
				printf(buffer);
		}

		if (this->file){
			fwrite(buffer, sizeof(char), strlen(buffer), this->f);
		}
}

/*
 *
 */
void Log::debug(const char* Format, ...){

	va_list arglist;

	va_start(arglist, Format);
	vsnprintf_s(this->buffertext, log_bufferSize, Format, arglist);
	va_end(arglist);

	this->text(log_DEBUG, this->buffertext);
}

/*
 *
 */
void Log::info(const char* Format, ...){

	va_list arglist;

	va_start(arglist, Format);
	vsnprintf_s(this->buffertext, log_bufferSize, Format, arglist);
	va_end(arglist);

	this->text(log_INFO, this->buffertext);
}

/*
 *
 */
void Log::error(const char* Format, ...){

	va_list arglist;

	va_start(arglist, Format);
	vsnprintf_s(this->buffertext, log_bufferSize, Format, arglist);
	va_end(arglist);

	this->text(log_ERROR, this->buffertext);
}
