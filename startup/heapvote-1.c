#include <stdio.h>

#include <emx/umalloc.h>

__declspec(dllimport) int hello( int rc );

int main( void )
{
    int result;

    printf("Testing if high-mem enabled even if linked against"
           "high-mem disabled DLL...\n");

    result = __libc_HeapGetResult();
    printf("%s: result = %d(%d)\n", result == 1 ? "PASSED" : "FAILED",
           result, 1 );

    return hello( result != 1 );
}
