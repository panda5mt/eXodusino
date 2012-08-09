/*
 * GENERATED FILE - DO NOT EDIT
 * (C) Code Red Technologies Ltd, 2008-2012
 * Linker script memory definitions
 * Created from LinkMemoryTemplate
 * By LPCXpresso v4.2.4 [Build 267] [2012-07-11]  on Fri Jul 13 01:18:22 JST 2012)
*/

MEMORY
{
  /* Define each memory region */
  MFlash32 (rx) : ORIGIN = 0x0000, LENGTH = 0x8000 /* 32k */
  RamLoc8 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x2000 /* 8k */

}
  /* Define a symbol for the top of each memory region */
  __top_MFlash32 = 0x0000 + 0x8000;
  __top_RamLoc8 = 0x10000000 + 0x2000;



