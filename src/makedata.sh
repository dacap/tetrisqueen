#! /bin/sh
# Copyright (C) 1999, 2000, 2001 by David A. Capello

datautil=dat
datafile=../qtetris.dat
headfile=data.h

if [ -f $datafile ] ; then rm $datafile ; fi

$datautil -t BMP -a $datafile data/*.bmp
$datautil -t PAL -a $datafile data/palette.bmp data/finalpal.bmp
$datautil -t FONT -a $datafile data/fontgame.pcx data/fontbig.pcx
$datautil -t SAMP -a $datafile data/*.wav
$datautil -t MIDI -a $datafile data/*.mid

$datautil -t BMP -a data/bgbmp.dat data/bg*.pcx
$datautil -t FILE -a $datafile data/bgbmp.dat
rm -f data/bgbmp.dat

$datautil -t PAL -a data/bgpal.dat data/bg*.pcx
$datautil -t FILE -a $datafile data/bgpal.dat
rm -f data/bgpal.dat

$datautil -t FILE -a $datafile data/*.dat

$datautil -h $headfile -c1 $datafile
