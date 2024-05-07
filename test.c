// #include <signal.h>
// #include <stdlib.h>
// #include"minishell.h"
// #include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// // Function to handle Ctrl+C (SIGINT)
// void handle_c_ctrol(int signal) {
//     (void)signal; // Prevents unused parameter warning
//     printf("\n"); // New line for a clean start
//     rl_replace_line(" ", 0); // Clear the current line
//     rl_on_new_line(); // Signal Readline for a new line
//     rl_redisplay(); // Redisplay the prompt
// }

// int main() {
//     // Register the signal handler for SIGINT
//     signal(SIGINT, handle_c_ctrol);

//     while (1) {
//         // Display the Readline prompt
//         char *input = readline("~ minishell 😎 ↪ ");

//         if (input == NULL) {
//             // Handle EOF (Ctrl+D) to exit
//             printf("\nExiting...\n");
//             break;
//         }

//         if (ft_strlen(input) > 0) {
//             add_history(input); // Add valid input to history
//         }

//         // Process the command here
//         // ...

//         free(input); // Free the Readline-allocated memory
//     }

//     return 0;
// }


       #include <stdint.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <sys/wait.h>
       #include <unistd.h>

       int
       main(int argc, char *argv[])
       {
           int    wstatus;
           pid_t  cpid, w;

           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {            /* Code executed by child */
               printf("Child PID is %jd\n", (intmax_t) getpid());
               if (argc == 1)
                   pause();                    /* Wait for signals */
               _exit(atoi(argv[1]));

           } else {                    /* Code executed by parent */
               do {
                   w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
                   if (w == -1) {
                       perror("waitpid");
                       exit(EXIT_FAILURE);
                   }

                   if (WIFEXITED(wstatus)) {
                       printf("exited, status=%d\n", WEXITSTATUS(wstatus));
                   } else if (WIFSIGNALED(wstatus)) {
                       printf("killed by signal %d\n", WTERMSIG(wstatus));
                   } else if (WIFSTOPPED(wstatus)) {
                       printf("stopped by signal %d\n", WSTOPSIG(wstatus));
                   } else if (WIFCONTINUED(wstatus)) {
                       printf("continued\n");
                   }
               } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
               exit(EXIT_SUCCESS);
           }
       }
