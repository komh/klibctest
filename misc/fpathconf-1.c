#include <os2.h>

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

int check( const char *path )
{
    int fd;
    int rc;
    int failed;

    fd = open( path, O_RDONLY );
    rc = fpathconf( fd, _PC_NAME_MAX );
    close( fd );

    failed = rc != CCHMAXPATHCOMP;
    printf("%s: name = [%s], rc = %d(%d)\n",
           failed ? "FAILED" : "PASSED", path, rc, CCHMAXPATHCOMP);

    return !!failed;
}

int main( void )
{
    const char *path_list[] = {".", "/", NULL};
    int errors;
    int i;

    printf("Testing fpathconf( dirfd, _PC_NAME_MAX )...\n");

    errors = 0;
    for( i = 0; path_list[ i ]; i++ )
        errors += check(path_list[ i ]);

    return !!errors;
}
