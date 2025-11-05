from gamesR2simple import BaseGame, keys, convert
from gamesR2simple.areas import RectArea
from gamesR2simple.utilities import OptionBar

colors = (
    (255, 0, 0),
    (255, 127, 0),
    (255, 255, 0),
    (0, 255, 0),
    (0, 127, 255),
    (0, 0, 255),
    (255, 0, 255),
    (255, 255, 255)
)

class Game(BaseGame):
    color = (255, 0, 0)
    
    def setup(self):
        #self.set_fullscreen()
        self.width, height = self.screen.get_size()
        self.option_height = height / (len(colors) + 2)
        self.selector = OptionBar([
            {
                "fill_style": colors[i],
                "x": self.width - 30,
                "y": (i + 1) * self.option_height,
                "width": 15,
                "height": self.option_height
            }
            for i in range(len(colors))
        ])

        self.i = 0
        self._add_events()
        self._set_drawing_properties()

    def _add_events(self):
        self.events.add_quit_event(keys["Escape"])
        self.events.add_mouse_event("down", self._draw_square)
        self.events.add_mouse_event("move", self._draw_square)
        self.events.add_mouse_event("scrollup", self._shift_selection_up)
        self.events.add_mouse_event("scrolldown", self._shift_selection_down)

        self.selector.register_event_handler(self.events)
        self.selector.attach_click_event(self._change_selection)
        self.selector.attach_scroll_event("up", self._shift_selection_up)
        self.selector.attach_scroll_event("down", self._shift_selection_down)
        
    def _set_drawing_properties(self):
        self.draw.fill_style = colors[self.i]
        self.draw.stroke_style = convert.hex_to_rgb("#999999")
        self.draw.line_width = 2

    def _change_selection(self, i):
        self.i = i

    def _shift_selection_up(self):
        if self.i > 0:
            self.i -= 1

    def _shift_selection_down(self):
        if self.i < len(colors) - 1:
            self.i += 1

    def _draw_square(self, pos):
        if pos[0] < self.width - 45:
            self.draw.anchor = self.draw.CENTER
            self.draw.fill_style = colors[self.i]
            self.draw.fill_rect(pos[0], pos[1], 100, 100)

    def _draw_selection(self):
        self.draw.anchor = self.draw.TOP_LEFT
        self.draw.draw_option_bar(self.selector, color_mapping=colors)
        self.draw.stroke_rect(
            self.width - 30,
            self.option_height * (self.i + 1),
            15,
            self.option_height
        )

    def update(self):
        self._draw_selection()

if __name__ == "__main__":
    game = Game()
