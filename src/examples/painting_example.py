from gamesR2simple import (
    BaseGameWindow,
    run,
    MouseEvents,
    set_update_order,
    UpdateOrder
)
from gamesR2simple.areas import BaseArea, CircleArea, RectArea
from gamesR2simple.utilities import SameOptionsBar

colors = (
    (255, 0, 0),
    (255, 127, 0),
    (255, 255, 0),
    (0, 255, 0),
    (0, 127, 255),
    (0, 0, 255),
    (255, 0, 255),
    (255, 255, 255),
    (0, 0, 0)
)

class Game(BaseGameWindow):
    color = (255, 0, 0)
    
    def setup(self):
        self.create_window("Painting example", 800, 400)
        self.window.set_maximized()

        self.shape = "circ"
        self.shape_changed = False
        
        self.width, height = self.window.get_size()
        self.option_height = int(height / (len(colors) + 2))
        self.color_selec = SameOptionsBar(
            [
                {
                    "color": colors[i],
                    "area": RectArea(
                        self.width - 30,
                        (i + 1) * self.option_height,
                        15,
                        self.option_height
                    )
                }
                for i in range(len(colors))
            ],
            item_type = RectArea
        )
        self.shape_selec = SameOptionsBar(
            [
                {
                    "color": (153, 153, 153),
                    "area": RectArea(self.width / 2 - 45, 10, 30, 30),
                    "value": "rect"
                },
                {
                    "color": (153, 153, 153),
                    "area": CircleArea(self.width / 2 + 45, 10, 15, "topleft"),
                    "value": "circ"
                }
            ],
            item_type = BaseArea
        )

        set_update_order(UpdateOrder.EVENTS_FIRST)
        
        self.events.add_mouse_event(MouseEvents.L_CLICK, self._draw_square)
        self.events.add_mouse_event(MouseEvents.L_DRAG, self._draw_square)

        self.events.add_utility_mouse_event(
            *self.color_selec.enter_click_data(MouseEvents.L_CLICK)
        )
        self.events.add_utility_scroll_event(
            *self.color_selec.enter_scroll_data()
        )

        self.events.add_utility_mouse_event(
            *self.shape_selec.enter_click_data(
                MouseEvents.L_CLICK,
                self._set_shape
            )
        )

    def _set_shape(self, shape):
        self.shape = shape
        self.shape_changed = True

    def _draw_square(self, x, y):
        if not self.shape_changed:
            self.window.set_color(*colors[self.color_selec.i])
            if self.shape == "rect":
                self.window.fill_rect(x - 50, y - 50, 100, 100)
            else:
                self.draw.area(CircleArea(x, y, 50))
        else:
            self.shape_changed = False

    def update(self):
        self.draw.option_bar(self.color_selec)
        self.draw.option_bar(self.shape_selec)
        self.window.set_color(153, 153, 153)
        self.window.stroke_rect(
            self.width - 30,
            self.option_height * (self.color_selec.i + 1),
            15,
            self.option_height
        )
        self.window.save()

run()
