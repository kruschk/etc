/******************************************************************************
 * Function pointers are to functions what array pointers are to indexed
 * arrays. Function names, function pointers, array names, and array pointers
 * are all essentially (but not exactly, functions actually have type "function
 * returning type" and arrays have type "array of type") pointers because of
 * default conversions which are made automatically. Each of these pairs point
 * to the same respective things (either a function or an array). Function
 * names and array names cannot be reassigned, but function pointers and array
 * pointers can be! A function name is just a pointer which points to the
 * beginning of a function. Because of these considerations, my preferred forms
 * of function pointer usage are highlighted below.
 *****************************************************************************/
#include <stdio.h>

int add_one(int n);
int call_add_one(int a, int (*func)(int b));

int main(void) {
	int n = 5;
	int result1, result2, result3, result4;
	struct test_struct {
		int something;
		int (*increment)(int);
	};
	struct test_struct first_struct = {
		7,
		add_one
	};

	int (*fptr)(int n);
	fptr = add_one; /* preferred assignment form <-------------------------- */
	/**************************************************************************
	 * The following is equivalent to the above, but more explicit. In the
	 * above, there is an implicit conversion of add_one from type "function
	 * returning type" to type "pointer to function returning type" (per
	 * ISO/IEC 9899:1999 (C99 standard) section 6.3.2.1 paragraph 4 and 6.5.3.2
	 * paragraph 1). Since it aligns better with the more standard/more common
	 * behaviour of a function designator (which is for the conversion to
	 * occur), and because it is very similar to the way arrays behave, and
	 * because assignments for arrays are done without the & operator, I prefer
	 * to use the assignment without the & operator (i.e. the above).
	 *************************************************************************/
	fptr = &add_one;


	/* normal function call */
	result1 = add_one(n);
	/**************************************************************************
	 * call fptr, which is identical to calling add_one 
	 * https://stackoverflow.com/questions/17317747/explicit-dereference-of-function-pointer-in-c
	 *************************************************************************/
	result2 = fptr(result1); /* preferred calling form <-------------------- */
	/* explicitly dereference fptr, then pass result1 to the function */
	result2 = (*fptr)(result1);
	/* these are just playing around */
	first_struct.something = first_struct.increment(first_struct.something);
	result3 = first_struct.something;
	/* preferred form for passing arguments */
	result4 = call_add_one(result3, add_one); /* preferred  <--------------- */

	/* print results */
	/* A regular function can be called using explicit dereferencing of the
	 * function pointer. Normally would just use printf("%d\n", add_one(5)); */
	printf("Regular function call, but using explicit dereference: %d\n",
			(*add_one)(5));
	printf("result1: %d\n", result1);
	printf("result2: %d\n", result2);
	printf("result3: %d\n", result3);
	printf("result4: %d\n", result4);

	return 0;
}

int add_one(int n) {
	return n + 1;
}

int call_add_one(int a, int (*func)(int)) {
	return func(a);
}
