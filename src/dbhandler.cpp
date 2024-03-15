#include "dbhandler.hpp"

namespace csa {
    void DBHandler::addCar(Car &car) {
        int res = sqlite3_open(dbname, &db);
        if (res != SQLITE_OK) {
            std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        const char* query = "INSERT INTO Car (Brand, Model, Mileage, Year) VALUES (?, ?, ?, ?);";
        
        sqlite3_stmt* stmt;
        res = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr); //length = -1 
        if (res != SQLITE_OK) {
            std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_text(stmt, 1, car.getBrand().c_str(), car.getBrand().length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, car.getModel().c_str(), car.getModel().length(), SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, car.getMileage());
        sqlite3_bind_int(stmt, 4, car.getYear());

        res = sqlite3_step(stmt);
        if (res != SQLITE_DONE) {
            std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

    void DBHandler::initDB(){
        int res = sqlite3_open(dbname, &db);
        if (res != SQLITE_OK) {
            std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        const char *query = "CREATE TABLE IF NOT EXISTS Car (ID INTEGER PRIMARY KEY AUTOINCREMENT, Brand TEXT NOT NULL, Model TEXT NOT NULL, Mileage INTEGER NOT NULL, Year INTEGER NOT NULL);";
        char *error = nullptr;
        res = sqlite3_exec(db, query, nullptr, nullptr, &error); //callbacks none
        if (res != SQLITE_OK) {
            std::cerr << "Error creating table: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_free(error);
        }
        sqlite3_close(db);
    }

    std::vector<Car> DBHandler::getAllCars() {
        int res = sqlite3_open(dbname, &db);
        std::vector<Car> cars{};

        if (res != SQLITE_OK) {
            std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
            return cars;
        }

        const char* query = "SELECT * FROM Car;";
        sqlite3_stmt* stmt;
        res = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
        if (res != SQLITE_OK) {
            std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return cars;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* brand = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            const char* model = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            int mileage = sqlite3_column_int(stmt, 3);
            int year = sqlite3_column_int(stmt, 4);
            cars.push_back(Car(id, brand, model, mileage, year));
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return cars;
    }

    std::vector<Car> DBHandler::getAllByKeyword(std::string keyword){
        int res = sqlite3_open(dbname, &db);
        std::vector<Car> cars{};

        if (res != SQLITE_OK) {
            std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
            return cars;
        }

        
        std::string query = "SELECT * FROM Car WHERE Brand LIKE ? OR Model LIKE ?";
        sqlite3_stmt* stmt;
        res = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if (res != SQLITE_OK) {
            std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return cars;
        }

        std::string filter = "%" + keyword + "%";

        sqlite3_bind_text(stmt, 1, filter.c_str(), filter.length(), SQLITE_TRANSIENT); //something + keyword + something
        sqlite3_bind_text(stmt, 2, filter.c_str(), filter.length(), SQLITE_TRANSIENT);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* brand = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            const char* model = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            int mileage = sqlite3_column_int(stmt, 3);
            int year = sqlite3_column_int(stmt, 4);
            cars.push_back(Car(id, brand, model, mileage, year));
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        return cars;
    }


    void DBHandler::deleteCar(int id) {
        int res = sqlite3_open(dbname, &db);
        if (res != SQLITE_OK) {
            std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        const char* query = "DELETE FROM Car WHERE ID = ?;";

        sqlite3_stmt* stmt;
        res = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
        if (res != SQLITE_OK) {
            std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_int(stmt, 1, id);

        res = sqlite3_step(stmt);
        if (res != SQLITE_DONE) {
            std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

}
