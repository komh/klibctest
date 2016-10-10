#include <stdio.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include <errno.h>

int main( void )
{
    const char *name_list[] = {"freopen-1.c", "stdin", "stdout", "stderr", NULL };
    FILE *fp_list[ sizeof( name_list ) / sizeof( name_list[ 0 ])];
    const char *mode_list[] = {"rb", "rb", "wb", "wb", NULL };
    const char *name;
    int flags;
    int errors;
    int failed;
    FILE *fp;
    FILE *fpr;
    int i;

    printf("Testing if freopen() returns NULL even if it succeeds...\n");

    name = "freopen-1.c";

    fp_list[ 0 ] = fopen( name_list[ 0 ], "rt");
    fp_list[ 1 ] = stdin;
    fp_list[ 2 ] = stdout;
    fp_list[ 3 ] = stderr;
    fp_list[ 4 ] = NULL;

    errors = 0;
    for( i = 0; fp_list[ i ]; i++ )
    {
        name = name_list[ i ];
        fp = fp_list[ i ];

        errno = 0;
        fpr = freopen( NULL, mode_list[ i ], fp );

        failed = ( fpr && errno ) || ( !fpr && !errno );
        if( failed )
            errors++;

        flags = fcntl( fileno( fp ), F_GETFL ) & O_BINARY;

        if( !strcmp( mode_list[ i ], "wb"))
            freopen( NULL, "wt", fp );

        printf("%s: name = [%s], freopen() = %p(%p), errno = %d(%d), flags = %s(%s)\n",
               failed ? "FAILED" : "PASSED", name, fpr, fp, errno, 0,
               flags == O_BINARY ? "O_BINARY" : "O_TEXT", "O_BINARY");
    }

    if( fp_list[ 0 ])
        fclose( fp_list[ 0 ]);

    return !!errors;
}
