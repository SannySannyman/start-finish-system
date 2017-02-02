/*******************************************************************************
* File Name: LED_RED_PIN.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "LED_RED_PIN.h"

static LED_RED_PIN_BACKUP_STRUCT  LED_RED_PIN_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: LED_RED_PIN_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet LED_RED_PIN_SUT.c usage_LED_RED_PIN_Sleep_Wakeup
*******************************************************************************/
void LED_RED_PIN_Sleep(void)
{
    #if defined(LED_RED_PIN__PC)
        LED_RED_PIN_backup.pcState = LED_RED_PIN_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            LED_RED_PIN_backup.usbState = LED_RED_PIN_CR1_REG;
            LED_RED_PIN_USB_POWER_REG |= LED_RED_PIN_USBIO_ENTER_SLEEP;
            LED_RED_PIN_CR1_REG &= LED_RED_PIN_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(LED_RED_PIN__SIO)
        LED_RED_PIN_backup.sioState = LED_RED_PIN_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        LED_RED_PIN_SIO_REG &= (uint32)(~LED_RED_PIN_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: LED_RED_PIN_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to LED_RED_PIN_Sleep() for an example usage.
*******************************************************************************/
void LED_RED_PIN_Wakeup(void)
{
    #if defined(LED_RED_PIN__PC)
        LED_RED_PIN_PC = LED_RED_PIN_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            LED_RED_PIN_USB_POWER_REG &= LED_RED_PIN_USBIO_EXIT_SLEEP_PH1;
            LED_RED_PIN_CR1_REG = LED_RED_PIN_backup.usbState;
            LED_RED_PIN_USB_POWER_REG &= LED_RED_PIN_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(LED_RED_PIN__SIO)
        LED_RED_PIN_SIO_REG = LED_RED_PIN_backup.sioState;
    #endif
}


/* [] END OF FILE */
