#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

int menu();
void selectStock();
void addStock();
void searchStock();
void modifyStock();
void displayStock();
void deleteStock();
void donateStock();
void checkItemCode(char code[]);
void checkItemDesc(char desc[]);
void checkItemPrice(double price);
void checkQty(int qty);
void checkMinLvl(int minLvl);
void checkReorderQty(int reorderQty);

struct Stock {
	char itemCode[6];          // Item code
	char itemDesc[30];         // Item description
	double itemPrice;          // Item price
	int qty;                   // Quantity in Stock
	int minLvl;                // Minimum Level
	int reorderQty;            // Reorder Quantity

};

void selectStock() {
	int choice;
	char nextFunc;

	system("cls");

	printf("\n");
	printf("  /$$$$$$  /$$$$$$$$ /$$$$$$   /$$$$$$  /$$   /$$       /$$      /$$  /$$$     /$$   /$$\n");
	printf(" /$$__  $$|__  $$__//$$__  $$ /$$__  $$| $$  /$$/      | $$$    /$$$ /$$ $$   | $$  | $$\n");
	printf("| $$  \\__/   | $$  | $$  \\ $$| $$  \\__/| $$ /$$/       | $$$$  /$$$$|  $$$    | $$  | $$\n");
	printf("|  $$$$$$    | $$  | $$  | $$| $$      | $$$$$/        | $$ $$/$$ $$ /$$ $$/$$| $$$$$$$$\n");
	printf(" \\____  $$   | $$  | $$  | $$| $$      | $$  $$        | $$  $$$| $$| $$  $$_/| $$__  $$\n");
	printf(" /$$  \\ $$   | $$  | $$  | $$| $$    $$| $$\\  $$       | $$\\  $ | $$| $$\\  $$ | $$  | $$\n");
	printf("|  $$$$$$/   | $$  |  $$$$$$/|  $$$$$$/| $$ \\  $$      | $$ \\/  | $$|  $$$$/$$| $$  | $$\n");
	printf(" \\______/    |__/   \\______/  \\______/ |__/  \\__/      |__/     |__/ \\____/\\_/|__/  |__/\n");

	printf("\n=============================================================================================\n");

	do {
		do {
			choice = menu();
			switch (choice) {
			case 1: addStock(); break;
			case 2: searchStock(); break;
			case 3: modifyStock(); break;
			case 4: displayStock(); break;
			case 5: deleteStock(); break;
			case 6: donateStock(); break;
			case 7: ;
			default:break;
			}
		} while (choice < 1 || choice > 7);

		do {
			printf("\n\nContinue to next function ? ( Y = Yes , N = No ) : ");
			rewind(stdin);
			scanf("%c", &nextFunc);
			printf("\n");
			if (toupper(nextFunc) != 'Y' && toupper(nextFunc) != 'N')
				printf("\nInvalid choice! Only ( Y = Yes , N = No ) !\n");
		} while (toupper(nextFunc) != 'Y' && toupper(nextFunc) != 'N');

	} while (toupper(nextFunc) == 'Y');
	system("pause");

}

int menu() {
	int choice;
	char choice2[99];

	do {
		
		printf("\nSTOCK MENU\n");
		printf("==========\n");
		printf("1. Add new stock\n");
		printf("2. Search stock\n");
		printf("3. Modify stock\n");
		printf("4. Display stock\n");
		printf("5. Delete stock\n");
		printf("6. Donate stock\n");
		printf("7. Exit\n");
		printf("Enter your choice : ");

		if (scanf("%d", &choice) != 1) {
			scanf("%[^\n]", choice2);
			printf("\nError! '%s' is not a digit, enter your choice again (only 1 - 7) \n", choice2);
			choice = 0;
		}
		else if (choice < 1 || choice>7) {
			printf("\nInvalid choice!! Enter 1 - 7 only ! \n");
		}
		while (getchar() != '\n');

	} while (choice < 1 || choice > 7);

	return choice;
}

