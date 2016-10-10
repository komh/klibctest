#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <errno.h>

int main( void )
{
    const char *name = "spawn-5.pl";
    int rc;

    printf("Testing to run perl even if perl dir entry exists...\n");

    mkdir("perl", 0755);

    errno = 0;
    rc = spawnlp( P_WAIT, name, name, NULL );

    printf("%s: %s\n", rc == -1 ? "FAILED" : "PASSED", strerror( errno ));

    rmdir("perl");

    return rc == -1;
}
