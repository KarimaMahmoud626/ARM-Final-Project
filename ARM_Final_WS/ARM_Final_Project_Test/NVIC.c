 /******************************************************************************
 *
 * Module: Nested Vectored Interrupt Controller
 *
 * File Name: nvic.c
 *
 * Description: Source file for the NVIC driver for TM4C123GH6PM
 *
 * Author: Karima Mahmoud
 *
 *******************************************************************************/

/*******************************************************************************
 *                                    Header Files                             *
 *******************************************************************************/
#include "NVIC.h"
#include "tm4c123gh6pm_registers.h"

/*******************************************************************************
 *                               Functions Definitions                         *
 *******************************************************************************/

/*********************************************************************
* Service Name: NVIC_EnableIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to enable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    switch(IRQ_Num)
    {
    case 0 ... 31: /* In case of IRQs with numbers from 0 to 31 */
        /* Enable the IRQ on NVIC_EN0_REG based on IRQ_Num function argument */
        NVIC_EN0_REG |= (1<<IRQ_Num);
        break;
    case 32 ... 63: /* In case of IRQs with numbers from 32 to 63 */
        /* Enable the IRQ on NVIC_EN1_REG based on IRQ_Num function argument */
        NVIC_EN1_REG |= (1<<(IRQ_Num & 0x1F));
        break;
    case 64 ... 95: /* In case of IRQs with numbers from 64 to 95 */
        /* Enable the IRQ on NVIC_EN2_REG based on IRQ_Num function argument */
        NVIC_EN2_REG |= (1<<(IRQ_Num & 0x1F));
        break;
    case 96 ... 127: /* In case of IRQs with numbers from 96 to 127 */
        /* Enable the IRQ on NVIC_EN3_REG based on IRQ_Num function argument */
        NVIC_EN3_REG |= (1<<(IRQ_Num & 0x1F));
        break;
    case 128 ... 138: /* In case of IRQs with numbers from 128 to 138 */
        /* Enable the IRQ on NVIC_EN4_REG based on IRQ_Num function argument */
        NVIC_EN4_REG |= (1<<(IRQ_Num & 0x1F));
        break;
    }
}

/*********************************************************************
* Service Name: NVIC_DisableIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to disable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{
    switch(IRQ_Num)
    {
    case 0 ... 31: /* In case of IRQs with numbers from 0 to 31 */
        /* Disable the IRQ on NVIC_DIS0_REG based on IRQ_Num function argument */
        NVIC_DIS0_REG |= (1<<IRQ_Num);
        break;
    case 32 ... 63: /* In case of IRQs with numbers from 32 to 63 */
        /* Disable the IRQ on NVIC_DIS1_REG based on IRQ_Num function argument */
        NVIC_DIS1_REG |= (1<<(IRQ_Num & 0x1F));
        break;
    case 64 ... 95: /* In case of IRQs with numbers from 64 to 95 */
        /* Disable the IRQ on NVIC_DIS2_REG based on IRQ_Num function argument */
        NVIC_DIS2_REG |= (1<<(IRQ_Num & 0x1F));
        break;
    case 96 ... 127: /* In case of IRQs with numbers from 96 to 127 */
        /* Disable the IRQ on NVIC_DIS3_REG based on IRQ_Num function argument */
        NVIC_DIS3_REG |= (1<<(IRQ_Num & 0x1F));
        break;
    case 128 ... 138: /* In case of IRQs with numbers from 128 to 138 */
        /* Disable the IRQ on NVIC_DIS4_REG based on IRQ_Num function argument */
        NVIC_DIS4_REG |= (1<<(IRQ_Num & 0x1F));
        break;
    }
}

/*********************************************************************
* Service Name: NVIC_SetPriorityIRQ
* Sync/Async: Synchronous
* Reentrancy: non reentrant
* Parameters (in): 1.IRQ_Num - Number of the IRQ from the target vector table
*                  2.IRQ_Priority - The required Priority for the IRQ
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the priority value for specific IRQ.
**********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority)
{
    /* Pointer to uint32 to point to the required Priority Register (NVIC_PRIn_REG) */
    volatile uint32 *Pri_Reg_PTR = NULL_PTR;
    uint8 Pri_Mask = 0;
    /* Variable to hold the bits position of the priority number */
    volatile uint8 Pri_Bits_Pos = 0;

    /* Equation to calculate the address of the required priority register based on the IRQ_Num */
    Pri_Reg_PTR = (volatile uint32 *)(NVIC_PRI_BASE_ADDRESS + ((IRQ_Num / 4) * 4));

    /* The priority bit positions has a fixed starting numbers 5  - 7, 13 - 15, 21 - 23, 29 - 31
     *                                                         00101   01101    10101    11101
     * The Least Significant 3 bits are the same (0x05) and the remaining two bits are numbers from 0 to 3
     * The Least Significant two Bits of the IRQ_NUM are numbers from 0 to 3
     * So with this two bits shifted left by 3 and insert the number (0x05), we have the required position */
    Pri_Bits_Pos = ((IRQ_Num & 0x03)<<3) | 0x05;

    Pri_Mask = ~(0x07<<Pri_Bits_Pos);

    /* Set the required Priority for the required IRQ */
    (*Pri_Reg_PTR) = ((*Pri_Reg_PTR) & Pri_Mask) | (IRQ_Priority<<Pri_Bits_Pos);
}

