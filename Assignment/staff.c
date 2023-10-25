#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<windows.h>
#pragma warning(disable:4996)

//function
void selectStaff();
int staffMenu();
void displayStaff();
void addStaff();
void modifyStaff();
void searchStaff();
void deleteStaff();
void backUpStaff();
void recoveryStaff();
void displayHeader1();
void displayHeader2();
void login();
void modifyPassword();
int checkid(char idEnter[5]);
int loginCheck(char id[5], char password[71]);
void staffSalesReport();



//datafield
typedef struct
{
	char name[31];
	char idAlpha[5];
	int  birthDate, birthMonth, birthYear;
	char address[71];
	char gender;
	char password[71];
	char position[7];
	char IcNum[13];
	char email[51];
	//time and date, nested structure
	SYSTEMTIME t;
}Staff;

typedef struct
{
	char salesId[10], staffid[10];
	char staffname[30], prodName[30];
	int qtysold;
	double stockprice;

}SalesStaffRecord;

SalesStaffRecord staffsales;

void selectStaff()
{
	char con;
	int choose;

	//selection of staff function

	do
	{
		choose = staffMenu();

		if (choose == 1)
		{
			addStaff();
		}
		else if (choose == 2)
		{
			displayStaff();
		}
		else if (choose == 3)
		{
			modifyStaff();
		}
		else if (choose == 4)
		{
			searchStaff();
		}
		else if (choose == 5)
		{
			deleteStaff();
		}
		else if (choose == 6)
		{
			backUpStaff();
		}
		else if (choose == 7)
		{
			recoveryStaff();
		}
		else if (choose == 8)
		{
			modifyPassword();
		}
		else if (choose == 9)
		{
			staffSalesReport();
		}
		
		printf("Do you want to go back to the staff menu?(Yes = Y ; No = N): ");
		rewind(stdin);
		scanf("%c", &con);

		while (con != 'Y' && con != 'y' && con != 'N' && con != 'n')
		{
			printf("Invalid selection, please re-enter , Do you want to go back to the menu?(Yes = Y ; No = N): ");
			rewind(stdin);
			scanf("%c", &con);
		}
		con = toupper(con);
		
	} while (con == 'Y');

}

int staffMenu()
{
	//Staff menu display
	system("cls");
	int choose = 0;


	printf("  /$$$$$$   /$$$$$$$$ /$$$$$$   /$$$$$$$$ /$$$$$$$$\n");
	printf(" /$$__  $$ |__  $$__//$$__ $$  |$$_____/ |$$_____/\n");
	printf("| $$  \__/    | $$   | $$  \  $$ | $$      | $$      \n");
	printf("|  $$$$$$    | $$   | $$$$$$$$ | $$$$$   | $$$$$   \n");
	printf(" \____  $$    | $$   | $$__  $$ | $$__/   | $$__/   \n");
	printf(" /$$  \ $$    | $$   | $$  | $$ | $$      | $$      \n");
	printf("|  $$$$$$/   | $$   | $$  | $$ | $$      | $$      \n");
	printf(" \______/     |__/   |__/  |__/ |__/      |__/      \n");



	printf(" =============================================\n");
	printf("|1.Add new staff record %23c\n", '|');
	printf("|2.Display staff information %18c\n", '|');
	printf("|3.Modify existed staff information %11c\n", '|');
	printf("|4.Search staff information with ID %11c\n", '|');
	printf("|5.Delete staff record %24c\n", '|');
	printf("|6.Backup record for staff information %8c\n", '|');
	printf("|7.Recovery record for staff information %6c\n", '|');
	printf("|8.Modify password%29c\n", '|');
	printf("|9.Staff Sales comission Report %15c\n", '|');
	printf("|10.Exit %38c\n", '|');
	printf(" =============================================\n");
	printf("\n\n\n");
	printf("Enter integer as your selection: ");
	scanf("%d", &choose);


	//validation
	while (choose != 1 && choose != 2 && choose != 3 && choose != 4 && choose != 5 && choose != 6 && choose != 7 && choose != 8 && choose != 9 && choose != 10)
	{
		printf("Invalid number you have key in (please key in the right integer by the table given): ");
		rewind(stdin);
		scanf("%d", &choose);
	}

	return(choose);
}

