# Hash it out

Hash-it-out is a generic look-aside cache.
A look-aside cache is a key-value storage for items that are difficult or slow to compute.

## TODO
- add some explanation of how our hash-bucket double linked list is working
  - mention asymptotics, collisions, etc.
- dynamic resizing
    - dynamic_resize(cache_t cache);
- eviction policy
    - evict.c and evict.h files
