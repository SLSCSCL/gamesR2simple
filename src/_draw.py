from .areas import RectArea

class Draw:
    def __init__(self, window):
        self.window = window

    def area(self, area):
        if type(area) == RectArea:
            self.window.fill_rect(area.x, area.y, area.width, area.height)
        
        for point in area.points:
            self.window.point(point[0], point[1])

    def outline_area(self, area):
        if type(area) == RectArea:
            self.window.stroke_rect(area.x, area.y, area.width, area.height)
        
        for point in area.outline:
            self.window.point(point[0], point[1])

    def _utility(self, utility, *funcs):
        utility.draw(self.window.set_color, *funcs)

    def option_bar(self, utility):
        self._utility(utility, self.area)

    def slider(self, utility):
        self._utility(utility, self.window.draw_line, self.area)

    def button(self, utility):
        self._utility(utility, self.area)
