#include <stdio.h>
#include <dlfcn.h>
#include <ffi.h>

int main() {
    // void* handle = dlopen(0, RTLD_NOW | RTLD_GLOBAL);
    void* handle = dlopen(0, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        return 1;
    }

    void* f = dlsym(handle, "InitWindow");
    if (!f) {
        fprintf(stderr, "dlsym failed: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    ffi_cif cif;
    ffi_status status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 3, &ffi_type_void, (ffi_type*[]){ &ffi_type_sint32, &ffi_type_sint32, &ffi_type_pointer });
    if (status != FFI_OK) {
        fprintf(stderr, "ffi_prep_cif failed: %d\n", status);
        dlclose(handle);
        return 1;
    }

    int width = 800;
    int height = 600;
    const char* title = "Hello, World!";
    ffi_call(&cif, f, 0, (void*[]){ &width, &height, &title });

    while (1) { }

    (void) dlclose(handle);

    return 0;
}
