#include "menus.h"
#include <stdio.h>
#include <stdlib.h>

//Menu principal
int menu()
{
	printf("0. Sair\n");
	printf("1. Bruxo\n");
	printf("2. Paciente\n");
	printf("3. Pocao\n");
	printf("4. Tratamento\n");
	int opcao_menu;
	scanf("%d", &opcao_menu);
	return opcao_menu;
}
//Submenu para bruxo, paciente, pocao
int submenu()
{
	printf("0. Sair\n");
	printf("1. Listar\n");
	printf("2. Cadastrar\n");
	printf("3. Alterar\n");
	printf("4. Excluir\n");
	int opcao_submenu;
	scanf("%d", &opcao_submenu);
	return opcao_submenu;
}
//Submenu para tratamento
int submenu_tratamento()
{
	printf("0. Sair\n");
	printf("1. Listar tratamentos do paciente\n");
	printf("2. Listar tratamentos do bruxo\n");
	printf("3. Iniciar tratamento\n");
	printf("4. Ampliar tratamento\n");
	printf("5. Excluir tratamento\n");
	int opcao_tratamento;
	scanf("%d", &opcao_tratamento);
	return opcao_tratamento;
}
//Validação de opções dos menus e submenus
int validarOpcao (int opcao, int min, int max)
{
	if(opcao<min || opcao>max)
	{
		printf("\nOpcao inexistente!\n\n");
		return 0;
	}
	return 1;
}

//Listar

