#pragma once

#include <cstddef>
#include <stdint.h>

/* CMSIS compiler specific defines */
#ifndef   __ASM
  #define __ASM                                  __asm
#endif
#ifndef   __STATIC_FORCEINLINE                 
  #define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
#endif        

/**
  \brief   Enable IRQ Interrupts
  \details Enables IRQ interrupts by clearing the I-bit in the CPSR.
           Can only be executed in Privileged modes.
 */
__STATIC_FORCEINLINE void __enable_irq(void)
{
  __ASM volatile ("cpsie i" : : : "memory");
}


/**
  \brief   Disable IRQ Interrupts
  \details Disables IRQ interrupts by setting the I-bit in the CPSR.
           Can only be executed in Privileged modes.
 */
__STATIC_FORCEINLINE void __disable_irq(void)
{
  __ASM volatile ("cpsid i" : : : "memory");
}


#define interrupts()        __enable_irq()
#define noInterrupts()      __disable_irq()

// Template which will evaluate at *compile time* to a single 32b number
// with the specified bits set.
template <size_t N>
constexpr uint32_t __bitset(const int (&a)[N], size_t i = 0U) {
    return i < N ? (1L << a[i]) | __bitset(a, i + 1) : 0;
}