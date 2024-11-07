#ifndef CAR_1_H
#define CAR_1_H

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
};

class Mercedes : public Car {
public: 
  void start() override
  {
    std::cout << "Mercedes has just started\n";
  }
  void run() override
  {
    std::cout << "Mercedes is running\n";
  }
  void stop() override
  {
    std::cout << "Mercedes has just stopped\n";
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

class VolvoXC90 : public Volvo {
public:
  void start() override
  {
    std::cout << "VolvoXC90 has just started\n";
  }
  void stop() override
  {
    std::cout << "VolvoXC90 has just stopped\n";
  }
};

#endif // CAR_1_H
