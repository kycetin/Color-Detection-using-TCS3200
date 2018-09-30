#include <msp430.h>
int valueR=0,valueG=0,valueB=0;
int value_counter=0,count=0;
volatile int set=0,Picker=0;
int Pred=0,Pgreen=0,Pblue=0,Pyellow=0,Porange=0,Pgray=0,Pwhite=0,Pnavy=0,Ppurple=0;
void Colour_Picker(int,int,int );
void main( void )
{
 WDTCTL = WDTPW + WDTHOLD;
 BCSCTL1=CALBC1_1MHZ + DIVA_3;
 BCSCTL1 = CALBC1_1MHZ;
 DCOCTL = CALDCO_1MHZ;
P1DIR = 0XFB;
P2DIR = 0xFF;
P2OUT = 0x00;
P1SEL = 0x04; 
 TA0CCTL1 = CM_1 + CCIS_0 + CAP + SCS + SCCI + CCIE+COV;
 TA0CTL = MC_1 + TASSEL_2;
 TA0CCR0 = 10000 - 1;
 TA0CCTL0 = CCIE;
 while(1)
 {
__bis_SR_register(CPUOFF + GIE);
Colour_Picker(valueR , valueG , valueB);
 }
}
#pragma vector = TIMER0_A1_VECTOR
__interrupt void TA0_A1_ISR( void )
{
 __bic_SR_register_on_exit(CPUOFF);
 if(TA0IV==2)
 {
 value_counter++
 }
}

#pragma vector=TIMER0_A0_VECTOR // 10ms 
__interrupt void TA0_A0_ISR(void)
{
 count++;
 if(count==10)
 {
 set++;
 if(set==1)
 {
 valueR=value_counter;
 P2OUT=0x0E;
 value_counter=0;
 }
 else if(set==3)
 {
 valueG=value_counter;
 P2OUT=0x0A;
 value_counter=0;
 }
 else if(set==2)
 {
 valueB=value_counter;
 P2OUT=0x02;
 value_counter=0;
 }
 else if(set==4)
 {
 set=0
 }
 value_counter=0;
 count=0;
 }
}

void Colour_Picker(int r ,int g ,int b)
{
 if((45<r && r<65) && (100<g && g<125) && (30<b && b<50))
 {
 //RED
 P1OUT=0X10;
 }
 else if((44<r && r<60) && (38<g && g<50) && (58<b && b<70))
 {
 //GREEN
 P1OUT=0X20;
 }
 else if((55<r&& r<90) && (17<g && g<50) && (18<b && b<50))
 {
 //BLUE
 P1OUT=0X40;
 }
 else if((64<r && r<84) && (137<g && g<157) && (100<b && b<121))
 {
 //YELLOW
 P1OUT=0X30;
 }
 
 else if((97<r && r<137) && (13<g && g<53) && (41<b && b<81))
 {
 //LIGHT BLUE
 P1OUT=0X60;
 }
 else if((52<r && r<92) && (56<g && g<86) && (20<b && b<60))
 {
 //PURPLE
 P1OUT =0X50;
 }
 else if((30<r && r<50) && (30<g && g<40) && (21<b && b<40))
 {
 //BLACK
 P1OUT=0X00;
 }
 else if((150<r && r<210) && (120<g && g<180) && (100<b && b<158))
 {
 //WHITE
 P1OUT=0X70;
 }
}
