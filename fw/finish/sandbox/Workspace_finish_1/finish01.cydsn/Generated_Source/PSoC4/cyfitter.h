#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include "cydevice_trm.h"

/* led_green */
#define led_green__0__DM__MASK 0x1C0u
#define led_green__0__DM__SHIFT 6
#define led_green__0__DR CYREG_PRT0_DR
#define led_green__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define led_green__0__HSIOM_MASK 0x00000F00u
#define led_green__0__HSIOM_SHIFT 8u
#define led_green__0__INTCFG CYREG_PRT0_INTCFG
#define led_green__0__INTSTAT CYREG_PRT0_INTSTAT
#define led_green__0__MASK 0x04u
#define led_green__0__PA__CFG0 CYREG_UDB_PA0_CFG0
#define led_green__0__PA__CFG1 CYREG_UDB_PA0_CFG1
#define led_green__0__PA__CFG10 CYREG_UDB_PA0_CFG10
#define led_green__0__PA__CFG11 CYREG_UDB_PA0_CFG11
#define led_green__0__PA__CFG12 CYREG_UDB_PA0_CFG12
#define led_green__0__PA__CFG13 CYREG_UDB_PA0_CFG13
#define led_green__0__PA__CFG14 CYREG_UDB_PA0_CFG14
#define led_green__0__PA__CFG2 CYREG_UDB_PA0_CFG2
#define led_green__0__PA__CFG3 CYREG_UDB_PA0_CFG3
#define led_green__0__PA__CFG4 CYREG_UDB_PA0_CFG4
#define led_green__0__PA__CFG5 CYREG_UDB_PA0_CFG5
#define led_green__0__PA__CFG6 CYREG_UDB_PA0_CFG6
#define led_green__0__PA__CFG7 CYREG_UDB_PA0_CFG7
#define led_green__0__PA__CFG8 CYREG_UDB_PA0_CFG8
#define led_green__0__PA__CFG9 CYREG_UDB_PA0_CFG9
#define led_green__0__PC CYREG_PRT0_PC
#define led_green__0__PC2 CYREG_PRT0_PC2
#define led_green__0__PORT 0u
#define led_green__0__PS CYREG_PRT0_PS
#define led_green__0__SHIFT 2
#define led_green__DR CYREG_PRT0_DR
#define led_green__INTCFG CYREG_PRT0_INTCFG
#define led_green__INTSTAT CYREG_PRT0_INTSTAT
#define led_green__MASK 0x04u
#define led_green__PA__CFG0 CYREG_UDB_PA0_CFG0
#define led_green__PA__CFG1 CYREG_UDB_PA0_CFG1
#define led_green__PA__CFG10 CYREG_UDB_PA0_CFG10
#define led_green__PA__CFG11 CYREG_UDB_PA0_CFG11
#define led_green__PA__CFG12 CYREG_UDB_PA0_CFG12
#define led_green__PA__CFG13 CYREG_UDB_PA0_CFG13
#define led_green__PA__CFG14 CYREG_UDB_PA0_CFG14
#define led_green__PA__CFG2 CYREG_UDB_PA0_CFG2
#define led_green__PA__CFG3 CYREG_UDB_PA0_CFG3
#define led_green__PA__CFG4 CYREG_UDB_PA0_CFG4
#define led_green__PA__CFG5 CYREG_UDB_PA0_CFG5
#define led_green__PA__CFG6 CYREG_UDB_PA0_CFG6
#define led_green__PA__CFG7 CYREG_UDB_PA0_CFG7
#define led_green__PA__CFG8 CYREG_UDB_PA0_CFG8
#define led_green__PA__CFG9 CYREG_UDB_PA0_CFG9
#define led_green__PC CYREG_PRT0_PC
#define led_green__PC2 CYREG_PRT0_PC2
#define led_green__PORT 0u
#define led_green__PS CYREG_PRT0_PS
#define led_green__SHIFT 2

