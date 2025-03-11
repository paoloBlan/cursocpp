#include <stdio.h>
int main()
{ 
   char ifilename[] = "entrada.txt";
   char ofilename[] = "salida.txt";
   char name[30];
   int idNum;

   FILE *ofp, *ifp;                    
   ifp = fopen(ifilename,"r");         
   fscanf(ifp,"%s %d",name,&idNum); 	
   ofp = fopen(ofilename,"w");         
   fprintf(ofp,"%d %s\n",idNum, name); 
   fclose(ifp); fclose(ofp);           
   return 0;

} 
