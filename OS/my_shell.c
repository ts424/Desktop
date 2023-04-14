#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64


pid_t foreground_pid;

void sigint_handler(int signum) {
    if (foreground_pid != 0) {
        kill(foreground_pid, SIGINT);
    }
}

void func_exit()
{
	exit(0);
}

void func_ls()
{
pid_t pid;
/* fork a child process */
pid = fork();
if (pid == 0) { /* child process */
execlp("/bin/ls","ls",NULL);
}
}

void func_cat()
{
pid_t pid;
/* fork a child process */
pid = fork();
if (pid == 0) { /* child process */
//execvp(tokens[0],tokens);
}
}
/* Splits the string by space and returns the array of tokens
*
*/


char **tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;

  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
      token[tokenIndex] = '\0';
      if (tokenIndex != 0){
	tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
	strcpy(tokens[tokenNo++], token);
	tokenIndex = 0; 
      }
    } else {
      token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}


int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	int i;
	struct sigaction sigint_action;
    sigint_action.sa_handler = sigint_handler;
    sigemptyset(&sigint_action.sa_mask);
    sigint_action.sa_flags = 0;
    sigaction(SIGINT, &sigint_action, NULL);


	while(1) {			
		/* BEGIN: TAKING INPUT */
		bzero(line, sizeof(line));
		printf("$ ");
		scanf("%[^\n]", line);
		getchar();

		// printf("Command entered: %s (remove this debug output later)\n", line);
		/* END: TAKING INPUT */

		line[strlen(line)] = '\n'; //terminate with new line
		tokens = tokenize(line);
   
       //do whatever you want with the commands, here we just print them

		// printf("found token %s (remove this debug output later)\n", tokens[i]);
			if(!strcmp(tokens[0],"exit"))
			{
				func_exit();
			}
			if(!strcmp(tokens[0],"cd"))
			{
				if(tokens[1]!=NULL)
				chdir (tokens[1]);
				else
				chdir ("..");

			continue;
			}
			pid_t pid;
			pid=fork();

			if(pid==0)
			{
				execvp(tokens[0],tokens);
				exit(0);
			}
			
       
		// Freeing the allocated memory	
		for(i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);
		}
		free(tokens);

	}
	return 0;
}
