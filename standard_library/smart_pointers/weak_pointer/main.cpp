#include <iostream>
#include <memory>

class Slave;

class Master
{
  private:
    std::shared_ptr<Slave> m_ptr {nullptr};

  public:
    Master() = default;
    ~Master();
    Master(std::shared_ptr<Slave> ptr);
    void setSlave(std::shared_ptr<Slave> ptr);
};

Master::Master(std::shared_ptr<Slave> ptr)
  : m_ptr { ptr }
{
}

Master::~Master()
{
  std::cout << "~Master()" << std::endl;
}

void Master::setSlave(std::shared_ptr<Slave> ptr)
{
  m_ptr = ptr;
}

class Slave
{
  private:
    //    std::shared_ptr<Master> m_ptr {};
    std::weak_ptr<Master> m_ptr {};

  public:
    Slave() = default;
    ~Slave();
    Slave(std::shared_ptr<Master> ptr);
    void setMaster(std::shared_ptr<Master> ptr);
};

Slave::Slave(std::shared_ptr<Master> ptr)
  : m_ptr { ptr }
{
}

Slave::~Slave()
{
  std::cout << "Is expired: " << std::boolalpha << m_ptr.expired() << std::endl;
}

void Slave::setMaster(std::shared_ptr<Master> ptr)
{
  m_ptr = ptr;
}

int main()
{

  std::shared_ptr<Master> master {std::make_shared<Master>()};
  std::shared_ptr<Slave> slave {std::make_shared<Slave>()};

  master->setSlave(slave);
  slave->setMaster(master);

  return 0;
}
