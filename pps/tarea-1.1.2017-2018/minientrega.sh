  #!/bin/bash
	
	
	if [  -z "${MINIENTREGA_CONF}" ]  ; 
	then
	echo "minientrega.sh: Error, no se pudo realizar la entrega">&2
	echo "minientrega.sh+ variable no declarada">&2
	exit $EX_USAGE
	fi
	
  if test $# -ne 1; then                                                                                      #Comprueba si el numero de argumentos es distinto de 1

   echo "minientrega.sh: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"" >&2
   echo "minientrega.sh+ <<Error, el numero de argumentos es distinto a 1>>" >&2

   exit 64

  fi
   if  [ $1 = "-h" ] || [ $1 = "--help" ] ; then

  echo "minientrega.sh: Uso: El programa recibe una practica, con sus archivos de configuracion"
  echo "minientrega.sh+ El programa recibe una practica y la analiza para comprobar si los datos son correctos y legibles, asi como su fecha y la fecha limite"
  
  exit 0

 fi
 source ${MINIENTREGA_CONF}/$1
  if ! test -d ${MINIENTREGA_CONF}; then                                                                      #Comprueba si MINIENTREGA_CONF es un directorio

   echo "minientrega.sh: Error, no se pudo realizar la entrega" >&2
   echo "minientrega.sh+ no es accesible el directorio \"${MiNIENTREGA_CONF}\"" >&2

   exit 64

  fi

  if ! test -r ${MINIENTREGA_CONF}; then                                                                      #Comprueba si el archivo es accesible

   echo "minientrega.sh: Error, no se pudo realizar la entrega" >&2
   echo "minientrega.sh+ no es accesible el fichero" >&2

   exit 64

  fi

  if test `ls -F ${MINIENTREGA_CONF} | grep -V /| wc -l `-eq 0; then                                          #Comprueba si MINIENTREGA_CONF es un fichero que existe y estandar

   echo "minientrega.sh: Error, no se pudo realizar la entrega" >&2
   echo "minientrega.sh+ no es accesible el fichero" >&2

   exit 66

  fi
  
   

  regex = '[0-9]{4}-[0-1][0-9]-[0-3][0-9]'                                                                    #Comprueba si MINIENTREGA_FECHALIMITE tiene un formato correcto

  if ! [[ $MINIENTREGA_FECHALIMITE =~ $regex ]] ; then

   echo "minientrega.sh: Error, no se pudo realizar la entrega" >&2
   echo "minientrega.sh+ FECHA INCORRECTA \"${MINIENTREGA_FECHALIMITE}\"" >&2

   exit 65

  fi

  for archivo in `ls ${MINIENTREGA_CONF}/*`; do                                                               #Comprueba si existe el archivo del parametro

   if test $archivo == ${MINIENTREGA_CONF}/$1; then

    return

   fi

  done
  
  echo "minientrega.sh: Error, no se pudo realizar la entrega" >&2
  echo "minientrega.sh+ no es accesible el fichero \"no vale\"" >&2
  exit 66

  ##Variables                                                                                                  #Comprueba si MINIENTREGA_FECHALIMITE esta dentro de la fecha acordada

  dia = `date +%Y`
  mes = `date +%m`
  anio = `date +%d`
  ultimoDia = ${MINIENTREGA_FECHALIMITE:0:4}
  ultimoMes = ${MINIENTREGA_FECHALIMITE:5:2}
  ultimoAnio = ${MINIENTREGA_FECHALIMITE:8:2}

  if [%anio -gt $ultimoAnio]; then

   echo "minientrega.sh: Error, no se pudo realizar la entrega" >&2
   echo "minientrega.sh+ El plazo acabo el \"${MINIENTREGA_FECHALIMITE}\"" >&2
   exit 65

  elif [$anio -eq $ultimoAnio]; then

   if [$mes -gt $ultimoMes]; then

    echo "minientrega.sh: Error, no se pudo realizar la entrega" >&2
    echo "minientrega.sh+ El plazo acabo el \"${MINIENTREGA_FECHALIMITE}\"" >&2
    exit 65

   elif [$mes -eq $ultimoMes];

    if [$dia -gt $ultimoDia]; then

     echo "minientrega.sh: Error, no se pudo realizar la entrega" >&2
     echo "minientrega.sh+ El plazo acabo el \"${MINIENTREGA_FECHALIMITE}\"" >&2
     exit 66

    fi

  fi

fi

                                                                                                                #Comprueba los ficheros que deben ser entregados
 for fichero in ${MINIENTREGA_FICHEROS}; do

  if test -e ${PWD}/$fichero; then

   if ! test -r ${PWD}/$fichero; then

    echo "minientrega.sh: Error, no se pudo realizar la entrega" >&2
    echo "minientrega.sh+ No es accesible el fichero \"${PWD}/$fichero\"" >&2
    exit 66

   fi

  echo "minientrega.sh: Error, no se pudo realizar la entrega" >&2
  echo "minientrega.sh+ No es accesible el fichero \"${PWD}/$fichero\"" >&2
  exit 66

 fi

 done

                                                                                                                #Comprueba el destino
 if test -d ${MINIENTREGA_DESTINO};then

  if ! test -w ${MINIENTREGA_DESTINO};then

   echo "minientrega.sh: Error, no se pudo realizar la entrega" >&2
   echo "minientrega.sh+ No se pudo crear el subdirectorio de entrega \"${MINIENTREGA_DESTINO}\"" >&2
   exit 73

 else

  exit 73

 fi
                                                                                                                #Muestra por la salida estandar el funcionamiento del programa

 if ! test -d ${MINIENTREGA_DESTINO}/${USER} && ! test -r ${MINIENTREGA_DESTINO}/${USER}/; then                 #Si no existe, crea al usuario

  mkdir -p ${MINIENTREGA_DESTINO}/${USER}

 fi







