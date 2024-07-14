#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TICKETS 100
#define MAX_MOVIES 10

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

typedef struct {
    char name[50];
    int price;
    char time[20];
} Movie;

typedef struct {
    Movie movie;
    int quantity;
} Ticket;

Movie movies[MAX_MOVIES] = {
    {"Inception", 100, "18:00"},
    {"Interstellar", 120, "20:00"},
    {"The Matrix", 90, "17:00"},
    {"The Dark Knight", 110, "19:00"},
    {"Avatar", 130, "21:00"},
    {"Titanic", 85, "16:00"},
    {"The Godfather", 95, "15:00"},
    {"Pulp Fiction", 105, "18:30"},
    {"Fight Club", 100, "22:00"},
    {"Forrest Gump", 90, "17:30"}
};

Ticket cart[MAX_TICKETS];
int cartSize = 0;

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
        cartSize++;
    }
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
        total += cart[i].movie.price * cart[i].quantity;
    }
    printf(GREEN "Total: %d UAH\n" RESET, total);
}

void payCart() {
    int total = 0;
    for (int i = 0; i < cartSize; i++) {
        total += cart[i].movie.price * cart[i].quantity;
    }
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
    }
    fclose(file);
    printf(GREEN "Cart saved successfully.\n" RESET);
}

void loadCart() {
    FILE *file = fopen("cart.txt", "r");
    if (file == NULL) {
        printf(RED "Error opening file for loading cart.\n" RESET);
        return;
    }
    cartSize = 0;
    while (fscanf(file, "%s %d %d", cart[cartSize].movie.name, &cart[cartSize].movie.price, &cart[cartSize].quantity) != EOF) {
        cartSize++;
    }
    fclose(file);
    printf(GREEN "Cart loaded successfully.\n" RESET);
}

void menu() {
    int choice;
    while (1) {
        printf(GREEN "\nCinema Ticket Service\n" RESET);
        printf(YELLOW "1. List Movies\n" RESET);
        printf(YELLOW "2. Buy Tickets\n" RESET);
        printf(YELLOW "3. View Cart\n" RESET);
        printf(YELLOW "4. Pay Cart\n" RESET);
        printf(YELLOW "5. Save Cart\n" RESET);
        printf(YELLOW "6. Load Cart\n" RESET);
        printf(YELLOW "7. Exit\n" RESET);
        printf("Enter your choice: ");
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
                loadCart();
                break;
            case 7:
                exit(0);
            default:
                printf(RED "Invalid choice!\n" RESET);
        }
    }
}

int main() {
    menu();
    return 0;
}
