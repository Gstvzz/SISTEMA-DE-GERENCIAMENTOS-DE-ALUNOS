#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 50
#define TAM_STR 50

typedef struct {
    int matricula;
    char nome[TAM_STR];
    char curso[TAM_STR];
    float nota1;
    float nota2;
} Aluno;

/* 
 * PROTÓTIPOS DAS FUNÇÕES (ETAPA II)
 * Agora utilizamos ponteiros (Aluno *vetor) para o array e (int *total) 
 * para alterar a variável original na memória.
 */
float calcularMedia(Aluno a);
int buscarAlunoPorMatricula(Aluno *vetor, int total, int matricula);
void cadastrarAluno(Aluno *vetor, int *total);
void listarAlunos(Aluno *vetor, int total);
void pesquisarAluno(Aluno *vetor, int total);
void alterarAluno(Aluno *vetor, int total);
void excluirAluno(Aluno *vetor, int *total);
void exibirSituacaoAlunos(Aluno *vetor, int total);
void estatisticasTurma(Aluno *vetor, int total);

int main() {
    Aluno alunos[MAX_ALUNOS];
    int totalAlunos = 0; 
    int opcao;

    do {
    
        printf("   SISTEMA DE GERENCIAMENTO DE ALUNOS    \n");
    
        printf("1 - Cadastrar aluno\n");
        printf("2 - Listar alunos\n");
        printf("3 - Pesquisar aluno\n");
        printf("4 - Alterar dados de um aluno\n");
        printf("5 - Excluir aluno\n");
        printf("6 - Exibir situação dos alunos\n");
        printf("7 - Estatísticas da turma\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                // Passamos o endereço de memória de totalAlunos usando '&'
                cadastrarAluno(alunos, &totalAlunos);
                break;
            case 2:
                listarAlunos(alunos, totalAlunos);
                break;
            case 3:
                pesquisarAluno(alunos, totalAlunos);
                break;
            case 4:
                alterarAluno(alunos, totalAlunos);
                break;
            case 5:
                // Passamos o endereço de memória de totalAlunos usando '&'
                excluirAluno(alunos, &totalAlunos);
                break;
            case 6:
                exibirSituacaoAlunos(alunos, totalAlunos);
                break;
            case 7:
                estatisticasTurma(alunos, totalAlunos);
                break;
            case 0:
                printf("\nA encerrar o programa...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

float calcularMedia(Aluno a) {
    return (a.nota1 + a.nota2) / 2.0;
}

int buscarAlunoPorMatricula(Aluno *vetor, int total, int matricula) {
    for (int i = 0; i < total; i++) {
        if (vetor[i].matricula == matricula) {
            return i;
        }
    }
    return -1;
}

// O parâmetro 'int *total' recebe um endereço de memória
void cadastrarAluno(Aluno *vetor, int *total) {
    // Usamos '*total' para acessar e modificar o valor guardado nesse endereço
    if (*total >= MAX_ALUNOS) {
        printf("\nErro: Limite máximo de 50 alunos atingido[cite: 1, 2]!\n");
        return;
    }

    int matriculaTemp;
    printf("\n--- Cadastrar Novo Aluno ---\n");
    printf("Digite a matrícula: ");
    scanf("%d", &matriculaTemp);
    getchar();

    if (buscarAlunoPorMatricula(vetor, *total, matriculaTemp) != -1) {
        printf("Erro: Já existe um aluno registado com esta matrícula[cite: 2]!\n");
        return;
    }

    vetor[*total].matricula = matriculaTemp;

    printf("Digite o nome do aluno: ");
    fgets(vetor[*total].nome, TAM_STR, stdin);
    vetor[*total].nome[strcspn(vetor[*total].nome, "\n")] = '\0';

    printf("Digite o curso: ");
    fgets(vetor[*total].curso, TAM_STR, stdin);
    vetor[*total].curso[strcspn(vetor[*total].curso, "\n")] = '\0';

    printf("Digite a nota da 1ª avaliação: ");
    scanf("%f", &vetor[*total].nota1);

    printf("Digite a nota da 2ª avaliação: ");
    scanf("%f", &vetor[*total].nota2);
    getchar();

    // Incrementa diretamente a variável original no main()
    (*total)++;
    printf("Aluno cadastrado com sucesso!\n");
}

void listarAlunos(Aluno *vetor, int total) {
    if (total == 0) {
        printf("\nNenhum aluno registado.\n");
        return;
    }

    printf("\n Lista de Alunos \n");
    printf("%-20s | %-6s | %-10s\n", "Nome", "Média", "Situação");
    printf("-----------------------------------------\n");
    for (int i = 0; i < total; i++) {
        float media = calcularMedia(vetor[i]);
        char *situacao = (media >= 6.0) ? "APROVADO" : "REPROVADO";
        printf("%-20s | %6.2f | %-10s\n", vetor[i].nome, media, situacao);
    }
}

void pesquisarAluno(Aluno *vetor, int total) {
    if (total == 0) {
        printf("Nenhum aluno registado.\n");
        return;
    }

    int matricula;
    printf("Digite a matrícula do aluno que deseja pesquisar: ");
    scanf("%d", &matricula);
    getchar();

    int index = buscarAlunoPorMatricula(vetor, total, matricula);
    if (index == -1) {
        printf("Aluno com a matrícula %d não encontrado.\n", matricula);
    } else {
        float media = calcularMedia(vetor[index]);
        printf("\n--- Dados do Aluno ---\n");
        printf("Matrícula: %d\n", vetor[index].matricula);
        printf("Nome: %s\n", vetor[index].nome);
        printf("Curso: %s\n", vetor[index].curso);
        printf("Nota 1: %.2f\n", vetor[index].nota1);
        printf("Nota 2: %.2f\n", vetor[index].nota2);
        printf("Média: %.2f\n", media);
        printf("Situação: %s\n", (media >= 6.0) ? "APROVADO" : "REPROVADO");
    }
}

void alterarAluno(Aluno *vetor, int total) {
    if (total == 0) {
        printf("\nNenhum aluno registado.\n");
        return;
    }

    int matricula;
    printf("\nDigite a matrícula do aluno cujos dados deseja alterar: ");
    scanf("%d", &matricula);
    getchar();

    int index = buscarAlunoPorMatricula(vetor, total, matricula);
    if (index == -1) {
        printf("Aluno não encontrado.\n");
        return;
    }

    printf("A alterar dados para o aluno: %s\n", vetor[index].nome);
    
    printf("Novo nome: ");
    fgets(vetor[index].nome, TAM_STR, stdin);
    vetor[index].nome[strcspn(vetor[index].nome, "\n")] = '\0';

    printf("Novo curso: ");
    fgets(vetor[index].curso, TAM_STR, stdin);
    vetor[index].curso[strcspn(vetor[index].curso, "\n")] = '\0';

    printf("Nova nota da 1ª avaliação: ");
    scanf("%f", &vetor[index].nota1);

    printf("Nova nota da 2ª avaliação: ");
    scanf("%f", &vetor[index].nota2);
    getchar();

    printf("Dados alterados com sucesso!\n");
}

void excluirAluno(Aluno *vetor, int *total) {
    if (*total == 0) {
        printf("\nNenhum aluno registado.\n");
        return;
    }

    int matricula;
    printf("\nDigite a matrícula do aluno que deseja excluir: ");
    scanf("%d", &matricula);
    getchar();

    int index = buscarAlunoPorMatricula(vetor, *total, matricula);
    if (index == -1) {
        printf("Aluno não encontrado.\n");
        return;
    }

    for (int i = index; i < *total - 1; i++) {
        vetor[i] = vetor[i + 1];
    }

    // Decrementa diretamente a variável original no main()
    (*total)--;
    printf("Aluno excluído com sucesso!\n");
}

void exibirSituacaoAlunos(Aluno *vetor, int total) {
    if (total == 0) {
        printf("\nNenhum aluno registado.\n");
        return;
    }

    printf("\n--- Situação Acadêmica dos Alunos ---\n");
    printf("%-20s | %-10s\n", "Nome", "Situação");
    printf("----------------------------------\n");
    for (int i = 0; i < total; i++) {
        float media = calcularMedia(vetor[i]);
        char *situacao = (media >= 6.0) ? "APROVADO" : "REPROVADO";
        printf("%-20s | %-10s\n", vetor[i].nome, situacao);
    }
}

void estatisticasTurma(Aluno *vetor, int total) {
    if (total == 0) {
        printf("\nNenhum aluno registado para gerar estatísticas.\n");
        return;
    }

    int aprovados = 0, reprovados = 0;
    float somaMedias = 0, maiorMedia = -1, menorMedia = 11;
    char nomeMaior[TAM_STR] = "", nomeMenor[TAM_STR] = "";

    for (int i = 0; i < total; i++) {
        float media = calcularMedia(vetor[i]);
        somaMedias += media;

        if (media >= 6.0) aprovados++;
        else reprovados++;

        if (media > maiorMedia) {
            maiorMedia = media;
            strcpy(nomeMaior, vetor[i].nome);
        }

        if (media < menorMedia) {
            menorMedia = media;
            strcpy(nomeMenor, vetor[i].nome);
        }
    }

    printf("\n--- Estatísticas da Turma ---\n");
    printf("Quantidade de alunos cadastrados: %d[cite: 2]\n", total);
    printf("Quantidade de aprovados: %d[cite: 2]\n", aprovados);
    printf("Quantidade de reprovados: %d[cite: 2]\n", reprovados);
    printf("Média geral da turma: %.2f[cite: 2]\n", somaMedias / total);
    printf("Aluno com maior média: %s (%.2f)[cite: 2]\n", nomeMaior, maiorMedia);
    printf("Aluno com menor média: %s (%.2f)[cite: 2]\n", nomeMenor, menorMedia);
}