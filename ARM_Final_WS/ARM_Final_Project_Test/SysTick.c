 /******************************************************************************
 *
 * Module: SysTick Timer
 *
 * File Name: systick.h
 *
 * Description: Source file for the SysTick Timer driver
 *
 * Author: Karima Mahmoud
 *
 *******************************************************************************/

/*******************************************************************************
 *                            Header Files                                     *
 *******************************************************************************/
#include "SysTick.h"
#include "tm4c123gh6pm_registers.h"

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                          Exception Handlers                                 *
 *******************************************************************************/
/*********************************************************************
* Service Name: SysTick_Handler
* Sync/Async: Asynchronous
* Reentrancy: non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Handler for SysTick interrupt use to call the call-back function.
**********************************************************************/
 void SysTick_Handler(void)
 {
     if(g_callBackPtr != NULL_PTR)
     {
         /* Call back function in main application after edge detected */
         (*g_callBackPtr)();
     }
 }

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

 /*********************************************************************
 * Service Name: SysTick_Init
 * Sync/Async: Synchronous
 * Reentrancy: non reentrant
 * Parameters (in): a_TimeInMilliSeconds - Required Time delay in milliseconds
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to initialize SysTick Timer with  the specified time in milliseconds
                using interrupts.
 **********************************************************************/

 void SysTick_Init(uint16 a_TimeInMilliSeconds)
 {
     SYSTICK_CTRL_REG = 0;      /* Disable the SysTick Timer by clear the ENABLE bit */

     /* Set the Reload value with the value of a_TimeInMilliSeconds in seconds */
     SYSTICK_RELOAD_REG = ((a_TimeInMilliSeconds * 16000) - 1);

     /* Clear the Current register value */
     SYSTICK_CURRENT_REG = 0;

     /* Configure the SysTick Control Register
      * Enable the SysTick Timer (ENABLE = 1)
      * Enable SysTick Interrupt (INTEN = 1)
      * Choose the clock source to be the system clock (CLK_SRC = 1) */
     SYSTICK_CTRL_REG |= 0x07;

 }

 /*********************************************************************
 * Service Name: SysTick_StartBusyWait
 * Sync/Async: Synchronous
 * Reentrancy: non reentrant
 * Parameters (in): a_TimeInMilliSeconds - Required Time delay in milliseconds
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to initialize SysTick Timer with  the specified time in milliseconds
                using Polling.
 **********************************************************************/
 void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds)
 {
     SYSTICK_CTRL_REG = 0;      /* Disable the SysTick Timer by clear the ENABLE bit */

     /* Set the Reload value with the value of a_TimeInMilliSeconds in seconds */
     SYSTICK_RELOAD_REG = ((a_TimeInMilliSeconds * 16000) - 1);

     /* Clear the Current register value */
     SYSTICK_CURRENT_REG = 0;

     /* Configure the SysTick Control Register
      * Enable the SysTick Timer (ENABLE = 1)
      * Disable SysTick Interrupt (INTEN = 0)
      * Choose the clock source to be the system clock (CLK_SRC = 1) */
     SYSTICK_CTRL_REG |= 0x05;

     /* wait until the COUNT flag = 1 which mean SysTick Timer reaches ZERO value ... COUNT flag is cleared after read the CTRL register value */
     while(!(SYSTICK_CTRL_REG & (1<<16)));

     /* Disable the SysTick Timer by clear the ENABLE bit */
     SysTick_Stop();
 }

 /*********************************************************************
 * Service Name: SysTick_SetCallBack
 * Sync/Async: Synchronous
 * Reentrancy: non-reentrant
 * Parameters (in): Ptr2Func - a pointer to function to hold the address of the call back function
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to setup the SysTick Timer call back to be executed in
                SysTick Handler.
 **********************************************************************/
 void SysTick_SetCallBack(volatile void (*Ptr2Func) (void))
 {
     g_callBackPtr = Ptr2Func;
 }

 /*********************************************************************
 * Service Name: SysTick_Stop
 * Sync/Async: Synchronous
 * Reentrancy: non-reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Stop the SysTick timer.
 **********************************************************************/
 void SysTick_Stop(void)
 {
     /* Disable The SysTick Timer */
     SYSTICK_CTRL_REG &= ~(1<<0);
 }

 /*********************************************************************
 * Service Name: SysTick_Start
 * Sync/Async: Synchronous
 * Reentrancy: non-reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Start the SysTick timer.
 **********************************************************************/
 void SysTick_Start(void)
 {
     /* Enable The SysTick Timer  */
     SYSTICK_CTRL_REG |= (1<<0);
 }

 /*********************************************************************
 * Service Name: SysTick_DeInit
 * Sync/Async: Synchronous
 * Reentrancy: non-reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to De-initialize the SysTick Timer.
 **********************************************************************/
 void SysTick_DeInit(void)
 {
     /* Clear the SysTick Control Register */
     SYSTICK_CTRL_REG = 0;

     /* Clear the SysTick Current Register */
     SYSTICK_CURRENT_REG = 0;

     /* Clear the SysTick Reload Register */
     SYSTICK_RELOAD_REG = 0;
 }

