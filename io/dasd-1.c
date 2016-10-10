#define INCL_DOS
#include <os2.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>     /* setmode() */
#include <fcntl.h>  /* O_BINARY  */
#include <sys/types.h>
#include <sys/stat.h>
#include <InnoTekLIBC/backend.h>

int main( void )
{
    char drive[] = "/dev/drivex";
    int fd;
    char cwd[ 512 ];
    char path[ 512 ];
    ULONG ulType;
    ULONG ulAttr;
    ULONG ulMode;
    struct stat st;
    int rc;
    int failed;
    int errors = 0;

    drive[ 10 ] = _getdrive();

    printf("----- DASD test : drive = %s -----\n", drive);

    rc = stat( drive, &st );
    failed = rc == -1 || !S_ISREG( st.st_mode );
    printf("%s: check stat() and S_ISREG(), rc = %d(%d), mode = %#x(%#x)\n",
           failed ? "FAILED" : "PASSED", rc, 0, st.st_mode, S_IFREG );
    errors += !!failed;

    failed = rc == -1 || ( char )st.st_dev != drive[10];
    printf("%s: check stat() and st_dev, rc = %d(%d), st_dev = %c(%c)\n",
           failed ? "FAILED" : "PASSED", rc, 0, st.st_dev, drive[ 10 ]);
    errors += !!failed;

    fd = open( drive, O_RDONLY );

    rc = __libc_Back_ioFHToPath( fd, path, sizeof( path ));
    failed = rc || drive[10] != path[ 0 ] || path[ 1 ] != ':' || path[ 2 ];
    printf("%s: get a path from fd, rc = %d(%d), path = [%s](%c:)\n",
           failed ? "FAILED" : "PASSED", rc, 0, path, drive[10] );
    errors += !!failed;

    rc = DosQueryHType( fd, &ulType, &ulAttr );
    failed = rc || ulType != HANDTYPE_FILE;
    printf("%s: check handle type, rc = %d(%d), type = %#lx(%#x)\n",
           failed ? "FAILED" : "PASSED", rc, 0, ulType, HANDTYPE_FILE );
    errors += !!failed;

    rc = DosQueryFHState( fd, &ulMode );
    failed = rc || !( ulMode & OPEN_FLAGS_DASD );
    printf("%s: check DASD flag, rc = %d(%d), flag = %#lx(%#x)\n",
           failed ? "FAILED" : "PASSED", rc, 0,
           ulMode & OPEN_FLAGS_DASD, OPEN_FLAGS_DASD );
    errors += !!failed;

    rc = fstat( fd, &st );
    failed = rc == -1 || !S_ISREG( st.st_mode );
    printf("%s: check fstat() and S_ISREG(), rc = %d(%d), mode = %#x(%#x)\n",
           failed ? "FAILED" : "PASSED", rc, 0, st.st_mode, S_IFREG );
    errors += !!failed;

    failed = rc == -1 || ( char )st.st_dev != drive[ 10 ];
    printf("%s: check fstat() and st_dev, rc = %d(%d), st_dev = %c(%c)\n",
           failed ? "FAILED" : "PASSED", rc, 0, st.st_dev, drive[ 10 ]);
    errors += !!failed;

    close( fd );

    drive[ 0 ] = _getdrive();
    drive[ 1 ] = ':';
    drive[ 2 ] = '\0';

    printf("----- DIR test : drive = %s -----\n", drive);

    rc = stat( drive, &st );
    failed = rc == -1 || !S_ISDIR( st.st_mode );
    printf("%s: check stat() and S_ISDIR(), rc = %d(%d), mode = %#x(%#x)\n",
           failed ? "FAILED" : "PASSED", rc, 0, st.st_mode, S_IFDIR );
    errors += !!failed;

    failed = rc == -1 || ( char )st.st_dev != drive[0];
    printf("%s: check stat() and st_dev, rc = %d(%d), st_dev = %c(%c)\n",
           failed ? "FAILED" : "PASSED", rc, 0, st.st_dev, drive[ 0 ]);
    errors += !!failed;

    fd = open( drive, O_RDONLY );

    rc = __libc_Back_ioFHToPath( fd, path, sizeof( path ));
    _getcwd1( cwd, drive[ 0 ]);

    failed = rc || drive[ 0 ] != path[ 0 ] || path[1 ] != ':' ||
             stricmp( cwd, path + 2 );
    printf("%s: get a path from fd, rc = %d(%d), path = [%s](%s%s)\n",
           failed ? "FAILED" : "PASSED", rc, 0, path, drive, cwd );
    errors += !!failed;

    rc = DosQueryHType( fd, &ulType, &ulAttr );
    failed = rc || ulType != HANDTYPE_DEVICE;
    printf("%s: check handle type, rc = %d(%d), type = %#lx(%#x)\n",
           failed ? "FAILED" : "PASSED", rc, 0, ulType, HANDTYPE_DEVICE );
    errors += !!failed;

    rc = DosQueryFHState( fd, &ulMode );
    failed = rc || ( ulMode & OPEN_FLAGS_DASD );
    printf("%s: check DASD flag, rc = %d(%d), flag = %#lx(%#x)\n",
           failed ? "FAILED" : "PASSED", rc, 0,
           ulMode & OPEN_FLAGS_DASD, 0 );
    errors += !!failed;

    rc = fstat( fd, &st );
    failed = rc == -1 || !S_ISDIR( st.st_mode );
    printf("%s: check fstat() and S_ISDIR(), rc = %d(%d), mode = %#x(%#x)\n",
           failed ? "FAILED" : "PASSED", rc, 0, st.st_mode, S_IFDIR );
    errors += !!failed;

    failed = rc == -1 || ( char )st.st_dev != drive[ 0 ];
    printf("%s: check fstat() and st_dev, rc = %d(%d), st_dev = %c(%c)\n",
           failed ? "FAILED" : "PASSED", rc, 0, st.st_dev, drive[ 0 ]);
    errors += !!failed;

    close( fd );

    return !!errors;
}
