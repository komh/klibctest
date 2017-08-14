#include <stdio.h>
#include <wchar.h>

int main( void )
{
    const wchar_t *wcs1 = L"Hello";
    const wchar_t *wcs2 = L"Hello, world!";
    int rc;

    printf("Testing if wmemcmp() compares sub-string correctly...\n");

    rc = wmemcmp( wcs1, wcs2, wcslen( wcs1 ));
    printf("%s: comparing sub-string: rc = %x(0)\n",
           rc != 0 ? "FAILED" : "PASSED", rc );

    return rc != 0;
}
