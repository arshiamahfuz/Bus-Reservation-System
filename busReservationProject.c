#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define numofBusSeats 40
#define numofBuses 10
#define numofpassengers 2
#define fName "seatInfo.txt"
void userSetup();//Arshia Mahfuz 2522791643
int login(int num);//Arshia Mahfuz 2522791643
void takeInfo();//Arshia Mahfuz 2522791643
void saveInfo();//Arshia Mahfuz 2522791643
void bookSeats();//Arshia Mahfuz 2522791643
void updateBooking();//Arshia Mahfuz 2522791643


void adminMenu();//Najiba Nowar Meethi 2522423642
void passengerMenu();//Najiba Nowar Meethi 2522423642
void addBus();//Najiba Nowar Meethi 2522423642
void viewBuses();//Najiba Nowar Meethi 2522423642
void cancelSeat();//Najiba Nowar Meethi 2522423642
void searchBooking();//Najiba Nowar Meethi 2522423642



struct Bus
 {
    int busID;
    char route[30];
    char time[10];
    char seats[numofBusSeats][30];
};
struct Bus buses[numofBuses];
int totalBuses = 0;
char adminUser[10], adminPass[10];
struct passenger
{
    char username[10];
    char password[10];

}passenger[numofpassengers];


void userSetup()
{
    printf("Set Admin Username: ");
    scanf("%s", adminUser);
    printf("Set Admin Password: ");
    scanf("%s", adminPass);


    for (int i = 0; i < numofpassengers; i++)

     {
        printf("Set passenger %d Username: ", i+1);
        scanf("%s",passenger[i].username);
        printf("Set passenger %d Password: ", i+1);
        scanf("%s", passenger[i].password);
    }
}


int login(int num)
{
    char usr[10], pass[10];
    printf("User name: ");
    gets(usr);
    printf("Password: ");
    gets(pass);
    if (num == 1)
    {
        if (strcmp(usr, adminUser) == 0 && strcmp(pass, adminPass) == 0)
        {
            printf("Login successful.\n");
            return 1;
        }
    }
    else

    {

        for (int i = 0; i < numofpassengers; i++)
        {
            if (strcmp(usr, passenger[i].username) == 0 &&
                strcmp(pass, passenger[i].password) == 0)

            {
                printf("Login successful.\n");
                return 1;
            }
        }
    }

    printf("Incorrect Password.\n");
    return 0;
}


void takeInfo()
{

      FILE *fp = fopen(fName, "rb");
    if (fp)

    {

        fread(&totalBuses, sizeof(int), 1, fp);
        fread(buses, sizeof(struct Bus), totalBuses, fp);
        fclose(fp);
    }
}


void saveInfo()

{
     FILE *fp = fopen(fName, "wb");
    if (fp)

    {
        fwrite(&totalBuses, sizeof(int), 1, fp);
        fwrite(buses, sizeof(struct Bus), totalBuses, fp);
        fclose(fp);
    }


}

void bookSeats()