//staff function
void addStaff()
{
	FILE* writePt;
	FILE* idPt;
	FILE* idEnter;
	Staff st, check;
	GetLocalTime(&st.t);
	int id, ic = 0, emailcheck = 0, emailCheck1, checkic;
	char select;
	char confirm;
	int i = 0, upperCase;



	do
	{
		
		//initialize value
		st.birthDate = 0;
		st.birthMonth = 0;
		st.birthYear = 0;
		st.name[0] = '-';
		st.password[0] = '-';
		st.address[0] = '-';
		st.IcNum[0] = '-';
		st.email[51] = '-';
		char gender;

		system("cls");

		//File opened
		writePt = fopen("staff.bin", "ab");
		idPt = fopen("idNum.bin", "rb");

		//check file exist
		if (idPt == NULL)
		{
			id = 1;
			sprintf(st.idAlpha, "E%03d", id);
		}

		//read file
		else
		{
			while (fread(&id, sizeof(id), 1, idPt))
			{
				id = id + 1;
				sprintf(st.idAlpha, "E%03d", id);
			}
			fclose(idPt);
		}
		printf(" =========================================================\n");
		printf("|                    Add new staff                        |\n");
		printf(" =========================================================\n\n");
		printf("Current ID for new staff:%s\n", st.idAlpha);
		
		
		//enter name
		printf("Enter name :");
		rewind(stdin);
		scanf("%[^\n]", &st.name);
		//validate for enter nothing
		while (st.name[0] == '-')
		{
			printf("Please enter name :");
			rewind(stdin);
			scanf("%[^\n]", &st.name);
		}
		
		//create password
		printf("Enter account password :");
		rewind(stdin);
		scanf("%[^\n]", &st.password);

		//validate for password
		while (st.password[0] == '-')
		{
			printf("Please enter sign in password :");
			rewind(stdin);
			scanf("%[^\n]", &st.password);
		}

		//enter position
		printf("Enter position (ENTER: ADMIN , STAFF ,MANAGER):");
		rewind(stdin);
		scanf("%[^\n]", &st.position);
		
		for (upperCase = 0; upperCase < 7;upperCase++)
		{
			st.position[upperCase] = toupper(st.position[upperCase]);
		}

		//validate for position
		while (strcmp(st.position, "ADMIN") != 0 && strcmp(st.position, "STAFF") != 0 && strcmp(st.position, "MANAGER") != 0)
		{
			printf("Please enter valid position (ENTER: ADMIN , STAFF ,MANAGER): ");
			rewind(stdin);
			scanf("%[^\n]", &st.position);

			for (upperCase = 0; upperCase < 7;upperCase++)
			{
				st.position[upperCase] = toupper(st.position[upperCase]);
			}
		}

		i = 0;

		//enter birthdate
		printf("Enter staff birth date: ");
		rewind(stdin);
		scanf("%d", &st.birthDate);

		//validate
		while (st.birthDate < 1 || st.birthDate > 31)
		{
			printf("please enter a valid birth date:");
			rewind(stdin);
			scanf("%d", &st.birthDate);
		}

		//enter birth month
		printf("Enter staff birth month: ");
		rewind(stdin);
		scanf("%d", &st.birthMonth);
		
		//validation
		while (st.birthMonth < 1 || st.birthMonth > 12)
		{
			printf("Please enter a valid birth month: ");
			rewind(stdin);
			scanf("%d", &st.birthMonth);
		}

		if (st.birthMonth != 1 && st.birthMonth != 3 && st.birthMonth != 5 && st.birthMonth != 7 && st.birthMonth != 8 && st.birthMonth != 10 && st.birthMonth != 12 && st.birthDate == 31)
		{
			while (st.birthDate < 1 || st.birthDate > 30)
			{
				printf("There's no %d date in %d month\n", st.birthDate, st.birthMonth);
				printf("please enter a valid birth date:");
				rewind(stdin);
				scanf("%d", &st.birthDate);
			}
		}

		while (st.birthMonth == 2 && st.birthDate > 29)
		{
			printf("Please enter a valid birth month: ");
			scanf("%d", &st.birthMonth);
			while (st.birthDate < 1 || st.birthDate > 29)
			{
				printf("please enter a valid birth date:");
				rewind(stdin);
				scanf("%d", &st.birthDate);
			}
		}

		//enter year
		printf("Enter staff birth year: ");
		rewind(stdin);
		scanf("%d", &st.birthYear);


		//validation 
		while (st.birthYear < 1900 || st.birthYear > 2020)
		{
			printf("Please enter a valid birth year: ");
			rewind(stdin);
			scanf("%d", &st.birthYear);
		}

		if (st.birthYear % 4 == 0 && st.birthYear % 100 == 0 && st.birthYear % 400 != 0 && st.birthMonth == 2 && st.birthDate == 29)
		{
			printf("Due to this year is not a leap year,February will not have 29 days\n");
			rewind(stdin);
			printf("Please valid birth date :");
			scanf("%d", &st.birthDate);

			while (st.birthDate < 1 || st.birthDate > 28)
			{
				printf("Please valid birth date :");
				rewind(stdin);
				scanf("%d", &st.birthDate);
			}
		}


		//enter address
		printf("Enter address :");
		rewind(stdin);
		scanf("%[^\n]", &st.address);

		//validate for enter empty
		while (st.address[0] == '-')
		{
			printf("Please enter address :");
			rewind(stdin);
			scanf("%[^\n]", &st.address);
		}

		//enter gender
		printf("Enter gender(M = male; F = Female):");
		rewind(stdin);
		scanf("%c", &st.gender);

		st.gender = toupper(st.gender);

		//validate for gender
		while (st.gender != 'M' && st.gender != 'F')
		{
			printf("\nPlease enter valid answer, Do you want to continue (M = Male , F = Female): ");
			rewind(stdin);
			scanf("%c", &st.gender);

			st.gender = toupper(st.gender);
		}

		st.gender = toupper(st.gender);


		//enter ic
		printf("Enter IC number (no '-' require):");
		rewind(stdin);
		scanf("%[^\n]", &st.IcNum);


		//validate for ic
		while (st.IcNum[0] == '-' || (st.IcNum[2] != '0' && st.IcNum[2] != '1') || (st.IcNum[4] != '0' && st.IcNum[4] != '1' && st.IcNum[4] != '2' && st.IcNum[4] != '3'))
		{
			printf("Please enter correct IcNum (no '-' require):");
			rewind(stdin);
			scanf("%[^\n]", &st.IcNum);
		}

		//enter email
		printf("Enter email :");
		rewind(stdin);
		scanf("%[^\n]", &st.email);

		//validate for email
		for (emailCheck1 = 0; emailCheck1 < 51; emailCheck1++)
		{
			if (st.email[emailCheck1] == '@')
			{
				emailcheck++;
			}
		}

		//validate for email format
		while (st.email[0] == '-' || emailcheck == 0)
		{
			printf("Please enter email with format(@) :");
			rewind(stdin);
			scanf("%[^\n]", &st.email);

			for (emailCheck1 = 0; emailCheck1 < 51; emailCheck1++)
			{
				if (st.email[emailCheck1] == '@')
				{
					emailcheck++;
				}
			}

		}

		system("cls");

		//confirmation for insert information
		printf("Do you sure you want to key in following data into the file:\n");
		printf("%-15s:\t%s\n", "ID", st.idAlpha);
		printf("%-15s:\t%s\n", "Name", st.name);
		printf("%-15s:\t%s\n", "Position", st.position);
		printf("%-15s:\t%02d-%02d-%04d\n", "Date of birth", st.birthDate, st.birthMonth, st.birthYear);
		printf("%-15s:\t%s\n", "Address", st.address);
		printf("%-15s:\t%c\n", "Gender", st.gender);
		printf("%-15s:\t%s\n", "Ic Number", st.IcNum);
		printf("%-15s:\t%s\n", "E-mail", st.email);
		printf("Are you sure to enter these staff information into file(Yes = Y ; No = N): ");
		rewind(stdin);
		scanf("%c", &confirm);
		confirm = toupper(confirm);



		if (confirm == 'Y')
		{
			idEnter = fopen("idNum.bin", "wb");
			fwrite(&id, sizeof(int), 1, idEnter);
			fwrite(&st, sizeof(st), 1, writePt);
			fclose(idEnter);
			printf("Information saved\n");
		}
		else
		{
			printf("Information did not save\n");
		}

		fclose(writePt);

		//continue for staff module
		printf("Do want you to continue (YES = Y ; NO = N) :");
		rewind(stdin);
		scanf("%c", &select);
		select = toupper(select);

		i = 0;


	} while (select == 'Y');


}


