/* This software was developed at the National Institute of Standards and Technology by employees of the Federal Government
in the course of their official duties. Pursuant to title 17 Section 105 of the United States Code this software is
not subject to copyright protection and is in the public domain. NIST assumes no responsibility whatsoever for its use by
other parties, and makes no guarantees, expressed or implied, about its quality, reliability, or any other characteristic.

We would appreciate acknowledgement if the software is used. The SAMATE project website is: http://samate.nist.gov
*/ 

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv)
{
	/* px is initialized */
	int *px = malloc(sizeof *px);                       /* FIX */
	float foo;

    if(px)
    {
    	foo = 3.5; 
        *px = argc;
    	if(*px == 1) printf("%6.1f", foo);
        free(px);
    }

	return 0;
}
