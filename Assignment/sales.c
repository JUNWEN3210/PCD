#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <Windows.h>
#pragma warning (disable:4996)

void salesMenu();
void displaySales();
void searchSales();
void addSales();
void addsalesstock();
void addsalesstaff();
void deleteSales();
void deletesalesstock();
void deletesalesstaff();
void modifySales();
void modifysalesstock();
void modifysalesstaff();
void salesreport();
int codeValidation(char code[5], char codeChar, char codeChecked[10]);

typedef struct {
	char salesid[10];
	char prodName[30];
	double price;
	int qty;
	int qtysold, remain;
}SALESSTOCK;

SALESSTOCK ss;

typedef struct {

	char salesId[10], staffid[10];
	char staffname[30], prodName[30];
	int qtysold;
	double stockprice;

}STAFFRECORD;
STAFFRECORD SR;

typedef struct {
	char dltSalesId[10];
	char dltprodName[30];
	double dltprice;
	int dltqty;
	int dltqtysold, dltremain;

}DELETESALESSTOCK;

DELETESALESSTOCK DSS[999];

typedef struct {
	char dltSalesId[10], dltStaffid[10];
	char dltstaffname[30], dltprodName[30];
	int dltqtysold;
	double dltstockprice;

}DELETESTAFFRECORD;

DELETESTAFFRECORD DSR[999];

typedef struct {
	char MSalesId[10];
	char MprodName[30];
	double Mprice;
	int Mqty;
	int Mqtysold, Mremain;

}MODIFYSALESSTOCK;

MODIFYSALESSTOCK MSS[999];

typedef struct {
	char MSalesId[10], MStaffid[10];
	char Mstaffname[30], MprodName[30];
	int Mqtysold;
	double Mstockprice;
}MODIFYSTAFFRECORD;

MODIFYSTAFFRECORD MSR[999];

typedef struct {
	char memberid[10], name[30], gender, itemPuchase[30];
	int Nointroduced;
	double comm;

}Member;



struct member {
	char id[5], name[50], gender, email[25], phone[12], ic[20];
	int noIntro, level;
	int bday, bmonth, byear;
};

struct member convert;

void salesMenu() {
	int opt;
	char ans = 'N';

	printf("===================================================================================================\n");
	printf("  /$$$$$$   /$$$$$$  /$$       /$$$$$$$$  /$$$$$$        /$$      /$$  /$$$     /$$   /$$\n");
	printf(" /$$__  $$ /$$__  $$| $$      | $$_____/ /$$__  $$      | $$$    /$$$ /$$ $$   | $$  | $$\n");
	printf("| $$  \\__/| $$  \\ $$| $$      | $$      | $$  \\__/      | $$$$  /$$$$|  $$$    | $$  | $$\n");
	printf("|  $$$$$$ | $$$$$$$$| $$      | $$$$$   |  $$$$$$       | $$ $$/$$ $$ /$$ $$/$$| $$$$$$$$\n");
	printf(" \\____  $$| $$__  $$| $$      | $$__/    \\____  $$      | $$  $$$| $$| $$  $$_/| $$__  $$\n");
	printf(" /$$  \\ $$| $$  | $$| $$      | $$       /$$  \\ $$      | $$\\  $ | $$| $$\\  $$ | $$  | $$\n");
	printf("|  $$$$$$/| $$  | $$| $$$$$$$$| $$$$$$$$|  $$$$$$/      | $$ \\/  | $$|  $$$$/$$| $$  | $$\n");
	printf(" \\______/ |__/  |__/|________/|________/ \\______/       |__/     |__/ \\____/\\_/|__/  |__/ \n");
	printf("====================================================================================================\n");
	do {
		printf("1.Diplays sales\n");
		printf("2.Search sales\n");
		printf("3.Add sales\n");
		printf("4.Delete sales\n");
		printf("5.Modify sales\n");
		printf("6.Generate report of sales\n");
		printf("7.Exit\n");
		printf("Enter an option--->");
		scanf("%d", &opt);

		/*validation*/
		while (opt != 1 && opt != 2 && opt != 3 && opt != 4 && opt != 5 && opt != 6 && opt != 7) {
			printf("Invalid option! Please re-enter\n");
			printf("1.Diplays sales\n");
			printf("2.Search sales\n");
			printf("3.Add sales\n");
			printf("4.Delete sales\n");
			printf("5.Modify sales\n");
			printf("6.Generate report of sales\n");
			printf("7.Exit\n");
			printf("Enter an option--->");
			scanf("%d", &opt);

		}

		if (opt == 1)
			displaySales();

		else if (opt == 2)
			searchSales();

		else if (opt == 3)
			addSales();

		else if (opt == 4)
			deleteSales();

		else if (opt == 5)
			modifySales();

		else if (opt == 6)
			salesreport();

		if (opt != 7)
		{
			ans == 'Y';
		}

	} while (toupper(ans) == 'Y');

}


