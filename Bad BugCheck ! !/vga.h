#ifndef VGA_H
#define VGA_H

#include <wdm.h>

struct X86_BIOS_REGISTERS {
    ULONG Eax;
    ULONG Ecx;
    ULONG Edx;
    ULONG Ebx;
    ULONG Ebp;
    ULONG Esi;
    ULONG Edi;
    USHORT SegDs;
    USHORT SegEs;
};

NTKERNELAPI BOOLEAN x86BiosCall(ULONG InterruptNumber, struct X86_BIOS_REGISTERS* pRegisters);
NTSTATUS VgaGetMode(ULONG* pMode);
NTSTATUS VgaSetMode(ULONG Mode);


#endif // !VGA_H
