#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <errno.h>

int main( void )
{
    int fd;
    int rc;

    printf("Testing dup() for a directory fd...\n");

    fd = open(".", O_RDONLY);

    errno = 0;
    rc = dup( fd );

    printf("%s: rc = %d(!%d), errno = %d\n",
           rc == -1 ? "FAILED" : "PASSED", rc, -1, errno );
    fflush( stdout );

    if( rc == -1 )
        perror("dup()");

    close( fd );

    return rc == -1;
}
