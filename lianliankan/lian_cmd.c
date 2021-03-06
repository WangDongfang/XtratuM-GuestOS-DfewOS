/*==============================================================================
** lian_cmd.c -- lian command to Dfew OS
**
** MODIFY HISTORY:
**
** 2011-10-13 wdf Create.
==============================================================================*/
#include "../cmd.h"

/*======================================================================
  declare lian module main function
======================================================================*/
int lian_main(int argc, char **argv);

/*======================================================================
  "lian" command information struct
======================================================================*/
static CMD_INF _G_lian_cmd = {"lian", "lianliankan game", lian_main};

/*==============================================================================
 * - lian_cmd_init()
 *
 * - intstall "lian" command
 */
void lian_cmd_init()
{
    cmd_add(&_G_lian_cmd);
}

/*==============================================================================
** FILE END
==============================================================================*/

