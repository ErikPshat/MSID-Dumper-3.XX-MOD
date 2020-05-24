@echo off
PATH = C:\pspsdk\bin;
make clean && make

if exist EBOOT.PBP (
if not exist "MSID Dumper 3.XX MOD ENG" md "MSID Dumper 3.XX MOD ENG"
move /y EBOOT.PBP "MSID Dumper 3.XX MOD ENG"
copy /y "..\res\mdumper.prx" "MSID Dumper 3.XX MOD ENG"
echo.
)
if exist "MSID Dumper 3.XX MOD ENG\EBOOT.PBP" (
echo.     Well Done^!
) else (
echo.     ERROR^!
)
echo.
pause