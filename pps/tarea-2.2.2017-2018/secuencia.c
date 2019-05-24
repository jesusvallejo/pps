#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "auxiliar.h"





double hasta = 10;
double desde = 1;
double paso = 1;
double impreso =0;
char* max;
int maximumPrint =100;
bool vale(char* input){
	
    int length,i; 

    length = strlen (input);
    for (i=0;i<length; i++){
        if (!isdigit(input[i]))
        {
            
            return false;
        }
	}
   return true;

}
bool esNumero(char* input){
	int length,i;
	length = strlen(input);
	for (i=0;i<length; i++){
	    if (i==0){
			if (input[0]!='-' && input[0]!='+' && !isdigit(input[0]) ){
				return false;
				printf ("Entered input is not a number ---code: signo\n");
               // exit(1);
				
			}
		}
		else
		if(i!=0 && input[i]=='-'){
			return false;
		}
		else
		if(i!=0 && input[i]=='+'){
			return false;
		}
		else
		if (input[0]=='.'){
			return false;
			printf ("Entered input is not a number ---code: punto origen\n");
               // exit(1);
		}
		else
		if (input[i]=='.' && i == length-1){
			return false;
			printf ("Entered input is not a number ---code: punto final\n");
                //exit(1);
		}
		else
        if (!isdigit(input[i]) && input[i]!='.' )
        {
			return false;
            printf ("Entered input is not a number ---code: no es numero\n");
           // exit(1);
        }
	}
	return true;
    
}
int esPositivo(double number){
 // true if number is less than 0
 
 
    if (number < 0.0){
		//fprintf(stdout,"%s\n","Has llamado ha esPositivo:");
		//fprintf(stdout,"%s\n","--NEGATIVO");
       return -1;
	}
    // true if number is greater than 0
    else if ( number > 0.0){
		//fprintf(stdout,"%s\n","Has llamado ha esPositivo:");
		//fprintf(stdout,"%s\n","++POSITIVO");
        return 1;
	}
    // if both test expression is evaluated to false
    else  {
	
	return 0;
	}
       
}
bool ordenCorrecto(){
	
	
	//fprintf(stdout,"%s\n","-+-+-+-+-+-+-+- Pruebas ordenCorrecto -+-+-+-+-+-+-");
	
	/*
	        //fprintf(stdout,"%s\n","");
		    hasta = strtod(arg[1],NULL);
			//fprintf(stdout,"%f\n",hasta);
			desde=strtod(arg[2],NULL);
			//fprintf(stdout,"%f\n",desde);
			paso=strtod(arg[3],NULL);
			//fprintf(stdout,"%f\n",paso);
			*/
	
	if (hasta>desde&& esPositivo(paso)>0){
		
		//fprintf(stdout,"%s\n","++orden corrento: fin mayor que origen y paso positivo");
		//fprintf(stdout,"%s\n","");
		//fprintf(stdout,"%s\n","-+-+-+-+-+-+-+- Fin pruebas ordenCorrecto -+-+-+-+-+-+-");
		return true;
	}
	else
	if (hasta<desde && esPositivo(paso)>0){
		//fprintf(stdout,"%s\n","--orden erroneo: origen mayor que fin y paso positivo");
		//fprintf(stdout,"%s\n","");
		//fprintf(stdout,"%s\n","-+-+-+-+-+-+-+- Fin pruebas ordenCorrecto -+-+-+-+-+-+-");
		return false;
	}
	else
	if (hasta>desde && esPositivo(paso)<0){
		//fprintf(stdout,"%s\n","--orden erroneo: fin mayor que origen y paso negativo");
		//fprintf(stdout,"%s\n","");
		//fprintf(stdout,"%s\n","-+-+-+-+-+-+-+- Fin pruebas ordenCorrecto -+-+-+-+-+-+-");
		return false;
	}
	else
	if (hasta<desde && esPositivo(paso)<0){
		//fprintf(stdout,"%s\n","++orden correcto: origen mayor que fin y paso negativo");
		//fprintf(stdout,"%s\n","");
		//fprintf(stdout,"%s\n","-+-+-+-+-+-+-+- Fin pruebas ordenCorrecto -+-+-+-+-+-+-");
		return true;
	}
    
    else{
		
	Error(EX_USAGE, "El parametro \"paso\" no puede valer 0.");
	return false;
    }
		
	
}

void Ayuda(void){
	fprintf(stdout, "%s: Uso: secuencia [ hasta [ desde [ paso ]]]\n", argv0);
	fprintf(stdout, "%s: Genera la secuencia de numeros en el intervalo y paso indicados.\n", argv0);
	exit(0);
}

