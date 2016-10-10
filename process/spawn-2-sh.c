#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[])
{
    char me[ 512 ];
    char argv0[ 512 ];
    int i;
    int rc;

    printf("Testing if argv[0] is an interpreter name\n");

    _execname( me, sizeof( me ));

    for( i = 0; argv[ i ]; i++ )
        printf("argv[ %d ] = [%s]\n", i, argv[ i ]);

    _fnslashify( me );
    _fnslashify( argv[ 0 ]);

    strcpy( argv0, argv[ 0 ]);
    _defext( argv0, "exe");

    rc = stricmp( _getname( me ), _getname( argv0 ));

    printf("%s: me = [%s], argv[0] = [%s]\n",
           rc ? "FAILED" : "PASSED", me, argv[0]);

    return rc;
}
