#include "vga.h"

NTSTATUS VgaGetMode(ULONG* pMode) {
    BOOLEAN b;
    NTSTATUS Status;
    struct X86_BIOS_REGISTERS Registers;

    memset(&Registers, 0, sizeof(Registers));

    Registers.Eax = 0x4F03;

    b = x86BiosCall(0x10, &Registers);

    if ((b) && (Registers.Eax == 0x4F)) {
        *pMode = Registers.Ebx;
        Status = STATUS_SUCCESS;
    }
    else Status = STATUS_UNSUCCESSFUL;

    return Status;
}

NTSTATUS VgaSetMode(ULONG Mode) {
    BOOLEAN b;
    NTSTATUS Status;
    struct X86_BIOS_REGISTERS Registers;

    memset(&Registers, 0, sizeof(Registers));

    Registers.Eax = 0x4F02;
    Registers.Ebx = 0x4000 | Mode;

    b = x86BiosCall(0x10, &Registers);

    if ((b) && (Registers.Eax == 0x4F)) {
        Status = STATUS_SUCCESS;
    }
    else Status = STATUS_UNSUCCESSFUL;

    return Status;
}
