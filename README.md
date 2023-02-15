# Bliss Engine
[![CMake](https://github.com/EinKara/Bliss/actions/workflows/cmake.yml/badge.svg)](https://github.com/EinKara/Bliss/actions/workflows/cmake.yml)

User-Friendly software engine with GLFW implementation.

## IMPORTANT THINGS TO UNDERSTAND

### Input

Input is handled by the window, not the program. This is because of GLFW, and the workaround I had was messy.

## KNOWN ERRORS

When testing on my Chromebook's linux environment, I'll sometimes get this error:

```console
Segmentation fault (core dumped)
```

I cannot yet determine whether this is a system error, or a software error.