void addStock() {
	FILE* add;

	char continueAdd;
	int count = 0;
	struct Stock s[999];

	add = fopen("stock.txt", "a");

	if (add == NULL) {
		printf("Error opening file !\n");
		exit(-1);
	}
	do {
		system("cls");

		printf("     _    ____  ____    ____ _____ ___   ____ _  __\n");
		printf("    / \\  |  _ \\|  _ \\  / ___|_   _/ _ \\ / ___| |/ /\n");
		printf("   / _ \\ | | | | | | | \\___ \\ | || | | | |   | ' / \n");
		printf("  / ___ \\| |_| | |_| |  ___) || || |_| | |___| . \\ \n");
		printf(" /_/   \\_\\____/|____/  |____/ |_| \\___/ \\____|_|\\_\ \n\n");

		//printf("-------------------------------------------------------\n");

		do {
			printf("\nItem Code          : ");
			rewind(stdin);
			scanf("%s", s[count].itemCode);
			checkItemCode(s[count].itemCode);
		} while (strlen(s[count].itemCode) != 5 || s[count].itemCode[0] != 'A' || !isdigit(s[count].itemCode[1]) ||
			!isdigit(s[count].itemCode[2]) || !isdigit(s[count].itemCode[3]) || !isdigit(s[count].itemCode[4]));

		do {
			printf("\nItem Description   : ");
			rewind(stdin);
			scanf("%[^\n]", &s[count].itemDesc);
			checkItemDesc(s[count].itemDesc);
		} while (strlen(s[count].itemDesc) > 30);


		do {
			printf("\nItem Price         : ");
			rewind(stdin);
			scanf("%lf", &s[count].itemPrice);
			checkItemPrice(s[count].itemPrice);
		} while (sizeof(s[count].itemPrice) != sizeof(double) || s[count].itemPrice <= 0);


		do {
			printf("\nQuantity in Stock  : ");
			rewind(stdin);
			scanf("%d", &s[count].qty);
			checkQty(s[count].qty);
		} while ( s[count].qty <= 0);

		do {
			printf("\nMinimum Level      : ");
			rewind(stdin);
			scanf("%d", &s[count].minLvl);
			checkMinLvl(s[count].minLvl);
		} while ( s[count].minLvl <= 0);

		do {
			printf("\nReorder Quantity   : ");
			rewind(stdin);
			scanf("%d", &s[count].reorderQty);
			checkReorderQty(s[count].reorderQty);
		} while ( s[count].reorderQty <= 0);


		fprintf(add, "%s|%s|%.2lf|%d|%d|%d\n", s[count].itemCode, s[count].itemDesc, s[count].itemPrice,
			s[count].qty, s[count].minLvl, s[count].reorderQty);

		printf("\nNew stock added successfully !! \n\n");
		printf("Continue to add new stock ( Y = Yes ) ? : ");
		rewind(stdin);
		scanf("%c", &continueAdd);

		count++;

	} while (continueAdd == 'Y' || continueAdd == 'y');

	printf("\nTotal %d new stock(s) added successfully !!\n", count);
	fclose(add);
	return(-1);
}

