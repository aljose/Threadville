/*
 * GetConf.h
 *
 *  Created on: Oct 9, 2016
 *      Author: edwin
 */

#ifndef GETCONF_H_
#define GETCONF_H_


typedef struct configuration

{

	char * TCMB1;
	char * TCMB2;
	char * TCMB3;
	char * scheduler;
	int S_Time_right1;
	int S_Time_left1;
	int S_Time_right2;
	int S_Time_left2;
	int S_Time_right3;
	int S_Time_left3;
	int AverageSpeed;
	int k;
	int ambulancesPercentage;
	int radioActiveCarsPercentage;
	float median_distribution;
    /*int length;
	float mleft;
	float mright;
	int carspeedleft;
	int carspeedright;
	char *traffic;
	int semaphoretime;
	int transitcars;
	int ambulancesright;
	int ambulancesleft;
	int radioactiveright;
	int radioactiveleft;
	char *carshedulling;*/

}*Conf; //Conf cambiar por Conf

Conf setNewConfiguration();
char *createNewCharArray( int size);
void remove_all_chars(char* str, char c);
void Getconf (char* path,Conf conf);


#endif /* GETCONF_H_ */

/*TCMB1=
S_Time_right1=
S_Time_left1=
TCMB2=
S_Time_right2=
S_Time_left2=
TCMB3=
S_Time_right3=
S_Time_left3=
AverageSpeed=
k=
ambulancesPercentage=
radioActiveCarsPercentage=
scheduler=*/