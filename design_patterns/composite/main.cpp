#include <iostream>
#include <memory>
#include <vector>

/***************************************
 *  COMPONENT
 **************************************/
class Component
{
  public:
    virtual void operation() const = 0;
};

/***************************************
 *  COMPOSITE
 **************************************/
class Composite : public Component
{
  private:
    std::vector< std::shared_ptr<Component> > components {};

  public:
    virtual void operation() const override;
    void add(std::shared_ptr<Component> component);
    void remove(std::shared_ptr<Component> component);
    void remove(uint32_t index);
    std::shared_ptr<Component> getLeaf(uint32_t index);
};

void Composite::operation() const
{
  for(const auto& c : components)
    c->operation();
}

void Composite::add(std::shared_ptr<Component> component)
{
  components.push_back(component);
}

void Composite::remove(std::shared_ptr<Component> component)
{
  for(auto it {components.begin()}; it != components.end(); ++it)
  {
    auto c = *it;
    if(c == component)
      components.erase(it);
  }
}

void Composite::remove(uint32_t index)
{
  remove(getLeaf(index));
}

std::shared_ptr<Component> Composite::getLeaf(uint32_t index)
{
  if(index < components.size())
    return components.at(index);
  else
    throw std::out_of_range("Index out of range!");
}

/***************************************
 *  LEAF
 **************************************/
class Leaf final : public Component
{
  public:
    virtual void operation() const override;
};

void Leaf::operation() const
{
  std::cout << "Leaf::operation()" << std::endl;
}

/***************************************
 *  ELEMENT
 **************************************/
class Element final : public Component
{
  public:
    virtual void operation() const override;
};

void Element::operation() const
{
  std::cout << "Element::operation()" << std::endl;
}

/***************************************
 *  CLIENT
 **************************************/
class Client
{
  private:
    Composite composite {};
    Component* component {&composite};

  public:
    Client();
    Client(const Client&) = delete;
    Client(Client&&) = delete;
    void operator()() const;
    void setComponentAt(uint32_t index);
    void setComposite();
};

Client::Client()
{
  composite.add(std::make_shared<Leaf>());
  composite.add(std::make_shared<Leaf>());
  composite.add(std::make_shared<Element>());
  composite.add(std::make_shared<Leaf>());
  composite.add(std::make_shared<Element>());
  composite.add(std::make_shared<Leaf>());
  composite.add(std::make_shared<Element>());
  composite.add(std::make_shared<Element>());
}

void Client::operator()() const
{
  component->operation();
  std::cout << "---------------" << std::endl;
}

void Client::setComponentAt(uint32_t index)
{
  try {
    auto leaf = composite.getLeaf(index);
    component = leaf.get();
  }
  catch(std::out_of_range& oor)
  {
    std::cout << "getLeaf() error: " << oor.what() << std::endl;
  }
}

void Client::setComposite()
{
  component = &composite;
}


/***************************************
 *
 *  MAIN
 *
 **************************************/
int main()
{

// *** Example 1: Client management
//
  Client client {};
  client();
  client.setComponentAt(3);
  client();
  client.setComponentAt(4);
  client();
  client.setComposite();
  client();


// *** Example 2: Raw usage
//
//  Composite composite {};
//  composite.add(std::make_shared<Leaf>());
//  composite.add(std::make_shared<Element>());
//  composite.add(std::make_shared<Leaf>());
//  composite.add(std::make_shared<Element>());
//  composite.operation();
//
//  try {
//    auto leaf = composite.getLeaf(5);
//  }
//  catch(std::out_of_range& oor)
//  {
//    std::cout << "getLeaf() error: " << oor.what() << std::endl;
//  }
//
//  try {
//    composite.remove(5);
//  }
//  catch(std::out_of_range& oor)
//  {
//    std::cout << "remove() error: " << oor.what() << std::endl;
//  }
//
//  try {
//    auto leaf = composite.getLeaf(1);
//    composite.remove(leaf);
//  }
//  catch(std::out_of_range& oor)
//  {
//    std::cout << "getLeaf() error: " << oor.what() << std::endl;
//  }
//
//  composite.operation();

  return 0;
}