void searchStock() {
	FILE* search;

	struct Stock ss[999];
	struct Stock s;
	int searchChoice;
	char searchCode[10], searchDesc[50], continueSearch;
	double searchPrice;
	int searchQty, searchMinLvl, searchReorderQty, records = 0;

	

	

	do {
		search = fopen("stock.txt", "r");

		if (search == NULL) {
			printf("Error opening file !\n");
			exit(-1);
		}

		int i = 0;
		while (fscanf(search, "%[^\|]|%[^\|]|%lf|%d|%d|%d\n", &s.itemCode, &s.itemDesc, &s.itemPrice,
			&s.qty, &s.minLvl, &s.reorderQty) != EOF) {
			strcpy(ss[i].itemCode, s.itemCode);
			strcpy(ss[i].itemDesc, s.itemDesc);
			ss[i].itemPrice = s.itemPrice;
			ss[i].qty = s.qty;
			ss[i].minLvl = s.minLvl;
			ss[i].reorderQty = s.reorderQty;
			i++;
		}
		fclose(search);

		system("cls");
		printf("  ___ ___   _   ___  ___ _  _   ___ _____ ___   ___ _  __\n");
		printf(" / __| __| /_\\ | _ \\/ __| || | / __|_   _/ _ \\ / __| |/ /\n");
		printf(" \\__ \\ _| / _ \\|   / (__| __ | \\__ \\ | || (_) | (__| ' < \n");
		printf(" |___/___/_/ \\_\\_|_\\____|_||_| |___/ |_| \\___/ \\___|_|\\_\\ \n\n");

		printf("-----------------------------------------------------------\n");

		printf("1. Item Code\n");
		printf("2. Item Description\n");
		printf("3. Item price\n");
		printf("4. Quantity in Stock\n");
		printf("5. Minimum Level\n");
		printf("6. Reorder Quantity\n\n");
		printf("Enter your choice : ");
		rewind(stdin);
		scanf("%d", &searchChoice);

		switch (searchChoice) {
		case 1:
		{
			do {
				printf("\nEnter your item code to search (A####) : ");
				rewind(stdin);
				scanf("%[^\n]", &searchCode);
				checkItemCode(searchCode);
			} while (strlen(searchCode) != 5 || searchCode[0] != 'A' || !isdigit(searchCode[1]) || !isdigit(searchCode[2]) || !isdigit(searchCode[3]) || !isdigit(searchCode[4]));

			printf("\nResults\n");
			printf("-------\n");

			printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
				"Item Code", "Item Description", "Item Price", "Quantity in Stock", "Minimum Level", "Reorder Quantity");
			printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
				"==========", "====================", "============", "====================", "===============", "================");

			for (int j = 0; j <= i; j++) {

				if (strcmp(searchCode, ss[j].itemCode) == 0) {
					
					printf("%-10s | %-20s | %-12.2f | %-20d | %-15d | %-16d\n", ss[j].itemCode,ss[j].itemDesc, ss[j].itemPrice,
						ss[j].qty, ss[j].minLvl, ss[j].reorderQty);

					records++;
				}

				
			}
			if (records < 1) {
				printf("\n [ No Records Found ] \n");
			}
		}
		break;

		case 2:
			do {
				printf("\nEnter your item description to search : ");
				rewind(stdin);
				scanf("%[^\n]", &searchDesc);
				checkItemDesc(searchDesc);
			} while (strlen(searchDesc) > 30);

			printf("\nResults\n");
			printf("-------\n");
			printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
				"Item Code", "Item Description", "Item Price", "Quantity in Stock", "Minimum Level", "Reorder Quantity");
			printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
				"==========", "====================", "============", "====================", "===============", "================");

			for (int j = 0; j <= i; j++) {

				if (strcmp(searchDesc, ss[j].itemDesc) == 0) {
					
					printf("%-10s | %-20s | %-12.2f | %-20d | %-15d | %-16d\n", ss[j].itemCode, ss[j].itemDesc, ss[j].itemPrice,
						ss[j].qty, ss[j].minLvl, ss[j].reorderQty);
					records++;
				}
			}
			if (records < 1) {
				printf("\n [ No Records Found ] \n");
			}
			break;

		case 3:
			do {
				printf("\nEnter your item price to search : ");
				rewind(stdin);
				scanf("%lf", &searchPrice);
				checkItemPrice(searchPrice);
			} while (sizeof(searchPrice) != sizeof(double) || searchPrice <= 0);

			printf("\nResults\n");
					printf("-------\n");
					printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
						"Item Code", "Item Description", "Item Price", "Quantity in Stock", "Minimum Level", "Reorder Quantity");
					printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
						"==========", "====================", "============", "====================", "===============", "================");

			for (int j = 0; j <= i; j++) {

				if (searchPrice == ss[j].itemPrice) {
					
					
					printf("%-10s | %-20s | %-12.2f | %-20d | %-15d | %-16d\n", ss[j].itemCode, ss[j].itemDesc, ss[j].itemPrice,
						ss[j].qty, ss[j].minLvl, ss[j].reorderQty);
					records++;
				}
			}
			if (records < 1) {
				printf("\n [ No Records Found ] \n");
			}
			break;

		case 4:
			do {
				printf("\nEnter your quantity in stock to search : ");
				rewind(stdin);
				scanf("%d", &searchQty);
				checkQty(searchQty);
			} while (searchQty <= 0);

			printf("\nResults\n");
			printf("-------\n");
			printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
				"Item Code", "Item Description", "Item Price", "Quantity in Stock", "Minimum Level", "Reorder Quantity");
			printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
				"==========", "====================", "============", "====================", "===============", "================");

			for (int j = 0; j <= i; j++) {

				if (searchQty == ss[j].qty) {
					
					printf("%-10s | %-20s | %-12.2f | %-20d | %-15d | %-16d\n", ss[j].itemCode, ss[j].itemDesc, ss[j].itemPrice,
						ss[j].qty, ss[j].minLvl, ss[j].reorderQty);
					records++;
				}

				

			}

			if (records < 1) {
				printf("\n [ No Records Found ] \n");
			}
			break;

		case 5:
			do {
				printf("\nEnter your minimum level to search : ");
				rewind(stdin);
				scanf("%d", &searchMinLvl);
				checkMinLvl(searchMinLvl);
			} while ( searchMinLvl <= 0);

			printf("\nResults\n");
			printf("-------\n");
			printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
				"Item Code", "Item Description", "Item Price", "Quantity in Stock", "Minimum Level", "Reorder Quantity");
			printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
				"==========", "====================", "============", "====================", "===============", "================");

			for (int j = 0; j <= i; j++) {

				if (searchMinLvl == ss[j].minLvl) {
					
					printf("%-10s | %-20s | %-12.2f | %-20d | %-15d | %-16d\n", ss[j].itemCode, ss[j].itemDesc, ss[j].itemPrice,
						ss[j].qty, ss[j].minLvl, ss[j].reorderQty);
					records++;
				}

				
			}

			if (records < 1) {
				printf("\n [ No Records Found ] \n");
			}

			break;

		case 6:
			do {
				printf("\nEnter your reorder quantity to search : ");
				rewind(stdin);
				scanf("%d", &searchReorderQty);
				checkReorderQty(searchReorderQty);
			} while (searchReorderQty <= 0);

			printf("\nResults\n");
			printf("-------\n");
			printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
				"Item Code", "Item Description", "Item Price", "Quantity in Stock", "Minimum Level", "Reorder Quantity");
			printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
				"==========", "====================", "============", "====================", "===============", "================");

			for (int j = 0; j <= i; j++) {

				if (searchReorderQty == ss[j].reorderQty) {
				
					printf("%-10s | %-20s | %-12.2f | %-20d | %-15d | %-16d\n", ss[j].itemCode, ss[j].itemDesc, ss[j].itemPrice,
						ss[j].qty, ss[j].minLvl, ss[j].reorderQty);
					records++;
				}


			}


			if (records < 1) {
				printf("\n [ No Records Found ] \n");
			}

			break;


		default:
			searchChoice = 0;
			printf("Invalid!! Enter your choice (only 1-6) : \n");
			rewind(stdin);
			scanf("%d", &searchChoice);
			break;
		}

		printf("\n\nContinue to search ( Y = Yes ) ? : ");
		rewind(stdin);
		scanf("%c", &continueSearch);

		records = 0;

	} while (toupper(continueSearch) == 'Y');

	
}

