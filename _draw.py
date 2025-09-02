from ._cpp.draw import draw, Rect
from .areas import RectArea

class Draw:
    CENTER = "center"
    TOP_LEFT = "top-left"
    fill_style = (0, 0, 0)
    stroke_style = (0, 0, 0)
    line_width = 1
    def __init__(self, game):
        self.game = game
        self.anchor = self.TOP_LEFT

    def _check_line_width(self):
        if self.line_width <= 0:
            self.game.destroy(error=True)
            raise ValueError(
                "Draw.line_width cannot be 0!!!!"
            )

    def fill_rect(self, x, y, width, height):
        if self.anchor == self.CENTER:
            x -= width / 2
            y -= height / 2
        
        rect = Rect(x, y, width, height)
        draw.rect(self.game.screen, self.fill_style, rect)
    
    def stroke_rect(self, x, y, width, height):
        if self.anchor == self.CENTER:
            x -= width / 2
            y -= height / 2

        rect = Rect(x, y, width, height)
        self._check_line_width()
        draw.rect(
            self.game.screen,
            self.stroke_style,
            rect,
            width = self.line_width
        )

    def fill_circle(self, x, y, r):
        if self.anchor == self.TOP_LEFT:
            x += r
            y += r
        
        draw.circle(
            self.game.screen,
            self.fill_style,
            (x, y),
            r
        )

    def stroke_circle(self, x, y, r):
        if self.anchor == self.TOP_LEFT:
            x += r
            y += r

        self._check_line_width()
        draw.circle(
            self.game.screen,
            self.stroke_style,
            (x, y),
            r,
            self.line_width
        )

    def fill_ellipse(self, x, y, x_radius, y_radius):
        if self.anchor == self.TOP_LEFT:
            x += x_radius
            y += y_radius
        
        rect = Rect(
            x - x_radius,
            y - y_radius,
            x_radius * 2,
            y_radius * 2
        )
        draw.ellipse(
            self.game.screen,
            self.fill_style,
            rect
        )

    def stroke_ellipse(self, x, y, x_radius, y_radius):
        if self.anchor == self.TOP_LEFT:
            x += x_radius
            y += y_radius

        rect = Rect(
            x - x_radius,
            y - y_radius,
            x_radius * 2,
            y_radius * 2
        )
        self._check_line_width()
        draw.ellipse(
            self.game.screen,
            self.stroke_style,
            rect,
            self.line_width
        )

    def stroke_arc(self, x, y, width, height, start_angle, stop_angle):
        if self.anchor == self.CENTER:
            x -= width / 2
            y -= height / 2

        rect = Rect(
            x,
            y,
            width,
            height
        )
        draw.arc(
            self.game.screen,
            self.stroke_color,
            rect,
            start_angle,
            stop_angle,
            self.line_width
        )

    def fill_area(self, area):
        self._fill_points(area.points)

    def fill_rect_in_area(self, x, y, width, height, area):
        self._fill_points(
            area.points.intersection(
                RectArea(x, y, width, height).points
            )
        )

    def _fill_points(self, points):
        for point in points:
            self.fill_rect(point[0], point[1], 1, 1)

    def draw_option_bar(self, utility, color_mapping=None):
        mapping = utility.get_mapping()
        if not color_mapping:
            color_mapping = []
            for _ in range(len(mapping)):
                color_mapping.append(self.fill_style)
        
        for i in range(len(color_mapping)):
            self.fill_style = color_mapping[i]
            utility.draw(self, mapping[i])

    def draw_button(self, button):
        button.draw(self.fill_area)
