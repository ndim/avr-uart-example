#include <stdint.h>
#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart-ringbuf-global.h"


volatile uint8_t rb_buf[RB_SIZE];


uint8_t read_byte(void)
{
  const uint8_t next_rb_head = (rb_head+1) & RB_MASK;
  if (rb_head == rb_tail) {
    /* FIXME: Signal and/or handle the buffer underflow error condition */
    return 0xff;
  } else {
    rb_head = next_rb_head;
    const uint8_t value = rb_buf[rb_head];
    return value;
  }
}


#if 0

/*
 * Remarks on this C code:
 *  - Keep below inline asm ISR in sync with this C ISR.
 */
ISR(USART0_RX_vect)
{
  const uint8_t received_byte = UDR0;
  const uint8_t next_rb_tail = (rb_tail+1) & RB_MASK;
  if (next_rb_tail == rb_head) {
    /* FIXME: Signal and/or handle the buffer overflow error condition */
  } else {
    rb_buf[next_rb_tail] = received_byte;
    rb_tail = next_rb_tail;
  }
}

#else

/*
 * Remarks on the assembly code:
 *  - Naked ISR, i.e. we do everything in inline asm.
 *  - The above C ISR does the same work with more overhead.
 *  - Keep above C ISR in sync with this inline asm ISR.
 *  - We do not use __tmp_reg__ and __zero_reg__ in here (r0 and r1).
 *  - We rely on global register variables from uart-ringbuf-global.h
 *    which must be included in all C source files.
 */
ISR(USART0_RX_vect, ISR_NAKED)                 /* CLOCK CYCLES */
{
  asm("\n\t"                                   /* 5 ISR entry */
      "push  r24\n\t"                          /* 2 */
      "push  r25\n\t"                          /* 2 */
      "push  r30\n\t"                          /* 2 */
      "push  r31\n\t"                          /* 2 */
      "in    %r[sreg_save], __SREG__\n\t"      /* 1 */
      "\n\t"

      /* read byte from UART */
      "lds   r25, %M[uart_data]\n\t"           /* 2 */

      /* next_tail := (cur_tail + 1) & MASK; */
      "ldi   r24, 1\n\t"                       /* 1 */
      "add   r24, %r[tail]\n\t"                /* 1 */
      "andi  r24, %a[mask]\n\t"                /* 1 */

      /* if next_tail == cur_head */
      "cp    r24, %r[head]\n\t"                /* 1 */
      "breq  L_%=\n\t"                         /* 1/2 */

      /* rb_buf[next_tail] := byte */
      "mov   r30, r24\n\t"                     /* 1 */
      "ldi   r31, 0\n\t"                       /* 1 */
      "subi  r30, lo8(-(rb_buf))\n\t"          /* 1 */
      "sbci  r31, hi8(-(rb_buf))\n\t"          /* 1 */
      "st    Z, r25\n\t"                       /* 2 */

      /* rb_tail := next_tail */
      "mov   %r[tail], r24\n\t"                /* 1 */

      "\n"
"L_%=:\t"
      "out   __SREG__, %r[sreg_save]\n\t"      /* 1 */
      "pop   r31\n\t"                          /* 2 */
      "pop   r30\n\t"                          /* 2 */
      "pop   r25\n\t"                          /* 2 */
      "pop   r24\n\t"                          /* 2 */
      "reti\n\t"                               /* 5 ISR return */
      : /* output operands */
        [tail]      "+r"   (rb_tail)    /* both input+output */
      : /* input operands */
        [uart_data] "M"    (_SFR_MEM_ADDR(UDR0)),
        [mask]      "M"    (RB_MASK),
        [head]      "r"    (rb_head),
        [sreg_save] "r"    (rb_sreg_save)
        /* no clobbers */
      );
}

#endif


#define INIT_FUNCTION(SECTION, FUN_NAME)	\
  static void FUN_NAME(void)			\
       __attribute__ ((naked))			\
       __attribute__ ((used))			\
       __attribute__ ((section("." #SECTION))); \
  static void FUN_NAME(void)


INIT_FUNCTION(init5, uart_ringbuf_init)
{
  /* FIXME: IO pin setup */
}
