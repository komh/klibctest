/* ioctl() test with TCPV40HDRS */

#define TCPV40HDRS

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <types.h>
#include <sys/socket.h> /* socket() */
#include <unistd.h>     /* soclose() */
#include <sys/ioctl.h>  /* ioctl(), SIOCGIFCONF */
#include <net/if.h>     /* struct ifreq */

#define MAX_NICS    IFMIB_ENTRIES

#define CALL_IOCTL( cmd, data ) \
    do { \
        strcpy( iflist[ 0 ].ifr_name, "lan0"); \
        errno = 0; \
        rc = ioctl( s, ( cmd ), data ); \
        if( rc == -1 ) \
            errors++; \
        printf("%s: %s: rc = %d(0), errno = %d(0)\n", \
               #cmd, rc == -1 ? "FAILED" : "PASSED", rc, errno ); \
    } while( 0 )

int main( void )
{
    struct ifconf ifconf;
    struct ifreq iflist[ MAX_NICS ];
    int s;
    int rc;
    int errors = 0;

    printf("Testing ioctl() with TCPV40HDRS...\n");

    s = socket( PF_INET, SOCK_RAW, 0 );

    CALL_IOCTL( SIOCGIFADDR, &iflist[ 0 ]);
/*    CALL_IOCTL( SIOCGIFDSTADDR, &iflist[ 0 ]);*/
    CALL_IOCTL( SIOCGIFBRDADDR,&iflist[ 0 ]);
    CALL_IOCTL( SIOCGIFNETMASK,&iflist[ 0 ]);

    memset( iflist, 0, sizeof( iflist ));
    ifconf.ifc_len = sizeof( iflist );
    ifconf.ifc_req = iflist;
    CALL_IOCTL( SIOCGIFCONF, &ifconf );

    soclose( s );

    return !!errors;
}