void modifyStock() {
	FILE* modify;

	struct Stock s;
	struct Stock ms[999];
	int i = 0;
	char code[6];
	int modifychoice;
	char newItemDesc[30];
	double newItemPrice;
	int newQty, newMinLvl, newReorderQty, records = 0;
	char continueModify;

	modify = fopen("stock.txt", "r");


	if (modify == NULL) {
		printf("Error opening file !\n");
		exit(-1);
	}

	do {
		while (fscanf(modify, "%[^\|]|%[^\|]|%lf|%d|%d|%d\n", &s.itemCode, &s.itemDesc, &s.itemPrice,
			&s.qty, &s.minLvl, &s.reorderQty) != EOF) {
			strcpy(ms[i].itemCode, s.itemCode);
			strcpy(ms[i].itemDesc, s.itemDesc);
			ms[i].itemPrice = s.itemPrice;
			ms[i].qty = s.qty;
			ms[i].minLvl = s.minLvl;
			ms[i].reorderQty = s.reorderQty;
			i++;
		}
		fclose(modify);

		do {
			system("cls");

			printf("  __  __  ___  ___ ___ _____   __  ___ _____ ___   ___ _  __\n");
			printf(" |  \\/  |/ _ \\|   \\_ _| __\\ \\ / / / __|_   _/ _ \\ / __| |/ /\n");
			printf(" | |\\/| | (_) | |) | || _| \\ V /  \\__ \\ | || (_) | (__| ' < \n");
			printf(" |_|  |_|\\___/|___/___|_|   |_|   |___/ |_| \\___/ \\___|_|\\_\\\n");

			printf("\n-----------------------------------------------------------------\n");


			printf("\nEnter your item code to modify (A####) : ");
			rewind(stdin);
			scanf("%s", &code);
			checkItemCode(code);
		} while (strlen(code) != 5 || code[0] != 'A' || !isdigit(code[1]) || !isdigit(code[2]) || !isdigit(code[3]) || !isdigit(code[4]));

		for (int j = 0; j < i; j++) {
			if (strcmp(code, ms[j].itemCode) == 0) {
				printf("\nProduct found\n");
				printf("-------------\n");

				printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
					"Item Code", "Item Description", "Item Price", "Quantity in Stock", "Minimum Level", "Reorder Quantity");
				printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
					"==========", "====================", "============", "====================", "===============", "================");
				printf("%-10s | %-20s | %-12.2f | %-20d | %-15d | %-16d\n", ms[j].itemCode, ms[j].itemDesc, ms[j].itemPrice,
					ms[j].qty, ms[j].minLvl, ms[j].reorderQty);

				
				records++;

				printf("\n\n1. Modify Item Description\n");
				printf("2. Modify Item Price\n");
				printf("3. Modify Quantity in Stock\n");
				printf("4. Modify Minimum Level\n");
				printf("5. Modify Reorder Quantity\n");
				printf("6. Modify All\n");
				printf("Enter your choice to modify : ");
				scanf("%d", &modifychoice);

				switch (modifychoice) {
				case 1:
					do {
						printf("Enter new Item Description : ");
						rewind(stdin);
						scanf("%[^\n]", &newItemDesc);
						checkItemDesc(newItemDesc);
					} while (strlen(newItemDesc) > 30);

					strcpy(ms[j].itemDesc, newItemDesc);
					printf("Modify successfully!!\n");
					break;

				case 2:
					do {
						printf("Enter new Item Price : ");
						rewind(stdin);
						scanf("%lf", &newItemPrice);
						checkItemPrice(newItemPrice);
					} while (newItemPrice <= 0);

					ms[j].itemPrice = newItemPrice;
					printf("Modify successfully!!\n");
					break;

				case 3:
					do {
						printf("Enter new Quantity in Stock : ");
						rewind(stdin);
						scanf("%d", &newQty);
						checkQty(newQty);
					} while ( newQty <= 0);

					ms[j].qty = newQty;
					printf("Modify successfully!!\n");
					break;

				case 4:
					do {
						printf("Enter new Minimum Level : ");
						rewind(stdin);
						scanf("%d", &newMinLvl);
						checkMinLvl(newMinLvl);
					} while ( newMinLvl <= 0);

					ms[j].minLvl = newMinLvl;
					printf("Modify successfully!!\n");
					break;

				case 5:
					do {
						printf("Enter new Reorder Quantity : ");
						rewind(stdin);
						scanf("%d", &newReorderQty);
						checkReorderQty(newReorderQty);
					} while ( newReorderQty <= 0);

					ms[j].reorderQty = newReorderQty;
					printf("Modify successfully!!\n");
					break;

				case 6:
					do {
						printf("Enter new Item Description : ");
						rewind(stdin);
						scanf("%[^\n]", &newItemDesc);
						checkItemDesc(newItemDesc);
					} while (strlen(newItemDesc) > 30);
					strcpy(ms[j].itemDesc, newItemDesc);

					do {
						printf("Enter new Item Price : ");
						rewind(stdin);
						scanf("%lf", &newItemPrice);
						checkItemPrice(newItemPrice);
					} while (sizeof(newItemPrice) != sizeof(double) || newItemPrice <= 0);
					ms[j].itemPrice = newItemPrice;

					do {
						printf("Enter new Quantity in Stock : ");
						rewind(stdin);
						scanf("%d", &newQty);
						checkQty(newQty);
					} while ( newQty <= 0);
					ms[j].qty = newQty;

					do {
						printf("Enter new Minimum Level : ");
						rewind(stdin);
						scanf("%d", &newMinLvl);
						checkMinLvl(newMinLvl);
					} while ( newMinLvl <= 0);
					ms[j].minLvl = newMinLvl;

					do {
						printf("Enter new Reorder Quantity : ");
						rewind(stdin);
						scanf("%d", &newReorderQty);
						checkReorderQty(newReorderQty);
					} while ( newReorderQty <= 0);
					ms[j].reorderQty = newReorderQty;
					printf("Modify successfully!!\n");
					break;

				default:
					printf("\nInvalid choice ! Re-enter your choice ( only 1 - 6 ) : ");
					modifychoice = 0;
					rewind(stdin);
					scanf("%d", &modifychoice);
				}
			}

			
		}

		if (records < 1) {
			printf("\n [ No Records Found ] \n");
		}

		printf("Continue to modify ? ( Y = Yes ) : ");
		rewind(stdin);
		scanf("%c", &continueModify);
	} while (toupper(continueModify) == 'Y');


	FILE* modifyIN;
	modifyIN = fopen("stock.txt", "w");
	for (int k = 0; k < i; k++) {
		fprintf(modifyIN, "%s|%s|%.2lf|%d|%d|%d\n", ms[k].itemCode, ms[k].itemDesc, ms[k].itemPrice,
			ms[k].qty, ms[k].minLvl, ms[k].reorderQty);
	}
	fclose(modifyIN);
}

