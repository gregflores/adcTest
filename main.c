//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

//****************************************************************************
//
// main.c - adcTest
// Code to test all 20 ADCs
//
//****************************************************************************

#include "msp.h"
#include "driverlib.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "lcd_pages.h"
#include "mcu_init.h"
//#include "HAL_MSP432_320x240_ILI9341.h"
#include "color.h"
#include "graphics.h"
//#include "lcd.h"


/* ADC results buffer */
static uint16_t resultsBuffer[20];

static float normalizedResults[20];

static bool lcd_flag = false;
/*
 * Main function
 */
void main(void)
{
    /* Halting WDT and disabling master interrupts */
    MAP_WDT_A_holdTimer();
    MAP_Interrupt_disableMaster();

    /* Zero-filling buffer */


    clockInit();
    memset(resultsBuffer, 0x00, 20);
    lcd_pageInit();
    lcd_primary();
    adcInit();

    while(1)
    {
        if(lcd_flag == true)
        {
        	uint8_t i;
        	for (i = 0; i<20; i++)
			{
				int8_t string[] = "";
				normalizedResults[i] = (resultsBuffer[i] * 3.3) / 16384;
				if (i < 10)
				{
					sprintf((char*)string, "%.2fv", normalizedResults[i]);
					drawString(68, (34+(i*16)), FONT_MD_BKG, string);
					if (normalizedResults[i] > 0.075)
					{
						drawString(196, 34+(i*16), FONT_MD_BKG, "   ACTIVE");
						setColor(COLOR_16_GREEN);
						fillCircle(279, 39+(i*16), 4);
						setColor(COLOR_16_WHITE);
					}
					else
					{
						drawString(196, 34+(i*16), FONT_MD_BKG, " INACTIVE");
						setColor(COLOR_16_RED);
						fillCircle(279, 39+(i*16), 4);
						setColor(COLOR_16_WHITE);
					}
				}
				else if (10 < i < 20)
				{
					sprintf((char*)string, " %.2fv", normalizedResults[i]);
					drawString(148, (34+((i-10)*16)), FONT_MD_BKG, string);
				}
			}
        	lcd_flag = false;
        	MAP_ADC14_toggleConversionTrigger();
        }
    }
}


/* This interrupt is fired whenever a conversion is completed and placed in
 * ADC_MEMx. This signals the end of conversion and the results array is
 * grabbed and placed in resultsBuffer */
void ADC14_IRQHandler(void)
{
    uint64_t status;

    status = MAP_ADC14_getEnabledInterruptStatus();
    MAP_ADC14_clearInterruptFlag(status);

    /* ADC_MEM1 conversion completed */
    if(status & ADC_INT19)
    {
        /* Store ADC14 conversion results */
        MAP_ADC14_getMultiSequenceResult(resultsBuffer);
        lcd_flag = true;

    }
}
