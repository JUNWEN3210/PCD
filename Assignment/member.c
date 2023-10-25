#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <string.h>
#pragma warning (disable:4996)

void memberMenu();
void addMember();
void displayMember();
void modifyMember();
void deleteMember();
void levelMember();
void searchMember();
double discountMember(int level);


struct member {
	char id[5], name[50], gender, email[25], phone[12], ic[20];
	int noIntro, level;
	int bday, bmonth, byear;
}m;


struct member mb[50];
SYSTEMTIME t;


void memberMenu() {
	int choice;

	system("cls");

	printf("\n");
	printf(" /$$      /$$                         /$$                                 /$$      /$$  /$$$     /$$   /$$\n");
	printf("| $$$    /$$$                        | $$                                | $$$    /$$$ /$$ $$   | $$  | $$\n");
	printf("| $$$$  /$$$$  /$$$$$$  /$$$$$$/$$$$ | $$$$$$$   /$$$$$$   /$$$$$$       | $$$$  /$$$$|  $$$    | $$  | $$\n");
	printf("| $$ $$/$$ $$ /$$__  $$| $$_  $$_  $$| $$__  $$ /$$__  $$ /$$__  $$      | $$ $$/$$ $$ /$$ $$/$$| $$$$$$$$\n");
	printf("| $$  $$$| $$| $$$$$$$$| $$ \\ $$ \\ $$| $$  \\ $$| $$$$$$$$| $$  \\__/      | $$  $$$| $$| $$  $$_/| $$__  $$\n");
	printf("| $$\\  $ | $$| $$_____/| $$ | $$ | $$| $$  | $$| $$_____/| $$            | $$\\  $ | $$| $$\\  $$ | $$  | $$\n");
	printf("| $$ \\/  | $$|  $$$$$$$| $$ | $$ | $$| $$$$$$$/|  $$$$$$$| $$            | $$ \\/  | $$|  $$$$/$$| $$  | $$\n");
	printf("|__/     |__/ \\_______/|__/ |__/ |__/|_______/  \\_______/|__/            |__/     |__/ \\____/\\_/|__/  |__/\n");
	printf("==========================================================================================================\n");

	printf("\nMember Information\n");
	printf("==================\n");
	printf("1 - Add Member\n");
	printf("2 - Display Member\n");
	printf("3 - Modify Member\n");
	printf("4 - Delete Member\n");
	printf("5 - Level Member\n");
	printf("6 - Search Member\n");
	printf("7 - Exit\n");
	printf("Enter your choice > ");
	scanf("%d", &choice);

	while (choice <= 0 || choice > 7)
	{
		printf("\nInvalid value\n");
		printf("Enter your choice > ");
		scanf("%d", &choice);
	}

	while (choice != 7) {
		switch (choice)
		{
		case 1:
			addMember();
			break;
		case 2:
			displayMember();
			break;
		case 3:
			modifyMember();
			break;
		case 4:
			deleteMember();
			break;
		case 5:
			levelMember();
			break;
		case 6:
			searchMember();
			break;
		case 7:
			break;
		default:
			printf("Please select correct options!");
		}
		printf("\n\nMember Information\n");
		printf("==================\n");
		printf("1 - Add Member\n");
		printf("2 - Display Member\n");
		printf("3 - Modify Member\n");
		printf("4 - Delete Member\n");
		printf("5 - Member Level Details\n");
		printf("6 - Search Member\n");
		printf("7 - Exit\n");
		printf("Enter your choice > ");
		rewind(stdin);
		scanf("%d", &choice);
	} 
}

void addMember() {
	char ans;

	FILE* fptr;
	fptr = fopen("member.dat", "ab");
	if (fptr == NULL) {
		printf("Unable to open the file.");
		exit(-1);
	}
	do {
		printf("\nEnter the member details\n");
		printf("Member Id            : ");
		rewind(stdin);
		scanf("%s", &m.id);
		printf("Name                 : ");
		rewind(stdin);
		scanf("%[^\n]", &m.name);
		printf("Gender(F/M)          : ");
		rewind(stdin);
		scanf("%c", &m.gender);
		printf("Contact Number       : ");
		rewind(stdin);
		scanf("\t%s", &m.phone);
		printf("IC (eg.020511010136) : ");
		rewind(stdin);
		scanf("%s", &m.ic);
		printf("Email                : ");
		rewind(stdin);
		scanf("%s", &m.email);
		printf("Birthday Date        : \n");
		printf("\tDay           : ");
		scanf("%d", &m.bday);
		rewind(stdin);
		printf("\tMonth         : ");
		scanf("%d", &m.bmonth);
		rewind(stdin);
		printf("\tYear          : ");
		scanf("%d", &m.byear);
		rewind(stdin);
		printf("No. introduced        : ");
		scanf("%d", &m.noIntro);
		rewind(stdin);
		printf("Level                : ");
		scanf("%d", &m.level);
		rewind(stdin);
		printf("\n");

		fwrite(&m, sizeof(struct member), 1, fptr);

		printf("Add Sucessfully.\nAdd another member(Y = yes)?");
		scanf("%c", &ans);
		rewind(stdin);
	} while (ans == 'Y' || ans == 'y');

	fclose(fptr);
}

