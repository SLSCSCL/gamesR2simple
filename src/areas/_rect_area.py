from functools import singledispatchmethod

from ._base_area import BaseArea
from ._operators import Operators

class RectArea(BaseArea, Operators):
    def __init__(self, x, y, width, height):
        super().__init__(x, y)
        self.width = int(width)
        self.height = int(height)
        self._calculate()

    @singledispatchmethod
    def collision(self, obj):
        super().collision(obj)

    @collision.register
    def collision(self, coord: tuple):
        x, y = coord
        return x >= self.x and x <= self.x + self.width and \
               y >= self.y and y <= self.y + self.height
        
    def _get_x_y(self):
        for y in range(self.y, self.y + self.height + 1):
            for x in range(self.x, self.x + self.width + 1):
                yield x, y

    def _get_outline_x_y(self):
        for y in range(self.y, self.y + self.height + 1, self.height):
            for x, y in (
                    (x, y)
                    for x in range(self.x, self.x + self.width + 1)
                ):
                yield x, y
