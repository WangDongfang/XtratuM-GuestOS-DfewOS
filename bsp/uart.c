/*==============================================================================
** uart.c -- XtratuM GuestOS uart driver.
**
** MODIFY HISTORY:
**
** 2016-10-27 wdf Create.
==============================================================================*/
#include "../config.h"
#include "../types.h"
#include "../dlist.h"
#include "../task.h"
#include "../delayQ.h"
#include <xm.h>

/*==============================================================================
 * - uart_init()
 *
 * - init UART hardware
 */
int uart_init()
{
    return 0;
}

/*==============================================================================
 * - uart_putc()
 *
 * - use UART send a char
 */
int uart_putc (char c)
{
    XM_write_console(&c, 1);

    /* If \n, also do \r */
    if (c == '\n')
        uart_putc('\r');

    return 1;
}

/*==============================================================================
 * - uart_tstc()
 *
 * - check whether have received char in FIFO
 */
int uart_tstc(void)
{
    return XM_seek_console(0, 0);
}

/*==============================================================================
 * - uart_getc()
 *
 * - use UART receive a char
 */
int uart_getc ()
{
    char c;

    while (uart_tstc() == 0) {
        delayQ_delay(1); /* wait for recv char */
    }
    XM_read_console(&c, 20);

    return c;
}

/*==============================================================================
 * - uart_pend()
 *
 * - wait some ticks for receive data
 */
int uart_pend (int ticks)
{
    while (ticks--) {
        if (uart_tstc()) {
            return 1;
        }
        delayQ_delay(1);
    }
    return uart_tstc();
}

/*==============================================================================
** FILE END
==============================================================================*/

