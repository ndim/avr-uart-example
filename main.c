#include "uart-ringbuf-global.h"

/* This code is using lots of registers and is including
 * <uart-ringbuf-global.h> because we want to see which registers are
 * used by the generated code.
 */


/* The blubb_in and blubb_out variables are just to convince the
 * compiler that all the stupid calculations are actually necessary
 * and thus does not optimize it out. We do want to see all registers
 * being used in the code which the compiler thinks it can use.
 */
static volatile uint8_t blubb_in;
static volatile uint8_t blubb_out;


inline static
void main_event_loop(void)
  __attribute__ ((noreturn));
inline static
void main_event_loop(void)
{
  /* enough variables to exhaused the 32 registers on the AVR */
  uint8_t a=1, b=2, c=1, d=7, e=9, f=1, g=2, h=1;
  uint8_t i=3, j=3, k=6, l=3, m=1, n=1, o=2, p=2;
  uint8_t q=2, r=6, s=9, t=2, u=8, v=2, w=6, x=6;
  uint8_t A=1, B=2, C=3, D=4, E=5, F=8, G=9, H=7;

  /* Exercise all 32 registers and then some. This allows you to check
     that the emitted code is not using registers from
     uart-ringbuf-global.h it should not use. */
  while (1) {
    a += blubb_in + b;
    b += c;
    c += d;
    d += e;
    e += f;
    f += g;
    g += h;
    h += i;
    i += j;
    j += k;
    k += l;
    l += m;
    m += n;
    n += o;
    o += p;
    p += q;
    q += r;
    r += s;
    s += t;
    t += u;
    u += v;
    v += w;
    w += x;
    x += A;
    A += B;
    B += C;
    C += D;
    D += E;
    E += F;
    F += G;
    G += H;
    H += a;
    blubb_out = x;
  }
}


int main(void)
{
  main_event_loop();
} /* int main(void) */
