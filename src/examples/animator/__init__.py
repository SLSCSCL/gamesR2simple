from gamesR2simple import BaseGame, keys

from project_handler import *

class Game(BaseGame):
    def setup(self):
        self.drawing = {
            "kind": "c",
            "radius": 5
        }
        
        self.set_screen_size(1000, 700)
        
        self.events.add_quit_event(keys["Escape"])
        self.events.add_mouse_event("move", self._plot)
        self.events.add_mouse_event("down", self._plot)
        
        self.draw.fill_style = (255, 255, 255)

    def _plot(self, pos):
        if pos[0] > 200 and pos[1] < 500:
            match self.drawing["kind"]:
                case "r":
                    self.draw.fill_rect(
                        pos[0],
                        pos[1],
                        self.drawing["width"],
                        self.drawing["height"]
                    )
                case "c":
                    self.draw.fill_circle(
                        pos[0],
                        pos[1],
                        self.drawing["radius"]
                    )

    def update(self):
        self.draw.stroke_style = (100, 100, 100)
        self.draw.line_width = 5
        self.draw.stroke_rect(200, 0, 800, 500)

if __name__ == "__main__":
    Game()
