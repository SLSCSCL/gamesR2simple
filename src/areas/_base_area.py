from .._cpp.quit import q

from ._lines import Line, Lines

class BaseArea:
    points, outline = set(), set()

    def __init__(self, x, y):
        self._x = int(x)
        self._y = int(y)
    
    def _calculate(self):
        self.outline = {
            coords
            for coords in self._get_outline_x_y()
        }
        self.points = {
            coords
            for coords in [
                line
                for line in self._get_x_y()
            ]
        }
    
    def collision(self, other):
        if isinstance(other, (BaseArea, Line)):
            return bool(self.points.intersection(other.points))
        elif isinstance(other, Lines):
            for line in other:
                if (line.get_x(y), y) in self.points:
                    return True
            return False
        elif isinstance(other, set):
            return bool(self.points.intersection(other))
        elif isinstance(other, tuple):
            return other in self.points
        
        q()
        raise TypeError(
            f"Cannot determine collisions with objects of type '{type(other)}'"
        )
    
    def set_x(self, new_x):
        self._x = new_x
        self._calculate()

    def set_y(self, new_y):
        self._y = new_y
        self._calculate()
    
    def shift_x(self, delta):
        self._x += delta
        self._calculate()

    def shift_y(self, delta):
        self._y += delta
        self._calculate()

    def set_coords(self, coords):
        if not isinstance(coords, (tuple, list)):
            q()
            raise TypeError(
                "Argument 'coords' must be of type 'list' or 'tuple'"
            )
        self._x = coords[0]
        self._y = coords[1]
        self._calculate()
