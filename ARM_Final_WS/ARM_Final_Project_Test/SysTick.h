 /******************************************************************************
 *
 * Module: SysTick Timer
 *
 * File Name: systick.h
 *
 * Description: header file for the SysTick Timer driver
 *
 * Author: Karima Mahmoud
 *
 *******************************************************************************/

#ifndef SYSTICK_H_
#define SYSTICK_H_

/*******************************************************************************
 *                            Header Files                                     *
 *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
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
 void SysTick_Init(uint16 a_TimeInMilliSeconds);

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
 void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);

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
 void SysTick_Handler(void);

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
 void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));

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
 void SysTick_Stop(void);

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
 void SysTick_Start(void);

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
 void SysTick_DeInit(void);


#endif /* SYSTICK_H_ */
