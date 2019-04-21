#include <iostream>
#include <memory>

class Client;
class Factory;
class Car;
class Truck;
class DaimlerFactory;
class BmwFactory;
class MercedesCar;
class BmwCar;
class MercedesTruck;
class BmwTruck;


/***************************************
 *  VEHICLE
 **************************************/
class Vehicle
{
  public:
    virtual ~Vehicle() = default;
    virtual std::string brand() const = 0;
    virtual std::string type() const = 0;
};

/***************************************
 *  CAR
 **************************************/
class Car : public Vehicle
{
  public:
    virtual std::string type() const { return "Car"; };
};

/***************************************
 *  TRUCK
 **************************************/
class Truck : public Vehicle
{
  public:
    virtual std::string type() const { return "Truck"; };
};

/***************************************
 *  FACTORY
 **************************************/
class Factory
{
  public:
    virtual ~Factory() = default;
    virtual std::unique_ptr<Car> createCar() const = 0;
    virtual std::unique_ptr<Truck> createTruck() const = 0;
};

/*************************************** 
 *  MERCEDES CAR 
 ***************************************/
class MercedesCar : public Car
{
  public:
    virtual std::string brand() const { return "Mercedes"; };
};

/*************************************** 
 *  BMW CAR 
 ***************************************/
class BmwCar : public Car
{
  public:
    virtual std::string brand() const { return "Bmw"; };
};

/*************************************** 
 *  MERCEDES TRUCK
 ***************************************/
class MercedesTruck : public Truck
{
  public:
    virtual std::string brand() const { return "Mercedes"; };
};

/*************************************** 
 *  BMW TRUCK 
 ***************************************/
class BmwTruck : public Truck
{
  public:
    virtual std::string brand() const { return "Bmw"; };
};

/***************************************
 *  DAIMLER FACTORY
 **************************************/
class DaimlerFactory : public Factory
{
  public:
    virtual std::unique_ptr<Car> createCar() const override;
    virtual std::unique_ptr<Truck> createTruck() const override;
};

std::unique_ptr<Car> DaimlerFactory::createCar() const
{
  return std::make_unique<MercedesCar>();
}

std::unique_ptr<Truck> DaimlerFactory::createTruck() const
{
  return std::make_unique<MercedesTruck>();
}

/***************************************
 *  BMW FACTORY
 **************************************/
class BmwFactory : public Factory
{
  public:
    virtual std::unique_ptr<Car> createCar() const override;
    virtual std::unique_ptr<Truck> createTruck() const override;
};

std::unique_ptr<Car> BmwFactory::createCar() const
{
  return std::make_unique<BmwCar>();
}

std::unique_ptr<Truck> BmwFactory::createTruck() const
{
  return std::make_unique<BmwTruck>();
}

/***************************************
 *  CLIENT
 **************************************/
class Client
{
  private:
    std::unique_ptr<Factory> m_factory;

  public:
    Client() = delete;
    Client(const Client& client) = delete;
    Client(Client&& client) = default;
    Client(std::unique_ptr<Factory> factory);
    virtual ~Client() = default;

    void createVehicles() const;
};

Client::Client(std::unique_ptr<Factory> factory)
: m_factory { std::move(factory) }
{
}

void Client::createVehicles() const
{
  auto car = m_factory->createCar();
  auto truck = m_factory->createTruck();

  std::cout << car->brand() << " " << car->type() << std::endl;
  std::cout << truck->brand() << " " << truck->type() << std::endl;
}

/***************************************
 *
 *  MAIN
 *
 **************************************/
int main()
{
  Client client1 {std::make_unique<DaimlerFactory>()};
  Client client2 {std::make_unique<BmwFactory>()};

  client1.createVehicles();
  client2.createVehicles();
  client1.createVehicles();
  client2.createVehicles();

  return 0;
}
