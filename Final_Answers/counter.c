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
//  recommended runner var
int shouldRun = 1;

int counting = 0;


void		sigAlarmHandler	(int		sigInt
				)
{
  //  YOUR CODE HERE
  shouldRun = 0;
}


void		sigUser1Handler	(int		sigInt
				)
{
  //  YOUR CODE HERE
  counting++;
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
  //  number 1
  //  do I need an fgets();?
  if (argc > 1)
  {
        //char buffer[256];
        //fgets(buffer, 256, stdin);
  	numSecs = strtol(argv[1], &cPtr, 0);
	sigProb = strtod(argv[2], &cPtr);
	if (numSecs < 1 || numSecs > 60)
	{
	 fprintf(stderr, "dis number is out of bounds"); 
	}
	if (sigProb < 0.0 || sigProb > 1.0)
        {
         fprintf(stderr, "that probability number is out of bounds");
        }
  }
  else
  {
   write(STDOUT_FILENO, &errorResponse, sizeof(errorResponse));
   exit(EXIT_FAILURE);
  }

  // nummber 2
  struct sigaction	memaw;

  memset(&memaw,'\0', sizeof(memaw));
  memaw.sa_handler	= sigAlarmHandler;
  sigaction(SIGALRM, &memaw, NULL);

  memaw.sa_handler        = sigUser1Handler;
  sigaction(SIGUSR1, &memaw, NULL);

    
  //number 3
  pid_t childPid;
  childPid = fork();
  if (childPid  == 0)
  {
  	char buffer[256];
	snprintf(buffer, 256, "%g", sigProb);
	execl(SIGNALER_PROGNAME, SIGNALER_PROGNAME, buffer, NULL);
	write(STDOUT_FILENO, &errorResponse, sizeof(errorResponse));
	exit(EXIT_FAILURE);
  }
  else if (childPid < 0)
  {
  write(STDOUT_FILENO, &errorResponse, sizeof(errorResponse));
  exit(EXIT_FAILURE);
  }
  // number 4 
  alarm(numSecs);
  //number 5
  while(shouldRun)
  {
  	sleep(1);
  }

  //number 6
  kill(childPid, SIGINT);
  wait(NULL);

  // number 7
  // host to network long
  counting =  htonl(counting);
  write(STDOUT_FILENO, &counting, sizeof(counting));
  //write(STDOUT_FILE, &errorRe


  return(EXIT_SUCCESS);
}
