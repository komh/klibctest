#define INCL_DOS
#include <os2.h>

#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#define PIPE_NAME "\\PIPE\\FCNTL\\NAMED_PIPE"

static int named_pipe( int *ph )
{
    HPIPE hpipe;
    HFILE hpipeWrite;
    ULONG ulAction;

    DosCreateNPipe( PIPE_NAME,
                    &hpipe,
                    NP_ACCESS_DUPLEX,
                    NP_NOWAIT | NP_TYPE_BYTE | NP_READMODE_BYTE | 1,
                    32768, 32768, 0 );

    DosConnectNPipe( hpipe );

    DosOpen( PIPE_NAME, &hpipeWrite, &ulAction, 0, FILE_NORMAL,
             OPEN_ACTION_OPEN_IF_EXISTS,
             OPEN_SHARE_DENYREADWRITE | OPEN_ACCESS_WRITEONLY,
             NULL );

    ph[ 0 ] = hpipe;
    ph[ 1 ] = hpipeWrite;

    return 0;

}

int check( const char *msg, int fd )
{
    ULONG ulState;
    int fl;
    int failed;
    ULONG rc;

    rc = DosQueryNPHState( fd, &ulState );
    if(!rc)
    {
        fl = fcntl(fd, F_GETFL);

        rc = fl != -1 ? 0 : 1;
    }

    failed = rc ||
             ((( ulState & NP_NOWAIT ) == NP_NOWAIT ) !=
              (( fl & O_NONBLOCK ) == O_NONBLOCK ));

    printf("%s: %s, fcntl() = %s(%s)\n",
           failed ? "FAILED" : "PASSED", msg,
           ( fl & O_NONBLOCK ) ? "Non-block" : "Block",
           ( ulState & NP_NOWAIT ) ? "Non-block" : "Block");

    return failed;
}

int main( void )
{
    int ph[ 2 ];
    int fd;
    int fl;
    int errors = 0;

    printf("Testing fcntl(O_NONBLOCK) for a named pipe\n");

    named_pipe( ph );

    fd = ph[ 0 ];
    fl = fcntl( fd, F_GETFL );
    errors += check("S: Import", fd );

    fcntl( fd, F_SETFL, fl & ~O_NONBLOCK );
    errors += check("S: Set to BLOCK", fd );

    fcntl( fd, F_SETFL, fl | O_NONBLOCK );
    errors += check("S: Set to NON-BLOCK", fd );

    fd = ph[ 1 ];
    fl = fcntl( fd, F_GETFL );
    errors += check("C: Import", fd );

    fcntl( fd, F_SETFL, fl & ~O_NONBLOCK );
    errors += check("C: Set to BLOCK", fd );

    fcntl( fd, F_SETFL, fl | O_NONBLOCK );
    errors += check("C: Set to NON-BLOCK", fd );

    close( ph[ 0 ]);
    close( ph[ 1 ]);

    return !!errors;
}
