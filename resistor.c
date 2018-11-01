/*A-Nony-Mus
10 Mar. 2012
This program takes input from the user and transforms it into resistance values for resistors or takes input from the user and transforms it into colored band values

 ex.
 Would you like to convert a value (v) or colors (c)? v
 Please input the value of the resistor 3.6k
 From left to right, the color of the bands are: orange blue red 
 Figure out the tolerance on your own
 
                ------------and------------
 
  Would you like to convert a value (v) or colors (c)? c
 Please input the colors of the bands
 in order from left to right followed by spaces
 (ex. red green blue silver) red green blue silver
 The value of the resistor is 25000.0k ohms with a tolerance of 10%
 
 Possible color input values (case insensitive):
 
 Black      Brown
 Red        Orange
 Yellow     Green
 Blue       Purple
 Grey       Gray
 White      Gold
 Silver     Clear
 
 
 11 Apr. 2012
 Idea to use enumerated type data didn't work, edited to use strings
 20 Apr. 2012
 Edited to also be able to convert values into colored bands*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define STRINGLEN 7

void colors();
void values();
int resistance_value(char color[], int y, int *error);
void lowercase(char value[], int y);
int find_zeroes(double ohms);
void band_color(int band);

int main(void){
    
    char choice,
        lcv;
    
    do {
    printf("Would you like to convert a value (v) or colors (c)? ");
    scanf("%c", &choice);
        if (choice == '\n')
            scanf("%c", &choice);
    
    choice = tolower(choice);
    
    if (choice == 'c')
        colors();
    else if (choice == 'v')
        values();
    else
        printf("I'm sorry, that was not one of the inputs");
        printf("Would you like to continue(y/n)? ");
        scanf("%c", &lcv);
        if (lcv == '\n')
            scanf("%c", &lcv);
    } while (lcv == 'y');

    return(0);
}
//Inputs: None
//This function scans in color bands input by the user and converts it to the resistance value in ohms
void colors()
{
    char band1[STRINGLEN],
        band2[STRINGLEN],
        band3[STRINGLEN],
        band4[STRINGLEN];
    int value,
        tolerance,
        err;
    double ohms;
    
    err = 0;
    printf("Please input the colors of the bands\n in order from left to right followed by spaces\n (ex. red green blue silver) ");
    scanf("%s%s%s%s", band1, band2, band3, band4);
    
    lowercase(band1, 7);
    lowercase(band2, 7);
    lowercase(band3, 7);
    lowercase(band4, 7);
    
    value = resistance_value(band1, 1, &err);
    value += resistance_value(band2, 2, &err);
    value *= resistance_value(band3, 3, &err);
    tolerance = resistance_value(band4, 4, &err);
    
    if (err == 0){
        if (value/1000 > 1)
            printf("The value of the resistor is %3.1fk ohms with a tolerance of %d%%\n", (double)value/1000, tolerance);
    }
}

//Inputs: None
//This function scans in a resistance value input by the user and converts it to colored values
void values()
{
    char k;
    int band1,
        band2,
        band3,
        temp;
    double value;
        
    printf("Please input the value of the resistor ");
    scanf("%lf%c", &value, &k);
        
    if (k == 'k')
        value *= 1000;
        
    band3 = find_zeroes(value);
        
    band2 = (value / pow(10, band3));
    temp = (value / pow(10, band3 + 1));
    temp *= 10;
    band2 -= temp;
    band1 = value / pow(10, band3 + 1);
        
    printf("From left to right, the color of the bands are: ");
    band_color(band1);
    band_color(band2);
    band_color(band3);
    printf("\n");
        
    printf("Figure out the tolerance on your own\n");
}

//Inputs: The string for the band color, the number band that it is, and an error variable
//Outputs: A value for the band color, error variable
int resistance_value(char color[], int y, int *error){
    
    int ohms;
    
    if (y == 1 || y == 2) {
        if (strcmp(color, "black") == 0)
            ohms = 0;
        else if (strcmp(color, "brown") == 0)
            ohms = 1;
        else if (strcmp(color, "red") == 0)
            ohms = 2;
        else if (strcmp(color, "orange") == 0)
            ohms = 3;
        else if (strcmp(color, "yellow") == 0)
            ohms = 4;
        else if (strcmp(color, "green") == 0)
            ohms = 5;
        else if (strcmp(color, "blue") == 0)
            ohms = 6;
        else if (strcmp(color, "purple") == 0)
            ohms = 7;
        else if (strcmp(color, "gray") == 0)
            ohms = 8;
        else if (strcmp(color, "grey") == 0)
            ohms = 8;
        else if (strcmp(color, "white") == 0)
            ohms = 9;
        else {
            printf("I'm sorry, that was an invalid input,\n");
            *error = 1;
        }
        
        if (y == 1)
            ohms *= 10;
        if(*error == 1){
            if (y == 1) 
                printf("first arguement\n");
            
            else
                printf("second arguement\n");
        }
    }
    else if (y == 3){
        if (strcmp(color, "black") == 0)
            ohms = 1;
        else if (strcmp(color, "brown") == 0)
            ohms = 10;
        else if (strcmp(color, "red") == 0)
            ohms = 100;
        else if (strcmp(color, "orange") == 0)
            ohms = 1000;
        else if (strcmp(color, "yellow") == 0)
            ohms = 10000;
        else if (strcmp(color, "green") == 0)
            ohms = 100000;
        else if (strcmp(color, "blue") == 0)
            ohms = 1000000;
        else if (strcmp(color, "purple") == 0)
            ohms = 10000000;
        else if (strcmp(color, "gray") == 0)
            ohms = 100000000;
        else if (strcmp(color, "grey") == 0)
            ohms = 100000000;
        else if (strcmp(color, "white") == 0)
            ohms = 1000000000;
        else {
            printf("I'm sorry, that was an invalid input, third statement\n");
            *error = 1;
        }
    }
    else if (y == 4) {
        if (strcmp(color, "silver") == 0)
            ohms = 10;
        else if (strcmp(color, "gold") == 0)
            ohms = 5;
        else if (strcmp(color, "clear") == 0)
            ohms = 0;
        else {
            printf("I'm sorry, that was an invalid input fourth statement\n");
            *error = 1;
        }
    }
    
    return(ohms);
}

//Inputs: A character string and a maximum string size
//Outputs: A string with all lowercase letters
void lowercase(char value[], int y)
{
    int x;
    
    x = 0;
    while (x < y) {
        value[x] = tolower(value[x]);
        x++;
    }
}
//Inputs: A resistance value in ohms
//Outputs: The number of zeroes in the value
int find_zeroes(double ohms){
    
    int y,
    value;
    
    y = 1;
    while (value > 0){
        value = ohms * pow(10, (y * -1));
        y++;
    }
    ohms *= pow(10, 2);
    
    return(y - 3);
}
//Inputs: A band value
//Outputs: Prints the related color
void band_color(int band){
    
    if (band == 0){
        printf("black ");
    }
    else if (band == 1){
        printf("brown ");
    }
    else if (band == 2){
        printf("red ");
    }
    else if (band == 3){
        printf("orange ");
    }
    else if (band == 4){
        printf("yellow ");
    }
    else if (band == 5){
        printf("green ");
    }
    else if (band == 6){
        printf("blue ");
    }
    else if (band == 7){
        printf("purple ");
    }
    else if (band == 8){
        printf("grey ");
    }
    else if (band == 9){
        printf("white ");
    }
    
}
