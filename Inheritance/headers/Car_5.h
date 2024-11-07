#ifndef CAR_5_H
#define CAR_5_H

#include <iostream>

class Car {
public:
  virtual void start()
  {
    std::cout << "Car has just started\n";
  }
  virtual void run()
  {
    std::cout << "Car is running\n";
  }
  virtual void stop()
  {
    std::cout << "Car has just stopped\n";
  }

  void test_car()
  {
    Car::start(); // qualified(Base class) name
    Car::run();   // qualified(Base class) name
    Car::stop();  // qualified(Base class) name
  }
};

class Volvo : public Car {
public:
  void start() override
  {
    std::cout << "Volvo has just started\n";
  }
  void run() override
  {
    std::cout << "Volvo is running\n";
  }
  void stop() override
  {
    std::cout << "Volvo has just stopped\n";
  }
};

#endif // CAR_5_H