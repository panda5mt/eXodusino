/* Application does not use first 4k of flash as this is
   reserved for the bootloader. */

MEMORY
{
  /* Define each memory region */
  MFlash32 (rx) : ORIGIN = 0x1000, LENGTH = 0x7000 /* 28k */     
  RamLoc8 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x1FE0 /* 8k less 32 bytes used for IAP(LPC1114/301) */
  //RamLoc8 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x0FE0 /* 8k less 32 bytes used for IAP(LPC1114FN28/102) */
}
  /* Define a symbol for the top of each memory region */
  __top_MFlash32 = 0x1000 + 0x7000;
  __top_RamLoc8 = 0x10000000 + 0x1FE0; /* LPC1114/301 */
  //__top_RamLoc8 = 0x10000000 + 0x0FE0; /* LPC1114FN28/102 */
