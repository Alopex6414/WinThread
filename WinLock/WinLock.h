/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		WinLock.h
* @brief	This Program is WinLock DLL Project.
* @author	Alopex/Helium
* @version	v1.11a
* @date		2017-12-8	v1.00a	alopex	Create Project.
* @date		2017-12-9	v1.10a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2017-1-4	v1.11a	alopex	Cancel inline.
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
//CriticalLock��(�ٽ���)(�ⲿ�ٽ���)
class WINLOCK_API CWinCriticalLock
{
private:
	CRITICAL_SECTION* m_pCriticalSection;

public:
	CWinCriticalLock(CRITICAL_SECTION* pCriticalSection);			//����
	~CWinCriticalLock();											//����
};

//CriticalLockEx��(�ٽ���)(�ڲ��ٽ���)
class WINLOCK_API CWinCriticalLockEx
{
private:
	CRITICAL_SECTION m_CriticalSection;

public:
	CWinCriticalLockEx();											//����
	~CWinCriticalLockEx();											//����
};

//MutexLock��(�������)(�ⲿ������)
class WINLOCK_API CWinMutexLock
{
private:
	HANDLE* m_pMutex;

public:
	CWinMutexLock(HANDLE* pMutex);									//����
	~CWinMutexLock();												//����
	void Lock() const;
	void Unlock() const;
};

//MutexLockEx��(�������)(�ڲ�������)
class WINLOCK_API CWinMutexLockEx
{
private:
	HANDLE m_Mutex;

public:
	CWinMutexLockEx();												//����
	~CWinMutexLockEx();												//����
	void Lock() const;
	void Unlock() const;
};

#endif