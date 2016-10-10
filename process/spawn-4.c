#include <stdio.h>
#include <process.h>

int main( void )
{
    const char *name = "spawn-4.sh";
    char * const argv[] = {( char * )name, NULL };
    int rc;

    printf("Testing to run a script not starting with #!\n");

    rc = spawnvp( P_WAIT, argv[ 0 ], argv);
    printf("%s: %s, rc = %d(!-1)\n", rc != -1 ? "PASSED" : "FAILED",
           name, rc );

    return !!rc;
}
