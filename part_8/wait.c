#include "apue.h"
#include <sys/wait.h>

void pr_exit(int status){
    if (WIFEXITED(status)){
        printf("normal treminatrion exit status = %d\n",WEXITSTATUS(status));
    }else if(WIFSIGNALED(status)){
        printf("abnormal termination signal number = %d%s\n",WTERMSIG(status),
    
#ifdef WCOREDUMP 
    WCOREDUMP(status) ? "core file generated" : "" );
    }
#else 
    "");
    }
#endif 
    else if (WIFSTOPPED(status)) {
        printf("child stopped signal number = %d\n",WSTOPSIG(status));
    }
    
}
int main(void){
    pid_t pid;
    int status;
    int zero = 0;

    // =================== // ===================
    if ((pid = fork()) < 0){
        err_sys("fork error");
    }else if(pid == 0){
        exit(7);
    }

    if (wait(&status) !=  pid){
        err_sys("fork error");
    }
    pr_exit(status);
    // =================== // ===================
     if ((pid = fork()) < 0){
        err_sys("fork error");
    }else if(pid == 0){
        abort();
    }

    if (wait(&status) !=  pid){
        err_sys("fork error");
    }
      pr_exit(status);
    
    // =================== // ===================

  
    if ((pid = fork()) < 0){
        err_sys("fork error");
    }else if(pid == 0){
        status /= zero;
    }

    if (wait(&status) !=  pid){
        err_sys("fork error");
    }
      pr_exit(status);


    return 0;
}