
  TETRIS Queen - Version 1.3
  Copyright (C) 1999, 2000, 2001 by David A. Capello
  --------------------------------------------------------------------------

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


  1. INDEX
  --------------------------------------------------------------------------

   1. Index
   2. Introduction
   3. Requirements
   4. Configuration
   5. Controls
   6. Menus
   7. Playing
   8. Programming
   9. Faq
  10. Credits


  2. INTRODUCTION
  --------------------------------------------------------------------------

  I am David A. Capello and I will introduce you to one of so many clones of
  the original TETRIS Arcade game created by TEAM TETRIS in 1988. The game
  is not an exact copy of the old TETRIS but shares the same concept created
  by Alexey Pajitnov in it's good old days.

  To add a little more emotion to the game, I added a new game mode which
  you can fin only in TETRIS Queen: "destroyer". And of course, the "Queen"
  title is given because the game is a whole tribute to the famous british
  music band: Queen.

  For more information and updates about the game, you can visit the
  official TETRIS Queen website at:

    http://qtetris.sourceforge.net

  Bye, and I await your feedback.


  3. REQUIREMENTS
  --------------------------------------------------------------------------

  These are the minimum requirements you need to play TETRIS Queen:

    - 486 DX (you may get to run it on a 386);
    - 4 MB of RAM (8 MB would be better, 16 MB are really nice);
    - VGA card;
    - MS-DOS (or UNIX);
    - Keyboard;

  Here you have the recommended requirements:

    - Pentium 166 Mhz or better;
    - 32 MB of RAM;
    - VGA card;
    - Sound Blaster;
    - Windows 95/98 (or GNU/Linux);
    - Keyboard and two joysticks;


  4. CONFIGURATION
  --------------------------------------------------------------------------

  All the game's configuration can be tuned by the `qtetris.cfg' file, you
  shouldn't touch anything outside of the [tetris] section, where you can
  find the specific configuration of the game and not the configuration of
  the system.

  On the other hand, for "quick" configurations, you can use the
  commandline, where you can start the game with different options:

    qtetris [OPTIONS]

  Available options are:

    -i, --nointro   doesn't display the introduction
    -s, --nosound   doesn't install sounds
    -j, --nojoy     doesn't install joystick
    -?, --help      shows the program's help

  For example, if you want to play without sound (because you are already
  hearing to your favourite MP3 files with another program), you can start
  the game like this:

    qtetris -s


  5. CONTROLS
  --------------------------------------------------------------------------

  The general keys of the game are:

    ESC       quits the game, returns to the menus, and does anything
              to cancel things;
    CTRL+Q    aborts the game and returns to the operative system;
    F11       pauses the game;
    F12       makes a BMP screenshot of the game;

  Keys for some extra functions while you are playing:

    F1        lower the digital sound volume;
    F2        increase the digital sound volume;
    F3        lower the music sound volume;
    F4        increase the music sound volume;
    F5        jumps to the previous song;
    F6        jumps to the next song;
    F7        jumps to a random song;

  The DEFAULT keys for each player are:

    PLAYER1:       PLAYER2:
    Left           A            move the block to the left;
    Right          D            move the block to the right;
    Down           S            drops the block quickly;
    Delete         1            rotate block to the left;
    End            2            rotate block to the right;

  The default keys can be changed from the menu OPTIONS/CONTROLS/PLAYER X.
  For example, if you want to use joystick's one first button to move
  player's one block down:

    - go to "OPTIONS/CONTROLS/PLAYER 1";
    - select option "DOWN: ...", and press ENTER;
    - now, press joystick's 1 first button;
    - done, now, if you want to recover the default values for all keys, you
      only have to choose the "RESET" option found on the same menu;

  IMPORTANT NOTE WHEN ENTERING A NEW RECORD: when you have to enter a new
  record, you will see three letters, using the keys to move the block to
  the sides you can go changing the first, second and third letter, using
  the rotate buttons you can change the selected letter, and pressing down
  you accept it. Take care whith this operation, as you might enter unwanted
  initials.


  6. Menus
  --------------------------------------------------------------------------

  MAIN:
  |
  +- 1 PLAYER:       start the game for one player (you first will have to
  |                  select a game mode);
  |
  +- 2 PLAYERS:      start the game for two players;
  |
  +- HALL OF FAME:   shows the best scores;
  |
  +- OPTIONS:
  |  |
  |  +- SOUND:       modify the digital sound volume;
  |  |
  |  +- MUSIC:       modify the music sound volume;
  |  |
  |  +- SOUND TEST:
  |  |  |
  |  |  +- LEFT:     plays a sound through the left speaker;
  |  |  |
  |  |  +- CENTRE:   plays a sound through both speakers;
  |  |  |
  |  |  +- RIGHT:    plays a sound through the right speaker;
  |  |  |
  |  |  +- FLIP PAN: flips the sound orientation (if sounds play from
  |  |               through the wrong speakers, use this option and try
  |  |               again);
  |  |
  |  +- CONTROLS:
  |  |  |
  |  |  +- PLAYER 1: shows player's one button configuration;
  |  |  |
  |  |  +- PLAYER 2: shows player's two button configuration;
  |  |  |
  |  |  +- CALIBRATE
  |  |     JOYSTICK: shows a screen where you can calibrate both joysticks;
  |  |
  |  |
  |  +- RESET HIGH
  |     SCORES:      erases the scores, changing them for the default values
  |                  (you will first have to choose the mode's high scores
  |                  you want to delete);
  |
  +- CREDITS:        shows the game's credits;
  |
  +- EXIT:           exits the game and returns to the operative system;


  7. PLAYING
  --------------------------------------------------------------------------

  TETRIS Queen's different game modes are:

  1 PLAYER:

    CLASSIC:

      The classic TETRIS mode. The main purpose of the game is to make
      complete lines with the falling blocks, and if you do two, three or
      four lines at the same time, you will get more points. Here you have
      the points table:

        SINGLE:  1 line    10 points
        DOUBLE:  2 lines   50 points
        TRIPLE:  3 lines   200 points
        TETRIS:  4 lines   500 points

    DESTROYER:

      Just like the classic, but this time some of the falling blocks will
      contain a bomb, none, or will be full of them. When you complete a
      line, all the bombs of that line will activate themselves, exploting
      and throwing away all the nearest blocks. If the expansive wave hits
      another bomb, this will also explode, creating thus "chain reactions".

      But this is not all, if you join 4 bombs, you will make a Mega-Bomb,
      which will have a bigger explosive wave.

      Exploting bombs will also give points, but only if the bomb was in the
      same line you completed, bombs hit by expansive waves don't count.

      The points are:

        BOMB:       10 points
        MEGA-BOMB:  50 points

      And last, to make the game more challenging, every 10 seconds you will
      be rewarded with a "bad" line, so you will have to be quick.

  2 PLAYERS:

    CLASSIC:
    DESTROYER:

      Just like classic one player mode, but completed lines will be
      accumulated, and every 10 seconds, the other player will recieve a bad
      line for one accumulated line. Evenly, if the other player continues
      to complete lines, he can diminish the effect, to the point that if he
      completes more lines that you, you would be added "bad lines".


  8. PROGRAMMING
  --------------------------------------------------------------------------

  If you are really interested in programming TETRIS Queen, you are allowed
  to freeely read, modify and extend the source code in any way you like
  (that is, if you anderstand anything :-).

  First, there are two ways of getting the source code, one through the
  "qtetris*-src.tar.gz" package, or directly from the CVS repository.
  Anyway, if you want to compile the game, you will always need the data
  source, that is, the "qtetris*-dat.tar.gz" package, and this is because
  when you build the game, the "qtetris.dat" file has to be generated
  automatically by the process.

  To compile successfully the game, before anything else, you should have
  Allegro, and if you have Allegro you are suposed to know how to compile
  it. Now, the process to build TETRIS Queen is exactly the same (or
  practically the same). Go to the directory `qtetris/src', and run one of
  the files fixdjgpp, fixmingw, fixmsvc, fixunix or fixwat (depending on
  your compiler and platform). Then run `make depend' and finally `make'
  from the commandline. If everything goes well, you will have the game
  ready to play, and if not, you will have to warn me, since I didn't test
  some versions (ie: the Watcom port).

  On the other hand, some versions have problems to create the datafile
  from data.h, so a good way and option is to build everything like this:

    fix*****
    make depend
    make data.h
    make

  You can also use options like `make DEBUGMODE=1' to generate code suitable
  for debugging TETRIS Queen, or `make STATICLINK=1' to link against static
  versions of Allegro (under Windows or Unix) and avoid using dynamic
  libraries (like .DLLs or .so files).


  9. FAQ
  --------------------------------------------------------------------------

  P: What's new in this version?
  R: A little bit more documentation and different internal improvements to
     allow building the game under other platforms (MS-DOS, Windows, Unix,
     GNU/Linux).

  P: Will you release more versions?
  R: Not now, but who knows, I had some plans for TETRIS Queen II, but...

  P: Did you take 3 years to write a simple TETRIS?
  R: The truth is that it was one and without motivation :-) The main
     culprit was that I changed my mind every day (something which shouldn't
     be done if you make a good previous design :-), and I didn't want to
     program something without much future (nobody get's suprised by a
     simple tetris), but now I only write maintenance versions (if Allegro
     changes, TETRIS too) and that's why I keep adding years (ie: 2001).
     Anyway, I don't understand why are you so interested in my delay, when
     after all the game is done.

  P: The music has low quality ¿How can I improve them?
  R: The only way, for the moment, is to download some WAVETABLES to
     substitute the "poor" MIDI sounds with "powerfull" high quality samples
     included in these wavetable files. You can find some links to them from
     the Allegro web page itself:

       http://www.talula.demon.co.uk/allegro/digmid.html

  P: ¿How do I uncompress *.tar.gz files?
  R: Using the gzip and tar programs, which you can find in the following
     FTP with the names gzp*b.zip y tar*.zip:

       ftp://ftp.demon.co.uk/pub/mirrors/simtelnet/gnu/djgpp/v2gnu/

     Once you have them, you can run:

       tar -xzvf ase*.tar.gz

  P: ¿Where do I get the CVS tool?
  R: The Windows CVS (Concurrent Versions Systems) version is at:

       ftp://ftp.cvshome.org/pub/cvs-1.11/windows/cvs1-11.zip

     For other versions of this program you can go to:

       http://www.cvshome.org

  P: How do I get the source code from the CVS repository?
  R: Once you have the cvs tool, follow these steps:

     1) You have to login anonymously to the repository with:

        cvs -d :pserver:anonymous@cvs.qtetris.sourceforge.net:/cvsroot/qtetris login

     2) Now checkout the module, getting a "fresh" TETRIS Queen version:

        cvs -z3 -d :pserver:anonymous@cvs.qtetris.sourceforge.net:/cvsroot/qtetris checkout qtetris

     3) Once you have done this, every time you want to update your local
        copy, you only have to run from the `qtetris/' directory:

        cvs update

     IMPORTANT: when you get the CVS version, don't delete the CVS
     directories or their contents, they are used internally by the program.

  P: I've got problems and there's not much documentation :-(
     Where can I get more help?
  R: You can send me an email to my own address:

       davidcapello@yahoo.com

     If you find a bug, a documentation mistake or something weird or
     confusing, don't hesitate to ask me and warn me about it.


  10. CREDITS
  --------------------------------------------------------------------------

  Programmer, graphics, sounds, documentation, tester, and other things:

    David A. Capello (davidcapello@yahoo.com)
    http://come.to/davidcapello/

  Translation of the documentation to english:

    Grzegorz Adam Hankiewicz (gradha@iname.com), really thank you for the
    uninterested colaboration (for the moment :-) of translating the
    documentation and loosing time with such a horrible task. Really thanks.
    http://gradha.infierno.org

  MIDI songs and album images:

    All the Queen songs in the game, and all album covers where downloaded
    from:

      http://www.queentrivia.mcmail.com/

    Here you will find a link to MIDI songs, where you will see the authors
    of each song.


  SPECIAL THANKS TO:
  --------------------------------------------------------------------------

  Shawn Hargreaves (shawn@talula.demon.co.uk) and the hundreds of people of
  the whole world who helped him writting the Allegro library.
  http://www.talula.demon.co.uk/allegro/

  DJ Delorie and all the people who created the DJGPP compiler.
  http://www.delorie.com/djgpp/

  Robert Höhne (robert.hoehne@gmx.net), Salvador Eduardo Tropea (SET)
  (salvador@inti.gov.ar), Andris Pavenis (pavenis@lanet.lv), and more people
  who contributed to RHIDE.
  http://www.lanet.lv/~pavenis/rhide.html

  Charles W Sandmann (sandmann@clio.rice.edu) for the DOS' DPMI server.

  Alexey Pajitnov for making one of the most addictive games of the history.

  And of course, thanks to Freddie Mercury,  Roger Taylor, John Deacon, and
  Brian May, for making the best music of all times.

  --------------------------------------------------------------------------
                          Copyright (C) 1999, 2000, 2001 by David A. Capello
