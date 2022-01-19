/*
 * FreeRTOS V202104.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/******************************************************************************
 * NOTE: Windows will not be running the FreeRTOS demo threads continuously, so
 * do not expect to get real time behaviour from the FreeRTOS Windows port, or
 * this demo application.  Also, the timing information in the FreeRTOS+Trace
 * logs have no meaningful units.  See the documentation page for the Windows
 * port for further information:
 * http://www.freertos.org/FreeRTOS-Windows-Simulator-Emulator-for-Visual-Studio-and-Eclipse-MingW.html
 *
 * NOTE 2:  This project provides two demo applications.  A simple blinky style
 * project, and a more comprehensive test and demo application.  The
 * mainCREATE_SIMPLE_BLINKY_DEMO_ONLY setting in main.c is used to select
 * between the two.  See the notes on using mainCREATE_SIMPLE_BLINKY_DEMO_ONLY
 * in main.c.  This file implements the simply blinky version.  Console output
 * is used in place of the normal LED toggling.
 *
 * NOTE 3:  This file only contains the source code that is specific to the
 * basic demo.  Generic functions, such FreeRTOS hook functions, are defined
 * in main.c.
 ******************************************************************************
 *
 * main_blinky() creates one queue, one software timer, and two tasks.  It then
 * starts the scheduler.
 *
 * The Queue Send Task:
 * The queue send task is implemented by the prvQueueSendTask() function in
 * this file.  It uses vTaskDelayUntil() to create a periodic task that sends
 * the value 100 to the queue every 200 milliseconds (please read the notes
 * above regarding the accuracy of timing under Windows).
 *
 * The Queue Send Software Timer:
 * The timer is a one-shot timer that is reset by a key press.  The timer's
 * period is set to two seconds - if the timer expires then its callback
 * function writes the value 200 to the queue.  The callback function is
 * implemented by prvQueueSendTimerCallback() within this file.
 *
 * The Queue Receive Task:
 * The queue receive task is implemented by the prvQueueReceiveTask() function
 * in this file.  prvQueueReceiveTask() waits for data to arrive on the queue.
 * When data is received, the task checks the value of the data, then outputs a
 * message to indicate if the data came from the queue send task or the queue
 * send software timer.
 *
 * Expected Behaviour:
 * - The queue send task writes to the queue every 200ms, so every 200ms the
 *   queue receive task will output a message indicating that data was received
 *   on the queue from the queue send task.
 * - The queue send software timer has a period of two seconds, and is reset
 *   each time a key is pressed.  So if two seconds expire without a key being
 *   pressed then the queue receive task will output a message indicating that
 *   data was received on the queue from the queue send software timer.
 *
 * NOTE:  Console input and output relies on Windows system calls, which can
 * interfere with the execution of the FreeRTOS Windows port.  This demo only
 * uses Windows system call occasionally.  Heavier use of Windows system calls
 * can crash the port.
 */

/* Standard includes. */
#include <stdio.h>
#include <conio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "queue.h"

/* Priorities at which the tasks are created. */
#define mainQUEUE_RECEIVE_TASK_PRIORITY		( tskIDLE_PRIORITY + 2 )
#define	mainQUEUE_SEND_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )

/* The rate at which data is sent to the queue.  The times are converted from
milliseconds to ticks using the pdMS_TO_TICKS() macro. */
#define mainTASK_SEND_FREQUENCY_MS			pdMS_TO_TICKS( 200UL )
#define mainTIMER_SEND_FREQUENCY_MS			pdMS_TO_TICKS( 2000UL )

/* The number of items the queue can hold at once. */
#define mainQUEUE_LENGTH					( 2 )

/* The values sent to the queue receive task from the queue send task and the
queue send software timer respectively. */
#define mainVALUE_SENT_FROM_TASK			( 100UL )
#define mainVALUE_SENT_FROM_TIMER			( 200UL )

/*-----------------------------------------------------------*/

/*
 * The tasks as described in the comments at the top of this file.
 */
static void prvQueueReceiveTask( void *pvParameters );
static void prvQueueSendTask( void *pvParameters );

/*
 * The callback function executed when the software timer expires.
 */
static void prvQueueSendTimerCallback( TimerHandle_t xTimerHandle );

/*-----------------------------------------------------------*/

/* The queue used by both tasks. */
static QueueHandle_t xQueue = NULL;

/* A software timer that is started from the tick hook. */
static TimerHandle_t xTimer = NULL;

/*-----------------------------------------------------------*/

