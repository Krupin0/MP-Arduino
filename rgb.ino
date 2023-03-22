int red1 = 11;
int blue1 = 9;
int green1 = 10;

int red2 = 13;
int blue2 = 8;
int green2 = 12;

int red3 = 7;
int blue3 = 2;
int green3 = 4;

unsigned long nextTimeLed1 = 0;
unsigned long nextTimeLed2 = 0;
unsigned long nextTimeLed3 = 0;

byte dataLed1[25][10];
byte dataLed2[25][10];
byte dataLed3[25][10];

byte data[250];

int delka1 = 0;
int delka2 = 0;
int delka3 = 0;

int pocetCekani = 0;

bool prvniLed = false;
bool druhaLed = false;
bool tretiLed = false;

#define RX 5
#define TX 6

// připojení knihovny SoftwareSerial
#include <SoftwareSerial.h>
#include "SoftPWM.h"
// inicializace Bluetooth modulu z knihovny SoftwareSerial
SoftwareSerial bluetooth(TX, RX);




void setup() {
  pinMode(red1, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(blue1, OUTPUT);

  pinMode(red2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(blue2, OUTPUT);

  pinMode(red3, OUTPUT);
  pinMode(green3, OUTPUT);
  pinMode(blue3, OUTPUT);

  SoftPWMBegin();
  bluetooth.begin(9600);
  Serial.begin(9600);

}

void loop() {

  if (bluetooth.available() > 0) {
        byte size = bluetooth.read();
        pocetCekani = 0;
        while(bluetooth.available() < (size*10) && pocetCekani < 750){
          delay(20);
          pocetCekani++;
        }
        if(pocetCekani < 750){
            data[i] = bluetooth.read() + 128;
            Serial.println("x");
        }
        
        bluetooth.flush();
        

        //CHECK ZMEN A PRIRAZENI DAT
        prvniLed = false;
        druhaLed = false;
        tretiLed = false;
        
        for(int j = 0; j < size; j++){
          if(data[j*10] == 1){
            delka1 = 0;
          }
          if(data[j*10] == 2){
            delka2 = 0;
          }
          if(data[j*10] == 3){
            delka3 = 0;
          }
        }
        

        for(int j = 0; j < size; j++){
          if(data[j*10] == 1){
            prvniLed = true;
      
            dataLed1[delka1][0] = data[0 + (j*10)];
            dataLed1[delka1][1] = data[1 + (j*10)];
            dataLed1[delka1][2] = data[2 + (j*10)];
            dataLed1[delka1][3] = data[3 + (j*10)];
            dataLed1[delka1][4] = data[4 + (j*10)];
            dataLed1[delka1][5] = data[5 + (j*10)];
            dataLed1[delka1][6] = data[6 + (j*10)];
            dataLed1[delka1][7] = data[7 + (j*10)];
            dataLed1[delka1][8] = data[8 + (j*10)];
            dataLed1[delka1][9] = data[9 + (j*10)];
            delka1++;
          }
          if(data[j*10] == 2){
            druhaLed = true;

            dataLed2[delka2][0] = data[0 + (j*10)];
            dataLed2[delka2][1] = data[1 + (j*10)];
            dataLed2[delka2][2] = data[2 + (j*10)];
            dataLed2[delka2][3] = data[3 + (j*10)];
            dataLed2[delka2][4] = data[4 + (j*10)];
            dataLed2[delka2][5] = data[5 + (j*10)];
            dataLed2[delka2][6] = data[6 + (j*10)];
            dataLed2[delka2][7] = data[7 + (j*10)];
            dataLed2[delka2][8] = data[8 + (j*10)];
            dataLed2[delka2][9] = data[9 + (j*10)];
            delka2++;
          }
          if(data[j*10] == 3){
            tretiLed = true;

            dataLed3[delka3][0] = data[0 + (j*10)];
            dataLed3[delka3][1] = data[1 + (j*10)];
            dataLed3[delka3][2] = data[2 + (j*10)];
            dataLed3[delka3][3] = data[3 + (j*10)];
            dataLed3[delka3][4] = data[4 + (j*10)];
            dataLed3[delka3][5] = data[5 + (j*10)];
            dataLed3[delka3][6] = data[6 + (j*10)];
            dataLed3[delka3][7] = data[7 + (j*10)];
            dataLed3[delka3][8] = data[8 + (j*10)];
            dataLed3[delka3][9] = data[9 + (j*10)];
            delka3++;
          }
        }


      //ODSTRANENI PREBYTECNYCH DAT A NASTAVENI NEXT CASU
        if(prvniLed){
          for(int i = delka1; i < 25; i++){
            for(int j = 0; j < 10; j++){
              dataLed1[i][j] = 0;
            }
          }
          nextTimeLed1 = (((16581375*(dataLed1[0][5])) + (65025*(dataLed1[0][6])) + (255*(dataLed1[0][7])) + (dataLed1[0][8])) * 1000) + millis();
        }
        if(druhaLed){
          for(int i = delka2; i < 25; i++){
            for(int j = 0; j < 10; j++){
              dataLed2[i][j] = 0;
            }
          }
          nextTimeLed2 = (((16581375*(dataLed2[0][5])) + (65025*(dataLed2[0][6])) + (255*(dataLed2[0][7])) + (dataLed2[0][8])) * 1000) + millis();
        }
        if(tretiLed){
          for(int i = delka3; i < 25; i++){
            for(int j = 0; j < 10; j++){
              dataLed3[i][j] = 0;
            }
          }
          nextTimeLed3 = (((16581375*(dataLed3[0][5])) + (65025*(dataLed3[0][6])) + (255*(dataLed3[0][7])) + (dataLed3[0][8])) * 1000) + millis();
        }
        }
    }

  
  //ZDE CHECKUJU JESTLI BY SE NEMELA ZMENIT NEJAKA LED
  if(millis() > nextTimeLed1 && dataLed1[0][0] == 1){
        //double xd = ((double)dataLed1[0][4]/(double)255);

        SoftPWMSet(red1, ((double)dataLed1[0][4]/(double)255) * dataLed1[0][1]);
        SoftPWMSet(green1,((double)dataLed1[0][4]/(double)255) * dataLed1[0][2]);
        SoftPWMSet(blue1, ((double)dataLed1[0][4]/(double)255) * dataLed1[0][3]);

      //POKUD SE NEOPAKUJE TAK ODSTRANIT
      if(dataLed1[0][9] == 0){
        for(int i = 0; i < 10; i++){
          dataLed1[0][i] = 0;
        }
        delka1--;
      }
      
      //POKUD SE OPAKUJE DAM DOLU
      else{
          for(int i = 0; i < 10; i++){
            dataLed1[delka1][i] = dataLed1[0][i];
        }
      }
      //POSUNU VSE NAHORU
      for(int i = 0; i < delka1; i++){
        for(int j = 0; j < 10; j++){
          dataLed1[i][j] = dataLed1[i+1][j];
        }
      }

      nextTimeLed1 = (((16581375*(dataLed1[0][5])) + (65025*(dataLed1[0][6])) + (255*(dataLed1[0][7])) + (dataLed1[0][8])) * 1000) + nextTimeLed1;
  }
  if(millis() > nextTimeLed2 && dataLed2[0][0] == 2){
        SoftPWMSet(red2, ((double)dataLed2[0][4]/(double)255) * dataLed2[0][1]);
        SoftPWMSet(green2, ((double)dataLed2[0][4]/(double)255) * dataLed2[0][2]);
        SoftPWMSet(blue2, ((double)dataLed2[0][4]/(double)255) * dataLed2[0][3]);

      //POKUD SE NEOPAKUJE TAK ODSTRANIT
      if(dataLed2[0][9] == 0){
        for(int i = 0; i < 10; i++){
          dataLed2[0][i] = 0;
        }
        delka2--;
      }
      //POKUD SE OPAKUJE DAM DOLU
      else{
          for(int i = 0; i < 10; i++){
            dataLed2[delka2][i] = dataLed2[0][i];
        }
      }
      //POSUNU VSE NAHORU
      for(int i = 0; i < delka2; i++){
        for(int j = 0; j < 10; j++){
          dataLed2[i][j] = dataLed2[i+1][j];
        }
      }

      nextTimeLed2 = (((16581375*(dataLed2[0][5])) + (65025*(dataLed2[0][6])) + (255*(dataLed2[0][7])) + (dataLed2[0][8])) * 1000) + nextTimeLed2;
  }
  if(millis() > nextTimeLed3 && dataLed3[0][0] == 3){

        SoftPWMSet(red3, ((double)dataLed3[0][4]/(double)255) * dataLed3[0][1]);
        SoftPWMSet(green3, ((double)dataLed3[0][4]/(double)255) * dataLed3[0][2]);
        SoftPWMSet(blue3, ((double)dataLed3[0][4]/(double)255) * dataLed3[0][3]);

      //POKUD SE NEOPAKUJE TAK ODSTRANIT
      if(dataLed3[0][9] == 0){
        for(int i = 0; i < 10; i++){
          dataLed3[0][i] = 0;
        }
        delka3--;
      }
      //POKUD SE OPAKUJE DAM DOLU
      else{
          for(int i = 0; i < 10; i++){
            dataLed3[delka3][i] = dataLed3[0][i];
        }
      }
      //POSUNU VSE NAHORU
      for(int i = 0; i < delka3; i++){
        for(int j = 0; j < 10; j++){
          dataLed3[i][j] = dataLed3[i+1][j];
        }
      }

      nextTimeLed3 = (((16581375*(dataLed3[0][5])) + (65025*(dataLed3[0][6])) + (255*(dataLed3[0][7])) + (dataLed3[0][8])) * 1000) + nextTimeLed3;
  }
}
