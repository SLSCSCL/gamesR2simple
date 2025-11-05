from ._base_area import BaseArea, q
from ._operators import Operators

class CircleArea(BaseArea, Operators):
    def __init__(self, center_x, center_y, r, anchor="center"):
        if anchor == "topleft":
            center_x += r
            center_y += r
        
        super().__init__(center_x, center_y)
        self._r = r
        self._calculate()

    def _get_x_y(self):
        r_squared = self._r * self._r
        for y in range(self._y - self._r, self._y + self._r + 1):
            dy = y - self._y
            dx_limit = int((r_squared - dy * dy) ** 0.5)
            for x in range(self._x - dx_limit, self._x + dx_limit + 1):
                yield x, y

    def _get_outline_x_y(self):
        x = 0
        y = self._r
        d = 1 - self._r  # Initial decision parameter

        cx = self._x
        cy = self._y

        while x <= y:
            # 8-way symmetry
            yield cx + x, cy + y
            yield cx - x, cy + y
            yield cx + x, cy - y
            yield cx - x, cy - y
            yield cx + y, cy + x
            yield cx - y, cy + x
            yield cx + y, cy - x
            yield cx - y, cy - x

            if d < 0:
                d += 2 * x + 3
            else:
                d += 2 * (x - y) + 5
                y -= 1
            x += 1
