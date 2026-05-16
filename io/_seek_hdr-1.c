#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <a_out.h>

int main( int argc, char *argv[])
{
    const char *me = argv[ 0 ];
    int fd;
    int ret;
    int failed;
    int errors = 0;

    printf("Testing _seek_hdr() recognizes a.out with old-EMX startup code...\n");

    fd = open( me, O_RDONLY | O_BINARY );
    ret = _seek_hdr( fd );
    failed = ret != 0;
    printf("%s: _seek_hdr() = %d(0)\n", failed ? "FAILED": "PASSED", ret );
    errors += failed;

    if( !failed )
    {
        long hdrpos;
        struct exec hdr;

        hdrpos = tell( fd );
        read( fd, &hdr, sizeof( hdr ));
        failed = N_BADMAG( hdr );
        printf("%s: magic = %lo(ZMAGIC = %o, NMAGIC = %o, OMAGIC = %o)\n",
               failed ? "FAILED" : "PASSED",
               N_MAGIC( hdr ), ZMAGIC, NMAGIC, OMAGIC );
        if( !failed )
            printf("Found header at pos %04lX\n", hdrpos );

        errors += failed;
    }

    close( fd );

    return !!errors;
}
