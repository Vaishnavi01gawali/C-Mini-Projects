#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 40
#define FILE_NAME "bus_data.dat"

/* Passenger Structure */
struct Passenger
{
    int seatNo;
    char name[50];
    int age;
    char gender[10];
    char phone[15];
};

/* Global passenger array */
struct Passenger passengers[MAX_SEATS];

/* Function declarations */
void initializeSeats();
void displaySeats();
void bookTicket();
void searchPassenger();
void cancelTicket();
void displayPassengers();
void saveData();
void loadData();
void menu();


/* Main Function */
int main()
{
    loadData();

    menu();

    return 0;
}


/* Menu Function */
void menu()
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("         BUS RESERVATION SYSTEM\n");
        printf("========================================\n");

        printf("1. Display Bus Seats\n");
        printf("2. Book Ticket\n");
        printf("3. Search Passenger\n");
        printf("4. Cancel Ticket\n");
        printf("5. Display All Passengers\n");
        printf("6. Save Data\n");
        printf("7. Exit\n");

        printf("========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                displaySeats();
                break;

            case 2:
                bookTicket();
                break;

            case 3:
                searchPassenger();
                break;

            case 4:
                cancelTicket();
                break;

            case 5:
                displayPassengers();
                break;

            case 6:
                saveData();
                break;

            case 7:
                saveData();

                printf("\nData saved successfully.\n");
                printf("Thank you for using Bus Reservation System!\n");

                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while(choice != 7);
}


/* Load Data */
void loadData()
{
    FILE *fp;

    fp = fopen(FILE_NAME, "rb");

    if(fp == NULL)
    {
        initializeSeats();
        return;
    }

    fread(passengers,
          sizeof(struct Passenger),
          MAX_SEATS,
          fp);

    fclose(fp);
}


/* Initialize Seats */
void initializeSeats()
{
    int i;

    for(i = 0; i < MAX_SEATS; i++)
    {
        passengers[i].seatNo = i + 1;

        strcpy(passengers[i].name, "");

        passengers[i].age = 0;

        strcpy(passengers[i].gender, "");

        strcpy(passengers[i].phone, "");
    }
}


/* Display Seats */
void displaySeats()
{
    int i;

    printf("\n========== BUS SEAT STATUS ==========\n");

    for(i = 0; i < MAX_SEATS; i++)
    {
        if(strcmp(passengers[i].name, "") == 0)
        {
            printf("Seat %2d : Available\n",
                   passengers[i].seatNo);
        }
        else
        {
            printf("Seat %2d : Booked\n",
                   passengers[i].seatNo);
        }
    }
}


/* Book Ticket */
void bookTicket()
{
    int seatNo;
    int index;

    printf("\n========== BOOK TICKET ==========\n");

    printf("Enter Seat Number (1-%d): ", MAX_SEATS);
    scanf("%d", &seatNo);

    if(seatNo < 1 || seatNo > MAX_SEATS)
    {
        printf("\nInvalid seat number!\n");
        return;
    }

    index = seatNo - 1;

    if(strcmp(passengers[index].name, "") != 0)
    {
        printf("\nSeat %d is already booked!\n",
               seatNo);

        return;
    }

    passengers[index].seatNo = seatNo;

    printf("Enter Passenger Name: ");
    scanf(" %[^\n]", passengers[index].name);

    printf("Enter Age: ");
    scanf("%d", &passengers[index].age);

    if(passengers[index].age <= 0 ||
       passengers[index].age > 120)
    {
        printf("\nInvalid age!\n");

        strcpy(passengers[index].name, "");

        return;
    }

    printf("Enter Gender: ");
    scanf("%9s", passengers[index].gender);

    printf("Enter Phone Number: ");
    scanf("%14s", passengers[index].phone);

    printf("\n================================\n");
    printf("       TICKET BOOKED\n");
    printf("================================\n");

    printf("Seat No : %d\n",
           passengers[index].seatNo);

    printf("Name    : %s\n",
           passengers[index].name);

    printf("Age     : %d\n",
           passengers[index].age);

    printf("Gender  : %s\n",
           passengers[index].gender);

    printf("Phone   : %s\n",
           passengers[index].phone);

    printf("================================\n");

    saveData();
}


/* Search Passenger */
void searchPassenger()
{
    int seatNo;
    int index;

    printf("\n========== SEARCH PASSENGER ==========\n");

    printf("Enter Seat Number: ");
    scanf("%d", &seatNo);

    if(seatNo < 1 || seatNo > MAX_SEATS)
    {
        printf("\nInvalid seat number!\n");
        return;
    }

    index = seatNo - 1;

    if(strcmp(passengers[index].name, "") == 0)
    {
        printf("\nNo passenger found on seat %d.\n",
               seatNo);

        return;
    }

    printf("\nPassenger Found!\n");

    printf("Seat No : %d\n",
           passengers[index].seatNo);

    printf("Name    : %s\n",
           passengers[index].name);

    printf("Age     : %d\n",
           passengers[index].age);

    printf("Gender  : %s\n",
           passengers[index].gender);

    printf("Phone   : %s\n",
           passengers[index].phone);
}


/* Cancel Ticket */
void cancelTicket()
{
    int seatNo;
    int index;

    printf("\n========== CANCEL TICKET ==========\n");

    printf("Enter Seat Number: ");
    scanf("%d", &seatNo);

    if(seatNo < 1 || seatNo > MAX_SEATS)
    {
        printf("\nInvalid seat number!\n");
        return;
    }

    index = seatNo - 1;

    if(strcmp(passengers[index].name, "") == 0)
    {
        printf("\nSeat %d is already available.\n",
               seatNo);

        return;
    }

    printf("\nPassenger Name: %s\n",
           passengers[index].name);

    printf("Are you sure you want to cancel? (1 = Yes, 0 = No): ");

    int confirm;
    scanf("%d", &confirm);

    if(confirm == 1)
    {
        strcpy(passengers[index].name, "");

        passengers[index].age = 0;

        strcpy(passengers[index].gender, "");

        strcpy(passengers[index].phone, "");

        printf("\nTicket cancelled successfully!\n");

        saveData();
    }
    else
    {
        printf("\nCancellation stopped.\n");
    }
}


/* Display All Passengers */
void displayPassengers()
{
    int i;
    int found = 0;

    printf("\n================ PASSENGER LIST ================\n");

    printf("%-8s %-25s %-8s %-10s %-15s\n",
           "Seat",
           "Name",
           "Age",
           "Gender",
           "Phone");

    printf("-----------------------------------------------------------\n");

    for(i = 0; i < MAX_SEATS; i++)
    {
        if(strcmp(passengers[i].name, "") != 0)
        {
            printf("%-8d %-25s %-8d %-10s %-15s\n",
                   passengers[i].seatNo,
                   passengers[i].name,
                   passengers[i].age,
                   passengers[i].gender,
                   passengers[i].phone);

            found = 1;
        }
    }

    if(found == 0)
    {
        printf("\nNo passengers found.\n");
    }

    printf("===========================================================\n");
}


/* Save Data */
void saveData()
{
    FILE *fp;

    fp = fopen(FILE_NAME, "wb");

    if(fp == NULL)
    {
        printf("\nError opening file!\n");
        return;
    }

    fwrite(passengers,
           sizeof(struct Passenger),
           MAX_SEATS,
           fp);

    fclose(fp);
}
