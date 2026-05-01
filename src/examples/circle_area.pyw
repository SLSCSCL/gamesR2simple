from gamesR2simple import BaseGameWindow, run
from gamesR2simple.areas import CircleArea

class Game(BaseGameWindow):
    circle = CircleArea(50, 50, 50)
    def setup(self):
        self.create_window("Circle area example", 800, 400)

    def update(self):
        self.window.set_color(255, 255, 0)
        self.draw.area(self.circle)

        self.window.set_color(255, 0, 0)
        self.draw.outline_area(self.circle)

run()
