#include <os2.h>

#include <stdio.h>
#include <unistd.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>

int main( void )
{
    const char *msg_list[] = {"[.]", "[..]", "trailing slash", NULL };
    const char *name_list[] = {".", "..", "./", NULL };
    const char *name;
    int name_max;
    int errors = 0;
    int i;

    printf("Testing pathconf( _PC_NAME_MAX )...\n");

    for( i = 0; name_list[ i ]; i++ )
    {
        name = name_list[ i ];
        name_max = pathconf( name, _PC_NAME_MAX );
        printf("%s: %s test: name = %s, NAME_MAX = %d(%d)\n",
               name_max == CCHMAXPATHCOMP ? "PASSED" : "FAILED", msg_list[ i ],
               name, name_max, CCHMAXPATHCOMP );
        if( name_max == -1 )
            errors++;
    }

    return !!errors;
}
