#ifndef CAR_4_H
#define CAR_4_H

#include <iostream>

class Car {
public:
  Car()   // Base classes constructor
  {
    start();
    run();
    stop();
  }

  ~Car()  // Base classes destructor
  {
    start();
    run();
    stop();
  }
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

class Volvo : public Car
{
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

#endif // CAR_4_H
