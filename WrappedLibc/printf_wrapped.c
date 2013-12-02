// Wrapper

#include <dlfcn.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

extern int printf(const char * restrict format, ...);
extern int vprintf(const char * restrict format, va_list ap);

int printf(const char * restrict format, ...)
{
    static int (*real_printf)(const char * restrict, ...);
    if (!real_printf) {
        real_printf = dlsym(RTLD_NEXT, "printf");
        if (!real_printf) {
            write(2, "dlsym: ", 7);
            
            const char *err = dlerror();
            write(2, err, strlen(err));
            
            write(2, "\n", 1);
            
            abort();
        }
    }
    
    real_printf("wrapped printf:\n");
    
    va_list ap;
    va_start(ap, format);
    int retval = vprintf(format, ap);
    va_end(ap);
    return retval;
}
