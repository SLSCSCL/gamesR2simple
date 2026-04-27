from ._lines import Line, Lines

class BaseArea:
    def __init__(self, x, y):
        self.x = int(x)
        self.y = int(y)
        self.points, self.outline = set(), set()
    
    def _calculate(self):
        self.outline = {
            coords
            for coords in self._get_outline_x_y()
        }
        self.points = {coords for coords in self._get_x_y()}
    
    def collision(self, obj):
        if isinstance(obj, tuple):
            return obj in self.points
        elif isinstance(obj, set):
            return bool(self.points.intersection(obj))
        elif isinstance(obj, (BaseArea, Line)):
            return bool(self.points.intersection(obj.points))
        elif isinstance(obj, Lines):
            for line in obj:
                if (line.get_x(y), y) in self.points:
                    return True
            return False
        
        raise TypeError(
            f"Cannot determine collisions with objects of type '{type(obj)}'"
        )
    
    def set_x(self, new_x):
        self.x = new_x
        self._calculate()

    def set_y(self, new_y):
        self.y = new_y
        self._calculate()
    
    def shift_x(self, delta):
        self._x += delta
        self._calculate()

    def shift_y(self, delta):
        self.y += delta
        self._calculate()

    def set_coords(self, x, y):
        if not isinstance(x, (int, float)):
            raise TypeError("The x coordinate must be of type int or float!")
        elif not isinstance(y, (int, float)):
            raise TypeError("The y coordinate must be of type int or float!")
        
        self.x = int(x)
        self.y = int(y)
        self._calculate()
