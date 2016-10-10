#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <errno.h>

int main( void )
{
    const char *name = "spawn-1.sh";
    int rc;

    printf("Testing to run /bin/sh even if sh dir entry exists...\n");

    mkdir("sh", 0755);

    errno = 0;
    rc = spawnlp( P_WAIT, name, name, NULL );

    printf("%s: %s\n", rc == -1 ? "FAILED" : "PASSED", strerror( errno ));

    rmdir("sh");

    return rc == -1;
}