void displaySales() {
	system("cls");
	FILE* fptr;

	fptr = fopen("stocksales.txt", "r");

	if (fptr == NULL) {
		printf("Unable to open the file\n");
		exit(-1);
	}

	int qtyStock, qtySold, qtyremain;
	double stockPrice;
	char stockName[30];
	char salesID[10];
	int i, count = 0;

	printf("%-15s %-15s %-16s %-10s %-20s %-15s\n", "SALES ID", "PRODUCT NAME", "PRICE(RM)", "QUANTITY", "QUANTITY SOLD", "QUANTITY LEFT");
	printf("--------------------------------------------------------------------------------------------------------\n");
	while (fscanf(fptr, "%s %s %lf %d %d %d\n", &salesID, &stockName, &stockPrice, &qtyStock, &qtySold, &qtyremain) != EOF)
	{
		count++;
		printf("%-15s %-15s %6.2lf %15d %10d %20d\n", salesID, stockName, stockPrice, qtyStock, qtySold, qtyremain);
	}

	printf("--------------------------------------------------------------------------------------------------------\n");
	printf("< %d product listed >\n\n", count);

	fclose(fptr);
	system("pause");

	system("cls");
	salesMenu();

}


void searchSales() {
	FILE* inptr;
	char ans;
	char salesid[10];
	int j = 0, sum = 0;
	int checkSI;

	inptr = fopen("salesstaff.txt", "r");


	if (inptr == NULL) {
		printf("Unable to open the file\n");
		exit(-1);
	}


	do {

		printf("Search sales that successfully made by staff \n");
		printf("============================================\n");
		do {
			printf("Enter sales ID(SXXX):");
			scanf("%s", &salesid);
			rewind(stdin);
			checkSI = codeValidation(salesid, 'S', "salesid");

		} while (checkSI == 0);


		printf("%-15s %-15s %-16s %-20s %-10s\n", "STAFF ID", "STAFF NAME", "SALES MADE", "PRODUCT NAME", "PRICE(RM)");
		printf("---------------------------------------------------------------------------------\n");

		inptr = fopen("salesstaff.txt", "r");

		while (fscanf(inptr, "%s %s %s %d %s %lf\n", &SR.salesId, &SR.staffname, &SR.staffid, &SR.qtysold, &SR.prodName, &SR.stockprice) != EOF) {
			if (strcmp(SR.salesId, salesid) == 0) {
				printf("%-15s %-15s %d                 %s %19.2lf\n", SR.staffid, SR.staffname, SR.qtysold, SR.prodName, SR.stockprice);
				sum += SR.qtysold;

			}

		}

		printf("Total sales made:%d\n", sum);
		printf("Continue search?(Y=YES ; N=NO):");
		rewind(stdin);
		scanf("%c", &ans);
		sum = 0;

		/*Validation*/
		while (toupper(ans) != 'Y' && toupper(ans) != 'N')
		{
			printf("Please key in correct value for continue(Y=YES ; N=NO):");
			rewind(stdin);
			scanf("%c", &ans);
			ans = toupper(ans);
		}
	} while (toupper(ans) == 'Y');

	fclose(inptr);

	system("cls");
	salesMenu();
}

void addSales() {


	int ans;
	char choice;

	do {
		printf("1. Add sales stock\n");
		printf("2. Add sales that made by staff\n");
		printf("3. Exit\n");
		printf("Enter your choice:");
		scanf("%d", &ans);
		rewind(stdin);

		while (ans != 1 && ans != 2 && ans != 3) {
			printf("Invalid option! Please re-enter\n");
			printf("1. Add sales stock\n");
			printf("2. Add sales that made by staff\n");
			printf("3. Exit\n");
			scanf("%d", &ans);
			rewind(stdin);

		}

		if (ans == 1)
			addsalesstock();
		else if (ans == 2)
			addsalesstaff();

		else if (ans == 3)
			salesMenu();

		printf("Continue? (Y = Yes): ");
		rewind(stdin);
		scanf("%c", &choice);

		//validation
		while (toupper(choice) != 'Y' && toupper(choice) != 'N')
		{
			printf("Please key in correct value for continue(Y=YES ; N=NO):");
			rewind(stdin);
			scanf("%c", &choice);
			choice = toupper(choice);
		}


	} while (toupper(choice) == 'Y');

	system("cls");
	salesMenu();


}

void addsalesstock() {
	FILE* addstockptr;
	addstockptr = fopen("stocksales.txt", "a");

	if (addstockptr == NULL) {
		printf("Unable to open the file\n");
		exit(-1);

	}

	char ans;
	int checkSI;

	do {
		do {
			printf("Enter sales id (SXXX):");
			scanf("%s", &ss.salesid);
			rewind(stdin);
			checkSI = codeValidation(ss.salesid, 'S', "salesid");
		} while (checkSI == 0);

		printf("Enter product name (in capital letter):");
		scanf("%[^\n]", &ss.prodName);
		rewind(stdin);

		printf("Enter price of the product (in RM):");
		scanf("%lf", &ss.price);
		rewind(stdin);

		printf("Enter quantity in stock:");
		scanf("%d", &ss.qty);
		rewind(stdin);

		printf("Enter quantity sold:");
		scanf("%d", &ss.qtysold);
		rewind(stdin);

		printf("Enter quantity stock remaining:");
		scanf("%d", &ss.remain);
		rewind(stdin);

		fprintf(addstockptr, "%s %s %.2lf %d %d %d\n", ss.salesid, ss.prodName, ss.price, ss.qty, ss.qtysold, ss.remain);
		printf("Safe Succesfully\n");
		printf("Add another record?(Y=YES,N=NO):");
		rewind(stdin);
		scanf("%c", &ans);


		//validation 
		while (toupper(ans) != 'Y' && toupper(ans) != 'N')
		{
			printf("Please key in correct value for continue(Y=YES ; N=NO):");
			rewind(stdin);
			scanf("%c", &ans);
			ans = toupper(ans);
		}

	} while (toupper(ans) == 'Y');

	fclose(addstockptr);
}

