#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TICKETS 100
#define MAX_MOVIES 10
#define ROWS 5
#define SEATS_PER_ROW 10

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

typedef struct {
    char name[50];
    int price;
    char time[20];
    char description[200];
    int duration; // in minutes
} Movie;

typedef struct {
    Movie movie;
    int quantity;
    char seats[ROWS][SEATS_PER_ROW];
} Ticket;

typedef struct {
    char code[10];
    int discount; // in percentage
} Discount;

Movie movies[MAX_MOVIES] = {
    {"Inception", 100, "18:00", "A mind-bending thriller by Christopher Nolan.", 148},
    {"Interstellar", 120, "20:00", "A journey to save mankind through space and time.", 169},
    {"The Matrix", 90, "17:00", "A computer hacker learns about the true nature of reality.", 136},
    {"The Dark Knight", 110, "19:00", "Batman faces the Joker in a fight for Gotham's soul.", 152},
    {"Avatar", 130, "21:00", "A paraplegic Marine dispatched to the moon Pandora.", 162},
    {"Titanic", 85, "16:00", "A love story unfolds on the ill-fated Titanic.", 195},
    {"The Godfather", 95, "15:00", "The aging patriarch of an organized crime dynasty.", 175},
    {"Pulp Fiction", 105, "18:30", "The lives of two mob hitmen, a boxer, and a pair of robbers.", 154},
    {"Fight Club", 100, "22:00", "An insomniac office worker forms an underground fight club.", 139},
    {"Forrest Gump", 90, "17:30", "The life and times of a man with a low IQ.", 142}
};

Ticket cart[MAX_TICKETS];
int cartSize = 0;

Discount discounts[] = {
    {"SAVE10", 10},
    {"SAVE20", 20},
    {"SAVE30", 30}
};

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int getIntInput() {
    int num;
    while (scanf("%d", &num) != 1) {
        printf(RED "Invalid input. Please enter a valid number: " RESET);
        clearInputBuffer();
    }
    clearInputBuffer();
    return num;
}

void displayMovies() {
    printf(CYAN "\nAvailable Movies:\n" RESET);
    for (int i = 0; i < MAX_MOVIES; i++) {
        printf(CYAN "%d. %s - %d UAH, Time: %s\n" RESET, i + 1, movies[i].name, movies[i].price, movies[i].time);
        printf(CYAN "   Description: %s\n" RESET, movies[i].description);
        printf(CYAN "   Duration: %d minutes\n" RESET, movies[i].duration);
    }
}

