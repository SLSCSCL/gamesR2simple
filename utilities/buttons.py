from .._legends import pressed_btns
from ._base_utilities import BaseClickableUtility

def _do_nothing():
    pass

class Button(BaseClickableUtility):
    def __init__(self, area):
        super().__init__()
        self.area = area
        self._callbacks = {
            "left": _do_nothing,
            "mid": _do_nothing,
            "right": _do_nothing,
        }

    def _click_callback(self, mouse_pos):
        if self.area.collision(mouse_pos):
            if pressed_btns["left"]:
                self._callbacks["left"]()
            elif pressed_btns["mid"]:
                self._callbacks["mid"]()
            elif pressed_btns["right"]:
                self._callbacks["right"]()

    def draw(self, draw_area):
        draw_area(self.area)
