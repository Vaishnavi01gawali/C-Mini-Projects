#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "contacts.dat"

/* Structure for Contact */
struct Contact
{
    char name[50];
    char phone[15];
    char email[50];

    struct Contact *next;
};

/* Head pointer */
struct Contact *head = NULL;


/* Function declarations */
void addContact();
void displayContacts();
void searchContact();
void updateContact();
void deleteContact();
void sortContacts();
void saveContacts();
void loadContacts();
void freeContacts();
void menu();


/* Main Function */
int main()
{
    loadContacts();

    menu();

    freeContacts();

    return 0;
}


/* Menu */
void menu()
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("       CONTACT MANAGEMENT SYSTEM\n");
        printf("========================================\n");

        printf("1. Add Contact\n");
        printf("2. Display All Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Update Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Sort Contacts by Name\n");
        printf("7. Save Contacts\n");
        printf("8. Exit\n");

        printf("========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addContact();
                break;

            case 2:
                displayContacts();
                break;

            case 3:
                searchContact();
                break;

            case 4:
                updateContact();
                break;

            case 5:
                deleteContact();
                break;

            case 6:
                sortContacts();
                break;

            case 7:
                saveContacts();
                break;

            case 8:
                saveContacts();

                printf("\nContacts saved successfully.\n");
                printf("Thank you for using Contact Management System!\n");

                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while(choice != 8);
}


/* Add Contact */
void addContact()
{
    struct Contact *newContact;
    struct Contact *temp;

    newContact = (struct Contact *)malloc(sizeof(struct Contact));

    if(newContact == NULL)
    {
        printf("\nMemory allocation failed!\n");
        return;
    }

    printf("\n========== ADD CONTACT ==========\n");

    printf("Enter Name: ");
    scanf(" %[^\n]", newContact->name);

    printf("Enter Phone Number: ");
    scanf("%14s", newContact->phone);

    printf("Enter Email: ");
    scanf("%49s", newContact->email);

    newContact->next = NULL;

    /* First contact */
    if(head == NULL)
    {
        head = newContact;
    }
    else
    {
        temp = head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newContact;
    }

    printf("\nContact added successfully!\n");
}


/* Display Contacts */
void displayContacts()
{
    struct Contact *temp;
    int count = 0;

    if(head == NULL)
    {
        printf("\nNo contacts available.\n");
        return;
    }

    temp = head;

    printf("\n================ CONTACT LIST ================\n");

    printf("%-25s %-15s %-30s\n",
           "Name",
           "Phone",
           "Email");

    printf("--------------------------------------------------------------\n");

    while(temp != NULL)
    {
        printf("%-25s %-15s %-30s\n",
               temp->name,
               temp->phone,
               temp->email);

        temp = temp->next;

        count++;
    }

    printf("--------------------------------------------------------------\n");
    printf("Total Contacts: %d\n", count);
}


/* Search Contact */
void searchContact()
{
    struct Contact *temp;

    char searchName[50];

    int found = 0;

    if(head == NULL)
    {
        printf("\nNo contacts available.\n");
        return;
    }

    printf("\n========== SEARCH CONTACT ==========\n");

    printf("Enter name to search: ");
    scanf(" %[^\n]", searchName);

    temp = head;

    while(temp != NULL)
    {
        if(strcmp(temp->name, searchName) == 0)
        {
            printf("\nContact Found!\n");

            printf("Name  : %s\n", temp->name);
            printf("Phone : %s\n", temp->phone);
            printf("Email : %s\n", temp->email);

            found = 1;

            break;
        }

        temp = temp->next;
    }

    if(found == 0)
    {
        printf("\nContact not found!\n");
    }
}


/* Update Contact */
void updateContact()
{
    struct Contact *temp;

    char searchName[50];

    int found = 0;

    if(head == NULL)
    {
        printf("\nNo contacts available.\n");
        return;
    }

    printf("\n========== UPDATE CONTACT ==========\n");

    printf("Enter name to update: ");
    scanf(" %[^\n]", searchName);

    temp = head;

    while(temp != NULL)
    {
        if(strcmp(temp->name, searchName) == 0)
        {
            printf("\nContact Found!\n");

            printf("Enter New Name: ");
            scanf(" %[^\n]", temp->name);

            printf("Enter New Phone Number: ");
            scanf("%14s", temp->phone);

            printf("Enter New Email: ");
            scanf("%49s", temp->email);

            printf("\nContact updated successfully!\n");

            found = 1;

            break;
        }

        temp = temp->next;
    }

    if(found == 0)
    {
        printf("\nContact not found!\n");
    }
}


