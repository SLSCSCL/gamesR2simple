from ._base_area import BaseArea
from ._operators import Operators

class RoundRectArea(BaseArea, Operators):
    def __init__(self, x, y, width, height, round_depths: dict):
        super().__init__(x, y)
        self._width = width
        self._height = height
        self._calculate()

    def _get_x_y(self):
        pass

    def _get_outline_x_y(self):
        pass
