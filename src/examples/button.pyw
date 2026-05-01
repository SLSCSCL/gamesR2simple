from random import randint

from gamesR2simple import BaseGameWindow, run, MouseEvents
from gamesR2simple.areas import CircleArea
from gamesR2simple.utilities import Button

class Game(BaseGameWindow):
    def setup(self):
        self.create_window("Button example", 800, 400)
        self.button = Button(CircleArea(100, 100, 50), (0, 255, 255))
        
        self.events.add_utility_mouse_event(
            *self.button.enter_click_data(
                MouseEvents.L_CLICK,
                self._change_button_color
            )
        )

    def _change_button_color(self):
        self.button.color = (
            randint(0, 255),
            randint(0, 255),
            randint(0, 255),
            randint(0, 255)
        )

    def update(self):
        self.draw.button(self.button)
        
run()
