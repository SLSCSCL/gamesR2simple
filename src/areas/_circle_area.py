from ._base_area import BaseArea
from ._operators import Operators

class CircleArea(BaseArea, Operators):
    def __init__(self, center_x, center_y, radius, anchor="center"):
        if anchor == "topleft":
            center_x += radius
            center_y += radius
        
        super().__init__(center_x, center_y)
        self.r = radius
        self._calculate()

    def _get_x_y(self):
        r_squared = self.r * self.r
        for y in range(self.y - self.r, self.y + self.r + 1):
            dy = y - self.y
            dx_limit = int((r_squared - dy * dy) ** 0.5)
            for x in range(self.x - dx_limit, self.x + dx_limit + 1):
                yield x, y

    def _get_outline_x_y(self):
        x = 0
        y = self.r
        d = 1 - self.r  # Initial decision parameter

        cx = self.x
        cy = self.y

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
