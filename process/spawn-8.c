#include <stdio.h>
#include <stdlib.h>
#include <process.h>

#define ABORT_RC 127

int child( int argc, char *argv[])
{
    abort();

    /* NOT REACH HERE */

    exit( ABORT_RC );

    return 0;
}

int main( int argc, char *argv[])
{
    int rc;
    int failed;

    if( argc > 1 )
        return child( argc, argv );

    printf("Testing to return the correct exit code when a child abort()s...\n");
    rc = spawnl( P_WAIT, argv[ 0 ], argv[ 0 ], argv[ 0 ], NULL );

    failed = rc != ABORT_RC;
    printf("%s: rc = %d(%d)\n", failed ? "FAILED" : "PASSED", rc, ABORT_RC );

    return failed;
}
