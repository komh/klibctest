#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <errno.h>

int main( void )
{
    int fd;
    int rc;

    printf("Testing dup2() for a directory fd...\n");

    fd = open(".", O_RDONLY);

    errno = 0;
    rc = dup2( fd, fd + 1 );

    printf("%s: rc = %d(%d), errno = %d\n",
           rc == -1 ? "FAILED" : "PASSED", rc, fd + 1, errno );
    fflush( stdout );

    if( rc == -1 )
        perror("dup2()");

    close( fd );

    return rc == -1;
}