void displayStaff()
{
	FILE* readPt;
	readPt = fopen("staff.bin", "rb");
	int i = 1, page = 1;
	char month[4], gender[7];

	//check file exist
	if (readPt == NULL)
	{
		printf("File unable to open.");
		system("pause");
		exit(-1);
	}

	system("cls");

	Staff disStaff;

	//display staff
	do
	{
		printf(" ----------------------------------------------------------------------------------------------------------------------\n");
		printf("|                                                LIST OF STAFF                                                 Page: %02d|\n", page);
		printf("|                                                                                                                      |\n");
		displayHeader1();
		printf("| NO |  %s  | %-20s | %-12s | %8s |%-44s |%-6s|\n", "ID", "NAME", "POSITION", "DATE OF BIRTH", "ADDRESS", "GENDER");
		displayHeader2();

		int record = 0;

		while (record < 10 && fread(&disStaff, sizeof(disStaff), 1, readPt))

		{

			if (disStaff.birthMonth == 1)
			{
				strcpy(month, "JAN");
			}

			else if (disStaff.birthMonth == 2)
			{
				strcpy(month, "FEB");
			}
			else if (disStaff.birthMonth == 3)
			{
				strcpy(month, "MAC");
			}
			else if (disStaff.birthMonth == 4)
			{
				strcpy(month, "APR");
			}
			else if (disStaff.birthMonth == 5)
			{
				strcpy(month, "MAY");
			}
			else if (disStaff.birthMonth == 6)
			{
				strcpy(month, "JUN");
			}
			else if (disStaff.birthMonth == 7)
			{
				strcpy(month, "JUL");
			}
			else if (disStaff.birthMonth == 8)
			{
				strcpy(month, "AUG");
			}
			else if (disStaff.birthMonth == 9)
			{
				strcpy(month, "SEP");
			}
			else if (disStaff.birthMonth == 10)
			{
				strcpy(month, "OCT");
			}
			else if (disStaff.birthMonth == 11)
			{
				strcpy(month, "NOV");
			}
			else
			{
				strcpy(month, "DEC");
			}

			if (disStaff.gender == 'M')
			{
				strcpy(gender, "MALE");
			}
			else
			{
				strcpy(gender, "FEMALE");
			}


			printf("| %02d.| %s | %-20s | %-11s  |  %02d-%s-%04d  |%-44s |%-6s|\n", i, disStaff.idAlpha, disStaff.name, disStaff.position, disStaff.birthDate, month, disStaff.birthYear, disStaff.address, gender);
			printf(" ----------------------------------------------------------------------------------------------------------------------\n");
			printf("|Added date: %02d/%02d/%04d , Added time: %02d:%02d %76c\n", disStaff.t.wDay, disStaff.t.wMonth, disStaff.t.wYear, disStaff.t.wHour, disStaff.t.wMinute, '|');
			printf(" ----------------------------------------------------------------------------------------------------------------------\n");
			record++;
			i++;

		}
		printf("\n\n\n\n");
		page++;

	} while (!feof(readPt));

	printf(" ---------------------------------------------------------------------------------------------------------------------\n");
	printf("|                                                                                                                     |\n");
	printf("|                                          TOTAL STAFF RECORD OF STAFF :%02d                                            |\n", i - 1);
	printf("|                                                                                                                     |\n");
	printf(" ---------------------------------------------------------------------------------------------------------------------\n");
	fclose(readPt);
}

