/*-------------------------------------------------------------------------*
 *---									---*
 *---		signaler.c						---*
 *---									---*
 *---	    To get a signaling probability from	the command line, and	---*
 *---	signal the parent process with that probability after each	---*
 *---	second.  Stops when receives SIGINT.				---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a					Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>k		// memset()
#include	<sys/types.h>
#include	<signal.h>


//  YOUR CODE HERE

void		sigIntHandler	(int		sigInt
				)
{
  //  YOUR CODE HERE
}


int		main		(int		argc,
				 char*		argv[]
				)
{
  float		sigProb;
  char*		cPtr;

  //  YOUR CODE HERE


  return(EXIT_SUCCESS);
}
