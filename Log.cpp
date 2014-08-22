
#include "PirateDotty.h"
#include "Debug.h"
#include "Log.h"
#include <stdarg.h>

// --------------------------------------------------------------------
// GLOBAL VAR

#define KPRINTF_BUF_SIZE 256

// --------------------------------------------------------------------

#if defined(DEBUG) || defined(DEBUG_BT)
	bool debug_on = true;
#else
	bool debug_on = false;
#endif

//int log_level = 3;
int log_level = 1;

// --------------------------------------------------------------------
// LOCAL VAR
// --------------------------------------------------------------------

Stream* serialLine;

// --------------------------------------------------------------------
// FUNCTIONS
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// create a output function
// This works because Serial.write, although of
// type virtual, already exists.
//int uart_write (char c, FILE *stream)
//{
//	if (serialLine != NULL) {
//		serialLine->write(c) ;
//		return 0;
//	}
//}


void initLogging(Stream *stream) {

}

char buf[KPRINTF_BUF_SIZE];

/*
  * like printf() but output goes to "Serial.print".
  * If FREE_RTOS is defined, a mutex is used to protect from reentrancy.
  * TODO: Success/fail checks for xSemaphoreCreateMutex() and xSemaphoreTake() timeout.
  * Returns number of chars that did not fit into I/O port device buffer or 0.
  * Note:  Serial.print on the USB returns 0 in error, causing a flawed return value here.
*/
int kprintf(const char *format, ...)  {
  int n;
#ifdef _FREE_RTOS_
  static xSemaphoreHandle kprintfLock = 0; // mutual exclusion for non-reentrant va_start

  if (kprintfLock == 0)  {
    // first time only
    kprintfLock = xSemaphoreCreateMutex();
    xSemaphoreGive(kprintfLock);
  }

  if ((xSemaphoreTake(kprintfLock, configTICK_RATE_HZ / 4)) == pdPASS)  // TODO if pdFAIL, do more than just discard the print data.
#endif

  {
    va_list args;
    va_start (args, format);
    vsnprintf(buf, sizeof(buf), format, args); // does not overrun sizeof(buf) including null terminator
    va_end (args);
    // the below assumes that the new data will fit into the I/O buffer. If not, Serial may drop it.
    //   if Serial had a get free buffer count, we could delay and retry. Such does exist at the device class level, but not at this level.
    n = strlen(buf) - Serial2.print(buf); // move chars to I/O buffer, freeing up local buf
#ifdef _FREE_RTOS_
    xSemaphoreGive(kprintfLock);
#endif

  }
  return n; // number of chars unable to fit in device I/O buffer (see bug notice above)
}

void LOGi(const int loglevel, const char* fmt, ... )
{
//	if (serialLine == NULL) return;

	if (loglevel <= log_level) {
		va_list argptr;
		va_start(argptr, fmt);
//		kprintf(fmt, ...);
		vsnprintf(buf, sizeof(buf), fmt, argptr); // does not overrun sizeof(buf) including null terminator
		va_end(argptr);
	    // the below assumes that the new data will fit into the I/O buffer. If not, Serial may drop it.
	    //   if Serial had a get free buffer count, we could delay and retry. Such does exist at the device class level, but not at this level.
	    int n = strlen(buf) - Serial2.print(buf); // move chars to I/O buffer, freeing up local buf
	    Serial2.println(" ");
	}
}

void LOGd(const int loglevel, const char* fmt, ... )
{
//	if (serialLine == NULL) return;

	if (debug_on && loglevel <= log_level) {
		va_list argptr;
		va_start(argptr, fmt);
//		kprintf(fmt, argptr);
		vsnprintf(buf, sizeof(buf), fmt, argptr); // does not overrun sizeof(buf) including null terminator
		va_end(argptr);
	    // the below assumes that the new data will fit into the I/O buffer. If not, Serial may drop it.
	    //   if Serial had a get free buffer count, we could delay and retry. Such does exist at the device class level, but not at this level.
	    int n = strlen(buf) - Serial2.print(buf); // move chars to I/O buffer, freeing up local buf
	    Serial2.println(" ");
	}
}

