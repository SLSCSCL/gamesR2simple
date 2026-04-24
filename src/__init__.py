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
    "KeyEvents",
    "KeyCombination",
    "MouseKeyCombination"
]

_run = run #Overwritten

class BaseGameWindow(ABC):
    _game_windows = []

    def __init_subclass__(cls):
        super().__init_subclass__()
        BaseGameWindow._game_windows.append(cls)
    
    def __init__(self):
        arg_count = self.update.__code__.co_argcount
        if self.update.__self__ is not None:
            arg_count -= 1

        self._UPDATE_NEEDS_DT = arg_count == 1
        
        self.active = True
        self.setup()

    def _get_update(self):
        def update():
            if self.active:
                if self._UPDATE_NEEDS_DT:
                    return self.update(dt)
                self.update()
        
        return update
    
    def create_window(
        self,
        name = "gamesR2simple window",
        width = 200,
        height = 100
    ):
        self.window, self.events = create_window(name, width, height)
        self.draw = Draw(self.window)

    def go_dormant(self):
        self.window.destroy()
        self.active = False

def run(fps = 60):
    start()
    
    game_windows = [cls() for cls in BaseGameWindow._game_windows]
    for game in game_windows:
        if game.active:
            add_update_func(game.window, game._get_update())

    _run()
