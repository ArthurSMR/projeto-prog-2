//Igor Martins Silverio 217972
//Victor Pereira Cordeiro   206588
//Arthur Santos Machado Rodrigues   213315

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//---------------------------------------------------------------
//---------------------------------------------------------------

typedef struct Aluno
{
    char nome[100];
    int ra;
    char login[30];
    char senha[30];
} Aluno;

typedef struct Disciplina
{
    Aluno *v[200];
    int top; // numero de alunos
    int codigo, qtdCreditos;
    char nome[100];
} Disciplina;

//---------------------------------------------------------------

int validaLogin(char usuario[30], char senha[30], Disciplina *d)
{
    int loginRes = 0, cont = 0, ra, top;
    char usuarioRes[30], senhaRes[30], nome[30];
    FILE *fp;

    if ((fp = fopen("./cadastros/Alunos.txt", "r")) == NULL)
    {
        printf("Nenhum aluno previamente cadastrado\n");
    }
    fscanf(fp, "%d", &d->top);
    while (cont < d->top)
    {
        fscanf(fp, "%d", &ra);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%[^,]", nome);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%[^,]", usuarioRes);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%[^\n]", senhaRes);
        if (strcmp(usuario, usuarioRes) == 0 && strcmp(senha, senhaRes) == 0)
        {
            loginRes = 1;
            break;
        }
        cont++;
    }
    fclose(fp);
    return loginRes;
}

//---------------------------------------------------------------

Aluno *newAluno(char *nome, int ra, char *login, char *senha)
{
    Aluno *aux = (Aluno *)malloc(sizeof(Aluno));
    strcpy(aux->nome, nome);
    aux->ra = ra;
    strcpy(aux->login, login);
    strcpy(aux->senha, senha);
    return aux;
}

//---------------------------------------------------------------

Aluno *le()
{
    //le um aluno do teclado e faz um return.
    char nome[100];
    int ra;
    char login[30];
    char senha[30];
    printf("Digite o seu nome: ");
    fgets(nome, 100, stdin);
    printf("Digite seu RA: ");
    scanf("%d", &ra);
    getchar();
    printf("Digite seu Login: ");
    fgets(login, 30, stdin);
    printf("Digite sua senha: ");
    fgets(senha, 30, stdin);
    return newAluno(nome, ra, login, senha);
}

//---------------------------------------------------------------

void salvaAluno(Disciplina *d)
{
    FILE *f;
    f = fopen("./cadastros/Alunos.txt", "w");

    fprintf(f, "%d\n", d->top);
    for (int aluno = 0; aluno < d->top; aluno++)
    {
        fprintf(f, "%d,", d->v[aluno]->ra);
        fprintf(f, "%s,", d->v[aluno]->nome);
        fprintf(f, "%s,", d->v[aluno]->login);
        fprintf(f, "%s\n", d->v[aluno]->senha);
    }
    fclose(f);
}

//---------------------------------------------------------------

void ordenaRA(Disciplina *d)
{
    FILE *f;
    Aluno *aux;

    for (int i = 0; i < d->top; i++)
    {
        for (int k = 0; k < d->top - 1; k++)
        {
            if (d->v[k]->ra > d->v[k + 1]->ra)
            {
                aux = d->v[k];
                d->v[k] = d->v[k + 1];
                d->v[k + 1] = aux;
            }
        }
    }
    salvaAluno(d);
}

//---------------------------------------------------------------

int leDisciplinas(char codigoPreRequisitos[10])
{
    char nome[100], codigo[10];
    int top, credito, cont = 0;
    FILE *fp;

    if ((fp = fopen("./cadastros/PreRequisitos.txt", "r")) == NULL)
        printf("Nenhuma disciplina encontrada\n");

    fscanf(fp, "%d\n", &top);
    while (cont < top)
    {
        fscanf(fp, "%[^,]", codigo);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%[^,]", nome);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%d\n", &credito);
        if (strcmp(codigo, codigoPreRequisitos) == 0)
        {
            printf("Pre-requisito: %s \n", codigo);
        }
        cont++;
    }
    return 0;
}

//---------------------------------------------------------------

