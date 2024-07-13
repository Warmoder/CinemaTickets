#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TICKETS 100
#define MAX_MOVIES 5

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
    {"Avatar", 130, "21:00"}
};

Ticket cart[MAX_TICKETS];
int cartSize = 0;

void displayMovies() {
    printf("\nAvailable Movies:\n");
    for (int i = 0; i < MAX_MOVIES; i++) {
        printf("%d. %s - %d UAH, Time: %s\n", i + 1, movies[i].name, movies[i].price, movies[i].time);
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
    scanf("%d", &choice);
    if (choice < 1 || choice > MAX_MOVIES) {
        printf("Invalid choice!\n");
        return;
    }
    printf("Enter the number of tickets: ");
    scanf("%d", &quantity);
    if (quantity < 1) {
        printf("Invalid quantity!\n");
        return;
    }
    addTicketToCart(movies[choice - 1], quantity);
    printf("Tickets for %s added to cart.\n", movies[choice - 1].name);
}

void viewCart() {
    printf("\nYour Cart:\n");
    int total = 0;
    for (int i = 0; i < cartSize; i++) {
        printf("%d. %s - %d UAH x %d\n", i + 1, cart[i].movie.name, cart[i].movie.price, cart[i].quantity);
        total += cart[i].movie.price * cart[i].quantity;
    }
    printf("Total: %d UAH\n", total);
}

void menu() {
    int choice;
    while (1) {
        printf("\nCinema Ticket Service\n");
        printf("1. List Movies\n");
        printf("2. Buy Tickets\n");
        printf("3. View Cart\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
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
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
