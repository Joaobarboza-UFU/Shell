#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/wait.h>
#define SIZEOF_MASTER (sizeof(char) * 128)

int flag = 0;

char* usuario;

char* builtin_cmd[] = {
    "cd",
    "de4d-help",
    "de4d-exit"
};

void de4d_help(){
    printf("Há 3 comandos built in na Shell\n");
    printf("cd para navegar pelos diretórios\n");
    printf("de4d-exit para navegar sair da Shell\n");
    printf("de4d-help para receber ajudar\n");

}

char* replace_char(char* str, char antigo, char novo){
    char *pos = strchr(str,antigo);
    while (pos){
        *pos = novo;
        pos = strchr(pos,antigo);
    }
    return str;
}

int fork_and_exec(char **args){
    pid_t process;
    process = fork();

    if (process == -1){
        printf("Erro ,  failed to fork");
        return 2;
    }
    if ( process == 0) {
        execvp(args[0] , args);
        printf("\033[1;31m");
        printf("EXECECUTION ERROR , INPUT IS NOT VALID\n");
        printf("\033[0m");
        return 0;
    }
    if (process > 0){
        int status;
        waitpid(process , &status, 0);
    }
    return 0;
}

int parsing(char *commando ){
    int i = 0;
    char ** tokens = malloc(sizeof(SIZEOF_MASTER));
    char *token = malloc(sizeof(SIZEOF_MASTER));
    if(strlen(commando) == 1){
        free(token);
        free(tokens);
        return 2;
    }
    replace_char(commando , '\n' , '\0');
    token = strtok(commando, " ");
    while( token != NULL ) {
        tokens[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    tokens[i] = NULL;
    if(strcmp(tokens[0],builtin_cmd[2]) == 0){
        flag = 1;
        return 0;
    }
    else if(strcmp(tokens[0],builtin_cmd[1]) == 0){
        de4d_help();
        return 0;
    }
    else if(strcmp(tokens[0],builtin_cmd[0]) == 0){
        chdir(tokens[1]);
        return 0;
    }
    else{
        fork_and_exec(tokens);
    }
    free(token);
    free(tokens);
    return 0;
}

int shell_loop(){

    do{
        char *directory = malloc(SIZEOF_MASTER);
        char *command = malloc(SIZEOF_MASTER);
        int k = 0;
        int c;
        getcwd(directory ,(SIZEOF_MASTER));
        printf("@%s -> " , usuario);
        printf("%s" , directory);
        printf(" (De4dl0ck Sh3ll) $ ");
        fgets(command,SIZEOF_MASTER,stdin);
        parsing(command); //Tomar o que o usuário escrever , separar , avaliar e chamar rotinas usando exec , caso o comando seja cd , exit ou help , chamar funcoes.
        free(directory);
        free(command);

    } while (flag == 0);
    return 0;
}


int main(){
    char **flags_builtin = malloc(SIZEOF_MASTER);
    char *token;
    printf("\033[1;31m");
    printf("Bem-vindo a Shell De4dl0ck \n");
    printf("Você pode executar programas da distro padrão , e utilziar os comandos cd , para mudar o diretório ,  \n");
    printf("de4d-help , para rever os comandos e de4d-exit para sair da Shell\n");
    printf("\033[0m");
    usuario = getenv("USER");
    shell_loop();
    return 0;
}
