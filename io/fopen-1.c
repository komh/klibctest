#include <stdio.h>
#include <errno.h>

const char *name = "f:/home/komh/.mplayer/sub/mp4%3B+codecs=%22avc1.64001F%2C+mp4a.40.2%22&ip=218.232.8.77&cp=U0hWRVRRVF9KTENONl9MS1hHOm5JUDZYZ1J0Y05Z&key=yt1&id=703c4dde27ef73b9&upn=4wc8CVwC7XY&mt=1370440835&ratebypass=yes&sver=3&fexp=921713%2C900352%2C924605%2C928201%2C901208%2C929117%2C929123%2C929121%2C929915%2C929906%2C929907%2C925714%2C929919%2C929119%2C931202%2C932802%2C912512%2C912518%2C911416%2C906906%2C904476%2C930807%2C919373%2C906836%2C933701%2C912711%2C929606%2C910075&ms=au&source=youtube&expire=1370466652&newshard=yes&sparams=cp%2Cid%2Cip%2Cipbits%2Citag%2Cratebypass%2Csource%2Cupn%2Cexpire&ipbits=8&mv=m&quality=hd720&fallback_host=tc.v4.cache8.c.youtube.com&signature=7552C571FD9449F2C70329F68BF09D33AD4CF7DB";

int main( void )
{
    FILE *fp;

    printf("Testing if fopen() works with a very long name...\n");

    errno = 0;
    fp = fopen( name, "r");
    printf("%s\n", ( !fp && errno == ENAMETOOLONG ) ? "PASSED" : "FAILED");

    return !!fp;
}
