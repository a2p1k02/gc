#include "vm.h"

void mark_all(vm_t* vm) {
    for (int i = 0; i < vm->stack_size; i++) {
        mark(vm->stack[i]);
    }
}

void sweep(vm_t* vm) {
    object_t** object = &vm->first_object;
    while (*object) {
        if (!(*object)->marked) {
            object_t* unreached = *object;

            *object = unreached->next;
            free(unreached);
        } else {
            (*object)->marked = 0;
            object = &(*object)->next;
        }
    }
}

void gc(vm_t* vm) {
    int num_objects = vm->num_objects;

    mark_all(vm);
    sweep(vm);

    vm->max_objects = vm->num_objects * 2;
}

void free_vm(vm_t* vm) {
    vm->stack_size = 0;
    gc(vm);
    free(vm);
}

vm_t* new_vm() {
    vm_t* vm = malloc(sizeof(vm));
    vm->stack_size = 0;
    vm->num_objects = 0;
    vm->max_objects = INITIAL_GC_THRESHOLD;
    return vm;
}

void gc(vm_t* vm);

void push(vm_t* vm, object_t* value) {
    assert((vm->stack_size < STACK_MAX, "stack overflow!"));
    vm->stack[vm->stack_size++] = value;
}

object_t* pop(vm_t* vm) {
    assert((vm->stack_size > 0, "stack underflow!"));
    return vm->stack[--vm->stack_size];
}

object_t* new_object(vm_t* vm, object_type type) {
    if (vm->num_objects == vm->max_objects) gc(vm);

    object_t* object = malloc(sizeof(object_t));
    object->type = type;
    object->marked = 0;

    object->next = vm->first_object;
    vm->first_object = object;

    vm->num_objects++;
    return object;
}

void push_int(vm_t* vm, int int_value) {
    object_t* object = new_object(vm, OBJ_INT);
    object->value = int_value;
    push(vm, object);
}

object_t* push_pair(vm_t* vm) {
    object_t* object = new_object(vm, OBJ_PAIR);
    object->tail = pop(vm);
    object->head = pop(vm);

    push(vm, object);
    return object;
}
