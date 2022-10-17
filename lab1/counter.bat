echo off
runthis
Tasklist | find /v /n /c "" >> D:\OS\forkbomb\CountOfProcess.txt
goto runthis