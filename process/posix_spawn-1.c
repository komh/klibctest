#include <stdio.h>
#include <fcntl.h>
#include <spawn.h>
#include <errno.h>

int main( void )
{
    pid_t pid;
    char *path = "pwd.exe";
    char *argv[] = { path, NULL };
    posix_spawn_file_actions_t actions;
    int err;
    int failed;
    int errors = 0;

    printf( "Testing if posix_spawn() and posix_spawnp() are swapped...\n" );

    posix_spawn_file_actions_init( &actions );
    posix_spawn_file_actions_addopen( &actions, 1, "/dev/nul", 0, O_WRONLY );

    err = posix_spawn( &pid, path, &actions, NULL, argv, NULL );
    failed = err == 0;
    printf( "%s: posix_spawn() = %d(%d)\n",
            failed ? "FAILED" : "PASSED", err, ENOENT );
    errors += failed;

    err = posix_spawnp( &pid, path, &actions, NULL, argv, NULL );
    failed = err != 0;
    printf( "%s: posix_spawnp()= %d(%d)\n",
             failed ? "FAILED" : "PASSED", err, 0 );

    posix_spawn_file_actions_destroy( &actions );

    return errors != 0;
}