void modifyStaff()
{
	char cont;
	int upperCase;

	do {
		//declare file pointer and open file
		FILE* showPt, * readPt, * checkPt, * writePt, * copyPt, * oWritePt;
		showPt = fopen("staff.bin", "rb");
		readPt = fopen("staff.bin", "rb");
		writePt = fopen("staffTemporary.bin", "wb");
		copyPt = fopen("staffTemporary.bin", "rb");

		//declare and initialize
		Staff readStaff;
		int selection, i = 0, found = 0;
		char readId[5], confirm;

		readStaff.birthDate = 0;
		readStaff.birthMonth = 0;
		readStaff.birthYear = 0;
		readStaff.name[0] = '-';
		readStaff.address[0] = '-';
		readStaff.IcNum[0] = '-';
		readStaff.email[51] = '-';

		//check file exist
		if (readPt == NULL)
		{
			printf("file: satff.dat unable to open with read file pointer .\n");
			exit(-1);
		}
		if (showPt == NULL)
		{
			printf("file satff.dat unable to open for show file pointer.\n");
			exit(-1);
		}


		system("cls");
		printf(" =====================\n");
		printf("|ID\t\t  Name|\n");
		printf(" =====================\n");

		//list name and id exist
		while (fread(&readStaff, sizeof(Staff), 1, showPt))
		{
			printf("%s\t\t|%s\n", readStaff.idAlpha, readStaff.name);
		}

		fclose(showPt);

		//accept id to modify
		printf("\nEnter the id you want to modify: ");
		rewind(stdin);
		scanf("%s", &readId);

		do {

			checkPt = fopen("staff.bin", "rb");

			if (checkPt == NULL)
			{
				printf("file satff.dat unable to open for check file pointer.\n");
				exit(-1);
			}

			//check for id exist or not

			while (fread(&readStaff, sizeof(Staff), 1, checkPt))
			{
				if (strcmp(readStaff.idAlpha, readId) == 0)
				{
					found++;
				}
			}

			if (found == 0)
			{
				printf("\nID:%s that you enter not found in the record\n", readId);
				printf("\nPlease enter an existed ID :");
				rewind(stdin);
				scanf("%s", &readId);
			}

			fclose(checkPt);

		} while (found == 0);

		system("cls");


		while (fread(&readStaff, sizeof(Staff), 1, readPt))
		{

			if (strcmp(readStaff.idAlpha, readId) == 0)
			{

				//selection for modify
				printf("============================================\n");
				printf("              Modify section                \n");
				printf("============================================\n");
				printf("1.Name\n");
				printf("2.Position\n");
				printf("3.birth date:\n");
				printf("4.birth month\n");
				printf("5.birth year\n");
				printf("6.address\n");
				printf("7.gender\n");
				printf("8.ALL(Exclude password, email and ic) \n");
				printf("Enter which part you want to modify(1 - 8):");
				scanf("%d", &selection);

				//validation
				while (selection != 8 && selection != 7 && selection != 6 && selection != 5 && selection != 4 && selection != 3 && selection != 2 && selection != 1)
				{
					printf("\nPlease enter a valid selection (1 to 8):");
					rewind(stdin);
					scanf("%d", &selection);
				}


				if (selection == 1 || selection == 8)
				{
					printf("Enter name :");
					rewind(stdin);
					scanf("%[^\n]", &readStaff.name);
				}


				if (selection == 2 || selection == 8)
				{
					printf("Enter position (Enter: ADMIN, STAFF, MANAGER):");
					rewind(stdin);
					scanf("%[^\n]", &readStaff.position);

					for (upperCase = 0; upperCase < 7;upperCase++)
					{
						readStaff.position[upperCase] = toupper(readStaff.position[upperCase]);
					}

					while (strcmp(readStaff.position, "ADMIN") != 0 && strcmp(readStaff.position, "STAFF") != 0 && strcmp(readStaff.position, "MANAGER") != 0)
					{
						printf("Please enter valid position(Enter: ADMIN, STAFF, MANAGER): ");
						rewind(stdin);
						scanf("%[^\n]", &readStaff.position);
						for (upperCase = 0; upperCase < 7;upperCase++)
						{
							readStaff.position[upperCase] = toupper(readStaff.position[upperCase]);
						}
					}

				}

				if (selection == 3 || selection == 8)
				{
					printf("Enter staff birth date: ");
					rewind(stdin);
					scanf("%d", &readStaff.birthDate);
					while (readStaff.birthDate < 1 || readStaff.birthDate > 31)
					{
						printf("please enter a valid birth date:");
						rewind(stdin);
						scanf("%d", &readStaff.birthDate);
					}
				}
				if (selection == 4 || selection == 8)
				{
					printf("Enter staff birth month: ");
					rewind(stdin);
					scanf("%d", &readStaff.birthMonth);
					//validation for month
					while (readStaff.birthMonth < 1 || readStaff.birthMonth > 12)
					{
						printf("Please enter a valid birth month: ");
						rewind(stdin);
						scanf("%d", &readStaff.birthMonth);
					}
				}

				if (selection == 5 || selection == 8)
				{
					printf("Enter staff birth year: ");
					rewind(stdin);
					scanf("%d", &readStaff.birthYear);


					//validation for year
					while (readStaff.birthYear < 1900 || readStaff.birthYear > 2020)
					{
						printf("Please enter a valid birth year: ");
						rewind(stdin);
						scanf("%d", &readStaff.birthYear);
					}

					if (readStaff.birthYear % 4 == 0 && readStaff.birthYear % 100 == 0 && readStaff.birthYear % 400 != 0 && readStaff.birthMonth == 2 && readStaff.birthDate == 29)
					{
						printf("Due to this year is not a leap year,February will not have 29 days\n");
						printf("Please valid birth date :");
						rewind(stdin);
						scanf("%d", &readStaff.birthDate);

						while (readStaff.birthDate < 1 || readStaff.birthDate > 28)
						{
							printf("Please enter valid birth date :");
							rewind(stdin);
							scanf("%d", &readStaff.birthDate);
						}
					}

				}
				//enter address
				if (selection == 6 || selection == 8)
				{
					printf("Enter address :");
					rewind(stdin);
					scanf("%[^\n]", &readStaff.address);


				}//enter gender
				if (selection == 7 || selection == 8)
				{
					printf("Enter gender(M = male; F = Female):");
					rewind(stdin);
					scanf("%c", &readStaff.gender);

					readStaff.gender = toupper(readStaff.gender);

					while (readStaff.gender != 'M' && readStaff.gender != 'F')
					{
						printf("\nPlease enter valid answer, Do you want to continue (M = Male , F = Female): ");
						rewind(stdin);
						scanf("%c", &readStaff.gender);

						readStaff.gender = toupper(readStaff.gender);
					}
					readStaff.gender = toupper(readStaff.gender);
				}
				
				printf("\n");

			}

			fwrite(&readStaff, sizeof(Staff), 1, writePt);
		}


		fclose(readPt);
		fclose(writePt);

		//check file open
		if (copyPt == NULL)
		{
			printf("file: staffTemporary.dat unable to open with copy file pointer .\n");
			exit(-1);
		}
		//confirmation
		printf("Do you sure you want to modify the id :%s (Yes = Y || No = N)", readId);
		rewind(stdin);
		scanf("%c", &confirm);
		//validation
		while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n')
		{
			printf("\nPlease enter a valid value, do you want to modify other id?(Yes = Y || No = N): ");
			rewind(stdin);
			scanf("%c", &confirm);
		}

		confirm = toupper(confirm);
		//saved the record changes
		if (confirm == 'Y')
		{
			oWritePt = fopen("staff.bin", "wb");
			while (fread(&readStaff, sizeof(Staff), 1, copyPt))
			{
				fwrite(&readStaff, sizeof(Staff), 1, oWritePt);
			}
			printf("\nModified record saved successfully.\n");
			fclose(oWritePt);
		}
		else
		{
			printf("\nModify information is not recorded\n");
		}
		//confirmation
		printf("\nDo you want to modify other id?(Yes = Y || No = N): ");
		rewind(stdin);
		scanf("%c", &cont);

		while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n')
		{
			printf("\nPlease enter a valid value, do you want to modify other id?(Yes = Y || No = N): ");
			rewind(stdin);
			scanf("%c", &cont);
		}

		cont = toupper(cont);

	} while (cont == 'Y');

}