/* Delete Contact */
void deleteContact()
{
    struct Contact *temp;
    struct Contact *previous;

    char searchName[50];

    if(head == NULL)
    {
        printf("\nNo contacts available.\n");
        return;
    }

    printf("\n========== DELETE CONTACT ==========\n");

    printf("Enter name to delete: ");
    scanf(" %[^\n]", searchName);


    /* If first node needs to be deleted */
    if(strcmp(head->name, searchName) == 0)
    {
        temp = head;

        head = head->next;

        free(temp);

        printf("\nContact deleted successfully!\n");

        return;
    }


    previous = head;
    temp = head->next;

    while(temp != NULL)
    {
        if(strcmp(temp->name, searchName) == 0)
        {
            previous->next = temp->next;

            free(temp);

            printf("\nContact deleted successfully!\n");

            return;
        }

        previous = temp;
        temp = temp->next;
    }

    printf("\nContact not found!\n");
}


/* Sort Contacts by Name */
void sortContacts()
{
    struct Contact *i;
    struct Contact *j;

    char tempName[50];
    char tempPhone[15];
    char tempEmail[50];

    if(head == NULL || head->next == NULL)
    {
        printf("\nNot enough contacts to sort.\n");
        return;
    }

    for(i = head; i != NULL; i = i->next)
    {
        for(j = i->next; j != NULL; j = j->next)
        {
            if(strcmp(i->name, j->name) > 0)
            {
                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);

                strcpy(tempPhone, i->phone);
                strcpy(i->phone, j->phone);
                strcpy(j->phone, tempPhone);

                strcpy(tempEmail, i->email);
                strcpy(i->email, j->email);
                strcpy(j->email, tempEmail);
            }
        }
    }

    printf("\nContacts sorted alphabetically.\n");

    displayContacts();
}


/* Save Contacts to File */
void saveContacts()
{
    FILE *fp;

    struct Contact *temp;

    fp = fopen(FILE_NAME, "wb");

    if(fp == NULL)
    {
        printf("\nError opening file!\n");
        return;
    }

    temp = head;

    while(temp != NULL)
    {
        fwrite(temp->name,
               sizeof(char),
               sizeof(temp->name),
               fp);

        fwrite(temp->phone,
               sizeof(char),
               sizeof(temp->phone),
               fp);

        fwrite(temp->email,
               sizeof(char),
               sizeof(temp->email),
               fp);

        temp = temp->next;
    }

    fclose(fp);
}


/* Load Contacts from File */
void loadContacts()
{
    FILE *fp;

    struct Contact *newContact;
    struct Contact *temp;

    fp = fopen(FILE_NAME, "rb");

    if(fp == NULL)
    {
        return;
    }

    while(1)
    {
        newContact = (struct Contact *)malloc(sizeof(struct Contact));

        if(newContact == NULL)
        {
            printf("\nMemory allocation failed!\n");

            fclose(fp);

            return;
        }

        if(fread(newContact->name,
                 sizeof(char),
                 sizeof(newContact->name),
                 fp) != sizeof(newContact->name))
        {
            free(newContact);
            break;
        }

        fread(newContact->phone,
              sizeof(char),
              sizeof(newContact->phone),
              fp);

        fread(newContact->email,
              sizeof(char),
              sizeof(newContact->email),
              fp);

        newContact->next = NULL;

        if(head == NULL)
        {
            head = newContact;
        }
        else
        {
            temp = head;

            while(temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = newContact;
        }
    }

    fclose(fp);
}


/* Free Memory */
void freeContacts()
{
    struct Contact *temp;

    while(head != NULL)
    {
        temp = head;

        head = head->next;

        free(temp);
    }
}
