/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33CH512MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/mcc.h"

//Variables globales
#define FOSC 8000000ULL                 
#define FCY (FOSC/2)
#include "libpic30.h"

/*
                         Main applicatio
 */

void Efecto1(unsigned int );
void Efecto2(unsigned int);
unsigned int pulso1=0;//Efecto1
unsigned int pulso2=0;//Efecto2

//=====================RUTINAS DE INTERRUPCION==================================
void Interrupt1(void)
{
      IFS0bits.T1IF = 0;
      pulso1++;
      if(pulso1 == 6){
            pulso1=0;
        }
      //Efecto1(pulso1); //Para visualizar el efecto 1
      Efecto2(pulso1);// Para visualizar el efecto2
 
}

//Interrupcion SW1 -> CAMBIA EFECTO
void Int1Switch(void){
    IFS0bits.T1IF = 0;
    if(PORTEbits.RE7 == 0)
    {   
        //IFS0bits.T1IF = 0;
        pulso1++;
        if (pulso1 == 6){
            pulso1 = 0;  //RESET de efectos
        }
        Efecto1(pulso1); //Para visualizar el efecto 1
        //Efecto2(pulso2);// Para visualizar el efecto2
    }//Cierro SW1
  
   if(PORTEbits.RE8 == 0)
    {
        IFS0bits.T1IF = 0;
        pulso2++;
        if (pulso2 == 6){
            pulso2 = 0;  //RESET de efectos
        }
        Efecto2(pulso2);// Para visualizar el efecto2
    }//SW2     

}

int main(void)
{
    //Temporizadores -RUTINA DE INTERRUPCION 
    SYSTEM_Initialize();
    CLOCK_Initialize();
    INTERRUPT_Initialize();
    TMR1_Initialize ();
    //TMR1_SetInterruptHandler(Interrupt1);
    TMR1_SetInterruptHandler(Int1Switch);
    
    while (1)
    {
        
           
    }//while
    return 1; 
}


void Efecto1(unsigned int cont){
    switch(cont){
        case 0:_LATE1=1;
        break;
        case 1:_LATE1=0;
               _LATE0=1;
        break;
        case 2:_LATE1=0;
               _LATE0=0;
               _LATD5=1;
        break;
        case 3:_LATE1=0;
               _LATE0=0;
               _LATD5=0;
               _LATD7=1;
        break;
        default:_LATE1=0;
               _LATE0=0;
               _LATD5=0;
               _LATD7=0;
    }
    return;
}

void Efecto2(unsigned int cont){
    //Efecto2 utilizado el LED1, LED2 y LED3
    switch(cont){
            case 0:_LATE1=1;
        break;
        case 1:_LATE1=1;
               _LATE0=1;
        break;
        case 2:_LATE1=1;
               _LATE0=1;
               _LATD5=1;
        break;
        case 3:_LATE1=1;
               _LATE0=1;
               _LATD5=0;
        break;
        case 4:_LATE1=1;
               _LATE0=0;
               _LATD5=0;
        break;
        default:_LATE0=0;
               _LATE1=0;
               _LATD5=0;

    }
    return;

}
/*
/*
 End of File
*/

