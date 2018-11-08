#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno{
    char nome[100];
    int ra;
    char login[30];
    char senha[30];
}Aluno;

typedef struct Disciplina{
    Aluno *v[200];
    int top; // numero de alunos
    int codigo, qtdCreditos;
    char nome[100];    
}Disciplina;

int validaLogin(char usuario[30], char senha[30], Disciplina *d){    
    
    int loginRes = 0, cont = 0, ra, top;
    char usuarioRes[30], senhaRes[30], nome[30];
    FILE* fp;
    
    if ((fp = fopen("./Cadastros/Alunos.txt", "r")) == NULL){
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

Aluno * newAluno(char *nome, int ra, char *login, char *senha){
    Aluno * aux = (Aluno*)malloc(sizeof(Aluno));
    strcpy(aux->nome, nome);
    aux->ra = ra;
    strcpy(aux->login, login);
    strcpy(aux->senha, senha);
    return aux;
}
Aluno * le(){
    //le um aluno do teclado e faz um return.
    char nome[100];
    int ra;
    char login[30];
    char senha[30];
    printf("Digite o seu nome: ");
    gets(nome);
    printf("Digite seu RA: ");
    scanf("%d", &ra);
    getchar();
    printf("Digite seu Login: ");
    gets(login);
    printf("Digite sua senha: ");
    gets(senha);
    return newAluno(nome,ra,login,senha);
}


void salvaAluno(Disciplina * d){
    FILE * f;
    f = fopen("./Cadastros/Alunos.txt","w");   

    fprintf(f,"%d\n",d->top);
    for(int aluno=0;aluno<d->top;aluno++){
        fprintf(f,"%d,",d->v[aluno]->ra);
        fprintf(f,"%s,",d->v[aluno]->nome);
        fprintf(f,"%s,",d->v[aluno]->login);
        fprintf(f,"%s\n",d->v[aluno]->senha);
    }
    fclose(f);
}

int consultaDisciplinas(char codigoDigitado[10]){
    char  codigo[10], nome[100];
    int qtdCreditos, top, res = 0;
    
    FILE * f;
    f = fopen("./Cadastros/Disciplinas.txt","r");
    
    fscanf(f, "%d", &top);    
    for(int i = 0; i < top; i++){        
        fscanf(f, "%[^,]", codigo);
        fseek(f, +1, SEEK_CUR);        
        fscanf(f, "%[^,]", nome);
        fseek(f, +1, SEEK_CUR);                    
        fscanf(f, "%d\n", &qtdCreditos);         
        if(strcmp(codigo, codigoDigitado) == 0){
            printf("Nome: %s\n", nome);
            printf("Quantidade de Creditos: %d\n", qtdCreditos);
            fclose(f);
            res = 1;
            break;
            return res;
        }
    }
    fclose(f);
    return res;
}

Disciplina * carregaD()
{
//le o que tem no .txt
    FILE * f;
    Disciplina * d;
    int cont=0;
    d = (Disciplina*)malloc(sizeof(Disciplina));
    f = fopen("./Cadastros/Alunos.txt","r"); //ler o que tem no dados.txt
    fscanf(f, "%d", &d->top);
    while(cont < d->top){
        d->v[cont] = newAluno("a", 0, "a", "a");
        fscanf(f, "%d", &d->v[cont]->ra);
        fseek(f, +1, SEEK_CUR);
        fscanf(f, "%[^,]", d->v[cont]->nome);
        fseek(f, +1, SEEK_CUR);
        fscanf(f, "%[^,]", d->v[cont]->login);
        fseek(f, +1, SEEK_CUR);
        fscanf(f, "%[^\n]", d->v[cont]->senha); 
        cont++;
    }
    fclose(f); 
    return d;
}

int main(){        
    int loginRes = 0, opcao=-1;
    char usuario[30], senha[30], codigoDigitado[10];
    Disciplina *d = (Disciplina *)malloc(sizeof(Disciplina));

    while(loginRes != 1){        
        puts("Menu Inicial");
        puts("Usuario: ");
        scanf("%s", &usuario);
        puts("Senha: ");
        scanf("%s", &senha);

        loginRes = validaLogin(usuario, senha, d);
        if(loginRes == 0){
            printf("Usuario ou senha incorreta\n\n");            
        }else{
            printf("Login efetuado\n\n");
        }        
    }

    d = carregaD();
    printf("%d\n",d->top);
    while(opcao != 0){
        printf("1->Cadastro aluno\n");
        printf("2->Consulta disciplinas\n");
        printf("0->Sair\n");
        printf("Digite a opcao:");
        scanf("%d",&opcao);
        getchar();
        switch(opcao){
            case 0: break;
            case 1:
                d->v[d->top++]=le();
                salvaAluno(d);
                printf("Cadastro realizado com sucesso!\n");
                break;
            case 2:
                printf("Digite o codigo da disciplina: ");
                scanf("%s", codigoDigitado);
                int res = consultaDisciplinas(codigoDigitado);
                if(res == 0){
                    printf("Disciplina não encontrada!");
                }
                break;
        }
    }
    
    return 0;
}