#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <process.h>
#include <sys/stat.h>

#define FILE1 "inode-1-FILE1"
#define FILE2 "inode-1-FILE2"

int main( void )
{
    int fd;
    struct stat st1, st2;
    int failed = 1;

    printf("Testing inode is unique even if copied with non-kLIBC programs...\n");

    fd = open( FILE1, O_RDWR | O_CREAT );
    if( fd == -1 )
    {
        perror("open");
        return 1;
    }
    close( fd );

    if( system("cmd /c copy " FILE1 " " FILE2 ) == -1 )
    {
        perror("system");
        goto out;
    }

    if( stat( FILE1, &st1 ) == -1 || stat( FILE2, &st2 ) == -1 )
    {
        perror("stat");
        goto out;
    }

    failed = st1.st_ino == st2.st_ino;
    printf("%s: inode1 = %Lx, inode2 = %Lx(!%Lx)\n",
           failed ? "FAILED" : "PASSED", st1.st_ino, st2.st_ino, st1.st_ino );

out:
    unlink( FILE1 );
    unlink( FILE2 );

    return failed;
}
