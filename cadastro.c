#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_RA 15
#define MAX_DATA 11 
#define MAX_TELEFONE 16 
#define MAX_EMAIL 100
#define MAX_CURSO 50 
#define MAX_SEMESTRE 20
#define MAX_AREA 50
#define MAX_COMENTARIOS 301
#define MAX_USUARIOS 100
#define ARQUIVO_DADOS "dados_uniwork.dat" 



typedef struct {
    int id; 
    char nome[MAX_NOME];
    char ra[MAX_RA];
    char data_nascimento[MAX_DATA];
    char telefone[MAX_TELEFONE];
    char email[MAX_EMAIL];

} Usuario;

Usuario lista_usuarios[MAX_USUARIOS];
int total_usuarios = 0;


void ler_string(char *dest, int max_len, const char *prompt) {
    printf("%s", prompt);

    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    

    if (fgets(dest, max_len, stdin) != NULL) {

        dest[strcspn(dest, "\n")] = 0;
    } else {
        dest[0] = '\0'; 
    }
}


void carregar_dados() {
    FILE *file = fopen(ARQUIVO_DADOS, "rb");
    if (file != NULL) {
        total_usuarios = fread(lista_usuarios, sizeof(Usuario), MAX_USUARIOS, file);
        printf("\n=> %d usuarios carregados de %s.\n", total_usuarios, ARQUIVO_DADOS);
        fclose(file);
    } else {
        total_usuarios = 0;
        printf("\n=> Arquivo de dados nao encontrado. Iniciando com 0 usuarios.\n");
    }
}


void salvar_dados() {
    FILE *file = fopen(ARQUIVO_DADOS, "wb");
    if (file != NULL) {
        fwrite(lista_usuarios, sizeof(Usuario), total_usuarios, file);
        printf("=> Dados salvos com sucesso em %s.\n", ARQUIVO_DADOS);
        fclose(file);
    } else {
        printf("=> ERRO: Nao foi possivel salvar os dados no arquivo.\n");
    }
}


void cadastrar_novo(Usuario novo) {
    if (total_usuarios < MAX_USUARIOS) {
        novo.id = total_usuarios + 1; 
        lista_usuarios[total_usuarios] = novo;
        total_usuarios++;
        salvar_dados(); 
        printf("\n✅ Usuario %s (RA: %s) cadastrado com sucesso!\n", novo.nome, novo.ra);
    } else {
        printf("\n❌ ERRO: Limite maximo de usuarios atingido.\n");
    }
}


Usuario ler_dados_do_usuario() {
    Usuario novo_usuario;
    
    printf("\n============================================\n");
    printf("         SISTEMA DE CADASTRO UNIWORK\n");
    printf("============================================\n");


    ler_string(novo_usuario.nome, MAX_NOME, "1. Nome Completo: ");
    ler_string(novo_usuario.ra, MAX_RA, "2. Registro Academico (RA): ");
    ler_string(novo_usuario.data_nascimento, MAX_DATA, "3. Data de Nascimento (DD/MM/AAAA): ");
    ler_string(novo_usuario.telefone, MAX_TELEFONE, "4. Telefone: ");
    ler_string(novo_usuario.email, MAX_EMAIL, "5. E-mail: ");
    
    return novo_usuario;
}


int main() {

    carregar_dados();

    Usuario dados_do_formulario = ler_dados_do_usuario();

    cadastrar_novo(dados_do_formulario);
    
    printf("\n\n--- FIM DA EXECUCAO ---\n");
    printf("Pressione ENTER para fechar...");
    getchar(); 
    
    return 0;
}