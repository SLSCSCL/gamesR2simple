from gamesR2simple import BaseGame
from gamesR2simple.areas import CircleArea
from gamesR2simple.utilities.buttons import Button

class Game(BaseGame):
    def setup(self):
        self.draw.fill_style = (0, 255, 0)
        self.button = Button(CircleArea(100, 100, 50))
        self._add_events()

    def _add_events(self):
        self.button.register_event_handler(self.events)
        self.button.attach_click_event(self.destroy)

    def update(self):
        self.draw.draw_button(self.button)
        
g = Game()
