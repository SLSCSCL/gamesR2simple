from ._base_area import BaseArea

#Operators has to be defined in this file to avoid an ImportError
#due to a circular import - BaseArea should have the class Operators , but it then
#import CombinedArea from here, which extends BaseArea
class Operators:
    class Area(BaseArea):
        def __init__(self, points):
            self.points = points
    def __add__(self, other):
        return CombinedArea(self, other)

    def __radd__(self, other):
        return CombinedArea(self, other)

    def __eq__(self, other):
        return self.points == other.points

    def __ne__(self, other):
        return self.points != other.points

    def __lt__(self, other):
        return len(self.points) < len(other.points)

    def __le__(self, other):
        return len(self.points) <= len(other.points)
    
    def __gt__(self, other):
        return len(self.points) > len(other.points)
    
    def __ge__(self, other):
        return len(self.points) >= len(other.points)

    def __iter__(self):
        return self.points.__iter__()

    def __repr__(self):
        return "".join([f"({x}, {y})\n" for x, y in self.points])

    def rotate(self, theta):
        #Rotation matrix:
        # | cos(a) -sin(a) 0 |
        # | sin(a)  cos(a) 0 |
        # | 0         0    1 |
        #Thus:
        # p_rotated = (xcos(a) + ysin(a), -xsin(a) + ycos(a)
        pass

class CombinedArea(BaseArea, Operators):
    def __init__(self, *areas):
        for area in areas:
            self.points = self.points.union(area.points)