void addsalesstaff() {
	FILE* addSalesptr;
	addSalesptr = fopen("salesstaff.txt", "a");

	if (addSalesptr == NULL) {
		printf("Unable to open the file\n");
		exit(-1);

	}

	char ans;
	int checkSI, checkEI;


	do {

		do {
			printf("Enter sales id (SXXX):");
			scanf("%s", &SR.salesId);
			rewind(stdin);
			checkSI = codeValidation(SR.salesId, 'S', "salesid");
		} while (checkSI == 0);

		printf("Enter staff name :");
		scanf("%s", &SR.staffname);
		rewind(stdin);

		do {
			printf("Enter staff id (EXXX) :");
			scanf("%[^\n]", &SR.staffid);
			rewind(stdin);
			checkEI = codeValidation(SR.staffid, 'E', "staffid");
		} while (checkEI == 0);


		printf("How many sales made by staff :");
		scanf("%d", &SR.qtysold);
		rewind(stdin);

		printf("Enter product name:");
		scanf("%[^\n]", &SR.prodName);
		rewind(stdin);

		printf("Enter price of the product (in RM):");
		scanf("%lf", &SR.stockprice);
		rewind(stdin);

		fprintf(addSalesptr, "%s %s %s %d %s %.2lf\n", SR.salesId, SR.staffname, SR.staffid, SR.qtysold, SR.prodName, SR.stockprice);
		printf("Safe Succesfully\n");
		printf("Add another record?(Y=YES,N=NO):");
		rewind(stdin);
		scanf("%c", &ans);

		//validation 
		while (toupper(ans) != 'Y' && toupper(ans) != 'N')
		{
			printf("Please key in correct value for continue(Y=YES ; N=NO):");
			rewind(stdin);
			scanf("%c", &ans);
			ans = toupper(ans);
		}

	} while (toupper(ans) == 'Y');

	fclose(addSalesptr);

}

int codeValidation(char code[5], char codeChar, char codeChecked[10]) {
	if (strlen(code) != 4) {
		printf("The %s should contain exactly 4 characters.\n", codeChecked);
		return 0;
	}
	else if (code[0] != codeChar) {
		printf("The first character of the %s should be '%c', please enter again.\n", codeChecked, codeChar);
		return 0;
	}
	else if (!isdigit(code[1]) || !isdigit(code[2]) || !isdigit(code[3])) {
		printf("There should be 3 digits after the character '%c', please enter again.\n", codeChar);
		return 0;
	}

	return 1;
}


void deleteSales() {
	int ans;
	char choice;

	do {
		printf("1. Delete sales stock\n");
		printf("2. Delete sales that made by staff\n");
		printf("3. Exit\n");
		printf("Enter your choice:");
		scanf("%d", &ans);
		rewind(stdin);

		while (ans != 1 && ans != 2 && ans != 3) {
			printf("Invalid option! Please re-enter\n");
			printf("1. Delete sales stock\n");
			printf("2. Delete sales that made by staff\n");
			printf("3. Exit\n");
			scanf("%d", &ans);
			rewind(stdin);

		}

		if (ans == 1)
			deletesalesstock();
		else if (ans == 2)
			deletesalesstaff();

		else if (ans == 3)
			salesMenu();

		printf("Continue? (Y=YES,N=NO): ");
		rewind(stdin);
		scanf("%c", &choice);

		while (toupper(choice) != 'Y' && toupper(choice) != 'N')
		{
			printf("Please key in correct value for continue(Y=YES ; N=NO):");
			rewind(stdin);
			scanf("%c", &choice);
			choice = toupper(choice);
		}


	} while (toupper(choice) == 'Y');

	system("cls");
	salesMenu();
}


void deletesalesstock() {
	int  i = 0, j;
	char dltsalesid[5];
	char dltchoice, choice;
	int dltcount = 0;
	int nondltcount, checkSI;



	FILE* dleptr;
	dleptr = fopen("stocksales.txt", "r");

	if (dleptr == NULL) {
		printf("Unable to open the file\n");
		exit(-1);
	}

	/*assign all records in file to delete array*/

	while (fscanf(dleptr, "%s %s %lf %d %d %d\n", ss.salesid, ss.prodName, &ss.price, &ss.qty, &ss.qtysold, &ss.remain) != EOF) {
		strcpy(DSS[i].dltSalesId, ss.salesid);
		strcpy(DSS[i].dltprodName, ss.prodName);
		DSS[i].dltprice = ss.price;
		DSS[i].dltqty = ss.qty;
		DSS[i].dltqtysold = ss.qtysold;
		DSS[i].dltremain = ss.remain;
		i++;

	}
	fclose(dleptr);

	printf("Delete stock of sales detail\n");
	printf("============================\n");

	do {

		do {
			printf("Enter sales id (SXXX) that you want to delete:");
			scanf("%s", &dltsalesid);
			rewind(stdin);
			checkSI = codeValidation(dltsalesid, 'S', "salesid");
		} while (checkSI == 0);

		printf("Sure you want to delete? ( Y = yes ) >");
		scanf("%c", &dltchoice);
		rewind(stdin);

		if (dltchoice == 'Y' || dltchoice == 'y') {
			for (j = 0; j < i; j++) {
				if (strcmp(dltsalesid, DSS[j].dltSalesId) == 0) {
					strcpy(DSS[j].dltSalesId, DSS[j + 1].dltSalesId);
					strcpy(DSS[j].dltprodName, DSS[j + 1].dltprodName);
					DSS[j].dltprice = DSS[j + 1].dltprice;
					DSS[j].dltqty = DSS[j + 1].dltqty;
					DSS[j].dltqtysold = DSS[j + 1].dltqtysold;
					DSS[j].dltremain = DSS[j + 1].dltremain;

					dltcount++;
				}


			}

		}

		if (dltcount > 0) {
			printf("Deleted successfully.\n");
			printf("%d record(s) deleted\n", dltcount);
		}

		else {
			printf("Deleted unsuccessfully.\n");
			printf("No Records found!\n");

		}

		printf("Delete another record? (Y=YES,N=NO):");
		rewind(stdin);
		scanf("%c", &choice);

		//validation 
		while (toupper(choice) != 'Y' && toupper(choice) != 'N')
		{
			printf("Please key in correct value for continue(Y=YES ; N=NO):");
			rewind(stdin);
			scanf("%c", &choice);
			choice = toupper(choice);
		}

	} while (toupper(choice) == 'Y');

	nondltcount = i - dltcount;

	FILE* dleinptr;
	dleinptr = fopen("stocksales.txt", "w");
	for (j = 0; j < nondltcount; j++) {
		fprintf(dleinptr, "%s %s %.2lf %d %d %d\n", DSS[j].dltSalesId, DSS[j].dltprodName, DSS[j].dltprice, DSS[j].dltqty, DSS[j].dltqtysold, DSS[j].dltremain);
	}

	fclose(dleinptr);
}