void displaySeats(char seats[ROWS][SEATS_PER_ROW]) {
    printf(YELLOW "\nSeat arrangement (0 - available, X - booked):\n" RESET);
    printf("   ");
    for (int i = 0; i < SEATS_PER_ROW; i++) {
        printf("%d ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        printf("%c: ", 'A' + i);
        for (int j = 0; j < SEATS_PER_ROW; j++) {
            printf("%c ", seats[i][j]);
        }
        printf("\n");
    }
}

void chooseSeats(char seats[ROWS][SEATS_PER_ROW], int quantity) {
    char row;
    int seat;
    for (int i = 0; i < quantity; i++) {
        printf("Enter seat (e.g., A1): ");
        scanf(" %c%d", &row, &seat);
        row = toupper(row) - 'A';
        seat -= 1;
        if (row < 0 || row >= ROWS || seat < 0 || seat >= SEATS_PER_ROW || seats[row][seat] == 'X') {
            printf(RED "Invalid seat or seat already booked. Try again.\n" RESET);
            i--;
        } else {
            seats[row][seat] = 'X';
        }
    }
}

void addTicketToCart(Movie movie, int quantity) {
    int found = 0;
    for (int i = 0; i < cartSize; i++) {
        if (strcmp(cart[i].movie.name, movie.name) == 0) {
            cart[i].quantity += quantity;
            found = 1;
            break;
        }
    }
    if (!found) {
        cart[cartSize].movie = movie;
        cart[cartSize].quantity = quantity;
        memset(cart[cartSize].seats, '0', sizeof(cart[cartSize].seats));
        cartSize++;
    }
    chooseSeats(cart[cartSize - 1].seats, quantity);
}

void buyTickets() {
    int choice, quantity;
    displayMovies();
    printf("\nEnter the movie number to buy tickets: ");
    choice = getIntInput();
    if (choice < 1 || choice > MAX_MOVIES) {
        printf(RED "Invalid choice!\n" RESET);
        return;
    }
    printf("Enter the number of tickets: ");
    quantity = getIntInput();
    if (quantity < 1) {
        printf(RED "Invalid quantity!\n" RESET);
        return;
    }
    addTicketToCart(movies[choice - 1], quantity);
    printf(GREEN "Tickets for %s added to cart.\n" RESET, movies[choice - 1].name);
}

void viewCart() {
    printf(GREEN "\nYour Cart:\n" RESET);
    int total = 0;
    for (int i = 0; i < cartSize; i++) {
        printf(GREEN "%d. %s - %d UAH x %d\n" RESET, i + 1, cart[i].movie.name, cart[i].movie.price, cart[i].quantity);
        displaySeats(cart[i].seats);
        total += cart[i].movie.price * cart[i].quantity;
    }
    printf(GREEN "Total: %d UAH\n" RESET, total);
}

void applyDiscount(int *total) {
    char code[10];
    printf("Enter discount code: ");
    scanf("%s", code);
    for (int i = 0; i < sizeof(discounts) / sizeof(Discount); i++) {
        if (strcmp(discounts[i].code, code) == 0) {
            *total = *total * (100 - discounts[i].discount) / 100;
            printf(GREEN "Discount applied! New total: %d UAH\n" RESET, *total);
            return;
        }
    }
    printf(RED "Invalid discount code.\n" RESET);
}

void payCart() {
    int total = 0;
    for (int i = 0; i < cartSize; i++) {
        total += cart[i].movie.price * cart[i].quantity;
    }
    applyDiscount(&total);
    printf(YELLOW "\nTotal amount to pay: %d UAH\n" RESET, total);
    printf("Enter payment amount: ");
    int payment = getIntInput();
    if (payment >= total) {
        printf(GREEN "Payment successful! Change: %d UAH\n" RESET, payment - total);
        cartSize = 0; // Clear the cart after successful payment
    } else {
        printf(RED "Insufficient amount! Payment failed.\n" RESET);
    }
}

void saveCart() {
    FILE *file = fopen("cart.txt", "w");
    if (file == NULL) {
        printf(RED "Error opening file for saving cart.\n" RESET);
        return;
    }
    for (int i = 0; i < cartSize; i++) {
        fprintf(file, "%s %d %d\n", cart[i].movie.name, cart[i].movie.price, cart[i].quantity);
        for (int j = 0; j < ROWS; j++) {
            for (int k = 0; k < SEATS_PER_ROW; k++) {
                fprintf(file, "%c", cart[i].seats[j][k]);
            }
            fprintf(file, "\n");
        }
    }
    fclose(file);
    printf(GREEN "Cart saved to cart.txt\n" RESET);
}

void loadCart() {
    FILE *file = fopen("cart.txt", "r");
    if (file == NULL) {
        printf(RED "Error opening file for loading cart.\n" RESET);
        return;
    }
    cartSize = 0;
    while (fscanf(file, "%s %d %d", cart[cartSize].movie.name, &cart[cartSize].movie.price, &cart[cartSize].quantity) != EOF) {
        for (int j = 0; j < ROWS; j++) {
            for (int k = 0; k < SEATS_PER_ROW; k++) {
                fscanf(file, " %c", &cart[cartSize].seats[j][k]);
            }
        }
        cartSize++;
    }
    fclose(file);
    printf(GREEN "Cart loaded from cart.txt\n" RESET);
}

void menu() {
    int choice;
    loadCart();
    do {
        printf(CYAN "\nCinema Ticket Purchase Service\n" RESET);
        printf("1. List of Movies\n");
        printf("2. Buy Tickets\n");
        printf("3. View Cart\n");
        printf("4. Pay Cart\n");
        printf("5. Save Cart\n");
        printf("6. Exit\n");
        printf("\nEnter your choice: ");
        choice = getIntInput();
        switch (choice) {
            case 1:
                displayMovies();
                break;
            case 2:
                buyTickets();
                break;
            case 3:
                viewCart();
                break;
            case 4:
                payCart();
                break;
            case 5:
                saveCart();
                break;
            case 6:
                printf(CYAN "Exiting...\n" RESET);
                break;
            default:
                printf(RED "Invalid choice! Please try again.\n" RESET);
        }
    } while (choice != 6);
}

int main() {
    menu();
    return 0;
}
