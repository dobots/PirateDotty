#ifndef _H_LOG
#define _H_LOG

#include "Arduino.h"

void initLogging(Stream *stream);
void setLogLevel(int level);

void LOGi(const int loglevel, const char* fmt, ... );
void LOGd(const int loglevel, const char* fmt, ... );

extern int log_level;

#endif