void deletesalesstaff() {
	int i, count = 0, dltcount2 = 0, nondltcount2;
	char dltsalesid2[10], dltstaffid[10], dltchoice2, choice;
	int checkSI, checkEI;


	FILE* dleptr2;
	dleptr2 = fopen("salesstaff.txt", "r");

	if (dleptr2 == NULL) {
		printf("Unable to open the file\n");
		exit(-1);
	}

	while (fscanf(dleptr2, "%s %s %s %d %s %lf\n", &SR.salesId, &SR.staffname, &SR.staffid, &SR.qtysold, &SR.prodName, &SR.stockprice) != EOF) {
		strcpy(DSR[count].dltSalesId, SR.salesId);
		strcpy(DSR[count].dltstaffname, SR.staffname);
		strcpy(DSR[count].dltStaffid, SR.staffid);
		DSR[count].dltqtysold = SR.qtysold;
		strcpy(DSR[count].dltprodName, SR.prodName);
		DSR[count].dltstockprice = SR.stockprice;
		count++;
	}

	fclose(dleptr2);
	printf("Delete sales that made by staff\n");
	printf("===============================\n");
	do {
		do {
			printf("Enter sales id (SXXX) that you want to delete:");
			scanf("%s", &dltsalesid2);
			rewind(stdin);
			checkSI = codeValidation(dltsalesid2, 'S', "salesid");
		} while (checkSI == 0);

		do {
			printf("Enter staff id (EXXX) that you want to delete:");
			scanf("%s", &dltstaffid);
			rewind(stdin);
			checkEI = codeValidation(dltstaffid, 'E', "staffid");
		} while (checkEI == 0);

		printf("Sure you want to delete? ( Y = yes ) >");
		scanf("%c", &dltchoice2);
		rewind(stdin);

		if (dltchoice2 == 'Y' || dltchoice2 == 'y') {
			for (i = 0; i < count; i++) {
				if (strcmp(dltsalesid2, DSR[i].dltSalesId) == 0 && strcmp(dltstaffid, DSR[i].dltStaffid) == 0) {
					strcpy(DSR[i].dltSalesId, DSR[i + 1].dltSalesId);
					strcpy(DSR[i].dltstaffname, DSR[i + 1].dltstaffname);
					strcpy(DSR[i].dltStaffid, DSR[i + 1].dltStaffid);
					DSR[i].dltqtysold = DSR[i + 1].dltqtysold;
					strcpy(DSR[i].dltprodName, DSR[i + 1].dltprodName);
					DSR[i].dltstockprice = DSR[i + 1].dltstockprice;
					dltcount2++;
				}
			}
		}

		if (dltcount2 > 0) {
			printf("Deleted successfully.\n");
			printf("%d record(s) deleted\n", dltcount2);
		}

		else {
			printf("Deleted unsuccessfully.\n");
			printf("No Records found!\n");

		}

		printf("Delete another record? (Y=YES,N=NO):");
		rewind(stdin);
		scanf("%c", &choice);


		//validation 
		while (toupper(choice) != 'Y' && toupper(choice) != 'N')
		{
			printf("Please key in correct value for continue(Y=YES ; N=NO):");
			rewind(stdin);
			scanf("%c", &choice);
			choice = toupper(choice);
		}


	} while (toupper(choice) == 'Y');
	FILE* dleinptr2;

	nondltcount2 = i - dltcount2;

	dleinptr2 = fopen("salesstaff.txt", "w");
	for (i = 0; i < nondltcount2; i++) {
		fprintf(dleinptr2, "%s %s %s %d %s %.2lf\n", DSR[i].dltSalesId, DSR[i].dltstaffname, DSR[i].dltStaffid, DSR[i].dltqtysold, DSR[i].dltprodName, DSR[i].dltstockprice);
	}

	fclose(dleinptr2);


}


