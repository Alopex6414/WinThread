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
//CWinThreadBase基类
class WINTHREAD_API CWinThreadBase
{
private:

public:
	CWinThreadBase();													//构造
	virtual ~CWinThreadBase();											//析构
	virtual void WINAPI WinThreadRun() = 0;								//纯虚函数
};

//CWinThread派生类
class WINTHREAD_API CWinThread :public CWinThreadBase
{
private:
	HANDLE m_hThread;													//线程句柄
	DWORD m_dwThreadID;													//线程号
	volatile bool m_bThreadRun;											//线程运行
	CWinThreadBase* m_pThreadBase;										//线程基类指针

private:
	static DWORD WINAPI WinThreadProc(LPVOID pThreadPara);				//线程处理函数(静态)

public:
	CWinThread();														//构造
	~CWinThread();														//析构
	CWinThread(CWinThreadBase* pThreadBase);							//构造

	DWORD WINAPI WinThreadGetID() const;								//线程ID获取

	virtual bool WINAPI WinThreadInit(bool bSuspend = false);			//线程初始化(挂起:true)
	virtual void WINAPI WinThreadRun();									//线程运行(重写)
	virtual void WINAPI WinThreadJoin(int nTimeOut = -1);				//线程等待结束
	virtual void WINAPI WinThreadResume();								//线程恢复
	virtual void WINAPI WinThreadSuspend();								//线程挂起
	virtual bool WINAPI WinThreadTerminate(DWORD dwExitCode);			//线程终止
	virtual void WINAPI WinThreadExit();								//线程退出
};

#endif