/* Rx_1 */
#define Rx_1__0__DM__MASK 0x7000u
#define Rx_1__0__DM__SHIFT 12
#define Rx_1__0__DR CYREG_PRT0_DR
#define Rx_1__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define Rx_1__0__HSIOM_MASK 0x000F0000u
#define Rx_1__0__HSIOM_SHIFT 16u
#define Rx_1__0__INTCFG CYREG_PRT0_INTCFG
#define Rx_1__0__INTSTAT CYREG_PRT0_INTSTAT
#define Rx_1__0__MASK 0x10u
#define Rx_1__0__PA__CFG0 CYREG_UDB_PA0_CFG0
#define Rx_1__0__PA__CFG1 CYREG_UDB_PA0_CFG1
#define Rx_1__0__PA__CFG10 CYREG_UDB_PA0_CFG10
#define Rx_1__0__PA__CFG11 CYREG_UDB_PA0_CFG11
#define Rx_1__0__PA__CFG12 CYREG_UDB_PA0_CFG12
#define Rx_1__0__PA__CFG13 CYREG_UDB_PA0_CFG13
#define Rx_1__0__PA__CFG14 CYREG_UDB_PA0_CFG14
#define Rx_1__0__PA__CFG2 CYREG_UDB_PA0_CFG2
#define Rx_1__0__PA__CFG3 CYREG_UDB_PA0_CFG3
#define Rx_1__0__PA__CFG4 CYREG_UDB_PA0_CFG4
#define Rx_1__0__PA__CFG5 CYREG_UDB_PA0_CFG5
#define Rx_1__0__PA__CFG6 CYREG_UDB_PA0_CFG6
#define Rx_1__0__PA__CFG7 CYREG_UDB_PA0_CFG7
#define Rx_1__0__PA__CFG8 CYREG_UDB_PA0_CFG8
#define Rx_1__0__PA__CFG9 CYREG_UDB_PA0_CFG9
#define Rx_1__0__PC CYREG_PRT0_PC
#define Rx_1__0__PC2 CYREG_PRT0_PC2
#define Rx_1__0__PORT 0u
#define Rx_1__0__PS CYREG_PRT0_PS
#define Rx_1__0__SHIFT 4
#define Rx_1__DR CYREG_PRT0_DR
#define Rx_1__INTCFG CYREG_PRT0_INTCFG
#define Rx_1__INTSTAT CYREG_PRT0_INTSTAT
#define Rx_1__MASK 0x10u
#define Rx_1__PA__CFG0 CYREG_UDB_PA0_CFG0
#define Rx_1__PA__CFG1 CYREG_UDB_PA0_CFG1
#define Rx_1__PA__CFG10 CYREG_UDB_PA0_CFG10
#define Rx_1__PA__CFG11 CYREG_UDB_PA0_CFG11
#define Rx_1__PA__CFG12 CYREG_UDB_PA0_CFG12
#define Rx_1__PA__CFG13 CYREG_UDB_PA0_CFG13
#define Rx_1__PA__CFG14 CYREG_UDB_PA0_CFG14
#define Rx_1__PA__CFG2 CYREG_UDB_PA0_CFG2
#define Rx_1__PA__CFG3 CYREG_UDB_PA0_CFG3
#define Rx_1__PA__CFG4 CYREG_UDB_PA0_CFG4
#define Rx_1__PA__CFG5 CYREG_UDB_PA0_CFG5
#define Rx_1__PA__CFG6 CYREG_UDB_PA0_CFG6
#define Rx_1__PA__CFG7 CYREG_UDB_PA0_CFG7
#define Rx_1__PA__CFG8 CYREG_UDB_PA0_CFG8
#define Rx_1__PA__CFG9 CYREG_UDB_PA0_CFG9
#define Rx_1__PC CYREG_PRT0_PC
#define Rx_1__PC2 CYREG_PRT0_PC2
#define Rx_1__PORT 0u
#define Rx_1__PS CYREG_PRT0_PS
#define Rx_1__SHIFT 4

/* Tx_1 */
#define Tx_1__0__DM__MASK 0x38000u
#define Tx_1__0__DM__SHIFT 15
#define Tx_1__0__DR CYREG_PRT0_DR
#define Tx_1__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define Tx_1__0__HSIOM_MASK 0x00F00000u
#define Tx_1__0__HSIOM_SHIFT 20u
#define Tx_1__0__INTCFG CYREG_PRT0_INTCFG
#define Tx_1__0__INTSTAT CYREG_PRT0_INTSTAT
#define Tx_1__0__MASK 0x20u
#define Tx_1__0__OUT_SEL CYREG_UDB_PA0_CFG10
#define Tx_1__0__OUT_SEL_SHIFT 10u
#define Tx_1__0__OUT_SEL_VAL 0u
#define Tx_1__0__PA__CFG0 CYREG_UDB_PA0_CFG0
#define Tx_1__0__PA__CFG1 CYREG_UDB_PA0_CFG1
#define Tx_1__0__PA__CFG10 CYREG_UDB_PA0_CFG10
#define Tx_1__0__PA__CFG11 CYREG_UDB_PA0_CFG11
#define Tx_1__0__PA__CFG12 CYREG_UDB_PA0_CFG12
#define Tx_1__0__PA__CFG13 CYREG_UDB_PA0_CFG13
#define Tx_1__0__PA__CFG14 CYREG_UDB_PA0_CFG14
#define Tx_1__0__PA__CFG2 CYREG_UDB_PA0_CFG2
#define Tx_1__0__PA__CFG3 CYREG_UDB_PA0_CFG3
#define Tx_1__0__PA__CFG4 CYREG_UDB_PA0_CFG4
#define Tx_1__0__PA__CFG5 CYREG_UDB_PA0_CFG5
#define Tx_1__0__PA__CFG6 CYREG_UDB_PA0_CFG6
#define Tx_1__0__PA__CFG7 CYREG_UDB_PA0_CFG7
#define Tx_1__0__PA__CFG8 CYREG_UDB_PA0_CFG8
#define Tx_1__0__PA__CFG9 CYREG_UDB_PA0_CFG9
#define Tx_1__0__PC CYREG_PRT0_PC
#define Tx_1__0__PC2 CYREG_PRT0_PC2
#define Tx_1__0__PORT 0u
#define Tx_1__0__PS CYREG_PRT0_PS
#define Tx_1__0__SHIFT 5
#define Tx_1__DR CYREG_PRT0_DR
#define Tx_1__INTCFG CYREG_PRT0_INTCFG
#define Tx_1__INTSTAT CYREG_PRT0_INTSTAT
#define Tx_1__MASK 0x20u
#define Tx_1__PA__CFG0 CYREG_UDB_PA0_CFG0
#define Tx_1__PA__CFG1 CYREG_UDB_PA0_CFG1
#define Tx_1__PA__CFG10 CYREG_UDB_PA0_CFG10
#define Tx_1__PA__CFG11 CYREG_UDB_PA0_CFG11
#define Tx_1__PA__CFG12 CYREG_UDB_PA0_CFG12
#define Tx_1__PA__CFG13 CYREG_UDB_PA0_CFG13
#define Tx_1__PA__CFG14 CYREG_UDB_PA0_CFG14
#define Tx_1__PA__CFG2 CYREG_UDB_PA0_CFG2
#define Tx_1__PA__CFG3 CYREG_UDB_PA0_CFG3
#define Tx_1__PA__CFG4 CYREG_UDB_PA0_CFG4
#define Tx_1__PA__CFG5 CYREG_UDB_PA0_CFG5
#define Tx_1__PA__CFG6 CYREG_UDB_PA0_CFG6
#define Tx_1__PA__CFG7 CYREG_UDB_PA0_CFG7
#define Tx_1__PA__CFG8 CYREG_UDB_PA0_CFG8
#define Tx_1__PA__CFG9 CYREG_UDB_PA0_CFG9
#define Tx_1__PC CYREG_PRT0_PC
#define Tx_1__PC2 CYREG_PRT0_PC2
#define Tx_1__PORT 0u
#define Tx_1__PS CYREG_PRT0_PS
#define Tx_1__SHIFT 5

