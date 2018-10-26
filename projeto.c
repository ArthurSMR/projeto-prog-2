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



Aluno *newAluno(char *nome, long int ra, char *login, char *senha){
    Aluno *aux = (Aluno*)malloc(sizeof(Aluno));
    strcpy(aux->nome, nome);
    aux->ra = ra;
    strcpy(aux->login, login);
    strcpy(aux->senha, senha);
    return aux;
}

Aluno *le(){
    char nome[100];
    long int ra;
    char login[30];
    char senha[30];
    printf("\n");
    printf("Menu Cadastro de Alunos:\n");
    printf("Digite o RA do Aluno: ");
    scanf("%ld", &ra);
    printf("Digite o Nome do Aluno:");
    scanf("%s", nome);
    printf("Digite o login:");
    scanf("%s",login);
    printf("Digite a senha:");
    scanf("%s", senha);
    return newAluno(nome,ra,login,senha);
}

void salvaAluno(Disciplina *d){
    FILE *fp;
    fp = fopen("Alunos.txt", "w");
    fprintf(fp,"%d\n", d->top);
    for(int aluno=0;aluno<d->top;aluno++){
        fprintf(fp,"%ld,%s,%s,%s\n", d->v[aluno]->ra, d->v[aluno]->nome, d->v[aluno]->login, d->v[aluno]->senha);
    }
    fclose(fp); 
}

Disciplina * carregaD(){
    FILE *fp;
    Disciplina *d;
    d = (Disciplina*)malloc(sizeof(Disciplina));
    fp = fopen("Alunos.txt", "r"); //le o que tem no txt
    fscanf(fp, "%ld", &d->top);
    for(int aluno=0; aluno<d->top; aluno++){
        d->v[aluno] = newAluno("a",0,"a","a");
        fscanf(fp, "%ld", &d->v[aluno]->ra);
        fgets(d->v[aluno]->nome, 100, fp);
        fgets(d->v[aluno]->login, 30, fp);
        fgets(d->v[aluno]->senha, 30, fp);

    }
    fclose(fp);
    return d;
}

/*int main(){
    FILE* fp;
    int q=1;
    Disciplina *d;
    fp = fopen("Alunos.txt","r");
    if(fp==NULL){
       //cria arquivo se nao existir
        fp = fopen("Alunos.txt","w");
        fprintf(fp,"0\n");
        fclose(fp);
    }  
    d = carregaD();

    while(q != 0){
        printf("--------MENU-------\n");
        printf("1->Cadastro aluno\n");
        printf("2->Login\n");
        printf("\nOpcao desejada: ");
        scanf("%d", &q);
        switch(q){
            case 1:
                fp = fopen("Alunos.txt", "r");
                d->v[d->top++] = le();
                salvaAluno(d);
                printf("Cadastro efetuado com sucesso!!!\n\n");
                break;

        }
    }
    return 0;
} */


int main(){
    FILE* fp;
    int ra, contador=0;
    char usuario[30], senha[30], nome[30], result[30], result2[30];
    Disciplina *d;
    if ((fp = fopen("Alunos.txt", "r")) == NULL){
        printf("Nenhum aluno previamente cadastrado\n");
    }
    while(1){
        puts("Menu Inicial\n");
        puts("Usuario: ");
        scanf("%s", usuario);
        puts("Senha: ");
        scanf("%s", senha);
        
        fscanf(fp, "%d\n", &d->top); //lendo qt de alunos
        while(contador<d->top){
            fscanf(fp, "%d", &ra);
            fscanf(fp, "%[^,]", nome);
            fscanf(fp, "%[^,]", result);
            fscanf(fp, "%[^\n]", result2);
            printf("%d, %s, %s, %s\n", ra,nome,result,result2);
            printf("%d %d\n", strcmp(usuario, result), strcmp(senha, result2) );
            /*if(strcmp(usuario, result) == 0){
                if(strcmp(senha, result2)==0){
                    printf("Login efetuado\n");
                    break;
                }
            } */
            contador++;
        }
    }
    fclose(fp);
    return 0;
}