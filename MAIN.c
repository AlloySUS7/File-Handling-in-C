#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <math.h>
#pragma warning(disable:4996)
#define MAINID 6969
#define N_Products 20
#define adminPass "thisisanicepassword"



typedef struct {
	char stfName[25], stfgender, stfPosition[40], contactNum[16];                   //Aloyius's struct
	int ID;
	float salary;
}Staff;

typedef struct {
	char msg[25];
	int day, month, year, hour, minute, second;                                     //Aloysius's struct
}Date;

typedef struct {
	int stockID, stockQuantity;                                                     //Gregory's struct
	char stockName[21];
	double unitPrice;
} Stock;

typedef struct {
	int stockID, IDChange, unitChange;
	char stockName[21], action[7];
	double priceChange;                                                            //Gregory's struct
	int minute, hour, day, month, year;
} History;

struct PERSN {

	char name[31];
	char gender;                                                                   //KhooLiXuan's struct
	int cntNumbr;
};
struct TIME
{
	int date, month, year;                                                        //KhooLiXuan's struct
};
typedef struct {

	int memberId;
	int tier;
	struct PERSN pDetails;
	struct TIME jDetails;                                                         //KhooLiXuan's struct
	struct TIME expDetails;
	char status;
	int discount;
	int ptAcc;

}MEM;

typedef struct {																   //Nicholas's struct
	int quantity;
	char salesID[5], itemcode[6], memberID[6], name[20]; 
	float price;
} Sales;

typedef struct {																   //Nicholas's struct
	int quantity; 
	char salesID[5], itemcode[6], memberID[6], name[20], action[7];
	float price;
	int minute, hour, day, month, year;
} His;


//Aloysius's module---------------------------------------------------------------------------------------

void historyArchive(char ans);

int chkName(char* name) {
	int j;

	for (j = 0; j < strlen(name); j++) {
		if (!isalpha(name[j]) && name[j] != ' ') {
			return 1;
		}
	}
	return 0;
}
int chkgender(char* gender) {
	if (toupper(gender) == 'M' || toupper(gender) == 'F')
		return 0;
	else
		return 1;
}
int chkPosition(int* position) {
	if (position >= 1 && position <= 8)
	{
		return 0;
	}
	else
		return 1;
}

int chkcontact(char* contactNum) {
	int i;
	if (strlen(contactNum) > 12 || strlen(contactNum) < 9)
		return 1;
	if (contactNum[0] != '0' || contactNum[1] != '1')
		return 1;
	for (i = 0; i < strlen(contactNum); i++) {
		if (!isdigit(contactNum[i]))
			return 1;
	}

	return 0;
}
void addStaff()
{
	FILE* addstf;
	Staff newStaff;
	addstf = fopen("staffInfo.bin", "rb");
	if (addstf == NULL)
	{
		printf("error!! file not found");
		exit(-1);
	}
	int i = 0, highID = 1, error, position;
	char yesno, ans, name[25], gender, contactNum[13];
	ans = 'A';
	while (fread(&newStaff, sizeof(Staff), 1, addstf) == 1)
	{
		if (highID <= newStaff.ID)
		{
			highID = newStaff.ID + 1;
		}
	}
	fclose(addstf);
	addstf = fopen("staffInfo.bin", "ab");
	do {
		newStaff.ID = highID; // Set the newStaff ID to the highest ID found
		do {
			error = 0;
			printf("Enter new Staff Name:");
			rewind(stdin);
			scanf("%[^\n]", name);
			if (chkName(name))
			{
				printf("Error!! Staff Name can only contain alphabets\n\n");
				error++;
			}
		} while (error != 0);
		do {
			error = 0;
			printf("Enter new staff's gender (M = Male, F = Female):");
			rewind(stdin);
			scanf("%c", &gender);
			if (chkgender(gender))
			{
				printf("Error!! Staff Gender only take one alphabet (M=Male, F=Female)\n\n)");
				++error;
			}
		} while (error != 0);
		do {
			error = 0;
			printf("Enter new Staff's job position:");
			printf("\n\n\t   Job Position available\n==================================================\n1.Store Manager              (salary = RM 5000.00)\n2.Sales Associate            (salary = RM 3000.00)\n3.Barista                    (salary = RM 2500.00)\n4.Beverage Specialist        (salary = RM 4000.00)\n5.Stock Clerk                (salary = RM 3000.00)\n6.Delivery Driver            (salary = RM 2500.00)\n7.Marketing Coordinator      (salary = RM 3000.00)\n8.Accounts Manager           (salary = RM 3500.00)\n\n");
			printf("Press 1 to 8 on the job position you decided on >");
			rewind(stdin);
			scanf("%d", &position);
			if (chkPosition(position))
			{
				printf("\n\n\tError!! Not within our job range\n\n");
				++error;
			}
			else
			{
				switch (position) {
				case 1:
					strcpy(newStaff.stfPosition, "Store Manager");
					newStaff.salary = 5000.00;
					break;
				case 2:
					strcpy(newStaff.stfPosition, "Sales Associate");
					newStaff.salary = 3000.00;
					break;
				case 3:
					strcpy(newStaff.stfPosition, "Barista");
					newStaff.salary = 2500.00;
					break;
				case 4:
					strcpy(newStaff.stfPosition, "Beverage Specialist");
					newStaff.salary = 4000.00;
					break;
				case 5:
					strcpy(newStaff.stfPosition, "Stock Clerk");
					newStaff.salary = 3000.00;
					break;
				case 6:
					strcpy(newStaff.stfPosition, "Delivery Driver");
					newStaff.salary = 2500.00;
					break;
				case 7:
					strcpy(newStaff.stfPosition, "Marketing Coordinator");
					newStaff.salary = 3000.00;
					break;
				case 8:
					strcpy(newStaff.stfPosition, "Accounts Manager");
					newStaff.salary = 3500.00;
					break;

				}
			}
		} while (error != 0);

		do {
			error = 0;
			printf("Enter new Staff's phone number:");
			rewind(stdin);
			scanf("%s", contactNum);
			if (chkcontact(contactNum)) {
				printf("\nError!! Phone number format is 01xxxxxxxx (and the range of digit is 10 to 11)\n\n");
				error++;
			}
		} while (error != 0);

		strcpy(newStaff.stfName, name);
		newStaff.stfgender = gender;
		strcpy(newStaff.contactNum, contactNum);


		fwrite(&newStaff, sizeof(Staff), 1, addstf);
		printf("\nNew ID generated! (%03d)\n\n", newStaff.ID);
		printf("Add more staff? (Y = Yes, press any key for No)");
		rewind(stdin);
		scanf("%c", &yesno);
		rewind(stdin);
		i++;
		highID++;
		historyArchive(ans);
	} while (toupper(yesno) == 'Y');
	fclose(addstf);
};
void displayStaff()
{
	FILE* displaystf;
	Staff staff;
	displaystf = fopen("staffInfo.bin", "rb");
	if (displaystf == NULL)
	{
		printf("error!! file not found");
		exit(-1);
	}
	printf("\n----------------------------------------------------------------------------------------------------------\n");
	printf("STAFF ID    STAFF NAME               GENDER\tJOBS\t\t\tCONTACT NUMBER\t\tSALARY\n\n========   ========================  ======\t======================  ==============\t\t==========\n");
	while (fread(&staff, sizeof(Staff), 1, displaystf) == 1)
	{
		printf("\n%03d        %-25s\t%-6c\t%-20s\t%-17s\tRM %-6.2f", staff.ID, staff.stfName, toupper(staff.stfgender), staff.stfPosition, staff.contactNum, staff.salary);
	}
	printf("\n----------------------------------------------------------------------------------------------------------\n");
	fclose(displaystf);
}
void searchStaff()
{
	FILE* search;
	Staff staff;
	search = fopen("staffInfo.bin", "rb");
	int i = 0, searchID;
	if (search == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}
	do {
		printf("\nEnter staff ID:");
		rewind(stdin);
		scanf("%d", &searchID);
		if (searchID < 0)
			printf("ID starts from 001");
	} while (searchID < 0);
	while (fread(&staff, sizeof(Staff), 1, search) == 1) {
		if (staff.ID == searchID)
		{
			printf("\n\n\t    \t ID FOUND \t\t\n");
			printf("\t=================================");
			printf("\n\t STAFF ID       : %03d \n\t STAFF NAME     : %-25s \n\t GENDER         : %-6c \n\t JOBS           : %-20s \n\t CONTACT NUMBER : %-17s \n\t SALARY         : RM %-6.2f \n", staff.ID, staff.stfName, toupper(staff.stfgender), staff.stfPosition, staff.contactNum, staff.salary);
			printf("\t=================================");
			i = 1;
			break;
		}
	}
	if (staff.ID != searchID)
		printf("\nERROR, invalid ID\n");
	fclose(search);
}
void deleteStaff()
{
	char yesno, cont, ans;
	int i = 0, infoCount, modiCount = 0, found, searchID;
	Staff staff[20], temp[20];
	ans = 'D';
	FILE* delData;
	delData = fopen("staffInfo.bin", "rb");
	if (delData == NULL)
	{
		printf("error!! file not found");
		exit(-1);
	}
	while (fread(&staff[i], sizeof(Staff), 1, delData) == 1)
		i++;
	infoCount = i;
	fclose(delData);
	do {
		printf("\nEnter Staff ID to be deleted > ");
		rewind(stdin);
		scanf("%d", &searchID);
		found = 0;
		printf("STAFF ID    STAFF NAME               GENDER\tJOBS\t\t\tCONTACT NUMBER\t\tSALARY\n\n========   ========================  ======\t======================  ==============\t\t==========\n");
		for (i = 0; i < infoCount; i++)
		{
			if (staff[i].ID == searchID)
			{
				found = 1;
				printf("\n%03d        %-25s\t%-6c\t%-20s\t%-17s\tRM %-6.2f", staff[i].ID, staff[i].stfName, toupper(staff[i].stfgender), staff[i].stfPosition, staff[i].contactNum, staff[i].salary);
				printf("\nDelete selected staff info? (Y=Yes / N=No)");
				rewind(stdin);
				scanf("%c", &yesno);
				if (toupper(yesno) == 'Y')
				{
					printf("\nDeleted!");
					for (int j = i; j < infoCount - 1; j++)
					{
						staff[j] = staff[j + 1];
					}
					infoCount--;
					break;
				}
			}
		}
		if (!found)
		{
			printf("Staff not found.\n");
		}
		else
		{
			delData = fopen("staffInfo.bin", "wb");
			if (delData == NULL)
			{
				printf("error!! file not found");
				exit(-1);
			}
			fwrite(&staff, sizeof(Staff), infoCount, delData);
			fclose(delData);
			historyArchive(ans);
		}
		printf("\nContinue? (Y=Yes) > ");
		rewind(stdin);
		scanf("%c", &cont);
	} while (toupper(cont) == 'Y');

}
void modifyStaff()
{
	char yesno, cont, contactNum[13], ans, name[25], gender;
	int i = 0, infoCount, modiCount = 0, found, searchID, opt, error, position;
	float updSLY;
	Staff staff[20];

	FILE* modify;
	ans = 'M';
	modify = fopen("staffInfo.bin", "rb");
	if (modify == NULL)
	{
		printf("error!! file not found");
		exit(-1);
	}
	while (fread(&staff[i], sizeof(Staff), 1, modify) == 1)
		i++;
	infoCount = i;
	fclose(modify);

	do
	{
		printf("\nEnter Staff ID for modification > ");
		rewind(stdin);
		scanf("%d", &searchID);
		found = 0;
		printf("STAFF ID    STAFF NAME               GENDER\tJOBS\t\t\tCONTACT NUMBER\t\tSALARY\n\n========   ========================  ======\t======================  ==============\t\t==========\n");

		for (i = 0; i < infoCount; i++)
		{

			if (searchID == staff[i].ID)
			{
				found = 1;
				printf("\n%03d        %-25s\t%-6c\t%-20s\t%-17s\tRM %-6.2f", staff[i].ID, staff[i].stfName, toupper(staff[i].stfgender), staff[i].stfPosition, staff[i].contactNum, staff[i].salary);
				printf("\nModify which Info? >\n");
				printf("--------------------\n1.Name\n2.Gender\n3.Job Position\n4.Salary\n5.ContactNumber\n(press anything to exit)\n");
				scanf("%d", &opt);
				switch (opt)
				{
				case 1:
					do {
						error = 0;
						printf("Change Staff Name To:");
						rewind(stdin);
						scanf("%[^\n]", name);
						if (chkName(name))
						{
							printf("Error!! Staff Name can only contain alphabets\n\n");
							error++;
						}
					} while (error != 0);
					strcpy(staff[i].stfName, name);
					break;
				case 2:
					do {
						error = 0;
						printf("Change gender (M = Male, F = Female):");
						rewind(stdin);
						scanf("%c", &gender);
						if (chkgender(gender))
						{
							printf("Error!! Staff Gender only take one alphabet (M=Male, F=Female)\n\n)");
							++error;
						}
					} while (error != 0);
					staff[i].stfgender = gender;
					break;
				case 3:
					do {
						error = 0;
						printf("Change Staff's job position:");
						printf("\n\n\t   Job Position available\n==================================================\n1.Store Manager              (salary = RM 5000.00)\n2.Sales Associate            (salary = RM 3000.00)\n3.Barista                    (salary = RM 2500.00)\n4.Beverage Specialist        (salary = RM 4000.00)\n5.Stock Clerk                (salary = RM 3000.00)\n6.Delivery Driver            (salary = RM 2500.00)\n7.Marketing Coordinator      (salary = RM 3000.00)\n8.Accounts Manager           (salary = RM 3500.00)\n\n");
						printf("Press 1 to 8 on the job position you decided on >");
						rewind(stdin);
						scanf("%d", &position);
						if (chkPosition(position))
						{
							printf("\n\n\tError!! Not within our job range\n\n");
							++error;
						}
						else
						{
							switch (position) {
							case 1:
								strcpy(staff[i].stfPosition, "Store Manager");
								staff[i].salary = 5000.00;
								break;
							case 2:
								strcpy(staff[i].stfPosition, "Sales Associate");
								staff[i].salary = 3000.00;
								break;
							case 3:
								strcpy(staff[i].stfPosition, "Barista");
								staff[i].salary = 2500.00;
								break;
							case 4:
								strcpy(staff[i].stfPosition, "Beverage Specialist");
								staff[i].salary = 4000.00;
								break;
							case 5:
								strcpy(staff[i].stfPosition, "Stock Clerk");
								staff[i].salary = 3000.00;
								break;
							case 6:
								strcpy(staff[i].stfPosition, "Delivery Driver");
								staff[i].salary = 2500.00;
								break;
							case 7:
								strcpy(staff[i].stfPosition, "Marketing Coordinator");
								staff[i].salary = 3000.00;
								break;
							case 8:
								strcpy(staff[i].stfPosition, "Accounts Manager");
								staff[i].salary = 3500.00;
								break;

							}
						}
					} while (error != 0);
					break;
				case 4:
					do {
						error = 0;
						printf("Current Salary for %s: RM %.2f", staff[i].stfName, staff[i].salary);
						printf("\nUpdated salary: ");
						rewind(stdin);
						scanf("%f", &updSLY);
						if (updSLY >= 1500.00 && updSLY <= 7000.00)
							staff[i].salary = updSLY;
						else
						{
							error++;
							printf("Salary can't go below 1500 or above 7000\n\n");
						}
					} while (error != 0);
					break;
				case 5:
					do {
						error = 0;
						printf("Updated Staff's phone number:");
						rewind(stdin);
						scanf("%s", contactNum);
						if (chkcontact(contactNum)) {
							printf("\nError!! Phone number format is 01xxxxxxxx (and the range of digit is 10 to 11)\n\n");
							error++;
						}
					} while (error != 0);
					strcpy(staff[i].contactNum, contactNum);
					break;
				default:
					break;
				}


				printf("Confirm to Modify (Y=yes)? > ");
				rewind(stdin);
				scanf("%c", &yesno);
				if (toupper(yesno) == 'Y')
				{
					printf("\nUpdate record:\n");
					printf("STAFF ID    STAFF NAME               GENDER\tJOBS\t\t\tCONTACT NUMBER\t\tSALARY\n\n========   ========================  ======\t======================  ==============\t\t==========\n");
					printf("\n%03d        %-25s\t%-6c\t%-20s\t%-17s\tRM %-6.2f", staff[i].ID, staff[i].stfName, toupper(staff[i].stfgender), staff[i].stfPosition, staff[i].contactNum, staff[i].salary);
					modify = fopen("staffInfo.bin", "wb");
					for (i = 0; i < infoCount; i++)
						fwrite(&staff[i], sizeof(Staff), 1, modify);
					modiCount++;
					historyArchive(ans);
				}
				fclose(modify);
				printf("\n\n\t%dRecord(s) modified.\n\n", modiCount);
			}
		}
		if (!found)
		{
			printf("\nNo staff found with this ID (Please check the available ID in the display menu)\n");
		}
		printf("\nAny more record to modify (Y=yes) > ");
		rewind(stdin);
		scanf("%c", &cont);
	} while (toupper(cont) == 'Y');
}
void historyArchive(char ans)
{
	FILE* history;
	history = fopen("history.bin", "ab");
	Date date;
	if (history == NULL) {
		printf("Failed to open history file\n");
		exit(-1);
	}
	SYSTEMTIME st;
	switch (ans)
	{
	case 'A':
		GetLocalTime(&st);
		date.day = st.wDay;
		date.month = st.wMonth;
		date.year = st.wYear;
		date.hour = st.wHour;
		date.minute = st.wMinute;
		date.second = st.wSecond;
		strcpy(date.msg, "Added Staff Info");
		fwrite(&date, sizeof(Date), 1, history);
		break;
	case 'M':
		GetLocalTime(&st);
		date.day = st.wDay;
		date.month = st.wMonth;
		date.year = st.wYear;
		date.hour = st.wHour;
		date.minute = st.wMinute;
		date.second = st.wSecond;
		strcpy(date.msg, "Modified Staff Info");
		fwrite(&date, sizeof(Date), 1, history);
		break;
	case 'D':
		GetLocalTime(&st);
		date.day = st.wDay;
		date.month = st.wMonth;
		date.year = st.wYear;
		date.hour = st.wHour;
		date.minute = st.wMinute;
		date.second = st.wSecond;
		strcpy(date.msg, "Deleted Staff Info");
		fwrite(&date, sizeof(Date), 1, history);
		break;
	}

	fclose(history);
}
void displayHistory()
{
	FILE* history;
	history = fopen("history.bin", "rb");
	if (history == NULL)
	{
		printf("error!! file not found");
		exit(-1);
	}
	Date date;

	printf("\n\tHistory Archive:\n\t=================================\n\n\n");

	while (fread(&date, sizeof(Date), 1, history) == 1) {
		printf("\t%02d/%02d/%04d %02d:%02d:%02d ---- %s\n\n", date.day, date.month, date.year, date.hour, date.minute, date.second, date.msg);
	}

	fclose(history);
}

