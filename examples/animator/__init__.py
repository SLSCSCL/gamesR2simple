from gamesR2simple import BaseGame

from .file_loader import FileLoader

class Game(BaseGame):
    def setup(self):
        self.set_screen_size(1000, 700)

    def update(self):
        pass

if __name__ == "__main__":
    Game()
