# Bliss Engine
[![CMake](https://github.com/EinKara/Bliss/actions/workflows/cmake.yml/badge.svg)](https://github.com/EinKara/Bliss/actions/workflows/cmake.yml)

Cross-Platform, Open Source, and Data-Oriented software framework (Currently being reworked for DOD)

## Requirements

| Library                                           | Download                                  |
| ------------------------------------------------- | ----------------------------------------- |
| **[GLFW](https://www.glfw.org/)**                 | ```$ ./scripts/requirements.sh```         |
| **[glad](https://glad.dav1d.de/)**                | **[Mirror](https://glad.dav1d.de/)**      |
| **[ASIO (boost)](https://think-async.com/Asio/)** | ```$ ./scripts/requirements.sh```         |

## Building

Configure Build Environment

```console
$ ./configure
```

Assuming the build directory has not been modified...

```console
$ cmake --build build
```

Building will generate a demo executable, located in build/bin.

## Using

Usage is fairly simple. For simplicity, window data is carried in a "Window" struct.

One example can be found in src/demo

```cpp
#include <Bliss.h>

Window demoWindow;

int main()
{
	demoWindow = CreateWindow(0,0,800,600,"Window Title", false);
	InitWindow(demoWindow);

	while (demoWindow.running) 
	{
		CullEvent(demoWindow);
	}

	DestroyWindow(demoWindow);

	return 0;
}
```

## Libraries Used

| Library |
| ------- |