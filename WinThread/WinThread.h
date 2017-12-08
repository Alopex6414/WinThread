/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		WinThread.h
* @brief	This Program is WinThread DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2017-12-8	v1.00a	alopex	Create Project
*/
#pragma once

#ifndef __WINTHREAD_H_
#define __WINTHREAD_H_

//Include Windows Header File
#include <Windows.h>

//Include C/C++ Running Header File
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <tchar.h>

//Macro Definition
#ifdef WINTHREAD_EXPORTS
#define WINTHREAD_API	__declspec(dllexport)
#else
#define WINTHREAD_API	__declspec(dllimport)
#endif

//Class Definition
//CWinThreadBase����
class WINTHREAD_API CWinThreadBase
{
private:

public:
	CWinThreadBase();													//����
	virtual ~CWinThreadBase();											//����
	virtual void WINAPI WinThreadRun() = 0;								//���麯��
};

//CWinThread������
class WINTHREAD_API CWinThread :public CWinThreadBase
{
private:
	HANDLE m_hThread;													//�߳̾��
	DWORD m_dwThreadID;													//�̺߳�
	volatile bool m_bThreadRun;											//�߳�����
	CWinThreadBase* m_pThreadBase;										//�̻߳���ָ��

private:
	static DWORD WINAPI WinThreadProc(LPVOID pThreadPara);				//�̴߳�����(��̬)

public:
	CWinThread();														//����
	~CWinThread();														//����
	CWinThread(CWinThreadBase* pThreadBase);							//����

	DWORD WINAPI WinThreadGetID() const;								//�߳�ID��ȡ

	virtual bool WINAPI WinThreadInit(bool bSuspend = false);			//�̳߳�ʼ��(����:true)
	virtual void WINAPI WinThreadRun();									//�߳�����(��д)
	virtual void WINAPI WinThreadJoin(int nTimeOut = -1);				//�̵߳ȴ�����
	virtual void WINAPI WinThreadResume();								//�ָ̻߳�
	virtual void WINAPI WinThreadSuspend();								//�̹߳���
	virtual bool WINAPI WinThreadTerminate(DWORD dwExitCode);			//�߳���ֹ
	virtual void WINAPI WinThreadExit();								//�߳��˳�
};

#endif