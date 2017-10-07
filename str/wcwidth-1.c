#include <stdio.h>
#include <locale.h>
#include <wchar.h>

static int test( wint_t wc, int expected )
{
    int rc;

    rc = wcwidth( wc );

    printf("%s: wcwidth( 0x%04X ) = %d(%d)\n",
           rc == expected ? "PASSED" : "FAILED", wc, rc, expected );

    return rc != expected;
}

int main( void )
{
    int failed = 0;

    printf("Testing if wcwidth() works reasonably in UTF-8 locales...\n");

    if (setlocale (LC_ALL, "fr_FR.UTF-8") != NULL)
    {
        failed += test( 0x0301/* COMBINING ACUTE ACCENT */, 0 );
        failed += test( 0x05B0/* HEBREW POINT SHEVA */, 0 );
        failed += test( 0x200B/* ZERO WIDTH SPACE */, 0 );
        failed += test( 0xFF1A/* FULLWIDTH COLON */, 2 );
    }

    return failed;
}