void modifySales() {
	int ans;
	char choice;

	do {
		printf("1. Modify sales stock\n");
		printf("2. Modify sales that made by staff\n");
		printf("3. Exit\n");
		printf("Enter your choice:");
		scanf("%d", &ans);
		rewind(stdin);

		while (ans != 1 && ans != 2 && ans != 3) {
			printf("Invalid option! Please re-enter\n");
			printf("1. Delete sales stock\n");
			printf("2. Delete sales that made by staff\n");
			printf("3. Exit\n");
			scanf("%d", &ans);
			rewind(stdin);

		}

		if (ans == 1)
			modifysalesstock();
		else if (ans == 2)
			modifysalesstaff();

		else if (ans == 3)
			salesMenu();

		printf("Continue? (Y=YES,N=NO): ");
		rewind(stdin);
		scanf("%c", &choice);

		//validation 
		while (toupper(choice) != 'Y' && toupper(choice) != 'N')
		{
			printf("Please key in correct value for continue(Y=YES ; N=NO):");
			rewind(stdin);
			scanf("%c", &choice);
			choice = toupper(choice);
		}


	} while (toupper(choice) == 'Y');

	system("cls");
	salesMenu();

}

void modifysalesstock() {
	int checkSI, modifyopt;
	char mdysalesid[10], newsalesid[10], newprodName[30], suremodify, anotherMchoice;
	double newprice;
	int newqty, newqtysold, newremain;
	int Mcount = 0, modifycount = 0, i;
	FILE* Mptr;
	Mptr = fopen("stocksales.txt", "r");

	if (Mptr == NULL) {
		printf("Unablle to open the file\n");
		exit(-1);

	}

	while (fscanf(Mptr, "%s %s %lf %d %d %d\n", &ss.salesid, &ss.prodName, &ss.price, &ss.qty, &ss.qtysold, &ss.remain) != EOF) {
		strcpy(MSS[Mcount].MSalesId, ss.salesid);
		strcpy(MSS[Mcount].MprodName, ss.prodName);
		MSS[Mcount].Mprice = ss.price;
		MSS[Mcount].Mqty = ss.qty;
		MSS[Mcount].Mqtysold = ss.qtysold;
		MSS[Mcount].Mremain = ss.remain;
		Mcount++;
	}

	fclose(Mptr);

	printf("Modify stock of sales detail\n");
	printf("============================\n");

	do {
		do {
			printf("Enter sales id (SXXX) that you want to modify:");
			scanf("%s", &mdysalesid);
			rewind(stdin);
			checkSI = codeValidation(mdysalesid, 'S', "sales id");
		} while (checkSI == 0);

		for (i = 0; i < Mcount; i++) {
			if (strcmp(mdysalesid, MSS[i].MSalesId) == 0) {
				printf("%-15s %-15s %-16s %-10s %-20s %-15s\n", "SALES ID", "PRODUCT NAME", "PRICE(RM)", "QUANTITY", "QUANTITY SOLD", "QUANTITY LEFT");
				printf("--------------------------------------------------------------------------------------------------------\n");
				printf("%-15s %-15s %6.2lf %15d %10d %20d\n", MSS[i].MSalesId, MSS[i].MprodName, MSS[i].Mprice, MSS[i].Mqty, MSS[i].Mqtysold, MSS[i].Mremain);
				printf("1.Modify Product Name\n");
				printf("2.Modify Price of the Product\n");
				printf("3.Modify Quantity of the Product\n");
				printf("4.Modify Quantity Sold of the Product\n");
				printf("5.Modify Quantity remaining of the Product\n");
				printf("6.Modify All\n");
				printf("Enter your choice:");
				scanf("%d", &modifyopt);

				while (modifyopt != 1 && modifyopt != 2 && modifyopt != 3 && modifyopt != 4 && modifyopt != 5 && modifyopt != 6 && modifyopt != 7) {

					printf("Invalid choice!Please re-enter\n");
					printf("1.Modify Product Name\n");
					printf("2.Modify Price of the Product\n");
					printf("3.Modify Quantity of the Product\n");
					printf("4.Modify Quantity Sold of the Product\n");
					printf("5.Modify Quantity remaining of the Product\n");
					printf("6.Modify All\n");
					printf("Enter your choice:");
					scanf("%d", &modifyopt);
				}

				switch (modifyopt) {

				case 1:
					rewind(stdin);
					printf("Enter New Product Name (in capital letter):");
					scanf("%s", &newprodName);
					rewind(stdin);
					printf("Sure to Modify ( Y = yes ) ?");
					scanf("%c", &suremodify);
					if (suremodify == 'Y' || suremodify == 'y') {
						strcpy(MSS[i].MprodName, newprodName);
						printf("Modify Successfully !\n");
						modifycount++;
						printf("%d record(s) modified\n", modifycount);
					}
					break;

				case 2:
					rewind(stdin);
					printf("Enter New Price of the Product (in RM):");
					scanf("%lf", &newprice);
					rewind(stdin);
					printf("Sure to Modify ( Y = yes ) ?");
					scanf("%c", &suremodify);
					if (suremodify == 'Y' || suremodify == 'y') {
						MSS[i].Mprice = newprice;
						printf("Modify Successfully !\n");
						modifycount++;
						printf("%d record(s) modified\n", modifycount);
					}
					break;

				case 3:
					rewind(stdin);
					printf("Enter New quantity of the Product:");
					scanf("%d", &newqty);
					rewind(stdin);
					printf("Sure to Modify ( Y = yes ) ?");
					scanf("%c", &suremodify);
					if (suremodify == 'Y' || suremodify == 'y') {
						MSS[i].Mqty = newqty;
						printf("Modify Successfully !\n");
						modifycount++;
						printf("%d record(s) modified\n", modifycount);
					}
					break;

				case 4:
					rewind(stdin);
					printf("Enter New quantity sold of the Product:");
					scanf("%d", &newqtysold);
					rewind(stdin);
					printf("Sure to Modify ( Y = yes ) ?");
					scanf("%c", &suremodify);
					if (suremodify == 'Y' || suremodify == 'y') {
						MSS[i].Mqtysold = newqtysold;
						printf("Modify Successfully !\n");
						modifycount++;
						printf("%d record(s) modified\n", modifycount);
					}
					break;

				case 5:
					rewind(stdin);
					printf("Enter New quantity left of the Product:");
					scanf("%d", &newremain);
					rewind(stdin);
					printf("Sure to Modify ( Y = yes ) ?");
					scanf("%c", &suremodify);
					if (suremodify == 'Y' || suremodify == 'y') {
						MSS[i].Mremain = newremain;
						printf("Modify Successfully !\n");
						modifycount++;
						printf("%d record(s) modified\n", modifycount);
					}
					break;

				case 6:

					rewind(stdin);
					printf("Enter New Product Name (in capital letter):");
					scanf("%s", &newprodName);
					rewind(stdin);

					printf("Enter New Price of the Product (in RM):");
					scanf("%lf", &newprice);
					rewind(stdin);

					printf("Enter New quantity of the Product:");
					scanf("%d", &newqty);
					rewind(stdin);

					printf("Enter New quantity sold of the Product:");
					scanf("%d", &newqtysold);
					rewind(stdin);

					printf("Enter New quantity left of the Product:");
					scanf("%d", &newremain);
					rewind(stdin);

					rewind(stdin);
					printf("Sure to Modify ( Y = yes ) ?");
					scanf("%c", &suremodify);
					if (suremodify == 'Y' || suremodify == 'y') {
						strcpy(MSS[i].MprodName, newprodName);
						MSS[i].Mprice = newprice;
						MSS[i].Mqty = newqty;
						MSS[i].Mqtysold = newqtysold;
						MSS[i].Mremain = newremain;
						printf("Modify Successfully !\n");
						modifycount++;
						printf("%d record(s) modified\n", modifycount);
					}
					break;

				}


			}
		}

		if (modifycount == 0) {
			printf("Modified unsucessfully!\n");
			printf("No Records found!\n");

		}

		printf("Modify Another record ? (Y=YES,N=NO):");
		rewind(stdin);
		scanf("%c", &anotherMchoice);

		//validation 
		while (toupper(anotherMchoice) != 'Y' && toupper(anotherMchoice) != 'N')
		{
			printf("Please key in correct value for continue(Y=YES ; N=NO):");
			rewind(stdin);
			scanf("%c", &anotherMchoice);
			anotherMchoice = toupper(anotherMchoice);
		}

	} while (toupper(anotherMchoice) == 'Y');

	FILE* Minptr;
	Minptr = fopen("stocksales.txt", "w");
	for (i = 0; i < Mcount; i++) {
		fprintf(Minptr, "%s %s %.2lf %d %d %d\n", MSS[i].MSalesId, MSS[i].MprodName, MSS[i].Mprice, MSS[i].Mqty, MSS[i].Mqtysold, MSS[i].Mremain);
	}

	fclose(Minptr);

}

