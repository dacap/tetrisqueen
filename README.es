TETRIS Queen - Versión 1.4
Copyright (C) 1999, 2000, 2001 por David A. Capello 
---------------------------------------------------

Este programa es software libre; usted puede redistribuirlo y/o
modificarlo bajo los términos de la Licencia Pública General GNU
(o GNU General Public License) publicada por la Fundación de Software
Libre (Free Software Foundation); cualquier versión 2 de la Licencia,
o (a su elección) alguna versión más antigua.

Este programa es distribuido con la esperanza de que sea útil,
pero SIN GARANTÍA ALGUNA; sin incluso la garantía implícita
de COMERCIALIZACIÓN o IDONEIDAD PARA UN PROPOSITO PARTICULAR.
Vea la GNU General Public License para más detalles.

Usted debe de haber recibido una copia de la GNU General Public
License junto con este programa; si no, escriba a la Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


1. ÍNDICE
---------

   1. Índice
   2. Introducción
   3. Requerimientos
   4. Configuración
   5. Controles
   6. Menús
   7. Jugando
   8. Programando
   9. Faq
  10. Créditos


2. INTRODUCCIÓN
---------------

Soy David A. Capello y le presento uno de los tantos clones del TETRIS
original de Arcade creado por el TEAM TETRIS en el año 1988. El juego no
es una réplica idéntica del viejo TETRIS pero sí tiene el mismo concepto
creado por Alexey Pajitnov por aquellos viejos tiempos.

Para ponerle un poco más de emoción a esto, incluí un nuevo modo de juego
exclusivo de TETRIS Queen: "el destructor" (ó "destroyer"). Y demás está
decir, que el "Queen" del título se debe nada más y nada menos a que el
juego es un total tributo a la famosa banda inglesa de música: Queen.

Para más información y actualizaciones del juego, puede visitar el sitio
oficial de TETRIS Queen en:

  http://qtetris.sourceforge.net

Adiós y espero sus comentarios.


3. REQUERIMIENTOS
-----------------

Estos son los requerimientos mínimos que necesita TETRIS Queen:

  - 486 DX (podría que funcione en una 386);
  - 4 MB de RAM (mejor serían 8 megas, y con 16 estás hecho);
  - Tarjeta VGA;
  - DOS (ó UNIX);
  - Teclado;

Aquí tiene los requerimientos recomendados:

  - Pentium 166 Mhz o superior;
  - 32 MB de RAM;
  - Tarjeta VGA;
  - Sound Blaster;
  - Windows 95/98 (ó GNU/Linux);
  - Teclado y dos joysticks;


4. CONFIGURACIÓN
----------------

Toda la configuración del juego se encuentra en el archivo qtetris.cfg,
usualmente no debería tocar nada aquí más que la sección [tetris] donde
se encuentra la configuración específica del juego y no la del sistema.

Por otro lado, para otras configuraciones "rápidas", puede utilizar la
línea de comandos, donde podrá iniciar el juego con diferentes opciones:

  qtetris [OPCIONES]

Las opciones disponibles son:

  -r, --resolution ANCHO ALTO     usar una resolución especial (en 8 bpp)
  -i, --nointro                   no mostrar la introducción
  -s, --nosound                   no instalar el sonido
  -j, --nojoy                     no instalar el joystick
  -m, --merge ARCHIVO_HOF         adjuntar otro "salón de la fama" al actual
  -h, --help                      visualizar la ayuda del programa (en inglés)
      --version                   mostrar información sobre la versión

Por ejemplo, si desea iniciar sin instalar el sonido (ya que está
escuchando sus MP3s favoritos con otro programa), y no quiere la
introducción, puede iniciar el juego de la siguiente manera:

  qtetris -is


5. CONTROLES
------------

Las teclas generales en el juego son:

  ESC       sale del juego, vuelve en los menús, y realiza cualquier cosa
            para cancelar algo;
  CTRL+Q    aborta el juego y vuelve al sistema operativo;
  F11       pone pausa;
  F12       captura la pantalla guardándola como un archivo BMP;

