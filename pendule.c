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

#define MIN_NB 60

//TODO issue with min and max

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

int categorise(float data);

//don't check min for 0 and 6
/*int min[7][2] = {{-90,-60}, {-90,-30}, {-60,0}, {-30,30}, {0,60}, {30,60}, {60,90}};

 appartenance sur les nombres positifs : (mesure-minimum)/pas
	pas=0.3
	 
	ex : 75=(0.3*50)+60 => 75-60=0.3*50 => (75-60)/0.3=50

float appartenance(float data, int phase){		
	float median;
	if(data<min[phase][0] || data>min[phase][1]){
		printf("first ");
		return 0;
	}

	if(phase==0 || phase==7){
		return (data-60)/0.3;
	}else{
		if(data==abs(min[phase][0]) || data==abs(min[phase][1])){
			return 0;
		}else{
			median = (min[phase][0]+min[phase][1])/2;
			if(data<=median){
				printf("%f-%d)/0.3\n", data, min[phase][0]);
				return (data-abs(min[phase][0]))/0.3;
			}else{
				printf("%f-%d)/0.3\n", data, min[phase][1]);
				return (data-abs(min[phase][1]))/0.3;
			}
		}
	}
}*/

float min3(float a, float b, float c){
	return min(min(a,b),c);
}

float belonging(int phase, float x){
	switch(phase){
		case NB:
			printf("NB : ");
			//printf("min(1,(-60-x)/30)=%f",min(1.0,(-60.0-x)/30.0));
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
			//printf("min3((%f-30)/30,(90-%f)/30,1)=%f \n", x,x,min3((x-30.0)/30.0,(90.0-x)/30.0,1.0));
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

int categorise(float data){
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
