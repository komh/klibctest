#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <errno.h>

int main( void )
{
    const char *name = "spawn-6.cmd";
    int rc;

    printf("Testing to run .cmd when COMSPEC is /bin/sh...\n");

    putenv("COMSPEC=/bin/sh");

    errno = 0;
    rc = spawnlp( P_WAIT, name, name, NULL );

    printf("%s: %s\n", rc  ? "FAILED" : "PASSED", strerror( errno ));

    return !!rc;
}
