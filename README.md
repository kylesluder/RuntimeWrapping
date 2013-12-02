RuntimeWrapping
===

This project demonstrates how to wrap a C function -- specifically, `printf(3)`.

Here's how it works:

1. `WrappedLibc` exports a `printf` function whose prototype matches the one declared in `stdio.h`.

2. `WrappedLibc`'s `printf` calls `dlsym` with the module handle `RTLD_NEXT` to find the original `printf` at runtime and invoke it with its own arguments. It can't invoke it with the original arguments because `printf` is variadic. So it creates a `va_list` and calls `vprintf` instead.

3. `WrappedLibc`'s `OTHER_LDFLAGS` includes `-sub_library libSystem`, which makes `libWrappedLibc.dylib` reexport all the symbols from `libSystem` (to which `libc` is an alias on OS X).

4. `WrapperTester` links against `libWrappedLibc.dylib`. It does *not* link against `libSystem` --- `LINK_WITH_STANDARD_LIBRARIES` is set to `NO`. This causes it to look up all standard library functions as indirect symbols via `libWrappedLibc`.
