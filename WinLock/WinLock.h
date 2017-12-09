/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		WinLock.h
* @brief	This Program is WinLock DLL Project.
* @author	Alopex/Helium
* @version	v1.10a
* @date		2017-12-8	v1.00a	alopex	Create Project
* @date		2017-12-9	v1.10a	alopex	Code Do Not Rely On MSVCR Library
*/
#pragma once

#ifndef __WINLOCK_H_
#define __WINLOCK_H_

//Include Windows Header File
#include <Windows.h>

//Include C/C++ Running Header File
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <mmreg.h>
#include <wchar.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>

//Macro Definition
#ifdef WINLOCK_EXPORTS
#define WINLOCK_API	__declspec(dllexport)
#else
#define WINLOCK_API	__declspec(dllimport)
#endif

//Class Definition
//CriticalLock类(临界区)(外部临界区)
class WINLOCK_API CWinCriticalLock
{
private:
	CRITICAL_SECTION* m_pCriticalSection;

public:
	inline CWinCriticalLock(CRITICAL_SECTION* pCriticalSection);	//构造
	inline ~CWinCriticalLock();										//析构
};

//CriticalLockEx类(临界区)(内部临界区)
class WINLOCK_API CWinCriticalLockEx
{
private:
	CRITICAL_SECTION m_CriticalSection;

public:
	inline CWinCriticalLockEx();									//构造
	inline ~CWinCriticalLockEx();									//析构
};

//MutexLock类(互斥对象)(外部互斥体)
class WINLOCK_API CWinMutexLock
{
private:
	HANDLE* m_pMutex;

public:
	inline CWinMutexLock(HANDLE* pMutex);							//构造
	inline ~CWinMutexLock();										//析构
	inline void Lock() const;
	inline void Unlock() const;
};

//MutexLockEx类(互斥对象)(内部互斥体)
class WINLOCK_API CWinMutexLockEx
{
private:
	HANDLE m_Mutex;

public:
	inline CWinMutexLockEx();										//构造
	inline ~CWinMutexLockEx();										//析构
	inline void Lock() const;
	inline void Unlock() const;
};

#endif