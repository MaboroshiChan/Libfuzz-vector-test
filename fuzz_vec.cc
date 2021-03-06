#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
extern "C" {
#include "vector/vector.h"

typedef struct MyStruct
{
    int integer;
    __uint8_t myuint;
    /* data */
} MyStruct;


Vector generate_vector(size_t size){
    Vector v;
    vector_setup(&v, size, sizeof(MyStruct));
    for(size_t i = 0; i < size; ++i){
        MyStruct * s = (MyStruct*)malloc(sizeof(MyStruct));
        s->integer = 12;
        s->myuint = 210;
        vector_push_back(&v, &s);
    }
    return v;
}

int int_vector_test(size_t siz){
    printf("int_vector_test\n");
    Vector v;
    vector_setup(&v, siz, sizeof(int));
    int x = v.capacity;
    printf("capacity = %d\n", x);
    for(int i = 0; i < siz; ++i){
        vector_push_back(&v, &i);
    }
    
    Iterator iterator = vector_begin(&v);
    Iterator last = vector_end(&v);
    for(;!iterator_equals(&iterator, &last);iterator_increment(&iterator)){
        int item = *(int*)iterator_get(&iterator);
        printf("%d ", item);
    }
    printf("\n");

    Vector v2;
    vector_setup(&v2, siz, sizeof(MyStruct));
    for(int i = 0; i < siz; ++i){
        MyStruct * s = (MyStruct*)malloc(sizeof(MyStruct));
        s->integer = 12;
        s->myuint = 210;
        vector_push_back(&v2, s);
    }
    Iterator it = vector_begin(&v2);
    Iterator end = vector_end(&v2);
    for(;!iterator_equals(&it, &end);iterator_increment(&it)){
        MyStruct * y = (MyStruct*)iterator_get(&it);
        printf("(%d, %d)", y->integer, y->myuint);
        y = NULL;
    }
    vector_destroy(&v2);
    printf(" end \n");

    return 0;
}
}


bool vector_pushpopback_MyStruct_test(Vector * my_struct_vec, MyStruct * my_struct){
    MyStruct back1 = *(MyStruct*)vector_back(my_struct_vec);
    int res1 = back1.integer;
    vector_push_back(my_struct_vec, my_struct);
    vector_pop_back(my_struct_vec);
    MyStruct back2 = *(MyStruct*)vector_back(my_struct_vec);
    int res2 = back2.integer;
    assert(res1 == res2);
    return (res1 == res2);
}

bool vector_pushpopfront_MyStruct_test(Vector * my_struct_vec, MyStruct * my_struct){
    MyStruct back1 = *(MyStruct*)vector_front(my_struct_vec);
    int res1 = back1.integer;
    vector_push_front(my_struct_vec, my_struct);
    vector_pop_front(my_struct_vec);
    MyStruct back2 = *(MyStruct*)vector_front(my_struct_vec);
    int res2 = back2.integer;
    return (res1 == res2);
}

bool iterator_index_test(Vector * v, MyStruct * my_struct, size_t move_step){
    return false;
}

bool iterator_next_test(Iterator * it){
    MyStruct s = ITERATOR_GET_AS(MyStruct, it);
    int sz = s.integer;
    iterator_increment(it);
    iterator_decrement(it);
    s = ITERATOR_GET_AS(MyStruct, it);
    int sz2 = s.integer;
    assert(sz == sz2);
    return sz == sz2;
}

bool vector_copy_test(Vector * v1, Vector * v2){
    vector_copy(v2, v1);
    MyStruct back1 = *(MyStruct*)vector_back(v1);
    MyStruct back2 = *(MyStruct*)vector_back(v2);
    return (v1->size == v2->size) 
        && (back1.integer == back2.integer)
        && (v1->capacity == v2->capacity);
}

bool vector_swap_test(Vector * v1, Vector * v2){
    int size1 = v1->size;
    int size2 = v2->size;
    vector_swap(v1, v2);
    return (v1->size == size2) && (v2->size == size1);
}

bool vector_insert_test(Vector * v1, MyStruct * value, size_t pos){

    vector_insert(v1, pos, value);
    MyStruct get = VECTOR_GET_AS(MyStruct, v1, pos);  
    return (get.integer == value->integer);
}

bool vector_isempty_test(MyStruct * value){
   Vector v;
   vector_setup(&v, 10, sizeof(MyStruct));
   bool b1 = vector_is_empty(&v);
   vector_push_back(&v, value);
   bool b2 = vector_is_empty(&v);
   vector_destroy(&v);
   assert(b1 && !b2);
   return b1 && !b2;
}

bool vector_erase_test(Vector * v, size_t index, MyStruct * s){
    vector_push_back(v, s);
    size_t size = v->size;
    vector_erase(v, size - 1);
    return (v->size == size - 1);
}

MyStruct * parse_mystruct(__uint8_t *data,size_t siz){
   int integer = 0;
   int i = 0;
   __uint8_t myuint = 0;
   for(; i <= siz && i < 4; ++i){
       if (data[i] != 0){
         integer <<= 8;
         integer += data[i];
       }
   }
   if(i <= siz)
      myuint = data[i];
   data = data + i;
   MyStruct * res = (MyStruct *)malloc(sizeof(MyStruct));
   return res;
}
/**
extern "C" int LLVMFuzzerTestOneInput(__uint8_t *data, size_t Size) {
  int siz = data[0];
  Vector v;
  vector_setup(&v, siz, sizeof(MyStruct));
  for(int i = 0; i < siz; ++i){
    MyStruct s = parse_mystruct(data, Size, 10);
    vector_push_back(&v, &s);
  }
  // MyStruct s = parse_mystruct(data, Size, 10);
  //vector_pushpopback_MyStruct_test(&v, &s);
  for(int i = 0; i < siz; ++i){
      MyStruct * f = (MyStruct *)vector_get(&v, i);
      mystruct_destroy(f);
  }
  vector_destroy(&v);

  return 0;
}
*/

bool vector_pushpopback_int_test(Vector * my_int_vec, int x){
    int res1 = *(int*)vector_back(my_int_vec);
    vector_push_back(my_int_vec, &x);
    vector_pop_back(my_int_vec);
    int res2 = *(int*)vector_back(my_int_vec);
    assert(res1 == res2);
    return (res1 == res2);
}

bool vector_pushpopfront_int_test(Vector * my_int_vec, int x){
    int res1 = *(int*)vector_front(my_int_vec);
    vector_push_front(my_int_vec, &x);
    vector_pop_front(my_int_vec);
    int res2 = *(int*)vector_front(my_int_vec);
    assert(res1 == res2);
    return (res1 == res2);
}



extern "C" int LLVMFuzzerTestOneInput(__uint8_t *data, size_t Size) {
  size_t siz = data[0] + 1;
  Vector v;
  vector_setup(&v, siz, sizeof(MyStruct));
  MyStruct * s;
  for(int i = 0; i < siz; ++i){
    s = parse_mystruct(data, Size);
    vector_push_back(&v, &s);
    free(s);
  }
  s = parse_mystruct(data, Size);
  
  //This is where test suites are running
  vector_pushpopback_MyStruct_test(&v, s);
  vector_pushpopfront_MyStruct_test(&v, s);
  vector_isempty_test(s);
  //
  
  for(int i = 0; i < siz; ++i){
      MyStruct * get = (MyStruct *)vector_get(&v, i);
  }
  vector_destroy(&v);
  free(s);
  s = NULL;

  return 0;
}

//int main(int argc, const char* argv[]) {
//    printf("My test start!!");
//    int_vector_test(12);
//    return 0;
//}
//