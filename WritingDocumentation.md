# Notes on Writing Documentation

This project uses **Doxygen** to generate documentation from specially formatted comments in the source code.

---

## Writing Doxygen-Style Comments

Please follow the guidelines below when documenting your code. These tags help Doxygen extract relevant information and generate structured documentation:

| Tag                  | Description                                     |
| -------------------- | ----------------------------------------------- |
| `@brief`             | Short summary (used in class/function listings) |
| `@details`           | More detailed description (optional)            |
| `@param`             | Describes a function parameter                  |
| `@return`            | Describes the return value                      |
| `@tparam`            | Template parameter documentation                |
| `@throws`            | Exceptions the function might throw             |
| `@see`               | Cross-reference to related symbols              |
| `@note`              | Notes or important caveats                      |
| `@warning`           | Warnings to the user                            |
| `@code` / `@endcode` | Embed code examples                             |
| `@file`              | File-level description                          |
| `@author`            | Author of the code                              |
| `@version`           | Version information                             |

---

### Example

Below is an example of how to properly document a class using Doxygen comments:

```cpp
/// @brief Base class/interface for all classes that are drawn on-screen.
///
/// All drawable elements should inherit from `Drawable` and implement the required virtual methods.
class Drawable {
public:
    ofRectangle rect;

    /// @brief Called once per frame, before drawing.
    ///
    /// All main logic and processing should happen here. Avoid doing heavy processing in `draw()`.
    /// 
    /// @note Must be overridden by subclasses.
    virtual void update() = 0;

    /// @brief Draws the object using the internal rectangle (`this->rect`).
    ///
    /// This version of `draw()` uses the pre-defined internal rectangle to determine the drawing area.
    ///
    /// @note Must be overridden by subclasses.
    virtual void draw() = 0;

    /// @brief Draws the object into a specified rectangle.
    ///
    /// This version allows the caller to specify the drawing area manually.
    ///
    /// @param _rect Rectangle to draw into.
    /// @note Must be overridden by subclasses.
    virtual void draw(ofRectangle _rect) = 0;

    /// @brief Sets the internal rectangle.
    ///
    /// Updates `this->rect`, which will be used by the parameterless `draw()` method.
    ///
    /// @param _rect Rectangle to assign.
    void setRect(ofRectangle _rect) {
        this->rect = _rect;
    }
};
```

Use `///` for single-line documentation or `/** ... */` for multi-line blocks.

---

## Generating the Documentation

To build or update the documentation, run the following command from the root of the project:

```bash
doxygen Doxyfile
```

This will create a `docs` directory containing:

* `docs/html/` — browsable HTML documentation
* `docs/latex/` — LaTeX source files

To compile the LaTeX files into a PDF:

```bash
cd docs/latex
make
```

The resulting PDF (typically named `refman.pdf`) will contain the full documentation in printable format.

---

## References and Further Reading

* Doxygen Official Site: [https://www.doxygen.nl](https://www.doxygen.nl)
* List of All Tags: [https://www.doxygen.nl/manual/commands.html](https://www.doxygen.nl/manual/commands.html)
* Getting Started Guide: [https://www.doxygen.nl/manual/starting.html](https://www.doxygen.nl/manual/starting.html)
* Markdown Support: [https://www.doxygen.nl/manual/markdown.html](https://www.doxygen.nl/manual/markdown.html)
* Example Projects: [https://github.com/doxygen/doxygen/tree/master/examples](https://github.com/doxygen/doxygen/tree/master/examples)

