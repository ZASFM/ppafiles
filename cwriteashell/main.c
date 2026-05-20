#include <main.h>
#include <stdio.h>

//Size of builtin functions array, note, this shell, for the sake of simplicity, only takes 3 command, [cd, help, exit]
int lsh_num_builtins(){
   return sizeof(builtin_str)/sizeof(char *);
}


/*---BUILTIN FUNCTIONS IMPLEMENTATIONS---*/
int lsh_cd(char ** args){
   if(args[1]==NULL){
       fprintf(stderr,"unexpected argument to /cd");
   }else{
      if(chdir(args[1])!=0){
         perror("lsh-cd, error");
      }
   }
   return 1;
}

int lsh_help(char ** args){
   int i=0;

   printf("--- SHELL PROMPT --- \n");
   printf("Type command and args, then hit enter.\n");
   printf("Following builtin functions are available: \n");

   for (; i<lsh_num_builtins; i++){
      printf("%s \n", builtin_str[i]);
   }

   printf("Use man for more info.\n");
   return 1;
}

int lsh(char ** args){
   return 0;
}
/*---BUILTIN FUNCTIONS IMPLEMENTATIONS---*/

//note, while duplicateing the "Init" process via sys.fork(), child processes return 0.
//for parent process, the PID of child process will be returned.
int lsh_launch(char ** args){
   pid_t pid, wpid;
   int status;

   pid=fork();
   if(pid == 0){
      //this is the case of being in the child process
      if(execvp(args[0],args) == -1){
         perror("Unable to run new program on child process");
      }
      exit(EXIT_FAILURE);
   }else if(pid < 0){    
      //this is the case of noe being able to duplicate parent process
      perror("Unable to create new process");
   }else{
      //this is the case of being the in parent process
      do {
         wpid = waitpid(pid, &status, WUNTRACED);
      } while (!WIFEXITED(status) && !WIFSIGNALED(status));
   }
   return 1;
}

char * lsh_read_line(){
   int pos=0; int c; int buffersize = LSH_RL_BUFSIZE;
   //string holding the command, later to be parsed
   char * buffer = malloc(sizeof(char) * LSH_RL_BUFSIZE);

   if(buffer == NULL) return fprintf(stderr,"Unable to allocate buffer for input command");
   
   while(1){
      c=getchar();
      if(c == EOF || c == "\n"){
         //string must end with the /0 string
         buffer[pos]="/0";
         return buffer;
      }else{
         buffer[pos]=c;
      }
      pos++;

      //since, we can not predict the size of the command, first we allocate a string of 1024 Bytes.
      //If command surpasses that size, we increment the size of buffer, and double it.
      if(pos>=buffersize){
         buffersize+=LSH_RL_BUFSIZE;
         buffer=realloc(buffer,buffersize);
         if(buffer == NULL) return fprintf(stderr,"Unable to allocate more space for this command");
      }
   }
}

char ** lsh_split_line(char * line){
   int bufferSize = LSH_TOK_BUFSIZE; int pos = 0;
   //hold the complete array of the parsed command, which is an array of strings.
   char ** tokens = malloc(sizeof(char *) * LSH_TOK_BUFSIZE);
   //token used for tokenization
   char * token;

   if(tokens == NULL) return fprintf(stderr,"Unable to allocate space for parsing command");

   while(token != NULL){
      tokens[pos]=token;
      pos++;

      //since, we can not predict the size of the command, first we allocate a string of 64 Bytes.
      //If command surpasses that size, we increment the size of buffer, and double it.
      if(pos>bufferSize){
         bufferSize+=LSH_TOK_BUFSIZE;
         tokens=realloc(tokens, bufferSize * sizeof(char *));
         if(tokens == NULL) return fprintf(stderr,"Unable to allocate more space for parsing command");
      }
      token = strtok(NULL, LSH_TOK_DELIM);
   }

   tokens[pos]=NULL;
   return tokens;
}

int lsh_execute(char ** args){
   int i;
   //in case of an empty command
   if(args[0]==NULL) return 1;

   for(; i<lsh_num_builtins; i++){
      if(strcmp(args[0],builtin_str[i]) ==0 ){
         return (* builtin_funcs[i])(args);
      }
   }

   return lsh_execute(args);
}

void lsh_loop(){
   char * line;
   char ** args;
   int status;

   do{
      line=lsh_read_line();
      args=lsh_split_line(line);
      status=lsh_execute(args);

      free(line);
      free(args);
   }while(status);
}


int main(int argc, char ** argv){
   //LOAD CONFIG FILES, note this shell program has none for sake of simplicity
   /*MAKE YOUR IMPLEMENTATION HERE IF YOU WANT TO BUILD ON TOP OF THIS*/

   //RUN COMMAND LOOP: READ->PARSE->EXECUTE
   lsh_loop();

   //CLEAN UP + TERMINATE, note this shell program has none either, for sake of simplicity
   /*MAKE YOUR IMPLEMENTATION HERE IF YOU WANT TO BUILD ON TOP OF THIS*/

   return EXIT_SUCCESS;
}