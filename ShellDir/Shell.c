#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include <fcntl.h>
#include <unistd.h>
#define MAXLINE 100

char *commands[100] , *argv[100]/*, *delete[3]*/;
/*char *d1="rm";
delete[0]=d1;
delete[2]=NULL;*/
int main()
{
    char buf[MAXLINE];
    size_t characters;
    int status;
    pid_t pid;
    printf("%%");
    fflush(stdin);



    while(1)
	{
	    while(fgets(buf, MAXLINE, stdin)!=NULL)
        {
		    int pipeop = 0,count;
		    int i = 0;
		    for(i=0;i<strlen(buf)-1;i++)
		    {
			if(buf[i] == '|')
			    pipeop++;
		    }
		    buf[strlen(buf)-1] = 0;
		    
		    pid = fork();
            i=0;
		    if(pid==0)
		    {	
			    int flag=0,fd;
			    if(!pipeop)
   			    {
					struct stat finfo;
					
					count = StringParse(buf, " ", commands);
			        if(!strcmp(commands[0],"cd"))
			        {
						if(commands[1]==NULL){
							chdir("/home");
						}
						else
			            	chdir(commands[1]);
			        }
			        else if((count>2)&&(!strcmp(commands[count-2],">>") || !strcmp(commands[count-2],">")))
			        {
			            if(commands[count -2] == ">>")
   			                flag =0;
                        else
		                    flag =1;
		                if(flag == 0)
						    {
	                            fd = open(commands[count-1], O_WRONLY | O_CREAT | O_APPEND , 0600);
								fstat(fd, &finfo);
								off_t filesize = finfo.st_size;
								lseek(fd, filesize, SEEK_CUR);
						    }
		                else
						{
							/*delete[1]=commands[count-1];
							execvp(delete[0],delete);*/
		                    fd = open(commands[count-1], O_WRONLY | O_CREAT , 0666);
						}
		                commands[count-2] = 0;
		                dup2(fd,fileno(stdout));
		                execvp(commands[0], commands);
		            }

			
		    	    else
			        {
		                int status = execvp(commands[0], commands);
		                if(status < 0)
                        {
		                    printf("Unable to run command");
			                exit(1); 
			            }
 			        }
		        }
				else
				{
					count = StringParse(buf,"|",argv);
					PipeExecution(count)-1;
				}
		    }
		    else if(pid<0)
			{
		        printf("Child process can't be created");
		        exit(1);
		    }
		    else
			{
		        wait(NULL);
		    }
			printf("%%");
		}
	}
    exit(0);
    return(0);
}

int StringParse(char *buf, char * deliminator, char **commands)
{
	int i=0;
        char* token = strtok(buf,deliminator);
        int count =0;
	while (token != NULL) {
	    count++;
            commands[i++] = token; 
            token = strtok(NULL, deliminator); 
    	}
	commands[i] = NULL;
	return count;
}


void PipeExecution(int No_OF_Pipes){
	int i = 0;
	char *temp1 = "TEMP1.txt";
	char *temp2 = "Temp2.txt";
	StringParse(argv[0], " ", commands);
	int fd = open(temp1, O_WRONLY | O_CREAT , 0666);
	dup2(fd,fileno(stdout));
	execvp(commands[0], commands);
	return;
}
