/*
 * parent processとchild processの同期を取るためのシグナルの使い方について
 */

#include <stdio.h>
#include <signal.h>
#include "sample.h"

/* シグナルハンドラが非ゼロに設定する */
static volatile sig_atomic_t	sigflag;
static sigset_t	newmask;
static sigset_t	oldmask;
static sigset_t	zeromask;

/* SIGUSR1とSIGUSR2に１つのシグナルハンドラ */
static void	sig_usr(int signo)
{
	sigflag = 1;
}

void	TELL_WAIT(void)
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
	{
		err_sys("signal(SIGUSR1) error");
	}
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
	{
		err_sys("signal(SIGUSR2) error");
	}
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
	sigaddset(&newmask, SIGUSR2);

	/* SIGUSR1とSIGUSR2をブロックし、現在のシグナルマスクを保存 */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	{
		err_sys("SIG_BLOCK error");
	}
}

/* parentの完了を通知 */
void	TELL_PARENT(pid_t pid)
{
	kill(pid, SIGUSR2);
}

void	WAIT_PARENT(void)
{
	while (sigflag == 0)
	{
		/* 親を待つ */
		sigsuspend(&zeromask);
	}
	sigflag = 0;
	/* シグナルマスクを元の値にリセット */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		err_sys("SIG_SETMASK error");
	}
}

/* childに完了を通知 */
void	TELL_CHILD(pid_t pid)
{
	kill(pid, SIGUSR1);
}

void	WAIT_CHILD(void)
{
	while (sigflag == 0)
	{
		/* childを待つ */
		sigsuspend(&zeromask);
	}
	sigflag = 0;
	/* シグナルマスクを元の値にリセット */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		err_sys("SIG_SETMASK error");
	}
}
