#include <stdint.h>
#include <assert.h>
#include <string.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef s8 b8;
typedef s16 b16;
typedef s32 b32;
typedef s64 b64;

typedef float f32;
typedef double f64;

#define unused(x) (void)x
#define bytes(n) (n)
#define kilobytes(n) ((n) << 10)
#define megabytes(n) ((n) << 20)
#define gigabytes(n) (((u64)n) << 30)
#define terabytes(n) (((u64)n) << 40)

#define trap() __builtin_trap()

#define threadlocal __thread

#define check(b) \
    if (!(b)) trap()

#define array_count(array) (sizeof(array)/sizeof((array)[0]))

#define check_null(p) ((p)==0)
#define set_null(p) ((p)=0)

#define queue_push_nz(f,l,n,next,zchk,zset) (zchk(f)?\
(((f)=(l)=(n)), zset((n)->next)):\
((l)->next=(n),(l)=(n),zset((n)->next)))
#define queue_push_front_nz(f,l,n,next,zchk,zset) (zchk(f) ? (((f) = (l) = (n)), zset((n)->next)) :\
((n)->next = (f)), ((f) = (n)))
#define queue_pop_nz(f,l,next,zset) ((f)==(l)?\
(zset(f),zset(l)):\
((f)=(f)->next))
#define stack_push_n(f,n,next) ((n)->next=(f),(f)=(n))
#define stack_pop_nz(f,next,zchk) (zchk(f)?0:((f)=(f)->next))

#define queue_push(f,l,n)         queue_push_nz(f,l,n,next,check_null,set_null)
#define queue_push_front(f,l,n)    queue_push_front_nz(f,l,n,next,check_null,set_null)
#define queue_pop(f,l)            queue_pop_nz(f,l,next,set_null)
#define stack_push(f,n)           stack_push_n(f,n,next)
#define stack_pop(f)              stack_pop_nz(f,next,check_null)

#define memory_copy memcpy
#define memory_set memset
#define memory_move memmove

#define memory_copy_struct(dst, src) do { static_assert(sizeof(*(dst)) == sizeof(*(src))); memory_copy((dst), (src), sizeof(*(dst))); while(0)
#define memory_copy_array(dst, src) do { static_assert(sizeof(dst) == sizeof(src); memory_copy((dst), (src), sizeof((src))); while(0)

#define memory_zero(pointer, size) memory_set((pointer), 0, size)
#define memory_zero_struct(pointer) memory_zero((pointer), sizeof(*(pointer))
#define memory_zero_array(array) memory_zero((array), sizeof(array))

