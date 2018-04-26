#include <math.h>
#include <time.h>
#include <pthread.h>
#include "GetConf.c"
#include "list.c"
#include <string.h>
#include "generatecars.h"

struct arguments_cars {
    int speed;
    //char  route;
    const char *a[5];
    char *parada1;
    char *parada2;
    char *parada3;
    char *parada4;
    char *parada5;
    char *color;
    char *model;
    int counted_trips;
    int priority; //1 radioactive cars, 2 ambulances, 3 (cars and buses)
    int ID;
};

struct arguments_buses {
    char *color;
    int priority; //1 radioactive cars, 2 ambulances, 3 (cars and buses)
    int ID;
};

tpointer *head_init_RR;


GenerationParams createNewGenerationParams(double median_distribution,int Average_car_speed,int ambulance_percentage,int radioactive_percentage, char * scheduler)
{
    GenerationParams newGenerationParams = (GenerationParams)malloc(sizeof(struct GenVars));
    if(newGenerationParams == NULL)
    {
    	free(newGenerationParams);
        return NULL;
    }
    else
    {
	    	newGenerationParams->median_distribution = median_distribution;
			newGenerationParams->Average_car_speed=Average_car_speed;
			newGenerationParams->ambulance_percentage=ambulance_percentage;
			newGenerationParams->radioactive_percentage=radioactive_percentage;
			newGenerationParams->scheduler=scheduler;


		    return newGenerationParams;

    }
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the null-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


char* getRandomPosition(){
	char * a;
	a = concat(getRandomLetter(),getRandomNum());
    return a;
}

char* getRandomLetter(){
	int number = 1+rand()%26;
	char* letter;
	switch(number)   
	{  
    case 1:  
        letter ="A"; 
        break; 
    case 2:  
        letter ="B"; 
        break;
	case 3:  
        letter ="C";
        break;
    case 4:  
        letter ="D";
        break;  
    case 5:  
        letter ="E";
        break; 
	case 6:  
        letter ="F";
        break;
    case 7:  
        letter ="G";  
        break;
    case 8:  
        letter ="H"; 
        break;
	case 9:  
        letter ="I";
        break;
	case 10:  
        letter ="J";  
        break;
    case 11:  
        letter ="K"; 
        break;
	case 12:  
        letter ="M";
        break;
    case 13:  
        letter ="N"; 
        break; 
    case 14:  
        letter ="L"; 
        break;
	case 15:  
        letter ="O";
        break;
    case 16:  
        letter ="P";  
        break;
    case 17:  
        letter ="Q"; 
        break;
	case 18:  
        letter ="R";
        break;
    case 19:  
        letter ="S";  
        break;
    case 20:  
        letter ="T"; 
        break;
	case 21:  
        letter ="U";
        break;
    case 22:  
        letter ="V";  
        break;
    case 23:  
        letter ="W"; 
        break;
	case 24:  
        letter ="X";
        break;
	case 25:  
        letter ="Y";  
        break;
    case 26:  
        letter ="Z";
        break;

	}  
	return letter;

}

char* getRandomColor(){
	int number = 1+rand()%9;
    char* color;
    switch(number)   
    {  
    case 1:  
        color ="Red";  
        break;
    case 2:  
        color ="Blue"; 
        break;
    case 3:  
        color ="Black";
        break;
    case 4:  
        color ="Cyan"; 
        break; 
    case 5:  
        color ="White"; 
        break; 
    case 6:  
        color ="Purple"; 
        break; 
    case 7:  
        color ="Green"; 
        break; 
    case 8:  
        color ="Brown"; 
        break; 
    case 9:  
        color ="Yellow"; 
        break;  
    default :  
        color ="pink";  
    }  
    return color;

}
void writeLogMSJ(char * message){
		FILE *fp;
	   	fp = fopen("events.log", "a");
   		fprintf(fp,"<<%s>>\n", message);
   		fclose(fp);
   		//printf("<<%s>>\n", message);

}
char* getRandomModel(){

	int number = 1+rand()%14;
    char* car;
    switch(number)   
    {  
    case 1:  
        car ="Mercedes-Benz";  
        break;
    case 2:  
        car ="Audi"; 
        break;
    case 3:  
        car ="Hiuday";
        break;
    case 4:  
        car ="MClaren"; 
        break; 
    case 5:  
        car ="Aston-Martin"; 
        break; 
    case 6:  
        car ="Porshe"; 
        break; 
    case 7:  
        car ="RAM"; 
        break; 
    case 8:  
        car ="Mazda"; 
        break; 
    case 9:  
        car ="Nissan"; 
        break; 
    case 10:  
        car ="Maserati"; 
        break; 
    case 11:  
        car ="Ferrari"; 
        break;
    case 12:  
        car ="Alfa-Romeo"; 
        break; 
    case 13:  
        car ="Bentley"; 
        break; 
    case 14:  
        car ="Lamborgini"; 
        break; 
    default :  
        car ="Honda";  
    }  
    return car;
}

char* getRandomNum(){
    int number = 1+rand()%4;
    char* num;
    switch(number)   
    {  
    case 1:  
        num ="1";  
        break;
    case 2:  
        num ="2"; 
        break;
    case 3:  
        num ="3";
        break;
    case 4:  
        num ="4"; 
        break; 
    default :  
        num ="1";  
    }  
    return num;

}
void wait(unsigned int milliseconds){

    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

void *newCar(void *arguments){
	int i = 0;
	int count = 10;
	char * j = "car";
	for (i; i < count; ++i)
	{
		printf("ha sido generad@ un@ %s\n",j);
		printf("estoy en el segundo %d\n",i);
		wait(150);

	}
}
void *newBus(void *arguments){
	int i = 0;
	int count = 10;
	char * j = "bus";
	for (i; i < count; ++i)
	{
		printf("ha sido generad@ un@ %s\n",j);
		printf("estoy en el segundo %d\n",i);
		wait(150);

	}
}

void* generateCars(GenerationParams genparams)
{
	int R_percentage = genparams->radioactive_percentage;//calculate percentages of cars
	int A_percentage = genparams->ambulance_percentage;
	int Cars_percentage = 100-(R_percentage+A_percentage);

	float createC = round(Cars_percentage * 0.1); // rate of cars produced
 	float createR = round(R_percentage * 0.1); // rate of radioactive cars produced
	float createA = round(A_percentage * 0.1); // rate of ambulances produced

	srand(time(NULL));// initialize a random value
	
	int randomSpeed;

	writeLogMSJ("Starting Buses generation :)");

	double lambda,seconds;// variables to define exponential distributio
	lambda = log (2)/ genparams->median_distribution;
	seconds=lambda*exp(-lambda*0.001);

	pthread_t newCarThread[15];//quantity of threads will be created

	tpointer head_real_time;
	tpointer head_round_robin;//creando la lista para calendarizar round robin
	tpointer head_lottery;//creando la lista para calendarizar lottery
	tpointer head_real_time_soft;//creando la lista para calendarizar real time soft
	tpointer head_real_time_hard;//creando la lista para calendarizar real time hard

	head_round_robin=NULL;//listas vacías al inicio
	head_lottery=NULL;
	head_real_time_soft=NULL;
	head_real_time_hard=NULL;
	head_real_time=NULL;

	int threadCounter = 0;
	int i3;
	char * BusesColors[5];
	BusesColors[0] ="RED";
	BusesColors[1] ="GREEN";
	BusesColors[2] ="AZUL";
	BusesColors[3] ="YELLOW";
	BusesColors[4] ="ORANGE";

	for (i3 = 0; i3 < 5; ++i3)
	{

		randomSpeed = genparams->Average_car_speed + (rand()%5)-4.5;
				struct arguments_buses args;
			    args.color = BusesColors[i3];
			    args.priority = 3;
			    args.ID = threadCounter;

			int err = pthread_create(&newCarThread[threadCounter], NULL, &newCar, (void *)&args);

			if (err != 0){	
				printf("\ncan't create thread :[%s]", strerror(err));
				break;
			}else{
				if (genparams->scheduler == "lottery")
				{
					insertFront(&head_lottery, &newCarThread[threadCounter]);
				}else if(genparams->scheduler == "real_time"){

					insertFront(&head_real_time, &newCarThread[threadCounter]);
				}else{//default round_robin
					insertFront(&head_round_robin, &newCarThread[threadCounter]);
				}
				threadCounter++;
				writeLogMSJ(concat("A bus has been generated: ",BusesColors[i3]));
			}

	}
	int times;//numbers of cicles generating threads
	int i0, i1, i2; //counter to generate ambulances, radioactive cars and cars

	for (times = 0; times < 20 ; ++times)
	{
		for (i0 = 0; i0 < createA; ++i0)//generating ambulances
		{
				randomSpeed = genparams->Average_car_speed + (rand()%6)+1;
				char * myArray[5];
			    myArray[0] = getRandomPosition();
			    myArray[1] = getRandomPosition();
			    myArray[2] = getRandomPosition();
			    myArray[3] = getRandomPosition();
			    myArray[4] = getRandomPosition();
				struct arguments_cars args;
			    args.speed = randomSpeed;
			    args.a[0] = myArray[0];
			    args.a[1] = myArray[1];
			    args.a[2] = myArray[2];
			    args.a[3] = myArray[3];
			    args.a[4] = myArray[4];
			    args.parada1=myArray[0];
			    args.parada2=myArray[1];
			    args.parada3=myArray[2];
			    args.parada4=myArray[3];
			    args.parada5=myArray[4];
			    args.model = "Ambulance";
			    args.color = "Red-white";
			    args.counted_trips =0;
			    args.priority = 2;
			    args.ID = threadCounter;


			int err = pthread_create(&newCarThread[threadCounter], NULL, &newCar, (void *)&args);

			if (err != 0){	
				printf("\ncan't create thread :[%s]", strerror(err));
				break;
			}else{
				insertFront(&head_real_time_soft, &newCarThread[threadCounter]);
				threadCounter++;
			}
			char str[80];
   			sprintf(str, "ID = %d",threadCounter);
			writeLogMSJ(concat("An ambulance has been generated ID->",str));
			wait(seconds*1000);


		}
		for (i1 = 0; i1 < createR; ++i1)//generating radioactive cars
		{
				randomSpeed = genparams->Average_car_speed + (rand()%5)+1;
				char * myArray[5];
			    myArray[0] = getRandomPosition();
			    myArray[1] = getRandomPosition();
			    myArray[2] = getRandomPosition();
			    myArray[3] = getRandomPosition();
			    myArray[4] = getRandomPosition();
				struct arguments_cars args;
			    args.speed = randomSpeed;
			    args.a[0] = myArray[0];
			    args.a[1] = myArray[1];
			    args.a[2] = myArray[2];
			    args.a[3] = myArray[3];
			    args.a[4] = myArray[4];
			    args.parada1=myArray[0];
			    args.parada2=myArray[1];
			    args.parada3=myArray[2];
			    args.parada4=myArray[3];
			    args.parada5=myArray[4];
			    args.model = "Radioactive";
			    args.color = "Green";
			    args.counted_trips =0;
			    args.priority = 1;
			    args.ID = threadCounter;

			int err = pthread_create(&newCarThread[threadCounter], NULL, &newCar, (void *)&args);

			if (err != 0){	
				printf("\ncan't create thread :[%s]", strerror(err));
				break;
			}else{
				insertFront(&head_real_time_hard, &newCarThread[threadCounter]);
				threadCounter++;
			}
			char str[80];
   			sprintf(str, "ID = %d",threadCounter);
			writeLogMSJ(concat("A Radioactive Car has been generated ID->",str));
			wait(seconds*1000);
		}
		for (i2 = 0; i2 < createC; ++i2)//generating car
		{
				randomSpeed = genparams->Average_car_speed + (rand()%5)-2.5;
				char * myArray[5];
			    myArray[0] = getRandomPosition();
			    myArray[1] = getRandomPosition();
			    myArray[2] = getRandomPosition();
			    myArray[3] = getRandomPosition();
			    myArray[4] = getRandomPosition();
				struct arguments_cars args;
			    args.speed = randomSpeed;
			    args.a[0] = myArray[0];
			    args.a[1] = myArray[1];
			    args.a[2] = myArray[2];
			    args.a[3] = myArray[3];
			    args.a[4] = myArray[4];
			    args.parada1=myArray[0];
			    args.parada2=myArray[1];
			    args.parada3=myArray[2];
			    args.parada4=myArray[3];
			    args.parada5=myArray[4];
			    args.model = getRandomModel();
			    args.color = getRandomColor();
			    args.counted_trips =0;
			    args.priority = 3;
			    args.ID = threadCounter;


			int err = pthread_create(&newCarThread[threadCounter], NULL, &newCar, (void *)&args);

			if (err != 0){	
				printf("\ncan't create thread :[%s]", strerror(err));
				break;
			}else{
				if (genparams->scheduler == "lottery")
				{
					insertFront(&head_lottery, &newCarThread[threadCounter]);
				}else if(genparams->scheduler == "real_time"){

					insertFront(&head_real_time, &newCarThread[threadCounter]);
				}else{//default round_robin
					insertFront(&head_round_robin, &newCarThread[threadCounter]);
				}
				threadCounter++;
			}
			char str[80];
   			sprintf(str, "ID = %d",threadCounter);
			writeLogMSJ(concat("A normal Car has been generated ID->",str));
			wait(seconds*1000);
		}
		
		

	}
	pthread_join(newCarThread[1],NULL);
	printf("cars: %s\n", ":)");
	printList(head_round_robin);
	printf("radioactivos: %s\n", ":)");
	printList(head_real_time_hard);
	printf("ambulancias: %s\n", ":)");
	printList(head_real_time_soft);
	printf("saliendo: %s\n", ":)");
	//pthread_exit(NULL);
	return 0;
}



int main()
{
    char* path3 = "configuration.config";
    Conf conf3 = setNewConfiguration();
    Getconf (path3,conf3);


    double mediana;
    mediana = (double) conf3->median_distribution;
//parametros (median_distribution,Average_car_speed,ambulance_percentage,radioactive_percentage,scheduler)
	GenerationParams parametrosr1 = createNewGenerationParams( mediana,conf3->AverageSpeed,conf3->ambulancesPercentage,conf3->radioActiveCarsPercentage,conf3->scheduler);


    generateCars(parametrosr1);


	//printf("Bridge1 rigth normal: %d ambulance_percentage: %d radioactive_percentage: %d \n",cantCarsR,cantAmbulancesR,cantRadioactivesR);

}