char lcdData[2][17] = { "                ",
					   "                " };
int charPos = 0;
int line = 0;

void lcdInit(void) {
	//hide cursor
	//printf("\e[?25l");

	charPos = 0;
	line = 0;
	for (int i = 0; i < 16; i++)
	{
		lcdData[0][i] = ' ';
		lcdData[1][i] = ' ';
	}
}

void lcdPrint(void) {
	printf("%s", "\033[2J\033[1;1H");
	//system("cls");
	printf("+----------------+\n|");
	printf(lcdData[0]);
	printf("|\n|");

	printf(lcdData[1]);
	printf("|\n");
	printf("+----------------+");
}

void lcdChar(char data) {

	if (charPos < 16) {
		lcdData[line][charPos] = data;
		charPos++;
	}
	lcdPrint();
}

void lcdStr(char data[]) {

	while (*data) {
		lcdChar(*data);
		data++;
	}

}

void lcdCommand(unsigned char cmd) {
	if ((cmd & 0xf0) == 0x80) {
		line = 0;
		charPos = cmd & 0x0f;
	}
	if ((cmd & 0xf0) == 0xC0) {
		line = 1;
		charPos = cmd & 0x0f;
	}
	if (cmd == 0x01) {
		lcdInit();

	}
}
/*-----------------------------------------------------------*/
struct xMsg { //queue
	char ucIDMsg;
	char ucDado[16];
} xMsg;

void vTime (void* param) {

	struct xMsg xtimeMsg;
	
	unsigned int count = 0;
	lcdInit();
	xtimeMsg.ucIDMsg = 0x80;

	for (;;) { 
		xtimeMsg.ucDado[0] =	(48 +	((count / 3600)/ 10)); //h
		xtimeMsg.ucDado[1] = 	(48 +	((count / 3600)% 10));		//h
		xtimeMsg.ucDado[2] =	(':');
		xtimeMsg.ucDado[3] =	(48 +	(((count / 60) % 60)/ 10));	//min
		xtimeMsg.ucDado[4] =	(48 +	(((count/60)%60)	% 10));	//min
		xtimeMsg.ucDado[5] =	(':');
		xtimeMsg.ucDado[6] =	(48 +	((count % 60) / 10));		//seg
		xtimeMsg.ucDado[7] =	(48 +	((count % 60 % 10)));		//seg
		xtimeMsg.ucDado[8] =	'\0';
		
		count++; 
		
		xQueueSend(xQueue, &xtimeMsg, (TickType_t)0);
		vTaskDelay(1000 / portTICK_RATE_MS);
	}
	//failsafe
}

void vWrite (void* param) {

	struct xMsg msg;

	msg.ucIDMsg = 0xC0;

	for (;;) {

		msg.ucDado[0] = 'E';
		msg.ucDado[1] = 'C';
		msg.ucDado[2] = 'O';
		msg.ucDado[3] = 'S';
		msg.ucDado[4] = '1';
		msg.ucDado[5] = '3';
		msg.ucDado[6] = '\0';
				
		xQueueSend(xQueue, &msg, (TickType_t)0);
		vTaskDelay(1000 / portTICK_RATE_MS);
	
	}
	//failsafe
}

void vVerify(void* param) {
	
	struct xMsg xReceive;
	lcdInit();
	if (xQueue != NULL) {
		for (;;) {
			if (xQueueReceive(xQueue, &(xReceive), (TickType_t)10) == pdPASS) {
				lcdCommand(xReceive.ucIDMsg);
				lcdStr(xReceive.ucDado);
				vTaskDelay(1000 / portTICK_RATE_MS);
			}
		}
	}
}


