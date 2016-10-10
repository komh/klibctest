eval '(exit $?0)' && eval 'exec perl -w "$0" ${1+"$@"}'
  & eval 'exec perl -w "$0" $argv:q'
    if 0;

my $v='spawn-4.sh: hello';
print $v, "\n";
