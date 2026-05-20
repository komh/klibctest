#include <stdio.h>

int dllexport_func( int );

int main( void )
{
    int err;
    int exp = 0x1234;
    int failed;

    printf("Testing if emxbind and ld export _declspec(dllexport) symbols...\n");

    err = dllexport_func( exp );
    failed = err != exp;
    printf("%s: dllexport_func() = %x(%x)\n",
           failed ? "FAILED" : "PASSED", err, exp );

    return failed;
}