void displayStock() {
	FILE* display;

	display = fopen("stock.txt", "r");

	int i = 0;
	struct Stock s[999];

	while (fscanf(display, "%[^\|]|%[^\|]|%lf|%d|%d|%d\n", &s[i].itemCode, &s[i].itemDesc, &s[i].itemPrice,
		&s[i].qty, &s[i].minLvl, &s[i].reorderQty) != EOF) {
		i++;
	}

	system("cls");
	printf("\n");


	printf("  ___ ___ ___ ___ _      ___   __  ___ _____ ___   ___ _  __\n");
	printf(" |   \\\_ _/ __| _ \\ |    /_\\ \\ / / / __|_   _/ _ \\ / __| |/ /\n");
	printf(" | |) | |\\__ \\  _/ |__ / _ \\ V /  \\__ \\ | || (_) | (__| ' < \n");
	printf(" |___/___|___/_| |____/_/ \\_\\_|   |___/ |_| \\___/ \\___|_|\\_\\ \n");

	printf("-----------------------------------------------------------------\n");

	printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
		"Item Code", "Item Description", "Item Price", "Quantity in Stock", "Minimum Level", "Reorder Quantity");
	printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
		"==========", "====================", "============", "====================", "===============", "================");
	for (int j = 0; j < i; j++) {
		printf("%-10s | %-20s | %-12.2lf | %-20d | %-15d | %-16d\n", s[j].itemCode, s[j].itemDesc, s[j].itemPrice,
			s[j].qty, s[j].minLvl, s[j].reorderQty);
	}
	printf("\n\nDisplay all stock items sucessfully !!\n");
	fclose(display);
}

