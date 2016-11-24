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

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

float min3(float a, float b, float c){
	return min(min(a,b),c);
}

float belonging(int phase, float x){
	switch(phase){
		case NB:
			printf("NB : ");
			return max(min(1.0,(-60.0-x)/30.0),0.0);
			break;
		case NM:
			printf("NM : ");
			return max(min((x+90.0)/30.0,(-30.0-x)/30.0),0.0);
			break;
		case NS:
			printf("NS : ");
			return max(min((x+60.0)/30.0,(-x)/30.0),0.0);
			break;
		case ZE:
			printf("ZE : ");
			return max(min((x+30.0)/30.0,(30.0-x)/30.0),0.0);
			break;
		case PS:
			printf("PS : ");
			return max(min3(x/30.0,(-x+60.0)/30.0,1.0),0.0);
			break;
		case PM:
			printf("PM : ");
			return max(min3((x-30.0)/30.0,(90.0-x)/30.0,1.0),0.0);
			break;
		case PB:
			printf("PB : ");
			return max(min(1.0,(x-60.0)/30.0),0.0);
			break;
		default:
			break;
	}
}

void fuzzy(float data){
	int i;
	for(i=0; i<7; i++){
		printf("%f \n",belonging(i,data)*100);
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
 
int main(void){
	//read_csv();
	fuzzy(60);
	return 0;
}
