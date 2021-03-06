TETRIS Queen - Versi�n 1.4
Copyright (C) 1999, 2000, 2001 por David A. Capello
---------------------------------------------------

1. �NDICE
---------

   1. �ndice
   2. Introducci�n
   3. Requerimientos
   4. Configuraci�n
   5. Controles
   6. Men�s
   7. Jugando
   8. Programando
   9. Faq
  10. Cr�ditos


2. INTRODUCCI�N
---------------

Soy David A. Capello y le presento uno de los tantos clones del TETRIS
original de Arcade creado por el TEAM TETRIS en el a�o 1988. El juego no
es una r�plica id�ntica del viejo TETRIS pero s� tiene el mismo concepto
creado por Alexey Pajitnov por aquellos viejos tiempos.

Para ponerle un poco m�s de emoci�n a esto, inclu� un nuevo modo de juego
exclusivo de TETRIS Queen: "el destructor" (� "destroyer"). Y dem�s est�
decir, que el "Queen" del t�tulo se debe nada m�s y nada menos a que el
juego es un total tributo a la famosa banda inglesa de m�sica: Queen.

Para m�s informaci�n y actualizaciones del juego, puede visitar el sitio
oficial de TETRIS Queen en:

  http://qtetris.sourceforge.net

Adi�s y espero sus comentarios.


3. REQUERIMIENTOS
-----------------

Estos son los requerimientos m�nimos que necesita TETRIS Queen:

  - 486 DX (podr�a que funcione en una 386);
  - 4 MB de RAM (mejor ser�an 8 megas, y con 16 est�s hecho);
  - Tarjeta VGA;
  - DOS (� UNIX);
  - Teclado;

Aqu� tiene los requerimientos recomendados:

  - Pentium 166 Mhz o superior;
  - 32 MB de RAM;
  - Tarjeta VGA;
  - Sound Blaster;
  - Windows 95/98 (� GNU/Linux);
  - Teclado y dos joysticks;


4. CONFIGURACI�N
----------------

Toda la configuraci�n del juego se encuentra en el archivo qtetris.cfg,
usualmente no deber�a tocar nada aqu� m�s que la secci�n [tetris] donde
se encuentra la configuraci�n espec�fica del juego y no la del sistema.

Por otro lado, para otras configuraciones "r�pidas", puede utilizar la
l�nea de comandos, donde podr� iniciar el juego con diferentes opciones:

  qtetris [OPCIONES]

Las opciones disponibles son:

  -r, --resolution ANCHO ALTO     usar una resoluci�n especial (en 8 bpp)
  -i, --nointro                   no mostrar la introducci�n
  -s, --nosound                   no instalar el sonido
  -j, --nojoy                     no instalar el joystick
  -m, --merge ARCHIVO_HOF         adjuntar otro "sal�n de la fama" al actual
  -h, --help                      visualizar la ayuda del programa (en ingl�s)
      --version                   mostrar informaci�n sobre la versi�n

Por ejemplo, si desea iniciar sin instalar el sonido (ya que est�
escuchando sus MP3s favoritos con otro programa), y no quiere la
introducci�n, puede iniciar el juego de la siguiente manera:

  qtetris -is


5. CONTROLES
------------

Las teclas generales en el juego son:

  ESC       sale del juego, vuelve en los men�s, y realiza cualquier cosa
            para cancelar algo;
  CTRL+Q    aborta el juego y vuelve al sistema operativo;
  F11       pone pausa;
  F12       captura la pantalla guard�ndola como un archivo BMP;

Las teclas para algunas funciones extras cuando se est� jugando:

  F1        baja el volumen del sonido;
  F2        sube el volumen del sonido;
  F3        baja el volumen de la m�sica;
  F4        sube el volumen de la m�sica;
  F5        salta a la m�sica anterior;
  F6        salta a la pr�xima m�sica;
  F7        cambia la m�sica por una al azar;

