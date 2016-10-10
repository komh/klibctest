#include <stdio.h>
#include <unistd.h>
#include <io.h>
#include <fcntl.h>
#include <errno.h>

int main( void )
{
    int fd;
    int rc;
    int errors = 0;

    printf("Testing fcntl() for a directory fd...\n");

    fd = open(".", O_RDONLY );

    errno = 0;
    rc = fcntl( fd, F_DUPFD, STDERR_FILENO );
    printf("fcntl(F_DUPFD): %s, rc = %d(>%d), errno = %d\n",
           rc == -1 ? "FAILED" : "PASSED", rc, STDERR_FILENO, errno );
    fflush( stdout);

    if (rc == -1)
    {
        perror("fcntl(F_DUPFD)");
        errors++;
    }

    errno = 0;
    rc = fcntl( fd, F_GETFL );
    printf("fcntl(F_GETFL): %s, rc = %d(>=%d), errno = %d\n",
           rc == -1 ? "FAILED" : "PASSED", rc, 0, errno );
    fflush( stdout);

    if (rc == -1)
    {
        perror("fcntl(F_GETFL)");
        errors++;
    }

    errno = 0;
    rc = fcntl( fd, F_SETFL, 0 );
    printf("fcntl(F_SETFL): %s, rc = %d(%d), errno = %d\n",
           rc == -1 ? "FAILED" : "PASSED", rc, 0, errno );
    fflush( stdout);

    if (rc == -1)
    {
        perror("fcntl(F_SETFL)");
        errors++;
    }

    errno = 0;
    rc = fcntl( fd, F_GETFD );
    printf("fcntl(F_GETFD): %s, rc = %d(>=%d), errno = %d\n",
           rc == -1 ? "FAILED" : "PASSED", rc, 0, errno );
    fflush( stdout);

    if (rc == -1)
    {
        perror("fcntl(F_GETFD)");
        errors++;
    }

    errno = 0;
    rc = fcntl( fd, F_SETFD, 0 );
    printf("fcntl(F_SETFD): %s, rc = %d(%d), errno = %d\n",
           rc == -1 ? "FAILED" : "PASSED", rc, 0, errno );
    fflush( stdout);

    if (rc == -1)
    {
        perror("fcntl(F_SETFD)");
        errors++;
    }

    close( fd );

    return !!errors;
}