void searchStaff()
{
	char cont;

	do {
		//declaration
		system("cls");
		FILE* searchPt;
		searchPt = fopen("staff.bin", "rb");
		char search[31], gender[7], oriName[31], oriId[5];
		int i;
		Staff searchStaff;

		//check file open
		if (searchPt == NULL)
		{
			printf("File: staff.bin unable to open");
			exit(-1);
		}
		//enter value
		printf("\nEnter id or name to search the record you want(ID: EXXX or Name): ");
		rewind(stdin);
		scanf("%[^\n]", &search);

		//printf result
		while (fread(&searchStaff, sizeof(Staff), 1, searchPt))
		{
			strcpy(oriId, searchStaff.idAlpha);
			strcpy(oriName, searchStaff.name);

			for (i = 0;i < 31;i++)
			{
				search[i] = toupper(search[i]);
				searchStaff.idAlpha[i] = toupper(searchStaff.idAlpha[i]);
				searchStaff.name[i] = toupper(searchStaff.name[i]);
			}
			if (strcmp(searchStaff.idAlpha, search) == 0 || strcmp(searchStaff.name, search) == 0)
			{
				printf("===============================================================================\n");
				printf("|        Name:%s             \t\t\t\t       ID:%s|\n", searchStaff.name, searchStaff.idAlpha);
				printf("===============================================================================\n");
				printf("|Staff ID:%30s\n", oriId);
				printf("|Staff Name:%32s\n", oriName);
				printf("|Staff Birthdate:                   %d-%d-%d             \n", searchStaff.birthDate, searchStaff.birthMonth, searchStaff.birthYear);
				printf("|Staff Address:%33s\n", searchStaff.address);
				printf("|Staff position:%25s\n", searchStaff.position);
				printf("|Staff Ic:%38s\n", searchStaff.IcNum);
				printf("|Staff E-mail:%40s\n", searchStaff.email);

				if (gender == 'M')
					printf("|Staff gender:%28s\n", "Male");
				else
					printf("|Staff gender:%28s\n", "Female");


				printf("===============================================================================\n");
			}
		}
		//confirmation
		printf("\nDo you want to search other staff?(Yes = Y || No = N): ");
		rewind(stdin);
		scanf("%c", &cont);
		//validation
		while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n')
		{
			printf("\nPlease enter a valid value, do you want to search other staff?(Yes = Y || No = N): ");
			rewind(stdin);
			scanf("%c", &cont);
		}

		fclose(searchPt);
		cont = toupper(cont);
	} while (cont == 'Y');
}

