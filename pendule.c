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
	float min=a;
	if(b<min)min=b;
	if(c<min)min=c;
	return min;
}

float belonging(int phase, int x){
	switch(phase){
		case NB:
			printf("min(1,(-60-x)/30)=%d",min(1,(-60-x)/30));
			return max(min(1,(-60-x)/30),0);
			break;
		case NM:
			return max(min((x+90)/30,(-30-x)/30),0);
			break;
		case NS:
			return max(min((x+60)/30,(-x)/30),0);
			break;
		case ZE:
			return max(min((x+30)/30,(30-x)/30),0);
			break;
		case PS:
			return max(min3(x/30,(-x+60)/30,1),0);
			break;
		case PM:
			printf("min3((x-30)/30,(90-x)/30,1)=%f", min3((x-30)/30,(90-x)/30,1));
			return max(min3((x-30)/30,(90-x)/30,1),0);
			break;
		case PB:
			return max(min(1,(x-60)/30),0);
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
	for(i=0; i<8; i++){
		//printf("data=%f phase=%d appartenance=%f \n",data, i, appartenance(data, i));
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
	int i;
	for(i=0; i<8; i++){
		printf("%f \n",belonging(i,40));
	}
	return 0;
}
