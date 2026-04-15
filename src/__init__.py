from abc import ABC, abstractmethod

from ._cpp import *
from ._draw import Draw
#from . import areas, utilities

__all__ = [
    "areas",
    "utilities",
    "BaseGameWindow",
    "run",
    "MouseEvents",
    "KeyEvents"
]

_run = run #Overwritten

class BaseGameWindow(ABC):
    _game_windows = []

    def __init_subclass__(cls):
        super().__init_subclass__()
        BaseGameWindow._game_windows.append(cls)
    
    def __init__(self):
        self.active = True
        self.setup()

    def _get_update(self):
        return self.update
    
    def create_window(self, name, width = 200, height = 100):
        self.window, self.events = create_window(name, width, height)
        self.draw = Draw(self.window)

    def go_dormant(self):
        self.window.destroy()
        self.active = False

    @abstractmethod
    def setup(self):
        pass

    @abstractmethod
    def update(self):
        pass

def run():
    game_windows = [cls() for cls in BaseGameWindow._game_windows]
    for game in game_windows:
        if game.active:
            add_update_func(game._get_update())

    _run()
