/*******************************************************************************
* File Name: LED_RED_PIN.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LED_RED_PIN_H) /* Pins LED_RED_PIN_H */
#define CY_PINS_LED_RED_PIN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LED_RED_PIN_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} LED_RED_PIN_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   LED_RED_PIN_Read(void);
void    LED_RED_PIN_Write(uint8 value);
uint8   LED_RED_PIN_ReadDataReg(void);
#if defined(LED_RED_PIN__PC) || (CY_PSOC4_4200L) 
    void    LED_RED_PIN_SetDriveMode(uint8 mode);
#endif
void    LED_RED_PIN_SetInterruptMode(uint16 position, uint16 mode);
uint8   LED_RED_PIN_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void LED_RED_PIN_Sleep(void); 
void LED_RED_PIN_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(LED_RED_PIN__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define LED_RED_PIN_DRIVE_MODE_BITS        (3)
    #define LED_RED_PIN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LED_RED_PIN_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the LED_RED_PIN_SetDriveMode() function.
         *  @{
         */
        #define LED_RED_PIN_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define LED_RED_PIN_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define LED_RED_PIN_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define LED_RED_PIN_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define LED_RED_PIN_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define LED_RED_PIN_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define LED_RED_PIN_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define LED_RED_PIN_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define LED_RED_PIN_MASK               LED_RED_PIN__MASK
#define LED_RED_PIN_SHIFT              LED_RED_PIN__SHIFT
#define LED_RED_PIN_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LED_RED_PIN_SetInterruptMode() function.
     *  @{
     */
        #define LED_RED_PIN_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define LED_RED_PIN_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define LED_RED_PIN_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define LED_RED_PIN_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(LED_RED_PIN__SIO)
    #define LED_RED_PIN_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(LED_RED_PIN__PC) && (CY_PSOC4_4200L)
    #define LED_RED_PIN_USBIO_ENABLE               ((uint32)0x80000000u)
    #define LED_RED_PIN_USBIO_DISABLE              ((uint32)(~LED_RED_PIN_USBIO_ENABLE))
    #define LED_RED_PIN_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define LED_RED_PIN_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define LED_RED_PIN_USBIO_ENTER_SLEEP          ((uint32)((1u << LED_RED_PIN_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << LED_RED_PIN_USBIO_SUSPEND_DEL_SHIFT)))
    #define LED_RED_PIN_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << LED_RED_PIN_USBIO_SUSPEND_SHIFT)))
    #define LED_RED_PIN_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << LED_RED_PIN_USBIO_SUSPEND_DEL_SHIFT)))
    #define LED_RED_PIN_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(LED_RED_PIN__PC)
    /* Port Configuration */
    #define LED_RED_PIN_PC                 (* (reg32 *) LED_RED_PIN__PC)
#endif
/* Pin State */
#define LED_RED_PIN_PS                     (* (reg32 *) LED_RED_PIN__PS)
/* Data Register */
#define LED_RED_PIN_DR                     (* (reg32 *) LED_RED_PIN__DR)
/* Input Buffer Disable Override */
#define LED_RED_PIN_INP_DIS                (* (reg32 *) LED_RED_PIN__PC2)

/* Interrupt configuration Registers */
#define LED_RED_PIN_INTCFG                 (* (reg32 *) LED_RED_PIN__INTCFG)
#define LED_RED_PIN_INTSTAT                (* (reg32 *) LED_RED_PIN__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define LED_RED_PIN_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(LED_RED_PIN__SIO)
    #define LED_RED_PIN_SIO_REG            (* (reg32 *) LED_RED_PIN__SIO)
#endif /* (LED_RED_PIN__SIO_CFG) */

/* USBIO registers */
#if !defined(LED_RED_PIN__PC) && (CY_PSOC4_4200L)
    #define LED_RED_PIN_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define LED_RED_PIN_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define LED_RED_PIN_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define LED_RED_PIN_DRIVE_MODE_SHIFT       (0x00u)
#define LED_RED_PIN_DRIVE_MODE_MASK        (0x07u << LED_RED_PIN_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins LED_RED_PIN_H */


/* [] END OF FILE */
