#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <process.h>

#include <io.h>
#include <fcntl.h>

#include <sys/socket.h>

#define STDIN   0
#define STDOUT  1
#define STDERR  2

#define PARENT_MSG "Hello"
#define CHILD_MSG  "World!!!"

#define CHILD_MAGIC "__CHILD_MAGIC__"

static int setcloexec( int fd )
{
    int ret;

    ret = fcntl( fd, F_GETFD );
    if( ret != -1 )
        ret = fcntl( fd, F_SETFD, ret | FD_CLOEXEC );

    return ret;
}

static int parent( int inwr, int outrd )
{
    FILE *fpin;
    FILE *fpout;
    char line[ 256 ];
    int error;

    fpin = fdopen( inwr, "w");
    fprintf( fpin, "%s", PARENT_MSG );
    fclose( fpin );

    fpout = fdopen( outrd, "r");
    fgets( line, sizeof( line ), fpout );
    fclose( fpout );

    error = strcmp( line, CHILD_MSG );
    printf("%s: PARENT: received = [%s], wanted = [%s]\n",
           error ? "FAILED" : "PASSED", line, CHILD_MSG );

    return !!error;
}

static int child( void )
{
    char line[ 256 ];
    int error;

    fgets( line, sizeof( line ), stdin );

    error = strcmp( line, PARENT_MSG );
    fprintf( stderr, "%s: CHILD: received = [%s], wanted = [%s]\n",
             error ? "FAILED" : "PASSED", line, PARENT_MSG );

    printf("World!!!");

    /* Without fflush()ing, the above output is only buffered, and not written
     * to a socket
     */
#if 0
    fflush( stdout );
#endif

    return !!error;
}

int main( int argc, char *argv[])
{
    int socksin[ 2 ], socksout[ 2 ];
    int savedin, savedout;

    if( argc > 1 && strcmp( argv[ 1 ], CHILD_MAGIC ) == 0)
        return child();

    printf("Testing if a stream associated with a socket is flushed at exit...\n");

    socketpair( AF_LOCAL, SOCK_STREAM, 0, socksin );
    socketpair( AF_LOCAL, SOCK_STREAM, 0, socksout );

    setcloexec( socksin[ 0 ]);
    setcloexec( socksin[ 1 ]);

    setcloexec( socksout[ 0 ]);
    setcloexec( socksout[ 1 ]);

    savedin = dup( STDIN );
    dup2( socksin[ 0 ], STDIN );

    savedout = dup( STDOUT );
    dup2( socksout[ 1 ], STDOUT );

    spawnl( P_NOWAIT, argv[ 0 ], argv[ 0 ], CHILD_MAGIC, NULL );

    dup2( savedout, STDOUT );
    close( savedout );

    dup2( savedin, STDIN );
    close( savedin );

    close( socksin[ 0 ]);
    close( socksout[ 1 ]);

    return parent( socksin[ 1 ], socksout[ 0 ]);
}
