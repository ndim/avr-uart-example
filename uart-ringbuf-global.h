#ifndef UART_RINGBUF_GLOBAL_H
#define UART_RINGBUF_GLOBAL_H

#include <stdint.h>

#define RB_WIDTH 5
#define RB_SIZE (1<<(RB_WIDTH))
#define RB_MASK ((RB_SIZE)-1)

extern volatile uint8_t rb_buf[RB_SIZE];

register uint8_t rb_head asm("r13");
register uint8_t rb_tail asm("r14");

register uint8_t rb_sreg_save asm("r15");

#endif /* UART_RINGBUF_GLOBAL_H */
