from ._base_area import BaseArea
from ._operators import Operators

class RectArea(BaseArea, Operators):
    def __init__(self, x, y, width, height):
        super().__init__(x, y)
        self._width = int(width)
        self._height = int(height)
        self._calculate()

    def _get_x_y(self):
        for y in range(self._y, self._y + self._height + 1):
            for x, y in (
                    (x, y)
                    for x in range(self._x, self._x + self._width + 1)
                ):
                yield x, y

    def _get_outline_x_y(self):
        for y in range(self._y, self._y + self._height + 1, self._height):
            for x, y in (
                    (x, y)
                    for x in range(self._x, self._x + self._width + 1)
                ):
                yield x, y