{

    int id, seat;
    char name[10];
    printf("Enter Bus ID: ");
    scanf("%d", &id);
    getchar();
    if (id < 1 || id > totalBuses)

    {

        printf("Error\n");
        return;
    }


    printf("Enter Seat Number (1-%d): ",numofBusSeats );
    scanf("%d", &seat);
    getchar();

    if (seat < 1 || seat > numofBusSeats)


     {

        printf("Error Occurs.\n");
        return;


     }
    if (strlen(buses[id-1].seats[seat-1]) > 0)

    {
        printf("Seat has already booked.\n");
        return;
    }


    printf("Enter name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    strcpy(buses[id-1].seats[seat-1], name);
    saveInfo();
    printf(" The seat is booked successfully.\n");
}

void updateBooking()


{

    char name[10];
    printf("Enter passenger name to update: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    for (int i = 0; i < totalBuses; i++)

    {

        for (int j = 0; j < numofBusSeats; j++)


        {
            if (strcmp(buses[i].seats[j], name) == 0)

            {
                char newName[30];
                printf("Enter new name: ");
                fgets(newName, sizeof(newName), stdin);
                newName[strcspn(newName, "\n")] = '\0';
                strcpy(buses[i].seats[j], newName);
                saveInfo();
                printf("Booking updated.\n");
                return;
            }
        }
    }
    printf("Booking not found.\n");
}




void adminMenu()

{
    int n;
    while (1)


    {
        printf("\n=== Admin Menu ===\n");
        printf("1. View Buses\n");
        printf("2. Add New Bus\n");
        printf("3. Search Bookings\n");
        printf("4. Update Bookings\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &n);
        getchar();

        if (n == 1)

            viewBuses();

        else if (n == 2)

            addBus();

        else if (n == 3)

            searchBooking();

        else if (n == 4)

            updateBooking();

        else if (n == 5)

            break;

        else

            printf("Error. Invalid choice.\n");

    }
}

void passengerMenu()

{
    int n;
    while (1)

    {
        printf("\n=== Customer Menu ===\n");
        printf("1. View Bus Details\n");
        printf("2. Book a Seat\n");
        printf("3. Cancel Booking\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &n);
        getchar();

        if (n == 1)

         viewBuses();

        else if (n == 2)

         bookSeats();

        else if (n == 3)

         cancelSeat();

        else if (n == 4)

         break;

        else

         printf("Error. Invalid choice.\n");
    }
}

void addBus()

{
    if (totalBuses >= numofBuses)


    {
        printf("Cannot add new bus.\n");
        return;
    }
    struct Bus b;
    b.busID = totalBuses + 1;
    printf("Enter route: ");
    fgets(b.route, sizeof(b.route), stdin);
    b.route[strcspn(b.route, "\n")] = '\0';
    printf("Enter time: ");
    fgets(b.time, sizeof(b.time), stdin);
    b.time[strcspn(b.time, "\n")] = '\0';

    for (int i = 0; i < numofBusSeats; i++)
        strcpy(b.seats[i], "");

    buses[totalBuses++] = b;
    saveInfo();
    printf("Bus added successfully.\n");
}

void viewBuses()
{
    if (totalBuses == 0)
    {
        printf("No bus is available.\n");
        return;
    }

    for (int i = 0; i < totalBuses; i++)
    {
        printf("\nBus ID: %d\n", buses[i].busID);
        printf("Route: %s\n", buses[i].route);
        printf("Departure: %s\n", buses[i].time);
        printf("Seats:\n");

        for (int j = 0; j < numofBusSeats; j++)
        {
            if (strlen(buses[i].seats[j]) > 0)
                printf("%2d:%-10s", j + 1, buses[i].seats[j]);
            else
                printf("%2d:%-10s", j + 1, "Empty");

            if ((j + 1) % 5 == 0)
                printf("\n");
        }
        printf("\n");
    }
}


void cancelSeat()


{
    int id, seat;
    printf("Enter Bus ID: ");
    scanf("%d", &id);
    getchar();
    if (id < 1 || id > totalBuses)


    {
        printf("Bus with Bus ID %d not found.\n", id);
        return;
    }
    printf("Enter Seat Number to cancel: ");
    scanf("%d", &seat);
    getchar();
    if (seat < 1 || seat > numofBusSeats)

    {
        printf("Invalid seat number\n", seat);
        return;
    }
    if (strlen(buses[id-1].seats[seat-1]) == 0)

    {
        printf("Seat is already empty.\n");
        return;
    }
    strcpy(buses[id-1].seats[seat-1], "");
    saveInfo();
    printf("Cancellation successful. %d seats canceled on Bus %d.\n", seat, id);
}

void searchBooking()
{
    char name[30];
    printf("Enter passenger name to: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    for (int i = 0; i < totalBuses; i++)


    {
        for (int j = 0; j < numofBusSeats; j++)

        {
            if (strcmp(buses[i].seats[j], name) == 0)

            {
                printf("%s \nBus : %d\nSeat %d\n", name, buses[i].busID, j+1);
                return;
            }
        }
    }
    printf("No booking found for %s.\n", name);
}





int main()
{
    userSetup();
    takeInfo();
    int type;
   while(1)


    {
        printf("\n***** Bus Reservation And Management System *****\n");
        printf("1. Admin Login\n");
        printf("2. Passenger  Login\n");
        printf("3. Exit\n");
        printf("Enter a type: ");
        scanf("%d", &type);
        getchar();

        if(type == 1)

        {
            if(login(1))

             adminMenu();
        }

           else if(type == 2)

        {

            if(login(2))

            passengerMenu();

        }


        else if(type == 3)

        {
            saveInfo();
            printf("Exiting...\n");
            break;
        }

        else

        {
            printf("Error.\n");
        }
    }

}
