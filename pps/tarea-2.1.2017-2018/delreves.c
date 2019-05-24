#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "auxiliar.h"


/*char* reverse(char* line){
  
  //char* outFileName = "tmp.txt";
  //FILE* outFile = fopen(outFileName, "a+");
  size_t l = strlen(line);
  char* reversed = (char*)malloc((l + 1) * sizeof(char));
  reversed[l] = '\0';
  int i;
  for(i = 0; i < l; i++) {
    reversed[i] = line[l - 1 - i];
  }
  printf("%s\n","--");
  printf("%s",reversed);
  return reversed;
  //fputs(r,outFile);
  //fclose(outFile);
  free(reversed);
  
  
	
}*/
char* reverse(char *str) {
	
    char* reversed = (char*) malloc(sizeof(char) * strlen(str+1));
    int j = 0;
    int i=0;
    for (i = strlen(str) - 2; i >= 0; i--, j++) {
        reversed[j] = str[i];
    }
    reversed[strlen(str)] = '\0';
	
    return reversed;
}

/*int counter(char const* const fileName)
{
 FILE *fp;
 char ch;
  int linecount, wordcount, charcount;

 // Initialize counter variables
 linecount = 0;
 wordcount = 0;
 charcount = 0;

 fp = fopen(fileName,"r");

   // If file opened successfully, then write the string to file
      if ( fp )
   {
	//Repeat until End Of File character is reached.	
	   while ((ch=getc(fp)) != EOF) {
	   	  // Increment character count if NOT new line or space
		    if (ch != ' ' && ch != '\n') { ++charcount; }
		  
		  // Increment word count if new line or space character
		   if (ch == ' ' || ch == '\n') { ++wordcount; }
		   
		  // Increment line count if new line character
		   if (ch == '\n') { ++linecount; }
		   


	   }

	   if (charcount > 0) {
		++linecount;
		++wordcount;
	   }
    }
   elsehttps://www.youtube.com/watch?v=Xds3f-Lnzcs
      {
         printf("Failed to open the file\n");
        }

    printf("Lines : %d \n", linecount);
    printf("Words : %d \n", wordcount);
    printf("Characters : %d \n", charcount);
fclose(fp);
getchar();
return(0);
}
*/

void Ayuda(void)
{
	fprintf(stdout, "%s: Uso: delreves [ fichero... ]\n", argv0);
	fprintf(stdout, "%s: Invierte el contenido de las lineas de los ficheros (o de la entrada).\n", argv0);
	exit(0);
}


int main(int argc, char* argv[])
{
	char line[2048];

	argv0 = "delreves";
	if (argc==1){
		while (fgets(line, sizeof(line),stdin)) {	
        fprintf(stdout,"%s\n",reverse(line));
	    
    }
		exit(EX_OK);
	}
	
	//////////////////////////////////////////////
    if (argc>1){
		
      if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
			Ayuda();
			return 0;
	  }
	  int total=1;
	  while(total<argc){
	  char const* const  fileName = argv[total]; 
      FILE* file = fopen(fileName, "r"); 
     
	if (file!=NULL){  
    
    while (fgets(line, sizeof(line), file)) {	
        fprintf(stdout,"%s\n",reverse(line));
	
    }
    
    fclose(file);
    
    total++;
	}
	  
	
	else{
		if( access( fileName, F_OK ) != -1 ) {
		if (access( fileName, R_OK ) == -1 ){
			//is readable
			Error(EX_NOINPUT, "El fichero \"%s\" no puede ser leido.",fileName);
			
		}
    // file exists  
} 
else {
	
	Error(EX_NOINPUT, "El fichero \"%s\" no existe.",fileName);
    // file doesn't exist
}
	}
	  }
	  exit(EX_OK);
}
	else{
		char buffer[500];

// read in the line and make sure it was successful
	if (fgets(buffer,500,stdin) != NULL)
	{
	fprintf(stdout,"%s",reverse(buffer));
	
    }
    else{	
		printf("\n");
		printf("%s"," Sin argumentos");
		exit(0);
	}
	}
	exit(EX_OK);
}

