@echo off
rem Copyright (C) 1999, 2000, 2001  David Capello

set datautil=%ALLEGRO%\tools\dat.exe
set datafile=..\qtetris.dat
set headfile=data.h

if exist %datafile% del %datafile%

%datautil% -t BMP -a %datafile% data\*.bmp
%datautil% -t PAL -a %datafile% data\palette.bmp data\finalpal.bmp
%datautil% -t FONT -a %datafile% data\fontgame.pcx data\fontbig.pcx
%datautil% -t SAMP -a %datafile% data\*.wav
%datautil% -t MIDI -a %datafile% data\*.mid

%datautil% -t BMP -a data\bgbmp.dat data\bg*.pcx
%datautil% -t FILE -a %datafile% data\bgbmp.dat
del data\bgbmp.dat

%datautil% -t PAL -a data\bgpal.dat data\bg*.pcx
%datautil% -t FILE -a %datafile% data\bgpal.dat
del data\bgpal.dat

%datautil% -t FILE -a %datafile% data\*.dat

%datautil% -h %headfile% -c1 %datafile%
