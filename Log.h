#ifndef _H_LOG
#define _H_LOG

#include "Arduino.h"

extern bool debug_on;
extern int log_level;

void initLogging(Stream *stream);
int kprintf(const char *format, ...);
void LOGi(const int loglevel, const char* fmt, ... );
void LOGd(const int loglevel, const char* fmt, ... );

#endif
