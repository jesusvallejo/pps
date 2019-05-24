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
if ! gcc -Wall -Wextra -o delreves delreves.c auxiliar.c; then
	echo EL PROGRAMA NO HA COMPILADO CORRECTAMENTE.
	exit -1;
fi
########################################################################
########################################################################
# Prueba delreves con -h
test_run ./delreves -h
test_status 0
test_lines 2 -eq 0
test_lines 1 -ge 2
test_content 1 << \EOF
delreves: Uso: delreves [ fichero... ]
delreves: Invierte el contenido de las lineas de los ficheros (o de la entrada).
EOF

########################################################################
# Prueba delreves con el fichero diez:
cat > diez << EOF
uno
dos
tres
cuatro
cinco
seis
siete
ocho
nueve
diez
EOF
test_run ./delreves diez
test_status 0
test_lines 2 -eq 0
test_content 1 << \EOF
onu
sod
sert
ortauc
ocnic
sies
eteis
ohco
eveun
zeid
EOF
########################################################################
# Prueba con la entrada estándar 
test_run ./delreves < diez
test_status 0
test_lines 2 -eq 0
test_content 1 << \EOF
onu
sod
sert
ortauc
ocnic
sies
eteis
ohco
eveun
zeid
EOF
