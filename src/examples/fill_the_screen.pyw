from math import floor
from random import randint

from gamesR2simple import BaseGameWindow, run, keys
from gamesR2simple.areas import RectArea

class Game(BaseGameWindow):
    def create_rand_rect(self):
        width, height = self.window.get_size()
        
        max_x = floor(width / 25)
        max_y = floor(height / 25)

        self.rects.add((randint(0, max_x) * 25, randint(0, max_y) * 25))
    
    def setup(self):
        self.create_window("Fill the screen", 800, 400)
        self.window.set_resizable()

        self.rects = set()
        self.create_rand_rect()
        
    def update(self):
        self.create_rand_rect()
        self.window.set_color(255, 0, 0)
        for rect in self.rects:
            self.window.fill_rect(rect[0], rect[1], 50, 50)

run()
