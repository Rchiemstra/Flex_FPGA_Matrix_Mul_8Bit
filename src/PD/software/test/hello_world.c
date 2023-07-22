#include <stdio.h>
#include <stdint.h>
#include <system.h>
#include "alt_types.h"
#include "sys/alt_irq.h"

//*(uint32_t *)(REG32_NEW_COMPONENT_0_BASE) = number;
//REG32_NEW_COMPONENT_1_BASE

//uint8_t

int main()
{
  printf("Hello from Nios II!\n");




  *(uint32_t *)(MATRIXMULTIPLIER_8BIT_COMPONENT_0_BASE)   = 0x01020301;
  *(uint32_t *)(MATRIXMULTIPLIER_8BIT_COMPONENT_0_BASE+4) = 0x02030102;
  *(uint32_t *)(MATRIXMULTIPLIER_8BIT_COMPONENT_0_BASE+8) = 0x03000000;

  printf("%x\n",*(uint32_t *)(MATRIXMULTIPLIER_8BIT_COMPONENT_0_BASE));
  printf("%x\n",*(uint32_t *)(MATRIXMULTIPLIER_8BIT_COMPONENT_0_BASE+4));
  printf("%x\n",*(uint32_t *)(MATRIXMULTIPLIER_8BIT_COMPONENT_0_BASE+8));


  *(uint32_t *)(MATRIXMULTIPLIER_8BIT_COMPONENT_0_BASE+12) = 0x02000000;
  *(uint32_t *)(MATRIXMULTIPLIER_8BIT_COMPONENT_0_BASE+16) = 0x02000000;
  *(uint32_t *)(MATRIXMULTIPLIER_8BIT_COMPONENT_0_BASE+20) = 0x02000000;

  printf("%x\n",*(uint32_t *)(MATRIXMULTIPLIER_8BIT_COMPONENT_0_BASE+12));
  printf("%x\n",*(uint32_t *)(MATRIXMULTIPLIER_8BIT_COMPONENT_0_BASE+16));
  printf("%x\n",*(uint32_t *)(MATRIXMULTIPLIER_8BIT_COMPONENT_0_BASE+20));



  while(1){

	  printf("%x\n",*(uint32_t *)(MATRIXMULTIPLIER_8BIT_COMPONENT_0_BASE+24));
	  printf("%x\n",*(uint32_t *)(MATRIXMULTIPLIER_8BIT_COMPONENT_0_BASE+28));
	  printf("%x\n",*(uint32_t *)(MATRIXMULTIPLIER_8BIT_COMPONENT_0_BASE+32));

  }


  return 0;
}
