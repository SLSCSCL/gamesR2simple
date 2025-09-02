from math import floor
from random import randint

from gamesR2simple import BaseGame, keys

class Game(BaseGame):
    def setup(self):
        self.fps = 0
        self.set_fullscreen()
        self.events.add_quit_event(keys["Escape"])
        width, height = self.screen.get_size()
        self.draw.fill_style = (255, 0, 0)
        self.max_x = floor(width / 25) - 2
        self.max_y = floor(height / 25) - 2
        
    def update(self):
        self.draw.fill_rect(
            randint(0, self.max_x) * 25,
            randint(0, self.max_y) * 25,
            50,
            50
        )

if __name__ == "__main__":
    game = Game()