int login()
{
	int ID, error;
	char passw[26];

	printf("\n\t\tStaff ID: ");
	rewind(stdin);
	scanf(" %d", &ID);
	if (ID == MAINID)
	{
		printf("\n\t\tPassword: ");
		rewind(stdin);
		scanf("%s", passw);
		if (strcmp(passw, "abc123") == 0)
		{
			printf("\n\n\t\t+----------------------------------------+\n");
			printf("\t\t|              LOGIN SUCCESS             |\n");
			printf("\t\t+----------------------------------------+\n");
			return 1;
		}
		else
		{
			printf("\t\tWRONG PASSWORD\n\n");
			return 0;
		}
	}
	else
	{
		printf("\t\tNOT VALID ID\n\n");
		return 0;
	}

}
int staffmain()
{
	int ans = 0, error;
	printf("\t\t*----------------------------------------*\n");
	printf("\t\t|              LOGIN SCREEN              |\n");
	printf("\t\t*----------------------------------------*\n");
	printf("\t\t|                                        |\n");
	printf("\t\t|             Enter Staff ID             |\n");
	printf("\t\t|             Enter Password             |\n");
	printf("\t\t|                                        |\n");
	printf("\t\t*----------------------------------------*\n");
	do {
		error = 0;
		if (login())
		{
			do {
				ans = 0;
				printf("\n\n\t\tSTAFF MANAGEMENT MODULE");
				printf("\n\t\t-----------------------");

				printf("\n\t\tPlease Select Action:");
				printf("\n\t\t1. Display Staff");
				printf("\n\t\t2. Search Staff");
				printf("\n\t\t3. Add Staff");
				printf("\n\t\t4. Delete Staff");
				printf("\n\t\t5. Modify Staff");
				printf("\n\t\t6. History Archive");

				printf("\n\n\t\tType anything else to Close\n");
				printf("\t\t> ");

				scanf(" %d", &ans);
				rewind(stdin);

				switch (ans)
				{
				case 1:
					displayStaff();
					break;
				case 2:
					searchStaff();
					break;
				case 3:
					addStaff();
					break;
				case 4:
					deleteStaff();
					break;
				case 5:
					modifyStaff();
					break;
				case 6:
					displayHistory();
					break;
				default:
					printf("\n\treturning to main module....\n");
					return 0;
					break;
				}
			} while (ans >= 1 && ans <= 6);
		}
		else
		{
			return 0;
		}
	} while (error != 0);
}
//Aloysius's module -------------------------------------------------------------------------------------------------------------------------^


//Gregory's module ----------------------------------------------------------------------------------------------------------------------------
void stockMainsecond();
void stockDisplay();
void productSearch();
void productAdd();
void productDelete();
void productModify();
void generateReport();
void generateReportStock();
void generateReportModify();

//checks
int checkStockID();

//MAIN edit this with team

//validation
void stockMainfirst()
{
	char password[31];

	printf("\nWelcome Stock Management System!");
	printf("\nKeys: [!] = Important/Inform | [?] = Awaiting User Input | [*] System Action\n");

	printf("\n\nTo Login,");

	do
	{
		printf("\n[?] Enter Admin Password > ");
		rewind(stdin);

		scanf("%[^\n]", &password);

		if (strcmp(password, adminPass) == 0)
		{
			printf("\n[!] Logging in... [!]\n");
			stockMainsecond();
		}
		else
		{
			printf("\n[!] Incorrect Admin Key. [!]\n");
		}
	} while (strcmp(password, adminPass) != 0);
}

//validation
int checkStockID()
{
	int entryNum = 0, i = 0, biggest;
	FILE* fstock;
	Stock product[N_Products];
	fstock = fopen("stock.bin", "rb");

	if (fstock == NULL)
	{
		printf("[!] File Error.\n");
		exit(-1);
	}

	while (fread(&product[entryNum], sizeof(Stock), 1, fstock) == 1)
	{
		entryNum++;
	}

	biggest = product[0].stockID;

	for (i = 0; i < entryNum; i++)
	{
		if (product[i + 1].stockID > product[i].stockID)
		{
			biggest = product[i + 1].stockID;
		}
	}

	if (biggest < 100)
	{
		biggest = 100;
	}

	return biggest;
}

void stockMainsecond()
{
	int ans = 0;

	printf("\n************");
	printf("\n STOCK MENU ");
	printf("\n------------");

	printf("\nPlease Select Action (1-6):");
	printf("\n 1. (*) Display Stock");
	printf("\n 2. (?) Search Stock");
	printf("\n 3. (+) Add Product");
	printf("\n 4. (-) Delete Product");
	printf("\n 5. (=) Modify Product");
	printf("\n 6. ($) Generate Report");

	printf("\n\nType anything else to Close\n");
	printf("[?] Input > ");

	rewind(stdin);
	scanf("%d", &ans);

	switch (ans)
	{
	case 1:
		stockDisplay();
		break;
	case 2:
		productSearch();
		break;
	case 3:
		productAdd();
		break;
	case 4:
		productDelete();
		break;
	case 5:
		productModify();
		break;
	case 6:
		generateReport();
		break;
	default:
		printf("\n[!] Closing Programme [!]\n");
		break;
	}
}

void stockDisplay()
{
	Stock product;
	FILE* fstock;
	fstock = fopen("stock.bin", "rb");

	if (fstock == NULL)
	{
		printf("[!] Stock File Error.\n");
		exit(-1);
	}

	printf("\n\n[*] Displaying Stock...");
	printf("\nID\tProduct (per serving)\tQuantity\tUnitPrice");
	printf("\n__________________________________________________________________");
	while (fread(&product, sizeof(Stock), 1, fstock) == 1)
	{
		printf("\nS%d\t%-20s\t%-10d\t$%.2lf", product.stockID, product.stockName, product.stockQuantity, product.unitPrice);
	}
	printf("\n__________________________________________________________________");
	printf("\n\n");
	fclose(fstock);
	stockMainsecond();
}

void productSearch()
{
	int i = 0, productID, productID2, biggest, found = 0;
	FILE* fstock;
	Stock product;
	fstock = fopen("stock.bin", "rb");

	if (fstock == NULL)
	{
		printf("[!] Stock File Error.\n");
		exit(-1);
	}

	biggest = checkStockID();

	printf("\n\n=====================");
	printf("\n Searching a Product ");
	printf("\n=====================");
	if (biggest != 100)
	{
		printf("\nID Range: S101 - S%d", biggest);
	}
	printf("\n- [!] To Cancel, type '-1'");
	printf("\n\n[?] Enter Product ID Minimum: S");
	rewind(stdin);
	scanf("%d", &productID);

	//cancel
	if (productID == -1)
	{
		printf("\n\n[!] Search Cancelled. [!]");
		printf("\n[*] Returning to Stock Menu...\n\n");
	}

	printf("\n\n[?] Enter Product ID Maximum: S");
	rewind(stdin);
	scanf("%d", &productID2);

	//cancel
	if (productID2 == -1)
	{
		printf("\n\n[!] Search Cancelled. [!]");
		printf("\n[*] Returning to Stock Menu...\n\n");
	}

	printf("\n\n[*] Displaying Stock with Product ID between S%d - S%d", productID, productID2);
	printf("\nID\tProduct (per serving)\tQuantity\tUnitPrice");
	printf("\n__________________________________________________________________");
	while (fread(&product, sizeof(Stock), 1, fstock) == 1) {
		if (product.stockID >= productID && product.stockID <= productID2)
		{
			found = 1;
			printf("\nS%d\t%-20s\t%-10d\t$%.2lf", product.stockID, product.stockName, product.stockQuantity, product.unitPrice);
		}
	}
	printf("\n__________________________________________________________________");

	if (found = 0)
	{
		printf("\n\n[!] Error! Product not found. [!]");
		printf("\n[*] Going to Stock Menu...\n\n");
	}

	printf("\n\n");

	fclose(fstock);
	stockMainsecond();
}

