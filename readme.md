# Hash it out
@aled1027, @ifjorissen

Hash-it-out is a generic look-aside cache.
A look-aside cache is a key-value storage for items that are difficult or slow to compute.

## TODO
- `set_get` tests sometimes failing for nsets > 200
    - always failing for nsets > 1000
- add some explanation of how our hash-bucket double linked list is working
  - mention asymptotics, collisions, etc.
- eviction policy
    - evict.c and evict.h files
- change some of the keys in the test functions
    - they are just the addresses of uin8_t values, as opposed to "strings"

-------

###Hash it out goal: Implement a bare-bones look-aside cache. Features: dynamic resizing, collision handling, customizable hash function, LRU eviction policy.

###File overview
```
  readme.md: what you're reading right now
  c_code/node.h: header file for the node type, which has been customized for this
                 assignment to store a key and a value
  c_code/node.c: implementation of the node type used in the linked list
  c_code/dbLL.h: header file for the doubly linked list of nodes, depending on
                 node.h
  c_code/dbLL.c: implementation of the doubly linked list
  c_code/cache.h: header file for cache; cache API 
  c_code/cache.c: implementation of cache
  c_code/dbLL_tests.c: tests for doubly linked list
  c_code/main.c: tests for the cache
  c_code/makefile: a simple makefile
```

### To run:
  * `make`: creates object files
  * `make run_all`: runs both the cache and linked list tests
  * `make run`: runs the cache tests
  * `make clean`: removes object files

------

### Some Notes on Collision Resolution
  We decided to use a doubly-linked list to handle collision detection. The idea of resolving collisions using some form of chaining is not new-- it is a common way to handle collisions in hash tables. Another reasonable choice might have been open-addressing. 

  So in our code, the hash bucket is a pointer to a doubly linked list.

  We chose to use the doubly-linked list for the following reasons: 
    * It was easy to implement and is a well known structure
    * It handles deletion more gracefully than a singly linked list. 
    * Collisions become something of a "non-issue," since we only have to insert the key into the list that each bucket in the cache has a pointer to.
    * Deletion in a hash table with chaining has fewer things to keep track of than deletion might in a hash table which leverages open addressing. This is also true of search.
    * Unlike open addressing, where the number of elements in the cache must always be less than the number of buckets, its _possible_ to store more elements in the cache than there are number of buckets. This means that the load factor approaches 1, a cache designed with open addressing will see much faster performance degredation than a cache designed chaining as it collision resolution mechanism. Of course, this comes at the expense of (near) constant time accesses, which is the whole point of a hash table. That being said, the performance of It also meant that we wouldn't have to develop an internal probing function (which open addressing relies on). 


### Some Notes on Testing
  We chose to implement two sets of tests. `dbLL_tests.c` contains tests for the doubly linked list, and attempts to exhaustively test insertion, removal, and search. It does not, however attempt to create "huge" lists. 


### Known Issues
  * We are relying quite heavily on the assumption that keys are unique. As of right now, we do not check to make sure that the key isn't already in the cache. To the user, it will seem as though the cache performed an "update", since the most recent key with that value will be closer to the head of the list, but because we don't (yet) remove previous <key, value> pair, we incur all of the costs of an "insertion," rather than an "update." This means that we are allocating additional memory to store this item, and also increasing load factor (unless, of course, we've triggered a resize). 


#####References
  * [Wiki on Open Addressing](https://en.wikipedia.org/wiki/Open_addressing)
  * [Wiki on Hash Tables & Collision Resolution](https://en.wikipedia.org/wiki/Hash_table#Collision_resolution)