/* xbee_BUART */
#define xbee_BUART_sRX_RxBitCounter__16BIT_CONTROL_AUX_CTL_REG CYREG_UDB_W16_ACTL_00
#define xbee_BUART_sRX_RxBitCounter__16BIT_CONTROL_CONTROL_REG CYREG_UDB_W16_CTL_00
#define xbee_BUART_sRX_RxBitCounter__16BIT_CONTROL_COUNT_REG CYREG_UDB_W16_CTL_00
#define xbee_BUART_sRX_RxBitCounter__16BIT_COUNT_CONTROL_REG CYREG_UDB_W16_CTL_00
#define xbee_BUART_sRX_RxBitCounter__16BIT_COUNT_COUNT_REG CYREG_UDB_W16_CTL_00
#define xbee_BUART_sRX_RxBitCounter__16BIT_MASK_MASK_REG CYREG_UDB_W16_MSK_00
#define xbee_BUART_sRX_RxBitCounter__16BIT_MASK_PERIOD_REG CYREG_UDB_W16_MSK_00
#define xbee_BUART_sRX_RxBitCounter__16BIT_PERIOD_MASK_REG CYREG_UDB_W16_MSK_00
#define xbee_BUART_sRX_RxBitCounter__16BIT_PERIOD_PERIOD_REG CYREG_UDB_W16_MSK_00
#define xbee_BUART_sRX_RxBitCounter__32BIT_CONTROL_AUX_CTL_REG CYREG_UDB_W32_ACTL_00
#define xbee_BUART_sRX_RxBitCounter__32BIT_CONTROL_REG CYREG_UDB_W32_CTL_00
#define xbee_BUART_sRX_RxBitCounter__32BIT_COUNT_REG CYREG_UDB_W32_CTL_00
#define xbee_BUART_sRX_RxBitCounter__32BIT_PERIOD_REG CYREG_UDB_W32_MSK_00
#define xbee_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG CYREG_UDB_W8_ACTL_00
#define xbee_BUART_sRX_RxBitCounter__CONTROL_REG CYREG_UDB_W8_CTL_00
#define xbee_BUART_sRX_RxBitCounter__CONTROL_ST_REG CYREG_UDB_CAT16_CTL_ST_00
#define xbee_BUART_sRX_RxBitCounter__COUNT_REG CYREG_UDB_W8_CTL_00
#define xbee_BUART_sRX_RxBitCounter__COUNT_ST_REG CYREG_UDB_CAT16_CTL_ST_00
#define xbee_BUART_sRX_RxBitCounter__MASK_CTL_AUX_CTL_REG CYREG_UDB_CAT16_ACTL_MSK_00
#define xbee_BUART_sRX_RxBitCounter__PER_CTL_AUX_CTL_REG CYREG_UDB_CAT16_ACTL_MSK_00
#define xbee_BUART_sRX_RxBitCounter__PERIOD_REG CYREG_UDB_W8_MSK_00
#define xbee_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_AUX_CTL_REG CYREG_UDB_W16_ACTL_00
#define xbee_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_REG CYREG_UDB_W16_ST_00
#define xbee_BUART_sRX_RxBitCounter_ST__32BIT_MASK_REG CYREG_UDB_W32_MSK_00
#define xbee_BUART_sRX_RxBitCounter_ST__32BIT_STATUS_AUX_CTL_REG CYREG_UDB_W32_ACTL_00
#define xbee_BUART_sRX_RxBitCounter_ST__32BIT_STATUS_REG CYREG_UDB_W32_ST_00
#define xbee_BUART_sRX_RxBitCounter_ST__MASK_REG CYREG_UDB_W8_MSK_00
#define xbee_BUART_sRX_RxBitCounter_ST__MASK_ST_AUX_CTL_REG CYREG_UDB_CAT16_ACTL_MSK_00
#define xbee_BUART_sRX_RxBitCounter_ST__PER_ST_AUX_CTL_REG CYREG_UDB_CAT16_ACTL_MSK_00
#define xbee_BUART_sRX_RxBitCounter_ST__STATUS_AUX_CTL_REG CYREG_UDB_W8_ACTL_00
#define xbee_BUART_sRX_RxBitCounter_ST__STATUS_CNT_REG CYREG_UDB_CAT16_CTL_ST_00
#define xbee_BUART_sRX_RxBitCounter_ST__STATUS_CONTROL_REG CYREG_UDB_CAT16_CTL_ST_00
#define xbee_BUART_sRX_RxBitCounter_ST__STATUS_REG CYREG_UDB_W8_ST_00
#define xbee_BUART_sRX_RxShifter_u0__16BIT_A0_REG CYREG_UDB_W16_A0_00
#define xbee_BUART_sRX_RxShifter_u0__16BIT_A1_REG CYREG_UDB_W16_A1_00
#define xbee_BUART_sRX_RxShifter_u0__16BIT_D0_REG CYREG_UDB_W16_D0_00
#define xbee_BUART_sRX_RxShifter_u0__16BIT_D1_REG CYREG_UDB_W16_D1_00
#define xbee_BUART_sRX_RxShifter_u0__16BIT_DP_AUX_CTL_REG CYREG_UDB_W16_ACTL_00
#define xbee_BUART_sRX_RxShifter_u0__16BIT_F0_REG CYREG_UDB_W16_F0_00
#define xbee_BUART_sRX_RxShifter_u0__16BIT_F1_REG CYREG_UDB_W16_F1_00
#define xbee_BUART_sRX_RxShifter_u0__32BIT_A0_REG CYREG_UDB_W32_A0_00
#define xbee_BUART_sRX_RxShifter_u0__32BIT_A1_REG CYREG_UDB_W32_A1_00
#define xbee_BUART_sRX_RxShifter_u0__32BIT_D0_REG CYREG_UDB_W32_D0_00
#define xbee_BUART_sRX_RxShifter_u0__32BIT_D1_REG CYREG_UDB_W32_D1_00
#define xbee_BUART_sRX_RxShifter_u0__32BIT_DP_AUX_CTL_REG CYREG_UDB_W32_ACTL_00
#define xbee_BUART_sRX_RxShifter_u0__32BIT_F0_REG CYREG_UDB_W32_F0_00
#define xbee_BUART_sRX_RxShifter_u0__32BIT_F1_REG CYREG_UDB_W32_F1_00
#define xbee_BUART_sRX_RxShifter_u0__A0_A1_REG CYREG_UDB_CAT16_A_00
#define xbee_BUART_sRX_RxShifter_u0__A0_REG CYREG_UDB_W8_A0_00
#define xbee_BUART_sRX_RxShifter_u0__A1_REG CYREG_UDB_W8_A1_00
#define xbee_BUART_sRX_RxShifter_u0__D0_D1_REG CYREG_UDB_CAT16_D_00
#define xbee_BUART_sRX_RxShifter_u0__D0_REG CYREG_UDB_W8_D0_00
#define xbee_BUART_sRX_RxShifter_u0__D1_REG CYREG_UDB_W8_D1_00
#define xbee_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG CYREG_UDB_W8_ACTL_00
#define xbee_BUART_sRX_RxShifter_u0__F0_F1_REG CYREG_UDB_CAT16_F_00
#define xbee_BUART_sRX_RxShifter_u0__F0_REG CYREG_UDB_W8_F0_00
#define xbee_BUART_sRX_RxShifter_u0__F1_REG CYREG_UDB_W8_F1_00
#define xbee_BUART_sRX_RxShifter_u0__MSK_DP_AUX_CTL_REG CYREG_UDB_CAT16_ACTL_MSK_00
#define xbee_BUART_sRX_RxShifter_u0__PER_DP_AUX_CTL_REG CYREG_UDB_CAT16_ACTL_MSK_00
#define xbee_BUART_sRX_RxSts__16BIT_STATUS_AUX_CTL_REG CYREG_UDB_W16_ACTL_01
#define xbee_BUART_sRX_RxSts__16BIT_STATUS_REG CYREG_UDB_W16_ST_01
#define xbee_BUART_sRX_RxSts__3__MASK 0x08u
#define xbee_BUART_sRX_RxSts__3__POS 3
#define xbee_BUART_sRX_RxSts__4__MASK 0x10u
#define xbee_BUART_sRX_RxSts__4__POS 4
#define xbee_BUART_sRX_RxSts__5__MASK 0x20u
#define xbee_BUART_sRX_RxSts__5__POS 5
#define xbee_BUART_sRX_RxSts__MASK 0x38u
#define xbee_BUART_sRX_RxSts__MASK_REG CYREG_UDB_W8_MSK_01
#define xbee_BUART_sRX_RxSts__STATUS_AUX_CTL_REG CYREG_UDB_W8_ACTL_01
#define xbee_BUART_sRX_RxSts__STATUS_REG CYREG_UDB_W8_ST_01
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A0_REG CYREG_UDB_W16_A0_02
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A1_REG CYREG_UDB_W16_A1_02
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D0_REG CYREG_UDB_W16_D0_02
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D1_REG CYREG_UDB_W16_D1_02
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_DP_AUX_CTL_REG CYREG_UDB_W16_ACTL_02
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F0_REG CYREG_UDB_W16_F0_02
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F1_REG CYREG_UDB_W16_F1_02
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__A0_A1_REG CYREG_UDB_CAT16_A_02
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__A0_REG CYREG_UDB_W8_A0_02
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__A1_REG CYREG_UDB_W8_A1_02
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__D0_D1_REG CYREG_UDB_CAT16_D_02
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG CYREG_UDB_W8_D0_02
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG CYREG_UDB_W8_D1_02
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__DP_AUX_CTL_REG CYREG_UDB_W8_ACTL_02
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__F0_F1_REG CYREG_UDB_CAT16_F_02
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__F0_REG CYREG_UDB_W8_F0_02
#define xbee_BUART_sTX_sCLOCK_TxBitClkGen__F1_REG CYREG_UDB_W8_F1_02
#define xbee_BUART_sTX_TxShifter_u0__A0_A1_REG CYREG_UDB_CAT16_A_03
#define xbee_BUART_sTX_TxShifter_u0__A0_REG CYREG_UDB_W8_A0_03
#define xbee_BUART_sTX_TxShifter_u0__A1_REG CYREG_UDB_W8_A1_03
#define xbee_BUART_sTX_TxShifter_u0__D0_D1_REG CYREG_UDB_CAT16_D_03
#define xbee_BUART_sTX_TxShifter_u0__D0_REG CYREG_UDB_W8_D0_03
#define xbee_BUART_sTX_TxShifter_u0__D1_REG CYREG_UDB_W8_D1_03
#define xbee_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG CYREG_UDB_W8_ACTL_03
#define xbee_BUART_sTX_TxShifter_u0__F0_F1_REG CYREG_UDB_CAT16_F_03
#define xbee_BUART_sTX_TxShifter_u0__F0_REG CYREG_UDB_W8_F0_03
#define xbee_BUART_sTX_TxShifter_u0__F1_REG CYREG_UDB_W8_F1_03
#define xbee_BUART_sTX_TxSts__0__MASK 0x01u
#define xbee_BUART_sTX_TxSts__0__POS 0
#define xbee_BUART_sTX_TxSts__1__MASK 0x02u
#define xbee_BUART_sTX_TxSts__1__POS 1
#define xbee_BUART_sTX_TxSts__2__MASK 0x04u
#define xbee_BUART_sTX_TxSts__2__POS 2
#define xbee_BUART_sTX_TxSts__3__MASK 0x08u
#define xbee_BUART_sTX_TxSts__3__POS 3
#define xbee_BUART_sTX_TxSts__MASK 0x0Fu
#define xbee_BUART_sTX_TxSts__MASK_REG CYREG_UDB_W8_MSK_03
#define xbee_BUART_sTX_TxSts__STATUS_AUX_CTL_REG CYREG_UDB_W8_ACTL_03
#define xbee_BUART_sTX_TxSts__STATUS_REG CYREG_UDB_W8_ST_03

