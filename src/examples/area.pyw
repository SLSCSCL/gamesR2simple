from gamesR2simple import BaseGameWindow, keys, run
from gamesR2simple.areas import Area, Lines, Line

class Game(BaseGameWindow):
    area = Area(
        Lines(
            Line(25, 0, 0, 50),  # /
            Line(0, 50, 25, 100) # \
        ),
        Lines(
            Line(75, 0, 100, 50),  # \
            Line(100, 50, 75, 100) # /
        )
    )
    
    def setup(self):
        self.create_window("Area example", 800, 400)
        
    def update(self):
        self.window.set_color(255, 255, 0)
        self.draw.area(self.area)

        self.window.set_color(255, 0, 0)
        for point in self.area.outline:
            self.window.point(point[0], point[1])

run()
