/* recvclr.c - recvclr */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  recvclr  -  clear incoming message, and return message if one waiting
 *------------------------------------------------------------------------
 */
umsg32	recvclr(void)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	umsg32	msg;			/* message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->msgindex > 0) {
		msg = prptr->prmsg[prptr->msgindex-1];	/* retrieve message		*/
		prptr->msgindex--;
	} else {
		msg = OK;
	}
	restore(mask);
	return msg;
}
