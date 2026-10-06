#include <stdio.h>
#include <string.h>

#define MAX 50

// Structure for one ticket
struct Ticket
{
    int ticketNo;
    char customerName[50];
    char movieName[50];
    int seatNo;
};

// Queue
struct Ticket queue[MAX];
int front = -1;
int rear = -1;

// Stack
struct Ticket stack[MAX];
int top = -1;


// ------------------------------------------------
// BOOK TICKET
// ------------------------------------------------
   void bookTicket()
{
    int n;
    int i;
    char customerName[50];
    char movieName[50];

    printf("\nEnter Customer Name: ");
    scanf(" %[^\n]", customerName);

    printf("Enter Movie Name: ");
    scanf(" %[^\n]", movieName);

    printf("How many tickets do you want to book? ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of tickets.\n");
        return;
    }

    if (rear + n >= MAX)
    {
        printf("Not enough space for these tickets.\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        if (front == -1)
        {
            front = 0;
        }

        rear++;

        strcpy(queue[rear].customerName, customerName);
        strcpy(queue[rear].movieName, movieName);

        printf("\nTicket %d\n", i + 1);

        printf("Enter Ticket Number: ");
        scanf("%d", &queue[rear].ticketNo);

        printf("Enter Seat Number: ");
        scanf("%d", &queue[rear].seatNo);
    }

    printf("\n%d ticket(s) booked successfully!\n", n);
}


// ------------------------------------------------
// CANCEL TICKET
// ------------------------------------------------
void cancelTicket()
{
    int ticketNo;
    int i, j;
    int found = 0;

    if (front == -1 || front > rear)
    {
        printf("\nNo pending bookings.\n");
        return;
    }

    printf("\nEnter Ticket Number to Cancel: ");
    scanf("%d", &ticketNo);

    // Search ticket
    for (i = front; i <= rear; i++)
    {
        if (queue[i].ticketNo == ticketNo)
        {
            found = 1;

            // Push cancelled ticket into Stack
            if (top < MAX - 1)
            {
                top++;
                stack[top] = queue[i];
            }

            // Shift remaining tickets
            for (j = i; j < rear; j++)
            {
                queue[j] = queue[j + 1];
            }

            rear--;

            // If queue becomes empty
            if (rear < front)
            {
                front = -1;
                rear = -1;
            }

            printf("\nTicket %d cancelled successfully.\n",
                   ticketNo);

            break;
        }
    }

    if (found == 0)
    {
        printf("\nTicket %d not found in pending bookings.\n",
               ticketNo);
    }
}


// ------------------------------------------------
// SHOW LAST CANCELLATION
// ------------------------------------------------
void showLastCancellation()
{
    if (top == -1)
    {
        printf("\nNo cancelled tickets.\n");
        return;
    }

    printf("\n===== LAST CANCELLED TICKET =====\n");

    printf("Ticket Number : %d\n", stack[top].ticketNo);
    printf("Customer Name : %s\n", stack[top].customerName);
    printf("Movie Name    : %s\n", stack[top].movieName);
    printf("Seat Number   : %d\n", stack[top].seatNo);
}


// ------------------------------------------------
// DISPLAY PENDING BOOKINGS
// ------------------------------------------------
void displayBookings()
{
    int i;

    if (front == -1 || front > rear)
    {
        printf("\nNo pending bookings.\n");
        return;
    }

    printf("\n========== PENDING BOOKINGS ==========\n");

    for (i = front; i <= rear; i++)
    {
        printf("\nTicket Number : %d",
               queue[i].ticketNo);

        printf("\nCustomer Name : %s",
               queue[i].customerName);

        printf("\nMovie Name    : %s",
               queue[i].movieName);

        printf("\nSeat Number   : %d\n",
               queue[i].seatNo);

        printf("--------------------------------------\n");
    }
}


// ------------------------------------------------
// MAIN FUNCTION
// ------------------------------------------------
int main()
{
    int choice;

    while (1)
    {
        printf("\n========================================\n");
        printf("     ONLINE TICKET BOOKING SYSTEM\n");
        printf("========================================\n");

        printf("1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. Show Last Cancellation\n");
        printf("4. Display current Bookings\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                bookTicket();
                break;

            case 2:
                cancelTicket();
                break;

            case 3:
                showLastCancellation();
                break;

            case 4:
                displayBookings();
                break;

            case 5:
                printf("\nThank you for using the system!\n");
                return 0;

            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}
