/*-------------------------------------------------------------------------*
 *---									---*
 *---		counter.c						---*
 *---									---*
 *---	    To get a number of seconds and a signaling probability from	---*
 *---	the command line, to launch a child process to signal this one	---*
 *---	with the given probability, and to count how many signals were	---*
 *---	received within the given number of seconds.			---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a					Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>	// memset()
#include	<signal.h>	// sigaction()
#include	<unistd.h>	// fork(), execl()
#include	<arpa/inet.h>	// htonl()


#define		SIGNALER_PROGNAME		"./signaler"


//  YOUR CODE HERE


void		sigAlarmHandler	(int		sigInt
				)
{
  //  YOUR CODE HERE
}


void		sigUser1Handler	(int		sigInt
				)
{
  //  YOUR CODE HERE
}


int		main		(int		argc,
				 char*		argv[]
				)
{
  int		numSecs;
  float		sigProb;
  char*		cPtr;
  int		errorResponse	= htonl(-1);

  //  YOUR CODE HERE

  return(EXIT_SUCCESS);
}
