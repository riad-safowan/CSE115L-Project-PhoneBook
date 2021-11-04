/*
Name: Riad Safowan
ID: 211****642
*/

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include <ctype.h>

#define LIMIT 1000

typedef struct Contact
{
    int serial_no;
    char first_name[20];
    char last_name[20];
    char number[20];
    char address[20];

} Contact;

void header(); //clears screen and prints header.
int getSize(); //reads the file the returns the number of contacts.
void sortContact(Contact contacts[], int size); //sorts the array alphabetically
void setContacts(Contact contacts[], int size); //updates the file.
void getContacts(Contact contacts[], int size); //reads the file and fill the array.
void printContacts(Contact contacts[], int size); //prints array to console.

void menu(Contact contacts[], int *size);
void showContact(Contact contacts[], int *size);
void addContact(Contact contacts[], int *size);
void deleteContact(Contact contacts[], int *size);
void editContact(Contact contacts[], int *size);
void searchContact(Contact contacts[], int *size);

int main(void)
{
    Contact contacts[LIMIT]; //array of contacts
    int *size, S;
    size = &S;
    *size = getSize(); //number of record in file
    getContacts(contacts, *size);

    menu(contacts, size);

    return 0;
}

void menu(Contact contacts[], int *size )
{
    do
    {
        header();
        printf("\tMain Menu: \n\n");
        getContacts(contacts, *size);

        printf("\t1 -> See all Contacts\n");
        printf("\t2 -> Add a new Contact\n");
        printf("\t3 -> Delete a Contact\n");
        printf("\t4 -> Edit a Contact\n");
        printf("\t5 -> Search Contacts\n");
        printf("\t0 -> Exit\n");

        printf("\n\tSelect an option: ");
        char op = getch(); //op to get store the character

        while(op < '0' || op > '5')
        {
            printf("\n\tEnter a value between 1-5 : ");
            op = getch();
        }

        switch(op)
        {
        case '1':
            showContact(contacts, size);
            break;

        case '2':
            addContact(contacts, size);
            break;

        case '3':
            deleteContact(contacts, size);
            break;

        case '4':
            editContact(contacts, size);
            break;

        case '5':
            searchContact(contacts, size);
            break;

        case '0':
            header();
            printf("\n\n\tApplication Closed!\n\n\n");
            exit(0); // exit the app
            break;
        }
    }
    while(1);

}

void showContact(Contact contacts[], int *size)
{
    header();
    printf("All Contacts:-\n\n");
    *size = getSize(); //updating current number of record in file.
    getContacts(contacts, *size);
    setContacts(contacts, *size);
    printContacts(contacts, *size);
    printf("\nPress any key to get menu_");
    getch();
    return;
}

void addContact(Contact contacts[], int *size)
{
    header();
    printf("Add a new Contact:-\n\n");

    //check if there is a room for new contact or not.
    if(*size >= LIMIT)
    {
        printf("\tContact list is already full !\n\n");
        printf("\nPress any key to get menu_");
        getch();
        return;
    }

    contacts[*size].serial_no = *size+1;
    int isExist = 0;
    char name[40];
    char name2[40];

    //check if the name already exists or not , and take name.
    do
    {
        isExist = 0;

        printf("\tEnter First Name (0 to cancel): ");
        scanf("%s",contacts[*size].first_name);

        if(contacts[*size].first_name[0] == '0' && contacts[*size].first_name[1] == '\0')
        {
            return;
        }

        printf("\tEnter Last Name: ");
        scanf("%s",contacts[*size].last_name);

        // concatenate first name and last name to get name
        strcpy(name,contacts[*size].first_name);
        strcat(name," ");
        strcat(name,contacts[*size].last_name);

        for(int i = 0; i < *size; i++)
        {
            // concatenate first name and last name to get name
            strcpy(name2, contacts[i].first_name);
            strcat(name2, " ");
            strcat(name2, contacts[i].last_name);

            if(strcmp(name, name2) == 0)
            {
                isExist = 1;
                printf("\t\nThe Name already exist !\n\n");
            }
        }
    }
    while(isExist);

    int flag;
    do
    {
        flag = 1;
        printf("\tEnter Phone Number: ");
        scanf("%s",contacts[*size].number);

        //check if the number is valid or not.
        for(int i = 0; i < strlen(contacts[*size].number); i++)
        {
            if((contacts[*size].number[i]  <= 47) || (contacts[*size].number[i] >= 58))
            {
                printf("\tPlease enter a valid phone number\n");
                flag = 0;
                break;
            }
        }
    }
    while(flag == 0);

    printf("\tEnter Address: ");
    scanf("%s",contacts[*size].address);

    // size increased by one for new contact.
    *size = *size+1;

    // update new array to File.
    setContacts(contacts, *size);
    printf("\n\tNew Contact Saved !\n");
    printf("\nPress any key to get menu_ ");
    getch();
    return;
}

