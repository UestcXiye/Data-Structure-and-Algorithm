@echo off
call clean.bat
Heap.exe data.txt
REM dot.exe -Tpng heapT.gv -o dotheapT.png && dotheapT.png 
REM dot.exe -Tpng heapA.gv -o dotheapA.png && dotheapA.png 
pause
