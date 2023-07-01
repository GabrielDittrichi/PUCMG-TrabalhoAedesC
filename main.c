#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 100
#define MAX_PASSAGEIROS 10

typedef struct {
  char cpf[MAX_STRING];
  char nome[MAX_STRING];
  char endereco[MAX_STRING];
  char telefone[MAX_STRING];
  char numeroPassagem[MAX_STRING];
  char numeroPoltrona[MAX_STRING];
  char numeroVoo[MAX_STRING];
  char horario[MAX_STRING];
} Passageiro;

int readFile(char filePath[], Passageiro passageiros[], int passageirosCount) {
  FILE *txtPassageiros = fopen(filePath, "r");

  char linha[MAX_STRING];
  passageirosCount = 0;

  while (fgets(linha, MAX_STRING, txtPassageiros)) {
    if (linha[0] == '\n' && passageirosCount <= MAX_PASSAGEIROS - 1) {
      (passageirosCount)++;
    } else {
      char dado[MAX_STRING], valor[MAX_STRING];
      scanf(linha, "%[^:]: %[^\n]", dado, valor);

      if (strcmp(dado, "CPF") == 0) {
        strcpy(passageiros[passageirosCount].cpf, valor);
      } else if (strcmp(dado, "Nome") == 0) {
        strncpy(passageiros[passageirosCount].nome, valor, MAX_STRING - 1);
      } else if (strcmp(dado, "Endereco") == 0) {
        strncpy(passageiros[passageirosCount].endereco, valor, MAX_STRING - 1);
      } else if (strcmp(dado, "Telefone") == 0) {
        strncpy(passageiros[passageirosCount].telefone, valor, MAX_STRING - 1);
      } else if (strcmp(dado, "Numero da Passagem") == 0) {
        strncpy(passageiros[passageirosCount].numeroPassagem, valor,
                MAX_STRING - 1);
      } else if (strcmp(dado, "Numero da Poltrona") == 0) {
        strncpy(passageiros[passageirosCount].numeroPoltrona, valor,
                MAX_STRING - 1);
      } else if (strcmp(dado, "Numero do Voo") == 0) {
        strncpy(passageiros[passageirosCount].numeroVoo, valor, MAX_STRING - 1);
      } else if (strcmp(dado, "Horario") == 0) {
        strncpy(passageiros[passageirosCount].horario, valor, MAX_STRING - 1);
      }
    }
  }

  fclose(txtPassageiros);

  return passageirosCount;
}

void setFile(char filePath[], Passageiro passageiros[], int numeroPassageiros) {
  FILE *file = fopen(filePath, "w");
  if (file == NULL) {
    printf("Erro.\n");
    return;
  }

  for (int i = 0; i < numeroPassageiros; i++) {
    if (strcmp(passageiros[i].cpf, "\0") == 0) {
      return;
    }
    fprintf(
        file,
        "CPF: %s\nNome: %s\nEndereco: %s\nTelefone: %s\nNumero da Passagem: "
        "%s\nNumero da Poltrona: %s\nNumero do Voo: %s\nHorario: %s\n\n",
        passageiros[i].cpf, passageiros[i].nome, passageiros[i].endereco,
        passageiros[i].telefone, passageiros[i].numeroPassagem,
        passageiros[i].numeroPoltrona, passageiros[i].numeroVoo, passageiros[i].horario);
  }

  fclose(file);
}

int buscarPassageiroPorNome(Passageiro passageiros[], int numeroPassageiros, char nomeBusca[]) {
  for (int i = 0; i < numeroPassageiros; i++) {
    if (strcmp(passageiros[i].nome, nomeBusca) == 0) {
      return i;
    }
  }

  return -1;
}

