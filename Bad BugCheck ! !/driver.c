#define _NO_CRT_STDIO_INLINE
#include <wdm.h>
#include <ntddk.h>
#include <ntstrsafe.h>
#include "bootvid.h"
#include "vga.h"
#include "fileio.h"

#define DELAY_ONE_MICROSECOND 	(-10)
#define DELAY_ONE_MILLISECOND	(DELAY_ONE_MICROSECOND*1000)
#define DELAY_SECOND (DELAY_ONE_MILLISECOND * 1000)


void DriverUnload(PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
}

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject) {
    
	ULONG Mode;
	NTSTATUS Status;
	LARGE_INTEGER Interval;
	Status = VgaGetMode(&Mode);

	if (((NTSTATUS)(Status)) >= 0) {
		VidInitialize(TRUE);
		VidResetDisplay(TRUE);
		VidSolidColorFill(0, 0, 639, 479, BV_COLOR_RED);
		VidSetTextColor(BV_COLOR_WHITE);
		unsigned char* rawData;
		WCHAR string[256];
		for (INT i = 0; i < 4367; i++) {
			rawData = ExAllocatePoolZero(NonPagedPool, 153718, 'SEX2');
			RtlStringCbPrintfExW(string, 256, NULL, NULL, STRSAFE_NO_TRUNCATION, L"\\DosDevices\\C:\\out_bootvid\\%d.bmp", i);
			ReadFile(string, rawData, 153718, 0);
			VidBitBlt(&rawData[0xe], 0, 0);
			ExFreePool(rawData);
			Interval.QuadPart = DELAY_ONE_MILLISECOND;
			KeDelayExecutionThread(KernelMode, FALSE, &Interval);
		}
		Interval.QuadPart = DELAY_SECOND * 2;
		KeDelayExecutionThread(KernelMode, FALSE, &Interval);
		VgaSetMode(Mode);
		KeBugCheckEx(0xbadadd7e, NULL, NULL, NULL, NULL);
	}

	DriverObject->DriverUnload = DriverUnload;
    return STATUS_SUCCESS;
}