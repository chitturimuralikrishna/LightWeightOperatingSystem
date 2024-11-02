#ifndef CONFIG_H
#define CONFIG_H

#define LW_OS_TOTAL_INTRRUPTS 512 
#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10

// 100 MB heap size  
#define LW_OS_HEAP_SIZE_BYTES 104857600
#define LW_OS_HEAP_BLOCK_SIZE 4096
#define LW_OS_HEAP_ADDRESS 0x01000000
#define LW_OS_HEAP_TABLE_ADDRESS 0x00007E00
#endif