void modifysalesstaff() {
	int Mcount2 = 0, checkSI, checkEI, modifycount2 = 0;
	char anotherMchoice2, mdysalesid2[10], mdystaffid[10], suremodify2;
	int i, modifyopt2;
	char newsalesid2[10], newstaffname[30], newstaffid[10], newprodName[30];
	int newqtysold;
	double newstockprice;


	FILE* Mptr2;
	Mptr2 = fopen("salesstaff.txt", "r");

	if (Mptr2 == NULL) {
		printf("Unablle to open the file\n");
		exit(-1);

	}

	while (fscanf(Mptr2, "%s %s %s %d %s %lf\n", &SR.salesId, &SR.staffname, &SR.staffid, &SR.qtysold, &SR.prodName, &SR.stockprice) != EOF) {
		strcpy(MSR[Mcount2].MSalesId, SR.salesId);
		strcpy(MSR[Mcount2].Mstaffname, SR.staffname);
		strcpy(MSR[Mcount2].MStaffid, SR.staffid);
		MSR[Mcount2].Mqtysold = SR.qtysold;
		strcpy(MSR[Mcount2].MprodName, SR.prodName);
		MSR[Mcount2].Mstockprice = SR.stockprice;
		Mcount2++;
	}

	fclose(Mptr2);

	printf("Modify sales that made by staff\n");
	printf("===============================\n");

	do {

		do {
			printf("Enter sales id (SXXX) that you want to modify:");
			scanf("%s", &mdysalesid2);
			rewind(stdin);
			checkSI = codeValidation(mdysalesid2, 'S', "salesid");
		} while (checkSI == 0);

		do {
			printf("Enter staff id (EXXX) that you want to modify:");
			scanf("%s", &mdystaffid);
			rewind(stdin);
			checkEI = codeValidation(mdystaffid, 'E', "staffid");
		} while (checkEI == 0);

		for (i = 0; i < Mcount2; i++) {
			if (strcmp(mdysalesid2, MSR[i].MSalesId) == 0 && strcmp(mdystaffid, MSR[i].MStaffid) == 0) {
				printf("%-15s %-15s %-16s %-10s %20s %25s\n", "SALES ID", "STAFF NAME", "STAFF ID", "SALES MADE", "PRODUCT NAME", "PRODUCT PRICE(in RM)");
				printf("------------------------------------------------------------------------------------------------------------\n");
				printf("%-15s %-15s %-16s %5d %18s %23.2lf\n", MSR[i].MSalesId, MSR[i].Mstaffname, MSR[i].MStaffid, MSR[i].Mqtysold, MSR[i].MprodName, MSR[i].Mstockprice);
				printf("1.Modify Staff Name\n");
				printf("2.Modify Product Name\n");
				printf("3.Modify Quantity Sales that made by Staff\n");
				printf("4.Modify Price of the Product\n");
				printf("5.Modify All\n");
				printf("Enter your choice:");
				scanf("%d", &modifyopt2);
				rewind(stdin);


				while (modifyopt2 != 1 && modifyopt2 != 2 && modifyopt2 != 3 && modifyopt2 != 4 && modifyopt2 != 5 && modifyopt2 != 6 && modifyopt2 != 7) {
					printf("Invalid choice!Please re-enter");
					printf("1.Modify Staff Name\n");
					printf("2.Modify Product Name\n");
					printf("3.Modify Quantity Sales that made by Staff\n");
					printf("4.Modify Price of the Product\n");
					printf("5.Modify All\n");
					printf("Enter your choice:");
					scanf("%d", &modifyopt2);
					rewind(stdin);


				}

				switch (modifyopt2) {
				case 1:
					printf("Enter New Staff Name:");
					scanf("%[^\n]", &newstaffname);
					rewind(stdin);

					printf("Sure to Modify ( Y = yes ) ?");
					rewind(stdin);
					scanf("%c", &suremodify2);
					if (suremodify2 == 'Y' || suremodify2 == 'y') {
						strcpy(MSR[i].Mstaffname, newstaffname);
						printf("Modify Successfully !\n");
						modifycount2++;
						printf("%d record(s) modified\n", modifycount2);
					}
					break;

				case 2:
					printf("Enter New Product Name (in capital letter):");
					scanf("%s", &newprodName);
					rewind(stdin);

					printf("Sure to Modify ( Y = yes ) ?");
					rewind(stdin);
					scanf("%c", &suremodify2);
					if (suremodify2 == 'Y' || suremodify2 == 'y') {
						strcpy(MSR[i].MprodName, newprodName);
						printf("Modify Successfully !\n");
						modifycount2++;
						printf("%d record(s) modified\n", modifycount2);
					}

					break;


				case 3:
					printf("Enter New Quantity Sales that made by Staff:");
					scanf("%d", &newqtysold);
					rewind(stdin);

					printf("Sure to Modify ( Y = yes ) ?");
					rewind(stdin);
					scanf("%c", &suremodify2);
					if (suremodify2 == 'Y' || suremodify2 == 'y') {
						MSR[i].Mqtysold = newqtysold;
						printf("Modify Successfully !\n");
						modifycount2++;
						printf("%d record(s) modified\n", modifycount2);
					}

					break;

				case 4:
					printf("Enter New Price of the Product (in RM):");
					scanf("%lf", &newstockprice);
					rewind(stdin);

					printf("Sure to Modify ( Y = yes ) ?");
					rewind(stdin);
					scanf("%c", &suremodify2);
					if (suremodify2 == 'Y' || suremodify2 == 'y') {
						MSR[i].Mstockprice = newstockprice;
						printf("Modify Successfully !\n");
						modifycount2++;
						printf("%d record(s) modified\n", modifycount2);
					}


					break;


				case 5:
					rewind(stdin);
					printf("Enter New Staff Name:");
					scanf("%[^\n]", &newstaffname);
					rewind(stdin);

					printf("Enter New Product Name:");
					scanf("%s", &newprodName);
					rewind(stdin);

					printf("Enter New Quantity Sales that made by Staff:");
					scanf("%d", &newqtysold);
					rewind(stdin);

					printf("Enter New Price of the Product (in RM):");
					scanf("%lf", &newstockprice);
					rewind(stdin);

					printf("Sure to Modify ( Y = yes ) ?");
					rewind(stdin);
					scanf("%c", &suremodify2);
					if (suremodify2 == 'Y' || suremodify2 == 'y') {
						strcpy(MSR[i].Mstaffname, newstaffname);
						strcpy(MSR[i].MprodName, newprodName);
						MSR[i].Mqtysold = newqtysold;
						MSR[i].Mstockprice = newstockprice;
						printf("Modify Successfully !\n");
						modifycount2++;
						printf("%d record(s) modified\n", modifycount2);
					}
					break;



				}

			}
		}

		if (modifycount2 == 0) {
			printf("Modified unsucessfully!\n");
			printf("No Records found!\n");

		}

		printf("Modify Another record ? (Y=YES,N=NO):");
		rewind(stdin);
		scanf("%c", &anotherMchoice2);

		//validation 
		while (toupper(anotherMchoice2) != 'Y' && toupper(anotherMchoice2) != 'N')
		{
			printf("Please key in correct value for continue(Y=YES ; N=NO):");
			rewind(stdin);
			scanf("%c", &anotherMchoice2);
			anotherMchoice2 = toupper(anotherMchoice2);
		}

	} while (toupper(anotherMchoice2) == 'Y');

	FILE* Minptr2;
	Minptr2 = fopen("salesstaff.txt", "w");

	for (i = 0; i < Mcount2; i++) {
		fprintf(Minptr2, "%s %s %s %d %s %.2lf\n", MSR[i].MSalesId, MSR[i].Mstaffname, MSR[i].MStaffid, MSR[i].Mqtysold, MSR[i].MprodName, MSR[i].Mstockprice);
	}

	fclose(Minptr2);

}


