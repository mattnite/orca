
set INCLUDES=/I ..\..\src /I ..\..\src\util /I ..\..\src\platform /I ../../ext

cl /we4013 /Zi /Zc:preprocessor /std:c11 %INCLUDES% main.c /link /LIBPATH:../../bin milepost.dll.lib /out:../../bin/test_open_dialog.exe
copy ..\..\build\bin\orca.dll bin