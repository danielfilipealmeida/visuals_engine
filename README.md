# Visuals Engine

**Visuals Engine** is a library designed for creating real-time, reactive multimedia applications. Built with [openFrameworks](https://openframeworks.cc/), it provides a foundation for developers to craft dynamic visual experiences. While the repository includes example applications—such as a simple VJing tool—the primary focus is on the underlying engine tailored for new media and reactive multimedia projects.

## Getting Started

### Prerequisites

- [openFrameworks](https://openframeworks.cc/download/) (version 0.11.0 or later)



## Installation & Compilation Guide

### 1. **Clone the Repository**

```bash
git clone https://github.com/danielfilipealmeida/visuals_engine.git
cd visuals_engine
```

---

### 2. **Set Up Dependencies**

* Ensure [**openFrameworks**](https://openframeworks.cc/download/) is installed and properly configured on your system.
* Install the required addons (include them in your `addons.make` as needed):

  * `ofxGui`
  * `ofxMidi`
  * `ofxFft`

---

### 3. **Project Structure**

```
visuals_engine/
├── engine/               # Core rendering and processing logic (built as a static library)
│   ├── src/
│   ├── lib/              # Output: libEngine.a
│   └── VisualsEngine.xcodeproj  # macOS-only
├── examples/
│   └── hello_world/      # Individual example using the engine
│       ├── src/
│       ├── bin/
│       ├── Makefile
│       ├── config.make
│       └── hello_world.xcodeproj  # macOS-only
```

---

### 4. **Building the Project**

#### 🖥 macOS (Xcode)

* Open the `VisualsEngine.xcodeproj` file at the **project root** to build the `engine` and shared code.
* For each example, open the `.xcodeproj` file inside its folder, e.g.:

```bash
open ./examples/hello_world/hello_world.xcodeproj
```

* Build and run the example from Xcode.

####  Linux (Makefiles)

Linux uses the openFrameworks makefile infrastructure to build both the engine and the examples.

#####  Step 1: Build the Engine (static library)

```bash
cd engine
make
```

This will create `lib/libEngine.a`.

##### 🎮 Step 2: Build the Example

```bash
cd ../examples/hello_world
make
```

##### 📦 Step 3: Copy Runtime Resources

```bash
make post
```

> This step ensures required assets like shaders are copied into `bin/data/`.

---

### 5.  Running the Example

After building, you’ll find the compiled binary at:

```bash
examples/hello_world/bin/hello_world
```

Make sure to run it from the same folder (or that it has access to the `bin/data/` files you copied during `make post`).

Let me know if you'd like this turned into a `README.md`, or if you're ready to generate instructions for other examples automatically.


## Usage

After building the project, you can run the example VJing application or develop your own applications using the Visuals Engine library. Refer to the `examples` directory (to be added) for sample projects demonstrating various features.

## Contributing

Contributions are welcome! Feel free to submit issues, fork the repository, and create pull requests. Please ensure that your contributions align with the project's coding standards and include appropriate documentation.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.
