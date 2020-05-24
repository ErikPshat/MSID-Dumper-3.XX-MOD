@echo off
PATH = C:\pspsdk\bin;
make clean && make

if exist EBOOT.PBP (
if not exist "MSID Dumper 3.XX MOD RUS" md "MSID Dumper 3.XX MOD RUS"
move /y EBOOT.PBP "MSID Dumper 3.XX MOD RUS"
copy /y "..\res\mdumper.prx" "MSID Dumper 3.XX MOD RUS"
echo.
)
if exist "MSID Dumper 3.XX MOD RUS\EBOOT.PBP" (
echo.     Well Done^!
) else (
echo.     ERROR^!
)
echo.
pause