/* xbee_IntClock */
#define xbee_IntClock__DIVIDER_MASK 0x0000FFFFu
#define xbee_IntClock__ENABLE CYREG_CLK_DIVIDER_A00
#define xbee_IntClock__ENABLE_MASK 0x80000000u
#define xbee_IntClock__MASK 0x80000000u
#define xbee_IntClock__REGISTER CYREG_CLK_DIVIDER_A00

/* Clock */
#define Clock__DIVIDER_MASK 0x0000FFFFu
#define Clock__ENABLE CYREG_CLK_DIVIDER_B00
#define Clock__ENABLE_MASK 0x80000000u
#define Clock__MASK 0x80000000u
#define Clock__REGISTER CYREG_CLK_DIVIDER_B00

/* timer_cy_m0s8_tcpwm_1 */
#define timer_cy_m0s8_tcpwm_1__CC CYREG_TCPWM_CNT0_CC
#define timer_cy_m0s8_tcpwm_1__CC_BUFF CYREG_TCPWM_CNT0_CC_BUFF
#define timer_cy_m0s8_tcpwm_1__COUNTER CYREG_TCPWM_CNT0_COUNTER
#define timer_cy_m0s8_tcpwm_1__CTRL CYREG_TCPWM_CNT0_CTRL
#define timer_cy_m0s8_tcpwm_1__INTR CYREG_TCPWM_CNT0_INTR
#define timer_cy_m0s8_tcpwm_1__INTR_MASK CYREG_TCPWM_CNT0_INTR_MASK
#define timer_cy_m0s8_tcpwm_1__INTR_MASKED CYREG_TCPWM_CNT0_INTR_MASKED
#define timer_cy_m0s8_tcpwm_1__INTR_SET CYREG_TCPWM_CNT0_INTR_SET
#define timer_cy_m0s8_tcpwm_1__PERIOD CYREG_TCPWM_CNT0_PERIOD
#define timer_cy_m0s8_tcpwm_1__PERIOD_BUFF CYREG_TCPWM_CNT0_PERIOD_BUFF
#define timer_cy_m0s8_tcpwm_1__STATUS CYREG_TCPWM_CNT0_STATUS
#define timer_cy_m0s8_tcpwm_1__TCPWM_CMD CYREG_TCPWM_CMD
#define timer_cy_m0s8_tcpwm_1__TCPWM_CMDCAPTURE_MASK 0x01u
#define timer_cy_m0s8_tcpwm_1__TCPWM_CMDCAPTURE_SHIFT 0
#define timer_cy_m0s8_tcpwm_1__TCPWM_CMDRELOAD_MASK 0x100u
#define timer_cy_m0s8_tcpwm_1__TCPWM_CMDRELOAD_SHIFT 8
#define timer_cy_m0s8_tcpwm_1__TCPWM_CMDSTART_MASK 0x1000000u
#define timer_cy_m0s8_tcpwm_1__TCPWM_CMDSTART_SHIFT 24
#define timer_cy_m0s8_tcpwm_1__TCPWM_CMDSTOP_MASK 0x10000u
#define timer_cy_m0s8_tcpwm_1__TCPWM_CMDSTOP_SHIFT 16
#define timer_cy_m0s8_tcpwm_1__TCPWM_CTRL CYREG_TCPWM_CTRL
#define timer_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK 0x01u
#define timer_cy_m0s8_tcpwm_1__TCPWM_CTRL_SHIFT 0
#define timer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE CYREG_TCPWM_INTR_CAUSE
#define timer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE_MASK 0x01u
#define timer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE_SHIFT 0
#define timer_cy_m0s8_tcpwm_1__TCPWM_NUMBER 0u
#define timer_cy_m0s8_tcpwm_1__TR_CTRL0 CYREG_TCPWM_CNT0_TR_CTRL0
#define timer_cy_m0s8_tcpwm_1__TR_CTRL1 CYREG_TCPWM_CNT0_TR_CTRL1
#define timer_cy_m0s8_tcpwm_1__TR_CTRL2 CYREG_TCPWM_CNT0_TR_CTRL2

