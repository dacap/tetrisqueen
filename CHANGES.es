Cambios realizados desde 1.3 a 1.3.1
------------------------------------

2001-06-03 - David A. Capello
	* Modificado en `main.c' el usage() y algunas cosas al reconocer
	  los argumentos.
	* Eliminada una variable est tica `game_over' en `credits.c',
	  no se utilizaba para absolutamente NADA (no es raro?).
	* Optimizado `credits.c' y la forma de manejar la lista de l¡neas
	  que deben ir apareciendo en la pantalla.
	* "Limpi‚" un poco el c¢digo y algunos TABs.
	* Eliminados de todos los ficheros de c¢digo fuente la versi¢n
	  del juego, esto har¡a sino que en cada nueva versi¢n todos los
	  ficheros se deban modificar.
	* Ahora que consegu¡ la utilidad InfoZIP para MSDOS (era hora :-),
	  los paquetes de src, dos y win est n formato ZIP.
	* Modificados algunas variables en makefile.pak y los nombres
	  de las reglas (ahora son `src', `dos', etc, sin el `pack').

2001-06-02 - David A. Capello
	* Modificado leame.txt y readme.txt a README.es,en, y license.txt
	  a COPYING.
	* Agregados los ficheros CHANGES.es y AUTHORS.es.
	* Un error reportado por Norberto Alfredo Bensa con el directorio
	  obj/, y también gracias a él, ahora en el makefiles se utilizan
	  barars normales (/) para indicar la ruta de acceso de la utilidad
	  DAT de Allegro.

2001-05-31 - David A. Capello
	* Agregados los ficheros makefile.qnx y fixqnx.sh por Angelo Mottola
	  para que el juego se compile en QNX.

