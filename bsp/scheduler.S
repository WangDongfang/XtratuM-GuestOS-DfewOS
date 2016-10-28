/*==============================================================================
** scheduler.S -- task scheduler routines.
**
** MODIFY HISTORY:
**
** 2016-10-27 wdf Create.
==============================================================================*/

/********************************************************************
*
*  after push the context frame in stack, the SP store in TCB
*
*           |  ....  |              [HIGH ADDRESS]
*           |  ....  |
*  SP --->  |  ....  |  before push the context in stack
*-----------------------------------
*           | EFLAGS |  \
*           ----------   |
*           |   CS   |   |
*           ----------   |
*           |   EIP  |   |
*           ----------   |
*           | iFlags |   |
*          ------------  |---> a context frame in task stack
*           |   SS   |   |
*           ----------   |
*           |   ..   |   |
*           |   ..   |   |
*           |   ..   |   |
*           ----------   |
*  SP --->  |   EBX  |  /
*           ----------
*           |        |
*           |        |
*           |        |              [LOW ADDRESS]
*
*********************************************************************/


#define FUNC_DEF(func)  \
        .type   func, %function;  \
func:

#define FUNC_END(func)    \
        .size   func, . - func

/*======================================================= 
 * SAVE_REGS (12 + 4)
**=====================================================*/
.macro  SAVE_REGS
    PUSHF               /* EFLAGS */
    PUSHL   %CS
    PUSHL   $archResumePc /* EIP */
    PUSHL   $0    /* FAKE iFlags, Next will be changed */

    PUSHL   %SS
    PUSHL   %GS
    PUSHL   %FS
    PUSHL   %ES
    PUSHL   %DS
    PUSHL   %EAX
    PUSHL   %EBP
    PUSHL   %EDI
    PUSHL   %ESI
    PUSHL   %EDX
    PUSHL   %ECX
    PUSHL   %EBX
.endm
/*======================================================= 
 * RESTORE_REGS (12 + 4)
**=====================================================*/
.macro  RESTORE_REGS
    POPL    %EBX
    POPL    %ECX
    POPL    %EDX
    POPL    %ESI
    POPL    %EDI
    POPL    %EBP
    POPL    %EAX
    POPL    %DS
    POPL    %ES
    POPL    %FS
    POPL    %GS
    POPL    %SS

    /* 
     * ���� iFlags �� partitionControlTable_t 
     * Ȼ��ִ�� IRET ָ��� EIP CS EFLAGS
     */
    jmp XM_iret
.endm

/*======================================================= 
 * archResumePc()
**=====================================================*/
FUNC_DEF(archResumePc)
    RET
FUNC_END(archResumePc)


.text
        /* DfewOS �������� */
        .extern G_readyQ
        .extern G_p_current_tcb

        /* XAL_OS �������� */
        .extern XAL_OSTaskSwitch

        /* Partition �������� */
        .extern Get_iFlags

        /* ���ļ��������� */
        .global LOAD_HIGHEST_TASK
        .global CONTEXT_SWITCH

/*======================================================= 
 * LOAD_HIGHEST_TASK()
**=====================================================*/
FUNC_DEF(LOAD_HIGHEST_TASK)
    MOVL $G_readyQ, %EDI
    MOVL 0(%EDI), %EAX
    MOVL 8(%EAX), %ESP

    MOVL $G_p_current_tcb, %ESI
    MOVL %EAX, 0(%ESI)

    RESTORE_REGS
FUNC_END(LOAD_HIGHEST_TASK)

/*======================================================= 
 * CONTEXT_SWITCH()
**=====================================================*/
FUNC_DEF(CONTEXT_SWITCH)
    SAVE_REGS

    call Get_iFlags /* ��ȡ�жϱ�־ */
    MOVL %EAX, 48(%ESP) /* iFlags ֵ�� ��ջ */

    PUSHL %esp
    call XAL_OSTaskSwitch
    ADDL  $4 , %esp
    MOVL %eax, %esp

    RESTORE_REGS
FUNC_END(CONTEXT_SWITCH)

.end

/*==============================================================================
** FILE END
==============================================================================*/