/*********************************************************************
* Service Name: NVIC_EnableException
* Sync/Async: Synchronous
* Reentrancy: non reentrant
* Parameters (in): Exception_Num - Number of the Exception from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to enable specific ARM system or fault exceptions.
**********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{
    switch(Exception_Num)
    {
    case EXCEPTION_MEM_FAULT_TYPE: /* In case of MemManagement Fault */
        /* Set MEM bit in the NVIC_SYSTEM_SYSHNDCTRL to enable MemManagement Fault */
        NVIC_SYSTEM_SYSHNDCTRL |= MEM_FAULT_ENABLE_MASK;
        break;
    case EXCEPTION_BUS_FAULT_TYPE: /* In case of Bus Fault */
        /* Set BUS bit in the NVIC_SYSTEM_SYSHNDCTRL to enable Bus Fault */
        NVIC_SYSTEM_SYSHNDCTRL |= BUS_FAULT_ENABLE_MASK;
        break;
    case EXCEPTION_USAGE_FAULT_TYPE: /* In case of Usage Fault */
        /* Set USAGE bit in the NVIC_SYSTEM_SYSHNDCTRL to enable Usage Fault */
        NVIC_SYSTEM_SYSHNDCTRL |= USAGE_FAULT_ENABLE_MASK;
        break;
    }
}

/*********************************************************************
* Service Name: NVIC_DisableException
* Sync/Async: Synchronous
* Reentrancy: non reentrant
* Parameters (in): Exception_Num - Number of the Exception from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to disable specific ARM system or fault exceptions.
**********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
    switch(Exception_Num)
    {
    case EXCEPTION_MEM_FAULT_TYPE: /* In case of MemManagement Fault */
        /* Clear MEM bit in the NVIC_SYSTEM_SYSHNDCTRL to disable MemManagement Fault */
        NVIC_SYSTEM_SYSHNDCTRL &= ~(MEM_FAULT_ENABLE_MASK);
        break;
    case EXCEPTION_BUS_FAULT_TYPE: /* In case of Bus Fault */
        /* Clear BUS bit in the NVIC_SYSTEM_SYSHNDCTRL to disable Bus Fault */
        NVIC_SYSTEM_SYSHNDCTRL &= ~(BUS_FAULT_ENABLE_MASK);
        break;
    case EXCEPTION_USAGE_FAULT_TYPE: /* In case of Usage Fault */
        /* Clear USAGE bit in the NVIC_SYSTEM_SYSHNDCTRL to disable Usage Fault */
        NVIC_SYSTEM_SYSHNDCTRL &= ~(USAGE_FAULT_ENABLE_MASK);
        break;
    }
}

/*********************************************************************
* Service Name: NVIC_SetPriorityException
* Sync/Async: Synchronous
* Reentrancy: non reentrant
* Parameters (in): 1.Exception_Num - Number of the Exception from the target vector table
*                  2.Exception_Priority - The required Priority for the Exception
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the priority value for specific IRQ.
**********************************************************************/
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority)
{
    switch(Exception_Num)
    {
    case EXCEPTION_MEM_FAULT_TYPE: /* In case of MemManagement Fault */
        /* Set priority of MemManagement Fault as required in Exception_Priority function argument */
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & MEM_FAULT_PRIORITY_MASK) | (Exception_Priority<<MEM_FAULT_PRIORITY_BITS_POS);
        break;
    case EXCEPTION_BUS_FAULT_TYPE: /* In case of Bus Fault */
        /* Set priority of Bus Fault as required in Exception_Priority function argument */
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & BUS_FAULT_PRIORITY_MASK) | (Exception_Priority<<BUS_FAULT_PRIORITY_BITS_POS);
        break;
    case EXCEPTION_USAGE_FAULT_TYPE: /* In case of Usage Fault */
        /* Set priority of Usage Fault as required in Exception_Priority function argument */
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & USAGE_FAULT_PRIORITY_MASK) | (Exception_Priority<<USAGE_FAULT_PRIORITY_BITS_POS);
        break;
    case EXCEPTION_SVC_TYPE: /* In case of SVC Exception */
        /* Set priority of SVC Exception as required in Exception_Priority function argument */
        NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & SVC_PRIORITY_MASK) | (Exception_Priority<<SVC_PRIORITY_BITS_POS);
        break;
    case EXCEPTION_DEBUG_MONITOR_TYPE: /* In case of Debug Exception */
        /* Set priority of Debug Exception as required in Exception_Priority function argument */
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & DEBUG_MONITOR_PRIORITY_MASK) | (Exception_Priority<<DEBUG_MONITOR_PRIORITY_BITS_POS);
        break;
    case EXCEPTION_PEND_SV_TYPE: /* In case of PendSV Exception */
        /* Set priority of PendSV Exception as required in Exception_Priority function argument */
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & PENDSV_PRIORITY_MASK) | (Exception_Priority<<PENDSV_PRIORITY_BITS_POS);
        break;
    case EXCEPTION_SYSTICK_TYPE: /* In case of SysTick Timer Exception */
        /* Set priority of SysTick Timer Exception as required in Exception_Priority function argument */
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) | (Exception_Priority<<SYSTICK_PRIORITY_BITS_POS);
        break;
    }
}
