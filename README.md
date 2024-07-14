# Cinema Ticket Purchase Service

This is a simple C program that simulates a cinema ticket purchase service. The program provides a console-based menu to list available movies, buy tickets, view the cart, and simulate payment.

## Features

- **List Movies:** Display a list of available movies with their names, prices, and show times.
- **Buy Tickets:** Select a movie and specify the number of tickets to add to the cart.
- **View Cart:** View the current cart with details of the selected movies and total cost.
- **Pay Cart:** Simulate the payment process by entering the total amount. The program checks if the payment is sufficient and clears the cart after successful payment.

## Available Movies

The program includes the following movies:

1. Inception - 100 UAH, Time: 18:00
2. Interstellar - 120 UAH, Time: 20:00
3. The Matrix - 90 UAH, Time: 17:00
4. The Dark Knight - 110 UAH, Time: 19:00
5. Avatar - 130 UAH, Time: 21:00
6. Titanic - 85 UAH, Time: 16:00
7. The Godfather - 95 UAH, Time: 15:00
8. Pulp Fiction - 105 UAH, Time: 18:30
9. Fight Club - 100 UAH, Time: 22:00
10. Forrest Gump - 90 UAH, Time: 17:30

## Code Overview

The main components of the program include:

- **Movie Structure:** Defines the movie properties such as name, price, and show time.
- **Ticket Structure:** Defines the ticket properties including the movie and the quantity of tickets.
- **Movie Array:** Contains a list of available movies.
- **Cart Array:** Stores the selected tickets.
- **Functions:**
  - `displayMovies()`: Displays the list of available movies.
  - `addTicketToCart()`: Adds tickets to the cart.
  - `buyTickets()`: Allows the user to buy tickets.
  - `viewCart()`: Displays the current cart.
  - `payCart()`: Simulates the payment process.
  - `menu()`: Displays the main menu and handles user input.

## Future Improvements

- Add validation for user input.
- Implement more detailed movie information.
- Include discounts or special offers.
- Enhance the user interface with colors and formatting.

## License

This project is open-source and available under the [MIT License](LICENSE).

---

Feel free to modify the code and enhance the features as per your requirements. Contributions are welcome!
