#include <stdio.h>
#include <wchar.h>
#include <limits.h>

#define TYPE_MAX(t) (( t )0 < ( t )-1 ? \
                     ( t )~0 : \
                     ( t )~(( t )1 << ( sizeof( t ) * 8 - 1 )))
#define TYPE_MIN(t) (( t )0 < ( t )-1 ? \
                     ( t )0 : \
                     ~TYPE_MAX( t ))

int main( void )
{
    int errors = 0;
    int failed;

    printf("Testing for correctness of WCHAR_MAX and WCHAR_MIN...\n");

    failed = TYPE_MAX( wchar_t ) != WCHAR_MAX;
    errors += failed;
    printf("%s: WCHAR_MAX = %d(%d)\n",
           failed ? "FAILED" : "PASSED", WCHAR_MAX, TYPE_MAX( wchar_t ));

    failed = TYPE_MIN( wchar_t ) != WCHAR_MIN;
    errors += failed;
    printf("%s: WCHAR_MIN = %d(%d)\n",
           failed ? "FAILED" : "PASSED", WCHAR_MIN, TYPE_MIN( wchar_t ));

    return !!errors;
}
