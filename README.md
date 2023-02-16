# Bliss Engine
[![CMake](https://github.com/EinKara/Bliss/actions/workflows/cmake.yml/badge.svg)](https://github.com/EinKara/Bliss/actions/workflows/cmake.yml)

User-Friendly software engine with GLFW implementation.

## Requirements

| Library                                           | H           |
| ------------------------------------------------- | ----------- |
| **[GLFW](https://www.glfw.org/)**                 |             |
| **[glad](https://glad.dav1d.de/)**                |             |
| **[ASIO (boost)](https://think-async.com/Asio/)** |             |

### Download

#### Linux

```console
$ ./scripts/requirements.sh
```

## IMPORTANT THINGS TO UNDERSTAND

### Input

Input is handled by the window, not the program. This is because of GLFW, and the workaround I had was messy.

## KNOWN ERRORS

When testing on my Chromebook's linux environment, I'll sometimes get this error:

```console
Segmentation fault (core dumped)
```

I cannot yet determine whether this is a system error, or a software error.
