#include <stdio.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main( void )
{
    const char *name = "read-1.test";

    char buf1[] = "\n\n\n";
    char buf2[ sizeof( buf1 )];
    int fd;
    int wrn;
    int rdn;
    int cmp;
    int failed;

    printf("Testing read() in text mode...\n");

    fd = open( name, O_RDWR | O_CREAT | O_TEXT, S_IREAD | S_IWRITE );

    wrn = write( fd, buf1, sizeof( buf1 ));

    lseek( fd, 0, SEEK_SET );
    rdn = read( fd, buf2, sizeof( buf1 ));

    cmp = memcmp( buf1, buf2, sizeof( buf1 ));

    failed = wrn != sizeof( buf1 ) || rdn != sizeof( buf1 ) || cmp != 0;

    printf("%s: wrn = %d(%d), rdn = %d(%d), cmp = %d(%d)\n",
           failed ? "FAILED" : "PASSED", wrn, sizeof( buf1 ),
           rdn, sizeof( buf1 ), cmp, 0 );

    close( fd );

    remove( name );

    return failed;
}