void deleteContact(Contact contacts[], int *size)
{
    header();
    printf("Delete a contact:-\n\n");
    printContacts(contacts, *size);

    //check if the list is empty or not.
    if(*size == 0)
    {
        printf("\nPress any key to get menu_");
        getch();
        return;
    }
    else
    {
        int x;
        do
        {
            printf("\nSelect a serial no. to delete (0 to back , -1 to delete all): ");

            scanf("%d", &x);
            fflush(stdin);
            if(x == 0) // 0 to back
            {
                return;
            }
            else if( x >= 1 && x <= *size) //selecting a valid contact to delete.
            {

                int position = x-1;
                getContacts(contacts, *size);

                char name[40];
                //getting the name of the contact being deleted.
                strcpy(name, contacts[position].first_name);
                strcat(name, " ");
                strcat(name, contacts[position].last_name);

                // shifting contacts from position x to (x-1).
                for(int i = position; i < * size-1; i++)
                {
                    contacts[i]=contacts[i+1];
                }

                // size decreased by one because of deleting a contact.
                *size = *size-1;

                //update file with updated array.
                setContacts(contacts, *size);
                header();

                printf("\t%s has been deleted !\n\n",name); //show name of the contact who is deleted.
                printf("All Contacts:-\n\n");

                //show new contact list.
                getContacts(contacts, *size);
                printContacts(contacts, *size);

                printf("\nPress any key to get menu_ ");
                getch();
                return;
            }
            else if(x = -1)  // to delete all.
            {
                // set size = 0, because the list should be empty.
                *size = 0;
                //file will be updated with 0 contact.
                setContacts(contacts, *size);
                header();

                printf("All contacts have been deleted !\n\n");

                getContacts(contacts,*size);
                printContacts(contacts, *size);

                printf("\nPress any key to get menu_ ");
                getch();
                return;
            }
            else
            {
                printf("\tValid option 0 - %d",*size);
            }
        }
        while(x != 0);
    }
}

void editContact(Contact contacts[], int *size)
{
    header();
    printf("Edit a contact:-\n\n");
    printContacts(contacts, *size);

    //check if the list is empty or not.
    if(*size == 0)
    {
        printf("\nPress any key to get menu_");
        getch();
        return;
    }
    else
    {
        int x;
        do
        {
            printf("\nSelect a serial no. to edit (0 to back): ");

            scanf("%d", &x);
            fflush(stdin);
            if(x == 0) // to go back.
            {
                return;
            }
            else if(x >= 1 && x <= *size) //selecting a valid contact to edit.
            {
                getContacts(contacts, *size);
                int position = x-1;

                //getting contacts old name.
                char name[40];
                strcpy(name, contacts[position].first_name);
                strcat(name, " ");
                strcat(name, contacts[position].last_name);


                //take the new name and check that if the name is already exist or not.
                int isExist = 0;
                char name2[40];
                char name3[40];
                do
                {
                    isExist = 0;

                    printf("\tEnter First Name : ");
                    scanf("%s",contacts[position].first_name);

                    printf("\tEnter Last Name: ");
                    scanf("%s",contacts[position].last_name);

                    // concatenate first name and last name to get name
                    strcpy(name2,contacts[position].first_name);
                    strcat(name2," ");
                    strcat(name2,contacts[position].last_name);

                    for(int i = 0; i < *size; i++)
                    {
                        //searching through all contacts except the one that is being edited.
                        if(i != position )
                        {
                            // concatenate first name and last name to get name
                            strcpy(name3, contacts[i].first_name);
                            strcat(name3, " ");
                            strcat(name3, contacts[i].last_name);

                            if(strcmp(name2, name3) == 0)
                            {
                                isExist = 1;
                                printf("\t\nThe Name already exist !\n\n");
                            }
                        }

                    }
                }
                while(isExist);

                //check and input a valid number.
                int flag;
                do
                {
                    flag = 1;
                    printf("\tEnter Phone Number: ");
                    scanf("%s",contacts[position].number);
                    for(int i = 0; i < strlen(contacts[position].number); i++)
                    {
                        if((contacts[position].number[i]  < '0') || (contacts[position].number[i] > '9'))
                        {
                            printf("\tEnter valid phone number\n");
                            flag = 0;
                            break;
                        }
                    }
                }
                while(flag == 0);

                printf("\tEnter Address: ");
                scanf("%s",contacts[position].address);

                //update new list to file.
                setContacts(contacts, *size);
                header();

                printf("\t%s has been edited !\n\n", name);
                printf("\tAll Contacts\n\n");

                // showing new contact list
                printContacts(contacts, *size);

                printf("\nPress any key to get menu_");
                getch();
                return;
            }
            else
            {
                printf("\tValid option 0 - %d", *size);
            }
        }
        while(x != 0);
    }
}

