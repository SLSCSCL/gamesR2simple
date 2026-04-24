from gamesR2simple import BaseGameWindow, run, keys, KeyCombination, quit

class Game(BaseGameWindow):
    def setup(self):
        self.create_window("Key combination events example", 800, 400)
        self.events.add_key_combination(
            KeyCombination(
                keys["Left Ctrl"],
                keys["F4"],
                quit
            )
        )
        self.events.add_key_combination(
            KeyCombination(
                keys["Right Ctrl"],
                keys["F4"],
                quit
            )
        )

    def update(self):
        pass

run()
