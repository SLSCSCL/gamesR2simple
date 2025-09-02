"""
A very simple game demonstratig the use of gamesR2simple.areas.Area
"""
from gamesR2simple import BaseGame, keys
from gamesR2simple.areas import Area, Lines, Line

class Game(BaseGame):
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
        self.events.add_quit_event(keys["Escape"])
        
    def update(self):
        self.draw.fill_style = (255, 255, 0)
        self.draw.fill_area(self.area)

        self.draw.fill_style = (255, 0, 0)
        for point in self.area.outline:
            self.draw.fill_rect(point[0], point[1], 1, 1)

if __name__ == "__main__":
    game = Game()