Las teclas POR DEFECTO de cada jugador son:

  PLAYER1:       PLAYER2:
  Izquierda      A            mueve la pieza hacia la izquierda;
  Derecha        D            mueve la pieza hacia la derecha;
  Abajo          S            baja la pieza r�pidamente;
  Supr/Delete    1            rota la pieza hacia la izquierda;
  Fin/End        2            rota la pieza hacia la derecha;

Las teclas de cada jugador, pueden ser reconfiguradas desde el men�
OPTIONS/CONTROLS/PLAYER X. Por ejemplo, si desea mover la pieza hacia
abajo del jugador 1 con el bot�n n�mero 1 del primer joystick conectado
a la computadora:

  - entre en "OPTIONS/CONTROLS/PLAYER 1";
  - seleccione la opci�n "DOWN: ...", y presione ENTER;
  - luego, presione la palanca (stick direccional) del joystick 1 hacia
    abajo;
  - y listo, ahora, si quiere volver a los valores anteriores de todas las
    teclas, solamente debe seleccionar la opci�n "RESTORE" que se encuentra
    en este mismo men�;

NOTA IMPORTANTE AL INGRESAR UN NUEVO RECORD: cuando hay que ingresar una
nueva puntuaci�n, le aparecer�n tres letras, usando las teclas para mover
la pieza hacia los costados, puede ir cambiando entre la 1era, 2da y 3er
letra, utilizando los botones para rotar, puede cambiar la letra actual,
y pulsando hacia abajo acepta. Tenga mucho cuidado al hacer esta
operaci�n, ya que podr�a colocar iniciales no deseadas.


6. MEN�S
--------

  MAIN (men� principal):
  |
  +- 1 PLAYER:       comienza un juego con un jugador (antes deber� elegir
  |                  el modo de juego);
  |
  +- 2 PLAYERS:      comienza un juego con dos jugadores;
  |
  +- HALL OF FAME:   muestra las mejores puntuaciones;
  |
  +- OPTIONS (opciones):
  |  |
  |  +- SOUND:       modifica el volumen del sonido;
  |  |
  |  +- MUSIC:       modifica el volumen de la m�sica;
  |  |
  |  +- SOUND TEST (prueba de sonido):
  |  |  |
  |  |  +- LEFT:     reproduce un sonido que se escucha desde la izquierda;
  |  |  |
  |  |  +- CENTRE:   reproduce un sonido que se escucha desde el centro;
  |  |  |
  |  |  +- RIGHT:    reproduce un sonido que se escucha desde la derecha;
  |  |  |
  |  |  `- FLIP PAN: invierte la orientaci�n del sonido (si los sonidos no
  |  |               salen correctamente por los lados que se indican,
  |  |               utilice esta opci�n y vuelva a probar);
  |  |
  |  +- CONTROLS (controles):
  |  |  |
  |  |  +- PLAYER 1: muestra la configuraci�n de los botones del 1er jugador;
  |  |  |
  |  |  +- PLAYER 2: muestra la configuraci�n de los botones del 2do jugador;
  |  |  |
  |  |  `- CALIBRATE
  |  |     JOYSTICK: muestra una pantalla donde se pueden calibrar los dos
  |  |               joysticks;
  |  |
  |  `- RESET HIGH
  |     SCORES:      borra las puntuaciones, restaur�ndolas por los valores
  |                  por defecto (antes deber� elegir la tabla de records
  |                  espec�fica del modo de juego que quiera borrar);
  |
  +- CREDITS:        muestra los cr�ditos del juegos;
  |
  `- EXIT:           sale del juego y vuelve al sistema operativo;


7. JUGANDO
----------

Los diferentes modos de juego de TETRIS Queen son:

