#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno{
    char nome[100];
    long int ra;
    char login[30];
    char senha[30];
}Aluno;

typedef struct Disciplina{
    Aluno *v[200];
    int top; // numero de alunos
}Disciplina;

int validaLogin(char usuario[30], char senha[30], Disciplina *d){    
    
    int loginRes = 0, cont = 0, ra, top;
    char usuarioRes[30], senhaRes[30], nome[30];
    FILE* fp;
    
    if ((fp = fopen("./cadastros/Alunos.txt", "r")) == NULL){
        printf("Nenhum aluno previamente cadastrado\n");        
    }    

    fscanf(fp, "%d", &d->top);

    while(cont < d->top){
        fscanf(fp, "%d", &ra);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%[^,]", nome);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%[^,]", usuarioRes);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%[^\n]", senhaRes);            
        
        if(strcmp(usuario, usuarioRes) == 0 && strcmp(senha, senhaRes) == 0){                
            loginRes = 1;
            break;
        }
        cont++;
    }        
    fclose(fp);
    return loginRes;
}

int main(){        
    int loginRes = 0;
    char usuario[30], senha[30];
    Disciplina *d = (Disciplina *)malloc(sizeof(Disciplina));

    while(loginRes != 1){        
        puts("Menu Inicial");
        puts("Usuario: ");
        scanf("%s", usuario);
        puts("Senha: ");
        scanf("%s", senha);

        loginRes = validaLogin(usuario, senha, d);
        if(loginRes == 0){
            printf("Usuario ou senha incorreta\n");            
        }else{
            printf("Login efetuado\n");
        }        
    }
    
    return 0;
}