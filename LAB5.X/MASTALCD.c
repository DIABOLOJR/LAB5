// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
// Configuración del PIC
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
 
/*
 *Bibliotecas
 */
#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000

char munecon;
char I2CIn;
char I2COut;

void __interrupt() isr(void){
    
    // Interrupción: I2C
    if(PIR1bits.SSPIF == 1){                    

        SSPCONbits.CKP = 0;                     

        if ((SSPOV == 1) || (WCOL == 1)){       
            munecon = SSPBUF;                   
            SSPCONbits.SSPOV = 0;               
            SSPCONbits.WCOL = 0;               
            SSPCONbits.CKP = 1;                 
        }
        
        
        if (!SSPSTATbits.D_nA && !SSPSTATbits.R_nW){
            munecon = SSPBUF;                    
            SSPCONbits.CKP = 1;                 
            while(!SSPSTATbits.BF);             
            I2CIn = SSPBUF;                     
            __delay_us(250);
        }
        
        
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            munecon = SSPBUF;                     
            SSPSTATbits.BF = 0;                 
            SSPBUF = I2COut;                       
            SSPCONbits.CKP = 1;                 
            while(SSPSTATbits.BF == 1);         
            __delay_us(250);
            
        }
                    
        PIR1bits.SSPIF = 0;                     
    }
    
}













void main(void) {
    while(1){
        
    }
    return;
}
