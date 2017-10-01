#ifndef RING_H_
#define RING_H_

/*
 * A simple compile time ring buffer 
 * All macro starting with a '_' are used internally
 */

#include <k/types.h>

/*
 * Concatenate 'x' and 'y' with an underscore
 * PASTER(my, var) ->  my_var
 */
#define PASTER(x, y) x ## _ ## y

/*
 * Rules to get the name of different ring specific variables
 */
#define _RING_SIZE(id) PASTER(id, sz)
#define _RING_LEN(id) PASTER(id, len)
#define _RING_IDX(id) PASTER(id, idx)
#define _RING_VAR(id) PASTER(id, ring)

/*
 * true if we can get an element from the ring
 */
#define _RING_CAN_GET(id) ((_RING_SIZE(id) > 0) ? true : false)

#define _RING_DECREMENT_SZ(id) (_RING_SIZE(id)-- || true)
#define _RING_DECREMENT_IDX(id)				\
  ((_RING_IDX(id) == 0 ?				\
    ((_RING_IDX(id) = (_RING_LEN(id) - 1)) || true) :	\
    _RING_IDX(id)--) || true)


/*
 * The max amount of element as well as the size of the Ring buffer depends on
 * _RING_UINT type. By default using a u16, if you need more entries
 * you need to overwrite this macro.
 */
#define _RING_UINT u16

/*
 * Create a Ring buffer and its variables.
 * Takes the type of the ring's elements, a uniq identifier 
 * and the desired length of the ring.
 * Creating a ring create 4 variables depending on the identifier.
 * For example if the identifier is 'myring', it will create the variables :
 * myring_ring, myring_idx, myring_len, myring_len, and myring_sz
 *
 * The ring buffer can be static if you use the RING_CREATE_STATIC macro.
 */
#define RING_CREATE(type, id, length)			 \
  type _RING_VAR(id) [length];				 \
  /* The index points to the next space to write at */	 \
  _RING_UINT _RING_IDX(id) = 0;				 \
  _RING_UINT _RING_LEN(id) = length;			 \
  _RING_UINT _RING_SIZE(id) = 0

#define RING_CREATE_STATIC(type, id, length)			\
  static type _RING_VAR(id) [length];				\
  /* The index points to the next space to write at */		\
  static _RING_UINT _RING_IDX(id) = 0;				\
  static _RING_UINT _RING_LEN(id) = length;			\
  static _RING_UINT _RING_SIZE(id) = 0

/*
 * Add an element in a ring buffer, take the uniq identifier used to create
 * the buffer and the value to put in
 */
#define RING_ADD(id, value)					\
  do {								\
    _RING_VAR(id)[_RING_IDX(id)] = value;			\
    if (_RING_IDX(id) == (_RING_LEN(id) - 1))			\
      _RING_IDX(id) = 0;					\
    else							\
      _RING_IDX(id)++;						\
    if (_RING_SIZE(id) < _RING_LEN(id))				\
      _RING_SIZE(id)++;						\
  } while(0)

/*
 * Get an element from the ring buffer, decrement the size and reposition
 * the index at the right place
 */
#define RING_GET(id)					\
  (_RING_CAN_GET(id) == true				\
   && _RING_DECREMENT_SZ(id)				\
   && (_RING_DECREMENT_IDX(id)) ?			\
   _RING_VAR(id)[_RING_IDX(id)] : -1)

#endif /* RING_H_ */
