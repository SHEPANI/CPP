#include <cstdlib>  // malloc/free
#include <new>      // placement new

struct Mine {};

int main() {
  void *data = malloc(sizeof(Mine));      // Allocation of memory only.
  new (data) Mine();                      // construction only.
  reinterpret_cast<Mine*>(data)->~Mine(); // destruction only.
  free(data);                             // deallocation only.
}