void deleteStaff()
{
	char cont;
	FILE* showPt, * deletePt, * readPt, * oWritePt, * readPt2, * idRead, * idUpdate, * checkPt;

	do {
		//validation
		char id[5], confirm;
		int i = 0, j = 1, update;
		int idCheck2;
		Staff deleteStaff;


		system("cls");

		//open file
		showPt = fopen("staff.bin", "rb");
		//check file open
		if (showPt == NULL)
		{
			printf("File: staff.bin unable to open");
			exit(-1);
		}
		//list information
		while (fread(&deleteStaff, sizeof(Staff), 1, showPt))
		{

			printf("Staff ID:%s\n", deleteStaff.idAlpha);
			printf("Staff Name:%s\n\n", deleteStaff.name);

		}

		fclose(showPt);

		printf("\nEnter an id to delete the record you want: ");
		rewind(stdin);
		scanf("%[^\n]", &id);

		//valid checking for existing id
		do
		{
			int idCheck = 0;
			checkPt = fopen("staff.bin", "rb");

			while (fread(&deleteStaff, sizeof(Staff), 1, checkPt))
			{

				if (strcmp(deleteStaff.idAlpha, id) == 0)
				{
					idCheck++;
				}

			}

			if (idCheck == 0)
			{
				printf("Id did not exist,please re-enter a valid id: ");
				rewind(stdin);
				scanf("%[^\n]", &id);
				fclose(checkPt);
			}
			idCheck2 = idCheck;

		} while (idCheck2 == 0);

		do
		{
			deletePt = fopen("staffDelete.bin", "wb");
			readPt = fopen("staff.bin", "rb");

			if (readPt == NULL)
			{
				printf("File: staff.bin unable to open");
				exit(-1);
			}

			while (fread(&deleteStaff, sizeof(Staff), 1, readPt))
			{

				idRead = fopen("idNum.bin", "rb");

				if (idRead == NULL)
				{
					printf("File:idNum.bin unable to open");
					exit(-1);
				}

				while (fread(&update, sizeof(int), 1, idRead))
				{
					update = update - 1;
				}

				fclose(idRead);
				if (strcmp(deleteStaff.idAlpha, id) != 0 && j <= update)
				{
					sprintf(deleteStaff.idAlpha, "E%03d", j);
					fwrite(&deleteStaff, sizeof(Staff), 1, deletePt);
					j++;
				}
				else
					i++;

			}

			fclose(readPt);
			fclose(deletePt);

			if (i == 0)
			{
				printf("\nEnter a valid id to delete the record you want: ");
				rewind(stdin);
				scanf("%[^\n]", &id);
			}


		} while (i == 0);

		readPt2 = fopen("staffDelete.bin", "rb");

		printf("Are you sure to delete record for id:%s (Yes = Y|| No = N): ", id);
		rewind(stdin);
		scanf("%c", &confirm);

		while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n')
		{
			printf("\nPlease enter a valid value, do you want to search other staff?(Yes = Y || No = N): ");
			rewind(stdin);
			scanf("%c", &confirm);
		}

		confirm = toupper(confirm);

		if (confirm == 'Y')
		{

			idRead = fopen("idNum.bin", "rb");

			if (idRead == NULL)
			{
				printf("File:idNum.bin unable to open");
				exit(-1);
			}

			//update id number
			fread(&update, sizeof(update), 1, idRead);
			idUpdate = fopen("idNum.bin", "wb");
			update = update - 1;
			fwrite(&update, sizeof(update), 1, idUpdate);
			fclose(idUpdate);

			oWritePt = fopen("staff.bin", "wb");

			while (fread(&deleteStaff, sizeof(Staff), 1, readPt2))
			{

				fwrite(&deleteStaff, sizeof(Staff), 1, oWritePt);

			}

			printf(" id:%s has been removed successfully. ", id);


			fclose(idRead);
			fclose(oWritePt);
		}
		else
		{
			printf("id:%s has been remove unsuccessfully.", id);
		}



		printf("\nDo you want to delete other staff?(Yes = Y || No = N): ");
		rewind(stdin);
		scanf("%c", &cont);


		while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n')
		{
			printf("\nPlease enter a valid value, do you want to delete other staff?(Yes = Y || No = N): ");
			rewind(stdin);
			scanf("%c", &cont);
		}


		cont = toupper(cont);

	} while (cont == 'Y');

}

void backUpStaff()
{
	FILE* backUpPt, * readPt;
	Staff backUp;
	char confirm;
	readPt = fopen("staff.bin", "rb");

	if (readPt == NULL)
	{
		printf("Unable to opened file staff.bin\n");
		exit(-1);
	}

	printf("Do you want to back up all these record?(Yes = Y | No = N): ");
	rewind(stdin);
	scanf("%c", &confirm);
	confirm = toupper(confirm);

	//validation
	while (confirm != 'Y' && confirm != 'N')
	{
		printf("Please enter a valid value, do you want to back up all these record?(Yes = Y | No = N): ");
		rewind(stdin);
		scanf("%c", &confirm);
	}
	//backup data
	if (confirm == 'Y')
	{
		backUpPt = fopen("backUpStaff.bin", "wb");
		while (fread(&backUp, sizeof(Staff), 1, readPt))
		{
			fwrite(&backUp, sizeof(Staff), 1, backUpPt);
		}
		printf("Record has been backup !\n");
		fclose(backUpPt);
	}
	fclose(readPt);
}

