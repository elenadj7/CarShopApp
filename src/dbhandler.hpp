#pragma once
#include <sqlite3.h>
#include <string>
#include <cstring>
#include <memory>
#include <iostream>
#include <vector>
#include "car.hpp"

namespace csa{
    class DBHandler{

        public:
        DBHandler(std::string name) {
            dbname = new char[name.length() + 1];
            std::strcpy(dbname, name.c_str());

            initDB();
        }
        ~DBHandler(){
            delete[] dbname;
            sqlite3_close(db);
        }

        void addCar(Car &car);
        std::vector<Car> getAllCars();
        void deleteCar(int id);
        std::vector<Car> getAllByKeyword(std::string keyword);

        private:
        sqlite3* db;
        char* dbname;

        void initDB();
    };
}