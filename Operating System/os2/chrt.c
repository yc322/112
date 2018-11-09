#include <sys/cdefs.h>
#include "namespace.h"
#include <lib.h>
#include <unistd.h>


int chrt(deadline)
long deadline;
{
	message m;
	m.m2_l1=deadline;
	alarm((unsigned int)deadline);
	return (_syscall(PM_PROC_NR,PM_CHRT,&m));
}