void recoveryStaff()
{
	FILE* recoverPt, * readPt, * idNumUpdate;
	Staff recover;
	char confirm;
	int updateId = 0;
	readPt = fopen("backUpStaff.bin", "rb");
	if (readPt == NULL)
	{
		printf("Unable to opened file backUpStaff.bin\n");
		exit(-1);
	}

	printf("Do you want to recover all the record from the latest backup?(Yes = Y | No = N): ");
	rewind(stdin);
	scanf("%c", &confirm);
	confirm = toupper(confirm);

	while (confirm != 'Y' && confirm != 'N')
	{
		printf("Please enter a valid value, do you want to back up all these record?(Yes = Y | No = N): ");
		rewind(stdin);
		scanf("%c", &confirm);
	}
	//recover back the information
	if (confirm == 'Y')
	{
		recoverPt = fopen("staff.bin", "wb");
		idNumUpdate = fopen("idNum.bin", "wb");
		while (fread(&recover, sizeof(Staff), 1, readPt))
		{
			fwrite(&recover, sizeof(Staff), 1, recoverPt);
			updateId++;
		}
		fwrite(&updateId, sizeof(int), 1, idNumUpdate);
		fclose(recoverPt);
		fclose(idNumUpdate);
		printf("Record has been recover !\n");
	}
	fclose(readPt);
}

void displayHeader1()
{
	printf("|======================================================================================================================|\n");
	printf("|    |      |                      |              |               |                                             |      |\n");
}
void displayHeader2()
{
	printf("|    |      |                      |              |               |                                             |      |\n");
	printf("|======================================================================================================================|\n");
}

void login()
{
	FILE* readPt;
	char star, id[5], password[71];
	int i, check = 0, checkSkip = 0, checkRecovery = 0;
	Staff login;
	//header
	printf(" =================================\n");
	printf("|              Log-in             |\n");
	printf(" =================================\n");
	printf("Enter ID (EXXX): ");
	rewind(stdin);
	scanf("%[^\n]", &id);
	//make it uppercase
	for (i = 0; i < 5; i++)
	{
		id[i] = toupper(id[i]);
	}

	

	if (strcmp(id, "SKIP") != 0)
	{

		i = 0;
		
		printf("Enter password:");
		while (1)
		{
			star = _getch();
			if (star == 13)
			{
				password[i] = '\0';
				break;
			}
			else if (star == 8 && i > 0)
			{
				i--;
				printf("\b \b");
			}
			else
			{
				password[i] = star;
				i++;
				printf("*");
			}

		}
		
		check = loginCheck(id, password);
		do
		{
			i = 0;

			if (check != 1)
			{
				printf("\n\n");
				printf("\nPlease enter an existed id: ");
				rewind(stdin);
				scanf("%[^\n]", &id);
				for (i = 0; i < 5; i++)
				{
					id[i] = toupper(id[i]);
				}

				i = 0;

				printf("Enter password:");
				while (1)
				{
					star = _getch();
					rewind(stdin);
					if (star == 13)
					{
						password[i] = '\0';
						break;
					}
					else if (star == 8 && i > 0)
					{
						i--;
						printf("\b \b");
					}
					else
					{
						password[i] = star;
						i++;
						printf("*");
					}

				}

				check = loginCheck(id,password);

			}
		} while (check != 1);

		i = 0;

	}


}



void modifyPassword()
{
	system("cls");
	FILE* writePt, * readPt, * write2Pt;
	Staff modifyPs;
	char idEnter[5], id[5], confirm;
	char newPassword[71], confirmPassword[71];
	int num,check;

	printf(" ==========================================================\n");
	printf("|                      Modify Password                     |\n");
	printf(" ==========================================================\n");

	printf("Enter id:");
	rewind(stdin);
	scanf("%[^\n]", &idEnter);
	
	for (num = 0; num < 5; num++)
	{
		idEnter[num] = toupper(idEnter[num]);
	}

		check = 0;
		check = checkid(idEnter);
	
		while (check != 1)
		{
			printf("Enter existed staff id(E001):");
			rewind(stdin);
			scanf("%[^\n]", &idEnter);
			for (num = 0; num < 5; num++)
			{
				idEnter[num] = toupper(idEnter[num]);
			}
			check = checkid(idEnter);
		}
	

	readPt = fopen("staff.bin", "rb");
	if (readPt == NULL)
	{
		printf("unable to open file staff.bin");
		exit(-1);
	}

	writePt = fopen("staffTemporary.bin", "wb");

	while (fread(&modifyPs, sizeof(Staff), 1, readPt))
	{
		if (strcmp(idEnter, modifyPs.idAlpha) == 0)
		{
			do
			{
				printf("\nCurrent ID: %s\n", modifyPs.idAlpha);
				printf("Enter new password: ");
				rewind(stdin);
				scanf("%[^\n]", &newPassword);
				printf("Re-enter new password: ");
				rewind(stdin);
				scanf("%[^\n]", &confirmPassword);
			} while (strcmp(newPassword, confirmPassword) != 0);
			
			strcpy(modifyPs.password, confirmPassword);
			fwrite(&modifyPs, sizeof(Staff), 1, writePt);
		}
		else 
		{
			fwrite(&modifyPs, sizeof(Staff), 1, writePt);
		}
	}
	fclose(readPt);
	fclose(writePt);
	
	printf("Do you sure to change your password(Yes = Y| No = N): ");
	rewind(stdin);
	scanf("%c", &confirm);
	confirm = toupper(confirm);

	while (confirm != 'Y' && confirm != 'N')
	{
		printf("Invalid value, do you sure to change your password(Yes = Y| No = N):");
		rewind(stdin);
		scanf("%c", &confirm);
		confirm = toupper(confirm);
	}
	

	if(confirm == 'Y')
	{
		readPt = fopen("staffTemporary.bin", "rb");
		write2Pt = fopen("staff.bin", "wb");
		while (fread(&modifyPs, sizeof(Staff), 1, readPt))
		{
			fwrite(&modifyPs, sizeof(Staff), 1,write2Pt );
		}
		fclose(readPt);
		fclose(write2Pt);

		printf("\nPassword changed\n");
	}
	else
	{
		printf("Password did not changes.\n");
	}
	
}

