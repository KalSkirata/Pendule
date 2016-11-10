#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

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
