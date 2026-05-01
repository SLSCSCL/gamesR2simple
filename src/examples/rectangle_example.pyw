from gamesR2simple import BaseGameWindow, run, MouseEvents
from gamesR2simple.areas import RectArea

class Game(BaseGameWindow):
    def click_rectangle(self, x, y):
        self.mouse_clicked_rect = self.rect.collision((x, y))
        if self.mouse_clicked_rect:
            self.move_rectangle(x, y)
    
    def move_rectangle(self, x, y):
        if self.mouse_clicked_rect:
            self.rect.set_coords(
                x - self.rect.width / 2,
                y - self.rect.height / 2
            )
    
    def setup(self):
        self.rect = RectArea(0, 0, 100, 100)
        self.create_window("Rectangle area example", 800, 400)
        self.events.add_mouse_event(MouseEvents.L_CLICK, self.click_rectangle)
        self.events.add_mouse_event(MouseEvents.L_DRAG, self.move_rectangle)
        
    def update(self):
        self.window.set_color(255, 255, 0)
        self.draw.area(self.rect)

        self.window.set_color(255, 0, 0)
        self.draw.outline_area(self.rect)

run()
