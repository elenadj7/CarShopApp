# C++ Assignment: CarShopApp

## Description
CarShopApp is a C++ application designed to manage information about cars. It allows users to input data such as brand, model, mileage, and year of the car, which is then stored in a SQLite3 database. The application provides a Command Line Interface (CLI) for interaction. It supports the following command line parameters:

- `./app help`: Display usage instructions.
- `./app add`: Add a new car to the database.
- `./app delete <id>`: Delete an entry from the database based on the internal ID.
- `./app search <keyword>`: Search the database for the specified keyword and display results.
- `./app list`: List all database entries.

## Usage
1. Clone the repository:
    ```bash
    git clone https://github.com/elenadj7/CarShopApp.git
    ```
2. Navigate to the project directory:
    ```bash
    cd CarShopApp
    ```
3. Build the application using CMake:
    ```bash
    cmake -B out/
    cmake --build out/
    ```
4. Run the application with desired command line parameters, e.g.:
    ```bash
    ./app help
    ./app add
    ./app delete 123
    ./app search Toyota
    ./app list
    ```

## Notes
- Ensure that SQLite3 is installed on your system for database functionality.