void consultaPreRequisitos(char codigoDigitado[10])
{
    char codigo[10], codigoPreRequisito[10];
    int top, cont = 0;
    FILE *fp;

    if ((fp = fopen("./cadastros/PreRequisitos.txt", "r")) == NULL)
        printf("Nenhum pre-requisito encontrado\n");

    fscanf(fp, "%d", &top);
    while (cont < top)
    {
        fscanf(fp, "%[^,]", codigo);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%[^\n]", codigoPreRequisito);
        //int a=strlen(codigo);
        //int b=strlen(codigoDigitado);
        //printf("%d %d\n",a,b);
        //printf("%s-%s\n",codigo,codigoDigitado);
        if (strcmp(codigo, codigoDigitado) == 0)
        {
            printf("Pré-requisitos: %s\n", codigoPreRequisito);
        }
        cont++;
    }
    fclose(fp);
}

//---------------------------------------------------------------

int consultaDisciplina(char codigoDigitado[10])
{
    char nome[100], codigo[10];
    int top, credito, cont = 0;
    FILE *fp;

    if ((fp = fopen("./cadastros/Disciplinas.txt", "r")) == NULL)
        printf("Nenhuma disciplina encontrada\n");

    fscanf(fp, "%d\n", &top);
    while (cont < top)
    {
        fscanf(fp, "%[^,]", codigo);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%[^,]", nome);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%d\n", &credito);
        if (strcmp(codigo, codigoDigitado) == 0)
        { //fazendo comparacao entre o codigo da disciplina e o codigoDigitado
            printf("Nome: %s\n", nome);
            printf("Quantidade de creditos: %d\n", credito);
            //chama a consultaPreRequisitos para saber os PreRequisitos
            consultaPreRequisitos(codigoDigitado);
            fclose(fp);
            return 0;
        }
        cont++;
    }
    fclose(fp);
    return 1;
}

//---------------------------------------------------------------

Disciplina *carregaD()
{
    //le o que tem no .txt
    FILE *f;
    Disciplina *d;
    int cont = 0;
    d = (Disciplina *)malloc(sizeof(Disciplina));
    f = fopen("./cadastros/Alunos.txt", "r"); //ler o que tem no dados.txt
    fscanf(f, "%d", &d->top);
    while (cont < d->top)
    {
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

//---------------------------------------------------------------

int realizaMatricula(char usuario[30], int semestre, char disciplina[10], Disciplina *d)
{
    FILE *fp;
    FILE *pont;
    int cont = 0, var = 0;
    int aux, top, credito;
    char codigo[10], nome[100];

    if ((fp = fopen("./cadastros/Disciplinas.txt", "r")) == NULL)
        printf("Nenhuma disciplina encontrada\n");

    while (cont < d->top)
    { //valida o usuario
        if (strcmp(d->v[cont]->login, usuario) == 0)
        {
            aux = d->v[cont]->ra;
            break;
        }
        cont++;
    }

    fscanf(fp, "%d", &top);
    while (var < top)
    {
        fscanf(fp, "%[^,]", codigo);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%[^,]", nome);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%d\n", &credito);
        if (strcmp(codigo, disciplina) == 0)
        {
            pont = fopen("./cadastros/AlunoDisciplina.txt", "a"); //grava no txt
            fprintf(pont, "%d,", aux);
            fprintf(pont, "%s,", disciplina);
            fprintf(pont, "%d,", semestre);
            fprintf(pont, "0,0\n");
            fclose(pont);
            fclose(fp);
            return 0;
        }
        else
            var++;
    }
    return 1;
}

//---------------------------------------------------------------

void atualizaNotaFalta()
{
    FILE *fp;
    FILE *temp;
    char codigoDigitado[10], disciplina[10];
    int nota, sem, ra, novaNota;
    float faltas, novaFalta;
    printf("Disciplina que deseja fazer a alteracao: ");
    scanf("%s", codigoDigitado);
    printf("\n");
    fp = fopen("./cadastros/AlunoDisciplina.txt", "r");
    temp = fopen("./cadastros/AlunoDisciplinaTemp.txt", "w");

    while (!feof(fp))
    { //procura todos do mesmo semestre
        fscanf(fp, "%d", &ra);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%[^,]", disciplina);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%d", &sem);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%d", &nota);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%f\n", &faltas);

        //escreve os dados em um arquivo temporario
        if (strcmp(codigoDigitado, disciplina) != 0)
        {
            fprintf(temp, "%d,", ra);
            fprintf(temp, "%s,", disciplina);
            fprintf(temp, "%d,", sem);
            fprintf(temp, "%d,%.1f\n", nota, faltas);
            
        }
        //atualiza a nota no arquivo temporario
        else{
            printf("Digite a sua nota: ");
            scanf("%d", &novaNota);
            printf("Digite sua falta: ");
            scanf("%f", &novaFalta);
            fprintf(temp, "%d,", ra);
            fprintf(temp, "%s,", disciplina);
            fprintf(temp, "%d,", sem);
            fprintf(temp, "%d,%.1f\n", novaNota, novaFalta);
            continue;
        }
    }
    fclose(fp);
    fclose(temp);
    //remove o arquivo antigo e renomeia o arquivo temporario
    remove("./cadastros/AlunoDisciplina.txt");
    rename("./cadastros/AlunoDisciplinaTemp.txt", "./cadastros/AlunoDisciplina.txt");
}

