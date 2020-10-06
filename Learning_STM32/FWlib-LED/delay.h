#ifndef  _DELAY_H
#define  _DELAY_H

void delay1s(void);   //Îó²î 0us

#if 0
void delay1s(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=46;c>0;c--)
        for(b=152;b>0;b--)
            for(a=70;a>0;a--);
 //   _nop_();  //if Keil,require use intrins.h
}

#endif


#endif/*_DELAY_H*/














