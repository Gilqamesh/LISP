#include <stdio.h>
#include <dlfcn.h>
#include <ffi.h>
#include <x86intrin.h>
#include <math.h>

int main() {
    // void* handle = dlopen(0, RTLD_NOW | RTLD_GLOBAL);
    void* handle = dlopen(0, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        return 1;
    }

    void* f = dlsym(handle, "pow");
    if (!f) {
        fprintf(stderr, "dlsym failed: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    size_t t_start = __rdtsc();

    ffi_cif cif;
    ffi_status status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 2, &ffi_type_double, (ffi_type*[]){ &ffi_type_double, &ffi_type_double });
    if (status != FFI_OK) {
        fprintf(stderr, "ffi_prep_cif failed: %d\n", status);
        dlclose(handle);
        return 1;
    }

    size_t t_start2 = __rdtsc();

    double rvalue;
    double arg1 = 2.0;
    double arg2 = 3.0;
    ffi_call(&cif, f, &rvalue, (void*[]){ &arg1, &arg2 });
    size_t t_end = __rdtsc();
    printf("Result: %f\n", rvalue);
    printf("Time taken: %zu cycles\n", t_end - t_start);
    printf("Time taken for ffi_prep_cif: %zu cycles\n", t_start2 - t_start);

    // Call the function from loaded symbol
    t_start = __rdtsc();
    rvalue = ((double (*)(double, double))f)(arg1, arg2);
    t_end = __rdtsc();
    printf("Loaded symbol call result: %f\n", rvalue);
    printf("Loaded symbol call time taken: %zu cycles\n", t_end - t_start);

    // Call the function directly for comparison
    t_start = __rdtsc();
    rvalue = pow(arg1, arg2);
    t_end = __rdtsc();
    printf("Direct call result: %f\n", rvalue);
    printf("Direct call time taken: %zu cycles\n", t_end - t_start);

    (void) dlclose(handle);

    return 0;
}
