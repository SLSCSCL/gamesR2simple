from gamesR2simple import BaseGame, keys

class Game(BaseGame):
    def setup(self):
        self.events.add_mouse_key_combination(keys["x"], self.destroy)
        
    def update(self):
        pass

if __name__ == "__main__":
    game = Game()
