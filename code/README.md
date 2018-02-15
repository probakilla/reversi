#### REVERSI@CODE@C++ ####
|
|
|
---- main.cc { point d'entrée }
|
|
---- include { emplacement des en-têtes }
|
|
---- src {emplacement des sources }

Options de CMAKE :
Il existe deux options sur le cmake :
	TESTS : Active la compilation des tests
	PEDANTIC : Active le flag -Wpedantic
	
	-Wpedantic est en otpion pour nous permettre de masquer des 
	warnings qui ne nous sont pas évitables mais qui s'affichant en 
	mass lors de l'utilisation de -Wpedantic (C++ does not support
	__int128 [...])
	
	Pour activer une option : (effectué depuis code/build)
	cmake ../ -DPEDANTIC=ON
	pour désactiver une option :
	cmake ../ -DTESTS=OFF
