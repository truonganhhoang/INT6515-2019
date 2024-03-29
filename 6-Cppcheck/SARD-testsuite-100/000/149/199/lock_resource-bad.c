/* This software was developed at the National Institute of Standards and
 * Technology by employees of the Federal Government in the course of their
 * official duties. Pursuant to title 17 Section 105 of the United States
 * Code this software is not subject to copyright protection and is in the
 * public domain. NIST assumes no responsibility whatsoever for its use by
 * other parties, and makes no guarantees, expressed or implied, about its
 * quality, reliability, or any other characteristic.

 * We would appreciate acknowledgement if the software is used.
 * The SAMATE project website is: http://samate.nist.gov
*/

/*
	Implementation of CAN-2002-1869
	Don't check if you can write a log file allow attackers 
	to avoid logging
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static const char logFileName[] = "access.log";
static FILE *logFile = (FILE *)NULL;

#define logStr(__str__) if (writeLog) {fputs(__str__,logFile); fputc('\n',logFile);}

int main(int argc, char *argv[])
{
	bool writeLog = true;
	// you should check that you can write the file here...	
	logFile = fopen(logFileName, "a");
	if (!logFile) 
		writeLog = false;							/* FLAW */
	
	logStr("Action 1");
	logStr("Action 2");
	
	if (writeLog) fclose(logFile);
	return 0;
}
