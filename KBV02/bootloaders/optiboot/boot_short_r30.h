/*
 * Modified to use "out" for SPM access
 * Peter Knight, Optiboot project http://optiboot.googlecode.com
 *
 * "_short" routines execute 1 cycle faster and use 1 less word of flash
 * by using "out" instruction instead of "sts".
 *
 * modified the _short (not extended) calls to take the address argument
 * as global variable in Z (r30/31); the caller must manage RAMPZ for the
 * extended versions herself - smr
 */

#ifndef BOOT_SHORT_H
#define BOOT_SHORT_H

#include <avr/boot.h>

#define __boot_page_fill_short_r30(address, data)    \
(__extension__({                                 \
    __asm__ __volatile__                         \
    (                                            \
        "movw  r0, %3\n\t"                       \
        "out %0, %1\n\t"                         \
        "spm\n\t"                                \
        "clr  r1\n\t"                            \
        :                                        \
        : "i" (_SFR_IO_ADDR(__SPM_REG)),         \
          "r" ((uint8_t)__BOOT_PAGE_FILL),       \
          "r" ((uint16_t)address),               \
          "r" ((uint16_t)data)                   \
        : "r0"                                   \
    );                                           \
}))


#define __boot_page_erase_short_r30(address)         \
(__extension__({                                 \
    __asm__ __volatile__                         \
    (                                            \
        "out %0, %1\n\t"                         \
        "spm\n\t"                                \
        :                                        \
        : "i" (_SFR_IO_ADDR(__SPM_REG)),         \
          "r" ((uint8_t)__BOOT_PAGE_ERASE),      \
          "r" ((uint16_t)address)                \
    );                                           \
}))


#define __boot_page_write_short_r30(address)         \
(__extension__({                                 \
    __asm__ __volatile__                         \
    (                                            \
        "out %0, %1\n\t"                         \
        "spm\n\t"                                \
        :                                        \
        : "i" (_SFR_IO_ADDR(__SPM_REG)),         \
          "r" ((uint8_t)__BOOT_PAGE_WRITE),      \
          "r" ((uint16_t)address)                \
    );                                           \
}))


#define __boot_rww_enable_short_r30()                \
(__extension__({                                 \
    __asm__ __volatile__                         \
    (                                            \
        "out %0, %1\n\t"                         \
        "spm\n\t"                                \
        :                                        \
        : "i" (_SFR_IO_ADDR(__SPM_REG)),         \
          "r" ((uint8_t)__BOOT_RWW_ENABLE)       \
    );                                           \
}))


#endif // BOOT_SHORT_R30_H
