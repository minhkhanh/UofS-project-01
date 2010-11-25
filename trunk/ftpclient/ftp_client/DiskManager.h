#pragma once
#ifndef vector
#include <vector>
using namespace std;
#endif
#ifndef _STRUCT_DI
#define _STRUCT_DI
struct DiskInfo
{
	int iID;
	int iType;
	ULONG uFlag;
	ULONG uVoLumeSerial;
	__int64 uUsed;
	__int64 uFree;
	__int64 uTotal;
	TCHAR sPath[MAX_PATH];
	TCHAR sVolumeName[MAX_PATH];
	TCHAR sFileSystemName[MAX_PATH];
};
#endif
class DiskManager
{
protected:
	vector<DiskInfo> listDisk;
	ULONG uMark;
public:
	DiskManager(void);
	virtual ~DiskManager(void);
	void UpdateStatus();
	DiskInfo &GetDiskInfo(int iIndex);
	int GetNumDisk();
	static void FormatDriveType(UINT type, TCHAR swDest[]);	
};