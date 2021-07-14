#include "fileio.h"

VOID ReadFile(PCWSTR path, PVOID buffer, ULONG len, INT offset) {
	UNICODE_STRING uniName;
	OBJECT_ATTRIBUTES objAttr;

	RtlInitUnicodeString(&uniName, path);
	InitializeObjectAttributes(&objAttr, &uniName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	HANDLE handle;
	NTSTATUS status;
	IO_STATUS_BLOCK ioStatusBlock;

	if (KeGetCurrentIrql() != PASSIVE_LEVEL)
		return;

	status = ZwCreateFile(&handle, GENERIC_READ, &objAttr, &ioStatusBlock, NULL, FILE_ATTRIBUTE_NORMAL, 0, FILE_OPEN, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);
	LARGE_INTEGER      byteOffset;

	if (((NTSTATUS)(status)) >= 0) {
		byteOffset.LowPart = byteOffset.HighPart = offset;
		//try to read the file
		status = ZwReadFile(handle, NULL, NULL, NULL, &ioStatusBlock, buffer, len, &byteOffset, NULL);
		ZwClose(handle);
	}
}