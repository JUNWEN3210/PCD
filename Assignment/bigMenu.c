#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#pragma warning(disable:4996)

void logo();

void main()
{
	

	int choose,validationLogin;
	char functionSelect, conSelect;

	system("cls");
	
	logo();
	login();
	

	do
	{
	system("cls");
	logo();
	printf(" ===========================\n");
	printf("|       Select Module       |\n");
	printf(" ===========================\n");
	printf("|E = staff module           |\n");
	printf("|M = member module          |\n");
	printf("|S = sales module           |\n");
	printf("|T = stock module           |\n");
	printf("|P = exit                   |\n");
	printf(" ===========================\n");
	printf("\nEnter the module you want to choose: ");
	rewind(stdin);
	scanf("%c", &functionSelect);

	functionSelect = toupper(functionSelect);

	while(functionSelect != 'E' && functionSelect != 'M' && functionSelect != 'S' && functionSelect != 'T' && functionSelect != 'P')
	{
		printf("Please choose the correct function: ");
		rewind(stdin);
		scanf("%c", &functionSelect);

		functionSelect = toupper(functionSelect);
	}

	

		if (functionSelect == 'E')
		{
			selectStaff();
		}

		else if (functionSelect == 'M')
		{
			memberMenu();
		}
		else if (functionSelect == 'S')
		{
			salesMenu();
		}
		else if (functionSelect == 'T')
		{
			selectStock();
		}
		else 
		{
			exit(-1);
		}

		system("cls");

		printf("\nBack to module selection?(Y = continue , E = exit): ");
		rewind(stdin);
		scanf("%c", &conSelect);
		conSelect = toupper(conSelect);

		while (conSelect != 'Y' && conSelect != 'E')
		{
			printf("\nPlease enter valid answer, Do you want to continue (Y = continue , E = exit): ");
			rewind(stdin);
			scanf("%c", &conSelect);

			conSelect = toupper(conSelect);
		}

	} while (conSelect != 'E');

	printf("thanks for using!!!!!");
}

void logo()
{
	printf("MMMMMMMM               MMMMMMMM     &&&&&&&&&&    HHHHHHHHH     HHHHHHHHH\n");
	printf("M:::::::M             M:::::::M    &::::::::::&   H:::::::H     H:::::::H\n");
	printf("M::::::::M           M::::::::M   &::::&&&:::::&  H:::::::H     H:::::::H\n");
	printf("M:::::::::M         M:::::::::M  &::::&   &::::&  HH::::::H     H::::::HH\n");
	printf("M::::::::::M       M::::::::::M  &::::&   &::::&    H:::::H     H:::::H  \n");
	printf("M:::::::::::M     M:::::::::::M   &::::&&&::::&     H:::::H     H:::::H  \n");
	printf("M:::::::M::::M   M::::M:::::::M   &::::::::::&      H::::::HHHHH::::::H  \n");
	printf("M::::::M M::::M M::::M M::::::M    &:::::::&&       H:::::::::::::::::H  \n");
	printf("M::::::M  M::::M::::M  M::::::M  &::::::::&   &&&&  H:::::::::::::::::H  \n");
	printf("M::::::M   M:::::::M   M::::::M &:::::&&::&  &:::&  H::::::HHHHH::::::H  \n");
	printf("M::::::M    M:::::M    M::::::M&:::::&  &::&&:::&&  H:::::H     H:::::H  \n");
	printf("M::::::M     MMMMM     M::::::M&:::::&   &:::::&    H:::::H     H:::::H  \n");
	printf("M::::::M               M::::::M&:::::&    &::::&  HH::::::H     H::::::HH\n");
	printf("M::::::M               M::::::M&::::::&&&&::::::&&H:::::::H     H:::::::H\n");
	printf("M::::::M               M::::::M &&::::::::&&&::::&H:::::::H     H:::::::H\n");
	printf("MMMMMMMM               MMMMMMMM   &&&&&&&&   &&&&&HHHHHHHHH     HHHHHHHHH\n\n\n");

	printf("=========================================================================\n\n\n");
}