void displayMember() {
	FILE* fptr;
	int count = 0;

	fptr = fopen("member.dat", "rb");
	if (fptr == NULL) {
		printf("Unable to open the file.");
		exit(-1);
	}
	printf("\nMember Details\n");
	printf("Member Id   Name                 Gender   Contact Number       IC             Email                   Birthday        No.Introduced    Level\n");
	printf("============================================================================================================================================\n");
	while (fread(&m, sizeof(struct member), 1, fptr) != 0) {
		printf("%-11s %-20s %-8c %-20s %-14s %-23s %2d-%2d-%-9d %-16d %d\n", m.id, m.name, m.gender, m.phone, m.ic, m.email, m.bday, m.bmonth, m.byear, m.noIntro, m.level);
		count++;
	}
	printf("============================================================================================================================================\n");
	printf("Total Member List = %d\n", count);

	fclose(fptr);
}

void modifyMember() {
	FILE* fptr, * fptr2;
	int i, mcount = 0, count = 0;
	char modifyid[5], sure, achoice;
	int mchoice;
	char newname[50], newgender, newemail[25], newphone[12], newic[20];
	int newnoIntro, newlevel;
	int newbday, newbmonth, newbyear;
	GetLocalTime(&t);

	fptr = fopen("member.dat", "rb");
	if (fptr == NULL) {
		printf("Unable to open the file.");
		exit(-1);
	}

	while (fread(&m, sizeof(struct member), 1, fptr) != 0) {
		strcpy(mb[mcount].id, m.id);
		strcpy(mb[mcount].name, m.name);
		mb[mcount].gender = m.gender;
		strcpy(mb[mcount].phone, m.phone);
		strcpy(mb[mcount].ic, m.ic);
		strcpy(mb[mcount].email, m.email);
		mb[mcount].bday = m.bday;
		mb[mcount].bmonth = m.bmonth;
		mb[mcount].byear = m.byear;
		mb[mcount].noIntro = m.noIntro;
		mb[mcount].level = m.level;
		mcount++;
	}
	printf("Data stored.\n");
	fclose(fptr);

	FILE* fp;
	fp = fopen("member.dat", "wb");

	do {
		printf("\nModify Member Details\n");
		printf("Enter Member Id that you want to modify > ");
		rewind(stdin);
		scanf("%s", &modifyid);
		for (i = 0; i < mcount; i++) {
			if (strcmp(modifyid, mb[i].id) == 0) {
				printf("\nMember Details\n");
				printf("Member Id   Name                 Gender   Contact Number       IC             Email                   Birthday        No.Introduced    Level\n");
				printf("============================================================================================================================================\n");
				printf("%-11s %-20s %-8c %-20s %-14s %-23s %d-%2d-%-9d %-16d %d\n", mb[i].id, mb[i].name, mb[i].gender, mb[i].phone, mb[i].ic, mb[i].email, mb[i].bday, mb[i].bmonth, mb[i].byear, mb[i].noIntro, mb[i].level);
				printf("============================================================================================================================================\n");
				printf("1 - Modify Name\n");
				printf("2 - Modify Gender\n");
				printf("3 - Modify Contact Number\n");
				printf("4 - Modify IC\n");
				printf("5 - Modify Email\n");
				printf("6 - Modify Birthday\n");
				printf("7 - Modify No.Introduced\n");
				printf("8 - Modify Level\n");
				printf("9 - Modify All\n");
				printf("Enter your choice > ");
				scanf("%d", &mchoice);
				switch (mchoice) {
				case 1:
					printf("Enter new name : ");
					rewind(stdin);
					scanf("%[^\n]", &newname);
					printf("Sure to Modify (Y = yes)?");
					rewind(stdin);
					scanf("%c", &sure);
					if (sure == 'Y' || sure == 'y') {
						strcpy(mb[i].name, newname);
						printf("Modify Successfully !\n");
						count++;
					}
					break;
				case 2:
					printf("Enter new gender(F = Female/M = Male) : ");
					rewind(stdin);
					scanf("%c", &newgender);
					printf("Sure to Modify (Y = yes)?");
					rewind(stdin);
					scanf("%c", &sure);
					if (sure == 'Y' || sure == 'y') {
						mb[i].gender = newgender;
						printf("Modify Successfully !\n");
						count++;
					}
					break;
				case 3:
					printf("Enter new contact number : ");
					scanf("%s", &newphone);
					rewind(stdin);
					printf("Sure to Modify (Y = yes)?");
					scanf("%c", &sure);
					if (sure == 'Y' || sure == 'y') {
						strcpy(mb[i].phone, newphone);
						printf("Modify Successfully !\n");
						count++;
					}
					break;
				case 4:
					printf("Enter new IC : ");
					scanf("%s", &newic);
					rewind(stdin);
					printf("Sure to Modify (Y = yes)?");
					scanf("%c", &sure);
					if (sure == 'Y' || sure == 'y') {
						strcpy(mb[i].ic, newic);
						printf("Modify Successfully !\n");
						count++;
					}
					break;
				case 5:
					printf("Enter new email : ");
					scanf("%s", &newemail);
					rewind(stdin);
					printf("Sure to Modify (Y = yes)?");
					scanf("%c", &sure);
					if (sure == 'Y' || sure == 'y') {
						strcpy(mb[i].email, newemail);
						printf("Modify Successfully !\n");
						count++;
					}
					break;
				case 6:
					printf("Enter new birthday date : \n");
					printf("\tNew birthday day :");
					scanf("%d", &newbday);
					rewind(stdin);
					printf("\tNew birthday month :");
					scanf("%d", &newbmonth);
					rewind(stdin);
					printf("\tNew birthday year :");
					scanf("%d", &newbyear);
					rewind(stdin);
					printf("Sure to Modify (Y = yes)?");
					scanf("%c", &sure);
					if (sure == 'Y' || sure == 'y') {
						mb[i].bday = newbday;
						mb[i].bmonth = newbmonth;
						mb[i].byear = newbyear;
						printf("Modify Successfully !\n");
						count++;
					}
					break;
				case 7:
					printf("Enter new number of introduced : ");
					scanf("%d", &newnoIntro);
					rewind(stdin);
					printf("Sure to Modify (Y = yes)?");
					scanf("%c", &sure);
					if (sure == 'Y' || sure == 'y') {
						mb[i].noIntro = newnoIntro;
						printf("Modify Successfully !\n");
						count++;
					}
					break;
				case 8:
					printf("Enter new level : ");
					scanf("%d", &newlevel);
					rewind(stdin);
					printf("Sure to Modify (Y = yes)?");
					scanf("%c", &sure);
					if (sure == 'Y' || sure == 'y') {
						mb[i].level = newlevel;
						printf("Modify Successfully !\n");
						count++;
					}
					break;
				case 9:
					rewind(stdin);
					printf("Enter new name : ");
					rewind(stdin);
					scanf("%[^\n]", &newname);
					printf("Enter new gender : ");
					rewind(stdin);
					scanf("%c", &newgender);
					printf("Enter new contact number : ");
					rewind(stdin);
					scanf("%s", &newphone);
					printf("Enter new IC : ");
					rewind(stdin);
					scanf("%s", &newic);
					printf("Enter new email : ");
					rewind(stdin);
					scanf("%s", &newemail);
					printf("Enter new birthday date : ");
					printf("\tNew birthday day :");
					scanf("%d", &newbday);
					rewind(stdin);
					printf("\tNew birthday month :");
					scanf("%d", &newbmonth);
					rewind(stdin);
					printf("\tNew birthday year :");
					scanf("%d", &newbyear);
					rewind(stdin);
					printf("Enter new number of introduced : ");
					scanf("%d", &newnoIntro);
					rewind(stdin);
					printf("Enter new level : ");
					scanf("%d", &newlevel);
					rewind(stdin);
					printf("Sure to Modify (Y = yes)?");
					rewind(stdin);
					scanf("%c", &sure);
					if (sure == 'Y' || sure == 'y') {
						strcpy(mb[i].name, newname);
						mb[i].gender = m.gender;
						strcpy(mb[i].phone, newphone);
						strcpy(mb[i].ic, newic);
						strcpy(mb[i].email, newemail);
						mb[i].bday = newbday;
						mb[i].bmonth = newbmonth;
						mb[i].byear = newbyear;
						mb[i].noIntro = newnoIntro;
						mb[i].level = newlevel;
						printf("Modify Successfully !\n");
						count++;
					}
					break;
				default:
					printf("Select the correct number!\n");
				}
			}
		}

		fwrite(&mb, sizeof(mb[0]), mcount, fp);

		printf("Modify another record (Y = Yes)?");
		rewind(stdin);
		scanf("%c", &achoice);
	} while (achoice == 'Y' || achoice == 'y');

	printf("\n%d record(s) modified\n", count);

	fclose(fp);
}

