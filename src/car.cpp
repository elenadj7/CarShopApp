#include <string>
#include "car.hpp"

namespace csa{

    std::string Car::getBrand(){
        return brand;
    };
    std::string Car::getModel(){
        return model;
    };

    int Car::getMileage(){
        return mileage;
    };
    int Car::getYear(){
        return year;
    };
    int Car::getId(){
        return id;
    }

    void Car::setBrand(const std::string &brand){
        this->brand = brand;
    }
    void Car::setModel(const std::string &model){
        this->model = model;
    }
    void Car::setMileage(int mileage){
        this->mileage = mileage;
    }
    void Car::setYear(int year){
        this->year = year;
    }
};