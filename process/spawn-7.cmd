/* spawn-7.cmd */
parse arg args;


if args == 'hello' then
do
    sResult = 'PASSED:'
    iFailed = 0;
end
else
do
    sResult = 'FAILED:'
    iFailed = 1;
end

sResult = sResult 'args = [' || args || '](hello)'

say sResult;

exit iFailed;

