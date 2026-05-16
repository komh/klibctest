#include <stdio.h>
#include <a_out.h>

int main( int argc, char *argv[])
{
    const char *me = argv[ 0 ];
    FILE *fp;
    int ret;
    int failed;
    int errors = 0;

    printf("Testing _fseek_hdr() recognizes a.out with old-EMX startup code...\n");

    fp = fopen( me, "rb");
    ret = _fseek_hdr( fp );
    failed = ret != 0;
    printf("%s: _fseek_hdr() = %d(0)\n", failed ? "FAILED": "PASSED", ret );
    errors += failed;

    if( !failed )
    {
        long hdrpos;
        struct exec hdr;

        hdrpos = ftell( fp );
        fread( &hdr, 1, sizeof( hdr ), fp );
        failed = N_BADMAG( hdr );
        printf("%s: magic = %lo(ZMAGIC = %o, NMAGIC = %o, OMAGIC = %o)\n",
               failed ? "FAILED" : "PASSED",
               N_MAGIC( hdr ), ZMAGIC, NMAGIC, OMAGIC );
        if( !failed )
            printf("Found header at pos %04lX\n", hdrpos );

        errors += failed;
    }

    fclose( fp );

    return !!errors;
}