int main(int argc, char* argv[]){
	max=getenv("MAX_OUTPUT");
	int i,p,o;
	
	if(max!=NULL){
		 if(strlen(max) != 0){
			 if(vale(max)){
		maximumPrint=strtod(getenv("MAX_OUTPUT"),NULL);
			 }
		 }
		 }
	
	else{
		
		//printf ("NO EXISTE MAX \n");
		#define MAX_OUTPUT 100
		maximumPrint=100;
	}
	
	
	argv0 = "secuencia";
	//fprintf(stdout,"%d",argc);
	
	switch(argc){
		case 4:
		for(p=1; p<argc;p++){
			if (!esNumero(argv[p])){
				if (p==1){
				Error(EX_USAGE, "El parametro \"hasta\" no es un numero real valido.");	
				}
				else if(p==2){
				Error(EX_USAGE, "El parametro \"desde\" no es un numero real valido.");	
				}else if(p==3){
					Error(EX_USAGE, "El parametro \"paso\" no es un numero real valido.");
				}
		
			}
		}
		    //fprintf(stdout,"%s\n","");
		    hasta = strtod(argv[1],NULL);
			//fprintf(stdout,"%f\n",hasta);
			desde=strtod(argv[2],NULL);
			//fprintf(stdout,"%f\n",desde);
			paso=strtod(argv[3],NULL);
			//fprintf(stdout,"%f\n",paso);
			
			
			if (!ordenCorrecto()){
		    
			Error(EX_USAGE, "El signo de \"paso\" no permite recorrer el intervalo en el sentido \"desde\" a \"hasta\".");
			
             		
			}
			
			//fprintf(stdout,"%s\n","hasta");
			//fprintf(stdout,"%f\n",hasta);
			//fprintf(stdout,"%s\n","desde");
			//fprintf(stdout,"%f\n",desde);
			//fprintf(stdout,"%s\n","paso");
			//fprintf(stdout,"%f\n",paso);
			
			//fprintf(stdout,"%s\n","-+-+-+-secuencia");
			
			if(esPositivo(paso)==-1){
				//fprintf(stdout,"%s\n","hola");
			while(desde>=hasta){
				if(impreso==maximumPrint){
					Error(EX_NOPERM, "Se intento superar el limite de salida establecido por MAX OUTPUT.");
				
			 }
			 fprintf(stdout,"\t%g\n",desde);
			 impreso++;
			 desde= desde + paso;
			}

			//fprintf(stdout,"%s\n","-+-+-+-fin de secuencia");
			}
			else{

				while(desde<=hasta){
				if(impreso==maximumPrint){
					Error(EX_NOPERM, "Se intento superar el limite de salida establecido por MAX OUTPUT.");
				
			 }
			 fprintf(stdout,"\t%g\n",desde);
			 impreso++;
			 desde= desde + paso;
			}

			//fprintf(stdout,"%s\n","-+-+-+-fin de secuencia");
			}
			
		
				
				
			
		return (0);
		break;
		
		case 3:
		for(o=1; o<argc;o++){
			if (!esNumero(argv[o])){
				if (o==1){
				Error(EX_USAGE, "El parametro \"hasta\" no es un numero real valido.");	
				}
				else if(o==2){
				Error(EX_USAGE, "El parametro \"desde\" no es un numero real valido.");	
				}else if(o==3){
					Error(EX_USAGE, "El parametro \"paso\" no es un numero real valido.");
				}
			}
		}
		     hasta = strtod(argv[1],NULL);
			desde=strtod(argv[2],NULL);
			if (!ordenCorrecto()){
				Error(EX_USAGE, "El signo de \"paso\" no permite recorrer el intervalo en el sentido \"desde a \"hasta\".");	
			}
			
			
			//fprintf(stdout,"%s\n","hasta");
			//fprintf(stdout,"%f\n",hasta);
			//fprintf(stdout,"%s\n","desde");
			//fprintf(stdout,"%f\n",desde);
			//fprintf(stdout,"%s\n","paso");
			//fprintf(stdout,"%f\n",paso);
			
			//fprintf(stdout,"%s\n","-+-+-+-secuencia");
			
			if(esPositivo(paso)==-1){
				//fprintf(stdout,"%s\n","hola");
			while(desde>=hasta){
				if(impreso==maximumPrint){
					Error(EX_NOPERM, "Se intento superar el limite de salida establecido por MAX OUTPUT.");
				
			 }
			 fprintf(stdout,"\t%g\n",desde);
			 impreso++;
			 desde= desde + paso;
			}

			//fprintf(stdout,"%s\n","-+-+-+-fin de secuencia");
			}
			else{

				while(desde<=hasta){
				if(impreso==maximumPrint){
					Error(EX_NOPERM, "Se intento superar el limite de salida establecido por MAX OUTPUT.");
				
			 }
			 fprintf(stdout,"\t%g\n",desde);
			 impreso++;
			 desde= desde + paso;
			}

			//fprintf(stdout,"%s\n","-+-+-+-fin de secuencia");
			}
		return (0);
		break;
		
		case 2:
		if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
			Ayuda();
		}
		
		for(i=1; i<argc;i++){
			if (!esNumero(argv[i])){
				
		        if (i==1){
				Error(EX_USAGE, "El parametro \"hasta\" no es un numero real valido.");	
				}
				else if(i==2){
				Error(EX_USAGE, "El parametro \"desde\" no es un numero real valido.");	
				}else if(i==3){
					Error(EX_USAGE, "El parametro \"paso\" no es un numero real valido.");
				}
		
			}
		}
		hasta = strtod(argv[1],NULL);
		//fprintf(stdout,"%f",hasta);
			if (!ordenCorrecto()){
				Error(EX_USAGE, "El signo de \"paso\" no permite recorrer el intervalo en el sentido \"desde a \"hasta\".");
		//secuencia: Error(EX_USAGE), uso incorrecto del mandato. "Success"
        //secuencia+ El signo de "paso" no permite recorrer el intervalo en el sentido "desde"		
			}
			
			//fprintf(stdout,"%s\n","hasta");
			//fprintf(stdout,"%f\n",hasta);
			//fprintf(stdout,"%s\n","desde");
			//fprintf(stdout,"%f\n",desde);
			//fprintf(stdout,"%s\n","paso");
			//fprintf(stdout,"%f\n",paso);
			
			//fprintf(stdout,"%s\n","-+-+-+-secuencia");
			
			if(esPositivo(paso)==-1){
				//fprintf(stdout,"%s\n","hola");
			while(desde>=hasta){
				if(impreso==maximumPrint){
					Error(EX_NOPERM, "Se intento superar el limite de salida establecido por MAX OUTPUT.");
				
			 }
			 fprintf(stdout,"\t%g\n",desde);
			 impreso++;
			 desde= desde + paso;
			}

			//fprintf(stdout,"%s\n","-+-+-+-fin de secuencia");
			}
			else{

				while(desde<=hasta){
				if(impreso==maximumPrint){
					Error(EX_NOPERM, "Se intento superar el limite de salida establecido por MAX OUTPUT.");
				
			 }
			 fprintf(stdout,"\t%g\n",desde);
			 impreso++;
			 desde= desde + paso;
			}

			//fprintf(stdout,"%s\n","-+-+-+-fin de secuencia");
			}
			
		return (0);
		break;
		case 1:
		if (!ordenCorrecto()){
				Error(EX_USAGE, "El signo de \"paso\" no permite recorrer el intervalo en el sentido \"desde a \"hasta\".");
		//secuencia: Error(EX_USAGE), uso incorrecto del mandato. "Success"
        //secuencia+ El signo de "paso" no permite recorrer el intervalo en el sentido "desde"		
			}
			
			//fprintf(stdout,"%s\n","hasta");
			//fprintf(stdout,"%f\n",hasta);
			//fprintf(stdout,"%s\n","desde");
			//fprintf(stdout,"%f\n",desde);
			//fprintf(stdout,"%s\n","paso");
			//fprintf(stdout,"%f\n",paso);
			
			//fprintf(stdout,"%s\n","-+-+-+-secuencia");
			
			if(esPositivo(paso)==-1){
				//fprintf(stdout,"%s\n","hola");
			while(desde>=hasta){
				if(impreso==maximumPrint){
					Error(EX_NOPERM, "Se intento superar el limite de salida establecido por MAX OUTPUT.");
				
			 }
			 fprintf(stdout,"\t%g\n",desde);
			 impreso++;
			 desde= desde + paso;
			}

			//fprintf(stdout,"%s\n","-+-+-+-fin de secuencia");
			}
			else{

				while(desde<=hasta){
				if(impreso==maximumPrint){
					Error(EX_NOPERM, "Se intento superar el limite de salida establecido por MAX OUTPUT.");
				
			 }
			 fprintf(stdout,"\t%g\n",desde);
			 impreso++;
			 desde= desde + paso;
			}

			//fprintf(stdout,"%s\n","-+-+-+-fin de secuencia");
			}
			
		return (0);
		break;
		default:
		Error(EX_USAGE, "El número de argumentos no es correcto.");
	}
	
	return 0;
}