#ifndef OBJECT_H
#define OBJECT_H

#define STACK_MAX 256
#define INITIAL_GC_THRESHOLD 10;

typedef enum {
    OBJ_INT,
    OBJ_PAIR
} object_type;

typedef struct object {
    unsigned char marked;

    struct object_t* next;

    object_type type;
    union {
        int value;

        struct {
            struct object* head;
            struct object* tail;
        };
    };
} object_t;

void mark(object_t* object);

#endif //OBJECT_H
