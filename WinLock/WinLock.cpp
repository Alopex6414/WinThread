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
// @Purpose: WinCriticalLock���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinCriticalLock::CWinCriticalLock(CRITICAL_SECTION* pCriticalSection)
{
	m_pCriticalSection = pCriticalSection;
	EnterCriticalSection(m_pCriticalSection);		//�����ٽ���
}

//------------------------------------------------------------------
// @Function:	 ~CWinCriticalLock()
// @Purpose: WinCriticalLock��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinCriticalLock::~CWinCriticalLock()
{
	LeaveCriticalSection(m_pCriticalSection);		//�뿪�ٽ���
}

//------------------------------------------------------------------
// @Function:	 CWinCriticalLockEx()
// @Purpose: WinCriticalLockEx���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinCriticalLockEx::CWinCriticalLockEx()
{
	InitializeCriticalSection(&m_CriticalSection);	//��ʼ���ٽ���
	EnterCriticalSection(&m_CriticalSection);		//�����ٽ���
}

//------------------------------------------------------------------
// @Function:	 ~CWinCriticalLockEx()
// @Purpose: WinCriticalLockEx��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinCriticalLockEx::~CWinCriticalLockEx()
{
	LeaveCriticalSection(&m_CriticalSection);		//�뿪�ٽ���
	DeleteCriticalSection(&m_CriticalSection);		//ɾ���ٽ���
}

//------------------------------------------------------------------
// @Function:	 CWinMutexLock()
// @Purpose: WinMutexLock���캯��
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
// @Purpose: WinMutexLock��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinMutexLock::~CWinMutexLock()
{
}

//------------------------------------------------------------------
// @Function:	 Lock()
// @Purpose: WinMutexLock����
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
// @Purpose: WinMutexLock����
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
// @Purpose: WinMutexLockEx���캯��
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
// @Purpose: WinMutexLockEx��������
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
// @Purpose: WinMutexLockEx����
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
// @Purpose: WinMutexLockEx����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CWinMutexLockEx::Unlock() const
{
	ReleaseMutex(m_Mutex);
}