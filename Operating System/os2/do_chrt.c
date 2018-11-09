/* The kernel call implemented in this file:
 *   m_type:	SYS_CHRT
 *
 * The parameters for this kernel call are:
 *   m2_i1: RA_PROC_NR indecates a process
 * 	 m2_|1: RA_DEADLINE deadline
 */


#include "kernel/system.h"
#include <minix/endpoint.h>
#include <stdio.h>
#include <signal.h>
#include "../system.h"
#include <minix/timers.h>

/*==========================================================*
*			do_chrt				*
*==========================================================*/


int do_chrt(struct proc * caller, message *m_ptr)
{
		struct proc *rp;
		minix_timer_t *tp;
		/* the proc structure of process */
		rp=proc_addr(m_ptr->m2_i1);
		/*dequeue to change the dispatch*/

		RTS_SET(rp,RTS_NO_QUANTUM);
		/*call chrt again ,need to clear the old deadline */
		if(rp->p_deadline.tmr_exp_time!=0){
			do_setalarm(rp,m_ptr);
			rp->p_deadline.tmr_exp_time=0;

		}
		/*set the information to a timer_t data structure*/
		if(m_ptr-> m2_l1!=0){
			tp=&rp->p_deadline;
			tp->tmr_exp_time=m_ptr->m2_l1 *60+get_monotonic();
			do_setalarm(rp,m_ptr);
			printf("Process %d set timer, deadline =%lu\n",tp->tmr_arg.ta_int,tp->tmr_exp_time);
		}
		/*enqueue and change the dispatch again*/
		RTS_UNSET(rp,RTS_NO_QUANTUM);
		return (OK);
}

