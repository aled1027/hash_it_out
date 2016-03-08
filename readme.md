# Hash it out

Hash-it-out is a generic look-aside cache.
A look-aside cache is a key-value storage for items that are difficult or slow to compute.

## TODO
- `set_get` tests sometimes failing for nsets > 200
    - always failing for nsets > 1000
- add some explanation of how our hash-bucket double linked list is working
  - mention asymptotics, collisions, etc.
- eviction policy
    - evict.c and evict.h files