1 PLAYER (un jugador):

  CLASSIC (cl�sico):

    El cl�sico modo de juego de todo TETRIS. El principal objetivo es ir
    haciendo l�neas con las piezas que se le van dando, si se hacen dos,
    tres o hasta cuatro l�neas al mismo tiempo nos dar� m�s puntaje. Aqu�
    tiene la lista de puntajes:

      SINGLE:  1 l�nea   10 puntos
      DOUBLE:  2 l�neas  50 puntos
      TRIPLE:  3 l�neas  200 puntos
      TETRIS:  4 l�neas  500 puntos

  DESTROYER (destructor):

    Igual que el cl�sico, solamente que las piezas ahora tendr�n una
    bomba, ninguna, o estar�n llenas de bombas. Al hacer una l�nea, se
    activar�n todas las bombas que se encuentren en la misma, explotando y
    tirando, fuera del panel, los bloques que est�n pegados a la misma. Si
    la onda expansiva llega a tocar otra bomba, esta tambi�n explotar�,
    pudiendo as� generar "reacciones en cadena".

    Pero eso no es todo, si llegamos a juntar 4 bombas, podemos generar
    una Mega-Bomba, la cual tendr� una onda expansiva mucho m�s grande.

    Romper bombas, tambi�n nos dar� puntaje, siempre y cuando la bomba se
    encuentre en la l�nea que rompimos, en ning�n caso se le adicionar�
    puntaje extra por las bombas que exploten por ondas expansivas.

    Los puntajes son:

      BOMB:       10 puntos
      MEGA-BOMB:  50 puntos

    Y por �ltimo, para hacer m�s emocionante el juego, cada 10 segundos,
    se le agregar� una l�nea "mala", por lo que se deber� apurar en hacer
    las cosas.

2 PLAYERS (dos jugadores):

  CLASSIC (cl�sico):
  DESTROYER (destructor):

    Igual que los modos de un jugador, solamente que las l�neas que
    hacemos se van acumulando, y cada 10 segundos, por cada l�nea que
    hicimos, se le pasar� una l�nea "mala" al otro jugador. Igualmente, si
    el otro jugador va haciendo l�neas, va contrarrestando el efecto,
    hasta tal punto que puede hacer m�s l�neas que nosotros en el per�odo
    de 10 segundos, lo que nos dar�a como resultado que a nosotros nos
    aumenten las l�neas "malas".


8. PROGRAMANDO
--------------

Para conseguir el c�digo fuente de TETRIS Queen y comenzar a modificar cosas,
puede hacerlo baj�ndose el paquete "qtetris*-src.zip" o directamente desde el
repositorio CVS (mire la secci�n FAQ para m�s informaci�n sobre este tema),
cualquier sea el modo que utilice, junto a esto necesitar� el paquete
"qtetris*-dat.zip" que contiene los fuentes de los datos (.BMP, .PCX, .WAV,
.MID, etc.) para poder crear el fichero de datos y su archivo de cabecera
correspondiente.

Para compilar satisfactoriamente el juego, deber� tener la librer�a Allegro,
y si tiene Allegro, se supone que tiene una m�nima idea sobre c�mo
compilarlo. Ahora, el proceso para TETRIS Queen es exactamente el mismo (o
bastante parecido). Vaya al directorio `qtetris/src', y ejecute uno de los
dos archivos fix.sh o fix.bat (dependiendo de su sistema operativo). Luego,
ejecute `make depend' y finalmente `make' desde la l�nea de comandos. Si
todo sale bien, tendr� el juego hecho y listo para ejecutar, y si no, me
deber� avisar que algo anda mal, ya que algunas versiones ni fueron probadas
(la de Watcom por ej.).

Por otro lado, si es la primera vez que compila el juego (o modifica los
datos fuentes), deber� reconstruir el archivo de datos ejecutando
`makedata.bat' (en plataformas basadas en DOS) o el archivo `makedata.sh'
(en plataformas basadas en Unix).

Aqu� tiene un ejemplo de c�mo ser�a compilar el juego en DOS con DJGPP:

  >fix.bat djgpp
  >makedata.bat
  >make depend
  >make

Tambi�n puede utilizar opciones como `make DEBUGMODE=1' para poder depurar
el c�digo de TETRIS Queen, o como `make STATICLINK=1' para que en algunas
versiones (como en Windows y Unix) se utilicen las librer�as est�ticas de
Allegro antes que las din�micas (como ficheros .DLL o .os).


