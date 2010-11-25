#include "StdAfx.h"
#include "DiskManager.h"
#include <direct.h>

DiskManager::DiskManager(void)
{
	//uMark = 0;
}

DiskManager::~DiskManager(void)
{
}

void DiskManager::UpdateStatus()
{
	ULONG uDriveMask = _getdrives();
	if (uDriveMask==uMark) return;
	listDisk.clear();
	uMark = uDriveMask;
	TCHAR g_szDrvMsg[] = _T("A:\\");
	int iDem = 0;
	ULONG unUsed;
	while (uDriveMask) 
	{
		if (uDriveMask & 1)
		{
			DiskInfo di;
			di.iID = iDem;
			di.iType = GetDriveType(g_szDrvMsg);
			wsprintf(di.sPath,_T("%s"),g_szDrvMsg);
			GetDiskFreeSpaceEx(g_szDrvMsg, (PULARGE_INTEGER)&di.uUsed, (PULARGE_INTEGER)&di.uTotal, (PULARGE_INTEGER)&di.uFree);
			GetVolumeInformation(g_szDrvMsg, di.sVolumeName, MAX_PATH, &di.uVoLumeSerial, &unUsed, &di.uFlag, di.sFileSystemName, MAX_PATH);
			di.uUsed = di.uTotal - di.uFree;
			listDisk.push_back(di);
		}
		iDem++;
		++g_szDrvMsg[0];
		uDriveMask >>= 1;
	}
}

void DiskManager::FormatDriveType(UINT type, TCHAR swDest[])
{
	const struct {
		UINT type;
		LPCTSTR name;
	} TypeNames[] = {
		{ DRIVE_UNKNOWN, _T("DRIVE_UNKNOWN") },
		{ DRIVE_NO_ROOT_DIR, _T("DRIVE_NO_ROOT_DIR") },
		{ DRIVE_REMOVABLE, _T("DRIVE_REMOVABLE") },
		{ DRIVE_FIXED, _T("DRIVE_FIXED") },
		{ DRIVE_REMOTE, _T("DRIVE_REMOTE") },
		{ DRIVE_CDROM, _T("DRIVE_CDROM") },
		{ DRIVE_RAMDISK, _T("DRIVE_RAMDISK") },
		{ 0, NULL },
	};
	for (int i=0; TypeNames[i].name; i++) 
		if (type==TypeNames[i].type)
		{
			_stprintf(swDest,_T("%s"), TypeNames[i].name);
			return;
		}
}

DiskInfo & DiskManager::GetDiskInfo(int iIndex)
{
	if (iIndex<=listDisk.size()) return listDisk[iIndex];
}

int DiskManager::GetNumDisk()
{
	return listDisk.size();
}