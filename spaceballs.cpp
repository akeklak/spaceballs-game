//By Creighton Nakamura and Alexander Keklak
//with updated end sequence and game sounds

#include <stdio.h>
#include <stdlib.h>
#include <mxapi.h>
#include <sound.h>
#include <lcd.h>


//random number generater


//function declarations
void printMatrix(int array[2][16]); //prints the matrix out
void assignMatrix(int array[2][16]); //assigns the initial matrix values

int checkForInput(void); //checks for input from the user 
void movePlayer(int inputCheckResult, int array[2][16]); //moves the player based on the input 

int testForAsteroid(int array[2][16]); //tests all non-player matrix positions for an asteroid
void moveAsteroid(int asteroidTestResult, int array[2][16], double timecounter); //creates an asteroid, or moves the asteroid, or deletes the asteroid

void endgame(double timecounter); //ends the game
int randomNumber(void); //generates a random number, 1 or 2

void introSequence(void); //plays the intro sequence - sounds, lights, text

void printLCD(int array[2][16]);

int main(void) {
    
    //declarations
    int array[2][16]; //integrated
    int inputCheckResult = 0; //integrated
    int asteroidTestResult = 0; //integrated

    double timecounter = 0;
    
    assignMatrix(array); //integrated
    printMatrix(array);  //integrated

    //port initiations
    output_pin(PORT_B5); //light
    input_pin(PORT_D6); //initialize PD6 as input pin [up button]
    pullup_on(PORT_D6); //make access input
    input_pin(PORT_B6); //initialize PB6 as input pin [down button]
    pullup_on(PORT_B6); //make access input
    lcd_init(); //lcd                          

    introSequence();
    ////GAME LOOP
    
    while (1==1) {
          
          asteroidTestResult = testForAsteroid(array);
          
          moveAsteroid(asteroidTestResult, array, timecounter);
          
          inputCheckResult = checkForInput();
          
          movePlayer(inputCheckResult, array);
          
          
          
          
          
          
          //before the loop restarts
          //printf("%d\n", randomNumber());
          printMatrix(array);
          inputCheckResult = 0;
          asteroidTestResult = 0;

          printLCD(array);
          delay_ms(10000 / (timecounter + 50) );
          timecounter++;
          
    }
    
    
    
    
    
    system("pause");
    return 0;
    
}

void printMatrix(int array[2][16]) {
     
     int i,j;
     
     for (i = 0; i < 2; i++) {
         
         for (j = 0; j < 16; j++) {
             
             
             printf("%d", array[i][j]);
             printf(" ");
             
         }
         
         printf("\n");
         
     }
     
}

void assignMatrix(int array[2][16]) {
     
     int i,j;
     
     for (i = 0; i < 2; i++) {
         
         for (j = 0; j < 16; j++) {
             
             array[i][j] = 0;
             
             
         }
         
         
     }
     
     array[0][0] = 2;
     
}

int checkForInput(void) {
     
     int n = 0;     

     if (pin_value(PORT_D6) == 0) {
              
              n = 1;
              
                  
     }
     
     if (pin_value(PORT_B6) == 0) {
            
             n = 2;
             
             
     }
     
     return n;
    
}


/*
int checkForInput(void) {
     
     char n;    
     
     scanf(" %c", &n);
     
     if (n == 'q') {
              
              n = 1;
                  
     }
     
     if (n == 'a') {
            
             n = 2;
             
     }
     
     return n;
    
}
*/

void movePlayer(int inputCheckResult, int array[2][16]) {
     
     
     
     
     if (inputCheckResult == 1) {
             
         if (array[1][0] == 2) {
                              
              array[0][0] = 2;
              array[1][0] = 0;
              tone_out(PORT_D4, 1319, 20);
                              
         }
         
         
         
    }
    
    if (inputCheckResult == 2) {
              
         if (array[0][0] == 2) {
                         
              array[0][0] = 0;
              array[1][0] = 2;
              tone_out(PORT_D4, 1319, 20);
              
         }
         
         
    
    }
    
}
     

