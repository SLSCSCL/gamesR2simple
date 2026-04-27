from ._base_area import BaseArea
from ._lines import Lines, Line
from ._operators import Operators

class Area(BaseArea, Operators):
    def __init__(self, left_lines, right_lines):
        if type(left_lines) != Lines:
            raise TypeError("left_lines argument must be of type 'Lines'")
        self._left_lines = left_lines
        
        if type(right_lines) != Lines:
            raise TypeError("right_lines argument must be of type 'Lines'")
        self._right_lines = right_lines

        self._calculate()

    def _get_x_y(self):
        #Iterate over all the lines on the left
        for line in self._left_lines:
            #Iterate over each y value on the current line
            for y in range(int(line.y1), int(line.y2) + 1):
                #Get a coordinate
                for x, y in (
                        (x, y)
                        #Iterate through a range of x values with the current y
                        for x in range(
                            #Smallest or leftmost x
                            line.get_x(y),
                            #Largest or rightmost x
                            self._right_lines.get_x(y) + 1
                        )
                    ):
                    yield x, y

    def _get_outline_x_y(self):
        #Left edge
        for line in self._left_lines:
            for x, y in line.get_points():
                #Because of the way y is calculated, it will likely be a float
                yield x, int(y)

        #Right edge
        for line in self._right_lines:
            for x, y in line.get_points():
                #Because of the way y is calculated, it will likely be a float
                yield x, int(y)

        #Gather y-ranges
        min_y = int(min(line.y1 for line in self._left_lines + self._right_lines))
        max_y = int(max(line.y2 for line in self._left_lines + self._right_lines))

        #Top edge
        try:
            x1 = self._left_lines.get_x(min_y)
            x2 = self._right_lines.get_x(min_y)
            for x in range(x1, x2 + 1):
                yield x, y
        except ValueError:
            pass

        #Bottom edge
        try:
            x1 = self._left_lines.get_x(max_y)
            x2 = self._right_lines.get_x(max_y)
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