Las teclas para algunas funciones extras cuando se está jugando:

  F1        baja el volumen del sonido;
  F2        sube el volumen del sonido;
  F3        baja el volumen de la música;
  F4        sube el volumen de la música;
  F5        salta a la música anterior;
  F6        salta a la próxima música;
  F7        cambia la música por una al azar;

Las teclas POR DEFECTO de cada jugador son:

  PLAYER1:       PLAYER2:
  Izquierda      A            mueve la pieza hacia la izquierda;
  Derecha        D            mueve la pieza hacia la derecha;
  Abajo          S            baja la pieza rápidamente;
  Supr/Delete    1            rota la pieza hacia la izquierda;
  Fin/End        2            rota la pieza hacia la derecha;

Las teclas de cada jugador, pueden ser reconfiguradas desde el menú
OPTIONS/CONTROLS/PLAYER X. Por ejemplo, si desea mover la pieza hacia
abajo del jugador 1 con el botón número 1 del primer joystick conectado
a la computadora:

  - entre en "OPTIONS/CONTROLS/PLAYER 1";
  - seleccione la opción "DOWN: ...", y presione ENTER;
  - luego, presione la palanca (stick direccional) del joystick 1 hacia
    abajo;
  - y listo, ahora, si quiere volver a los valores anteriores de todas las
    teclas, solamente debe seleccionar la opción "RESTORE" que se encuentra
    en este mismo menú;

NOTA IMPORTANTE AL INGRESAR UN NUEVO RECORD: cuando hay que ingresar una
nueva puntuación, le aparecerán tres letras, usando las teclas para mover
la pieza hacia los costados, puede ir cambiando entre la 1era, 2da y 3er
letra, utilizando los botones para rotar, puede cambiar la letra actual,
y pulsando hacia abajo acepta. Tenga mucho cuidado al hacer esta
operación, ya que podría colocar iniciales no deseadas.


