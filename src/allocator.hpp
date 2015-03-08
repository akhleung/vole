#ifndef VOLE_ALLOCATOR
#define VOLE_ALLOCATOR

#include <forward_list>

namespace Vole {

  class Allocator {
    std::forward_list<void*> objects;
    
    public:
    ~Allocator() {
      for (auto it : objects) free(it);
    }

    template <typename T>
    T* alloc(size_t c) {
      void* ptr = malloc(c*sizeof(T));
      objects.push_front(ptr);
      return static_cast<T*>(ptr);
    }

  };

}

#endif