void deleteStock() {
	FILE* deletestk;

	struct Stock s;
	struct Stock ds[999];
	int i = 0, records = 0;
	char code[6];
	char delChoice;
	char continueDelete;


	do {

		system("cls");


		deletestk = fopen("stock.txt", "r");

		if (deletestk == NULL) {
			printf("Error opening file !\n");
			exit(-1);
		}

		while (fscanf(deletestk, "%[^\|]|%[^\|]|%lf|%d|%d|%d\n", &s.itemCode, &s.itemDesc, &s.itemPrice,
			&s.qty, &s.minLvl, &s.reorderQty) != EOF) {
			strcpy(ds[i].itemCode, s.itemCode);
			strcpy(ds[i].itemDesc, s.itemDesc);
			ds[i].itemPrice = s.itemPrice;
			ds[i].qty = s.qty;
			ds[i].minLvl = s.minLvl;
			ds[i].reorderQty = s.reorderQty;
			i++;
		}
		fclose(deletestk);

		do {
			printf("\n");

			printf("  ___  ___ _    ___ _____ ___   ___ _____ ___   ___ _  __\n");
			printf(" |   \\| __| |  | __|_   _| __| / __|_   _/ _ \\ / __| |/ / \n");
			printf(" | |) | _|| |__| _|  | | | _|  \\__ \\ | || (_) | (__| ' < \n");
			printf(" |___/|___|____|___| |_| |___| |___/ |_| \\___/ \\___|_|\\_\\ \n");

			printf("--------------------------------------------------------------\n");

			printf("\nEnter your item code to delete (A####) : ");
			rewind(stdin);
			scanf("%s", &code);
			checkItemCode(code);
		} while (strlen(code) != 5 || code[0] != 'A' || !isdigit(code[1]) || !isdigit(code[2]) || !isdigit(code[3]) || !isdigit(code[4]));

		for (int j = 0; j < i; j++) {
			if (strcmp(code, ds[j].itemCode) == 0) {
				printf("\nProduct found\n");
				printf("-------------\n");

				printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
					"Item Code", "Item Description", "Item Price", "Quantity in Stock", "Minimum Level", "Reorder Quantity");
				printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
					"==========", "====================", "============", "====================", "===============", "================");
				printf("%-10s | %-20s | %-12.2f | %-20d | %-15d | %-16d\n", ds[j].itemCode, ds[j].itemDesc, ds[j].itemPrice,
					ds[j].qty, ds[j].minLvl, ds[j].reorderQty);

				records++;

				printf("\nSure to delete ? ( Y = Yes ) : ");
				rewind(stdin);
				scanf("%c", &delChoice);

				if (toupper(delChoice) == 'Y') {
					for (int p = j; p <= i - 1; p++) {
						strcpy(ds[p].itemCode, ds[p + 1].itemCode);
						strcpy(ds[p].itemDesc, ds[p + 1].itemDesc);
						ds[p].itemPrice = ds[p + 1].itemPrice;
						ds[p].qty = ds[p + 1].qty;
						ds[p].minLvl = ds[p + 1].minLvl;
						ds[p].reorderQty = ds[p + 1].reorderQty;
					}
					printf("\nDeleted successfully !! \n\n");
				}
			}

		}

		FILE* deleteStkIN;


		deleteStkIN = fopen("stock.txt", "w");
		for (int k = 0; k < i - 1; k++) {
			fprintf(deleteStkIN, "%s|%s|%.2lf|%d|%d|%d\n", ds[k].itemCode, ds[k].itemDesc, ds[k].itemPrice,
				ds[k].qty, ds[k].minLvl, ds[k].reorderQty);
		}

		i = 0;

		fclose(deleteStkIN);

		if (records < 1) {
			printf("\n [ No Records Found ] \n");
		}

		printf("\nContinue to delete ? ( Y = Yes ) : ");
		rewind(stdin);
		scanf("%c", &continueDelete);

		records = 0;

	} while (toupper(continueDelete) == 'Y');

	
}