int testForAsteroid(int array[2][16]) {
     
     int a = 0, i, j;
     
     for (i = 0; i < 2; i++) {
         
         for (j = 1; j < 16; j++) {
             
             if (array[i][j] == 1) {
                             
                  a = 1;
                  
             }
             
         }
         
     }
     //collisions happened
     if (array[0][0] == 1 && array[1][0] == 0) {
                     
          a = 2;
          
     }
     if (array[1][0] == 1 && array[0][0] == 0) {
                     
          a = 2;
          
     }
     
     
     
     // 1 means theres an asteroid
     // 2 means there was a collision
     
     return a;
     
}

void moveAsteroid(int asteroidTestResult, int array[2][16], double timecounter) {
     
     int oneOrTwo;
     int i,j;
     //need random number generator
     oneOrTwo = randomNumber();
     
     //create an asteroid 
     if (asteroidTestResult == 0) {
                            
          if (oneOrTwo == 1) {
                       
               array[0][15] = 1;
               tone_out(PORT_D4, 1975, 20);
          
          }
          if (oneOrTwo == 2) {
                       
               array[1][15] = 1;
               tone_out(PORT_D4, 1975, 20);
               
          }
          if (array[0][0] == 2 && array[1][0] == 1) {
                          
               array[1][0] = 0;
          
          }
          if (array[1][0] == 2 && array[0][0] == 1) {
                          
               array[0][0] = 0;
          
          }
          
     }
     
     //there is an asteroid coming towards the user
     if (asteroidTestResult == 1) {
                            
          for (i = 0; i < 2; i++) {
              
              for (j = 1; j < 16; j++) {
                  
                  if (array[i][j] == 1) {
                                  
                       array[i][j] = 0;
                       array[i][j-1] = 1;
                       
                  }
                  
              }
              
          }
          
     }
     
     
     //if there is a collision
     if (asteroidTestResult == 2) {
                        
          
          endgame(timecounter);
          assignMatrix(array);
          array[0][0] = 0;
          
          
     }
     
     
     
     
}


