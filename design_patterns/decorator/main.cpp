#include <iostream>
#include <memory>

/***************************************
 *  PHOTO
 **************************************/
class PhotoDecorator;

class Photo
{
  public:
    Photo() = default;
    Photo(const Photo&) = delete;
    Photo(Photo&&) = delete;

    virtual void draw() const = 0;
};
/***************************************
 *  PHOTO DECORATOR
 **************************************/
class PhotoDecorator : public Photo
{
  private:
    std::unique_ptr<PhotoDecorator> m_decorator { nullptr };

  public:
    using Photo::Photo;
    PhotoDecorator(std::unique_ptr<PhotoDecorator> decorator);
    virtual void draw() const override;

    void addBegin(std::unique_ptr<PhotoDecorator> decorator);
    void addEnd(std::unique_ptr<PhotoDecorator> decorator);
    void removeBegin();
    void removeEnd();
};

PhotoDecorator::PhotoDecorator(std::unique_ptr<PhotoDecorator> decorator)
  : m_decorator {std::move(decorator)}
{
}

void PhotoDecorator::draw() const
{
  if(m_decorator)
    m_decorator->draw();
}

void PhotoDecorator::addBegin(std::unique_ptr<PhotoDecorator> decorator)
{
  if(decorator)
  {
    if(decorator->m_decorator)
      decorator->m_decorator->addEnd(std::move(m_decorator));
    else
      decorator->m_decorator = std::move(m_decorator);

    m_decorator = std::move(decorator);
  }
}

void PhotoDecorator::addEnd(std::unique_ptr<PhotoDecorator> decorator)
{
  if(decorator)
  {
    if(!m_decorator) {
      m_decorator = std::move(decorator);
    }
    else {
      m_decorator->addEnd(std::move(decorator));
    }
  }
}

void PhotoDecorator::removeBegin()
{
  if(m_decorator)
  {
    m_decorator = std::move(m_decorator->m_decorator);
  }
}

void PhotoDecorator::removeEnd()
{
  if(m_decorator)
  {
    if(!m_decorator->m_decorator) {
      m_decorator.reset(nullptr);
    }
    else {
      m_decorator->removeEnd();
    }
  }
}

/***************************************
 *  BORDERED PHOTO
 **************************************/
class BorderedPhoto : public PhotoDecorator
{
  public:
    using PhotoDecorator::PhotoDecorator;
    virtual void draw() const override;
};

void BorderedPhoto::draw() const
{
  std::cout << "BorderedPhoto::draw()" << std::endl;
  PhotoDecorator::draw();
}
/***************************************
 *  TAGGED PHOTO
 **************************************/
class TaggedPhoto : public PhotoDecorator
{
  public:
    using PhotoDecorator::PhotoDecorator;
    virtual void draw() const override;
};

void TaggedPhoto::draw() const
{
  std::cout << "TaggedPhoto::draw()" << std::endl;
  PhotoDecorator::draw();
}
/***************************************
 *  Sepia PHOTO
 **************************************/
class SepiaPhoto : public PhotoDecorator
{
  public:
    using PhotoDecorator::PhotoDecorator;
    virtual void draw() const override;
};

void SepiaPhoto::draw() const
{
  std::cout << "SepiaPhoto::draw()" << std::endl;
  PhotoDecorator::draw();
}

/***************************************
 *  PHOTO COMPONENT A
 **************************************/
class PhotoComponentA : public Photo
{
  private:
    std::unique_ptr<Photo> photo {};
  public:
    PhotoComponentA();
    virtual void draw() const override;
};

PhotoComponentA::PhotoComponentA()
  : photo { std::make_unique<SepiaPhoto>(std::make_unique<TaggedPhoto>()) }
{
}

void PhotoComponentA::draw() const
{
  std::cout << "PhotoComponentA::draw()" << std::endl;
  photo->draw();
  std::cout << "-----------------------" << std::endl;
}

/***************************************
 *  PHOTO COMPONENT B
 **************************************/
class PhotoComponentB : public Photo
{
  private:
    std::unique_ptr<Photo> photo {};
  public:
    PhotoComponentB();
    virtual void draw() const override;
};

PhotoComponentB::PhotoComponentB()
  : photo { 
    std::make_unique<TaggedPhoto>(
        std::make_unique<SepiaPhoto>(
          std::make_unique<BorderedPhoto>(
            std::make_unique<TaggedPhoto>()
            )
          )
        ) 
  }
{
}

void PhotoComponentB::draw() const
{
  std::cout << "PhotoComponentB::draw()" << std::endl;
  photo->draw();
  std::cout << "-----------------------" << std::endl;
}


/***************************************
 *
 *  MAIN
 *
 **************************************/
int main()
{

//// *** Example 1: Raw usage
//
//  auto photo1 { std::make_unique<BorderedPhoto>() };
//  auto photo2 { std::make_unique<SepiaPhoto>(std::make_unique<TaggedPhoto>()) };
//  auto photo3 { std::make_unique<TaggedPhoto>(std::make_unique<SepiaPhoto>(std::make_unique<BorderedPhoto>(std::make_unique<TaggedPhoto>()))) };
//
//  photo3->draw();


//// *** Example 2: Phot components
//
//  PhotoComponentA photoA {};
//  PhotoComponentB photoB {};
//
//  photoA.draw();
//  photoB.draw();


//// *** Example 3: Dynamic decoration
//
//  constexpr bool addSecondBorder {true};
//  constexpr bool addSecondTag {false};
//  constexpr bool addSecondSepia {true};
//
//  auto bordered1 = std::make_unique<BorderedPhoto>();
//  auto tagged1 = std::make_unique<TaggedPhoto>(std::move(bordered1));
//  auto sepia1 = std::make_unique<SepiaPhoto>(std::move(tagged1));
//
//  std::unique_ptr<PhotoDecorator> photo {std::move(sepia1)};
//  if(addSecondBorder) {
//    std::unique_ptr<PhotoDecorator> photo_tmp { std::make_unique<BorderedPhoto>(std::move(photo)) };
//    photo.swap(photo_tmp);
//  }
//
//  if(addSecondTag) {
//    std::unique_ptr<PhotoDecorator> photo_tmp { std::make_unique<TaggedPhoto>(std::move(photo)) };
//    photo.swap(photo_tmp);
//  }
//
//  if(addSecondSepia) {
//    std::unique_ptr<PhotoDecorator> photo_tmp { std::make_unique<SepiaPhoto>(std::move(photo)) };
//    photo.swap(photo_tmp);
//  }
//
//  photo->draw();



// *** Example 4: Add/Remove decoration
  auto photo = std::make_unique<PhotoDecorator>();
  photo->addBegin(std::make_unique<BorderedPhoto>());

  photo->addBegin(std::make_unique<TaggedPhoto>(std::make_unique<SepiaPhoto>()));
  photo->addBegin(std::make_unique<TaggedPhoto>());
  photo->addBegin(std::make_unique<TaggedPhoto>(std::make_unique<SepiaPhoto>()));

  photo->addEnd(std::make_unique<SepiaPhoto>(std::make_unique<SepiaPhoto>()));
  photo->addEnd(std::make_unique<TaggedPhoto>(std::make_unique<SepiaPhoto>()));
  photo->addEnd(std::make_unique<SepiaPhoto>());

  photo->removeBegin();
  photo->removeBegin();

  photo->removeEnd();
  photo->removeEnd();

  photo->draw();

  return 0;
}