void donateStock() {
	FILE* donate;

	struct Stock s;
	struct Stock dnts[999];
	int i = 0;
	char code[6];
	char donatechoice;
	int donatepcs, records = 0;
	char continueDonate;

	donate = fopen("stock.txt", "r");

	if (donate == NULL) {
		printf("Error opening file !\n");
		exit(-1);
	}

	do {
		while (fscanf(donate, "%[^\|]|%[^\|]|%lf|%d|%d|%d\n", &s.itemCode, &s.itemDesc, &s.itemPrice,
			&s.qty, &s.minLvl, &s.reorderQty) != EOF) {
			strcpy(dnts[i].itemCode, s.itemCode);
			strcpy(dnts[i].itemDesc, s.itemDesc);
			dnts[i].itemPrice = s.itemPrice;
			dnts[i].qty = s.qty;
			dnts[i].minLvl = s.minLvl;
			dnts[i].reorderQty = s.reorderQty;
			i++;
		}
		fclose(donate);

		do {
			system("cls");
			printf("\n");
			printf("  ___   ___  _  _   _ _____ ___   ___ _____ ___   ___ _  __\n");
			printf(" |   \\ / _ \\| \\| | /_\\_   _| __| / __|_   _/ _ \\ / __| |/ /\n");
			printf(" | |) | (_) | .` |/ _ \\| | | _|  \\__ \\ | || (_) | (__| ' < \n");
			printf(" |___/ \\___/|_|\\_/_/ \\_\\_| |___| |___/ |_| \\___/ \\___|_|\\_\\ \n");

			printf("----------------------------------------------------------------\n");

			printf("\nEnter your item code to donate (A####) : ");
			rewind(stdin);
			scanf("%s", &code);

		} while (strlen(code) != 5 || code[0] != 'A' || !isdigit(code[1]) || !isdigit(code[2]) || !isdigit(code[3]) || !isdigit(code[4]));

		for (int j = 0; j < i; j++) {
			if (strcmp(code, dnts[j].itemCode) == 0) {
				printf("\nProduct found\n");
				printf("-------------\n");

				printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
					"Item Code", "Item Description", "Item Price", "Quantity in Stock", "Minimum Level", "Reorder Quantity");
				printf("%-10s | %-20s | %-12s | %-20s | %-15s | %-16s\n",
					"==========", "====================", "============", "====================", "===============", "================");
				printf("%-10s | %-20s | %-12.2f | %-20d | %-15d | %-16d\n", dnts[j].itemCode, dnts[j].itemDesc, dnts[j].itemPrice,
					dnts[j].qty, dnts[j].minLvl, dnts[j].reorderQty);

				records++;

				printf("\nSure to donate ? ( Y = Yes ) : ");
				rewind(stdin);
				scanf("%c", &donatechoice);

				if (donatechoice == 'Y' || donatechoice == 'y') {
					printf("\nDonate how many pieces ? : ");
					rewind(stdin);
					scanf("%d", &donatepcs);
					dnts[j].qty = dnts[j].qty - donatepcs;
					if (dnts[j].qty < dnts[j].minLvl) {
						printf("\nThe quantity of the donate item is below the minimum level!\n");
						printf("The auto reorder quantity is %d pcs.\n", dnts[j].reorderQty);
						dnts[j].qty = dnts[j].qty + dnts[j].reorderQty;
						printf("The quantity in stock now is %d pcs.\n", dnts[j].qty);
					}
					else {
						printf("Donate successfully ! \n");
						printf("The quantity in stock now is %d.\n", dnts[j].qty);
					}
				}
			}
		}

		if (records < 1) {
			printf("\n [ No Records Found ] \n");
		}

		FILE* donateIN;
		donateIN = fopen("stock.txt", "w");
		for (int k = 0; k < i; k++) {
			fprintf(donateIN, "%s|%s|%.2lf|%d|%d|%d\n", dnts[k].itemCode, dnts[k].itemDesc, dnts[k].itemPrice,
				dnts[k].qty, dnts[k].minLvl, dnts[k].reorderQty);
		}
		fclose(donateIN);

		printf("\nContinue to donate ? ( Y = Yes ) : ");
		rewind(stdin);
		scanf("%c", &continueDonate);

		records = 0;

	} while (toupper(continueDonate) == 'Y');

	
}