6. MENÚS
--------

  MAIN (menú principal):
  |
  +- 1 PLAYER:       comienza un juego con un jugador (antes deberá elegir
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
  |  +- MUSIC:       modifica el volumen de la música;
  |  |
  |  +- SOUND TEST (prueba de sonido):
  |  |  |
  |  |  +- LEFT:     reproduce un sonido que se escucha desde la izquierda;
  |  |  |
  |  |  +- CENTRE:   reproduce un sonido que se escucha desde el centro;
  |  |  |
  |  |  +- RIGHT:    reproduce un sonido que se escucha desde la derecha;
  |  |  |
  |  |  `- FLIP PAN: invierte la orientación del sonido (si los sonidos no
  |  |               salen correctamente por los lados que se indican,
  |  |               utilice esta opción y vuelva a probar);
  |  |
  |  +- CONTROLS (controles):
  |  |  |
  |  |  +- PLAYER 1: muestra la configuración de los botones del 1er jugador;
  |  |  |
  |  |  +- PLAYER 2: muestra la configuración de los botones del 2do jugador;
  |  |  |
  |  |  `- CALIBRATE
  |  |     JOYSTICK: muestra una pantalla donde se pueden calibrar los dos
  |  |               joysticks;
  |  |
  |  `- RESET HIGH
  |     SCORES:      borra las puntuaciones, restaurándolas por los valores
  |                  por defecto (antes deberá elegir la tabla de records
  |                  específica del modo de juego que quiera borrar);
  |
  +- CREDITS:        muestra los créditos del juegos;
  |
  `- EXIT:           sale del juego y vuelve al sistema operativo;


7. JUGANDO
----------

Los diferentes modos de juego de TETRIS Queen son:

1 PLAYER (un jugador):

  CLASSIC (clásico):

    El clásico modo de juego de todo TETRIS. El principal objetivo es ir
    haciendo líneas con las piezas que se le van dando, si se hacen dos,
    tres o hasta cuatro líneas al mismo tiempo nos dará más puntaje. Aquí
    tiene la lista de puntajes:

      SINGLE:  1 línea   10 puntos
      DOUBLE:  2 líneas  50 puntos
      TRIPLE:  3 líneas  200 puntos
      TETRIS:  4 líneas  500 puntos

  DESTROYER (destructor):

    Igual que el clásico, solamente que las piezas ahora tendrán una
    bomba, ninguna, o estarán llenas de bombas. Al hacer una línea, se
    activarán todas las bombas que se encuentren en la misma, explotando y
    tirando, fuera del panel, los bloques que estén pegados a la misma. Si
    la onda expansiva llega a tocar otra bomba, esta también explotará,
    pudiendo así generar "reacciones en cadena".

    Pero eso no es todo, si llegamos a juntar 4 bombas, podemos generar
    una Mega-Bomba, la cual tendrá una onda expansiva mucho más grande.

    Romper bombas, también nos dará puntaje, siempre y cuando la bomba se
    encuentre en la línea que rompimos, en ningún caso se le adicionará
    puntaje extra por las bombas que exploten por ondas expansivas.

    Los puntajes son:

      BOMB:       10 puntos
      MEGA-BOMB:  50 puntos

    Y por último, para hacer más emocionante el juego, cada 10 segundos,
    se le agregará una línea "mala", por lo que se deberá apurar en hacer
    las cosas.

2 PLAYERS (dos jugadores):

  CLASSIC (clásico):
  DESTROYER (destructor):

    Igual que los modos de un jugador, solamente que las líneas que
    hacemos se van acumulando, y cada 10 segundos, por cada línea que
    hicimos, se le pasará una línea "mala" al otro jugador. Igualmente, si
    el otro jugador va haciendo líneas, va contrarrestando el efecto,
    hasta tal punto que puede hacer más líneas que nosotros en el período
    de 10 segundos, lo que nos daría como resultado que a nosotros nos
    aumenten las líneas "malas".


8. PROGRAMANDO
--------------

Para conseguir el código fuente de TETRIS Queen y comenzar a modificar cosas,
puede hacerlo bajándose el paquete "qtetris*-src.zip" o directamente desde el
repositorio CVS (mire la sección FAQ para más información sobre este tema),
cualquier sea el modo que utilice, junto a esto necesitará el paquete
"qtetris*-dat.zip" que contiene los fuentes de los datos (.BMP, .PCX, .WAV,
.MID, etc.) para poder crear el fichero de datos y su archivo de cabecera
correspondiente.

Para compilar satisfactoriamente el juego, deberá tener la librería Allegro,
y si tiene Allegro, se supone que tiene una mínima idea sobre cómo
compilarlo. Ahora, el proceso para TETRIS Queen es exactamente el mismo (o
bastante parecido). Vaya al directorio `qtetris/src', y ejecute uno de los
archivos fixdjgpp, fixmingw, fixmsvc, fixunix o fixwat (dependiendo del
compilador y plataforma). Luego, ejecute `make depend' y finalmente `make'
desde la línea de comandos. Si todo sale bien, tendrá el juego hecho y listo
para ejecutar, y si no, me deberá avisar que algo anda mal, ya que algunas
versiones ni fueron probadas (la de Watcom por ej.).

Por otro lado, si es la primera vez que compila el juego (o modifica los
datos fuentes), deberá reconstruir el archivo de datos ejecutando
`makedata.bat' (en plataformas basadas en DOS) o el archivo `makedata.sh'
(en plataformas basadas en Unix).

Aquí tiene un ejemplo de cómo sería compilar el juego en DOS con DJGPP:

  >fixdjgpp
  >makedata
  >make depend
  >make

También puede utilizar opciones como `make DEBUGMODE=1' para poder depurar
el código de TETRIS Queen, o como `make STATICLINK=1' para que en algunas
versiones (como en Windows y Unix) se utilicen las librerías estáticas de
Allegro antes que las dinámicas (como ficheros .DLL o .os).


9. FAQ
------

P: ¿Qué hay de nuevo en esta versión?
R: Un poco más de documentación y varias mejoras internas para poder
   reconstruir el programa en otras plataformas (DOS, Windows, Unix,
   GNU/Linux, QNX). Y la nueva opción `-r' para poder ejecutar el juego
   en diferentes resoluciones (o tamaños de ventanas), y también `-m'
   para mezclar records de tus amigos con los tuyos.

P: ¿Estuviste 3 años para un simple TETRIS?
R: En realidad habrá sido 1 y sin ganas :-) La razón principal era que
   cambiaba de idea cada día (cosa que no se debe hacer si se realiza un
   buen diseño previo :-), y no me daba ganas de programar algo que no tiene
   mucho futuro (con un simple TETRIS nadie se sorprende ¿no?), pero ahora
   sólo hago versiones de mantenimiento (si Allegro cambia, TETRIS también),
   y por eso se van agregando años (2001 por ejemplo). De todos modos, no se
   por qué le interesa tanto cuánto demoré, al fin y al cabo, el juego ya
   está hecho.

