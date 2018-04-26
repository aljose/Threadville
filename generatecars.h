

#ifndef GENERATECARS_H_
#define GENERATECARS_H_


typedef struct GenVars//parameters for creating a new car

{
    double median_distribution;
	int Average_car_speed;
	int ambulance_percentage;
	int radioactive_percentage;
	char * scheduler;

}*GenerationParams;

//GenerationParams createNewGenerationParams(double median,int carspeed,int ambulance,int radioactive, char* scheduler);

void* generateCars(GenerationParams genparams); 
void wait(unsigned int milliseconds);
char* getRandomPosition();
char* getRandomLetter();
char* getRandomNum();
char* concat(const char *s1, const char *s2);
char* getRandomModel();
char* getRandomColor();


#endif /* GENERATECARS_H_ */
