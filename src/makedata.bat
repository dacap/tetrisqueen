@echo off
REM Copyright (C) 1999, 2000, 2001 by David A. Capello

set DAT=%ALLEGRO%\tools\dat.exe
set DATAFILE=..\qtetris.dat
set HEADFILE=data.h

if exist %DATAFILE% del %DATAFILE%

%DAT% -t BMP  -a %DATAFILE% data\*.bmp
%DAT% -t PAL  -a %DATAFILE% data\palette.bmp data\finalpal.bmp
%DAT% -t FONT -a %DATAFILE% data\fontgame.pcx data\fontbig.pcx
%DAT% -t SAMP -a %DATAFILE% data\*.wav
%DAT% -t MIDI -a %DATAFILE% data\*.mid

%DAT% -t BMP  -a data\bgbmp.dat data\bg*.pcx
%DAT% -t FILE -a %DATAFILE% data\bgbmp.dat
del data\bgbmp.dat

%DAT% -t PAL  -a data\bgpal.dat data\bg*.pcx
%DAT% -t FILE -a %DATAFILE% data\bgpal.dat
del data\bgpal.dat

%DAT% -t FILE -a -c2 %DATAFILE% data\*.dat

%DAT% -h %HEADFILE% %DATAFILE%

