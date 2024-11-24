/*
GROUP MICRO PROJECT FIRST YEAR

__CONTACT MANAGEMENT SYSTEM__

Group Students -
1. Nikhil   - 6650
2. Sajal    - 6651
3. Harini   - 6652
4. Leader   - 6653
5. Sameera  - 6654
6.
7. Aditya   - 6656
*/


//initializing all the header files required for the project.
#include <stdio.h>
#include <string.h>

//Creating a Structure for storing all the information of a contact.
struct contactsInfo {
    char name[25];
    char phoneNum[12];
    char address[20];
    char email[50];
}contacts, editContacts;

//Initializing all the Functions used in the programme
void addContact();
void viewContact();
void deleteContact();
void editContact();
void searchContact();

//Starting of the whole code
int main(void)
{
    // Initializing all the Datatype with Variables.
    int inputNum;

    // Making a do-while loop to execute the first menu. The menu keeps iterating until user presses 0.
    do {
        printf("-------------------------\n");
        printf("CONTACT MANAGEMENT SYSTEM\n");
        printf("-------------------------\n");
        printf("1. Add Contact\n");
        printf("2. View Contact\n");
        printf("3. Delete Contacts\n");
        printf("4. Edit Contacts\n");
        printf("5. Search Contacts\n");
        printf("0. Exit\n");

        // Taking input from the user on their choice.
        printf("Enter the number corresponding to the option:");
        scanf("%d", &inputNum);

        // Switch Statement for the respective number from menu.
        // Each case have a respective function to make the code clean.
        switch (inputNum) {
            case 1:
                addContact();
            break;
            case 2:
                viewContact();
            break;
            case 3:
                deleteContact();
            break;
            case 4:
                editContact();
            break;
            case 5:
                searchContact();
            break;
            default: ;
        }
    }while(inputNum!=0);
}

/* All the case functions are described below.
 * We have used a file to store the data of the user. So that the data is not lost.
 * The code is repeated multiple times.
 */


// Function for adding of a contact
void addContact(){
    // Initializing the file with name CONTACT.TXT in mode Append.
    // The file will append the data given by the user multiple times.
    FILE *fp = fopen("contact.txt", "a");

    // Creating a menu to read the data from the user
    printf("-------------------------\n");
    printf("ADD NEW CONTACT\n");
    printf("-------------------------\n");
    printf("Enter Name    : "); fflush(stdin); gets(contacts.name);
    printf("Enter Number  : "); fflush(stdin); gets(contacts.phoneNum);
    printf("Enter Address : "); fflush(stdin); gets(contacts.address);
    printf("Enter Email   : "); fflush(stdin); gets(contacts.email);

    // Storing the data given by user in the CONTACT.TXT file.
    fprintf(fp,"%s  %s  %s  %s\n",contacts.name,contacts.phoneNum,contacts.address,contacts.email);

    // Closing the file CONTACT.TXT
    fclose(fp);

    // Allowing user to know that the code was executed SUCCESSFULLY.
    printf("----SUCCESSFULLY ADDED CONTACT----\n");
    printf("\nPress any key to continue...");
    getchar();
}

//Creating a Function for Viewing Contacts.
void viewContact() {
    // Creating a Variable to check if the file is opened or not.
    int checkFileOpen = 0;

    // Opening file CONTACT.TXT in READ mode.
    FILE *fp = fopen("contact.txt", "r");

    // Printing the total list on screen
    printf("\n-------------------------\n");
    printf("CONTACT LIST\n");
    printf("-------------------------\n");
    printf("%-15s%-15s%-15s%-15s\n","Name","Number","Address","Email");

    /* Checking the condition if the file was opened or not.
     * If the file was not opened that means file has no DATA.
     * If the file is opened it prints the total data.
     * EOF = END OF FILE
     */
    while(fscanf(fp,"%s  %s  %s  %s\n",contacts.name,contacts.phoneNum,contacts.address,contacts.email)!=EOF) {
        checkFileOpen=1;
        printf("%-15s%-15s%-15s%-15s\n",contacts.name,contacts.phoneNum,contacts.address,contacts.email);
    }

    if(checkFileOpen==0) {
        printf("==========================\n");
        printf("---THE FILE HAS NO DATA---\n");
        printf("==========================\n\n\n");
    }

    // Closing the open file.
    fclose(fp);


}

//Creating a file for deleting the Contact.
void deleteContact() {
    // Creating a Variable to check if the file is opened or not.
    int checkFileOpen = 0;

    // Opening file CONTACT.TXT in READ mode.
    FILE *fp = fopen("contact.txt", "r");
    // Opening file TEMP.TXT in WRITE mode.
    FILE *newRecord = fopen("temp.txt", "w");

    // Asking the name of the person that needs to be deleted.
    // using fflush to clean the Buffered DATA.
    // Using gets to red the info.
    printf("Enter Name: "); fflush(stdin); gets(editContacts.name);

    /* Using fscanf to read the data from CONTACT.TXT file as it is in read mode only.
     * Executing file until the end of file is reached
     * EOF = End Of File
     * using strcmp to compare the USER GIVEN DATA that we took before with the NAMES of Contacts in the CONTACT.TXT file.
     * skipping the found data and rewriting all the data in a TEMP.TXT file.
     * This will not write the name of the data that we don't need. Ultimately deleting the data.
     */
    while(fscanf(fp,"%s  %s  %s  %s\n",contacts.name,contacts.phoneNum,contacts.address,contacts.email)!=EOF) {
        if(strcmpi(editContacts.name, contacts.name)==0) {
            checkFileOpen=1;
        }
        else {
            fprintf(newRecord,"%s  %s  %s  %s\n",contacts.name,contacts.phoneNum,contacts.address,contacts.email);
        }
    }

    // Closing the File fp and newRecord.
    // Then removing CONTACT.TXT file and renaming the TEMP.TXT file to CONTACT.TXT.
    fclose(fp);
    fclose(newRecord);
    remove("contact.txt");
    rename("temp.txt","contact.txt");

    // Checking if the file was opened or not.
    if(checkFileOpen==0) {
        printf("-------------------------\n");
        printf("DELETE CONTACT (ERROR)\n");
        printf("-------------------------\n");
        printf("Name not found.\n\n");
    } else {
        printf("\n----Successfully Deleted----\n");
    }

    printf("\nPress any key to continue...\n");
    getchar();
}


