/*
 * <author>Andice Rupen</author>
 * <email>andice.rupen@gmail.com</email>
 * <date>2013-11-23</date>
 * <summary>A minimal library to log messages into file or console</summary>
 */

void log_init(bool Console, bool File, char *Filename);
void log_error(const char* format, ...);
void log_debug(const char* format, ...);
void log_info(const char* format, ...);
void log_close();
