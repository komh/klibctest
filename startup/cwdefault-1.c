#include <stdio.h>
#include <float.h>

int main( void )
{
    unsigned cw;
    int failed;

    printf("Testing FPU CW exception mask...\n");

    cw = _control87( 0, 0 );
    failed = ( cw & MCW_EM ) != MCW_EM;

    printf("%s: EM = %#x(%#x)\n",
           failed ? "FAILED": "PASSED", cw & MCW_EM, MCW_EM );

    return failed;
}
