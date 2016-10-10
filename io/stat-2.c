#include <stdio.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

int main( int argc, char *argv[])
{
    const char *name = "\\..";
    struct stat st;
    int rc;

    printf("Testing stat() for [\\..]...\n");

    rc = stat( name, &st );
    printf("%s: [%s], rc = %d(%d).\n",
           rc == 0 ? "FAILED" : "PASSED", name, rc, -1 );

    return rc == 0;
}
