#include <stdio.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

int main( int argc, char *argv[])
{
    const char *name = "stat-1.c.";
    struct stat st;
    int rc;

    printf("Testing stat() for trailing dots...\n");

    rc = stat( name, &st );
    printf("%s: [%s], rc = %d(%d)\n",
           rc == 0 ? "PASSED" : "FAILED", name, rc, 0 );
    fflush( stdout );

    if( rc != 0)
        perror("stat");

    return rc == -1;
}
