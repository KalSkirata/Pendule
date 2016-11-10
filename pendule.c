#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANGLE_MAX 90

#define NB 0
#define NM 1
#define NS 2
#define ZE 3
#define PS 4
#define PM 5
#define PB 6

int fuzzy(float data){
	if(data==0.0){
		return ZE;
	}else if(data<0){
        	if(data<=ANGLE_MAX*(2/3)*(-1)){
                	return NB;
        	}else if(data<=ANGLE_MAX*(1/3)*(-1)){
                	return NM;
        	}else{
			return NS;
		}
	}else{
        	if(data>=ANGLE_MAX*(2/3)){
        	        return PB;
        	}else if(data>=ANGLE_MAX*(1/3)){
        	        return PM;
        	}else{
			return PS;
		}
	}	
}

int read_csv(){
	FILE *fichier;
        char tampon[BUFSIZ];
        int actuel = 0;
        int c;


        fichier = fopen ("fichier.csv", "r");
        if (!fichier) {
                return -1;
        }

        while ((c = fgetc (fichier)) != EOF) {
                if (c == ',' || c == '\n') {
                        printf ("%ld\n", strtol (tampon, NULL, 10));
                        actuel = 0;
                        memset (tampon, 0, sizeof tampon);
                } else {
                        tampon[actuel++] = c;
                }
        }
        fclose (fichier);
	return 0;
}
 
int
main (void)
{
	read_csv();
        return 0;
}
