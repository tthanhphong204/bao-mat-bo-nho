#include "types.h"
#include "param.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"

static struct spinlock rand_lock;
static uint64 rand_state;

void
randinit(void)
{
  initlock(&rand_lock, "rand");
  rand_state = r_time() ^ 0x9E3779B97F4A7C15ULL;
  if (rand_state == 0)
    rand_state = 88172645463325252ULL;
}

uint64
kernel_rand(void)
{
  uint64 x;
  acquire(&rand_lock);
  x = rand_state;
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  rand_state = x;
  release(&rand_lock);
  return x;
}