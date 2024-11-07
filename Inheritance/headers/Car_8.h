#ifndef CAR_8_H
#define CAR_8_H

#include <iostream>

class Car {
public:
  friend std::ostream& operator<<(std::ostream& os, const Car& c)
  {
    c.print(os);
    return os;
  }

  virtual void print(std::ostream& os) const = 0;

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

class Volvo : public Car {
public:
  void print(std::ostream& os) const override
  {
    os << "I am Volvo";
  }

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
  void open_sunroof()
  {
    std::cout << "Volvo's sunroof opened\n";
  }
};

class VolvoXC90 : public Volvo {
public:
  void print(std::ostream& os) const override
  {
    os << "I am VolvoXC90";
  }

  void start() override
  {
    std::cout << "VolvoXC90 has just started\n";
  }
  void run() override
  {
    std::cout << "VolvoXC90 is running\n";
  }
  void stop() override
  {
    std::cout << "VolvoXC90 has just stopped\n";
  }
};

class Audi : public Car {
public:
  void print(std::ostream& os) const override
  {
    os << "I am Audi";
  }

  void start() override
  {
    std::cout << "Audi has just started\n";
  }
  void run() override
  {
    std::cout << "Audi is running\n";
  }
  void stop() override
  {
    std::cout << "Audi has just stopped\n";
  }
  void open_sunroof()
  {
    std::cout << "Audi's sunroof opened\n";
  }
};

#endif // CAR_8_H