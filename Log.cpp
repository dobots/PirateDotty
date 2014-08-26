
#include "PirateDotty.h"
#include "Debug.h"
#include "Log.h"
#include <stdarg.h>

// --------------------------------------------------------------------
// GLOBAL VAR

#define KPRINTF_BUF_SIZE 256

// --------------------------------------------------------------------
// LOCAL VAR
// --------------------------------------------------------------------

Stream* serialLine = NULL;

char buf[KPRINTF_BUF_SIZE];

#if defined(DEBUG)
	bool debug_on = true;
#else
	bool debug_on = false;
#endif

int log_level = 3;
//int log_level = 1;

// --------------------------------------------------------------------
// FUNCTIONS
// --------------------------------------------------------------------

// --------------------------------------------------------------------
void initLogging(Stream *stream) {
	serialLine = stream;
}

// --------------------------------------------------------------------
void setLogLevel(int level) {
	log_level = level;
}

// --------------------------------------------------------------------
void timeStamp() {
#ifdef LOG_TIME
	sprintf(buf, "[%6d] ", millis());
	serialLine->write(buf);
#endif
}

// --------------------------------------------------------------------
void LOGi(const int loglevel, const char* fmt, ... )
{
	if (serialLine == NULL) return;

	if (loglevel <= log_level) {
		timeStamp();

		va_list argptr;
		va_start(argptr, fmt);
		vsnprintf(buf, sizeof(buf), fmt, argptr); // does not overrun sizeof(buf) including null terminator
		va_end(argptr);
	    // the below assumes that the new data will fit into the I/O buffer. If not, Serial may drop it.
	    //   if Serial had a get free buffer count, we could delay and retry. Such does exist at the device class level, but not at this level.

		int n = strlen(buf) - serialLine->write(buf);
	    serialLine->write("\r\n");
	}
}

// --------------------------------------------------------------------
void LOGd(const int loglevel, const char* fmt, ... )
{
	if (serialLine == NULL) return;

	if (debug_on && loglevel <= log_level) {
		timeStamp();

		va_list argptr;
		va_start(argptr, fmt);
		vsnprintf(buf, sizeof(buf), fmt, argptr); // does not overrun sizeof(buf) including null terminator
		va_end(argptr);
	    // the below assumes that the new data will fit into the I/O buffer. If not, Serial may drop it.
	    //   if Serial had a get free buffer count, we could delay and retry. Such does exist at the device class level, but not at this level.

		int n = strlen(buf) - serialLine->write(buf);
	    serialLine->write("\r\n");
	}
}
