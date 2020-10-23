# Shell

Esse programa consiste em uma implementação de uma Shell utilizando as system calls (Fork , Exec e Wait) do sistema unix. Apartir de um dado fornecido , o comando é interpretado por um parser e passado como argumento para a rotina exec() do processo filho , criado a partir de uma system call fork() , a partir dai o processo pai usa wait() para experar a execução do processo filho. 

Existem 3 comandos built in na Shell , cd para navegar pelos diretórios , de4d-exit para navegar sair da Shell , de4d-help para receber ajudar . 
