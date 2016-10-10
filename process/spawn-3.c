#include <stdio.h>
#include <stdlib.h>
#include <process.h>

#define NAME "ls"

int main( void )
{
    int rc;

    printf("Testing to run %s even if %s dir entry in a current directory exists...\n",
           NAME, NAME );

    mkdir( NAME, 0755 );

    rc = spawnlp( P_WAIT, NAME, NAME, NULL );
    printf("%s: rc = %d(%d)\n", rc == -1 ? "FAILED" : "PASSED", rc, 0 );
    if( rc == -1 )
        perror("spawnlp: " NAME );

    rmdir( NAME );

    return rc == -1;
}
