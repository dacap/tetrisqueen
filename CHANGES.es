2001-10-09  David A. Capello

	* Mejorado: el reconocimiento de argumentos.

2001-09-12  David A. Capello

	* Lista la traducción de los documentos (aunque fue muy poco).

2001-09-11  David A. Capello

	* Listo `merge_records()' en `hallfame.c'.
	* Se eliminaron todos los tabuladores (que gran cambio! :-)
	* Agregadas algunas macros MUSIC_*: como MUSIC_FIRST y MUSIC_LAST,
	  todo para facilitar tanto la lectura como la modificación del
	  código (por Marco Chiesi).

2001-09-10  David A. Capello

	* Nuevas opciones en la línea de comandos: --merge para mezclar
	  ficheros .hof, y la más importante: --resolution para poder utilizar
	  el juego en *cualquier* resolución de 8 bpp (se eliminó la entrada
	  en el TODO).
	* Una nueva opción en el menú `OPTIONS/CONTROLS/PLAYER*'.
	* Se arregló un error (reportado por Marco Chiesi) con las nuevas
	  versiones de Allegro: en el menú de configuración de control, como
	  el nuevo clear_keybuf() no borra los arreglos key[] y _key[], se
	  deben "limpiar" manualmente.

2001-06-27  David A. Capello

	* Nueva release 1.3.1: los paquetes src y dat.
	* Arreglados algunos makefile* y fix*.

2001-06-17  David A. Capello

	* Terminada la traducción: TODO.en y CHANGES.en.

2001-06-16  David A. Capello

	* Modificada la forma de crear el archivo de datos: ahora hay que
	  utilizar makedata.bat y makedata.sh, con esto se eliminan algunos
	  problemas que tenían los makefiles con las dependencias del data.h.
	* Modificada la documentación: lista la traducción de AUTHORS.es y
	  THANKS.es, arreglado un poco el README.
	* Eduard Bloch al parecer será el encargado de empaquetar el juego
	  para las distribuciones Debian.

2001-06-15  David A. Capello

	* Eliminado el readkey() al final del juego: en algunas plataformas
	  quedaba la pantalla negra sin nada (y se hacía confuso)
	  (recomendado por Eduard Bloch).

2001-06-07  David A. Capello

	* Todos los paquetes a formato ZIP (mirar makefile.pak):
	  la ayuda de cómo descomprimir ficheros .tar.gz fue eliminada.

2001-06-03  David A. Capello

	* Modificado en `main.c' el usage() y algunas cosas al reconocer
	  los argumentos.
	* Eliminada una variable estática `game_over' en `credits.c':
	  no se utilizaba para absolutamente NADA (raro, no?).
	* Optimizado `credits.c': la forma de manejar la lista de líneas
	  que deben ir apareciendo en la pantalla.
	* "Limpié" un poco el código: eliminados algunos TABs.
	* Eliminados de todos los ficheros de código fuente la versión
	  del juego: esto haría sino que en cada nueva versión todos los
	  ficheros se deban modificar.
	* Los paquetes de src, dos y win están en formato ZIP: ahora que
	  conseguí la utilidad InfoZIP para MSDOS (era hora :-)
	* Modificados algunas variables en makefile.pak y los nombres
	  de las reglas: ahora son `src', `dos', etc, sin el `pack'.

2001-06-02  David A. Capello

	* Modificado: leame.txt y readme.txt a README.es,en, y license.txt
	  a COPYING.
	* Agregados: los ficheros CHANGES.es y AUTHORS.es.
	* Un error reportado por Norberto Alfredo Bensa: el fichero
	  obj/tmpfile.txt no se agregaba en los paquetes, y también gracias
	  a él, ahora en el makefiles se utilizan barras normales (/) para
	  indicar la ruta de acceso de la utilidad DAT de Allegro.

2001-05-31  David A. Capello

	* Agregados los ficheros makefile.qnx y fixqnx.sh por Angelo Mottola:
	  ahora el juego compila también en QNX.
