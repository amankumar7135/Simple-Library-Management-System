# Simple-Library-Management-System
This C++ code implements a **Library Management System** that allows a user to manage a collection of books. The system provides the ability to add, search, issue, return, list, and delete books. It uses a **linked list** to store the book data and ensures that each book has a unique ID using a set. Here's a breakdown of the code:

### 1. **Class `Book`**:
   - Represents a book with attributes: 
     - `id`: Unique identifier.
     - `title`: Title of the book.
     - `author`: Author of the book.
     - `isIssued`: Indicates whether the book is issued or available.
   - The constructor initializes these values, and the `displayBookDetails()` method prints the book's details in a formatted way.

### 2. **Class `Node`**:
   - Each node in the linked list represents a book object.
   - Has two attributes:
     - `book`: A `Book` object.
     - `next`: A pointer to the next node in the linked list.

### 3. **Class `Library`**:
   - Manages the collection of books using a linked list structure.
   - **Private members**:
     - `head`: Points to the first node in the linked list.
     - `bookIds`: A `set` that ensures each book ID is unique.
   - **Private methods**:
     - `findBookNodeById(int id)`: Finds a book node by its ID.
     - `findBookNodeByTitle(const string& title)`: Finds a book node by its title.
   - **Public methods**:
     - `addBook()`: Adds a new book to the library. It checks for duplicate IDs using the `bookIds` set.
     - `searchBookById()`: Searches for a book by its ID and displays its details.
     - `searchBookByTitle()`: Searches for a book by its title and displays its details.
     - `issueBook()`: Marks a book as issued if it is available.
     - `returnBook()`: Marks a book as returned if it is issued.
     - `listAllBooks()`: Lists all the books in the library, sorted by ID.
     - `deleteBook()`: Deletes a book from the library based on its ID.
   - **Destructor**:
     - Deletes all nodes in the linked list when the library object is destroyed.

### 4. **Helper Functions**:
   - **`displayMenu()`**: Displays the menu options for the user.
   - **`getIntInput()`**: Safely gets an integer input from the user, handling invalid inputs.
   - **`getStringInput()`**: Safely gets a string input from the user.

### 5. **Main Function**:
   - The `main()` function serves as the program's entry point and contains an interactive loop where the user can select actions from the menu:
     - Add a book.
     - Search a book by ID or title.
     - Issue or return a book.
     - List all books.
     - Delete a book.
     - Exit the system.

### Key Concepts:
- **Linked List**: Used to store and manage books dynamically.
- **Sets**: Used to enforce unique book IDs.
- **Basic Validation**: Ensures that only integers are accepted where expected (e.g., book IDs).
- **Sorting**: Books are sorted by their ID when listing all books.

This system provides a simple, user-friendly way to manage a collection of books in a library.
