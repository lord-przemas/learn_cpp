#ifndef MY_UNIQUE_PTR
#define MY_UNIQUE_PTR

#include <iostream>

namespace my
{

  class Deleter
  {
    public:
    void operator()(int* p) const
    {
      delete p;
    }
  };

  template<typename T, typename D = Deleter>
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
      
      unique_ptr(unique_ptr&& uptr)
        : ptr {uptr.ptr}
      {
        uptr.ptr = nullptr;
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

  template <typename T>
  unique_ptr<T> make_unique(T x)
  {
    return unique_ptr<T>{ new T { x } };
  }
  
}

#endif // MY_UNIQUE_PTR
