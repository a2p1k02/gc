#ifndef VM_H
#define VM_H

#include "object.h"

#include <stdlib.h>
#include <assert.h>

typedef struct {
    int num_objects;
    int max_objects;
    object_t* first_object;
    object_t* stack[STACK_MAX];
    int stack_size;
} vm_t;

void mark_all(vm_t* vm);
void sweep(vm_t* vm);
void gc(vm_t* vm);
void free_vm(vm_t* vm);
vm_t* new_vm();
void gc(vm_t* vm);
void push(vm_t* vm, object_t* value);
object_t* pop(vm_t* vm);
object_t* new_object(vm_t* vm, object_type type);
void push_int(vm_t* vm, int int_value);
object_t* push_pair(vm_t* vm);

#endif //VM_H
