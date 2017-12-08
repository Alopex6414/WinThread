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
// @Purpose: WinThreadBase���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinThreadBase::CWinThreadBase()
{
}

//------------------------------------------------------------------
// @Function:	 ~CWinThreadBase()
// @Purpose: WinThreadBase��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinThreadBase::~CWinThreadBase()
{
}

//------------------------------------------------------------------
// @Function:	 CWinThread()
// @Purpose: WinThread���캯��
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
// @Purpose: WinThread��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CWinThread::~CWinThread()
{
}

//------------------------------------------------------------------
// @Function:	 CWinThread(CWinThreadBase* pThreadBase)
// @Purpose: WinThread���캯��
// @Since: v1.00a
// @Para: CWinThreadBase* pThreadBase	//�̻߳���ָ��
// @Return: None
//------------------------------------------------------------------
CWinThread::CWinThread(CWinThreadBase* pThreadBase)
{
	m_pThreadBase = pThreadBase;
	m_bThreadRun = false;
}

//------------------------------------------------------------------
// @Function:	 WinThreadInit(bool bSuspend)
// @Purpose: WinThread�̳߳�ʼ��
// @Since: v1.00a
// @Para: bool bSuspend	//�����Ƿ����
// @Return: None
//------------------------------------------------------------------
bool WINAPI CWinThread::WinThreadInit(bool bSuspend)
{
	//�߳���������״̬
	if (m_bThreadRun) return true;

	//�̳߳�ʼ������
	if (bSuspend)
	{
		m_hThread = CreateThread(NULL, 0, WinThreadProc, this, CREATE_SUSPENDED, &m_dwThreadID);
	}
	else
	{
		m_hThread = CreateThread(NULL, 0, WinThreadProc, this, 0, &m_dwThreadID);
	}

	//�߳�״̬
	m_bThreadRun = (m_hThread != NULL);

	return m_bThreadRun;
}

//------------------------------------------------------------------
// @Function:	 WinThreadRun()
// @Purpose: WinThread�߳�����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CWinThread::WinThreadRun()
{
	//�߳�δ����
	if (!m_bThreadRun) return;

	//�߳�����
	if (m_pThreadBase != NULL)
	{
		m_pThreadBase->WinThreadRun();
	}

	m_bThreadRun = false;
}

//------------------------------------------------------------------
// @Function:	 WinThreadJoin()
// @Purpose: WinThread�̵߳ȴ�
// @Since: v1.00a
// @Para: int nTimeOut	//�ȴ�ʱ��
// @Return: None
//------------------------------------------------------------------
void WINAPI CWinThread::WinThreadJoin(int nTimeOut)
{
	//�߳�δ�����ɹ����߳�δ����
	if (m_hThread == NULL || !m_bThreadRun)
	{
		return;
	}

	//�̵߳ȴ�ʱ��
	if (nTimeOut < 0)
	{
		nTimeOut = INFINITE;
	}

	WaitForSingleObject(m_hThread, nTimeOut);
}

//------------------------------------------------------------------
// @Function:	 WinThreadResume()
// @Purpose: WinThread�ָ̻߳�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CWinThread::WinThreadResume()
{
	//�߳�δ�����ɹ����߳�δ����
	if (m_hThread == NULL || !m_bThreadRun)
	{
		return;
	}

	ResumeThread(m_hThread);
}

//------------------------------------------------------------------
// @Function:	 WinThreadSuspend()
// @Purpose: WinThread�̹߳���
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CWinThread::WinThreadSuspend()
{
	//�߳�δ�����ɹ����߳�δ����
	if (m_hThread == NULL || !m_bThreadRun)
	{
		return;
	}

	SuspendThread(m_hThread);
}

//------------------------------------------------------------------
// @Function:	 WinThreadTerminate(DWORD dwExitCode)
// @Purpose: WinThread�߳��˳�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool WINAPI CWinThread::WinThreadTerminate(DWORD dwExitCode)
{
	//�߳�δ�����ɹ����߳�δ����
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
// @Purpose: WinThread�߳��˳�
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
// @Purpose: WinThread�߳�ID��ȡ
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
// @Purpose: WinThread�̴߳�����
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