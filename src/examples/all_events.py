from gamesR2simple import (
    BaseGameWindow,
    run,
    MouseEvents,
    KeyEvents,
    keys,
    KeyCombination,
    MouseKeyCombination
)

class Game(BaseGameWindow):
    def l_click(self, x, y):
        print(f"Left click at ({x}, {y})!")
    
    def r_click(self, x, y):
        print(f"Right click at ({x}, {y})!")
    
    def whl_click(self, x, y):
        print(f"Wheel click at ({x}, {y})!")
    
    def l_drag(self, x, y):
        print(f"Left drag to ({x}, {y})!")
    
    def r_drag(self, x, y):
        print(f"Right drag to ({x}, {y})!")
    
    def whl_drag(self, x, y):
        print(f"Wheel drag to ({x}, {y})!")
    
    def back_thumb(self, x, y):
        print(f"Back thumb click at ({x}, {y})!")
    
    def fwd_thumb(self, x, y):
        print(f"Back thumb click at ({x}, {y})!")
    
    def mousemove(self, x, y):
        print(f"Mouse moved to ({x}, {y})!")
    
    def mouseup(self, x, y):
        print(f"Mouse up at ({x}, {y})!")
    
    def setup(self):
        self.create_window("Hello, World!", 800, 400)

        #All possible mouse events
        self.events.add_mouse_event(MouseEvents.L_CLICK, self.l_click)
        self.events.add_mouse_event(MouseEvents.R_CLICK, self.r_click)
        self.events.add_mouse_event(MouseEvents.WHL_CLICK, self.whl_click)

        self.events.add_mouse_event(MouseEvents.L_DRAG, self.l_drag)
        self.events.add_mouse_event(MouseEvents.R_DRAG, self.r_drag)
        self.events.add_mouse_event(MouseEvents.WHL_DRAG, self.whl_drag)

        self.events.add_mouse_event(MouseEvents.BACK_THUMB, self.back_thumb)
        self.events.add_mouse_event(MouseEvents.FWD_THUMB, self.fwd_thumb)
        
        self.events.add_mouse_event(MouseEvents.MOUSE_MOVE, self.mousemove)
        self.events.add_mouse_event(MouseEvents.MOUSE_UP, self.mouseup)

    def update(self):
        pass

run()