void checkItemCode(char code[]) {
	if (strlen(code) != 5) {
		printf("\nInvalid ! Item Code can only contain 5 characters!\n");
	}
	if (code[0] != 'A') {
		printf("\nInvalid ! Item Code must start with letter 'A' !\n");
	}
	if (!isdigit(code[1]) || !isdigit(code[2]) || !isdigit(code[3]) || !isdigit(code[4])) {
		printf("\nInvalid ! Item Code must end with 4 digits number!\n");
	}
}

void checkItemDesc(char desc[]) {
	if (strlen(desc) > 30) {
		printf("\nInvalid ! Item Description only contain less than 30 characters!\n");
	}
}

void checkItemPrice(double price) {
	if (sizeof(price) != sizeof(double)) {
		printf("Invalid ! Item price should be a double variable ! \n");
	}

	if (price <= 0) {
		printf("\nInvalid ! Item Price more than zero ! \n");
	}
}

void checkQty(int qty) {
	if (qty <= 0) {
		printf("\nInvalid! Quantity in Stock must greater than or equal to zero ! \n");
	}
}

void checkMinLvl(int minLvl) {


	if (minLvl <= 0) {
		printf("\nInvalid! Minimum Level must greater than or equal to zero ! \n");
	}
}

void checkReorderQty(int reorderQty) {

	
	if (reorderQty <= 0) {
		printf("\nInvalid! Reorder Quantity must greater than or equal to zero ! \n");
	}
}