#include <stdio.h>
#include <process.h>

int main( void )
{
    const char *name = "spawn-7.cmd";
    const char *arg = "hello";

    printf("Testing if args are passed to REXX .cmd correctly...\n");

    return spawnl( P_WAIT, name, name, arg, NULL );
}
