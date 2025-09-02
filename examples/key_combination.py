from gamesR2simple import BaseGame, keys

class Game(BaseGame):
    def setup(self):
        self.events.add_key_combination(
            keys["Left-hand ctrl"],
            keys["F4"],
            self.destroy
        )
        self.events.add_key_combination(
            keys["Right-hand ctrl"],
            keys["F4"],
            self.destroy
        )

    def update(self):
        pass

if __name__ == "__main__":
    game = Game()
