/*
 * GENERATED FILE - DO NOT EDIT
 * (C) Code Red Technologies Ltd, 2008-2013
 * Linker script memory definitions
 * Created from LinkMemoryTemplate
 * By LPCXpresso v5.1.0 [Build 2048] [2013-02-05]  on Sat Apr 20 14:34:55 JST 2013)
*/

MEMORY
{
  /* Define each memory region */
  MFlash32 (rx) : ORIGIN = 0x1000, LENGTH = 0x7000 /* 32k */
  RamLoc8 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x1FE0 /* 8k */

}
  /* Define a symbol for the top of each memory region */
  __top_MFlash32 = 0x1000 + 0x7000;
  __top_RamLoc8 = 0x10000000 + 0x1FE0;

