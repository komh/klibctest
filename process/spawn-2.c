#include <stdio.h>
#include <process.h>

int main( void )
{
    int rc;

    rc = spawnlp(P_WAIT, "spawn-2.sh", "spawn-2.sh", "1", "2", "3", NULL );

    return !!rc;
}
