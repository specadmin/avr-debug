//-----------------------------------------------------------------------------
#include "debug.h"
#include "RAM_guard.h"
#ifdef RAM_GUARD_ENABLED
//-----------------------------------------------------------------------------
void init()
{
    // prefill whole the RAM with a magic 0xFE
    for(volatile register BYTE* ptr = (BYTE*)RAMSTART; ptr < (BYTE*)RAMEND; ptr++)
    {
        *ptr = 0xFE;
    }
}
//-----------------------------------------------------------------------------
void memory_usage()
{
    extern int __data_start;
    extern int __data_end;
    extern int __bss_start;
    extern int __bss_end;
    extern int __heap_start;
    extern void* __brkval;

    DSTR("============");
    DSTR(" RAM USAGE");
    DSTR("============");

    // .data section size
    WORD data = (WORD) &__data_end - (WORD) &__data_start;
    DVAR(data);

    // .bss section size
    WORD bss = (WORD) &__bss_end - (WORD) &__bss_start;
    DVAR(bss);

    // heap size
    WORD heap = 0;
    if(__brkval)
    {
        heap = (WORD)__brkval - (WORD)&__heap_start;
    }
    DVAR(heap);

    // stack depth
    DWORD tracker = 0;
    BYTE found = false;
    volatile register BYTE* ptr = (BYTE*)RAMEND;
    while(ptr-- > (BYTE*)RAMSTART)
    {
        tracker = (tracker << 8) | *ptr;
        if(tracker == 0xFEFEFEFE)
        {
            found = true;
            break;
        }
    }
    WORD stack = 0;
    if(found)
    {
        stack = RAMEND - (WORD) ptr - sizeof(tracker);
        DVAR(stack);
    }
    else
    {
        DSTR("Stack bottom not found");
    }

    DSTR("------------");

    // total RAM used
    WORD total = data + bss + heap + stack;
    DVAR(total);

    // free RAM
    WORD free = RAMEND - RAMSTART - total;
    DVAR(free);
}
//-----------------------------------------------------------------------------
#endif
