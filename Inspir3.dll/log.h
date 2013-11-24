/*
 * <author>Andice Rupen</author>
 * <email>andice.rupen@gmail.com</email>
 * <date>2013-11-24</date>
 * <summary>A minimal library to log messages into file or console</summary>
 */

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

typedef enum {log_DEBUG, log_INFO, log_ERROR} log_level;

#define log_bufferSize 4000

class Log{

	protected:
		char buffertext[log_bufferSize];
		char bufferdatetime[20];
		FILE *f;
		bool console;
		bool file;

		char *datetime();
		void text(log_level Level, char* Text);

	public:
		Log();
		void init(bool Console, bool File, char *Filename);
		void error(const char* format, ...);
		void debug(const char* format, ...);
		void info(const char* format, ...);
		void close();
};
