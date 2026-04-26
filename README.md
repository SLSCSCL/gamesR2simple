# gamesR2simple
A Python library to make it easier to write games.
# Important
This library is still under development for version 1, and is not complete. However, suggestions are welcome, and I will try my best to implement them!
## Installation
For most devices, you'll install with either `pip install gamesR2simple` or `pip3 install gamesR2simple`, depending on the OS.
## Basic example
```Python
"""hello_world.pyw"""
from gamesR2simple import BaseGameWindow, run

class Game(BaseGameWindow):
    #Never define __init__ - that's what setup() is for
    def setup(self):
        self.create_window("Hello World!", 800, 400) #All parameters are optional
        
    def update(self):
        pass

run()
```
## Core Features
- ### Areas
    Areas are a nice way to create bounding boxes, and can be drawn to the screen as shapes. However, I do not recommend continuously creating or updating any areas except RectArea - but still, be careful!
- ### Utilities
    Utilities are pure-Python implementations of graphical elements, such as option bars or sliders. Currently, they are rather limited as the library is still under development.

## Contributing
I am a solo developer, and as such, I may not be able to think of every feature needed on my own. So I welcome feedback and suggestions! If you do have feedback, open an issue. 
As a side note: I do not want this repository to be overwhelmed with pull requests, so please refrain from doing so unless you have a major change or idea.

## License
This project is licensed under the MIT License - see the LICENSE file for details.
