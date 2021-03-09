/*-------------------------------------------------------------------------*
 *---									---*
 *---		signalCountingServer.c					---*
 *---									---*
 *---	    This file defines a C program that gets file-sys commands	---*
 *---	from client via a socket, executes those commands in their own	---*
 *---	threads, and returns the corresponding output back to the	---*
 *---	client.								---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a					Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

//	Compile with:
//	$ gcc columnServer.c -o columnServer -lpthread

//---		Header file inclusion					---//

#include	"clientServer.h"
#include	<pthread.h>	// For pthread_create()


//---		Definition of constants:				---//

const int	ERROR_FD      		= -1;


//---		Definition of global vars:				---//

//  PURPOSE:  To be non-zero for as long as this program should run, or '0'
//	otherwise.


//---		Definition of functions:				---//


//  PURPOSE:  To:
//	(1) fork() a child process.  This child process will:
//	  (1a) Convert 'numSecs' to a string.
//	  (1b) Convert 'sigProb' to a string.
//	  (1c) Redirect output from 'toClientFd' to 'STDOUT_FILENO'.
//	  (1d) Run the program "./counter" with the string forms of
//	  	'numSecs' and 'sigProb' on the command line.
//	  (1e) Send an error message back to the client on file descriptor
//		'toClientFd' if the execl() failed.
//	(2) The parent process will wait() for the child process to end
void		countSignals	(int		toClientFd,
				 int		numSecs,
				 float		sigProb
				)
{
  //  YOUR CODE HERE
  //printf("\n i am in count signals");
  pid_t childPID = fork();
 // if (childPID < 0)
 // {
//	printf("i am here num 3");
//
//  	fprintf(stderr,"pid error", toClientFd);
//	//printf("i am here num 3");
//	return;
//  }
  if (childPID == 0)
  {
	//printf("\n here is child");
	char Buffer1[BUFFER_LEN];
	char Buffer2[BUFFER_LEN];
 	//printf("\n created char buffer");
	//dup2(toClientFd, STDOUT_FILENO);
	//printf("\n did dup 2");
	snprintf(Buffer1,BUFFER_LEN ,"%d",numSecs);
	snprintf(Buffer2,BUFFER_LEN ,"%g", sigProb);
	//fprintf(stderr, Buffer1);
	dup2(toClientFd, STDOUT_FILENO);
	//fprintf(stderr,"\n i am about to launch counter");
	execl("./counter","counter", Buffer1, Buffer2,  NULL); 
	fprintf(stderr,"execl error", toClientFd);
		
  }
  else
  {
	//fprintf(stderr, "\n i am waiting");
  	wait(NULL);
  }
 //printf("\n here is the end of count signals");
}


//  
//  PURPOSE:  To cast 'vPtr' to the pointer type coming from 'doServer()'
//	that points to two integers.  Then, to use those two integers,
//	one as a file descriptor, the other as a thread number, to fulfill
//	requests coming from the client over the file descriptor socket.
//	Returns 'NULL'.
void*		handleClient	(void*		vPtr
				)
{
  //  I.  Application validity check:

  //  II.  Handle client:
  //  II.A.  Get file descriptor:
  int*      intArray	=(int*)vPtr;
  int 	   clientFd	= intArray[0];	// CHANGE THAT 0!
  int	   threadNum	= intArray[1];	// CHANGE THAT 0!

  //  YOUR CODE HERE
  printf("Thread %d starting.\n",threadNum);

  //  II.B.  Read command:
  char	buffer[BUFFER_LEN];
  int*	intBufferPtr	= (int*)buffer;
  int	numSecs;
  float	sigProb;

  read(clientFd,buffer,2*sizeof(int));
  numSecs		= ntohl(intBufferPtr[0]);	// CHANGE THAT 0!
  intBufferPtr[1]	= ntohl(intBufferPtr[1]);	// CHANGE THAT 0!
  sigProb		= *(float*)&intBufferPtr[1];	// CHANGE THAT 0.0!

  printf("Thread %d received: %d %g\n",threadNum,numSecs,sigProb);
  countSignals(clientFd,numSecs,sigProb);
  //printf("\n count signal was executed");


  //  III.  Finished:
  printf("Thread %d quitting.\n",threadNum);
  return(NULL);
}


//  PURPOSE:  To run the server by 'accept()'-ing client requests from
//	'listenFd' and doing them.
void		doServer	(int		listenFd
				)
{
  //  I.  Application validity check:

  //  II.  Server clients:
  pthread_t		threadId;
  pthread_attr_t	threadAttr;
  int			threadCount	= 0;

  //  YOUR CODE HERE
  pthread_attr_init(&threadAttr);
  pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);
  while  (1)
  {
    //  YOUR CODE HERE
    int* clientFdPtr = (int*)malloc(2*sizeof(int));
    clientFdPtr[0] = accept(listenFd,NULL, NULL);
    clientFdPtr[1] = threadCount++;
    
    pthread_create(&threadId, &threadAttr, handleClient, clientFdPtr);
  }
  //  YOUR CODE HERE
    pthread_attr_destroy(&threadAttr);
  //  III.  Finished:
  printf("i am here num 1");
}


//  PURPOSE:  To decide a port number, either from the command line arguments
//	'argc' and 'argv[]', or by asking the user.  Returns port number.
int		getPortNum	(int	argc,
				 char*	argv[]
				)
{
  //  I.  Application validity check:

  //  II.  Get listening socket:
  int	portNum;

  if  (argc >= 2)
    portNum	= strtol(argv[1],NULL,0);
  else
  {
    char	buffer[BUFFER_LEN];

    printf("Port number to monopolize? ");
    fgets(buffer,BUFFER_LEN,stdin);
    portNum	= strtol(buffer,NULL,0);
  }

  //  III.  Finished:  
  return(portNum);
}


//  PURPOSE:  To attempt to create and return a file-descriptor for listening
//	to the OS telling this server when a client process has connect()-ed
//	to 'port'.  Returns that file-descriptor, or 'ERROR_FD' on failure.
int		getServerFileDescriptor
				(int		port
				)
{
  //  I.  Application validity check:

  //  II.  Attempt to get socket file descriptor and bind it to 'port':
  //  II.A.  Create a socket
  int socketDescriptor = socket(AF_INET, // AF_INET domain
			        SOCK_STREAM, // Reliable TCP
			        0);

  if  (socketDescriptor < 0)
  {
    perror("socket()");
    return(ERROR_FD);
  }

  //  II.B.  Attempt to bind 'socketDescriptor' to 'port':
  //  II.B.1.  We'll fill in this datastruct
  struct sockaddr_in socketInfo;

  //  II.B.2.  Fill socketInfo with 0's
  memset(&socketInfo,'\0',sizeof(socketInfo));

  //  II.B.3.  Use TCP/IP:
  socketInfo.sin_family = AF_INET;

  //  II.B.4.  Tell port in network endian with htons()
  socketInfo.sin_port = htons(port);

  //  II.B.5.  Allow machine to connect to this service
  socketInfo.sin_addr.s_addr = INADDR_ANY;

  //  II.B.6.  Try to bind socket with port and other specifications
  int status = bind(socketDescriptor, // from socket()
		    (struct sockaddr*)&socketInfo,
		    sizeof(socketInfo)
		   );

  if  (status < 0)
  {
    perror("bind()");
    return(ERROR_FD);
  }

  //  II.B.6.  Set OS queue length:
  listen(socketDescriptor,5);

  //  III.  Finished:
  return(socketDescriptor);
}


int		main		(int	argc,
				 char*	argv[]
				)
{
  //  I.  Application validity check:

  //  II.  Do server:
  int 	      port	= getPortNum(argc,argv);
  int	      listenFd	= getServerFileDescriptor(port);
  int	      status	= EXIT_FAILURE;

  if  (listenFd >= 0)
  {
    doServer(listenFd);
    close(listenFd);
    status	= EXIT_SUCCESS;
  }

  //  III.  Finished:
  return(status);
}
