AVR UART example inspired by https://electronics.stackexchange.com/questions/188238/avr-how-optimize-cycle-counted-isr-to-portable-code-using-inline-asm/
=========================================================================================================================================================

The goal is to implement a ring buffer for receiving bytes from the
UART, where the ISR receiving the byte and storing it in the ring
buffer runs as quickly as possible.

To help with that, the ISR uses some global register variables
implemented by adding `-ffixed-rNN` to `CFLAG` for all compilation
units and declaring the respective variables as

    register uint8_t foo asm("rNN");

This removes the `rNN` register from the pool of registers available
to the compiler's register allocator. To check this, see the sets of
registers used by `main_event_loop()` function from `main.c` and
`unrelated_event_loop()` from `unrelated-sources.c`.

The general code structure is as follows:

  * `main.c`

    The main loop.

  * `uart-ringbuf.c`

    The implementation of the ring buffer including the UART ISR.

  * `uart-ringbuf-global.h`

    The API definition of the ring buffer for the main event loop's use.

  * `unrelated-sources.c`

     Sources unrelated to the ring buffer which should not use the
     registers globally reserved for the ring buffer's global
     variables.

Tools used:

  * avr-binutils
  * avr-gcc
  * GNU awk
  * GNU make
