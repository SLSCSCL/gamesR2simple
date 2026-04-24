from ._base_option_bar import BaseOptionBar

from .. import MouseEvents

from ..areas._base_area import BaseArea
from ..areas import RectArea

class SameOptionsBar(BaseOptionBar):
    def __init__(self, *mapping, item_type, starting_index = 0):
        if len(mapping) == 1:
            mapping = mapping[0]
        super().__init__(mapping, starting_index)
        
        if issubclass(item_type, BaseArea):
            self._left_click = lambda coord: \
                self._area_collision(coord, MouseEvents.L_CLICK)
            self._right_click = lambda coord: \
                self._area_collision(coord, MouseEvents.R_CLICK)
            self._wheel_click = lambda coord: \
                self._area_collision(coord, MouseEvents.WHL_CLICK)
            
            self.draw = self._draw_areas
        #image support soon

    def _area_collision(self, coord, event):
        for i in range(len(self._mapping)):
            if self._mapping[i]["area"].collision(coord):
                self.i = i
                self._click_callbacks[event](self._get_param())

    def _draw_areas(self, set_color, draw_area):
        for item in self._mapping:
            set_color(*item["color"])
            draw_area(item["area"])
