#define INCL_DOS
#include <os2.h>

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/syslimits.h>
#include <errno.h>

int check( const char *msg, long val, long exp )
{
    int failed;

    failed = val != exp;

    printf("%s: %s = %ld(%ld)\n",
           failed ? "FAILED" : "PASSED", msg, val, exp );

    return failed;
}

int main( void )
{
    LONG lReqCount;
    ULONG ulOrgMaxFH, ulMaxFH, ulCurMaxFH;
    int maxfd = OPEN_MAX;
    int fd;
    ULONG rc;
    int errors = 0;

    printf("Testing if the maximum count of fds is correct...\n");

    lReqCount = 0;
    rc = DosSetRelMaxFH( &lReqCount, &ulOrgMaxFH );
    errors += check("Get initial MaxFH with DosSetRelMaxFH(): rc", rc, 0 );
    if( rc == 0 )
        errors += check("MaxFH", ulOrgMaxFH, ulOrgMaxFH );

    lReqCount = maxfd;
    rc = DosSetRelMaxFH( &lReqCount, &ulMaxFH );
    errors += check("Increase by maxfd with DosSetRelMaxFH(): rc", rc, 0 );
    if( rc == 0 )
    {
        errors += check("MaxFH", ulMaxFH, maxfd );

        rc = DosSetMaxFH( ulOrgMaxFH );
        check("Restore MaxFH with DosSetMaxFH(): rc", rc, 0 );
        if( rc == 0 )
        {
            lReqCount = 0;
            rc = DosSetRelMaxFH( &lReqCount, &ulCurMaxFH );
            errors += check("Get current MaxFH with DosSetRelMaxFHH(): rc",
                            rc, 0 );
        }
        else
        {
            lReqCount = ulOrgMaxFH - ulMaxFH;
            rc = DosSetRelMaxFH( &lReqCount, &ulCurMaxFH );
            errors += check("Restore MaxFH with DosSetRelMaxFH(): rc", rc, 0 );
        }

        if( rc == 0 )
            errors += check("MaxFH", ulCurMaxFH, ulOrgMaxFH );
    }

    rc = DosSetMaxFH( maxfd );
    errors += check("Set to maxfd with DosSetMaxFH(): rc", rc, 0 );
    if( rc == 0 )
    {
        lReqCount = 0;
        rc = DosSetRelMaxFH( &lReqCount, &ulCurMaxFH );
        errors += check("Get current MaxFH with DosSetRelMaxFH(): rc", rc, 0 );
        if( rc == 0 )
            errors += check("MaxFH", ulCurMaxFH, ulMaxFH );

        rc = DosSetMaxFH( ulOrgMaxFH );
        check("Restore MaxFH with DosSetMaxFH(): rc", rc, 0 );
        if( rc == 0 )
        {
            lReqCount = 0;
            rc = DosSetRelMaxFH( &lReqCount, &ulCurMaxFH );
            errors += check("Get current MaxFH with DosSetRelMaxFH(): rc",
                            rc, 0 );
        }
        else
        {
            lReqCount = ulOrgMaxFH - ulMaxFH;
            rc = DosSetRelMaxFH( &lReqCount, &ulCurMaxFH );
            errors += check("Restore MaxFH with DosSetRelMaxFH(): rc", rc, 0 );
        }

        if( rc == 0 )
            errors += check("MaxFH", ulCurMaxFH, ulOrgMaxFH );
    }

    errors += check("getdtablesize()", getdtablesize(), maxfd );

    errors += check("sysconf( _SC_OPEN_MAX )",
                    sysconf( _SC_OPEN_MAX ), maxfd );

#if 0
    struct rlimit r;

    /* The value of getrlimit() changes according to DosSetRelMaxFH().
       The minimum is 10000. */
    rc = getrlimit( RLIMIT_NOFILE, &r );
    errors += check("getrlimit( RLIMIT_NOFILE ): rc", rc, 0 );
    if( rc == 0 )
        errors += check("getrlimit( RLIMIT_NOFILE ): rlim_max",
                        r.rlim_max, maxfd );
#endif

    fd = dup2( 0, maxfd );
    errors += check("dup2( 0, maxfd )", fd, -1 );
    if( fd == -1 )
        errors += check("dup2( 0, maxfd ): errno", errno, EBADF );

    fd = dup2( 0, maxfd - 1 );
    errors += check("dup2( 0, maxfd - 1 )", fd, maxfd - 1 );

    fd = dup2( 0, maxfd + 1 );
    errors += check("dup2( 0, maxfd + 1 )", fd, -1 );
    if( fd == -1 )
        errors += check("dup2( 0, maxfd + 1 ): errno", errno, EBADF );

    return !!errors;
}