int main() {
  Passageiro passageiros[MAX_PASSAGEIROS];
  int numeroPassageiros = 0;
  char tpvoo[MAX_STRING];

  printf("Digite o codigo do voo:\n 1. BH-RIO\n 2. BH-SP\n 3. BH-BRASILIA\n ");
  scanf("%s", tpvoo);

  char filePath[MAX_STRING];
  snprintf(filePath, sizeof(filePath), "%s.txt", tpvoo);

  numeroPassageiros = readFile(filePath, passageiros, numeroPassageiros);

  int opcao;
  do {
    printf("\nSelecione uma opcao:\n");
    printf("1. Listar passageiros\n");
    printf("2. Buscar passageiro por CPF\n");
    printf("3. Buscar passageiro por nome\n");
    printf("4. Adicionar passageiro\n");
    printf("5. Remover passageiro\n");
    printf("6. Mostrar lista de espera\n");
    printf("9. Sair\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
      case 1:
        printf("\nLista de passageiros:\n");
        for (int i = 0; i < numeroPassageiros; i++) {
          printf("CPF: %s\nNome: %s\nEndereco: %s\nTelefone: %s\nNumero da "
                 "Passagem: %s\nNumero da Poltrona: %s\nNumero do Voo: %s\n"
                 "Horario: %s\n\n",
                 passageiros[i].cpf, passageiros[i].nome,
                 passageiros[i].endereco, passageiros[i].telefone,
                 passageiros[i].numeroPassagem, passageiros[i].numeroPoltrona,
                 passageiros[i].numeroVoo, passageiros[i].horario);
        }
        break;
      case 2:
        printf("\nDigite o CPF do passageiro: ");
        char cpfPesquisar[MAX_STRING];
        scanf("%s", cpfPesquisar);

        for (int i = 0; i < numeroPassageiros; i++) {
          if (strcmp(passageiros[i].cpf, cpfPesquisar) == 0) {
            printf("\nPassageiro encontrado:\n");
            printf("CPF: %s\nNome: %s\nEndereco: %s\nTelefone: %s\nNumero da "
                   "Passagem: %s\nNumero da Poltrona: %s\nNumero do Voo: %s\n"
                   "Horario: %s\n\n",
                   passageiros[i].cpf, passageiros[i].nome,
                   passageiros[i].endereco, passageiros[i].telefone,
                   passageiros[i].numeroPassagem, passageiros[i].numeroPoltrona,
                   passageiros[i].numeroVoo, passageiros[i].horario);
            break;
          }
        }
        break;
      case 3:
        printf("\nDigite o nome do passageiro: ");
        char nomeBusca[MAX_STRING];
        scanf(" %[^\n]", nomeBusca);

        int index = buscarPassageiroPorNome(passageiros, numeroPassageiros, nomeBusca);

        if (index != -1) {
          printf("\nPassageiro encontrado:\n");
          printf("CPF: %s\nNome: %s\nEndereco: %s\nTelefone: %s\nNumero da "
                 "Passagem: %s\nNumero da Poltrona: %s\nNumero do Voo: %s\n"
                 "Horario: %s\n\n",
                 passageiros[index].cpf, passageiros[index].nome,
                 passageiros[index].endereco, passageiros[index].telefone,
                 passageiros[index].numeroPassagem, passageiros[index].numeroPoltrona,
                 passageiros[index].numeroVoo, passageiros[index].horario);
        } else {
          printf("\nPassageiro inexistente.\n");
        }
        break;
      case 4:
        if (numeroPassageiros >= MAX_PASSAGEIROS) {
          printf("\nLimite de maximo passageiros excedido.\n");
          break;
        }

        printf("\nDigite os dados do passageiro:\n");
        printf("CPF: ");
        scanf("%s", passageiros[numeroPassageiros].cpf);
        printf("Nome: ");
        scanf(" %[^\n]", passageiros[numeroPassageiros].nome);
        printf("Endereco: ");
        scanf(" %[^\n]", passageiros[numeroPassageiros].endereco);
        printf("Telefone: ");
        scanf( "%s", passageiros[numeroPassageiros].telefone);
        printf("Numero da Passagem: ");
        scanf( "%s", passageiros[numeroPassageiros].numeroPassagem);
        printf("Numero da Poltrona: ");
        scanf( "%s", passageiros[numeroPassageiros].numeroPoltrona);
        printf("Numero do Voo: ");
        scanf( "%s", passageiros[numeroPassageiros].numeroVoo);
        printf("Horario: ");
        scanf( "%s", passageiros[numeroPassageiros].horario);

        numeroPassageiros++;
        printf("\nPassageiro adicionado.\n");
        break;
      case 5:
        printf("\nDigite o CPF do passageiro que deseja deletar: ");
        char cpfDelete[MAX_STRING];
        scanf("%s", cpfDelete);

        int passageirosDelete = -1;
        for (int i = 0; i < numeroPassageiros; i++) {
          if (strcmp(passageiros[i].cpf, cpfDelete) == 0) {
            passageirosDelete = i;
            break;
          }
        }

        if (passageirosDelete != -1) {
          for (int i = passageirosDelete; i < numeroPassageiros - 1; i++) {
            passageiros[i] = passageiros[i + 1];
          }
          numeroPassageiros--;
          printf("\nPassageiro deletado.\n");
        } else {
          printf("\nPassageiro inexiste.\n");
        }
        break;
      case 6:
        printf("\nLista de espera:\n");
        for (int i = numeroPassageiros; i < MAX_PASSAGEIROS; i++) {
          printf("CPF: %s\nNome: %s\nEndereco: %s\nTelefone: %s\nNumero da "
                 "Passagem: %s\nNumero da Poltrona: %s\nNumero do Voo: %s\n"
                 "Horario: %s\n\n",
                 passageiros[i].cpf, passageiros[i].nome,
                 passageiros[i].endereco, passageiros[i].telefone,
                 passageiros[i].numeroPassagem, passageiros[i].numeroPoltrona,
                 passageiros[i].numeroVoo, passageiros[i].horario);
        }
        break;
      case 9:
        printf("\nEncerrando o programa.\n");
        break;
      default:
        printf("\nOpcao invalida.\n");
        break;
    }
  } while (opcao != 9);

  setFile(filePath, passageiros, numeroPassageiros);

  return 0;
}
