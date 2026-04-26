# gamesR2simple
A beginner-friendly Python library for making games.
# Status: 🚧WIP🚧
This library is still under development (pre-version 1), so things are still evolving. That said, suggestions are ***always*** welcome, and I will do my best to implement them!
## Installation
Installing with pip for Windows: 
```bash
pip install gamesR2simple
```
For MacOS and Linux: 
```bash
pip3 install gamesR2simple
```
## Quick example: Hello, World!
```Python
"""hello_world.pyw"""
from gamesR2simple import BaseGameWindow, run

class Game(BaseGameWindow):
    #Don't define __init__ — use setup() instead
    def setup(self):
        self.create_window("Hello, World!", 800, 400) #All parameters are optional
        
    def update(self):
        pass

run()
```
## Core Features
- ### Areas
    Areas are simple, pure-Python shapes that define a certain region on the coordinate plane. They're useful as bounding-boxes, or just shapes drawn to the screen.
  ⚠️Warning: do not continuously create or update areas (well, RectArea *might* be fine, depending on the context - but still, be careful!)
- ### Utilities
    Utilities are pure-Python implementations of graphical elements, such as buttons or sliders. These are still pretty limited, as the library is still under development, but more are coming.

## Contributing
This is currently a solo project, so outside ideas will be incredibly helpful. If you have feedback, or have an idea for a new feature, 1) open an issue, and 2) describe what you'd like to see! 
I reserve pull requests for major or breaking changes, so to keep things manageable, smaller ideas should be discussed in issues.

## License
This project is licensed under the MIT License - see the LICENSE file for details.
