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

float fuzzy_angle[7], fuzzy_speed[7], result_inference[7];
int range[7][2] = { {-90,-60},{-90, -30},{-60, 0},{-30,30},{0,60},{30,90},{60,90} };

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

void fuzzy(float angle, float speed){
	int i;
	float s=speed;
	printf("fuzzy(%f,%f) \n", angle, s);
	if(angle < 0 && speed > 0)s=speed*(-1);
	for(i=0; i<7; i++){
		fuzzy_angle[i]=belonging(i,angle)*100;
		fuzzy_speed[i]=belonging(i,s)*100;
	}
	printf("\n");
}

void inference(){
	int phase;
	for(phase=0; phase<7; phase++){
		printf("phase(%d) : belong(angle)=%f belong(speed)=%f \n", phase, fuzzy_angle[phase], fuzzy_speed[phase]);
		if(fuzzy_angle[phase]==0.0 || fuzzy_speed[phase]==0.0){
			result_inference[phase] = fuzzy_angle[phase] + fuzzy_speed[phase];
		}else{
			result_inference[phase] = min(fuzzy_angle[phase], fuzzy_speed[phase]);
		}
		printf("inference: phase=%d belong=%f \n", phase, result_inference[phase]);
 	}
}

void defuzzy(){
	int i, found=0, min_range=0, max_range=0, tmp;
	int phases[2] = {-1, -1};

	float result = 0.0;

	//looking for phases
	for(i=0; i<7; i++){
		if(result_inference[i]!=0){
			phases[found]=i;
			found++;
		}
	}

	if(found==1){
		min_range=range[phases[0]][0];
		max_range=range[phases[0]][1];

		printf("defuzzy : phase=%d min=%d max=%d \n", phases[0], min_range, max_range);

		for(i=0; i<=(max_range-min_range)/10; i++) result+=min_range+i*10;
		result*=result_inference[phases[0]];
		result/=((max_range-min_range)/10)*result_inference[phases[0]];

		printf("defuzzy : result = %f \n", result);
	}else{
		min_range=min(range[phases[0]][0], range[phases[1]][0]);
		max_range=max(range[phases[0]][1], range[phases[1]][1]);

		printf("defuzzy : phase=%d min=%d max=%d \n", phases[0], min_range, max_range);

		for(i=0; i<=(range[phases[0]][1]-range[phases[0]][0])/10; i++) tmp+=min_range+i*10;
		tmp*=result_inference[phases[0]];
		result=tmp;
		tmp=0;

		for(i=0; i<=(range[phases[0]][1]-range[phases[0]][0])/10; i++) tmp+=min_range+i*10;
		tmp*=result_inference[phases[0]];
		result+=tmp;

		result/=((range[phases[0]][1]-range[phases[0]][0])/10)*result_inference[phases[0]]+((range[phases[1]][1]-range[phases[1]][0])/10)*result_inference[phases[1]];

		printf("defuzzy : result = %f \n", result);
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
	float angle=-80.0, speed=-20.0;

	fuzzy(angle,speed);

	for(i=0; i<7; i++)
		printf("fuzzy_angle[%d] = %f \n", i, fuzzy_angle[i]);

	for(i=0; i<7; i++)
		printf("fuzzy_speed[%d] = %f \n", i, fuzzy_speed[i]);

	inference();
	defuzzy();
	return 0;
}
