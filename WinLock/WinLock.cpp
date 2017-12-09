/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		WinLock.cpp
* @brief	This Program is WinLock DLL Project.
* @author	Alopex/Helium
* @version	v1.10a
* @date		2017-12-8	v1.00a	alopex	Create Project
* @date		2017-12-9	v1.10a	alopex	Code Do Not Rely On MSVCR Library
*/
#include "WinLock.h"

//------------------------------------------------------------------
// @Function:	 CWinCriticalLock()
// @Purpose: WinCriticalLock构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinCriticalLock::CWinCriticalLock(CRITICAL_SECTION* pCriticalSection)
{
	m_pCriticalSection = pCriticalSection;
	EnterCriticalSection(m_pCriticalSection);		//进入临界区
}

//------------------------------------------------------------------
// @Function:	 ~CWinCriticalLock()
// @Purpose: WinCriticalLock析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinCriticalLock::~CWinCriticalLock()
{
	LeaveCriticalSection(m_pCriticalSection);		//离开临界区
}

//------------------------------------------------------------------
// @Function:	 CWinCriticalLockEx()
// @Purpose: WinCriticalLockEx构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinCriticalLockEx::CWinCriticalLockEx()
{
	InitializeCriticalSection(&m_CriticalSection);	//初始化临界区
	EnterCriticalSection(&m_CriticalSection);		//进入临界区
}

//------------------------------------------------------------------
// @Function:	 ~CWinCriticalLockEx()
// @Purpose: WinCriticalLockEx析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinCriticalLockEx::~CWinCriticalLockEx()
{
	LeaveCriticalSection(&m_CriticalSection);		//离开临界区
	DeleteCriticalSection(&m_CriticalSection);		//删除临界区
}

//------------------------------------------------------------------
// @Function:	 CWinMutexLock()
// @Purpose: WinMutexLock构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinMutexLock::CWinMutexLock(HANDLE* pMutex)
{
	m_pMutex = pMutex;
}

//------------------------------------------------------------------
// @Function:	 ~CWinMutexLock()
// @Purpose: WinMutexLock析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinMutexLock::~CWinMutexLock()
{
}

//------------------------------------------------------------------
// @Function:	 Lock()
// @Purpose: WinMutexLock锁定
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CWinMutexLock::Lock() const
{
	WaitForSingleObject(*m_pMutex, INFINITE);
}

//------------------------------------------------------------------
// @Function:	 Unlock()
// @Purpose: WinMutexLock解锁
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CWinMutexLock::Unlock() const
{
	ReleaseMutex(*m_pMutex);
}

//------------------------------------------------------------------
// @Function:	 CWinMutexLockEx()
// @Purpose: WinMutexLockEx构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinMutexLockEx::CWinMutexLockEx()
{
	m_Mutex = CreateMutex(NULL, FALSE, NULL);
}

//------------------------------------------------------------------
// @Function:	 ~CWinMutexLockEx()
// @Purpose: WinMutexLockEx析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinMutexLockEx::~CWinMutexLockEx()
{
	CloseHandle(m_Mutex);
}

//------------------------------------------------------------------
// @Function:	 Lock()
// @Purpose: WinMutexLockEx锁定
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CWinMutexLockEx::Lock() const
{
	WaitForSingleObject(m_Mutex, INFINITE);
}

//------------------------------------------------------------------
// @Function:	 Unlock()
// @Purpose: WinMutexLockEx解锁
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CWinMutexLockEx::Unlock() const
{
	ReleaseMutex(m_Mutex);
}