void productAdd()
{
	SYSTEMTIME t;
	GetLocalTime(&t);

	int biggest;
	char choice = ' ';
	Stock product;
	History history;

	FILE* fstock;
	FILE* fhistory;
	fstock = fopen("stock.bin", "ab");
	fhistory = fopen("stockreport.bin", "ab");

	if (fstock == NULL)
	{
		printf("[!] Stock File Error.\n");
		exit(-1);
	}

	if (fhistory == NULL)
	{
		printf("[!] Report File Error.\n");
		exit(-1);
	}

	//Code owned by gregory chia ming feng

	printf("\n\n======================");
	printf("\n Adding a NEW Product ");
	printf("\n======================");

	biggest = checkStockID();

	biggest++;
	printf("\n[!] Adding New Product with ID: S%d", biggest);
	product.stockID = biggest;

	//printf("\nEnter Product ID [eg. 100>]: ");
	//scanf("%d", &product.stockID);
	//rewind(stdin);

	printf("\n- [!] To Cancel, type '-1' for any");

	printf("\n\n[?] Enter Product Name (max 20): S");
	rewind(stdin);
	scanf("%[^\n]", &product.stockName);

	//cancel
	if (strcmp(product.stockName, "-1") == 0)
	{
		printf("\n\n[!] Add Cancelled. [!]");
		printf("\n[*] Returning to Stock Menu...\n\n");

		stockMainsecond();
	}

	printf("\n[?] Enter Current Quantity (per serving): ");
	rewind(stdin);
	scanf("%d", &product.stockQuantity);

	//cancel
	if (product.stockQuantity == -1)
	{
		printf("\n\n[!] Add Cancelled. [!]");
		printf("\n[*] Returning to Stock Menu...\n\n");

		stockMainsecond();
	}

	//validate
	while (product.stockQuantity < -1)
	{
		printf("\n[!] Error! Quantity cannot be less than 0.\n");
		printf("\n[?] Enter Current Quantity (per serving): ");
		rewind(stdin);
		scanf("%d", &product.stockQuantity);
	}

	printf("\n[?] Enter Price per Unit ($0.00): $");
	rewind(stdin);
	scanf("%lf", &product.unitPrice);

	//cancel
	if (product.unitPrice == -1)
	{
		printf("\n\n[!] Add Cancelled. [!]");
		printf("\n[*] Returning to Stock Menu...\n\n");

		stockMainsecond();
	}

	//validate
	while (product.unitPrice < -1)
	{
		printf("\n[!] Error! Unit Price cannot be 0 or less than 0.\n");
		printf("\n[?] Enter Current Price per Unit ($0.00): $");
		rewind(stdin);
		scanf("%lf", &product.unitPrice);
	}

	printf("\n\n[!] Reconfirm Add Product with ID: %d", product.stockID);
	printf("\n-----------------------------------------");
	printf("\nID		: S%d", product.stockID);
	printf("\nName		: %s", product.stockName);
	printf("\nQuantity	: %d", product.stockQuantity);
	printf("\nUnit Price	: $%.2lf", product.unitPrice);
	printf("\n-----------------------------------------");

	printf("\n\n[?] Confirm to Add (Y/N)? > ");
	rewind(stdin);
	scanf("%c", &choice);

	if (toupper(choice) == 'Y')
	{
		//report
		strcpy(history.action, "Added");
		history.stockID = product.stockID;
		strcpy(history.stockName, product.stockName);
		history.unitChange = product.stockQuantity;
		history.priceChange = product.unitPrice;
		history.minute = t.wMinute;
		history.hour = t.wHour;
		history.day = t.wDay;
		history.month = t.wMonth;
		history.year = t.wYear;

		fwrite(&history, sizeof(History), 1, fhistory);

		//add
		fwrite(&product, sizeof(Stock), 1, fstock);
		printf("\n\n[!] Successfully added. [!]");
	}
	else
	{
		printf("\n\n[!] Product not added. [!]");
	}

	fclose(fstock);
	fclose(fhistory);
	printf("\n[*] Returning to Stock Menu...\n\n");

	stockMainsecond();
}

void productDelete()
{
	SYSTEMTIME t;
	GetLocalTime(&t);

	int i = 0, entryNum = 0, productID = 1;
	char choice = ' ';
	Stock product[N_Products];
	History history;
	FILE* fstock;
	FILE* fhistory;
	fstock = fopen("stock.bin", "rb");

	if (fstock == NULL)
	{
		printf("[!] Stock File Error.\n");
		exit(-1);
	}

	//save all of products as array
	while (fread(&product[entryNum], sizeof(Stock), 1, fstock) == 1)
	{
		entryNum++;
	}

	fclose(fstock);
	//closed

	//what to delete
	printf("\n\n====================");
	printf("\n DELETING a Product ");
	printf("\n====================");
	printf("\n- To Cancel, type '-1'");
	printf("\n\n[?] Enter Product ID: S");
	rewind(stdin);
	scanf("%d", &productID);

	for (i = 0; i < entryNum; i++)
	{
		//if product id entered is product's stock id then,
		if (product[i].stockID == productID)
		{
			printf("\n[*] Displaying Products With ID: %d ", productID);
			printf("\n--------------------------------------");
			printf("\nID		: S%d", product[i].stockID);
			printf("\nName		: %s", product[i].stockName);
			printf("\nQuantity	: %d", product[i].stockQuantity);
			printf("\nUnit Price	: $%.2lf", product[i].unitPrice);
			printf("\n--------------------------------------");
			printf("\n\n[?] Confirm Delete? (Y/N) > ");
			rewind(stdin);
			scanf("%c", &choice);
		}

		//if yes, delete. if no, cancel
		if (toupper(choice) == 'Y')
		{
			//open report file
			fhistory = fopen("stockreport.bin", "ab");

			if (fhistory == NULL)
			{
				printf("[!] Report File Error.\n");
				exit(-1);
			}

			//report
			strcpy(history.action, "Deleted");
			history.stockID = product[i].stockID;
			strcpy(history.stockName, product[i].stockName);
			history.unitChange = product[i].stockQuantity;
			history.priceChange = product[i].unitPrice;
			history.minute = t.wMinute;
			history.hour = t.wHour;
			history.day = t.wDay;
			history.month = t.wMonth;
			history.year = t.wYear;

			fwrite(&history, sizeof(History), 1, fhistory);

			fclose(fhistory);

			//delete
			//delete deleted product from saved array
			printf("\n\n[!] Deleted! [!]");
			printf("\n[*] Returning to Stock Menu...\n\n");
			do
			{
				product[i] = product[i + 1];
			} while (++i < entryNum - 1);
			//shift everything forward

			//edit the file itself (instead of array)
			fstock = fopen("stock.bin", "wb");

			if (fstock == NULL)
			{
				printf("[!] Stock File Error.\n");
				exit(-1);
			}

			//deleted
			fwrite(product, sizeof(Stock), entryNum - 1, fstock);
		}
	}
	if (productID == -1)
	{
		printf("\n\n[!] Delete Cancelled. [!]");
		printf("\n[*] Returning to Stock Menu...\n\n");
	}

	fclose(fstock);
	stockMainsecond();
}

void productModify()
{
	//time
	SYSTEMTIME t;
	GetLocalTime(&t);

	char choice = ' ';
	int i = 0, entryNum = 0, found = 0, updQuantity, productID = 0, biggest, updID;
	double updPrice;
	Stock product[N_Products];
	History history;
	FILE* fstock;
	FILE* fhistory;
	fstock = fopen("stock.bin", "rb");
	fhistory = fopen("modifyreport.bin", "ab");

	if (fstock == NULL)
	{
		printf("[!] Stock File Error.\n");
		exit(-1);
	}

	if (fhistory == NULL)
	{
		printf("[!] Report File Error.\n");
		exit(-1);
	}

	//save all of products as array
	while (fread(&product[entryNum], sizeof(Stock), 1, fstock) == 1)
	{
		entryNum++;
	}

	fclose(fstock);
	//closed

	biggest = checkStockID();

	printf("\n\n=====================");
	printf("\n Modifying a Product ");
	printf("\n=====================");
	printf("\nID Range: S101 - S%d", biggest);
	printf("\n- To Cancel, type '-1'");
	printf("\n\n[?] Enter Product ID: S");
	rewind(stdin);
	scanf("%d", &productID);

	//cancel
	if (productID == -1)
	{
		found = 1;
		printf("\n\n[!] Modify Cancelled. [!]");
		printf("\n[*] Returning to Stock Menu...\n\n");

		stockMainsecond();
	}

	for (i = 0; i < entryNum; i++)
	{
		if (product[i].stockID == productID)
		{
			found = 1;
			printf("\n[*] Displaying Products With ID: S%d", productID);
			printf("\n-------------------------------------");
			printf("\nID		: S%d", product[i].stockID);
			printf("\nName		: %s", product[i].stockName);
			printf("\nQuantity	: %d", product[i].stockQuantity);
			printf("\nUnit Price	: $%.2lf", product[i].unitPrice);
			printf("\n-------------------------------------");

			printf("\n\n- [!] To Cancel, enter '-1' for any.");
			printf("\n- [!] To Not Change, enter '-2'");

			//
			// start of update section

			printf("\n\n[?] Enter New ID: S");
			rewind(stdin);
			scanf("%d", &updID);

			//cancel
			if (updID == -1)
			{
				printf("\n\n[!] Modify Cancelled. [!]");
				printf("\n[*] Returning to Stock Menu...\n\n");
				fclose(fstock);
				stockMainsecond();
			}
			//unchange
			if (updID == -2)
			{
				printf("\n[!] ID not changed.\n");
				updID = product[i].stockID;
			}
			//validate
			while (updID < -2 || updID > 999 || updID == 0)
			{
				printf("\n[!] Error! Product ID out of range.\n");
				printf("\n[?] Enter New ID: S");
				rewind(stdin);
				scanf("%d", &updID);
			}

			printf("\n[?] Enter New Quantity: ");
			rewind(stdin);
			scanf("%d", &updQuantity);

			//cancel
			if (updQuantity == -1)
			{
				printf("\n\n[!] Modify Cancelled. [!]");
				printf("\n[*] Returning to Stock Menu...\n\n");
				fclose(fstock);
				stockMainsecond();
			}
			//unchange
			if (updQuantity == -2)
			{
				printf("\n[!] Quantity not changed.\n");
				updQuantity = product[i].stockQuantity;
			}
			//validate
			while (updQuantity < -2)
			{
				printf("\n[!] Error! Quantity can't be 0 or less.\n");
				printf("\n[?] Enter New Quantity: ");
				rewind(stdin);
				scanf("%d", &updQuantity);
			}


			printf("\n[?] Enter New Unit Price ($0.00): $");
			rewind(stdin);
			scanf("%lf", &updPrice);

			//cancel
			if (updPrice == -1)
			{
				printf("\n\n[!] Modify Cancelled. [!]");
				printf("\n[*] Returning to Stock Menu...\n\n");
				fclose(fstock);
				stockMainsecond();
			}
			//unchanged
			if (updPrice == -2)
			{
				printf("\n[!] Price not changed.\n");
				updPrice = product[i].unitPrice;
			}
			//validate
			while (updPrice < -2)
			{
				printf("\n[!] Error! Unit Price can't be less than 0.\n");
				printf("\n[?] Enter New Unit Price ($0.00): ");
				rewind(stdin);
				scanf("%lf", &updPrice);
			}


			printf("\n\n[!] Reconfirm Update Product with ID: S%d", productID);
			printf("\n--------------------------------------------");
			printf("\nID		: S%d", updID);
			printf("\nName		: %s", product[i].stockName);
			printf("\nQuantity	: %d", updQuantity);
			printf("\nUnit Price	: $%.2lf", updPrice);
			printf("\n--------------------------------------------");

			printf("\n\n[?] Confirm to Modify (Y/N)? > ");
			rewind(stdin);
			scanf("%c", &choice);

			if (toupper(choice) == 'Y')
			{
				//report
				history.stockID = product[i].stockID;
				history.IDChange = updID;
				strcpy(history.stockName, product[i].stockName);
				history.unitChange = updQuantity - product[i].stockQuantity;
				history.priceChange = updPrice - product[i].unitPrice;
				history.minute = t.wMinute;
				history.hour = t.wHour;
				history.day = t.wDay;
				history.month = t.wMonth;
				history.year = t.wYear;

				//update
				product[i].stockQuantity = updQuantity;
				product[i].unitPrice = updPrice;
				product[i].stockID = updID;

				//open
				fstock = fopen("stock.bin", "wb");

				for (i = 0; i < entryNum; i++)
				{
					fwrite(&product[i], sizeof(Stock), 1, fstock);
				}

				fwrite(&history, sizeof(History), 1, fhistory);

				printf("\n\n[!] Product Updated! [!]");
				printf("\n[*] Returning to Stock Menu...\n\n");

				fclose(fstock);
				fclose(fhistory);
				//close
				stockMainsecond();
			}
			else
			{
				printf("\n\n[!] Modify Cancelled. [!]");
				printf("\n[*] Returning to Stock Menu...\n\n");
				fclose(fstock);
				fclose(fhistory);
				stockMainsecond();
			}
		}
	}

	if (!found)
	{
		printf("\n\n[!] Error! Product to Modify not found.");
		printf("\n[*] Going to Stock Menu...\n\n");
		fclose(fstock);
		stockMainsecond();
	}
}

