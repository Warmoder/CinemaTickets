# Cinema Ticket Purchase Service

This program is a console-based ticket purchase service for a cinema. It allows users to view available movies, buy tickets, choose seats, view their cart, and pay for their tickets. The program also supports discount codes and saves the cart to a file.

## Features

1. **List of Movies:**
   - Displays available movies with their name, price, showtime, description, and duration.

2. **Buy Tickets:**
   - Allows users to buy tickets for a selected movie.
   - Users can choose specific seats in the cinema hall.

3. **View Cart:**
   - Displays the movies in the cart along with the quantity and total price.
   - Shows the chosen seats for each movie.

4. **Pay Cart:**
   - Users can apply discount codes during payment.
   - Displays the total amount to be paid and handles the payment process.

5. **Save Cart:**
   - Saves the current cart to a file (`cart.txt`).

6. **Load Cart:**
   - Loads the cart from a file (`cart.txt`).

## Discount Codes

The program supports the following discount codes:

- `SAVE10`: 10% discount
- `SAVE20`: 20% discount
- `SAVE30`: 30% discount

**Main Menu:**
- **1. List of Movies:** View the list of available movies.
- **2. Buy Tickets:** Buy tickets for a movie and choose your seats.
- **3. View Cart:** View the items in your cart.
- **4. Pay Cart:** Apply discount codes and pay for your tickets.
- **5. Save Cart:** Save the current cart to a file.
- **6. Exit:** Exit the program.

## Code Structure

- **Movie:** A struct that holds information about a movie (name, price, time, description, duration).
- **Ticket:** A struct that holds information about a ticket (movie, quantity, seats).
- **Discount:** A struct that holds information about a discount code (code, discount percentage).

## Functions

- **displayMovies():** Displays the list of available movies.
- **displaySeats(char seats[ROWS][SEATS_PER_ROW]):** Displays the seat arrangement for a movie.
- **chooseSeats(char seats[ROWS][SEATS_PER_ROW], int quantity):** Allows the user to choose seats for a movie.
- **addTicketToCart(Movie movie, int quantity):** Adds a ticket to the cart.
- **buyTickets():** Handles the process of buying tickets.
- **viewCart():** Displays the contents of the cart.
- **applyDiscount(int *total):** Applies a discount code to the total amount.
- **payCart():** Handles the payment process for the cart.
- **saveCart():** Saves the cart to a file.
- **loadCart():** Loads the cart from a file.
- **menu():** Displays the main menu and handles user input.
