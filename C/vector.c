#define VEC_INIT(type, cap) \
	typedef struct { \
		size_t cap; \
		size_t len; \
		type *arr; \
	} Vector_type

typedef struct {
	size_t cap;
	size_t len;
	void **arr;
} Vector;