void endgame(double timecounter) {
     
     
  
     //Display TRY AGAIN
     lcd_init();                            
     lcd_text(FIRST_LINE, "      GAME");  //Send text to the LCD
     lcd_text(SECOND_LINE, "      OVER!");  //Second line

     output_pin(PORT_B5);  //Set up Port B0 as an output pin    
     high_pin(PORT_B5);    //Set the Port B0 pin high

     int x;
     for (x = 750; x > 250; x = x-2) {
          tone_out(PORT_D4, x, 2);  //Make a tone of x Hertz for 2 milliseconds
     }

     
           
     low_pin(PORT_B5);     //Set the Port B0 pin low
     delay_ms(250);
     high_pin(PORT_B5);    
     delay_ms(250);        
     low_pin(PORT_B5);     
     delay_ms(250);
     high_pin(PORT_B5);    
     delay_ms(250);        
     low_pin(PORT_B5);     
     delay_ms(250);

     lcd_clear();
     lcd_text(FIRST_LINE, "SCORE:");
     lcd_decimal(SECOND_LINE, timecounter, 5);

     tone_out(PORT_D4, 370, 175);
     delay_ms(10); 
     tone_out(PORT_D4, 370, 175);
     delay_ms(10); 
     tone_out(PORT_D4, 440, 175);
     delay_ms(10);
     tone_out(PORT_D4, 370, 175);
     delay_ms(10);
     tone_out(PORT_D4, 494, 175);
     delay_ms(10);
     tone_out(PORT_D4, 440, 175);
     delay_ms(10);
     tone_out(PORT_D4, 370, 175);
     delay_ms(10);
     tone_out(PORT_D4, 440, 175);
     delay_ms(10);
     tone_out(PORT_D4, 370, 175);
     delay_ms(10);
     tone_out(PORT_D4, 370, 175);
     delay_ms(10);
     tone_out(PORT_D4, 440, 175);
     delay_ms(10);
     tone_out(PORT_D4, 349, 175);
     delay_ms(10);
     tone_out(PORT_D4, 330, 175);
     delay_ms(10);
     tone_out(PORT_D4, 330, 175);
     delay_ms(10);
     tone_out(PORT_D4, 494, 350);

     lcd_clear();

     lcd_text(FIRST_LINE, " PRESS  RESTART ");
     lcd_text(SECOND_LINE, " TO PLAY AGAIN! ");

     tone_out(PORT_D4, 370, 175);
     delay_ms(10); 
     tone_out(PORT_D4, 370, 175);
     delay_ms(10); 
     tone_out(PORT_D4, 440, 175);
     delay_ms(10);
     tone_out(PORT_D4, 370, 175);
     delay_ms(10);
     tone_out(PORT_D4, 494, 175);
     delay_ms(10);
     tone_out(PORT_D4, 440, 175);
     delay_ms(10);
     tone_out(PORT_D4, 370, 175);
     delay_ms(10);
     tone_out(PORT_D4, 440, 175);
     delay_ms(10);
     tone_out(PORT_D4, 370, 175);
     delay_ms(10);
     tone_out(PORT_D4, 370, 175);
     delay_ms(10);
     tone_out(PORT_D4, 440, 175);
     delay_ms(10);
     tone_out(PORT_D4, 349, 175);
     delay_ms(10);
     tone_out(PORT_D4, 330, 175);
     delay_ms(10);
     tone_out(PORT_D4, 330, 175);
     delay_ms(10);
     tone_out(PORT_D4, 370, 350);
     


     lcd_clear();
     


     exit(0);
     
}
    
int randomNumber(void) {
    
    int p;
    
    //srand ( time(NULL) );
    
    p = rand()%2+1;

    //p = random(2);
    
    return p;
    
}

void introSequence(void) {

    high_pin(PORT_B5);

    tone_out(PORT_D4, 1319, 250);
    tone_out(PORT_D4, 1661, 250); 
    tone_out(PORT_D4, 1975, 250);

    low_pin(PORT_B5);
    delay_ms(250);
    high_pin(PORT_B5);
    delay_ms(250);
    low_pin(PORT_B5);
    delay_ms(250);
    high_pin(PORT_B5);
    delay_ms(250);
    low_pin(PORT_B5);
    delay_ms(250);

    while(1==1) {
    //Display PRESS TO PLAY
    lcd_init();                            
    lcd_text(FIRST_LINE, "    PRESS TO");  //Send text to the LCD
    lcd_text(SECOND_LINE, "      PLAY!");  //Second line
    if(pin_value(PORT_D6)==0 || pin_value(PORT_B6)==0) {
        
        lcd_clear();
        break;
    }

  }

}

void printLCD(int array[2][16]) {

    int i,j;
    char top[16];
    char bottom[16];

    i = 0;

    for (j = 0; j < 16; j++) {

            if (array[i][j] == 1) {

                //print an asteroid
                top[j] = 'o';

            }
            if (array[i][j] == 2) {

                //print a character
                top[j] = '>';

            }
            if (array[i][j] == 0) {

                //print a space
                top[j] = ' ';

            }
    }
    
    i = 1;

    for (j = 0; j < 16; j++) {

            if (array[i][j] == 1) {

                //print an asteroid
                bottom[j] = 'o';

            }
            if (array[i][j] == 2) {

                //print a player
                bottom[j] = '>';

            }
            if (array[i][j] == 0) {

                bottom[j] = ' ';

            }
    }

    lcd_text(FIRST_LINE, top);
    lcd_text(SECOND_LINE, bottom);
    
}




