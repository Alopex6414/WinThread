/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		WinThread.cpp
* @brief	This Program is WinThread DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2017-12-8	v1.00a	alopex	Create Project
*/
#include "WinThread.h"

//------------------------------------------------------------------
// @Function:	 CWinThreadBase()
// @Purpose: WinThreadBase构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinThreadBase::CWinThreadBase()
{
}

//------------------------------------------------------------------
// @Function:	 ~CWinThreadBase()
// @Purpose: WinThreadBase析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinThreadBase::~CWinThreadBase()
{
}

//------------------------------------------------------------------
// @Function:	 CWinThread()
// @Purpose: WinThread构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinThread::CWinThread()
{
	m_pThreadBase = NULL;
	m_bThreadRun = false;
}

//------------------------------------------------------------------
// @Function:	 ~CWinThread()
// @Purpose: WinThread析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinThread::~CWinThread()
{
}

//------------------------------------------------------------------
// @Function:	 CWinThread(CWinThreadBase* pThreadBase)
// @Purpose: WinThread构造函数
// @Since: v1.00a
// @Para: CWinThreadBase* pThreadBase	//线程基类指针
// @Return: None
//------------------------------------------------------------------
CWinThread::CWinThread(CWinThreadBase* pThreadBase)
{
	m_pThreadBase = pThreadBase;
	m_bThreadRun = false;
}

//------------------------------------------------------------------
// @Function:	 WinThreadInit(bool bSuspend)
// @Purpose: WinThread线程初始化
// @Since: v1.00a
// @Para: bool bSuspend	//运行是否挂起
// @Return: None
//------------------------------------------------------------------
bool WINAPI CWinThread::WinThreadInit(bool bSuspend)
{
	//线程正在运行状态
	if (m_bThreadRun) return true;

	//线程初始化挂起
	if (bSuspend)
	{
		m_hThread = CreateThread(NULL, 0, WinThreadProc, this, CREATE_SUSPENDED, &m_dwThreadID);
	}
	else
	{
		m_hThread = CreateThread(NULL, 0, WinThreadProc, this, 0, &m_dwThreadID);
	}

	//线程状态
	m_bThreadRun = (m_hThread != NULL);

	return m_bThreadRun;
}

//------------------------------------------------------------------
// @Function:	 WinThreadRun()
// @Purpose: WinThread线程运行
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CWinThread::WinThreadRun()
{
	//线程未运行
	if (!m_bThreadRun) return;

	//线程运行
	if (m_pThreadBase != NULL)
	{
		m_pThreadBase->WinThreadRun();
	}

	m_bThreadRun = false;
}

//------------------------------------------------------------------
// @Function:	 WinThreadJoin()
// @Purpose: WinThread线程等待
// @Since: v1.00a
// @Para: int nTimeOut	//等待时间
// @Return: None
//------------------------------------------------------------------
void WINAPI CWinThread::WinThreadJoin(int nTimeOut)
{
	//线程未创建成功或线程未运行
	if (m_hThread == NULL || !m_bThreadRun)
	{
		return;
	}

	//线程等待时间
	if (nTimeOut < 0)
	{
		nTimeOut = INFINITE;
	}

	WaitForSingleObject(m_hThread, nTimeOut);
}

//------------------------------------------------------------------
// @Function:	 WinThreadResume()
// @Purpose: WinThread线程恢复
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CWinThread::WinThreadResume()
{
	//线程未创建成功或线程未运行
	if (m_hThread == NULL || !m_bThreadRun)
	{
		return;
	}

	ResumeThread(m_hThread);
}

//------------------------------------------------------------------
// @Function:	 WinThreadSuspend()
// @Purpose: WinThread线程挂起
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CWinThread::WinThreadSuspend()
{
	//线程未创建成功或线程未运行
	if (m_hThread == NULL || !m_bThreadRun)
	{
		return;
	}

	SuspendThread(m_hThread);
}

//------------------------------------------------------------------
// @Function:	 WinThreadTerminate(DWORD dwExitCode)
// @Purpose: WinThread线程退出
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool WINAPI CWinThread::WinThreadTerminate(DWORD dwExitCode)
{
	//线程未创建成功或线程未运行
	if (m_hThread == NULL || !m_bThreadRun)
	{
		return true;
	}

	if (TerminateThread(m_hThread, dwExitCode))
	{
		CloseHandle(m_hThread);
		return true;
	}

	return false;
}

//------------------------------------------------------------------
// @Function:	 WinThreadExit()
// @Purpose: WinThread线程退出
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CWinThread::WinThreadExit()
{
	if (m_hThread == NULL)
	{
		return;
	}

	CloseHandle(m_hThread);
}

//------------------------------------------------------------------
// @Function:	 WinThreadGetID()
// @Purpose: WinThread线程ID获取
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DWORD WINAPI CWinThread::WinThreadGetID() const
{
	return m_dwThreadID;
}

//------------------------------------------------------------------
// @Function:	 WinThreadProc(LPVOID pThreadPara)
// @Purpose: WinThread线程处理函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DWORD WINAPI CWinThread::WinThreadProc(LPVOID pThreadPara)
{
	CWinThread* pThread = (CWinThread*)(pThreadPara);

	pThread->WinThreadRun();
	
	return 0;
}