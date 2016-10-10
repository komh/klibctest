#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

int main( void )
{
    const char *s = "ÇÑ±Û!";
    wchar_t ws[ 4 ];
    int rc;
    int wlen;
    int errors = 0;
    int failed;

    printf("Testing mbstowcs() returns in wide-characters...\n");

    setlocale( LC_ALL, "ko_KR.CP949");

    rc = mbstowcs( ws, s, sizeof( ws ));
    wlen = wcslen( ws );
    failed = rc != wlen;

    printf("%s: non-NULL: rc = %d(%d)\n",
           failed ? "FAILED" : "PASSED", rc, wlen );

    if( failed )
        errors++;

    rc = mbstowcs( NULL, s, 0 );
    failed = rc != wlen;

    printf("%s: NULL: rc = %d(%d)\n",
           failed ? "FAILED" : "PASSED", rc, wlen );

    if( failed )
        errors++;

    return !!errors;
}
