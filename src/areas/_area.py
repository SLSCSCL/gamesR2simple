from ._base_area import BaseArea, q
from ._lines import Lines, Line
from ._operators import Operators

class Area(BaseArea, Operators):
    def __init__(self, left_lines, right_lines):
        if type(left_lines) != Lines:
            q()
            raise TypeError("left_lines argument must be of type 'Lines'")
        self._left_lines = left_lines
        
        if type(right_lines) != Lines:
            q()
            raise TypeError("right_lines argument must be of type 'Lines'")
        self._right_lines = right_lines

        self._calculate()

    def _get_x_y(self):
        for line in self._left_lines:
            for y in range(int(line.y1), int(line.y2) + 1):
                for x, y in (
                        (x, y)
                        for x in range(
                            line.get_x(y),
                            self._right_lines.get_x(y) + 1
                        )
                    ):
                    yield x, y

    def _get_outline_x_y(self):
        # LEFT EDGE
        for line in self._left_lines:
            for x, y in line.get_points():
                yield x, int(y)

        # RIGHT EDGE
        for line in self._right_lines:
            for x, y in line.get_points():
                yield x, int(y)

        # Gather y-ranges
        min_y = int(min(line.y1 for line in self._left_lines + self._right_lines))
        max_y = int(max(line.y2 for line in self._left_lines + self._right_lines))

        # TOP EDGE
        for y in range(min_y, min_y + 1):
            try:
                x1 = self._left_lines.get_x(y)
                x2 = self._right_lines.get_x(y)
                for x in range(x1, x2 + 1):
                    yield x, y
            except ValueError:
                pass

        # BOTTOM EDGE
        for y in range(max_y, max_y + 1):
            try:
                x1 = self._left_lines.get_x(y)
                x2 = self._right_lines.get_x(y)
                for x in range(x1, x2 + 1):
                    yield x, y
            except ValueError:
                pass


    def shift_x(self, delta):
        for line in self._left_lines:
            line.x1 += delta
            line.x2 += delta
            line.calculate()
            
        for line in self._right_lines:
            line.x1 += delta
            line.x2 += delta
            line.calculate()

        self._calculate()

    def shift_y(self, delta):
        for line in self._left_lines:
            line.y1 += delta
            line.y2 += delta
            line.calculate()
        
        for line in self._right_lines:
            line.x1 += delta
            line.x2 += delta
            line.calculate()

        self._calculate()