void deleteMember() {
	FILE* fptr;
	int mcount = 0, i, dltcount = 0, nondltcount;
	char dltname[50], dltchoice, dltsure;

	fptr = fopen("member.dat", "rb");
	if (fptr == NULL) {
		printf("Unable to open the file.");
		exit(-1);
	}

	while (fread(&m, sizeof(struct member), 1, fptr) == 1) {
		strcpy(mb[mcount].id, m.id);
		strcpy(mb[mcount].name, m.name);
		mb[mcount].gender = m.gender;
		strcpy(mb[mcount].phone, m.phone);
		strcpy(mb[mcount].ic, m.ic);
		strcpy(mb[mcount].email, m.email);
		mb[mcount].bday = m.bday;
		mb[mcount].bmonth = m.bmonth;
		mb[mcount].byear = m.byear;
		mb[mcount].noIntro = m.noIntro;
		mb[mcount].level = m.level;
		mcount++;
	}

	fclose(fptr);

	FILE* fp;
	fp = fopen("member.dat", "wb");

	printf("\nDelete Member Details\n");
	do {
		printf("Enter member's name : ");
		rewind(stdin);
		scanf("%[^\n]", &dltname);
		printf("Sure to delete (Y = yes)?");
		rewind(stdin);
		scanf("%c", &dltsure);
		if (dltsure == 'Y' || dltsure == 'y') {
			for (i = 0; i < mcount; i++) {
				if (strcmp(dltname, mb[i].name) == 0) {
					strcpy(mb[i].id, mb[i + 1].id);
					strcpy(mb[i].name, mb[i + 1].name);
					mb[i].gender = mb[i + 1].gender;
					strcpy(mb[i].phone, mb[i + 1].phone);
					strcpy(mb[i].ic, mb[i + 1].ic);
					strcpy(mb[i].email, mb[i + 1].email);
					mb[i].bday = mb[i + 1].bday;
					mb[i].bmonth = mb[i + 1].bmonth;
					mb[i].byear = mb[i + 1].byear;
					mb[i].noIntro = mb[i + 1].noIntro;
					mb[i].level = mb[i + 1].level;
					dltcount++;
				}
			}
		}
		rewind(stdin);
		printf("Delete another record (Y = Yes)?");
		scanf("%c", &dltchoice);
		rewind(stdin);
	} while (dltchoice == 'Y' || dltchoice == 'y');

	nondltcount = mcount - dltcount;
	fwrite(&mb, sizeof(mb[0]), nondltcount, fp);
	printf("%d record(s) deleted\n", dltcount);

	fclose(fp);
}

