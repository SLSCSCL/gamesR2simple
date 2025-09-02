from gamesR2simple import BaseGame, keys
from gamesR2simple.areas import CircleArea

class Game(BaseGame):
    circle = CircleArea(50, 50, 50)
    def __init__(self):
        super().__init__()
        self.events.add_quit_event(keys["Escape"])
        self.run()

    def update(self):
        self.draw.fill_style = (255, 255, 0)
        for point in self.circle.points:
            self.draw.fill_rect(point[0], point[1], 1, 1)

        self.draw.fill_style = (255, 0, 0)
        for point in self.circle.outline:
            self.draw.fill_rect(point[0], point[1], 1, 1)

if __name__ == "__main__":
    game = Game()
