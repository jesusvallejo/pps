#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "auxiliar.h"
#include <sys/stat.h>

int memoryCheck() {
  const int KB = 1024; /* bytes */
  const int MB = 1024 * KB; /* bytes */
  const int GB = 1024 * MB; /* bytes */
  long size = 0;
  void *p = NULL;

  int ctr;
  int j;
  int times = 100000;
  long sum = 0;
  for(ctr = 0; ctr < times; ctr ++ ) {
    size = 100 * MB;
    //printf("Allocating %d bytes memory \n", size);
    p = calloc(1, size);
    if(p != NULL) {
      //printf("SUCCESS.\n");
      sum += size;

      for(j=0; j<size; j++) {
	((char*)p)[j] = 1;
      }

      if(sum < GB) {
	//printf("Total allocated so far: %ld MB\n", sum/MB);
      } else {
	//printf("Total allocated so far: %ld GB\n", sum/GB);
      }
      if(sum > (1*GB) )  break;
    } else {
      //printf("FAIL.\n");
      break;
    }
  }
  return sum;
}


void Ayuda(void)
{
	fprintf(stdout, "%s: Uso: bocabajo [ fichero... ]\n", argv0);
	fprintf(stdout, "%s: Invierte el orden de las lineas de los ficheros (o de la entrada).\n", argv0);
	exit(0);
}





void readfileinreverse(FILE *fp)
{
    int i, size, start, loop, counter;
    char *buffer;
    char line[256];
    start = 0;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
	
	struct stat buf;
    stat("tmp", &buf);
    long fsize = buf.st_size;
	//printf("-- %ld\n",fsize);
	long tt =memoryCheck();
	//printf("-- %ld\n",tt);
	char const* const  debugFileName = "debug"; 
    FILE* debugFile = fopen(debugFileName, "w+");
	char foo[30];
	sprintf(foo, "file size %ld\n", fsize);
	char foo2[30];
	sprintf(foo2, "pc limit %ld\n", tt);
    fputs(foo,debugFile);
	fputs(foo2,debugFile);
	if(fsize>tt){
		Error(EX_OSERR, "No se pudo ubicar la memoria dinamica necesaria.");
		exit(EX_OSERR);
		
	}
	
    
    buffer = malloc((size+1) * sizeof(char));
    for (i=0; i< size; i++)
    {
        fseek(fp, size-1-i, SEEK_SET);
        buffer[i] = fgetc(fp);

        if(buffer[i] == 10)
        {
           if(i != 0)
           {
            counter = 0;        
            for(loop = i; loop > start; loop--)
            {
                if((counter == 0) && (buffer[loop] == 10))
                {
                    continue;
                }               
                line[counter] = buffer[loop];
                counter++;
            }
            line[counter] = 0;
            start = i;
            printf("%s\n",line);
           }
        }
    }

    if(i > start)
    {    
        counter = 0;
        for(loop = i; loop > start; loop--)
        {       
            if((counter == 0) && ((buffer[loop] == 10) || (buffer[loop] == 0)))
            {
                continue;
            }               
            line[counter] = buffer[loop];
            counter++;
        }
        line[counter] = 0;
        printf("%s\n",line);

        return;
    }
}






int main(int argc, char* argv[])
{
	char const* const  tempFileName = "tmp"; 
    FILE* tempFile = fopen(tempFileName, "w+");
	char line[2048];

	argv0 = "bocabajo";
	if (argc==1){
		while (fgets(line, sizeof(line),stdin)) {	
        fputs(line,tempFile);
		
	    
    }
		readfileinreverse(tempFile);
	    remove(tempFileName);
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
        	
        fputs(line,tempFile);
	    
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
	  readfileinreverse(tempFile);
	  //remove(tempFileName);
	  exit(EX_OK);
}
	Error(EX_OSERR, "No se pudo ubicar la memoria dinamica necesaria.");
    exit(EX_OSERR);	
}

