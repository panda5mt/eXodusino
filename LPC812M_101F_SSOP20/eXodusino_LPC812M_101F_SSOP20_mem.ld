/*
 * GENERATED FILE - DO NOT EDIT
 * (C) Code Red Technologies Ltd, 2008-2013
 * Linker script memory definitions
 * Created from LinkMemoryTemplate
 * By LPCXpresso v5.1.0 [Build 2048] [2013-02-05]  on Wed Mar 27 01:18:53 JST 2013)
*/

MEMORY
{
  /* Define each memory region */
  MFlash16 (rx) : ORIGIN = 0x0, LENGTH = 0x4000 /* 16k */
  RamLoc4 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x1000 /* 4k */

}
  /* Define a symbol for the top of each memory region */
  __top_MFlash16 = 0x0 + 0x4000;
  __top_RamLoc4 = 0x10000000 + 0x1000;

