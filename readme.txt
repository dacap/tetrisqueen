
  TETRIS Queen - Version 1.3
  Copyright (C) 1999, 2000, 2001 by David A. Capello

  -------------------------------------------------------------------------

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


  INDEX
  -------------------------------------------------------------------------

     I. Introduction
    II. Requirements
   III. Configuration
    IV. Arguments
     V. Controls
    VI. Menus
   VII. Playing
  VIII. Faq
    IX. Credits


  I. INTRODUCTION
  -------------------------------------------------------------------------

  I am David A. Capello and I will introduce you to one of so many
  clones of the original TETRIS Arcade game created by TEAM TETRIS in
  1988. The game is not an exact copy of the old TETRIS but shares the
  same concept created by Alexey Pajitnov. And it also features an
  extra mode invented by me. To all of this I added the excelent
  music performed by QUEEN, WITH MORE THAN 30 OF IT'S SONGS.

  THIS GAME IS FREEWARE, which means that YOU DON'T PAY ANYTHING for it
  and you can copy it to any friend, or better said, you HAVE TO COPY it
  to all your friends.

  But of course, every silver lining has a cloud, and the game is free
  but IT COMES WITHOUT GUARANTEE, this is, if your machine or head
  explode while you are using it, you won't be able to blame me for that.
  Use it at your own risk.

  Also, if you want the source code of the game (C for the DJGPP
  compiler with Allegro) you can download it from my WEB PAGE (see
  CREDITS below).


  II. REQUIREMENTS
  -------------------------------------------------------------------------

  These are the minimum requirements you need to play TETRIS Queen:
  - 486 DX (you may get to run it on a 386...);
  - 4 MB of RAM (I don't really know if it will work,
                 you better have 8... but... with 16 you are safe);
  - VGA card;
  - DOS;
  - Keyboard;

  Here you have the recommended requirements:
  - Pentium 166 Mhz or better;
  - 32 MB of RAM;
  - VGA card;
  - Sound Blaster;
  - Windows 95/98;
  - Keyboard and two joysticks;


  III. CONFIGURATION
  -------------------------------------------------------------------------

  All the game's configuration can be tuned by the qtetris.cfg file, you
  shouldn't touch anything outside of the [tetris] section, where you
  can find the specific configuration of the game and not the
  configuration of the system.


  IV. ARGUMENTS
  -------------------------------------------------------------------------

  From the commandline, you can start the game with different options:

     qtetris [OPTIONS]

  Opciones:
    -i, --nointro   doesn't display the introduction
    -s, --nosound   doesn't install sounds
    -j, --nojoy     doesn't install joystick
    -?, --help      shows the program's help

  Example:
  To start without sounds

    qtetris --nosound


  V. CONTROLS
  -------------------------------------------------------------------------

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
    Supr/Delete    1            rotate block to the left;
    Fin/End        2            rotate block to the right;

  The default keys can be changed from the menu
  OPTIONS/CONTROLS/[PLAYER 1 or PLAYER 2].
  In this menu, pressing ENTER will allow you to reconfigure a key.
  For example, if you want to use joystick's one first button to
  move player's one block down:

    - go to OPTIONS/CONTROLS/PLAYER 1;
    - select option "DOWN: ...", and press ENTER;
    - now, press joystick's 1 first button;
    - done, now, if you want to recover the default
      values for all keys, you only have to choose the
      "RESET" option found on the same menu;

  IMPORTANT NOTE WHEN ENTERING A NEW RECORD:
  When you have to enter a new record, you will see three
  letters, using the keys to move the block to the sides you
  can go changing the first, second and third letter, using
  the rotate buttons you can change the selected letter, and
  pressing down you accept it. Take care whith this operation,
  as you might enter unwanted initials.


  VI. Menus
  -------------------------------------------------------------------------

  MAIN:
    1 PLAYER             start the game for one player (you first
                         will have to select a game mode);
    2 PLAYERS            start the game for two players;
    HALL OF FAME         shows the best scores;
    OPTIONS              go to the options menu to reconfigure the game;
    CREDITS              shows the game's credits;
    EXIT                 exits the game and returns to the OS;

  OPTIONS:
    SOUND: |||||||||     modify the digital sound volume;
    MUSIC: ||||||        modify the music sound volume;
    SOUND TEST           perform a sound test;
    CONTROLS             shows the screen which allows to redefine keys
                         and calibrate the joystick;
    RESET HIGH SCORES    erases the scores, changing them for the default
                         values (you will first have to choose the mode's
                         high scores you want to delete);

  SOUND TEST:
    LEFT                 plays a sound through the left speaker;
    CENTRE               plays a sound through the right speaker;
    RIGHT                plays a sound through both speakers;
    FLIP PAN             flips the sound orientation (if sounds play from
                         through the wrong speakers, use this option and
                         try again);

  CONTROLS:
    PLAYER 1             shows player's one button configuration
    PLAYER 2             shows player's two button configuration
    CALIBRATE JOYSTICK   shows a screen where you can calibrate both
                         joysticks;


  VII. PLAYING
  -------------------------------------------------------------------------

  Here I will explain you how to play the different game's modes:
  
  1 PLAYER:
  
    CLASSIC:
      The classic TETRIS mode.
      The main purpose of the game is to make complete lines
      with the falling blocks, and if you do two, three or
      four lines at the same time, you will get more points.
      Here you have the points table:
        Lines      Name       Points
        ------     ------     -------
          1        SINGLE       10
          2        DOUBLE       50
          3        TRIPLE       200
          4        TETRIS       500

    DESTROYER:
      Just like the classic, but this time some of the falling
      blocks will contain a bomb, none, or will be full of them.
      When you complete a line, all the bombs of that line will
      activate themselves, exploting and throwing away all the
      nearest blocks. If the expansive wave hits another bomb,
      this will also explode, creating thus "chain reactions".
      But this is not all, if you join 4 bombs, you will
      make a Mega-Bomb, which will have a bigger explosive
      wave.
      Exploting bombs will also give points, but only if the
      bomb was in the same line you completed, bombs hit by
      expansive waves don't count. The points are:
      Name           Points
      ------         ------
      BOMB           10
      MEGA-BOMB      50

      And last, to make the game more challenging, every
      10 seconds you will be rewarded with a "bad" line,
      so you will have to be quick...


  2 PLAYERS:
  
    CLASSIC:
    DESTROYER:
      Just like classic one player mode, but completed
      lines will be accumulated, and every 10 seconds,
      the other player will recieve a bad line for one
      accumulated line.
      Evenly, if the other player continues to complete
      lines, he can diminish the effect, to the point
      that if he completes more lines that you, you
      would be added "bad lines".


  VIII. FAQ
  -------------------------------------------------------------------------

  P: What's new in this version?
  R: A little bit more documentation and different internal
     improvements to allow building the game under other platforms
     (MS-DOS, Windows, Unix, Linux).

  P: Will you release more versions?
  R: Not now, but who knows, I had some plans for TETRIS Queen II,
     but...

  P: Did you take 3 years to write a simple TETRIS?
  R: The truth is that it was one and without motivation :-)
     The main culprit was that I changed my mind every day with new
     ideas and I didn't want to program something without much future
     (nobody get's suprised by a simple tetris), but well, now I only
     write maintenance versions (if Allegro changes, TETRIS too) and
     that's why I keep adding years (ie: 2001).

  P: I've got the source code, I want to build TETRIS, but I can't.
  R: Before anything else, you should have Allegro, and if you have
     Allegro you are suposed to know how to compile it. Now, the
     process to build TETRIS Queen is exactly the same. Go to the
     directory `qtetris/src', and run one of the files fixdjgpp,
     fixmingw, fixmsvc, fixunix or fixwat (depending on your compiler
     and platform).
     Then run `make depend' and finally `make' from the commandline.
     If everything goes well, you will have the game ready to play,
     and if not, you will have to warn me, since I didn't test some
     versions (ie: the Watcom port).

  P: How can I obtain a debug version of the game?
  R: Instead of running `make' without switches, you can use
     `make DEBUGMODE=1'.

  P: I've got problems and there's not much documentation :-(
     Where can I get more help?
  R: You can send me an email to my own address:

       davidcapello@yahoo.com

     If you find a bug, a documentation mistake or something weird
     or confusing, don't hesitate to ask me and warn me about it.


  IX. CREDITS
  -------------------------------------------------------------------------

  Programmer, graphics, sounds,
  documentation, tester, and other things:

    David Alfredo Capello <davidcapello@yahoo.com>
    http://come.to/davidcapello/

  Translation of the documentation to english:

    Grzegorz Adam Hankiewicz <gradha@iname.com>
    http://welcome.to/gogosoftware/

  MIDI songs and album images:

    All the Queen songs in the game, and all album covers
    where downloaded from:

      http://www.queentrivia.mcmail.com/

    Here you will find a link to MIDI songs, where you will
    see the authors of each song.


  SPECIAL THANKS TO:
  -------------------------------------------------------------------------

    Shawn Hargreaves <shawn@talula.demon.co.uk>
    and the hundreds of people of the whole world who
    helped him writting the Allegro library
      http://www.talula.demon.co.uk/allegro/

    DJ Delorie and all the people who created the best
    C/C++ compiler: DJGPP
      http://www.delorie.com/djgpp/

    Robert Höhne <robert.hoehne@gmx.net>,
    Salvador Eduardo Tropea (SET) <salvador@inti.gov.ar>,
    Andris Pavenis <pavenis@lanet.lv>,
    and more people who contributed to RHIDE
      http://www.lanet.lv/~pavenis/rhide.html

    Charles W Sandmann <sandmann@clio.rice.edu>
    for the DOS' DPMI server

    Alexey Pajitnov
    for making one of the most addictive games
    of the history.

    And of course, thanks to Freddie Mercury,
    Roger Taylor, John Deacon, and Brian May, for
    making the best music of all times.


  -------------------------------------------------------------------------
                         Copyright (C) 1999, 2000, 2001 by David A. Capello

