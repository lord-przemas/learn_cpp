#ifndef MY_UNIQUE_PTR
#define MY_UNIQUE_PTR

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
  class unique_ptr
  {
    private:
      T* ptr { nullptr };
      D deleter {};

    public:
      unique_ptr(T* p, const D& del = D{})
        : ptr {p}, deleter { del }
      {
      }
      
      template<typename Tp>
      unique_ptr(unique_ptr<Tp>&& uptr)
        : ptr {uptr.release()}
      {
      }

      unique_ptr(unique_ptr&& uptr)
        : ptr {uptr.ptr}
      {
        uptr.ptr = nullptr;
      }

      template<typename Tp>
      void operator=(unique_ptr<Tp>&& uptr)
      {
        deleter(ptr);
        ptr = uptr.release();
      }

      void operator=(unique_ptr&& uptr)
      {
        deleter(ptr);
        ptr = uptr.ptr;
        uptr.ptr = nullptr;
      }

      ~unique_ptr()
      {
        deleter(ptr);
        ptr = nullptr;
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

      unique_ptr(const unique_ptr&) = delete;
      void operator=(const unique_ptr&) = delete;

      T* get() const { return ptr; }
      T* release()
      {
        T* const l_ptr { ptr };
        ptr = nullptr;
        return l_ptr;
      }
      T* release() const = delete;

      D& get_deleter() { return deleter; }
      const D& get_deleter() const { return deleter; }

      void reset(T* p)
      {
        deleter(ptr);
        ptr = p;
      }
      void reset()
      {
        deleter(ptr);
        ptr = nullptr;
      }

      void swap(unique_ptr<T,D>& uptr)
      {
        T* const l_ptr { ptr };
        ptr = uptr.ptr;
        uptr.ptr = l_ptr;
      }

      operator bool() { return static_cast<bool>(ptr); }
  };

  template <typename T, typename... Args>
  unique_ptr<T> make_unique(Args... x)
  {
    return unique_ptr<T>{ new T { x... } };
  }
  
}

#endif // MY_UNIQUE_PTR
