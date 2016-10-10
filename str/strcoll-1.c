#include <stdio.h>
#include <locale.h>
#include <string.h>

int main( void )
{
    const char *s1 = "12345";
    const char *s2 = "123456";
    int rc;

    setlocale( LC_COLLATE, "en_US.IBM949");
    printf("Testing strcoll()...\n");

    rc = strcoll( s1, s2 );
    printf("%s: s1 = [%s], s2 = [%s], rc = %d(!0)\n",
           rc == 0 ? "FAILED" : "PASSED", s1, s2, rc );

    return rc == 0;
}