void salesreport() {
	int range1, range2;
	char choice;
	int chkcount = 0;
	FILE* Sptr;

	//File convert
	FILE* fptr, * convertPtr,*scanPtr;
	struct member convert;
	fptr = fopen("member.dat", "rb");
	convertPtr = fopen("memberCommission.txt", "w");
	while (fread(&convert, sizeof(struct member), 1, fptr))
	{
		fprintf(convertPtr, "%s|%s|%c|%s|%s|%s|%d|%d|%d|%d|%d\n", convert.id, convert.name, convert.gender, convert.email, convert.phone, convert.ic, convert.noIntro, convert.level, convert.bday, convert.bmonth, convert.byear);
	}
	fclose(fptr);
	fclose(convertPtr);



	do {

		printf("Enter the range of No of introduced that you want to know\n");
		printf("Min No of introduced:");
		rewind(stdin);
		scanf("%d", &range1);
		printf("Max No of introduced:");
		scanf("%d", &range2);




		printf("%-10s %-18s %-10s %20s %25s %20s\n", "MEMBER ID", "MEMBER NAME", "GENDER", "NO.INTRODUCED", "COMMISSION REWARD", "MEMBER TYPE");
		printf("--------------------------------------------------------------------------------------------------------------------\n");

		scanPtr = fopen("memberCommission.txt", "r");
		if (scanPtr == NULL) {
			printf("Unable to open the file\n");
			exit(-1);
		}
		while (fscanf(scanPtr, "%[^\|]|%[^\|]|%c|%[^\|]|%[^\|]|%[^\|]|%d|%d|%d|%d|%d\n", &convert.id, &convert.name, &convert.gender, &convert.email, &convert.phone, &convert.ic, &convert.noIntro, &convert.level, &convert.bday, &convert.bmonth, &convert.byear) != EOF) {
			
			if (convert.noIntro >= range1 && convert.noIntro <= range2) {
				if (convert.noIntro >= 1 && convert.noIntro <= 9) {
					printf("%-11s %-19s %-20c %-8d %20.2lf %20s\n", convert.id, convert.name, convert.gender, convert.noIntro, 0.05, "BASIC");
				}

				else if (convert.noIntro >= 10 && convert.noIntro <= 19) {
					printf("%-11s %-19s %-8c %-8d %20.2lf %20s\n", convert.id, convert.name, convert.gender, convert.noIntro, 0.06, "BRONZE");
				}

				else if (convert.noIntro >= 20 && convert.noIntro <= 29) {
					printf("%-11s %-19s %-8c %-8d %20.2lf %20s\n", convert.id, convert.name, convert.gender, convert.noIntro, 0.07, "SILVER");
				}

				else if (convert.noIntro >= 30 && convert.noIntro <= 39) {
					printf("%-11s %-19s %-8c %-8d %20.2lf %20s\n", convert.id, convert.name, convert.gender, convert.noIntro, 0.08, "GOLD");
				}

				else if (convert.noIntro >= 40 && convert.noIntro <= 49) {
					printf("%-11s %-19s %-8c %-8d %20.2lf %20s\n", convert.id, convert.name, convert.gender, convert.noIntro, 0.09, "PLATINUM");
				}

				else if (convert.noIntro > 49) {
					printf("%-11s %-19s %-8c %-8d %20.2lf %20s\n", convert.id, convert.name, convert.gender, convert.noIntro, 0.10, "DIAMOND");
				}
				chkcount++;
			}


		}
		fclose(scanPtr);


		if (chkcount == 0) {
			printf("No Records found!\n");
		}


		printf("\n\n");
		printf("%-10s %-18s %-10s\n", "RANKING", "COMMISSION", "NO-INTRODUCED");
		printf("===========================================================\n");
		printf("%-10s %5.2lf %20s\n", "BASIC", 0.05, "1-9");
		printf("%-10s %5.2lf %20s\n", "BRONZE", 0.06, "10-19");
		printf("%-10s %5.2lf %20s\n", "SILVER", 0.07, "20-29");
		printf("%-10s %5.2lf %20s\n", "GOLD", 0.08, "30-29");
		printf("%-10s %5.2lf %20s\n", "PLATINUM", 0.09, "40-49");
		printf("%-10s %5.2lf %20s\n", "DIAMOND", 0.10, ">49");

		printf("Continue search?(Y=YES ; N=NO):");
		rewind(stdin);
		scanf("%c", &choice);

		/*Validation*/
		while (toupper(choice) != 'Y' && toupper(choice) != 'N')
		{
			printf("Please key in correct value for continue(Y=YES ; N=NO):");
			rewind(stdin);
			scanf("%c", &choice);
			choice = toupper(choice);
		}


	} while (toupper(choice) == 'Y');

	system("cls");
	salesMenu();

}

