#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "GetConf.h"



Conf setNewConfiguration()//set up a new configuration of user
{
    Conf newConfig = (Conf)malloc(sizeof(struct configuration));
    if(newConfig == NULL)
    {
    	free(newConfig);
        return NULL;
    }
    else
    {
	    	newConfig->TCMB1="";
			newConfig->S_Time_right1=0;
			newConfig->S_Time_left1=0;
			newConfig->TCMB2="";
			newConfig->S_Time_right2=0;
			newConfig->S_Time_left2=0;
			newConfig->TCMB3="";
			newConfig->S_Time_right3=0;
			newConfig->S_Time_left3=0;
			newConfig->k=0;
			newConfig->ambulancesPercentage=0;
			newConfig->radioActiveCarsPercentage=0;
			newConfig->median_distribution=0;
			newConfig->scheduler="";

		    return newConfig;

    }
}

char *createNewCharArray( int size) //array use to store params data
{
    char* newCharArray = (char *)malloc(size*sizeof(char));
    if(newCharArray == NULL)
    {
    	free(newCharArray);
        return NULL;
    }
    else
    {
		return newCharArray;
	}
}


void remove_all_chars(char* str, char c) { //clean data array
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}

void Getconf (char* path,Conf conf)//get stored configuration
{

    FILE* fid;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
	char *TCMB1 = createNewCharArray(50);
	char *TCMB2 = createNewCharArray(50);
	char *TCMB3 = createNewCharArray(50);
	char *scheduler = createNewCharArray(50);

    //Define the default log file
    //Open the logfile

if ((fid = fopen(path,"r")) == NULL)
	{
		return ;
	}
	//Parse the log file

	while ((read = getline(&line, &len, fid)) != -1)
	{
		if(strstr(line, "#")) continue; //Ignore the lines starting with #
		else if(strstr(line, "TCMB1="))
		{

			int lenght = (strstr(line, "\n") - line	);
			memcpy(TCMB1, line,lenght); //Get the path
			TCMB1[lenght] = 0;
			conf->TCMB1=&TCMB1[6];

		}
		else if (strstr(line, "S_Time_right1="))
		{
			char *S_Time_right1 = strstr(line, "S_Time_right1=") + 14; //Get the custom logfile path
			conf->S_Time_right1= atof(S_Time_right1);


		}
		else if (strstr(line, "median_distribution="))
		{
			char *median_distribution = strstr(line, "median_distribution=") + 20; //Get the custom logfile path
			conf->median_distribution= atof(median_distribution);


		}
		else if (strstr(line, "S_Time_left1="))
		{
			char *S_Time_left1 = strstr(line, "S_Time_left1=") + 13; //Get the custom logfile path
			conf->S_Time_left1= atoi(S_Time_left1);
		}
		else if(strstr(line, "TCMB2="))
		{

			int lenght = (strstr(line, "\n") -line	);
			memcpy(TCMB2, line,lenght); //Get the path
			TCMB2[lenght] = 0;
			conf->TCMB2=&TCMB2[6];
		}
		else if(strstr(line, "S_Time_right2="))
		{
			char *S_Time_right2 = strstr(line, "S_Time_right2=") + 14; //Get the custom logfile path
			conf->S_Time_right2= atoi(S_Time_right2);
		}
		else if (strstr(line, "S_Time_left2="))
		{
			char *S_Time_left2 = strstr(line, "S_Time_left2=") + 13; //Get the custom logfile path
			conf->S_Time_left2 = atoi(S_Time_left2);
		}
		else if (strstr(line, "TCMB3="))//TCMB3
		{
			int lenght = (strstr(line, "\n") -line	);
			memcpy(TCMB3, line,lenght); //Get the path
			TCMB3[lenght] = 0;
			conf->TCMB3=&TCMB3[6];
			//conf->TCMB3  = strstr(line, "TCMB3=") + 8; //Get the CPU threshold

		}
		else if(strstr(line, "S_Time_right3="))
		{
			char *S_Time_right3 = strstr(line, "S_Time_right3=") + 14; //Get the custom logfile path
			conf->S_Time_right3 = atoi(S_Time_right3);
		}
		else if (strstr(line, "S_Time_left3="))
		{
			char *S_Time_left3 = strstr(line, "S_Time_left3=") + 13; //Get the custom logfile path
			conf->S_Time_left3 = atoi(S_Time_left3);
		}
		/////////////////////////////////////
		else if (strstr(line, "AverageSpeed="))
		{
			char* AverageSpeed = strstr(line, "AverageSpeed=") + 13; //Get the Memory threshold
			conf->AverageSpeed = atoi(AverageSpeed);
		}
		else if (strstr(line, "k="))
		{
			char* k = strstr(line, "k=") + 2; //Get the Memory threshold
			conf->k = atoi(k);
		}
		else if (strstr(line, "ambulancesPercentage="))
		{
			char* ambulancesPercentage = strstr(line, "ambulancesPercentage=") + 21; //Get the Memory threshold
			conf->ambulancesPercentage = atoi(ambulancesPercentage);
		}
		else if (strstr(line, "radioActiveCarsPercentage="))
		{
			char* radioActiveCarsPercentage = strstr(line, "radioActiveCarsPercentage=") + 26; //Get the Memory threshold
			conf->radioActiveCarsPercentage = atoi(radioActiveCarsPercentage);
		}
		else if (strstr(line, "scheduler="))
		{

			int lenght = (strstr(line, "\n") -line	);
			memcpy(scheduler, line,lenght); //Get the path
			scheduler[lenght] = 0;
			conf->scheduler=&scheduler[10];
			
		}

	}
	fclose(fid);
	//return conf;
}


/*

 //main to prove getConfiguration
void main(){

	char* path1 = "configuration.config";

	Conf Initial_config = setNewConfiguration();

	Getconf (path1,Initial_config);
	
	//bridgeconf3 = Getconf (path1);



	printf("TCMB1 --> %s \n", Initial_config->TCMB1);
	printf("S_Time_right1 --> %i \n", Initial_config->S_Time_right1);
	printf("S_Time_left1 --> %i \n", Initial_config->S_Time_left1);
	printf("TCMB2 --> %s \n", Initial_config->TCMB2);
	printf("S_Time_right2 --> %i \n", Initial_config->S_Time_right2);
	printf("S_Time_left2 --> %i \n", Initial_config->S_Time_left2);
	printf("TCMB3 --> %s \n", Initial_config->TCMB3);
	printf("S_Time_right3 --> %i \n", Initial_config->S_Time_right3);
	printf("S_Time_left3 --> %i \n", Initial_config->S_Time_left3);
	printf("AverageSpeed --> %i \n", Initial_config->AverageSpeed);
	printf("k --> %i \n", Initial_config->k);
	printf("ambulancesPercentage --> %i \n", Initial_config->ambulancesPercentage);
	printf("radioActiveCarsPercentage --> %i \n", Initial_config->radioActiveCarsPercentage);
	printf("scheduler --> %i \n", Initial_config->scheduler);
	printf("median_distribution --> %i \n", Initial_config->median_distribution);





}
*/