void staffSalesReport()
{
	int range1, range2;
	char choice;
	int check = 0,num,i;
	char empId[5];
	FILE * readsalesPt;
	double totalAmount =0.00,commission = 0.00;

	system("cls");
	printf(" ==========================\n");
	printf("|                          |\n");
	printf("|Report of staff commission|\n");
	printf("|                          |\n");
	printf(" ==========================\n\n");
	printf(" Enter EmployeeId: ");
	rewind(stdin);
	scanf("%[^\n]", &empId);

	for (num = 0; num < 5; num++)
	{
		empId[num] = toupper(empId[num]);
	}

	check = checkid(empId);
	
	while (check != 1)
	{
		printf("\n");
		printf("Enter existed staff id(E001):");
		rewind(stdin);
		scanf("%[^\n]", &empId);
		for (num = 0; num < 5; num++)
		{
			empId[num] = toupper(empId[num]);
		}
		check = checkid(empId);
	}

	//File convert
	FILE* fptr, * convertPtr, * convertPtr1;
	fptr = fopen("salesstaff.txt", "r");
	if (fptr == NULL)
	{
		printf("\nUnable to open file salesstaff.txt\n");
		exit(-1);
	}
	convertPtr = fopen("salesStaffRecord1.bin", "wb");

	while (fscanf(fptr, "%s %s %s %d %s %lf\n", &staffsales.salesId, &staffsales.staffname, &staffsales.staffid, &staffsales.qtysold, &staffsales.prodName, &staffsales.stockprice) != EOF)
	{
		fwrite(&staffsales, sizeof(SalesStaffRecord), 1, convertPtr);
		
	}

	fclose(fptr);

	fclose(convertPtr);

	system("cls");
	printf("\n\n\n");

	printf(" ");
	for (i = 0;i < 139; i++)
	{
		printf("-");
	}
	printf(" \n");
	printf("|                              %110s\n", "|");
	printf("|                                                 Commision charge by employee and sales made      %42s\n",  "|");
	printf("|                              %110s\n", "|");
	printf("|");
	for (i = 0;i < 139; i++)
	{
		printf("-");
	}
	printf("|\n");
	printf("|                              %110s\n", "|");
	printf("|%-25s %-15s %-15s %-15s %-15s %-15s %s   |\n", "Name", "EmployeeId", "SalesID", "Item sold", "Quantity sold", "Total sales amount(each)", "Commission charge(5%)");
	printf("|                              %110s\n", "|");
	printf("|-------------------------------------------------------------------------------------------------------------------------------------------|\n");
	readsalesPt = fopen("salesStaffRecord1.bin", "rb");
	while (fread(&staffsales, sizeof(SalesStaffRecord), 1, readsalesPt))
	{
		if (strcmp(empId, staffsales.staffid) == 0)
		{
			printf("|%-25s %-15s %-15s %-15s %-15d RM%-22.2lf RM%7.2lf               |\n", staffsales.staffname, staffsales.staffid, staffsales.salesId, staffsales.prodName, staffsales.qtysold, staffsales.stockprice * staffsales.qtysold, (staffsales.stockprice * staffsales.qtysold) * 0.05);
			totalAmount += staffsales.stockprice * staffsales.qtysold;;
			commission += (staffsales.stockprice * staffsales.qtysold) * 0.05;
		}
	}
	fclose(readsalesPt);
	printf(" ------------------------------------------------------------------------------------------------------------------------------------------- \n");
	printf("|                              %110s\n", "|");
	printf("|Total sales amount(All sales):      :  RM%9.2lf %89s\n", totalAmount,"|");
	printf("|Total commission amount(All sales)  :  RM%9.2lf %89s\n", commission,"|");
	printf("|                              %110s\n", "|");
	printf(" ------------------------------------------------------------------------------------------------------------------------------------------- \n");
	printf("\n                                                               --End Of Report--                                                                  \n");

	printf("\n\n");
}






//validation for id 
int checkid(char idEnter[5])
{

	FILE *readPt;
	int check;
	Staff checkStaffId;
	readPt = fopen("staff.bin", "rb");
	check = 0;

	if (readPt == NULL)
	{
		printf("unable to open file staff.bin");
		exit(-1);
	}


	while (fread(&checkStaffId, sizeof(Staff), 1, readPt))
	{
		if (strcmp(idEnter, checkStaffId.idAlpha) == 0)
		{
			check++;
		}
	}
	fclose(readPt);

	if(check == 0)
	{
		printf("Record ID not found.\n");
	}

	return (check);
}

//validation for id and password
int loginCheck(char id[5], char password[71])
{
	FILE* readPt;
	int check;
	Staff checkStaffLogin;
	readPt = fopen("staff.bin", "rb");

	if (readPt == NULL)
	{
		printf("unable to open file staff.bin");
		exit(-1);
	}

	check = 0;

	readPt = fopen("staff.bin", "rb");
	while (fread(&checkStaffLogin, sizeof(Staff), 1, readPt))
	{
		if (strcmp(id, checkStaffLogin.idAlpha) == 0 && strcmp(password, checkStaffLogin.password) == 0)
		{
			check++;
		}
	}
	
	if (check == 0)
	{
		printf("\nInvalid password or ID");
	}

	fclose(readPt);

	return (check);

}

