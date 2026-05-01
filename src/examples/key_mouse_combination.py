from gamesR2simple import BaseGameWindow, run, keys, MouseKeyCombination#, quit

class Game(BaseGameWindow):
    def setup(self):
        self.create_window("Mouse-key event combination example", 800, 400)
        self.events.add_mouse_key_combination(
            MouseKeyCombination(keys["x"], lambda x, y: print("x-click"))#quit) #doesn't work - throws an error, will fix soon
        )
        
    def update(self):
        pass

run()
