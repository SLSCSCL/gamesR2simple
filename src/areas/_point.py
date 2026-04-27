from ._base_area import BaseArea
from ._operators import Operators

class Point(BaseArea, Operators):
    def __init__(self, x, y):
        self.point = (x, y)
