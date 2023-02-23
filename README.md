# Bliss Engine
[![CMake](https://github.com/EinKara/Bliss/actions/workflows/cmake.yml/badge.svg)](https://github.com/EinKara/Bliss/actions/workflows/cmake.yml)

User-Friendly, Cross-Platform, and Open Source software engine built on GLFW (BEING MOVED TO SDL2)

## Requirements

| Library                                           | Download                                  |
| ------------------------------------------------- | ----------------------------------------- |
| **[GLFW](https://www.glfw.org/)**                 | ```$ ./scripts/requirements.sh```         |
| **[glad](https://glad.dav1d.de/)**                | **[Mirror](https://glad.dav1d.de/)**      |
| **[ASIO (boost)](https://think-async.com/Asio/)** | ```$ ./scripts/requirements.sh```         |

## Building

```console
$ ./build.sh
```

Building will generate a demo executable, located in build/bin.

## Using

Usage is fairly simple. Most of the work is done in a single window class. Like most frameworks, this class includes functions for updates, input, rendering, and various other events.

One example can be found in src/demo

```cpp
#include <Bliss.h>

class WindowDemo : public Window {
public:
	WindowDemo() {
		
	}

	WindowDemo(windowData dat) {windat = dat;}
	void OnCreate() override {}

	void OnDestroy() override {}

	void Input() override {}

	void Update(double time) override {}

	void Render() override {}
};
```

This is a skeleton window. Nothing will display on screen. Calling this window to show is equally as simple.

```cpp
int main() {
    // Creates instance of WindowDemo
    Window* window = new WindowDemo();

    // Initialized window, starts program loop. Nothing after this will be executed until the window is closed.
    window->Init();

    return 0;
}
```

This will display a window.