/*==============================================================================
** tetris_cmd.c -- tetris command to Dfew OS
**
** MODIFY HISTORY:
**
** 2011-09-29 wdf Create.
==============================================================================*/
#include "../cmd.h"

/*======================================================================
  declare tetris module main function
======================================================================*/
int tetris_main(int argc, char **argv);

/*======================================================================
  "tetris" command information struct
======================================================================*/
static CMD_INF _G_tetris_cmd = {"tetris", "tetris game", tetris_main};

/*==============================================================================
 * - tetris_cmd_init()
 *
 * - intstall "tetris" command
 */
void tetris_cmd_init()
{
    cmd_add(&_G_tetris_cmd);
}

/*==============================================================================
** FILE END
==============================================================================*/

