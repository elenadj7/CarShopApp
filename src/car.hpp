#pragma once
#include <string>
#include <ostream>

namespace csa{
    class Car{

        public:

        Car(int id, const std::string &brand, const std::string &model, int mileage, int year){
            this->brand = brand;
            this->model = model;
            this->mileage = mileage;
            this->year = year;
            this->id = id;
        }

        Car(){

        }

        std::string getBrand();
        std::string getModel();
        int getMileage();
        int getYear();
        int getId();

        void setBrand(const std::string &brand);
        void setModel(const std::string &model);
        void setMileage(int mileage);
        void setYear(int year);

        friend std::ostream& operator<<(std::ostream& os, const Car& car) {
            os << "Id: " << car.id << ", Brand: " << car.brand << ", Model: " << car.model << ", Mileage: " << car.mileage << ", Year: " << car.year; 
            return os;
        }


        private:
        std::string brand, model;
        int mileage, year, id;
    };
}