/* wired */
#define wired__0__DM__MASK 0xE00000u
#define wired__0__DM__SHIFT 21
#define wired__0__DR CYREG_PRT2_DR
#define wired__0__HSIOM CYREG_HSIOM_PORT_SEL2
#define wired__0__HSIOM_MASK 0xF0000000u
#define wired__0__HSIOM_SHIFT 28u
#define wired__0__INTCFG CYREG_PRT2_INTCFG
#define wired__0__INTSTAT CYREG_PRT2_INTSTAT
#define wired__0__MASK 0x80u
#define wired__0__PA__CFG0 CYREG_UDB_PA2_CFG0
#define wired__0__PA__CFG1 CYREG_UDB_PA2_CFG1
#define wired__0__PA__CFG10 CYREG_UDB_PA2_CFG10
#define wired__0__PA__CFG11 CYREG_UDB_PA2_CFG11
#define wired__0__PA__CFG12 CYREG_UDB_PA2_CFG12
#define wired__0__PA__CFG13 CYREG_UDB_PA2_CFG13
#define wired__0__PA__CFG14 CYREG_UDB_PA2_CFG14
#define wired__0__PA__CFG2 CYREG_UDB_PA2_CFG2
#define wired__0__PA__CFG3 CYREG_UDB_PA2_CFG3
#define wired__0__PA__CFG4 CYREG_UDB_PA2_CFG4
#define wired__0__PA__CFG5 CYREG_UDB_PA2_CFG5
#define wired__0__PA__CFG6 CYREG_UDB_PA2_CFG6
#define wired__0__PA__CFG7 CYREG_UDB_PA2_CFG7
#define wired__0__PA__CFG8 CYREG_UDB_PA2_CFG8
#define wired__0__PA__CFG9 CYREG_UDB_PA2_CFG9
#define wired__0__PC CYREG_PRT2_PC
#define wired__0__PC2 CYREG_PRT2_PC2
#define wired__0__PORT 2u
#define wired__0__PS CYREG_PRT2_PS
#define wired__0__SHIFT 7
#define wired__DR CYREG_PRT2_DR
#define wired__INTCFG CYREG_PRT2_INTCFG
#define wired__INTSTAT CYREG_PRT2_INTSTAT
#define wired__MASK 0x80u
#define wired__PA__CFG0 CYREG_UDB_PA2_CFG0
#define wired__PA__CFG1 CYREG_UDB_PA2_CFG1
#define wired__PA__CFG10 CYREG_UDB_PA2_CFG10
#define wired__PA__CFG11 CYREG_UDB_PA2_CFG11
#define wired__PA__CFG12 CYREG_UDB_PA2_CFG12
#define wired__PA__CFG13 CYREG_UDB_PA2_CFG13
#define wired__PA__CFG14 CYREG_UDB_PA2_CFG14
#define wired__PA__CFG2 CYREG_UDB_PA2_CFG2
#define wired__PA__CFG3 CYREG_UDB_PA2_CFG3
#define wired__PA__CFG4 CYREG_UDB_PA2_CFG4
#define wired__PA__CFG5 CYREG_UDB_PA2_CFG5
#define wired__PA__CFG6 CYREG_UDB_PA2_CFG6
#define wired__PA__CFG7 CYREG_UDB_PA2_CFG7
#define wired__PA__CFG8 CYREG_UDB_PA2_CFG8
#define wired__PA__CFG9 CYREG_UDB_PA2_CFG9
#define wired__PC CYREG_PRT2_PC
#define wired__PC2 CYREG_PRT2_PC2
#define wired__PORT 2u
#define wired__PS CYREG_PRT2_PS
#define wired__SHIFT 7
#define wired__SNAP CYREG_PRT2_INTSTAT