9. FAQ
------

P: �Qu� hay de nuevo en esta versi�n?
R: Un poco m�s de documentaci�n y varias mejoras internas para poder
   reconstruir el programa en otras plataformas (DOS, Windows, Unix,
   GNU/Linux, QNX). Y la nueva opci�n `-r' para poder ejecutar el juego
   en diferentes resoluciones (o tama�os de ventanas), y tambi�n `-m'
   para mezclar records de tus amigos con los tuyos.

P: �Estuviste 3 a�os para un simple TETRIS?
R: En realidad habr� sido 1 y sin ganas :-) La raz�n principal era que
   cambiaba de idea cada d�a (cosa que no se debe hacer si se realiza un
   buen dise�o previo :-), y no me daba ganas de programar algo que no tiene
   mucho futuro (con un simple TETRIS nadie se sorprende �no?), pero ahora
   s�lo hago versiones de mantenimiento (si Allegro cambia, TETRIS tambi�n),
   y por eso se van agregando a�os (2001 por ejemplo). De todos modos, no se
   por qu� le interesa tanto cu�nto demor�, al fin y al cabo, el juego ya
   est� hecho.

P: Las m�sicas se escuchan con muy baja calidad �C�mo puedo mejorar esto?
R: La �nica forma, por ahora, es bajarse unos WAVETABLES para que los
   "pobres" sonidos MIDI sean reemplazados por los "poderosos" samples que
   traen estos ficheros (los wavetables). Puede encontrar varios enlaces
   desde la misma p�gina de Allegro:

     http://alleg.sourceforge.net/digmid.es.html

P: �D�nde consigo la utilidad CVS?
R: La versi�n para Windows de CVS (Concurrent Versions System) se encuentra
   en:

     ftp://ftp.cvshome.org/pub/cvs-1.11/windows/cvs1-11.zip

   Para otras versiones de este programa puede dirigirse a:

     http://www.cvshome.org

P: �C�mo consigo el c�digo fuente desde el repositorio CVS?
R: Una vez que tenga la utilidad cvs, debe seguir estos pasos:

   1) Debemos ingresar al repositorio de forma an�nima mediante:

      cvs -d :pserver:anonymous@cvs.qtetris.sourceforge.net:/cvsroot/qtetris login

   2) Realizamos el primer checkout, lo que significa que sacaremos una
      copia "fresca" de TETRIS Queen:

      cvs -z3 -d :pserver:anonymous@cvs.qtetris.sourceforge.net:/cvsroot/qtetris checkout qtetris

   3) Una vez esto, cada vez que quiera actualizar la copia local con la del
      repositorio, s�lo deber� ejecutar en el directorio `qtetris/':

      cvs update

   IMPORTATE: cuando obtenga la versi�n CVS, no borre los directorios CVS ni
   el contenido dentro de ellos, es para uso interno de este programa.

P: Cuando quiero compilar el juego aparece algo como esto:
   make.exe: *** No rule to make target `data.h', needed by `obj/block.o'.  Stop.
   �Qu� hago?
R: Esto se debe a que todav�a no ha reconstruido el archivo de datos, para
   hacerlo, ejecute makedata.bat o makedata.sh, espere un rato e int�ntelo
   nuevamente.

P: Tengo problemas y no hay mucha documentaci�n :-(
   �D�nde encuentro m�s ayuda?
R: Puede enviarme un email a mi direcci�n personal:

     davidcapello@gmail.com

   Si encuentra un bug, error de documentaci�n o algo extra�o o confuso, no
   dude en ponerse en contacto y avisarme al respecto.


10. CR�DITOS
------------

Mire `AUTHORS.es' para ver quien particip� directamente en el proyecto y
`THANKS.es' para ver los agradecimientos a las personas que sin su ayuda
ser�a imposible la existencia de TETRIS Queen hoy en d�a.