//Code owned by gregory chia ming feng

void generateReport()
{
	int ans = 0;

	printf("\n\n****************************");
	printf("\n GENERATE STOCK REPORT MENU ");
	printf("\n----------------------------");

	printf("\nPlease Select Action:");
	printf("\n 1. Add/Delete Report");
	printf("\n 2. Modify Report");

	printf("\n\nType anything else to Close\n");
	printf("[?] Input > ");

	rewind(stdin);
	scanf("%d", &ans);

	switch (ans)
	{
	case 1:
		generateReportStock();
		break;
	case 2:
		generateReportModify();
		break;
	default:
		printf("\n\n[*] Returning to Stock Menu...\n\n");
		stockMainsecond();
		break;
	}
}

void generateReportStock()
{
	History history;
	FILE* fhistory;
	fhistory = fopen("stockreport.bin", "rb");

	if (fhistory == NULL)
	{
		printf("[!] Report File Error.\n");
		exit(-1);
	}

	printf("\n\n[*] Generating Add/Delete Stock Report...");
	printf("\nAction\t\tID\tProduct (per serving)\tQuantity\tUnit Price\tTime [HH:MM][DD/MM/YYYY]");
	printf("\n________________________________________________________________________________________________________________");
	while (fread(&history, sizeof(History), 1, fhistory) == 1)
	{
		printf("\n%s\t\tS%d\t%-20s\t%-8d\t$%-8.2f", history.action, history.stockID, history.stockName, history.unitChange, history.priceChange);
		printf("\t[%02d:%02d][%02d/%02d/%02d]\n", history.hour, history.minute, history.day, history.month, history.year);
	}
	printf("\n________________________________________________________________________________________________________________");
	printf("\n\n");

	fclose(fhistory);
	stockMainsecond();
}

void generateReportModify()
{
	History history;
	FILE* fhistory;
	fhistory = fopen("modifyreport.bin", "rb");

	if (fhistory == NULL)
	{
		printf("[!] Report File Error.\n");
		exit(-1);
	}

	printf("\n\n[*] Generating Modify Stock Report...");
	printf("\nID -> New ID\tProduct (per serving)\tQuantity Changed\tUnit Price Changed\tTime [HH:MM][DD/MM/YYYY]");
	printf("\n________________________________________________________________________________________________________________");
	while (fread(&history, sizeof(History), 1, fhistory) == 1)
	{
		printf("\nS%d -> S%d\t%-20s\t%-8d\t\t$%-8.2f", history.stockID, history.IDChange, history.stockName, history.unitChange, history.priceChange);
		printf("\t\t[%02d:%02d][%02d/%02d/%02d]\n", history.hour, history.minute, history.day, history.month, history.year);
	}
	printf("\n________________________________________________________________________________________________________________");
	printf("\n\n");

	fclose(fhistory);
	stockMainsecond();
}
//Gregory's module -----------------------------------------------------------------------------------------------------------------^

//KhooLiXuan's module ---------------------------------------------------------------------------------------------------------------