/*** SEE THE COMMENTS AT THE TOP OF THIS FILE ***/
void main_blinky( void )
{		
	const TickType_t xTimerPeriod = mainTIMER_SEND_FREQUENCY_MS;

	xQueue = xQueueCreate(10, sizeof(xMsg));
	
	if (xQueue != 0) {
		
		xTaskCreate(vTime,					/* The function that implements the task. */
			"Time", 						/* The text name assigned to the task - for debug only as it is not used by the kernel. */
			configMINIMAL_STACK_SIZE, 		/* The size of the stack to allocate to the task. */
			NULL, 							/* The parameter passed to the task - not used in this simple case. */
			57,								/* The priority assigned to the task. */
			NULL);							/* The task handle is not required, so NULL is passed. */

		xTaskCreate(vWrite,					/* The function that implements the task. */
			"Write", 						/* The text name assigned to the task - for debug only as it is not used by the kernel. */
			configMINIMAL_STACK_SIZE, 		/* The size of the stack to allocate to the task. */
			NULL, 							/* The parameter passed to the task - not used in this simple case. */
			57,								/* The priority assigned to the task. */
			NULL);		/* The task handle is not required, so NULL is passed. */

		xTaskCreate(vVerify,					/* The function that implements the task. */
			"Verify", 						/* The text name assigned to the task - for debug only as it is not used by the kernel. */
			configMINIMAL_STACK_SIZE, 		/* The size of the stack to allocate to the task. */
			NULL, 							/* The parameter passed to the task - not used in this simple case. */
			57,								/* The priority assigned to the task. */
			NULL);		/* The task handle is not required, so NULL is passed. */
	}
					

	
	/* Start the tasks and timer running. */
	vTaskStartScheduler();
	

	/* If all is well, the scheduler will now be running, and the following
	line will never be reached.  If the following line does execute, then
	there was insufficient FreeRTOS heap memory available for the idle and/or
	timer tasks	to be created.  See the memory management section on the
	FreeRTOS web site for more details. */
	for( ;; );
}
/*-----------------------------------------------------------*/

static void prvQueueSendTask( void *pvParameters )
{
TickType_t xNextWakeTime;
const TickType_t xBlockTime = mainTASK_SEND_FREQUENCY_MS;
const uint32_t ulValueToSend = mainVALUE_SENT_FROM_TASK;

	/* Prevent the compiler warning about the unused parameter. */
	( void ) pvParameters;

	/* Initialise xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, pdMS_TO_TICKS() was used to
		convert a time specified in milliseconds into a time specified in ticks.
		While in the Blocked state this task will not consume any CPU time. */
		vTaskDelayUntil( &xNextWakeTime, xBlockTime );

		/* Send to the queue - causing the queue receive task to unblock and
		write to the console.  0 is used as the block time so the send operation
		will not block - it shouldn't need to block as the queue should always
		have at least one space at this point in the code. */
		xQueueSend( xQueue, &ulValueToSend, 0U );
	}
}
/*-----------------------------------------------------------*/

static void prvQueueSendTimerCallback( TimerHandle_t xTimerHandle )
{
const uint32_t ulValueToSend = mainVALUE_SENT_FROM_TIMER;

	/* This is the software timer callback function.  The software timer has a
	period of two seconds and is reset each time a key is pressed.  This
	callback function will execute if the timer expires, which will only happen
	if a key is not pressed for two seconds. */

	/* Avoid compiler warnings resulting from the unused parameter. */
	( void ) xTimerHandle;

	/* Send to the queue - causing the queue receive task to unblock and
	write out a message.  This function is called from the timer/daemon task, so
	must not block.  Hence the block time is set to 0. */
	xQueueSend( xQueue, &ulValueToSend, 0U );
}
/*-----------------------------------------------------------*/

static void prvQueueReceiveTask( void *pvParameters )
{
uint32_t ulReceivedValue;

	/* Prevent the compiler warning about the unused parameter. */
	( void ) pvParameters;

	for( ;; )
	{
		/* Wait until something arrives in the queue - this task will block
		indefinitely provided INCLUDE_vTaskSuspend is set to 1 in
		FreeRTOSConfig.h.  It will not use any CPU time while it is in the
		Blocked state. */
		xQueueReceive( xQueue, &ulReceivedValue, portMAX_DELAY );

		/*  To get here something must have been received from the queue, but
		is it an expected value?  Normally calling printf() from a task is not
		a good idea.  Here there is lots of stack space and only one task is
		using console IO so it is ok.  However, note the comments at the top of
		this file about the risks of making Windows system calls (such as
		console output) from a FreeRTOS task. */
		if( ulReceivedValue == mainVALUE_SENT_FROM_TASK )
		{
			printf( "Message received from task\r\n" );
		}
		else if( ulReceivedValue == mainVALUE_SENT_FROM_TIMER )
		{
			printf( "Message received from software timer\r\n" );
		}
		else
		{
			printf( "Unexpected message\r\n" );
		}

		/* Reset the timer if a key has been pressed.  The timer will write
		mainVALUE_SENT_FROM_TIMER to the queue when it expires. */
		if( _kbhit() != 0 )
		{
			/* Remove the key from the input buffer. */
			( void ) _getch();

			/* Reset the software timer. */
			xTimerReset( xTimer, portMAX_DELAY );
		}
	}
}
/*-----------------------------------------------------------*/