/* finish */
#define finish__0__DM__MASK 0xE00000u
#define finish__0__DM__SHIFT 21
#define finish__0__DR CYREG_PRT0_DR
#define finish__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define finish__0__HSIOM_MASK 0xF0000000u
#define finish__0__HSIOM_SHIFT 28u
#define finish__0__INTCFG CYREG_PRT0_INTCFG
#define finish__0__INTSTAT CYREG_PRT0_INTSTAT
#define finish__0__MASK 0x80u
#define finish__0__PA__CFG0 CYREG_UDB_PA0_CFG0
#define finish__0__PA__CFG1 CYREG_UDB_PA0_CFG1
#define finish__0__PA__CFG10 CYREG_UDB_PA0_CFG10
#define finish__0__PA__CFG11 CYREG_UDB_PA0_CFG11
#define finish__0__PA__CFG12 CYREG_UDB_PA0_CFG12
#define finish__0__PA__CFG13 CYREG_UDB_PA0_CFG13
#define finish__0__PA__CFG14 CYREG_UDB_PA0_CFG14
#define finish__0__PA__CFG2 CYREG_UDB_PA0_CFG2
#define finish__0__PA__CFG3 CYREG_UDB_PA0_CFG3
#define finish__0__PA__CFG4 CYREG_UDB_PA0_CFG4
#define finish__0__PA__CFG5 CYREG_UDB_PA0_CFG5
#define finish__0__PA__CFG6 CYREG_UDB_PA0_CFG6
#define finish__0__PA__CFG7 CYREG_UDB_PA0_CFG7
#define finish__0__PA__CFG8 CYREG_UDB_PA0_CFG8
#define finish__0__PA__CFG9 CYREG_UDB_PA0_CFG9
#define finish__0__PC CYREG_PRT0_PC
#define finish__0__PC2 CYREG_PRT0_PC2
#define finish__0__PORT 0u
#define finish__0__PS CYREG_PRT0_PS
#define finish__0__SHIFT 7
#define finish__DR CYREG_PRT0_DR
#define finish__INTCFG CYREG_PRT0_INTCFG
#define finish__INTSTAT CYREG_PRT0_INTSTAT
#define finish__MASK 0x80u
#define finish__PA__CFG0 CYREG_UDB_PA0_CFG0
#define finish__PA__CFG1 CYREG_UDB_PA0_CFG1
#define finish__PA__CFG10 CYREG_UDB_PA0_CFG10
#define finish__PA__CFG11 CYREG_UDB_PA0_CFG11
#define finish__PA__CFG12 CYREG_UDB_PA0_CFG12
#define finish__PA__CFG13 CYREG_UDB_PA0_CFG13
#define finish__PA__CFG14 CYREG_UDB_PA0_CFG14
#define finish__PA__CFG2 CYREG_UDB_PA0_CFG2
#define finish__PA__CFG3 CYREG_UDB_PA0_CFG3
#define finish__PA__CFG4 CYREG_UDB_PA0_CFG4
#define finish__PA__CFG5 CYREG_UDB_PA0_CFG5
#define finish__PA__CFG6 CYREG_UDB_PA0_CFG6
#define finish__PA__CFG7 CYREG_UDB_PA0_CFG7
#define finish__PA__CFG8 CYREG_UDB_PA0_CFG8
#define finish__PA__CFG9 CYREG_UDB_PA0_CFG9
#define finish__PC CYREG_PRT0_PC
#define finish__PC2 CYREG_PRT0_PC2
#define finish__PORT 0u
#define finish__PS CYREG_PRT0_PS
#define finish__SHIFT 7
#define finish__SNAP CYREG_PRT0_INTSTAT

