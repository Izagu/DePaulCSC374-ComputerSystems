/*-------------------------------------------------------------------------*
 *---                                                                   ---*
 *---           selfCaller.c                                            ---*
 *---                                                                   ---*
 *---       This program demonstrates process programming and           ---*
 *---   signalling by "recursively" calling itself a limited number of  ---*
 *---   and selectively signally its parent process.                    ---*
 *---                                                                   ---*
 *---   ----    ----    ----    ----    ----    ----    ----    ----    ---*
 *---                                                                   ---*
 *---   Version 1a              2020 April 18           Joseph Phillips ---*
 *---                                                                   ---*
 *-------------------------------------------------------------------------*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	<signal.h>

const int	TEXT_LEN	= 16;

const int	NUM_SECS_TO_RUN	= 30;

#define		PROGNAME	"selfCaller"

int		numTimesCalled[3]
				= {0,0,0};

pid_t		pidToSignal	= -1;

pid_t		childPid	= -1;

int		level		= +2;

int		shouldRun	= 1;

// YOUR SIGNAL HANDLERS HERE
void sigAlarm(int sig){
    printf("Process %d:call level 0\n", level);
    signal(SIGALRM, sigAlarm);
    alarm(rand()%10+1)
    numTimesCalled[0]++;
    if (level != 2){
        kill(getppid(), SIGUSR1);
    }
}

void sigUno(int sig){
    printf("Process %d:call level 1\n", level);
    numTimesCalled[1]++;
    if (level != 2){
        kill(getppid(), SIGUSR2);
    }
}

void sigDos(int sig){
    printf("Process %d:call level 0\n", level);
    numTimesCalled[2]++;
}
void sigInteger(int sig){
    shouldRun = 0;
}


int		main		(int		argc,
				 char*		argv[]
				)
{
  srand(getpid());
  // YOUR CODE HERE
  if(argc>0){
      level = strtol(argv[1], NULL, 0);
  }
  else if(argc < 0 ||argc != 0 || argc != 1)
  {
      level = 2;
  }
  

  if(level > 0){
    if (fork()==0){

        execl(PROGNAME, "selfCaller.c", NULL);
        char text[TEXT_LEN];
        snprintf(text, TEXT_LEN, "%d", level-1); 
    }
  }


  struct sigaction act;

  memset(&act, '\0', sixeof(act));
  //alarm
  act.sa_handler = sigAlarm;
  sigaction(SIGALRM, &act, NULL );
  //usr1
  act.sa_handler = sigUno;
  sigaction(SIGUSR1, &act, NULL );
  //usr2
  act.sa_handler = sigDos;
  sigaction(SIGUSR2, &act, NULL );
  //int
  act.sa_handler = sigInteger;
  sigaction(SIGINT, &act, NULL);

  //unsigned int Sendit = alarm(rand()%10+1);
  //signal(SIGALRM, Sendit)

if(getPid() == 0)
{   
    //something
    wait(NULL);
}

  printf("Level %d: %d %d %d\n",level,
	 numTimesCalled[0],numTimesCalled[1],numTimesCalled[2]
	);

  return(EXIT_SUCCESS);  
}