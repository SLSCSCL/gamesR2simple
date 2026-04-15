from .areas import RectArea

class Draw:
    def __init__(self, window):
        self.window = window

    def area(self, area):
        if type(area) is RectArea:
            self.window.fill_rect(area.x, area.y, area.width, area.height)
        
        for point in area.points:
            self.window.point(point[0], point[1])

    def utility(self, utility):
        utility.draw(self.window)
