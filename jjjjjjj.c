#include <stdio.h>
#include <string.h>
#define MAX_SEATS 20
#define MAX_ROUTES 3

struct Passenger {
    int ticketID;
    char name[30];
    int age;
    char contact[15];
    int seatNo;
    int routeIndex;
};

struct Train {
    char trainName[30];
    char departureTime[10];
    int seats[MAX_SEATS];
};

/* Available Routes */
char routes[MAX_ROUTES][50] = {
    "Dhaka - Chittagong",
    "Dhaka - Comilla",
    "Dhaka - Sylhet"
};

struct Passenger passengers[MAX_SEATS];
struct Train train;
int passengerCount = 0;
int ticketCounter = 1001;

void initializeTrain();
void bookTicket();
void displaySeats();
void cancelTicket();
void searchTrain();
void updatePassenger();
void bookingSummary(int index);

int main() {
    int choice;
    initializeTrain();

    do {
        printf("\n--- Railway Ticket Booking System ---\n");
        printf("           by~~ Mahi & Joy \n\n");

        printf("1. Book New Ticket\n");
        printf("2. Display Available & Booked Seats\n");
        printf("3. Cancel Ticket\n");
        printf("4. Search Train Information\n");
        printf("5. Update Passenger Information\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: bookTicket(); break;
            case 2: displaySeats(); break;
            case 3: cancelTicket(); break;
            case 4: searchTrain(); break;
            case 5: updatePassenger(); break;
            case 0: printf("Thank you for using our system.\nFrom Mahi & Joy\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}

void initializeTrain() {
    strcpy(train.trainName, "Express 101");
    strcpy(train.departureTime, "10:00 AM");

    for (int i = 0; i < MAX_SEATS; i++)
        train.seats[i] = 0;
}

void bookTicket() {
    int seat, routeChoice;

    if (passengerCount >= MAX_SEATS) {
        printf("All seats are booked!\n");
        return;
    }

    /* Route Selection */
    printf("\nAvailable Routes:\n");
    for (int i = 0; i < MAX_ROUTES; i++) {
        printf("%d. %s\n", i + 1, routes[i]);
    }

    printf("Select Route: ");
    scanf("%d", &routeChoice);

    if (routeChoice < 1 || routeChoice > MAX_ROUTES) {
        printf("Invalid route selection!\n");
        return;
    }

    displaySeats();
    printf("Enter seat number to book: ");
    scanf("%d", &seat);

    if (seat < 1 || seat > MAX_SEATS || train.seats[seat - 1] == 1) {
        printf("Invalid or already booked seat!\n");
        return;
    }

    train.seats[seat - 1] = 1;

    passengers[passengerCount].ticketID = ticketCounter++;
    passengers[passengerCount].seatNo = seat;
    passengers[passengerCount].routeIndex = routeChoice - 1;

    printf("Enter passenger name: ");
    scanf(" %[^\n]", passengers[passengerCount].name);
    printf("Enter age: ");
    scanf("%d", &passengers[passengerCount].age);
    printf("Enter contact number: ");
    scanf(" %s", passengers[passengerCount].contact);

    bookingSummary(passengerCount);
    passengerCount++;
}

void displaySeats() {
    printf("\nSeat Status:\n");
    for (int i = 0; i < MAX_SEATS; i++) {
        printf("Seat %d: %s\n", i + 1,
               train.seats[i] ? "Booked" : "Available");
    }
}

void cancelTicket() {
    int id, found = 0;
    printf("Enter Ticket ID to cancel: ");
    scanf("%d", &id);

    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].ticketID == id) {
            train.seats[passengers[i].seatNo - 1] = 0;
            passengers[i] = passengers[passengerCount - 1];
            passengerCount--;
            printf("Ticket cancelled successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Ticket ID not found.\n");
}

void searchTrain() {
    printf("\nTrain Name: %s\n", train.trainName);
    printf("Departure Time: %s\n", train.departureTime);
    printf("Available Routes:\n");

    for (int i = 0; i < MAX_ROUTES; i++) {
        printf("- %s\n", routes[i]);
    }
}

void updatePassenger() {
    int id, found = 0;
    printf("Enter Ticket ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].ticketID == id) {
            printf("Enter new name: ");
            scanf(" %[^\n]", passengers[i].name);
            printf("Enter new age: ");
            scanf("%d", &passengers[i].age);
            printf("Enter new contact: ");
            scanf(" %s", passengers[i].contact);
            printf("Passenger details updated successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Ticket ID not found.\n");
}

void bookingSummary(int index) {
    printf("\n--- Booking Summary ---\n");
    printf("Ticket ID: %d\n", passengers[index].ticketID);
    printf("Passenger Name: %s\n", passengers[index].name);
    printf("Seat Number: %d\n", passengers[index].seatNo);
    printf("Train: %s\n", train.trainName);
    printf("Route: %s\n", routes[passengers[index].routeIndex]);
    printf("Departure: %s\n", train.departureTime);
}
