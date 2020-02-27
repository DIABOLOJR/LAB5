/*
 * Esta libreria fue extraida de:  https://www.youtube.com/watch?v=RgTMbQ6lssI&t=2336s
 * y la cual fue implementada a 8 bits para el trabajo de este laboratorio.
 */


#include "8 bits.h"
#include <xc.h>
#include <stdint.h>
/* Definicion de variables en formato de los pines de salida del PIC*/
#define RS  PORTDbits.RD6
#define EN  PORTDbits.RD7
#define TRISRS TRISDbits.TRISD6
#define TRISEN TRISDbits.TRISD7
#define PUERTOTRS TRISB
#define PUERTO PORTB
int dms;
int dus;
void delay_ms(int dms){
    for(int i = 0; i<dms; i++){// ciclo para el aumento en miisegundos.
        for(int j = 0; j<255; j++);
    }
}

void delay_us (int dus){
    for(int i = 0; i<dus; i++);// ciclo para el aumento en microseg.
}

// Funcion para Activar y desactivar el Enable de la LCD
void Tiempocontrol (void){
    EN = 1;
    delay_us(5);
    EN = 0;
    delay_us(5);
}
// Coloca el RS de la LCD en 0 y manada el valor binario para desplegarlo en la pantalla.
void Control (char valor){
    RS =0;
    PUERTO = valor;
    Tiempocontrol();
    delay_ms(2);
}
//Funcion similar a la anterior con la diferencia que enciende el RS y coloca el valor en la pantalla nuevamente desde otra variable
void ON (char valor1){
    RS =1;
    PUERTO = valor1;
    Tiempocontrol();
    delay_us(50);
}
//Funcion de seteo de la LCD para inicializar las 16*2 lineas de la pantalla.
void LCDvalue (void){
    TRISRS=0;
    TRISEN=0;
    PUERTOTRS=0;
    RS=0;
    EN=0;
    PUERTO=0;
    delay_ms(50);
    Control(0x02);
    Control(0x38);
    Control(0x0C);
    Control(0x06);
    
}
// agarra el valor de puntero de la variable y llamado a la funcion para colocar el grupod de palabras en ela lcd
void impresion (char *valor){
    while (*valor){
        ON(*valor);
        valor++;
    }
}
//En esta funcion se colocan los datos en funcion de la posicion para poder escribir en toda la LCD para aprovechar los 16 cuadros
void lcddirection(int x, int y, char *valor){
    char posicion;
    switch (y) {
        case 1:
            posicion = 0x80 + x;
            break;
        case 2:
            posicion = 0xC0 + x;
            break;
        default:
            posicion = 0x80 + x;
            break;
    }
    Control (posicion);
    impresion (valor);
}

//Funcion para desplegar los valores del ADC mapeados en funcion del pot de 0 a 1023 // 0 a 255
void LCDCONT (int x, int z){
    
    switch (z) {
        case 0:
            lcddirection (x,2,"0");
            break;
        case 1:
            lcddirection (x,2,"1");
            break;
        case 2:
            lcddirection (x,2,"2");
            break;
        case 3:
            lcddirection (x,2,"3");
            break;
        case 4:
            lcddirection (x,2,"4");
            break;
        case 5:
            lcddirection (x,2,"5");
            break;
        case 6:
            lcddirection (x,2,"6");
            break;
        case 7:
            lcddirection (x,2,"7");
            break;
        case 8:
            lcddirection (x,2,"8");
            break;
        case 9:
            lcddirection (x,2,"9");
            break;
        case 10:
            lcddirection (x,2,"10");
            break;
        case 11:
            lcddirection (x,2,"11");
            break;
        case 12:
            lcddirection (x,2,"12");
            break;
        case 13:
            lcddirection (x,2,"13");
            break; 
        case 14:
            lcddirection (x,2,"14");
            break;    
        case 15:
            lcddirection (x,2,"15");
            break;    
        default:
            lcddirection (x,2,"16");
            break;
    }
  
}


void POTENCIOMETRO (uint8_t result){
    if (result>=250){result = 250;}
    uint8_t valor      = 0;
    uint8_t coordenada = 0;
    uint8_t unidades        = (result - (result % 50))/50;
    uint8_t decimas         = ((result %50) -((result %50)%5))/5;
    uint8_t centesimas      = (((result %50)%5) -(((result %50)%5)%1))*2;
    int numero[] = {unidades,decimas,centesimas};  
    for (int i=0; i<3;i++){
        valor = numero[i];
        if (i == 0) {
            coordenada = 0;
        }
        if (i == 1) {
            coordenada = 2;
        }
        if (i == 2) {
            coordenada = 3;
        }
        if (valor == 0){
            lcddirection(coordenada,2,"0");
        }
        if (valor == 1){
            lcddirection(coordenada,2,"1");
        }
        if (valor == 2){
            lcddirection(coordenada,2,"2");
        }
        if (valor == 3){
            lcddirection(coordenada,2,"3");
        }
        if (valor == 4){
            lcddirection(coordenada,2,"4");
        }
        if (valor == 5){
            lcddirection(coordenada,2,"5");
        }
        if (valor == 6){
            lcddirection(coordenada,2,"6");
        }
        if (valor == 7){
            lcddirection(coordenada,2,"7");
        }
        if (valor == 8){
            lcddirection(coordenada,2,"8");
        }
        if (valor == 9){
            lcddirection(coordenada,2,"9");
        }
    }
}

void FOTORESIS (uint8_t result){
    if (result>=250){result = 250;}
    uint8_t valor      = 0;
    uint8_t coordenada = 0;
    uint8_t unidades        = (result - (result % 50))/50;
    uint8_t decimas         = ((result %50) -((result %50)%5))/5;
    uint8_t centesimas      = (((result %50)%5) -(((result %50)%5)%1))*2;
    int numero[] = {unidades,decimas,centesimas};  
    for (int i=0; i<3;i++){
        valor = numero[i];
        if (i == 0) {
            coordenada = 12;
        }
        if (i == 1) {
            coordenada = 14;
        }
        if (i == 2) {
            coordenada = 15;
        }
        if (valor == 0){
            lcddirection(coordenada,2,"0");
        }
        if (valor == 1){
            lcddirection(coordenada,2,"1");
        }
        if (valor == 2){
            lcddirection(coordenada,2,"2");
        }
        if (valor == 3){
            lcddirection(coordenada,2,"3");
        }
        if (valor == 4){
            lcddirection(coordenada,2,"4");
        }
        if (valor == 5){
            lcddirection(coordenada,2,"5");
        }
        if (valor == 6){
            lcddirection(coordenada,2,"6");
        }
        if (valor == 7){
            lcddirection(coordenada,2,"7");
        }
        if (valor == 8){
            lcddirection(coordenada,2,"8");
        }
        if (valor == 9){
            lcddirection(coordenada,2,"9");
        }
    }
}


void clean (void){//Funcion de borrado de la LCD
    Control(0x01);
}


