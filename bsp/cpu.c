/*==============================================================================
** utils.S -- some assemble tool routines
**
** MODIFY HISTORY:
**
** 2016-10-27 wdf Create.
==============================================================================*/
#include "../config.h"
#include "../types.h"
#include "../dlist.h"
#include "../task.h"
#include <xm.h>

/*=======================================================
 * OS defined variables
**=====================================================*/
extern OS_TCB *G_p_current_tcb;
extern OS_TCB **G_pp_highest_tcb;

/*==============================================================================
 * - CPU_LOCK()
 *
 * - Disable Irqs
 */
int CPU_LOCK()
{
    xm_s32_t cpsr_c = XM_are_irqs_enabled();
    XM_disable_irqs();
    return cpsr_c;
}

/*==============================================================================
 * - CPU_UNLOCK()
 *
 * - Enable Irqs
 */
void CPU_UNLOCK(int cpsr_c)
{
    if (cpsr_c) {
        XM_enable_irqs();
    }
}

/*==============================================================================
 * - CPU_REBOOT()
 *
 * - Reboot this partition
 */
void CPU_REBOOT()
{
    XM_reset_partition(XM_PARTITION_SELF, XM_HM_AC_COLD_RESET, 0);
}

/*==============================================================================
 * - CPU_STACK_INIT()
 *
 * - Init XAL stack, [stk] just like %esp
 */
int CPU_STACK_INIT(int entry, int arg, int *stk)
{
    *--stk = arg; /* arg */
    *--stk = 0x0; /* stack frame */

    *--stk = 0x00000000; /* EFLAG */
    *--stk = ((1<<3)|1); /* CS */
    *--stk = entry;      /* EIP */
    *--stk = (0x100001); /* iFlags */

    *--stk = ((2<<3)|1); /* SS */
    *--stk = ((2<<3)|1); /* GS */
    *--stk = ((2<<3)|1); /* FS */
    *--stk = ((2<<3)|1); /* ES */
    *--stk = ((2<<3)|1); /* DS */
    *--stk = 0xeaeaeaea; /* EAX */
    *--stk = 0x00000000; /* EBP */
    *--stk = 0xe1e1e1e1; /* EDI */
    *--stk = 0xe4e4e4e4; /* ESI */
    *--stk = 0xedededed; /* EDX */
    *--stk = 0xecececec; /* ECX */
    *--stk = 0xebebebeb; /* EBX */

    return (int)stk;
}

/*==============================================================================
 * - XAL_OSTaskSwitch()
 *
 * - XAL or OS called at switch task
 */
uint32 XAL_OSTaskSwitch (uint32 sp)
{
    G_p_current_tcb->sp = sp; /* save sp */

    if (*G_pp_highest_tcb != NULL) {
        G_p_current_tcb = *G_pp_highest_tcb; /* get new task */
    }

    return G_p_current_tcb->sp; /* ret new task sp */
}


/*=======================================================
 * Heap, Stack memory
**=====================================================*/
int _HeapMemory[1*MB];
int _StakMemory[1*MB];

/*==============================================================================
** FILE END
==============================================================================*/

