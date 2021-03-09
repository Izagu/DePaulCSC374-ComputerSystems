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
#include	<string.h>		// memset()
#include	<sys/types.h>
#include	<signal.h>


//  YOUR CODE HERE

int shouldRun = 1;
int secsPassed = 0;
//pid_t parentPid = getppid();
void		sigIntHandler	(int		sigInt
				)
{
  //  YOUR CODE HERE
  shouldRun = 0;
}


int		main		(int		argc,
				 char*		argv[]
				)
{
  float		sigProb;
  char*		cPtr;

  //  YOUR CODE HERE
  if (argc > 1)
  {
    //int numSecs = strtol(argv[0], &cPtr, NULL);
    //fprintf(stderr, "this is argv[0]: %g", numSecs );
    sigProb = strtod(argv[1], &cPtr);
    //fprintf(stderr, "this is argv[1]: %g", sigProb ); 
  }
  struct sigaction  memaw;
  memset(&memaw, '\0', sizeof(memaw));
  memaw.sa_handler	= sigIntHandler;
  sigaction(SIGINT, &memaw, NULL);
  			//fprintf(stderr, "the code has gotten this far part 2");
  

  srand(getpid());
  			//fprintf(stderr, "the code has gotten this far");
  			//

  while(shouldRun)
  {
  sleep(1);
  secsPassed++;
  			//float dice = drand48();
  if (sigProb == 0.0 )
  {
  			//secsPassed++;
  fprintf(stderr, "\n sorry dude no signals will send, but %d seconds have passed\n", secsPassed);
  			//kill(getppid(), SIGALRM);
  
  }
  else if (sigProb == 1.0)
  {
  fprintf(stderr, "\n I will always send a signal. Seconds:%d \n", secsPassed);
  			//pid_t parentPid = getppid();
  kill(getppid(), SIGUSR1);
  			//signal(SIGUSR1,parentPid);
  }
  else if (((double)rand()/RAND_MAX) <= sigProb)
  {
    			//fprintf(stderr, "\n drand38() = %g", ((double)rand()/RAND_MAX));
    			//fprintf(stderr, "\n sigprob = %g", sigProb);
    			//double compare = drand48(void);
    			//if(compare <= sigProb)
    			//{
    			//secsPassed++;
  fprintf(stderr, "\n I sent a signal at %d second(s)",secsPassed );
  kill(getppid(), SIGUSR1);
    			//}

  }
  }
  return(EXIT_SUCCESS);
}
