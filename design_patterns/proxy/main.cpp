#include <iostream>
#include <memory>

/***************************************
 *  GRAPHIC
 **************************************/
class Graphic
{
  public:
    virtual void draw() = 0;
    virtual void load() = 0;
    virtual void save() = 0;
    virtual std::string getExtent() const = 0;
    virtual ~Graphic() = default;
};

/***************************************
 *  IMAGE JPEG
 **************************************/
class ImageJpeg : public Graphic
{
  public:
    virtual void draw() override;
    virtual void load() override;
    virtual void save() override;
    virtual std::string getExtent() const override;
};

void ImageJpeg::draw()
{
  std::cout << "ImageJpeg::draw()" << std::endl;
}

void ImageJpeg::load()
{
  std::cout << "ImageJpeg::load()" << std::endl;
}

void ImageJpeg::save()
{
  std::cout << "ImageJpeg::save()" << std::endl;
}

std::string ImageJpeg::getExtent() const
{
  return "jpeg";
}

/***************************************
 *  IMAGE BITMAP
 **************************************/
class ImageBitmap : public Graphic
{
  public:
    virtual void draw() override;
    virtual void load() override;
    virtual void save() override;
    virtual std::string getExtent() const override;
};

void ImageBitmap::draw()
{
  std::cout << "ImageBitmap::draw()" << std::endl;
}

void ImageBitmap::load()
{
  std::cout << "ImageBitmap::load()" << std::endl;
}

void ImageBitmap::save()
{
  std::cout << "ImageBitmap::save()" << std::endl;
}

std::string ImageBitmap::getExtent() const
{
  return "bitmap";
}

/***************************************
 *  IMAGE PROXY
 **************************************/
template <typename T>
class ImageProxy : public Graphic
{
  private:
    std::unique_ptr<Graphic> graphic {nullptr};

  public:
    ImageProxy() = default;
    ImageProxy(const ImageProxy&) = delete;
    ImageProxy(ImageProxy&&) = delete;

    virtual void draw() override;
    virtual void load() override;
    virtual void save() override;
    virtual std::string getExtent() const override;
};

  template <typename T>
void ImageProxy<T>::draw()
{
  load();
  graphic->draw();
}

  template <typename T>
void ImageProxy<T>::load()
{
  if(!graphic) {
    graphic = std::make_unique<T>();
    graphic->load();
  }
}

  template <typename T>
void ImageProxy<T>::save()
{
  if(graphic) {
    graphic->save();
    graphic.reset(nullptr);
  }
}

template <typename T>
std::string ImageProxy<T>::getExtent() const
{
  if(graphic)
    return graphic->getExtent();
  return "<uninitialized>";
}


/***************************************
 *
 *  MAIN
 *
 **************************************/
int main()
{
  ImageProxy<ImageJpeg> jpegProxy {};
  ImageProxy<ImageBitmap> bitmapProxy {};

  jpegProxy.draw();
  jpegProxy.draw();
  jpegProxy.save();

  bitmapProxy.load();
  bitmapProxy.draw();
  bitmapProxy.draw();
  bitmapProxy.save();

  return 0;
}
