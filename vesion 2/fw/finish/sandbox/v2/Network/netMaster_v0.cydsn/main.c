/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include "lib_Network\network.h"

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    InitNetwork();
    for(;;)
    {
        AppDelay(1500);
        
    }
}

/* [] END OF FILE */
