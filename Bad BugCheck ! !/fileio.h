#ifndef  FILEIO_H
#define	 FILEIO_H

#include <wdm.h>

VOID ReadFile(PCWSTR path, PVOID buffer, ULONG len, INT offset);

#endif // ! FILEIO_H