/* isr_xbee */
#define isr_xbee__INTC_CLR_EN_REG CYREG_CM0_ICER
#define isr_xbee__INTC_CLR_PD_REG CYREG_CM0_ICPR
#define isr_xbee__INTC_MASK 0x02u
#define isr_xbee__INTC_NUMBER 1u
#define isr_xbee__INTC_PRIOR_MASK 0xC000u
#define isr_xbee__INTC_PRIOR_NUM 3u
#define isr_xbee__INTC_PRIOR_REG CYREG_CM0_IPR0
#define isr_xbee__INTC_SET_EN_REG CYREG_CM0_ISER
#define isr_xbee__INTC_SET_PD_REG CYREG_CM0_ISPR

/* isr_timer */
#define isr_timer__INTC_CLR_EN_REG CYREG_CM0_ICER
#define isr_timer__INTC_CLR_PD_REG CYREG_CM0_ICPR
#define isr_timer__INTC_MASK 0x10000u
#define isr_timer__INTC_NUMBER 16u
#define isr_timer__INTC_PRIOR_MASK 0xC0u
#define isr_timer__INTC_PRIOR_NUM 3u
#define isr_timer__INTC_PRIOR_REG CYREG_CM0_IPR4
#define isr_timer__INTC_SET_EN_REG CYREG_CM0_ISER
#define isr_timer__INTC_SET_PD_REG CYREG_CM0_ISPR

/* isr_wired */
#define isr_wired__INTC_CLR_EN_REG CYREG_CM0_ICER
#define isr_wired__INTC_CLR_PD_REG CYREG_CM0_ICPR
#define isr_wired__INTC_MASK 0x04u
#define isr_wired__INTC_NUMBER 2u
#define isr_wired__INTC_PRIOR_MASK 0xC00000u
#define isr_wired__INTC_PRIOR_NUM 3u
#define isr_wired__INTC_PRIOR_REG CYREG_CM0_IPR0
#define isr_wired__INTC_SET_EN_REG CYREG_CM0_ISER
#define isr_wired__INTC_SET_PD_REG CYREG_CM0_ISPR