// Creating function to Edit Contacts.
void editContact() {
    // Variables and check open file.
    int inputNum, checkFileOpen =0;

    // Opening the file CONTACT.TXT in read mode.
    FILE *fp = fopen("contact.txt", "r");
    // Opening the TEMP.TXT in write mode.
    FILE *newRecord = fopen("temp.txt", "w");
    // Reading the data that user wants to edit.
    printf("Enter Name: "); fflush(stdin); gets(editContacts.name);

    /* Using fscanf to read the data from CONTACT.TXT file as it is in read mode only.
     * Executing file until the end of file is reached
     * EOF = End Of File
     * using strcmp to compare the USER GIVEN DATA that we took before with the NAMES of Contacts in the CONTACT.TXT file.
     * Asking the user what they want to edit in that data.
     * Creating a switch according to the need.
     * Updating the given data.
     */
    while(fscanf(fp,"%s  %s  %s  %s\n",contacts.name,contacts.phoneNum,contacts.address,contacts.email)!=EOF) {
        if(strcmp(editContacts.name, contacts.name)==0){
            checkFileOpen = 1;

            // Using a DO-WHILE loop until 0 is heard which terminates the loop.
            do {
                printf("-------------------------\n");
                printf("EDIT CONTACT (%s)\n",contacts.name);
                printf("-------------------------\n");
                printf("What do you want to edit ?\n");
                printf("1. Name\n");
                printf("2. Phone Number\n");
                printf("3. Address\n");
                printf("4. Email\n");
                printf("0. EXIT\n");

                //Reading user input.
                printf("Enter the number corresponding to the option: ");
                scanf("%d", &inputNum);

                //Creating switch statements.
                switch (inputNum) {
                    case 1:
                        printf("Enter New Name: "); fflush(stdin); gets(contacts.name);
                        printf("\n-----SUCCESSFUL-----\n");
                    break;
                    case 2:
                        printf("Enter Number: "); fflush(stdin); gets(contacts.phoneNum);
                        printf("\n-----SUCCESSFUL-----\n");
                    break;
                    case 3:
                        printf("Enter Address: "); fflush(stdin); gets(contacts.address);
                        printf("\n-----SUCCESSFUL-----\n");
                    break;
                    case 4:
                        printf("Enter Email: "); fflush(stdin); gets(contacts.email);
                        printf("\n-----SUCCESSFUL-----\n");
                    break;
                    case 0:
                        fprintf(newRecord,"%s  %s  %s  %s\n",contacts.name,contacts.phoneNum,contacts.address,contacts.email);
                        printf("----DATA SAVED SUCCESSFULLY----");
                    break;
                }
            }while(inputNum!=0);
        }
        else {
            //If no input is heard it will reset the data to default.
            fprintf(newRecord,"%s  %s  %s  %s\n",contacts.name,contacts.phoneNum,contacts.address,contacts.email);
        }
    }

    // Checking if the ile was opened or not.
    // If it wasn't that mean no data was found.
    if(checkFileOpen==0) {
        printf("-------------------------\n");
        printf("EDIT CONTACT (ERROR)\n");
        printf("-------------------------\n");
        printf("Name not found.\n\n");
    }

    // Closing the file fp and newRecord.
    // Then removing CONTACT.TXT file and renaming the TEMP.TXT file to CONTACT.TXT.
    fclose(fp);
    fclose(newRecord);
    remove("contact.txt");
    rename("temp.txt","contact.txt");

    printf("\nPress any key to continue...\n");
    getchar();
}


// Creating a function to search the data.
void searchContact() {
    int checkFileOpen =0;
    //Opening the CONTACT.TXT file in read mode
    FILE *fp = fopen("contact.txt", "r");

    printf("-------------------------\n");
    printf("SEARCH CONTACT\n");
    printf("-------------------------\n");
    //Taking user input.
    printf("Enter Name: "); fflush(stdin); gets(editContacts.name);

    /* Using fscanf to read the data from CONTACT.TXT file as it is in read mode only.
     * Executing file until the end of file is reached
     * EOF = End Of File
     * using strcmp to compare the USER GIVEN DATA that we took before with the NAMES of Contacts in the CONTACT.TXT file.
     * Print the data if it matched.
     */
    while(fscanf(fp,"%s  %s  %s  %s\n",contacts.name,contacts.phoneNum,contacts.address,contacts.email)!=EOF) {
        if(strcmp(editContacts.name, contacts.name)==0) {
            checkFileOpen = 1;
            printf("\nName         : %s\n",contacts.name);
            printf("Phone Number : %s\n",contacts.phoneNum);
            printf("Address      : %s\n",contacts.address);
            printf("Email        : %s\n\n",contacts.email);
        }
    }

    // If the file was not opened that means the data was not found in file.
    if(checkFileOpen==0) {
        printf("\n-------------------------\n");
        printf("SEARCH CONTACT (ERROR)\n");
        printf("-------------------------\n");
        printf("Name not found.\n\n");
    }

    printf("\nPress any key to continue...\n");
    getchar();
}