//---------------------------------------------------------------

int imprimeSemestre(char usuario[30], int semestre, Disciplina *d)
{
    FILE *fp;
    FILE *pont;
    int cont = 0, var = 0;
    int ra, sem, nota, credito, top;
    char disciplina[10], codigo[10], nome[50];
    float faltas;

    while (cont < d->top)
    { //valida o usuario
        if (strcmp(d->v[cont]->login, usuario) == 0)
        {
            break;
        }
        cont++;
    }
    fp = fopen("./cadastros/AlunoDisciplina.txt", "r");
    while (!feof(fp))
    { //procura todos do mesmo semestre
        fscanf(fp, "%d", &ra);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%[^,]", disciplina);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%d", &sem);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%d", &nota);
        fseek(fp, +1, SEEK_CUR);
        fscanf(fp, "%f\n", &faltas);
        if ((d->v[cont]->ra == ra) && (semestre == sem))
        {
            pont = fopen("./cadastros/Disciplinas.txt", "r");
            fscanf(pont, "%d\n", &top);
            var = 0;
            while (var < top)
            {
                fscanf(pont, "%[^,]", codigo);
                fseek(pont, +1, SEEK_CUR);
                fscanf(pont, "%[^,]", nome);
                fseek(pont, +1, SEEK_CUR);
                fscanf(pont, "%d\n", &credito);
                if (strcmp(codigo, disciplina) == 0)
                {
                    printf("%s - %s - Nota: %d, Faltas: %.1f\n\n", disciplina, nome, nota, faltas);
                    fclose(pont);
                    break;
                }
                var++;
            }
        }
    }
    fclose(fp);
    atualizaNotaFalta();
    return 0;
}

//---------------------------------------------------------------

int main()
{
    int loginRes = 0, opcao = -1, res, erro, semestre, disciplina;
    char usuario[30], senha[30], codigoDigitado[10];
    Disciplina *d = (Disciplina *)malloc(sizeof(Disciplina));

    while (loginRes != 1)
    {
        puts("Menu Inicial");
        puts("Usuario: ");
        scanf("%s", usuario);
        puts("Senha: ");
        scanf("%s", senha);
        loginRes = validaLogin(usuario, senha, d);
        if (loginRes == 0)
        {
            printf("Usuario ou senha incorreta!\n\n");
        }
        else
        {
            printf("Login efetuado!\n\n");
        }
    }

    d = carregaD();
    while (opcao != 0)
    {
        printf("1->Cadastro aluno\n");
        printf("2->Consulta disciplinas\n");
        printf("3->Realizar matricula\n");
        printf("4->Atualiza nota e falta\n");
        printf("0->Sair\n");
        printf("Digite a opcao:");
        scanf("%d", &opcao);
        getchar();
        switch (opcao)
        {
        case 0:
            break;
        case 1:
            d->v[d->top++] = le();
            ordenaRA(d);
            printf("Cadastro realizado com sucesso!\n");
            break;
        case 2:
            printf("\n");
            printf("Codigo da disciplina: ");
            scanf("%s", codigoDigitado);
            getchar();
            erro = consultaDisciplina(codigoDigitado);
            if (erro == 1)
            {
                printf("Disciplina nao encontrada!\n");
            }
            break;
        case 3:
            while (1)
            {
                printf("\nPara sair, digite um numero menor igual que 0\n");
                printf("Digite o semestre: \n");
                scanf("%d", &semestre);
                if (semestre <= 0)
                    break;
                printf("Digite a disciplina: \n");
                scanf("%s", codigoDigitado);
                erro = realizaMatricula(usuario, semestre, codigoDigitado, d);
                if (erro == 0)
                {
                    printf("Transacao realizada com sucesso\n");
                }
                else
                {
                    printf("Nao foi possivel realizar a matricula\n");
                }
            }
            break;
        case 4:
            printf("Digite o semestre: ");
            scanf("%d", &semestre);
            printf("\nDisciplinas: \n");
            imprimeSemestre(usuario, semestre, d);
            printf("Alteracoes realizadas!\n");
            break;
        }
    }

    return 0;
}
