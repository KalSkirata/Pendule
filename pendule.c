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

//TODO fix defuzzy (retourne 0 quand un des deux param est négatif)

struct rule{
	int phase;
	float belong;
};

typedef struct rule rule;

float min3(float a, float b, float c){
	return min(min(a,b),c);
}

float belonging(int phase, float x){
	switch(phase){
		case NB:
			return max(min(1.0,(-60.0-x)/30.0),0.0);
			break;
		case NM:
			return max(min((x+90.0)/30.0,(-30.0-x)/30.0),0.0);
			break;
		case NS:
			return max(min((x+60.0)/30.0,(-x)/30.0),0.0);
			break;
		case ZE:
			return max(min((x+30.0)/30.0,(30.0-x)/30.0),0.0);
			break;
		case PS:
			return max(min3(x/30.0,(-x+60.0)/30.0,1.0),0.0);
			break;
		case PM:
			return max(min3((x-30.0)/30.0,(90.0-x)/30.0,1.0),0.0);
			break;
		case PB:
			return max(min(1.0,(x-60.0)/30.0),0.0);
			break;
		default:
			break;
	}
}

void fuzzy(float data){
	int i;
	for(i=0; i<7; i++){
		printf("fuzzy : phase=%d belong=%f \n", i, belonging(i,data)*100);
	}
	printf("\n");
}

void defuzzy(float angle, float speed){
	int phase;
	for(phase=0; phase<7; phase++){
		rule r;
		r.phase=phase;
		printf("belong(angle)=%f belong(speed)=%f \n", belonging(phase, angle), belonging(phase, angle));
		r.belong=min(belonging(phase, angle), belonging(phase, speed)); //produit cartésien
		printf("defuzzy: phase=%d belong=%f \n", r.phase, r.belong);
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
	defuzzy(-50.0,20.0);
	return 0;
}
