#ifndef MY_SHARED_PTR
#define MY_SHARED_PTR

#include <iostream>

namespace my
{

  template<typename T>
  class Deleter
  {
    public:
    void operator()(T* p) const
    {
      delete p;
    }
  };

  template<typename T, typename D = Deleter<T>>
  class shared_ptr
  {
    private:
      T* ptr { nullptr };
      unsigned int* counter { nullptr };
      D deleter {};

    void dec()
    {
        if(*counter == 1)
        {
          deleter(ptr);
          delete counter;
        }
        else
          (*counter)--;
    }

    void inc()
    {
      (*counter)++;
    }


    template <typename Tp, typename Dp>
    friend class shared_ptr;

    public:
      shared_ptr(T* p, const D& del = D{})
      : ptr {p},
        counter { new unsigned int { 1 } },
        deleter { del }
      {
      }
      
      shared_ptr(const shared_ptr& sptr)
      : ptr { sptr.ptr },
        counter { sptr.counter }
      {
        inc();
      }

      template <typename Tp>
      shared_ptr(const shared_ptr<Tp>& sptr)
      : ptr { sptr.ptr },
        counter { sptr.counter }
      {
        inc();
      }

      shared_ptr(shared_ptr&& sptr)
      : ptr {sptr.ptr},
        counter { sptr.counter }
      {
        sptr.ptr = nullptr;
        sptr.counter = nullptr;
      }

      template <typename Tp>
      shared_ptr(shared_ptr<Tp>&& sptr)
      : ptr {sptr.ptr},
        counter { sptr.counter }
      {
        sptr.ptr = nullptr;
        sptr.counter = nullptr;
      }

      void operator=(const shared_ptr& sptr)
      {
        dec();
        ptr = sptr.ptr;
        counter = sptr.counter;
        inc();
      }

      template <typename Tp>
      void operator=(const shared_ptr<Tp>& sptr)
      {
        dec();
        ptr = sptr.ptr;
        counter = sptr.counter;
        inc();
      }

      void operator=(shared_ptr&& sptr)
      {
        dec();
        ptr = sptr.ptr;
        counter = sptr.counter;
        sptr.ptr = nullptr;
        sptr.counter = nullptr;
      }

      template <typename Tp>
      void operator=(shared_ptr<Tp>&& sptr)
      {
        dec();
        ptr = sptr.ptr;
        counter = sptr.counter;
        sptr.ptr = nullptr;
        sptr.counter = nullptr;
      }

      ~shared_ptr()
      {
        if(counter)
          dec();
      }

      T& operator*()
      {
        return *ptr;
      }
      const T& operator*() const
      {
        return *ptr;
      }

      T* operator->() const
      {
        return ptr;
      }


      T* get() const { return ptr; }
      unsigned int use_count() const { return counter ? *counter : 0; };

      void reset(T* p)
      {
        dec();
        ptr = p;
        counter = new unsigned int { 1 };
      }
      void reset()
      {
        dec();
        ptr = nullptr;
        counter = nullptr;
      }

      void swap(shared_ptr<T,D>& uptr)
      {
        T* const l_ptr { ptr };
        ptr = uptr.ptr;
        uptr.ptr = l_ptr;
      }

      operator bool() { return static_cast<bool>(ptr); }
  };

  template <typename T, typename... Args>
  shared_ptr<T> make_shared(Args... x)
  {
    return shared_ptr<T>{ new T { x... } };
  }
  
}

#endif // MY_SHARED_PTR
