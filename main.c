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

#include "HAL_MSP432_320x240_ILI9341.h"
#include "color.h"
#include "graphics.h"
#include "lcd.h"


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
    memset(resultsBuffer, 0x00, 20);

    FPU_enableModule();
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
    PCM_setPowerState(PCM_AM_DCDC_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    CS_setDCOFrequency(48000000);
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

	_delay_cycles(48000000);

	HAL_LCD_SpiInit();
	_delay_cycles(160000);
	initLCD();
	clearScreen(1);

	setColor(COLOR_16_WHITE);

	drawString(4, 2, FONT_MD, "MEGAHERTZ");
	drawString(236, 2, FONT_MD, "GIRAF Tech");

	drawString(4, 34, FONT_MD, " 1");
	drawString(4, 50, FONT_MD, " 2");
	drawString(4, 66, FONT_MD, " 3");
	drawString(4, 82, FONT_MD, " 4");
	drawString(4, 98, FONT_MD, " 5");
	drawString(4, 114, FONT_MD, " 6");
	drawString(4, 130, FONT_MD, " 7");
	drawString(4, 146, FONT_MD, " 8");
	drawString(4, 162, FONT_MD, " 9");
	drawString(4, 178, FONT_MD, "10");

	drawString(4, 210, FONT_MD, "TEMP  Inside:");
	drawString(116, 210, FONT_MD, "000F");
	drawString(4, 226, FONT_MD, "TEMP Outside:");
	drawString(116, 226, FONT_MD, "000F");

	drawString(156, 210, FONT_MD, " IP: 255.255.255.255");
	drawString(156, 226, FONT_MD, "Web: GIRAFTECH.XYZ");

	drawString(28, 34, FONT_MD, "FWD: 000V  RVS: 000V");
	drawString(28, 50, FONT_MD, "FWD: 000V  RVS: 000V");
	drawString(28, 66, FONT_MD, "FWD: 000V  RVS: 000V");
	drawString(28, 82, FONT_MD, "FWD: 000V  RVS: 000V");
	drawString(28, 98, FONT_MD, "FWD: 000V  RVS: 000V");
	drawString(28, 114, FONT_MD, "FWD: 000V  RVS: 000V");
	drawString(28, 130, FONT_MD, "FWD: 000V  RVS: 000V");
	drawString(28, 146, FONT_MD, "FWD: 000V  RVS: 000V");
	drawString(28, 162, FONT_MD, "FWD: 000V  RVS: 000V");
	drawString(28, 178, FONT_MD, "FWD: 000V  RVS: 000V");


    /* Configures Pins as ADC input */

    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN5, GPIO_TERTIARY_MODULE_FUNCTION);//P5.5 - A0
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);//P5.4 - A1
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN3, GPIO_TERTIARY_MODULE_FUNCTION);//P5.3 - A2
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN2, GPIO_TERTIARY_MODULE_FUNCTION);//P5.2 - A3
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN1, GPIO_TERTIARY_MODULE_FUNCTION);//P5.1 - A4
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);//P5.0 - A5
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN7, GPIO_TERTIARY_MODULE_FUNCTION);//P4.7 - A6
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN6, GPIO_TERTIARY_MODULE_FUNCTION);//P4.6 - A7
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN5, GPIO_TERTIARY_MODULE_FUNCTION);//P4.5 - A8
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);//P4.4 - A9
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN3, GPIO_TERTIARY_MODULE_FUNCTION);//P4.3 - A10
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN2, GPIO_TERTIARY_MODULE_FUNCTION);//P4.2 - A11
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN1, GPIO_TERTIARY_MODULE_FUNCTION);//P4.1 - A12
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);//P4.0 - A13
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN1, GPIO_TERTIARY_MODULE_FUNCTION);//P6.1 - A14
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);//P6.0 - A15
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9, GPIO_PIN1, GPIO_TERTIARY_MODULE_FUNCTION);//P9.1 - A16
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);//P9.0 - A17
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P8, GPIO_PIN7, GPIO_TERTIARY_MODULE_FUNCTION);//P8.7 - A18
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P8, GPIO_PIN6, GPIO_TERTIARY_MODULE_FUNCTION);//P8.6 - A19

    /* Initializing ADC (ADCOSC/1/1) */
    MAP_ADC14_enableModule();
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_1, ADC_DIVIDER_1, 0);

    /* Configuring ADC Memory (ADC_MEM0 - ADC_MEM19 (A0 - A19)  without repeat) */
    MAP_ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM19, false);

    MAP_ADC14_configureConversionMemory(ADC_MEM19, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A0, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM18, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A1, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM17, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A2, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM16, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A3, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM15, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A4, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM14, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A5, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM13, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A6, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM12, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A7, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM11, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A8, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM10, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A9, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM9, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A10, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM8, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A11, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM7, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A12, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM6, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A13, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM5, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A14, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM4, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A15, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM3, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A16, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM2, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A17, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM1, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A18, ADC_NONDIFFERENTIAL_INPUTS);
    MAP_ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A19, ADC_NONDIFFERENTIAL_INPUTS);


    /* Enabling the interrupt when a conversion on channel 1 (end of sequence)
     *  is complete and enabling conversions */
    MAP_ADC14_enableInterrupt(ADC_INT19);

    /* Enabling Interrupts */
    MAP_Interrupt_enableInterrupt(INT_ADC14);
    MAP_Interrupt_enableMaster();

    /* Setting up the sample timer to automatically step through the sequence
     * convert.
     */
    MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

    /* Triggering the start of the sample */
    MAP_ADC14_enableConversion();
    MAP_ADC14_toggleConversionTrigger();

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
 * ADC_MEM1. This signals the end of conversion and the results array is
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