/* isr_finish */
#define isr_finish__INTC_CLR_EN_REG CYREG_CM0_ICER
#define isr_finish__INTC_CLR_PD_REG CYREG_CM0_ICPR
#define isr_finish__INTC_MASK 0x01u
#define isr_finish__INTC_NUMBER 0u
#define isr_finish__INTC_PRIOR_MASK 0xC0u
#define isr_finish__INTC_PRIOR_NUM 3u
#define isr_finish__INTC_PRIOR_REG CYREG_CM0_IPR0
#define isr_finish__INTC_SET_EN_REG CYREG_CM0_ISER
#define isr_finish__INTC_SET_PD_REG CYREG_CM0_ISPR

/* Miscellaneous */
#define CY_PROJECT_NAME "finish01"
#define CY_VERSION "PSoC Creator  3.3 SP1"
#define CYDEV_BCLK__HFCLK__HZ 24000000U
#define CYDEV_BCLK__HFCLK__KHZ 24000U
#define CYDEV_BCLK__HFCLK__MHZ 24U
#define CYDEV_BCLK__SYSCLK__HZ 24000000U
#define CYDEV_BCLK__SYSCLK__KHZ 24000U
#define CYDEV_BCLK__SYSCLK__MHZ 24U
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PANTHER 18u
#define CYDEV_CHIP_DIE_PSOC4A 10u
#define CYDEV_CHIP_DIE_PSOC5LP 17u
#define CYDEV_CHIP_DIE_TMA4 2u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC4
#define CYDEV_CHIP_JTAG_ID 0x04C81193u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_4A 10u
#define CYDEV_CHIP_MEMBER_4C 15u
#define CYDEV_CHIP_MEMBER_4D 6u
#define CYDEV_CHIP_MEMBER_4E 4u
#define CYDEV_CHIP_MEMBER_4F 11u
#define CYDEV_CHIP_MEMBER_4G 2u
#define CYDEV_CHIP_MEMBER_4H 9u
#define CYDEV_CHIP_MEMBER_4I 14u
#define CYDEV_CHIP_MEMBER_4J 7u
#define CYDEV_CHIP_MEMBER_4K 8u
#define CYDEV_CHIP_MEMBER_4L 13u
#define CYDEV_CHIP_MEMBER_4M 12u
#define CYDEV_CHIP_MEMBER_4N 5u
#define CYDEV_CHIP_MEMBER_4U 3u
#define CYDEV_CHIP_MEMBER_5A 17u
#define CYDEV_CHIP_MEMBER_5B 16u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_4A
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_MEMBER_USED
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PANTHER_ES0 0u
#define CYDEV_CHIP_REV_PANTHER_ES1 1u
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CHIP_REV_TMA4_ES 17u
#define CYDEV_CHIP_REV_TMA4_ES2 33u
#define CYDEV_CHIP_REV_TMA4_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4C_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4D_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4E_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION_256K 0u
#define CYDEV_CHIP_REVISION_4G_ES 17u
#define CYDEV_CHIP_REVISION_4G_ES2 33u
#define CYDEV_CHIP_REVISION_4G_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4H_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4I_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4J_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4K_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4L_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4M_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4N_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4U_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_4A_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REVISION_USED
#define CYDEV_CONFIG_READ_ACCELERATOR 1
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_DEBUG_PROTECT_KILL 4
#define CYDEV_DEBUG_PROTECT_OPEN 1
#define CYDEV_DEBUG_PROTECT CYDEV_DEBUG_PROTECT_OPEN
#define CYDEV_DEBUG_PROTECT_PROTECTED 2
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_SWD
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DFT_SELECT_CLK0 1u
#define CYDEV_DFT_SELECT_CLK1 2u
#define CYDEV_HEAP_SIZE 0x80
#define CYDEV_IMO_TRIMMED_BY_USB 0u
#define CYDEV_IMO_TRIMMED_BY_WCO 0u
#define CYDEV_IS_EXPORTING_CODE 0
#define CYDEV_IS_IMPORTING_CODE 0
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LAUNCHER 5
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER 4
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_STACK_SIZE 0x0400
#define CYDEV_USE_BUNDLED_CMSIS 1
#define CYDEV_VARIABLE_VDDA 1
#define CYDEV_VDDA 3.3
#define CYDEV_VDDA_MV 3300
#define CYDEV_VDDD 3.3
#define CYDEV_VDDD_MV 3300
#define CYDEV_WDT_GENERATE_ISR 1u
#define CYIPBLOCK_M0S8_CTBM_VERSION 0
#define CYIPBLOCK_m0s8cpuss_VERSION 0
#define CYIPBLOCK_m0s8csd_VERSION 0
#define CYIPBLOCK_m0s8gpio2_VERSION 0
#define CYIPBLOCK_m0s8hsiom4a_VERSION 0
#define CYIPBLOCK_m0s8lcd_VERSION 0
#define CYIPBLOCK_m0s8lpcomp_VERSION 0
#define CYIPBLOCK_m0s8pclk_VERSION 0
#define CYIPBLOCK_m0s8sar_VERSION 0
#define CYIPBLOCK_m0s8scb_VERSION 0
#define CYIPBLOCK_m0s8srssv2_VERSION 1
#define CYIPBLOCK_m0s8tcpwm_VERSION 0
#define CYIPBLOCK_m0s8udbif_VERSION 0
#define CYIPBLOCK_S8_GPIO_VERSION 2
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