void levelMember() {
	FILE* fptr;
	GetLocalTime(&t);
	double discount;
	int i, mcount = 0;
	int level;

	fptr = fopen("member.dat", "rb");
	if (fptr == NULL) {
		printf("Unable to open the file.");
		exit(-1);
	}

	while (fread(&m, sizeof(struct member), 1, fptr) == 1) {
		strcpy(mb[mcount].id, m.id);
		mb[mcount].noIntro = m.noIntro;
		mb[mcount].level = m.level;
		strcpy(mb[mcount].phone, m.phone);
		strcpy(mb[mcount].email, m.email);
		mcount++;
	}

	level = mb[0].level;

	printf("Member's Level Details\n");
	printf("Level   Member Id    No.Intoduced   Discount   Email                   Contact Numer\n");
	printf("====================================================================================\n");
	for (i = 0; i < mcount; i++) {
		discount = discountMember(mb[i].level);
		printf("%-7d %-12s %-14d %-10.2f %-23s %s\n", mb[i].level, mb[i].id, mb[i].noIntro, discount, mb[i].email, mb[i].phone);
	}
	printf("=====================================================================================\n");
	printf("Date: %d/%d/%d  Time: %d:%2d\n\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute);

	fclose(fptr);
}

double discountMember(int level) {
	if (level == 5) {
		return 0.09;
	}
	else if (level == 4) {
		return 0.08;
	}
	else if (level == 3) {
		return 0.07;
	}
	else if (level == 2) {
		return 0.06;
	}
	else if (level == 1) {
		return 0.05;
	}
}

void searchMember() {
	FILE* fptr, * ptr;
	int searchChoice, mcount = 0, i;
	char searchid[5], sname[50], sgender, sphone[12], sic[20];
	int snoIntro, slevel;

	fptr = fopen("member.dat", "rb");
	if (fptr == NULL) {
		printf("Unable to open the file.");
		exit(-1);
	}

	while (fread(&m, sizeof(struct member), 1, fptr) == 1) {
		strcpy(mb[mcount].id, m.id);
		strcpy(mb[mcount].name, m.name);
		mb[mcount].gender = m.gender;
		strcpy(mb[mcount].phone, m.phone);
		strcpy(mb[mcount].ic, m.ic);
		strcpy(mb[mcount].email, m.email);
		mb[mcount].bday = m.bday;
		mb[mcount].bmonth = m.bmonth;
		mb[mcount].byear = m.byear;
		mb[mcount].noIntro = m.noIntro;
		mb[mcount].level = m.level;
		mcount++;
	}

	fclose(fptr);

	printf("\n\nSearch Member Details\n");
	printf("=====================\n");
	printf("1 - Search with Member Id\n");
	printf("2 - Search with Name\n");
	printf("3 - Search with Gender\n");
	printf("4 - Search with Contact Number\n");
	printf("5 - Search with IC\n");
	printf("6 - Search with No.Introduced\n");
	printf("7 - Search with Level\n");
	printf("8 - Exit\n");
	printf("Enter your choice > ");
	rewind(stdin);
	scanf("%d", &searchChoice);
	do {
		switch (searchChoice) {
		case 1:
			printf("Enter Member Id : ");
			scanf("%s", &searchid);
			rewind(stdin);
			printf("\nSEARCH RESULTS:\n");
			printf("Member Id   Name                 Gender   Contact Number       IC             Email                   Birthday        No.Introduced    Level\n");
			printf("============================================================================================================================================\n");
			for (i = 0; i < mcount; i++) {
				if (strcmp(searchid, mb[i].id) == 0) {
					printf("%-11s %-20s %-8c %-20s %-14s %-23s %2d-%2d-%-9d %-16d %d\n", mb[i].id, mb[i].name, mb[i].gender, mb[i].phone, mb[i].ic, mb[i].email, mb[i].bday, mb[i].bmonth, mb[i].byear, mb[i].noIntro, mb[i].level);
				}
			}
			printf("============================================================================================================================================\n");
			break;
		case 2:
			rewind(stdin);
			printf("Enter Member Name : ");
			scanf("%[^\n]", &sname);
			rewind(stdin);
			printf("\nSEARCH RESULTS:\n");
			printf("Member Id   Name                 Gender   Contact Number       IC             Email                   Birthday        No.Introduced    Level\n");
			printf("============================================================================================================================================\n");
			for (i = 0; i < mcount; i++) {
				if (strcmp(sname, mb[i].name) == 0) {
					printf("%-11s %-20s %-8c %-20s %-14s %-23s %2d-%2d-%-9d %-16d %d\n", mb[i].id, mb[i].name, mb[i].gender, mb[i].phone, mb[i].ic, mb[i].email, mb[i].bday, mb[i].bmonth, mb[i].byear, mb[i].noIntro, mb[i].level);
				}
			}
			printf("============================================================================================================================================\n");
			break;
		case 3:
			rewind(stdin);
			printf("Enter Gender(F = Female/M = Male) : ");
			scanf("%c", &sgender);
			rewind(stdin);
			printf("\nSEARCH RESULTS:\n");
			printf("Member Id   Name                 Gender   Contact Number       IC             Email                   Birthday        No.Introduced    Level\n");
			printf("============================================================================================================================================\n");
			for (i = 0; i < mcount; i++) {
				if (sgender == mb[i].gender) {
					printf("%-11s %-20s %-8c %-20s %-14s %-23s %2d-%2d-%-9d %-16d %d\n", mb[i].id, mb[i].name, mb[i].gender, mb[i].phone, mb[i].ic, mb[i].email, mb[i].bday, mb[i].bmonth, mb[i].byear, mb[i].noIntro, mb[i].level);
				}
			}
			printf("============================================================================================================================================\n");
			break;
		case 4:
			rewind(stdin);
			printf("Enter Contact Number : ");
			scanf("%s", &sphone);
			rewind(stdin);
			printf("\nSEARCH RESULTS:\n");
			printf("Member Id   Name                 Gender   Contact Number       IC             Email                   Birthday        No.Introduced    Level\n");
			printf("============================================================================================================================================\n");
			for (i = 0; i < mcount; i++) {
				if (strcmp(sphone, mb[i].phone) == 0) {
					printf("%-11s %-20s %-8c %-20s %-14s %-23s %2d-%2d-%-9d %-16d %d\n", mb[i].id, mb[i].name, mb[i].gender, mb[i].phone, mb[i].ic, mb[i].email, mb[i].bday, mb[i].bmonth, mb[i].byear, mb[i].noIntro, mb[i].level);
				}
			}
			printf("============================================================================================================================================\n");
			break;
		case 5:
			rewind(stdin);
			printf("Enter Member IC : ");
			scanf("%s", &sic);
			rewind(stdin);
			printf("\nSEARCH RESULTS:\n");
			printf("Member Id   Name                 Gender   Contact Number       IC             Email                   Birthday        No.Introduced    Level\n");
			printf("============================================================================================================================================\n");
			for (i = 0; i < mcount; i++) {
				if (strcmp(sic, mb[i].ic) == 0) {
					printf("%-11s %-20s %-8c %-20s %-14s %-23s %2d-%2d-%-9d %-16d %d\n", mb[i].id, mb[i].name, mb[i].gender, mb[i].phone, mb[i].ic, mb[i].email, mb[i].bday, mb[i].bmonth, mb[i].byear, mb[i].noIntro, mb[i].level);
				}
			}
			printf("============================================================================================================================================\n");
			break;
		case 6:
			rewind(stdin);
			printf("Enter Number Introduced : ");
			scanf("%d", &snoIntro);
			rewind(stdin);
			printf("\nSEARCH RESULTS:\n");
			printf("Member Id   Name                 Gender   Contact Number       IC             Email                   Birthday        No.Introduced    Level\n");
			printf("============================================================================================================================================\n");
			for (i = 0; i < mcount; i++) {
				if (snoIntro == mb[i].noIntro) {
					printf("%-11s %-20s %-8c %-20s %-14s %-23s %2d-%2d-%-9d %-16d %d\n", mb[i].id, mb[i].name, mb[i].gender, mb[i].phone, mb[i].ic, mb[i].email, mb[i].bday, mb[i].bmonth, mb[i].byear, mb[i].noIntro, mb[i].level);
				}
			}
			printf("============================================================================================================================================\n");
			break;
		case 7:
			rewind(stdin);
			printf("Enter Member Level : ");
			scanf("%d", &slevel);
			rewind(stdin);
			printf("\nSEARCH RESULTS:\n");
			printf("Member Id   Name                 Gender   Contact Number       IC             Email                   Birthday        No.Introduced    Level\n");
			printf("============================================================================================================================================\n");
			for (i = 0; i < mcount; i++) {
				if (slevel == mb[i].level) {
					printf("%-11s %-20s %-8c %-20s %-14s %-23s %2d-%2d-%-9d %-16d %d\n", mb[i].id, mb[i].name, mb[i].gender, mb[i].phone, mb[i].ic, mb[i].email, mb[i].bday, mb[i].bmonth, mb[i].byear, mb[i].noIntro, mb[i].level);
				}
			}
			printf("============================================================================================================================================\n");
			break;
		case 8:
			break;
		default:
			printf("Please select correct options!");
		}
		printf("\n\nSearch Member Details\n");
		printf("=====================\n");
		printf("1 - Search with Member Id\n");
		printf("2 - Search with Name\n");
		printf("3 - Search with Gender\n");
		printf("4 - Search with Contact Number\n");
		printf("5 - Search with IC\n");
		printf("6 - Search with No.Introduced\n");
		printf("7 - Search with Level\n");
		printf("8 - Exit\n");
		printf("Enter your choice > ");
		rewind(stdin);
		scanf("%d", &searchChoice);
	} while (searchChoice > 0 && searchChoice < 8);

}