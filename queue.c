#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 566

char * intArray[MAX];
int front = 0;
int rear = -1;
int itemCount = 0;
int count = 0;
char * nodeArray[MAX];

char * peek() {
   return intArray[front];
}

bool isEmpty() {
   return itemCount == 0;
}

bool isFull() {
   return itemCount == MAX;
}

int size() {
   return itemCount;
}  

void insert(char * data) {

   if(!isFull()) {
	
      if(rear == MAX-1) {
         rear = -1;            
      }       

      intArray[++rear] = data;
      nodeArray[count] = data;
      count++;
      itemCount++;
   }
}

char * getName(int i){
   return nodeArray[i];

}

int searchNumByName (char * name){
 int i = 0;
 for(i=0; i<MAX; i++){
   if(nodeArray[i]==name){
      break;
   }
 }
 return i;
}

char * removeData() {
   char * data = intArray[front++];
	
   if(front == MAX) {
      front = 0;
   }
	
   itemCount--;
   return data;  
}
void fillQueue (){
/*Y square*/
   insert("Y1");
   insert("Y2");
   insert("Y3");
   insert("Y4");
   insert("Y5");
   insert("Y6");
   insert("Y7");
   insert("Y8");
   insert("Y9");
   insert("Y10");
   insert("Y11");
   insert("Y12");
   insert("Y13");
   insert("Y14");
   insert("Y15");
/*Z square*/
   insert("Z1");
   insert("Z2");
   insert("Z3");
   insert("Z4");
   insert("Z5");
   insert("Z6");
   insert("Z7");
   insert("Z8");
   insert("Z9");
   insert("Z10");
   insert("Z11");
   insert("Z12");
   insert("Z13");
   insert("Z14");
   insert("Z15");
   /*A square*/
   insert("A1");
   insert("A2");
   insert("A3");
   insert("A4");
/*B square*/
   insert("B1");
   insert("B2");
   insert("B3");
   insert("B4");
/*C square*/
   insert("C1");
   insert("C2");
   insert("C3");
   insert("C4");
/*D square*/
   insert("D1");
   insert("D2");
   insert("D3");
   insert("D4");
/*E square*/
   insert("E1");
   insert("E2");
   insert("E3");
   insert("E4");
/*F square*/
   insert("F1");
   insert("F2");
   insert("F3");
   insert("F4");
/*G sqaure*/
   insert("G1");
   insert("G2");
   insert("G3");
   insert("G4");
/*H square*/
   insert("H1");
   insert("H2");
   insert("H3");
   insert("H4");
/*I square*/
   insert("I1");
   insert("I2");
   insert("I3");
   insert("I4");
/*J square*/
   insert("J1");
   insert("J2");
   insert("J3");
   insert("J4");
/*K square*/
   insert("K1");
   insert("K2");
   insert("K3");
   insert("K4");
/*L square*/
   insert("L1");
   insert("L2");
   insert("L3");
   insert("L4");
/*M square*/
   insert("M1");
   insert("M2");
   insert("M3");
   insert("M4");
/*N square*/
   insert("N1");
   insert("N2");
   insert("N3");
   insert("N4");
/*O square*/
   insert("O1");
   insert("O2");
   insert("O3");
   insert("O4");
/*P square*/
   insert("P1");
   insert("P2");
   insert("P3");
   insert("P4");
/*Q square*/
   insert("Q1");
   insert("Q2");
   insert("Q3");
   insert("Q4");
/*R square*/
   insert("R1");
   insert("R2");
   insert("R3");
   insert("R4");
/*S square*/
   insert("S1");
   insert("S2");
   insert("S3");
   insert("S4");
/*T square*/
   insert("T1");
   insert("T2");
   insert("T3");
   insert("T4");
/*U square*/
   insert("U1");
   insert("U2");
   insert("U3");
   insert("U4");
/*V square*/
   insert("V1");
   insert("V2");
   insert("V3");
   insert("V4");
/*W square*/
   insert("W1");
   insert("W2");
   insert("W3");
   insert("W4");
/*X square*/
   insert("X1");
   insert("X2");
   insert("X3");
   insert("X4");
/*Streets*/
   /*Street A EAST*/
   insert("_A1");
   insert("_A2");
   insert("_A3");
   insert("_A4");
   insert("_A5");
   insert("_A6");
   insert("_A7");
   insert("_A8");
   insert("_A9");
   insert("_A10");
   insert("_A11");
   insert("_A12");
   insert("_A13");
   insert("_A14");
   insert("_A15");
   /*Street A Highway*/
   insert("_A16");
   insert("_A17");
   insert("_A18");
   /*Street A West D ->*/
   insert("_A19");
   insert("_A20");
   insert("_A21");
   insert("_A22");
   insert("_A23");
   /*E1 - D4 ->*/
   insert("_A24");
   insert("_A25");
   insert("_A26");
   insert("_A27");
   insert("_A28");
   /*E4 - F1 ->*/
   insert("_A29");
   insert("_A30");
   insert("_A31");
   insert("_A32");
   insert("_A33");
   /*Street B EAST*/
   insert("_B1");
   insert("_B2");
   insert("_B3");
   insert("_B4");
   insert("_B5");
   insert("_B6");
   insert("_B7");
   insert("_B8");
   insert("_B9");
   insert("_B10");
   insert("_B11");
   insert("_B12");
   insert("_B13");
   insert("_B14");
   insert("_B15");
   /*Street B bridge 1*/
   insert("_B16");
   insert("_B17");
   insert("_B18");
   insert("_B19");
   insert("_B20");
   /*Street B West*/
   insert("_B21");
   insert("_B22");
   insert("_B23");
   insert("_B24");
   insert("_B25");
   insert("_B26");
   insert("_B27");
   insert("_B28");
   insert("_B29");
   insert("_B30");
   insert("_B31");
   insert("_B32");
   insert("_B33");
   insert("_B34");
   insert("_B35");
   /*Street C EAST*/
   insert("_C1");
   insert("_C2");
   insert("_C3");
   insert("_C4");
   insert("_C5");
   insert("_C6");
   insert("_C7");
   insert("_C8");
   insert("_C9");
   insert("_C10");
   insert("_C11");
   insert("_C12");
   insert("_C13");
   insert("_C14");
   insert("_C15");
   /*Street B bridge 1 done in segment above*/
   /*Street B West*/
   insert("_C21");
   insert("_C22");
   insert("_C23");
   insert("_C24");
   insert("_C25");
   insert("_C26");
   insert("_C27");
   insert("_C28");
   insert("_C29");
   insert("_C30");
   insert("_C31");
   insert("_C32");
   insert("_C33");
   insert("_C34");
   insert("_C35");
   /*Street D EAST*/
   insert("_D1");
   insert("_D2");
   insert("_D3");
   insert("_D4");
   insert("_D5");
   insert("_D6");
   insert("_D7");
   insert("_D8");
   insert("_D9");
   insert("_D10");
   insert("_D11");
   insert("_D12");
   insert("_D13");
   insert("_D14");
   insert("_D15");
   /*Street D bridge 1*/
   insert("_D16");
   insert("_D17");
   insert("_D18");
   insert("_D19");
   insert("_D20");
   /*Street D West*/
   insert("_D21");
   insert("_D22");
   insert("_D23");
   insert("_D24");
   insert("_D25");
   insert("_D26");
   insert("_D27");
   insert("_D28");
   insert("_D29");
   insert("_D30");
   insert("_D31");
   insert("_D32");
   insert("_D33");
   insert("_D34");
   insert("_D35");
   /*Street E EAST*/
   insert("_E1");
   insert("_E2");
   insert("_E3");
   insert("_E4");
   insert("_E5");
   insert("_E6");
   insert("_E7");
   insert("_E8");
   insert("_E9");
   insert("_E10");
   insert("_E11");
   insert("_E12");
   insert("_E13");
   insert("_E14");
   insert("_E15");
   /*Street D bridge 2 done in segment above*/
   /*Street B West*/
   insert("_E21");
   insert("_E22");
   insert("_E23");
   insert("_E24");
   insert("_E25");
   insert("_E26");
   insert("_E27");
   insert("_E28");
   insert("_E29");
   insert("_E30");
   insert("_E31");
   insert("_E32");
   insert("_E33");
   insert("_E34");
   insert("_E35");
   /*Street F EAST*/
   insert("_F1");
   insert("_F2");
   insert("_F3");
   insert("_F4");
   insert("_F5");
   insert("_F6");
   insert("_F7");
   insert("_F8");
   insert("_F9");
   insert("_F10");
   insert("_F11");
   insert("_F12");
   insert("_F13");
   insert("_F14");
   insert("_F15");
   /*Street F bridge 3*/
   insert("_F16");
   insert("_F17");
   insert("_F18");
   insert("_F19");
   insert("_F20");
   /*Street F West*/
   insert("_F21");
   insert("_F22");
   insert("_F23");
   insert("_F24");
   insert("_F25");
   insert("_F26");
   insert("_F27");
   insert("_F28");
   insert("_F29");
   insert("_F30");
   insert("_F31");
   insert("_F32");
   insert("_F33");
   insert("_F34");
   insert("_F35");
   /*Street G EAST*/
   insert("_G1");
   insert("_G2");
   insert("_G3");
   insert("_G4");
   insert("_G5");
   insert("_G6");
   insert("_G7");
   insert("_G8");
   insert("_G9");
   insert("_G10");
   insert("_G11");
   insert("_G12");
   insert("_G13");
   insert("_G14");
   insert("_G15");
   /*Street G bridge 3 done in segment above*/
   /*Street G West*/
   insert("_G21");
   insert("_G22");
   insert("_G23");
   insert("_G24");
   insert("_G25");
   insert("_G26");
   insert("_G27");
   insert("_G28");
   insert("_G29");
   insert("_G30");
   insert("_G31");
   insert("_G32");
   insert("_G33");
   insert("_G34");
   insert("_G35");
   /*Street H EAST*/
   insert("_H1");
   insert("_H2");
   insert("_H3");
   insert("_H4");
   insert("_H5");
   insert("_H6");
   insert("_H7");
   insert("_H8");
   insert("_H9");
   insert("_H10");
   insert("_H11");
   insert("_H12");
   insert("_H13");
   insert("_H14");
   insert("_H15");
   /*Street H Highway*/
   insert("_H16");
   insert("_H17");
   insert("_H18");
   insert("_H19");
   insert("_H20");
   /*Street H West*/
   insert("_H21");
   insert("_H22");
   insert("_H23");
   insert("_H24");
   insert("_H25");
   insert("_H26");
   insert("_H27");
   insert("_H28");
   insert("_H29");
   insert("_H30");
   insert("_H31");
   insert("_H32");
   insert("_H33");
   insert("_H34");
   insert("_H35");
/*Avenues*/
   /*Avenue I EAST*/
   insert("_I1");
   insert("_I2");
   insert("_I3");
   insert("_I4");
   insert("_I5");

   insert("_I6");
   insert("_I7");
   insert("_I8");
   insert("_I9");
   insert("_I10");

   insert("_I11");
   insert("_I12");
   insert("_I13");
   insert("_I14");
   insert("_I15");
   
   insert("_I16");
   insert("_I17");
   insert("_I18");
   insert("_I19");
   insert("_I20");
   /*Avenue J EAST*/
   insert("_J1");
   insert("_J2");
   insert("_J3");
   insert("_J4");
   insert("_J5");

   insert("_J6");
   insert("_J7");
   insert("_J8");
   insert("_J9");
   insert("_J10");

   insert("_J11");
   insert("_J12");
   insert("_J13");
   insert("_J14");
   insert("_J15");
   
   insert("_J16");
   insert("_J17");
   insert("_J18");
   insert("_J19");
   insert("_J20");
   /*Avenue K EAST*/
   insert("_K1");
   insert("_K2");
   insert("_K3");
   insert("_K4");
   insert("_K5");

   insert("_K6");
   insert("_K7");
   insert("_K8");
   insert("_K9");
   insert("_K10");

   insert("_K11");
   insert("_K12");
   insert("_K13");
   insert("_K14");
   insert("_K15");
   
   insert("_K16");
   insert("_K17");
   insert("_K18");
   insert("_K19");
   insert("_K20");
/*Highway L EAST*/
   insert("_L1");
   insert("_L2");
   insert("_L3");
   insert("_L4");
   insert("_L5");

   insert("_L6");
   insert("_L7");

   insert("_L8");
   insert("_L9");
   insert("_L10");
   insert("_L11");
   insert("_L12");

   insert("_L13");
   insert("_L14");

   insert("_L15");
   insert("_L16");
   insert("_L17");
   insert("_L18");
   insert("_L19");

   insert("_L20");
   insert("_L21");

   insert("_L22");
   insert("_L23");
   insert("_L24");
   insert("_L25");
   insert("_L26");
/*Highway M EAST*/
   insert("_M1");
   insert("_M2");
   insert("_M3");
   insert("_M4");
   insert("_M5");

   insert("_M6");
   insert("_M7");

   insert("_M8");
   insert("_M9");
   insert("_M10");
   insert("_M11");
   insert("_M12");

   insert("_M13");
   insert("_M14");

   insert("_M15");
   insert("_M16");
   insert("_M17");
   insert("_M18");
   insert("_M19");

   insert("_M20");
   insert("_M21");

   insert("_M22");
   insert("_M23");
   insert("_M24");
   insert("_M25");
   insert("_M26");
/*Highway N West*/
   insert("_N1");
   insert("_N2");
   insert("_N3");
   insert("_N4");
   insert("_N5");

   insert("_N6");
   insert("_N7");

   insert("_N8");
   insert("_N9");
   insert("_N10");
   insert("_N11");
   insert("_N12");

   insert("_N13");
   insert("_N14");

   insert("_N15");
   insert("_N16");
   insert("_N17");
   insert("_N18");
   insert("_N19");

   insert("_N20");
   insert("_N21");
   
   insert("_N22");
   insert("_N23");
   insert("_N24");
   insert("_N25");
   insert("_N26");
/*Highway O West*/
   insert("_O1");
   insert("_O2");
   insert("_O3");
   insert("_O4");
   insert("_O5");

   insert("_O6");
   insert("_O7");

   insert("_O8");
   insert("_O9");
   insert("_O10");
   insert("_O11");
   insert("_O12");

   insert("_O13");
   insert("_O14");

   insert("_O15");
   insert("_O16");
   insert("_O17");
   insert("_O18");
   insert("_O19");

   insert("_O20");
   insert("_O21");
   
   insert("_O22");
   insert("_O23");
   insert("_O24");
   insert("_O25");
   insert("_O26");

   /*Avenue  P WEST*/
   insert("_P1");
   insert("_P2");
   insert("_P3");
   insert("_P4");
   insert("_P5");

   insert("_P6");
   insert("_P7");
   insert("_P8");
   insert("_P9");
   insert("_P10");

   insert("_P11");
   insert("_P12");
   insert("_P13");
   insert("_P14");
   insert("_P15");
   
   insert("_P16");
   insert("_P17");
   insert("_P18");
   insert("_P19");
   insert("_P20");
   /*Avenue Q EAST*/
   insert("_Q1");
   insert("_Q2");
   insert("_Q3");
   insert("_Q4");
   insert("_Q5");

   insert("_Q6");
   insert("_Q7");
   insert("_Q8");
   insert("_Q9");
   insert("_Q10");

   insert("_Q11");
   insert("_Q12");
   insert("_Q13");
   insert("_Q14");
   insert("_Q15");
   
   insert("_Q16");
   insert("_Q17");
   insert("_Q18");
   insert("_Q19");
   insert("_Q20");
   /*Avenue S EAST*/
   insert("_S1");
   insert("_S2");
   insert("_S3");
   insert("_S4");
   insert("_S5");

   insert("_S6");
   insert("_S7");
   insert("_S8");
   insert("_S9");
   insert("_S10");

   insert("_S11");
   insert("_S12");
   insert("_S13");
   insert("_S14");
   insert("_S15");
   
   insert("_S16");
   insert("_S17");
   insert("_S18");
   insert("_S19");
   insert("_S20");

}

void printQueue(){
   printf("%d\n", itemCount );
   while(!isEmpty()) {
      char * n = removeData();           
      printf("%s ",n);
   }   
   printf("%s\n", "");
}
