/* ffmpeg_multitask.c
*/
#include <signal.h>
#include "ffmpeg_multitask.h"

#define SYNC_SIG SIGUSR1                /* Synchronization signal */


static void             /* Signal handler - does nothing but return */
handler(int sig)
{
 printf("SIGNAL received\n");
 printf("Both videos recorded\n");
}

int
main(int argc, char *argv[])
{
    pid_t childPid;
    sigset_t blockMask, origMask, emptyMask;
    struct sigaction sa;

    setbuf(stdout, NULL);               /* Disable buffering of stdout */

    signal(SIGUSR1, &handler);

    sigemptyset(&blockMask);
    sigaddset(&blockMask, SYNC_SIG);    /* Block signal */
    if (sigprocmask(SIG_BLOCK, &blockMask, &origMask) == -1)
         printf("sigprocmask failed\n");

    switch (childPid = fork()) {
    case -1:
         printf("fork failed\n");

    case 0: /* Child */

        /* Child does some required action here... */

        printf("Child started - recording from ipcam\n");
        system("ffmpeg -f mjpeg -i http://admin:dlink123@192.168.1.21:80/video/mjpg.cgi -map 0:v:0 -y webcam.mp4 -t 10");
        /* And then signals parent that it's done */

        printf("Child about to signal parent\n");
                
        if (kill(getppid(), SYNC_SIG) == -1)
             printf("signal sending failed\n");
        else 
	     printf("signal sent\n");
        
        _exit(EXIT_SUCCESS);

    default: /* Parent */

        /* Parent may do some work here, and then waits for child to
           complete the required action */

        printf("Parent about to wait for signal\n");
                
        int sig;
	int result = sigwait(&blockMask, &sig);
        if(!result)
            printf("Parent got signal- recording from webcam\n"); 
        
        /* If required, return signal mask to its original state */
        system("ffmpeg -f video4linux2 -r 25 -i /dev/video0 -map 0:v:0 -vcodec mpeg4 -y webcam8.mp4 -t 10"); 
        
	if (sigprocmask(SIG_SETMASK, &origMask, NULL) == -1)
             printf("sigprocmask failed\n");
        printf("signal unblocked\n");

	raise(SIGUSR1);
        /* Parent carries on to do other things... */
	exit(EXIT_SUCCESS);
    }
}