void searchContact(Contact contacts[], int *size)
{
    header();
    printf("Search Contacts:-\n\n");

    //check if the list is empty or not.
    if(*size == 0)
    {
        printContacts(contacts, *size);
        printf("\nPress any key to get menu_");
        getch();
        return;
    }


    //input is the text of the search box. record holds the total info of a contact as a string.
    char input[40], record[80];
    Contact search[100];
    printf("Enter Name or Phone Number or Address (0 to back): ");
    gets(input);

    // 0 to back
    if(input[0] == '0' && input[1] == '\0')
    {
        return;
    }

    // to do nothing if user enters no text or only space.
    else if(input[0] == '\0' || (input[0] == ' ' && input[1] == '\0'))
    {
        searchContact(contacts, size);
        return;
    }

    //to make our search non-case sensitive convert input text to lower case
    int count = 0;
    char ch;
    while (input[count])
    {
        ch = input[count];
        input[count] = tolower(ch);
        count++;
    }

    int z = 0;
    int found = 0;

    for(int i = 0; i<*size; i++ )
    {
        strcpy(record, contacts[i].first_name);
        strcat(record, " ");
        strcat(record, contacts[i].last_name);
        strcat(record, contacts[i].number);
        strcat(record, contacts[i].address);

        //to make our search non-case sensitive convert record text to lower case
        int count2 = 0;
        char ch2;
        while (record[count2])
        {
            ch2 = record[count2];
            record[count2] = tolower(ch2);
            count2++;
        }

        char *result;
        //result is not null if found.
        result = strstr(record, input);

        if(result != NULL)
        {
            found = 1;

            search[z].serial_no = contacts[i].serial_no;
            strcpy(search[z].first_name, contacts[i].first_name);
            strcpy(search[z].last_name, contacts[i].last_name);
            strcpy(search[z].number, contacts[i].number);
            strcpy(search[z++].address, contacts[i].address);
        }
    }
    if(!found)
    {
        printf("\n\tNo match found !\n");
    }
    else
    {
        printf("\t\n");
        printContacts(search, z);
    }

    printf("\nPress any key to get menu_");
    getch();
    menu(contacts,size);
}

void header()
{
    //clear the screen.
    system("cls");
    //print header.
    printf("============================ PHONEBOOK ============================         [ Developed by Riad Safowan ID:2112312642 ]\n\n");
}

int getSize()
{
    Contact contacts;
    //open file.
    FILE* file = fopen("contacts.txt", "r");

    //if file is not available then create a new file with the name.
    if(file==NULL)
    {
        file = fopen("contacts.txt", "w");
        fclose(file);

        //returns the size 0 because the file is newly created.
        return 0;
    }
    else
    {
        int input_status, n=-1;
        do
        {
            //go through the file and read all record
            input_status = fscanf(file, "%d %s %s %s %s",&contacts.serial_no, &contacts.first_name, &contacts.last_name, &contacts.number, &contacts.address);
            n++;
        }
        while (input_status != EOF);

        return n;
    }
}

void printContacts(Contact contacts[], int size)
{
    if(size == 0)
    {
        printf("\tContact list empty !\n");
    }
    else
    {
        printf("Serial no.  Name\t\t Phone Number    Address\n\n");

        for(int j = 0; j < size; j++)
        {
            char name[40];
            strcpy(name, contacts[j].first_name);
            strcat(name, " ");
            strcat(name, contacts[j].last_name);
            printf("\t%-3d %-20s %-15s %s\n",contacts[j].serial_no, name, contacts[j].number, contacts[j].address);
        }
    }
}

void getContacts(Contact contacts[], int size)
{
    FILE* output = fopen("contacts.txt", "r");

    for(int i = 0; i<size; i++)
    {
        fscanf(output, "%d %s %s %s %s",&contacts[i].serial_no, contacts[i].first_name, contacts[i].last_name, contacts[i].number, contacts[i].address);
    }
    fclose(output);
}

void setContacts(Contact contacts[], int size)
{
    //sort the array alphabetically the save to file.
    FILE* input = fopen("contacts.txt", "w");
    sortContact(contacts, size);
    for(int i = 0; i < size; i++)
    {
        fprintf(input, "%d %s %s %s %s\n",contacts[i].serial_no, contacts[i].first_name, contacts[i].last_name, contacts[i].number, contacts[i].address);
    }
    fclose(input);
}

void sortContact(Contact contacts[], int size)
{
    //sorting technique : find the smallest one then swap it.
    int position;
    char name[40];
    for(int i = 0; i < size; i++)
    {
        position = i;
        strcpy(name, contacts[i].first_name);
        strcat(name, contacts[i].last_name);

        for(int j = i; j < size; j++)
        {
            char name2[40];
            strcpy(name2, contacts[j].first_name);
            strcat(name2, contacts[j].last_name);

            if(strcmp(name, name2) > 0)
            {
                position = j;
            }
        }

        if(position != i)
        {
            Contact temp;
            temp = contacts[i];
            contacts[i] = contacts[position];
            contacts[position] = temp;
        }
        contacts[i].serial_no = i+1;
    }
}



