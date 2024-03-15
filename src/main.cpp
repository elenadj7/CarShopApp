#include <string>
#include <iostream>
#include "car.hpp"
#include "dbhandler.hpp"
#include "util.hpp"

int main(int argc, char** argv){
    
    if(argc < 2){
        std::cout << "Use \"" << argv[0] << " help\" for more information" << std::endl;
        return 1;
    }

    csa::DBHandler db("cars.db");
    std::string command = argv[1];
    if(command == "help"){
        std::cout << "Welcome to CarShopApp!" << "\n" << "Use: " << std::endl;
        std::cout << "add - add new car to the database\n"
                  << "delete <id> - delete an entry from the database based on the internal id\n"
                  << "search <keyword> - search the database for the keyword and display results\n"
                  << "list - list all database entries\n";
    }
    else if(command == "add"){
        csa::Car car{};
        std::string textData{};

        std::cout << "Fill in the fields:\n";
        std::cout << "Brand:";
        std::cin >> textData;
        car.setBrand(textData);

        std::cout << "Model:";
        std::cin >> textData;
        car.setModel(textData);

        do{
            std::cout << "Mileage[number]:";
            std::cin >> textData;
        }while (!csa::validMileage(textData));
        car.setMileage(std::stoi(textData));

        do{
            std::cout << "Year[number > 1900]:";
            std::cin >> textData;
        }while (!csa::validYear(textData));
        car.setYear(std::stoi(textData));

        db.addCar(car);
        std::cout << "Car successfully added!" << std::endl;
    }
    else if(command == "list"){
        std::vector<csa::Car> cars = db.getAllCars();
        if(cars.size() == 0){
            std::cout << "No cars added" << std::endl;
        }

        for(const csa::Car &car : cars){
            std::cout << car << std::endl;
        }
    }
    else if(command == "search"){
        if(argc == 3){
            std::vector<csa::Car> cars = db.getAllByKeyword(argv[2]);
            if(cars.size() == 0){
                std::cout << "No cars matched the keyword" << std::endl;
            }

            for(const csa::Car &car : cars){
                std::cout << car << std::endl;
            }
        }
        else{
            std::cout << "Pass the keyword after the search command" << std::endl;
        }
    }
    else if(command == "delete"){
        
        if(argc == 3){
            
            if(!csa::isNumber(argv[2])){
                std::cout << "Pass the number after the delete command" << std::endl;
            }
            else{
                db.deleteCar(std::stoi(argv[2]));
                std::cout << "Car successfully deleted!" << std::endl;
            }
            
        }
        else{
            std::cout << "Pass the id after the delete command" << std::endl;
        }
        
    }
    else{
        std::cout << "Invalid argument - use help for more information" << std::endl;
    }


    return 0;
}