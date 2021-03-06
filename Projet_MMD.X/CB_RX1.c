#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "CB_RX1.h"
#define CBRX1_BUFFER_SIZE 128

int cbRx1Head;
int cbRx1Tail;
unsigned char cbRx1Buffer[CBRX1_BUFFER_SIZE];

void CB_RX1_Add(unsigned char value)
{
if (CB_RX1_GetRemainingSize() >0)
{
    cbRx1Buffer[cbRx1Head]= value;
    cbRx1Head++;
}
    if(cbRx1Head>=CBRX1_BUFFER_SIZE){
        cbRx1Head=0;
    }
}

unsigned char CB_RX1_Get(void)
{
unsigned char value=cbRx1Buffer[cbRx1Tail] ;
    cbRx1Tail++;
    if(cbRx1Tail>=CBRX1_BUFFER_SIZE){
        cbRx1Tail=0;
    }
return value ;
}

unsigned char CB_RX1_IsDataAvailable(void)
{
if (cbRx1Head!=cbRx1Tail){
    return 1;
}
else
    return 0;
}

void __attribute__ (( interrupt , no_auto_psv )) _U1RXInterrupt (void){
IFS0bits.U1RXIF = 0 ; // c l e a r RX i n t e r r u p t f l a g
/*check for receive errors */
if (U1STAbits.FERR == 1 ){
    U1STAbits.FERR = 0 ;
}
/*must c l e a r the ove r run e r r o r t o keep u a r t r e c e i v i n g */

if (U1STAbits.OERR == 1) {
    U1STAbits.OERR = 0 ;
}
/* g e t the data */
while ( U1STAbits.URXDA == 1 ) {
    CB_RX1_Add(U1RXREG) ;
}
}

int CB_RX1_GetDataSize(void)
{
// r e t u r n s i z e o f data s t o r e d i n c i r c u l a r b u f f e r
    if (cbRx1Head >= cbRx1Tail)
        return cbRx1Head-cbRx1Tail;
    else
        return CBRX1_BUFFER_SIZE - (cbRx1Tail - cbRx1Head);  
}

int CB_RX1_GetRemainingSize( void)
{
    return  CBRX1_BUFFER_SIZE - CB_RX1_GetDataSize();
}