int chkcntNumbr(int* cntNumbr) {

	if (*cntNumbr < 199999999 && *cntNumbr > 100000000)
		return 1; // v
	else
		return 0; // inv
}
int nameChk(char* name) {
	int j;

	for (j = 0; j < strlen(name); j++) {
		if (!isalpha(name[j]) && name[j] != ' ') {
			return 0;
		}
	}
	return 1;
}
int chkGender(char* gender) {
	if (toupper(gender) == 'M' || toupper(gender) == 'F') {
		return 1; // valid input
	}
	else {
		return 0; // invalid input
	}

}
int chkTier(int* tier) {
	if (tier == 1 || tier == 2 || tier == 3)
		return 1; // v
	else
		return 0; // inv

}
int chkStatus(char* status) {
	if (toupper(status) == 'A' || toupper(status) == 'E')
		return 1;
	else
		return 0;

}
int chkPtAcc(int* points) {
	if (points < 0 && !isdigit(points))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int chkMbrId(int* id) {
	if (id < 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
//additional functions
void rAddedReport() {
	int j = 0, aCount, count = 0;
	FILE* readd;
	readd = fopen("recentlyAdded.txt", "r");
	MEM member[40];
	if (readd == NULL) {
		printf("Error: File not found!\n");
		exit(-1);
	}
	while (fscanf(readd, "%d|%d|%[^|]|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
		&member[j].memberId, &member[j].tier, member[j].pDetails.name, &member[j].pDetails.gender, &member[j].pDetails.cntNumbr,
		&member[j].jDetails.date, &member[j].jDetails.month, &member[j].jDetails.year, &member[j].expDetails.date,
		&member[j].expDetails.month, &member[j].expDetails.year, &member[j].status, &member[j].discount, &member[j].ptAcc) != EOF) {

		j++;
	}
	aCount = j;
	fclose(readd);
	printf("\n<================================================================ Recently Added ============================================================================>\n");
	printf("Member ID  Tier  Name                          Gender  Contact Number  Date joined    Expiry Date    Membership Status  Discount%%  Points Accumulated\n");
	printf("<============================================================================================================================================================>\n");

	for (j = 0; j < aCount; j++)
	{
		printf("M%04d       %-5d %-30s %-7c(+60)%-15d %02d/%02d/%-4d    %02d/%02d/%-4d     \t%-1c              %-2d         %-7d\n",
			member[j].memberId, member[j].tier, member[j].pDetails.name, member[j].pDetails.gender, member[j].pDetails.cntNumbr, member[j].jDetails.date,
			member[j].jDetails.month, member[j].jDetails.year, member[j].expDetails.date, member[j].expDetails.month, member[j].expDetails.year, member[j].status, member[j].discount, member[j].ptAcc);
		count++;
	}

	if (count > 0)
	{
		printf("\n< There are %d New Members  >\n", count);
	}
	else
	{
		printf("\n< There are no Recently Deleted Members >\n");
	}

}
void rDeletedReport() {
	int k = 0, dCount, count = 0;
	MEM member[40];
	FILE* redel;
	redel = fopen("recentlyDeleted.txt", "r");
	if (redel == NULL) {
		printf("Error: File not found!\n");
		exit(-1);
	}
	while (fscanf(redel, "%d|%d|%[^|]|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
		&member[k].memberId, &member[k].tier, member[k].pDetails.name, &member[k].pDetails.gender, &member[k].pDetails.cntNumbr,
		&member[k].jDetails.date, &member[k].jDetails.month, &member[k].jDetails.year, &member[k].expDetails.date,
		&member[k].expDetails.month, &member[k].expDetails.year, &member[k].status, &member[k].discount, &member[k].ptAcc) != EOF) {
		k++;
	}
	dCount = k;
	fclose(redel);
	printf("\n<================================================================ Recently Deleted ==========================================================================>\n");
	printf("Member ID  Tier  Name                          Gender  Contact Number  Date joined    Expiry Date    Membership Status  Discount%%  Points Accumulated\n");
	printf("<============================================================================================================================================================>\n");

	for (k = 0; k < dCount; k++)
	{
		printf("M%04d       %-5d %-30s %-7c(+60)%-15d %02d/%02d/%-4d    %02d/%02d/%-4d     \t%-1c              %-2d         %-7d\n",
			member[k].memberId, member[k].tier, member[k].pDetails.name, member[k].pDetails.gender, member[k].pDetails.cntNumbr, member[k].jDetails.date,
			member[k].jDetails.month, member[k].jDetails.year, member[k].expDetails.date, member[k].expDetails.month, member[k].expDetails.year, member[k].status, member[k].discount, member[k].ptAcc);
		count++;
	}

	if (count > 0)
	{
		printf("\n< There are %d Recently Deleted Members  >\n", count);
	}
	else
	{
		printf("\n< There are no Recently Deleted Members >\n");
	}

}
void searchByName()
{
	char name[31] = { '\0' };
	int i = 0, pCount, search = 0, choice = 0, error = 0;
	char yesno;
	MEM member[50];
	FILE* fptr;

	fptr = fopen("member.txt", "r");
	if (fptr == NULL) {
		printf("Error: File not found!\n");
		exit(-1);
	}
	//retrieve all data into array
	while (fscanf(fptr, "%d|%d|%[^|]|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
		&member[i].memberId, &member[i].tier, member[i].pDetails.name, &member[i].pDetails.gender, &member[i].pDetails.cntNumbr,
		&member[i].jDetails.date, &member[i].jDetails.month, &member[i].jDetails.year, &member[i].expDetails.date,
		&member[i].expDetails.month, &member[i].expDetails.year, &member[i].status, &member[i].discount, &member[i].ptAcc) != EOF) {

		i++;
	}
	pCount = i;
	fclose(fptr);

	do
	{
		error = 0;
		while (error != 1) {

			printf("< Enter Name Of Member To Be Found > \n> ");
			rewind(stdin);
			scanf("%[^\n]", name);
			if (nameChk(name))
			{
				error = 1; // set error to 0 to exit the loop 
				break;
			}
			else
			{
				printf("\n< Error! Enter Valid Input Within 30 characters! >\n");
			}
			printf("\n\n");
		}
		for (i = 0; i < pCount; i++)
		{
			if (strcmp(name, member[i].pDetails.name) == 0) {
				search = 1;
				printf("\n Member Found!\n");
				printf("Member with Name > %s", name);
				printf("\n<======================================================================================================>\n");
				printf("\n");
				printf(" ID                  \t\t\tM%04d\n", member[i].memberId);
				printf(" Tier                \t\t\t%-d\n", member[i].tier);
				printf(" Name                \t\t\t%-s\n", member[i].pDetails.name);
				printf(" Gender              \t\t\t%c\n", member[i].pDetails.gender);
				printf(" Contact Number      \t\t\t(+60)%-d\n", member[i].pDetails.cntNumbr);
				printf(" Join Date           \t\t\t%d/%d/%d\n", member[i].jDetails.date, member[i].jDetails.month, member[i].jDetails.year);
				printf(" Expiry Date         \t\t\t%d/%d/%d\n", member[i].expDetails.date, member[i].expDetails.month, member[i].expDetails.year);
				printf(" Account Status      \t\t\t%c\n", member[i].status);
				printf(" Discount %%         \t\t\t%d\n", member[i].discount);
				printf(" Points Accumulated  \t\t\t%d\n", member[i].ptAcc);
				printf("\n<======================================================================================================>\n");
				break;
			}

		}

		if (search != 1)
		{
			printf("\n< Error ! Member Not Found ! >\n");
		}

		printf("< Any other members ? >\n");
		printf("< Press Y if Yes >\n>");
		rewind(stdin);
		scanf(" %c", &yesno);
		rewind(stdin);
		printf("\n\n");

	} while (toupper(yesno) == 'Y');

}
void searchById()
{

	int i = 0, pCount, search = 0, choice = 0, id, error = 0;
	char yesno;

	MEM member[50];
	FILE* fptr;

	fptr = fopen("member.txt", "r");
	if (fptr == NULL) {
		printf("Error: File not found!\n");
		exit(-1);
	}

	//retrieve all data into array
	while (fscanf(fptr, "%d|%d|%[^|]|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
		&member[i].memberId, &member[i].tier, member[i].pDetails.name, &member[i].pDetails.gender, &member[i].pDetails.cntNumbr,
		&member[i].jDetails.date, &member[i].jDetails.month, &member[i].jDetails.year, &member[i].expDetails.date,
		&member[i].expDetails.month, &member[i].expDetails.year, &member[i].status, &member[i].discount, &member[i].ptAcc) != EOF) {

		i++;
	}
	pCount = i;

	fclose(fptr);
	do
	{
		error = 0;
		while (error != 1)
		{
			id = 0;
			rewind(stdin);
			printf("< Enter ID Of Member To Be Found > \n> ");
			rewind(stdin);
			scanf(" %d", &id);
			if (chkMbrId(id))
			{
				error = 1;
			}
			else
			{
				printf("\n< Error! Enter Valid Input  >\n");
			}
			printf("\n\n");

		}

		for (i = 0; i < pCount; i++)
		{
			if (member[i].memberId == id) {
				search = 1;
				printf("\n Member Found!\n");
				printf("Member with ID > M%04d", id);
				printf("\n<======================================================================================================>\n");
				printf(" Member Found!\n");
				printf("\n");
				printf(" ID                  \t\t\tM%04d\n", member[i].memberId);
				printf(" Tier                \t\t\t%-d\n", member[i].tier);
				printf(" Name                \t\t\t%-s\n", member[i].pDetails.name);
				printf(" Gender              \t\t\t%c\n", member[i].pDetails.gender);
				printf(" Contact Number      \t\t\t(+60)%-d\n", member[i].pDetails.cntNumbr);
				printf(" Join Date           \t\t\t%d/%d/%d\n", member[i].jDetails.date, member[i].jDetails.month, member[i].jDetails.year);
				printf(" Expiry Date         \t\t\t%d/%d/%d\n", member[i].expDetails.date, member[i].expDetails.month, member[i].expDetails.year);
				printf(" Account Status      \t\t\t%c\n", member[i].status);
				printf(" Discount %%         \t\t\t%d\n", member[i].discount);
				printf(" Points Accumulated  \t\t\t%d\n", member[i].ptAcc);
				printf("\n<======================================================================================================>\n");

			}

		}

		if (search != 1)
		{
			printf("\n< Error ! Member Not Found ! >\n");
		}

		rewind(stdin);
		printf("< Any other members ? >\n");
		printf("< Press Y if Yes >\n>");
		rewind(stdin);
		scanf(" %c", &yesno);
		rewind(stdin);
		printf("\n");

	} while (toupper(yesno) == 'Y');

	fclose(fptr);
}

//add serch modify del report display
void addNewMem();
void searchMemBy();
void modifyMemDetails();
int deleteMem();
void genReport();
void displayAll();

void membermain() {

	int choice = 0;
	//to loop the switch case
	do{
		choice = 0;
		printf("\n=================================\n");
		printf("\n===== Member Module Function ====\n");
		printf("\n===< Select A Function >===\n< 1 > Add Member \n< 2 > Search Member \n< 3 > Modify Member Details \n< 4 > Delete Member \n< 5 > Generate Report \n< 6 > Display All Members \n< 7 > Exit Program\n=================================\n>");
		rewind(stdin);
		scanf("%d", &choice);
		rewind(stdin);

		switch (choice)
		{
		case 1:
			addNewMem();
			break;
		case 2:
			searchMemBy();
			break;
		case 3:
			modifyMemDetails();
			break;
		case 4:
			deleteMem();
			break;
		case 5:
			genReport();
			break;
		case 6:
			displayAll();
			break;
		case 7:
			printf("Thanks For Using This Program\n\n");
			break;
		default:
			printf("\n< Error, Select Valid input ! >\n\n");
		}

	} while (choice != 7);
}

void addNewMem() {

	char yesNo, cont, gender = ' ', name[31];
	int  error = 1, cTier, id = 1, i = 0, cntNumbr = 0, addCount = 0, points = 0;

	SYSTEMTIME t;//structure for date, time 
	GetLocalTime(&t);//get date /time from OS

	//to add new member and to scan existing member id to autogenerate new one
	MEM member, reading;
	//for reading and appending member.txt file, for adding into recentlyAdded.txt file
	FILE* fptr, * readd;

	do
	{
		fptr = fopen("member.txt", "r");
		if (fptr == NULL)
		{
			printf("Error !, File not found !");
			exit(-1);
		}

		printf("\nAdd New Member\n");
		printf("===============\n");

		//autogenerate new id
		while (fscanf(fptr, "%d|%d|%[^|]|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
			&reading.memberId, &reading.tier, reading.pDetails.name, &reading.pDetails.gender, &reading.pDetails.cntNumbr,
			&reading.jDetails.date, &reading.jDetails.month, &reading.jDetails.year, &reading.expDetails.date,
			&reading.expDetails.month, &reading.expDetails.year, &reading.status, &reading.discount, &reading.ptAcc) != EOF) {

			if (id <= reading.memberId)
			{
				id = reading.memberId + 1;
				member.memberId = id;
			}

		}

		fclose(fptr);

		fptr = fopen("member.txt", "a");
		readd = fopen("recentlyAdded.txt", "a");
		if (readd == NULL)
		{
			printf("Error !, File not found !");
			exit(-1);
		}

		if (fptr == NULL)
		{
			printf("Error !, File not found !");
			exit(-1);
		}

		while (error != 0) {
			printf("\n< Enter Tier ( Tiers = 1-3 ) >\n>");
			rewind(stdin);
			scanf("%d", &cTier);

			if (chkTier(cTier)) {
				member.tier = cTier;
				error = 0; // set error to 0 to exit the loop 
				break;
			}
			else
			{
				printf("\n< Error! Enter Valid Input!  ( Tiers = 1-3 ) >\n");
			}
		}

		while (error != 1) {
			error = 0;
			printf("\n< Enter Member Name ( Max 30 characters ) >\n>");
			rewind(stdin);
			scanf(" %[^\n]", name);
			if (nameChk(name))
			{
				strcpy(member.pDetails.name, name);
				error = 1; // set error to 0 to exit the loop 
				break;
			}
			else
			{
				printf("\n< Error! Enter Valid Input Within 30 characters! >\n");
			}

		}

		while (error != 0) {
			printf("\n< Enter Member Gender  (M = Male, F = Female) >\n>");
			rewind(stdin);
			scanf("%c", &gender);
			rewind(stdin);
			if (chkGender(gender))
			{
				member.pDetails.gender = toupper(gender);
				error = 0; // set error to 0 to exit the loop
				break;
			}
			else
			{
				printf("\n< Error! Enter Valid Input! ( M = Male, F = Female ) >\n");
			}
		}


		while (error != 1) {
			printf("\n< Enter Contact +60 ( no space or - required ) >\n>");
			rewind(stdin);
			scanf("%d", &cntNumbr);
			rewind(stdin);
			if (chkcntNumbr(&cntNumbr))
			{
				member.pDetails.cntNumbr = cntNumbr;
				error = 1; // set error to 0 to exit the loop
				break;
			}
			else
			{
				printf("\n< Error! Enter Valid Input! >\n");
			}
		}

		member.jDetails.date = t.wDay;
		member.jDetails.month = t.wMonth;
		member.jDetails.year = t.wYear;
		member.expDetails.date = member.jDetails.date;
		member.expDetails.month = member.jDetails.month;

		if (member.tier == 1)
		{
			member.expDetails.year = member.jDetails.year + 3;
			member.discount = 10;
		}
		else if (member.tier == 2)
		{
			member.expDetails.year = member.jDetails.year + 2;
			member.discount = 7;
		}
		else if (member.tier == 3)
		{
			member.expDetails.year = member.jDetails.year + 1;
			member.discount = 5;
		}

		if (member.expDetails.year < t.wYear)
		{
			member.status = 'E';
		}
		else
		{
			member.status = 'A';
		}

		while (error != 0)
		{
			printf("\n< Enter Points Accumilated >\n>");
			rewind(stdin);
			scanf("%d", &points);
			if (chkPtAcc(points)) {
				member.ptAcc = points;
				error = 0;
				break;
			}
			else
			{
				printf("\n< Error! Enter Valid Input! >\n");
			}
		}

		printf("\n< Confirm ? (Y = yes, Other = No ) >\n>");
		rewind(stdin);
		scanf("%c", &yesNo);

		if (toupper(yesNo) == 'Y')
		{
			//id tier name gender cntnum dd/mm/yyyy.j dd/mm/yyyy.exp st d% pt
			fprintf(fptr, "%d|%d|%s|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
				member.memberId, member.tier, member.pDetails.name, member.pDetails.gender, member.pDetails.cntNumbr, member.jDetails.date,
				member.jDetails.month, member.jDetails.year, member.expDetails.date, member.expDetails.month, member.expDetails.year, member.status, member.discount, member.ptAcc);
			fprintf(readd, "%d|%d|%s|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
				member.memberId, member.tier, member.pDetails.name, member.pDetails.gender, member.pDetails.cntNumbr, member.jDetails.date,
				member.jDetails.month, member.jDetails.year, member.expDetails.date, member.expDetails.month, member.expDetails.year, member.status, member.discount, member.ptAcc);

			addCount++;

		}
		printf("\n< Any More Members ? >\n< (Press Y if Yes) >\n>");
		rewind(stdin);
		scanf("%c", &cont);
		rewind(stdin);
		printf("\n\n");

	} while (toupper(cont) == 'Y');


	printf("\n< %d Members Added >\n", addCount);
	fclose(fptr);
}
void searchMemBy() {

	int filter = 0, searchLoop = 1;
	rewind(stdin);

	while (searchLoop != 0) {
		printf("\n\n<==== Select Filter to search by ====>\n< 1 > Name \n< 2 > Membership Id \n< 3 > Return To Member Menu\n< 4 > Exit Program\n<====================================>\n\n> ");
		rewind(stdin);
		scanf("%d", &filter);
		rewind(stdin);

		switch (filter)
		{
		case 1:
			searchByName();
			break;
		case 2:
			searchById();
			break;
		case 3:
			searchLoop = 0;
			break;
		case 4:
			printf("Thanks For Using This Program");
			exit(-1);
			break;
		default:
			printf("Error ! Enter Valid Value");
			break;
		}
	}

}
void modifyMemDetails() {

	int i = 0, pCount = 0, search = 0, id, modiCount = 0, error = 1, cTier = 0, cntNumbr = 0, points = 0;
	char yesno, cont, gender, name[31];

	//int nId, nTier, nCntNum, nDate, nMonth, nYear, nptAcc;
	int nYear = 0;
	char nName[31] = { '\0' };

	SYSTEMTIME t;//structure for date, time 
	GetLocalTime(&t);//get date /time from OS
	MEM member[50];
	FILE* fptr;

	fptr = fopen("member.txt", "r");
	if (fptr == NULL) {
		printf("Error: File not found!\n");
		exit(-1);
	}

	//retrieve all data into array
	while (fscanf(fptr, "%d|%d|%[^|]|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
		&member[pCount].memberId, &member[pCount].tier, member[pCount].pDetails.name, &member[pCount].pDetails.gender, &member[pCount].pDetails.cntNumbr,
		&member[pCount].jDetails.date, &member[pCount].jDetails.month, &member[pCount].jDetails.year, &member[pCount].expDetails.date,
		&member[pCount].expDetails.month, &member[pCount].expDetails.year, &member[pCount].status, &member[pCount].discount, &member[pCount].ptAcc) != EOF) {

		pCount++;
	}

	fclose(fptr);

	do
	{
		printf("< Enter ID Of Member To Be Found >\n>");
		rewind(stdin);
		scanf("%d", &id);

		for (i = 0; i < pCount; i++)
		{
			if (id == member[i].memberId) {
				search = 1;

				printf("\n Member Found!\n");
				printf("Member with ID > M%04d", id);
				printf("\n<======================================================================================================>\n");
				printf(" Member Found!\n");
				printf("\n");
				printf(" ID                  \t\t\tM%04d\n", member[i].memberId);
				printf(" Tier                \t\t\t%-d\n", member[i].tier);
				printf(" Name                \t\t\t%-s\n", member[i].pDetails.name);
				printf(" Gender              \t\t\t%c\n", member[i].pDetails.gender);
				printf(" Contact Number      \t\t\t(+60)%-d\n", member[i].pDetails.cntNumbr);
				printf(" Join Date           \t\t\t%d/%d/%d\n", member[i].jDetails.date, member[i].jDetails.month, member[i].jDetails.year);
				printf(" Expiry Date         \t\t\t%d/%d/%d\n", member[i].expDetails.date, member[i].expDetails.month, member[i].expDetails.year);
				printf(" Account Status      \t\t\t%c\n", member[i].status);
				printf(" Discount %%         \t\t\t%d\n", member[i].discount);
				printf(" Points Accumulated  \t\t\t%d\n", member[i].ptAcc);
				printf("\n<======================================================================================================>\n");

				while (error != 0) {
					printf("\n< Enter Updated Tier ( Tiers = 1-3 ) >\n>");
					rewind(stdin);
					scanf("%d", &cTier);

					if (chkTier(cTier)) {
						member[i].tier = cTier;
						error = 0; // set error to 0 to exit the loop 
						break;
					}
					else
					{
						printf("\n< Error! Enter Valid Input!  ( Tiers = 1-3 ) >\n");
					}

				}

				while (error != 1) {
					printf("\n< Enter Member Name ( Max 30 characters ) >\n>");
					rewind(stdin);
					scanf(" %[^\n]", name);
					if (nameChk(name))
					{
						strcpy(member[i].pDetails.name, name);
						error = 1; // set error to 0 to exit the loop 
						break;
					}
					else
					{
						printf("\n< Error! Enter Valid Input Within 30 characters! >\n");
					}

				}

				while (error != 0) {
					printf("\n< Enter Updated Member Gender (M = Male, F = Female) >\n>");
					rewind(stdin);
					scanf("%c", &gender);
					rewind(stdin);

					if (chkGender(gender))
					{
						member[i].pDetails.gender = toupper(gender);
						error = 0; // set error to 0 to exit the loop
						break;
					}
					else
					{
						printf("\n< Error! Enter Valid Input! ( M = Male, F = Female ) >\n");
					}
				}

				while (error != 1) {
					printf("\n< Enter Updated Contact +60 ( no space or - required ) >\n>");
					rewind(stdin);
					scanf("%d", &cntNumbr);
					rewind(stdin);

					if (chkcntNumbr(&cntNumbr))
					{
						member[i].pDetails.cntNumbr = cntNumbr;
						error = 1; // set error to 0 to exit the loop
						break;
					}
					else
					{
						printf("\n< Error! Enter Valid Input! >\n");
					}
				}

				while (error != 0)
				{
					printf("\n< Enter Points Accumilated >\n>");
					rewind(stdin);
					scanf("%d", &points);
					if (chkPtAcc(points)) {
						member[i].ptAcc = points;
						error = 0;
						break;
					}
					else
					{
						printf("\n< Error! Enter Valid Input! >\n");
					}
				}

				printf("\n< Proceed with modification ? >\n> ");
				rewind(stdin);
				scanf(" %c", &yesno);

				if (toupper(yesno) == 'Y')
				{
					if (member[i].tier == 1)
					{
						member[i].discount = 10;
					}
					else if (member[i].tier == 2)
					{
						member[i].discount = 7;
					}
					else if (member[i].tier == 3)
					{
						member[i].discount = 5;
					}

					if (member[i].expDetails.year < t.wYear)
					{
						member[i].status = 'E';
					}
					else
					{
						member[i].status = 'A';
					}

					modiCount++;
				}

			}

		}

		if (search != 1)
		{
			printf("< Error ! Member Not Found ! >");
		}

		printf("\n< Any more record to modify (Y=yes) >\n>");
		rewind(stdin);
		scanf("%c", &cont);

	} while (toupper(cont) == 'Y');

	fptr = fopen("member.txt", "w");

	for (i = 0; i < pCount; i++)
		fprintf(fptr, "%d|%d|%s|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
			member[i].memberId, member[i].tier, member[i].pDetails.name, member[i].pDetails.gender, member[i].pDetails.cntNumbr, member[i].jDetails.date,
			member[i].jDetails.month, member[i].jDetails.year, member[i].expDetails.date, member[i].expDetails.month, member[i].expDetails.year, member[i].status, member[i].discount, member[i].ptAcc);

	fclose(fptr);
	printf("\n\t< %d Record(s) modified. >\n\n", modiCount);

}
int deleteMem() {

	int memberId, i = 0, pCount = 0, search, action, deleteCount = 0, oCount = 0, dloop = 1;
	char yesno, cont;

	MEM member[50];
	FILE* fptr, * redel, * temp;

	while (dloop != 0)
	{
		printf("\n\n======< Select Action >======\n< 1 > Delete a selected member \n< 2 > Delete all records \n< 3 > Return To Menu\n< 4 > Exit Program \n=============================\n\n>");
		rewind(stdin);
		scanf("%d", &action);
		rewind(stdin);

		switch (action)
		{
		case 1:

			fptr = fopen("member.txt", "r");
			if (fptr == NULL)
			{
				printf("ERROR ! File not Found !");
				exit(-1);
			}
			// scan into array
			while (fscanf(fptr, "%d|%d|%[^|]|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
				&member[i].memberId, &member[i].tier, member[i].pDetails.name, &member[i].pDetails.gender, &member[i].pDetails.cntNumbr,
				&member[i].jDetails.date, &member[i].jDetails.month, &member[i].jDetails.year, &member[i].expDetails.date,
				&member[i].expDetails.month, &member[i].expDetails.year, &member[i].status, &member[i].discount, &member[i].ptAcc) != EOF) {
				i++;
			}
			pCount = i;
			fclose(fptr);

			do
			{
				search = 0;
				printf("\n< Enter ID of Record to be Deleted >\n>");
				rewind(stdin);
				scanf("%d", &memberId);
				rewind(stdin);

				printf("======================================================================================================\n");
				for (i = 0; i < pCount; i++)
				{
					if (memberId == member[i].memberId) {
						search = 1;
						printf("Member Found!\n");
						printf("======================================================================================================\n");
						printf("\n");
						printf("ID                  \t\t\tM%04d\n", member[i].memberId);
						printf("Tier                \t\t\t%-d\n", member[i].tier);
						printf("Name                \t\t\t%-s\n", member[i].pDetails.name);
						printf("Gender              \t\t\t%c\n", member[i].pDetails.gender);
						printf("Contact Number      \t\t\t%-d\n", member[i].pDetails.cntNumbr);
						printf("Join Date           \t\t\t%d/%d/%d\n", member[i].jDetails.date, member[i].jDetails.month, member[i].jDetails.year);
						printf("Expiry Date         \t\t\t%d/%d/%d\n", member[i].expDetails.date, member[i].expDetails.month, member[i].expDetails.year);
						printf("Account Status      \t\t\t%c\n", member[i].status);
						printf("Discount %%         \t\t\t%d\n", member[i].discount);
						printf("Points Accumulated  \t\t\t%d\n", member[i].ptAcc);
						printf("\n");
					}
				}

				if (search == 1)
				{
					printf("\n< Confirm ? >\n");
					printf("< If Yes, Press Y >\n >");
					rewind(stdin);
					scanf("%c", &yesno);
					rewind(stdin);

					if (toupper(yesno) == 'Y')
					{
						for (int i = 0; i < pCount; i++)
						{
							if (memberId == member[i].memberId)
							{
								redel = fopen("recentlyDeleted.txt", "a");
								fprintf(redel, "%d|%d|%s|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
									member[i].memberId, member[i].tier, member[i].pDetails.name, member[i].pDetails.gender, member[i].pDetails.cntNumbr,
									member[i].jDetails.date, member[i].jDetails.month, member[i].jDetails.year, member[i].expDetails.date,
									member[i].expDetails.month, member[i].expDetails.year, member[i].status, member[i].discount, member[i].ptAcc);
								deleteCount++;
								fclose(redel);
							}
							else
							{
								temp = fopen("temp.txt", "a");
								fprintf(temp, "%d|%d|%s|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
								member[i].memberId, member[i].tier, member[i].pDetails.name, member[i].pDetails.gender, member[i].pDetails.cntNumbr,
								member[i].jDetails.date, member[i].jDetails.month, member[i].jDetails.year, member[i].expDetails.date,
								member[i].expDetails.month, member[i].expDetails.year, member[i].status, member[i].discount, member[i].ptAcc);
								fclose(temp);
								remove("member.txt");
								rename("temp.txt", "member.txt");
							}
						}
						for (int i = 0; i < pCount - 1; i++)
						{
							member[i] = member[i + 1];
						}
						pCount--;
					}
					else
					{
						temp = fopen("temp.txt", "a");
						for (int i = 0; i < pCount; i++) {
							fprintf(temp, "%d|%d|%s|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
								member[i].memberId, member[i].tier, member[i].pDetails.name, member[i].pDetails.gender, member[i].pDetails.cntNumbr,
								member[i].jDetails.date, member[i].jDetails.month, member[i].jDetails.year, member[i].expDetails.date,
								member[i].expDetails.month, member[i].expDetails.year, member[i].status, member[i].discount, member[i].ptAcc);
						}
							fclose(temp);
							remove("member.txt");
							rename("temp.txt", "member.txt");
						
					}

				}
				if (search != 1)
				{
					printf("\n< Error ! Record Not Found >\n");
				}

				printf("< Any more records to delete ? >\n>");
				rewind(stdin);
				scanf("%c", &cont);
				rewind(stdin);


			} while (toupper(cont) == 'Y');

			if (deleteCount > 0)
			{
				printf("< %d record(s) deleted successfully. >\n", deleteCount);
			}
			else
			{
				printf("< No record(s) deleted. >\n");
			}

			break;

		case 2:
			printf("\n< Are you sure you want to delete all records? >\n");
			printf("< Enter Y to proceed with deletion, Any key to exit >\n\n>");
			rewind(stdin);
			scanf("%c", &yesno);
			rewind(stdin);
			if (toupper(yesno) == 'Y')
			{
				fptr = fopen("member.txt", "r");
				if (fptr == NULL)
				{
					printf("ERROR ! File not Found !");
					exit(-1);
				}
				// scan into array
				while (fscanf(fptr, "%d|%d|%[^|]|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
					&member[i].memberId, &member[i].tier, member[i].pDetails.name, &member[i].pDetails.gender, &member[i].pDetails.cntNumbr,
					&member[i].jDetails.date, &member[i].jDetails.month, &member[i].jDetails.year, &member[i].expDetails.date,
					&member[i].expDetails.month, &member[i].expDetails.year, &member[i].status, &member[i].discount, &member[i].ptAcc) != EOF) {
					i++;
				}
				pCount = i;
				fclose(fptr);

				redel = fopen("recentlyDeleted.txt", "a");
				for (i = 0; i < pCount; i++)
				{
					fprintf(redel, "%d|%d|%s|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
						member[i].memberId, member[i].tier, member[i].pDetails.name, member[i].pDetails.gender, member[i].pDetails.cntNumbr,
						member[i].jDetails.date, member[i].jDetails.month, member[i].jDetails.year, member[i].expDetails.date,
						member[i].expDetails.month, member[i].expDetails.year, member[i].status, member[i].discount, member[i].ptAcc);
				}

				fclose(redel);

				fptr = fopen("member.txt", "w");
				fclose(fptr);
				printf("\n< All records deleted successfully. >\n");
			}
			else
				break;
		case 3:
			dloop = 0;
			break;
		case 4:
			printf("Thanks For Using This Program");
			exit(-1);
		default:
			printf("\n < Error ! Select Valid Input ! > \n");
			break;
		}
	}


}
void genReport() {

	// Filter by ?
	// gender, date, status, tiers
	//recenly removed ?


	int i = 0, pCount = 0, search = 0, modiCount = 0, tier, grloop = 1, day = 0, month = 0, year = 0;
	int nYear = 0, choice = 0, error = 1, count;
	char gender = { '\0' }, status = { '\0' };

	SYSTEMTIME t;//structure for date, time 
	GetLocalTime(&t);//get date /time from OS
	MEM member[50];
	FILE* fptr;

	fptr = fopen("member.txt", "r");
	if (fptr == NULL) {
		printf("Error: File not found!\n");
		exit(-1);
	}

	//retrieve all data into array
	while (fscanf(fptr, "%d|%d|%[^|]|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
		&member[i].memberId, &member[i].tier, member[i].pDetails.name, &member[i].pDetails.gender, &member[i].pDetails.cntNumbr,
		&member[i].jDetails.date, &member[i].jDetails.month, &member[i].jDetails.year, &member[i].expDetails.date,
		&member[i].expDetails.month, &member[i].expDetails.year, &member[i].status, &member[i].discount, &member[i].ptAcc) != EOF) {

		i++;
	}
	pCount = i;
	fclose(fptr);

	while (grloop != 0)
	{
		rewind(stdin);
		printf("\n\nSelect Filter To Report By \n==========================\n< 1 > Gender\n< 2 > Membership Status\n< 3 > Membership Tiers\n< 4 > Recently Added\n< 5 > Recently Deleted\n< 6 > Return to Menu\n< 7 > Exit Program \n>");
		rewind(stdin);
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			error = 1;
			while (error != 0) {
				printf("\n< Enter Gender to look for ( M = Male, F = Female ) >\n>");
				rewind(stdin);
				scanf("%c", &gender);

				if (chkGender(gender)) {
					error = 0; // set error to 0 to exit the loop
				}
				else {
					printf("\n< Error! Enter Valid Input! ( M = Male, F = Female ) >\n");
				}
			}

			day = t.wDay;
			month = t.wMonth;
			year = t.wYear;
			count = 0;

			printf("\n<================================================= Report of Members with Gender '%c' as of %02d/%02d/%04d =======================================================>\n", toupper(gender), day, month, year);
			printf("Member ID  Tier  Name                          Gender  Contact Number  Date joined    Expiry Date    Membership Status  Discount%%  Points Accumulated\n");
			printf("\n<============================================================================================================================================================>\n");

			for (i = 0; i < pCount; i++)
			{
				if (toupper(member[i].pDetails.gender) == toupper(gender))
				{
					printf("M%04d       %-5d %-30s %-7c(+60)%-15d %02d/%02d/%-4d    %02d/%02d/%-4d     \t%-1c              %-2d         %-7d\n",
						member[i].memberId, member[i].tier, member[i].pDetails.name, member[i].pDetails.gender, member[i].pDetails.cntNumbr, member[i].jDetails.date,
						member[i].jDetails.month, member[i].jDetails.year, member[i].expDetails.date, member[i].expDetails.month, member[i].expDetails.year, member[i].status, member[i].discount, member[i].ptAcc);
					count++;
				}
			}

			printf("\n< There are %d Members With Gender '%c' >\n", count, toupper(gender));
			error = 1;
			break;
		case 2:
			error = 1;
			while (error != 0) {
				printf("\n< Enter Membership Status To Filter By ( A = Active, E = Expired ) >\n>");
				rewind(stdin);
				scanf("%c", &status);

				if (chkStatus(status)) {
					error = 0; // set error to 0 to exit the loop
				}
				else {
					printf("\n< Error! Enter Valid Input! ( A = Active, E = Expired ) >\n");
				}
			}

			day = t.wDay;
			month = t.wMonth;
			year = t.wYear;
			count = 0;

			printf("\n<====================================================== Report of Members with Status %c as of %02d/%02d/%04d ====================================================>\n", toupper(status), day, month, year);
			printf("Member ID  Tier  Name                          Gender  Contact Number  Date joined    Expiry Date    Membership Status  Discount%%  Points Accumulated\n");
			printf("\n<============================================================================================================================================================>\n");

			for (i = 0; i < pCount; i++)
			{
				if (toupper(member[i].status) == toupper(status))
				{
					printf("M%04d       %-5d %-30s %-7c(+60)%-15d %02d/%02d/%-4d    %02d/%02d/%-4d     \t%-1c              %-2d         %-7d\n",
						member[i].memberId, member[i].tier, member[i].pDetails.name, member[i].pDetails.gender, member[i].pDetails.cntNumbr, member[i].jDetails.date,
						member[i].jDetails.month, member[i].jDetails.year, member[i].expDetails.date, member[i].expDetails.month, member[i].expDetails.year, member[i].status, member[i].discount, member[i].ptAcc);
					count++;
				}
			}

			printf("\n< There are %d Members With Status '%c' >\n", count, toupper(status));
			error = 1;
			break;
		case 3:
			tier = 0;
			error = 1;
			while (error != 0) {
				rewind(stdin);
				printf("\n< Enter Tier To Filter By >\n> ");
				rewind(stdin);
				scanf("%d", &tier);

				if (chkTier(tier)) {
					error = 0; // set error to 0 to exit the loop
				}
				else {
					printf("\n< Error! Enter Valid Input!  ( Tiers = 1-3 ) >\n");
				}
			}

			day = t.wDay;
			month = t.wMonth;
			year = t.wYear;
			count = 0;

			printf("\n<======================================================= Report of Members with Tiers %d as of %02d/%02d/%04d ====================================================>\n", tier, day, month, year);
			printf("Member ID  Tier  Name                          Gender  Contact Number  Date joined    Expiry Date    Membership Status  Discount%%  Points Accumulated\n");
			printf("\n<============================================================================================================================================================>\n\n");
			for (i = 0; i < pCount; i++)
			{
				if (member[i].tier == tier)
				{
					printf("M%04d       %-5d %-30s %-7c(+60)%-15d %02d/%02d/%-4d    %02d/%02d/%-4d     \t%-1c              %-2d         %-7d\n",
						member[i].memberId, member[i].tier, member[i].pDetails.name, member[i].pDetails.gender, member[i].pDetails.cntNumbr, member[i].jDetails.date,
						member[i].jDetails.month, member[i].jDetails.year, member[i].expDetails.date, member[i].expDetails.month, member[i].expDetails.year, member[i].status, member[i].discount, member[i].ptAcc);
					count++;
				}
			}

			printf("\n< There are %d Members With Tier '%d' >\n", count, tier);
			break;
		case 4:
			rAddedReport();
			break;
		case 5:
			rDeletedReport();
			break;
		case 6:
			grloop = 0;
			break;
		case 7:
			printf("Thanks For Using This Program");
			exit(-1);
		default:
			printf("< Error ! Enter Valid Value ! >\n");
			break;
		}

	}

}
void displayAll() {
	MEM member;
	FILE* fptr;
	int mCount = 0, day, month, year;

	SYSTEMTIME t;//structure for date, time 
	GetLocalTime(&t);//get date /time from OS

	day = t.wDay;
	month = t.wMonth;
	year = t.wYear;

	fptr = fopen("member.txt", "r");
	if (fptr == NULL) {
		printf("Error: File not found!\n");
		exit(-1);
	}
	printf("\n<================================================================= All Existing Members =====================================================================>\n");
	printf("Member ID  Tier  Name                          Gender  Contact Number  Date joined    Expiry Date    Membership Status  Discount%%  Points Accumulated\n");
	printf("<============================================================================================================================================================>\n");

	while (fscanf(fptr, "%d|%d|%[^|]|%c|%d|%d|%d|%d|%d|%d|%d|%c|%d|%d|\n",
		&member.memberId, &member.tier, member.pDetails.name, &member.pDetails.gender, &member.pDetails.cntNumbr,
		&member.jDetails.date, &member.jDetails.month, &member.jDetails.year, &member.expDetails.date,
		&member.expDetails.month, &member.expDetails.year, &member.status, &member.discount, &member.ptAcc) != EOF) {

		printf("M%04d       %-5d %-30s %-7c(+60)%-15d %02d/%02d/%-4d    %02d/%02d/%-4d     \t%-1c              %-2d         %-7d\n",
			member.memberId, member.tier, member.pDetails.name, member.pDetails.gender, member.pDetails.cntNumbr, member.jDetails.date,
			member.jDetails.month, member.jDetails.year, member.expDetails.date, member.expDetails.month, member.expDetails.year, member.status, member.discount, member.ptAcc);
		mCount++;
	}

	printf("\n< There are %d Members as of %02d/%02d/%04d >\n", mCount, day, month, year);
	fclose(fptr);
}
//KhooLiXuan's module ------------------------------------------------------------------------------------------^

//Nicholas's module -------------------------------------------------------------------------------------------------

void salesMain();
void displaySales();
void searchSales();
void addSales();
void modifySales();
void deleteSales();
void displayReport();
void salesReport();
void modifyReport();

void salesMain() //settle
{

	printf("\n-------------------------------\n");
	printf("| Sales Management System |");
	printf("\n-------------------------------\n");
	int num = 0;
	do
	{
		printf("\n-------------------------------\n");
		printf("List of Sales Module Functions");
		printf("\n-------------------------------\n");
		printf("1) Display Sales Data \n");
		printf("2) Search Sales  \n");
		printf("3) Add Sales  \n");
		printf("4) Modify Sales  \n");
		printf("5) Delete Sales  \n");
		printf("6) Display Sales Report  \n");
		printf("\nEnter a number between (1-6) > \n");

		rewind(stdin);
		scanf("%d", &num);

	} while (num < 0 || num > 6);
	if (num == 0)
		return 0;
	else
	{
		switch (num)
		{
		case 1:
			displaySales();
			break;
		case 2:
			searchSales();
			break;
		case 3:
			addSales();
			break;
		case 4:
			modifySales();
			break;
		case 5:
			deleteSales();
			break;
		case 6:
			displayReport();
			break;
		default:
			printf("END");
			break;
		}
	}
}

void displaySales() //settle
{
	Sales sales[101];
	int salesID, found = 0, i = 0, count;

	FILE* fptr;
	fptr = fopen("sales.txt", "r");
	if (fptr == NULL) {
		printf("Unable to open file\n");
		exit(-1);
	}

	printf("\n===============================================================================================");
	printf("\nDisplaying Sales");
	printf("\n-----------------------------------------------------------------------------------------------");
	printf("\nSales ID\tItem Code\tMember ID\tName\t\t\tPrice\t\tQuantity");
	printf("\n===============================================================================================");

	while (fscanf(fptr, "%[^,], %[^,], %[^,], %[^,], %f, %d\n", &sales[i].salesID, &sales[i].itemcode, &sales[i].memberID, sales[i].name, &sales[i].price, &sales[i].quantity) != EOF)
	{
		printf("\n%s\t\t%s\t\t%s\t\t%-10s\t\t%.2f\t\t%d\n", sales[i].salesID, sales[i].itemcode, sales[i].memberID, sales[i].name, sales[i].price, sales[i].quantity);
		i++;
	}
	printf("\n-----------------------------------------------------------------------------------------------");
	printf("\n\n");
	fclose(fptr);
	salesMain();
}


void searchSales()  //settle
{
	char yes;

	FILE* fptr;
	Sales sales[101];

	int found = 0, i = 0;
	char salesID[10];

	fptr = fopen("sales.txt", "r");
	if (fptr == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}

	printf("============================ \n");
	printf("Search Sales Data");
	printf("\n============================ \n");
	printf("\nEnter Sales ID: ");
	scanf("%s", &salesID);
	printf("Displaying Sales with ID: %s\n", salesID);

	while (fscanf(fptr, "%[^,], %[^,], %[^,], %[^,], %f, %d\n", &sales[i].salesID, &sales[i].itemcode, &sales[i].memberID, sales[i].name, &sales[i].price, &sales[i].quantity) != EOF) {
		if (strcmp(sales[i].salesID, salesID) == 0) {
			found = 1;
			printf("\n\nSales Data");
			printf("\n----------------------------------------------------------------------------------------------------");
			printf("\nSales ID\tItem Code\tMember ID\tName\t\t\tPrice\t\tQuantity");
			printf("\n----------------------------------------------------------------------------------------------------");
			printf("\n%s\t\t%s\t\t%s\t\t%-10s\t\t%.2f\t\t%d\n", sales[i].salesID, sales[i].itemcode, sales[i].memberID, sales[i].name, sales[i].price, sales[i].quantity);
			rewind(stdin);
			break; // exit the loop once the sales data has been displayed
		}
		i++;
	}

	if (!found) {
		printf("\nError! Sales not found.");
	}

	while (!found) { // ask for a new sales ID if the previous one was not found
		printf("\nEnter another Sales ID (or 0 to exit): ");
		scanf("%s", &salesID);
		if (salesID[0] == '0') {
			break; // exit the loop if the user enters 0
		}
		printf("Displaying Sales with ID: %s\n", salesID);
		i = 0; // reset i to 0 to start searching from the beginning of the sales array
		rewind(fptr);
		while (fscanf(fptr, "%[^,], %[^,], %[^,], %[^,], %f, %d\n", &sales[i].salesID, &sales[i].itemcode, &sales[i].memberID, sales[i].name, &sales[i].price, &sales[i].quantity) != EOF) {
			if (strcmp(sales[i].salesID, salesID) == 0) {
				found = 1;
				printf("\n\nSales Data");
				printf("\n----------------------------------------------------------------------------------------------------");
				printf("\nSales ID\tItem Code\tMember ID\tName\t\t\tPrice\t\tQuantity");
				printf("\n----------------------------------------------------------------------------------------------------");
				printf("\n%s\t\t%s\t\t%s\t\t%-10s\t\t%.2f\t\t%d\n", sales[i].salesID, sales[i].itemcode, sales[i].memberID, sales[i].name, sales[i].price, sales[i].quantity);
				rewind(stdin);
				break;
			}
		}
	}
	salesMain();
}


void addSales()
{
	SYSTEMTIME t;
	GetLocalTime(&t);

	char yes = ' ', choice;
	Sales sales;
	His history;

	FILE* fptr;
	FILE* report;
	fptr = fopen("sales.txt", "a");
	report = fopen("report.txt", "a");

	if (fptr == NULL)
	{
		printf("Unable to open file\n");
		exit(-1);
	}

	if (report == NULL)
	{
		printf("Error opening file.\n");
		exit(-1);
	}

	printf("============================ \n");
	printf("Add new sales\n");
	printf("============================\n");
	do
	{
		printf("\nEnter Sales ID: ");
		rewind(stdin);
		scanf("%[^\n]", &sales.salesID);

		printf("\nEnter Item Code: ");
		rewind(stdin);
		scanf("%[^\n]", &sales.itemcode);

		printf("\nEnter Member ID: ");
		rewind(stdin);
		scanf("%[^\n]", &sales.memberID);

		printf("\nEnter Item Name: ");
		rewind(stdin);
		scanf("%[^\n]", sales.name);

		printf("\nEnter Price: ");
		scanf("%f", &sales.price);

		printf("\nEnter Quantity: ");
		scanf("%d", &sales.quantity);

		printf("Confirm Add ? (Y/N) : ");
		rewind(stdin);
		scanf("%c", &choice);

		if (toupper(choice) == 'Y')
		{
			strcpy(history.action, "Added");
			strcpy(history.salesID, sales.salesID);
			strcpy(history.itemcode, sales.itemcode);
			strcpy(history.memberID, sales.memberID);
			strcpy(history.name, sales.name);
			history.price = sales.price;
			history.quantity = sales.quantity;
			history.minute = t.wMinute;
			history.hour = t.wHour;
			history.day = t.wDay;
			history.month = t.wMonth;
			history.year = t.wYear;

			fprintf(report, "%s, %s, %s, %s, %s, %.2f, %d, %d, %d, %d, %d, %d\n", history.action, history.salesID, history.itemcode, history.memberID, history.name, history.price, history.quantity, history.minute, history.hour, history.day, history.month, history.year);
			fprintf(fptr, "%s, %s, %s, %s, %.2f, %d\n", sales.salesID, sales.itemcode, sales.memberID, sales.name, sales.price, sales.quantity);
			printf("\n===================================");
			printf("\nSales record added successfully.\n");
			printf("\n===================================");
		}
		else
		{
			printf("\n=========================");
			printf("\nSales not added !\n");
			printf("\n=========================");
		}

		printf("\nAdd another Sales ? (Y/N) :");
		rewind(stdin);
		scanf("%c", &yes);

	} while (toupper(yes) == 'Y');

	fclose(fptr);
	fclose(report);
	printf("\nReturning to Sales Menu");
	salesMain();
}



void modifySales() //settle
{
	int i = 0, pCount = 0, found = 0, modiCount = 0, newquantity;
	char yesno = ' ', cont = ' ', searchSalesID[5], newsalesID[10], newitemcode[10], newmemberID[10], newname[20];
	float newprice;

	SYSTEMTIME t;
	GetLocalTime(&t);
	Sales sales[101];
	His history;

	FILE* fptr;
	FILE* report2;
	fptr = fopen("sales.txt", "r");
	report2 = fopen("report2.txt", "a");

	if (fptr == NULL)
	{
		printf("Error opening file.\n");
		exit(-1);
	}


	if (report2 == NULL)
	{
		printf("Error opening file.\n");
		exit(-1);
	}


	while (fscanf(fptr, "%[^,], %[^,], %[^,], %[^,], %f, %d\n", &sales[pCount].salesID, &sales[pCount].itemcode, &sales[pCount].memberID, sales[pCount].name, &sales[pCount].price, &sales[pCount].quantity) != EOF)
	{
		pCount++;
	}

	fclose(fptr);

	do
	{
		found = 0;
		printf("====================");
		printf("\nModifying Sales ");
		printf("\n====================");
		printf("\nEnter Sales ID to modify : ");
		rewind(stdin);
		scanf("%[^\n]", &searchSalesID);

		for (i = 0; i < pCount; i++)
		{
			if (strcmp(sales[i].salesID, searchSalesID) == 0) {
				found = 1;
				printf("\nSales ID\tItem Code\tMember ID\tName\t\t\tPrice\t\tQuantity");
				printf("\n----------------------------------------------------------------------------------------------------\n");
				printf("\n%s\t\t%s\t\t%s\t\t%-10s\t\t%.2f\t\t%d\n", sales[i].salesID, sales[i].itemcode, sales[i].memberID, sales[i].name, sales[i].price, sales[i].quantity);

				//update 

				printf("\n\nEnter the new values and name\n");
				printf("---------------------------------");
				printf("\nSales ID : ");
				rewind(stdin);
				scanf("%[^\n]", &newsalesID);

				printf("\nItem Code : ");
				rewind(stdin);
				scanf("%[^\n]", &newitemcode);

				printf("\nMember ID : ");
				rewind(stdin);
				scanf("%[^\n]", &newmemberID);

				printf("\nName : ");
				rewind(stdin);
				scanf("%[^\n]", &newname);

				printf("\nPrice : ");
				scanf("%f", &newprice);

				printf("\nQuantity : ");
				scanf("%d", &newquantity);

				printf("Confirm to Modify (Y/N)? > ");
				rewind(stdin);
				scanf("%c", &yesno);

				if (toupper(yesno) == 'Y')
				{
					strcpy(sales[i].salesID, newsalesID);
					strcpy(sales[i].itemcode, newitemcode);
					strcpy(sales[i].memberID, newmemberID);
					strcpy(sales[i].name, newname);
					sales[i].price = newprice;
					sales[i].quantity = newquantity;

					strcpy(history.salesID, sales[i].salesID);
					strcpy(history.itemcode, sales[i].itemcode);
					strcpy(history.memberID, sales[i].memberID);
					strcpy(history.name, sales[i].name);
					history.price = sales[i].price;
					history.quantity = sales[i].quantity;
					history.minute = t.wMinute;
					history.hour = t.wHour;
					history.day = t.wDay;
					history.month = t.wMonth;
					history.year = t.wYear;

					fprintf(report2, "%s, %s, %s, %s, %.2f, %d, %d, %d, %d, %d, %d\n", history.salesID, history.itemcode, history.memberID, history.name, history.price, history.quantity, history.minute, history.hour, history.day, history.month, history.year);
					fprintf(fptr, "%s, %s, %s, %s, %.2f, %d\n", sales[i].salesID, sales[i].itemcode, sales[i].memberID, sales[i].name, sales[i].price, sales[i].quantity);

					printf("\nUpdate record:\n");
					printf("\nSales ID\tItem Code\tMember ID\tName\t\t\tPrice\t\tQuantity");
					printf("\n----------------------------------------------------------------------------------------------------\n");
					printf("\n%s\t\t%s\t\t%s\t\t%-10s\t\t%.2f\t\t%d\n", sales[i].salesID, sales[i].itemcode, sales[i].memberID, sales[i].name, sales[i].price, sales[i].quantity);
					modiCount++;

					fptr = fopen("sales.txt", "w");

					for (i = 0; i < pCount; i++)
					{
						fprintf(fptr, "%s, %s, %s, %s, %.2f, %d\n", sales[i].salesID, sales[i].itemcode, sales[i].memberID, sales[i].name, sales[i].price, sales[i].quantity);
					}

					printf("\n\n\t%d Record(s) modified.\n\n", modiCount);
					fclose(fptr);
					fclose(report2);
				}
				else
				{
					printf("\n\n[!] Modify Cancelled. [!]");
					fclose(fptr);
					fclose(report2);

				}
			}
		}
		printf("\nModify anymore sales record? (Y/N) > ");
		rewind(stdin);
		scanf("%c", &cont);

	} while (toupper(cont) == 'Y');

	if (!found)
	{
		fclose(fptr);
		fclose(report2);
		printf("\nReturning to menu");
		salesMain();
	}
	salesMain();
}


void deleteSales()
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	int i = 0, entryNum = 0, found = 0;
	char choice = ' ', searchsalesID[5];

	Sales sales[101];
	His history;

	FILE* fptr;
	FILE* report;
	fptr = fopen("sales.txt", "r");

	if (fptr == NULL)
	{
		printf("Error opening file.\n");
		exit(-1);
	}

	while (fscanf(fptr, "%[^,], %[^,], %[^,], %[^,], %f, %d\n", &sales[i].salesID, &sales[i].itemcode, &sales[i].memberID, &sales[i].name, &sales[i].price, &sales[i].quantity) != EOF)
		i++;

	entryNum = i;
	fclose(fptr);
	printf("============================ \n");
	printf("Delete Sales\n");
	printf("============================\n");
	printf("Enter Sales ID : ");
	rewind(stdin);
	scanf("%s", &searchsalesID);

	for (i = 0; i < entryNum; i++) {
		if (strcmp(sales[i].salesID, searchsalesID) == 0) {
			found = 1;
			printf("\n\nSales Data");
			printf("\n----------------------------------------------------------------------------------------------------");
			printf("\nSales ID\tItem Code\tMember ID\tName\t\t\tPrice\t\tQuantity");
			printf("\n----------------------------------------------------------------------------------------------------");
			printf("\n%s\t\t%s\t\t%s\t\t%-10s\t\t%.2lf\t\t%d\n", sales[i].salesID, sales[i].itemcode, sales[i].memberID, sales[i].name, sales[i].price, sales[i].quantity);
			printf("\nConfirm Delete Sales ? (Y/N) : ");
			rewind(stdin);
			scanf("%c", &choice);

			if (toupper(choice) == 'Y')
			{
				report = fopen("report.txt", "a");

				if (report == NULL)
				{
					printf("Error opening file.\n");
					exit(-1);
				}

				printf("Sales Deleted !");

				strcpy(history.action, "Delete");
				strcpy(history.salesID, sales[i].salesID);
				strcpy(history.itemcode, sales[i].itemcode);
				strcpy(history.memberID, sales[i].memberID);
				strcpy(history.name, sales[i].name);
				history.price = sales[i].price;
				history.quantity = sales[i].quantity;
				history.minute = t.wMinute;
				history.hour = t.wHour;
				history.day = t.wDay;
				history.month = t.wMonth;
				history.year = t.wYear;

				fprintf(report, "%s, %s, %s, %s, %s, %.2f, %d, %d, %d, %d, %d, %d\n", history.action, history.salesID, history.itemcode, history.memberID, history.name, history.price, history.quantity, history.minute, history.hour, history.day, history.month, history.year);
				fclose(report);

				for (int j = i; j < entryNum - 1; j++)
				{
					sales[j] = sales[j + 1];
				}

				entryNum--;


				fptr = fopen("sales.txt", "w");

				if (fptr == NULL)
				{
					printf("Error opening file.\n");
					exit(-1);
				}

				for (i = 0; i < entryNum; i++)
				{
					fprintf(fptr, "%s, %s, %s, %s, %.2f, %d\n", sales[i].salesID, sales[i].itemcode, sales[i].memberID, sales[i].name, sales[i].price, sales[i].quantity);
				}

				fclose(fptr);
			}
		}

	} salesMain();
}

void displayReport()
{
	int ans = 0;

	printf("\nGenerate Sales Report");
	printf("\n--------------------------");

	printf("\nSelect a number : ");
	printf("\n1) Add/Delete Sales");
	printf("\n2) Modify Report");

	printf("\nEnter Number > ");
	scanf("%d", &ans);
	rewind(stdin);

	switch (ans) {
	case 1:
		salesReport();
		break;
	case 2:
		modifyReport();
		break;
	default:
		printf("\n\nReturn to Sales Main Menu\n\n");
		salesMain();
		break;
	}
}

void salesReport()
{
	FILE* report;
	His history[101];
	int i = 0;

	report = fopen("report.txt", "r");
	if (report == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}

	printf("\nAdd and Delete Sales Report and History");
	printf("\n--------------------------------------------------------------------------------------------------------------");
	printf("\nAction\tSales ID\tItem Code\tMember ID\tName\t\tPrice\tQuantity\tTime [HH:MM][DD/MM/YYYY]\n");
	printf("\n--------------------------------------------------------------------------------------------------------------");

	while (fscanf(report, "%[^,], %[^,], %[^,], %[^,], %[^,], %f, %d, %d, %d, %d, %d, %d\n",
		&history[i].action, &history[i].salesID, &history[i].itemcode,
		&history[i].memberID, &history[i].name, &history[i].price,
		&history[i].quantity, &history[i].minute, &history[i].hour, &history[i].day, &history[i].month, &history[i].year) != EOF) {

		printf("\n%s\t%s\t\t%s\t\t%s\t\t%-10s\t%.2f\t%d", history[i].action, history[i].salesID, history[i].itemcode, history[i].memberID, history[i].name, history[i].price, history[i].quantity);
		printf("\t\t[%02d:%02d][%02d/%02d/%02d]\n", history[i].minute, history[i].hour, history[i].day, history[i].month, history[i].year);
		i++;

	}
	fclose(report);
	salesMain();
}

void modifyReport()
{
	FILE* report2;
	His history[101];
	int i = 0;

	report2 = fopen("report2.txt", "r");
	if (report2 == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}

	printf("\nModify Sales Report and History");
	printf("\n--------------------------------------------------------------------------------------------------------------");
	printf("\nSales ID\tItem Code\tMember ID\tName\t\tPrice\tQuantity\tTime [HH:MM][DD/MM/YYYY]\n");
	printf("\n--------------------------------------------------------------------------------------------------------------");

	while (fscanf(report2, "%[^,], %[^,], %[^,], %[^,], %f, %d, %d, %d, %d, %d, %d\n",
		&history[i].salesID, &history[i].itemcode,
		&history[i].memberID, &history[i].name, &history[i].price,
		&history[i].quantity, &history[i].minute, &history[i].hour, &history[i].day, &history[i].month, &history[i].year) != EOF) {

		printf("\n%s\t\t%s\t\t%s\t\t%-10s\t%.2f\t%d", history[i].salesID, history[i].itemcode, history[i].memberID, history[i].name, history[i].price, history[i].quantity);
		printf("\t\t[%02d:%02d][%02d/%02d/%02d]\n", history[i].minute, history[i].hour, history[i].day, history[i].month, history[i].year);
		i++;

	}
	fclose(report2);
	salesMain();
}
//Nicholas's module ---------------------------------------------------------------------------------------------------^




//Main module --------------------------------------------------------------------------------------------------
void main() {

	int ans;
	do 
	{
		ans = 6;
		printf("\n======================================================================================================\n\n");
		printf("           ( ( ( (                  ====   ====   ====  ====  ====  ====     ====  =   =  ====  ====  \n");
		printf("            ) ) ) )                =      =    =  =     =     =     =       =      =   = =    = =   = \n");
		printf("       ...............             =      =    =  ====  ====  ====  ====     ====  ===== =    = ====  \n");
		printf("       |             |oo           =      =    =  =     =     =     =            = =   = =    = =     \n");
		printf("       |             |  oo          ====   ====   =     =     ====  ====     ====  =   =  ====  =     \n\n");
		printf("       |             |  oo             ====   =   =   ====  ===== ====  =   =                         \n");
		printf("       \\             /oo              =       =   =  =        =   =     == ==                         \n");
		printf("        `-----------'                  ====    = =    ====    =   ====  = = =                         \n");
		printf("                                           =    =         =   =   =     =   =                         \n");
		printf("                                       ====     =     ====    =   ====  =   =                         \n");
		printf("\n======================================================================================================\n\n");
		printf("\tSelect from 1 to 4 for entering module\n");
		printf("\n\t[1]Staff Management Module\n\t[2]Stock Management Module\n\t[3]Member Management Module\n\t[4]Sales Management Module\n\t[0]Exit program\n\n");
		printf("\tEnter a value > ");
		rewind(stdin);
		scanf(" %d", &ans);

		switch (ans) {
		case 1:
			staffmain();
			break;
		case 2:
			stockMainfirst();
			break;
		case 3:
			membermain();
			break;
		case 4:
			salesMain();
			break;
		case 0:
			printf("\n\tExit Program ............(bye bye!)\n\n");
			return 0;
		default:
			printf("\n\t=================================\n\t Error!! Not within select range\n\t=================================\n");
		}
	} while (ans >= 1);
}