P: Las músicas se escuchan con muy baja calidad ¿Cómo puedo mejorar esto?
R: La única forma, por ahora, es bajarse unos WAVETABLES para que los
   "pobres" sonidos MIDI sean reemplazados por los "poderosos" samples que
   traen estos ficheros (los wavetables). Puede encontrar varios enlaces
   desde la misma página de Allegro:

     http://alleg.sourceforge.net/digmid.es.html

P: ¿Dónde consigo la utilidad CVS?
R: La versión para Windows de CVS (Concurrent Versions System) se encuentra
   en:

     ftp://ftp.cvshome.org/pub/cvs-1.11/windows/cvs1-11.zip

   Para otras versiones de este programa puede dirigirse a:

     http://www.cvshome.org

P: ¿Cómo consigo el código fuente desde el repositorio CVS?
R: Una vez que tenga la utilidad cvs, debe seguir estos pasos:

   1) Debemos ingresar al repositorio de forma anónima mediante:

      cvs -d :pserver:anonymous@cvs.qtetris.sourceforge.net:/cvsroot/qtetris login

   2) Realizamos el primer checkout, lo que significa que sacaremos una
      copia "fresca" de TETRIS Queen:

      cvs -z3 -d :pserver:anonymous@cvs.qtetris.sourceforge.net:/cvsroot/qtetris checkout qtetris

   3) Una vez esto, cada vez que quiera actualizar la copia local con la del
      repositorio, sólo deberá ejecutar en el directorio `qtetris/':

      cvs update

   IMPORTATE: cuando obtenga la versión CVS, no borre los directorios CVS ni
   el contenido dentro de ellos, es para uso interno de este programa.

P: Cuando quiero compilar el juego aparece algo como esto:
   make.exe: *** No rule to make target `data.h', needed by `obj/block.o'.  Stop.
   ¿Qué hago?
R: Esto se debe a que todavía no ha reconstruido el archivo de datos, para
   hacerlo, ejecute makedata.bat o makedata.sh, espere un rato e inténtelo
   nuevamente.

P: Tengo problemas y no hay mucha documentación :-(
   ¿Dónde encuentro más ayuda?
R: Puede enviarme un email a mi dirección personal:

     dacap@users.sourceforge.net

   Si encuentra un bug, error de documentación o algo extraño o confuso, no
   dude en ponerse en contacto y avisarme al respecto.


10. CRÉDITOS
------------

Mire `AUTHORS.es' para ver quien participó directamente en el proyecto y
`THANKS.es' para ver los agradecimientos a las personas que sin su ayuda
sería imposible la existencia de TETRIS Queen hoy en día.
