#include <iostream>
#include <memory>
class Engine {
    public:
    Engine(float o) : oil{o} {}
    ~Engine() = default;
    float getOil() const {return oil;}
    void setOil(float newOil) {oil = newOil;}
    private:
    float oil;
};

class Boat {
    public:
    Boat(std::shared_ptr<Engine> e) : engine{e} {}
    ~Boat() = default;

    // To delete copy constructor you can delete the constructor that takes in the reference of another boat instance
    // Boat(const Boat& b) = delete;

    // Also delete the = operator that takes in a boat reference and outputs another Boat reference 
    // auto operator=(const Boat& b) -> Boat& = delete;

    int getID() const {return id;}
    void setID(int newID) {id = newID;}
    float getEngineOil() const {return engine->getOil();}
    void setEngineOil(float a) const {return engine->setOil(a);}
    private:
    std::shared_ptr<Engine> engine;
    int id;
};

// This function demonstrates that the copy constructor only copies the pointer but not the content of the pointer
int main() {
    std::shared_ptr<Engine> boatEngine = std::make_shared<Engine>(0.3);
    Boat boat1{boatEngine};
    boat1.setID(0);
    Boat boat2 = boat1; // Copy Constructor called here
    std::cout << "boat1 oil: " << boat1.getEngineOil() << "\n"; //boat 1 oil will be 0.3
    std::cout << "boat2 oil: " << boat2.getEngineOil() << "\n"; //boat 2 oil will be 0.3
    std::cout << "boat1 id: " << boat1.getID() << "\n"; //boat 1 id will be 0
    std::cout << "boat2 id: " << boat2.getID() << "\n"; //boat 2 id will be 0
    boat2.setEngineOil(0.5);
    boat2.setID(1);
    std::cout << "boat1 oil: " << boat1.getEngineOil() << "\n"; //boat 1 oil will be 0.5
    std::cout << "boat2 oil: " << boat2.getEngineOil() << "\n"; //boat 2 oil will be 0.5
    std::cout << "boat1 id: " << boat1.getID() << "\n"; //boat 1 id will be 0
    std::cout << "boat2 id: " << boat2.getID() << "\n"; //boat 2 id will be 1
    return 0;
}