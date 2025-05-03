#include <stdio.h>
#include "vm.h"

int main() {
    printf("Test 1: Objects on stack are preserved.\n");
    vm_t* vm = new_vm();
    push_int(vm, 1);
    push_int(vm, 2);

    gc(vm);
    assert((vm->num_objects == 2, "Should have preserved objects."));
    free_vm(vm);
    return 0;
}
