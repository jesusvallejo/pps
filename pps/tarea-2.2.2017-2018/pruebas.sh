#!/bin/bash

########################################################################
# Este fichero pretende ser un ejemplo para que los estudiantes
# elaboren nuevos tests para sus programas.

########################################################################
# Funciones auxiliares

# ejecuta un mandato, retorna el exit status del mandato previamente
# almacenado en la variable de entorno xtatus y almacena la salida
# estándar en el fichero .fd1 y la salida de error en el fichero .fd2
test_run() # Command [args...] [| Command...] [<2>> redirections...]
{
	echo "$ $@"
        [ -x $1 ] || (echo "No existe el ejecutable $1"; exit 1)
	"$@" > .fd1 2> .fd2
        xtatus=$?
        return $xtatus
}

# Comprueba que xtatus tiene como valor el indicado por el primer
# parámetro
test_status()
{
    if [ $xtatus -eq $1 ]; then
        echo "Valor de terminación correcto"
    else
        echo "Valor de terminación incorrecto"
        echo "Se esperaba $1 y pero el valor es $xtatus"
        exit 1
    fi;
    return 0
}

# Comprueba que el número de líneas de la salida estándar o de error
# son los adecudados
test_lines()
{
    typeset -i nlines=`cat .fd$1 | wc -l`
    [ $nlines $2 $3 ] && return 0

    echo "Error en el número de líneas del descriptor $1"
    echo "Se esperaba $nlines $2 $3"
    exit 1
}

# Comprueba que el contenido de la salida estándar o de la salida de
# error son adecuados
test_content()
{
    if sdiff .fd$1 ${2:--}; then
        echo "Contenido correcto"
    else
        echo "El contenido del descriptor $1 NO es el esperado"
        exit 1
    fi;
    return 0
}
########################################################################
########################################################################
########################################################################
########################################################################
# Prueba de compilación
if ! gcc -Wall -Wextra -o secuencia secuencia.c auxiliar.c; then
	echo EL PROGRAMA NO HA COMPILADO CORRECTAMENTE.
	exit -1;
fi
########################################################################
# Prueba secuencia con -h
test_run ./secuencia -h
test_status 0
test_lines 2 -eq 0
test_lines 1 -ge 2
#Si se quiere comparar el contenido exacto, descomentar lo siguiente
#test_content 1 << \EOF
#secuencia: Uso: secuencia [ hasta [ desde [ paso ]]]
#secuencia: Genera la secuencia de numeros en el intervalo y paso indicados.
#EOF

########################################################################
# Prueba secuencia sin argumentos: 
# Hay que tener especial cuidado con el formato de salida.
test_run ./secuencia
test_status 0
test_lines 2 -eq 0
test_content 1 << \EOF
	1
	2
	3
	4
	5
	6
	7
	8
	9
	10
EOF

########################################################################
# Prueba secuencia con argumentos no válidos
test_run ./secuencia 10 1 -1
test_status 64 
test_lines 1 -eq 0
test_lines 2 -ge 2
#Si se quiere comparar el contenido exacto, descomentar lo siguiente
#test_content 2 << \EOF
#secuencia: Error(EX_USAGE), uso incorrecto del mandato. "Success"
#secuencia+ El signo de "paso" no permite recorrer el intervalo en el sentido "desde" a "hasta".
#EOF

########################################################################
# RECOMENDACIONES
# La estructura de estos test es siempre:
# Se realiza la llamada con los argumentos deseados: test_run ./secuencia argumentos si los hay
# Se testea el exit_status (se debe hacer siempre): test_status numero
# Si se desea, se testea el numero de lineas de las salidas estandar y/o de error (1 o 2 respectivamente): test_lines salida comparacion numero
# Si se desea, se testea el contenido exacto de las salidas estandar y/o de error (1 o 2 respectivamente): test_content salida contenido exacto
########################################################################
# A partir de este lugar debe incluir los tests el estudiante
 
