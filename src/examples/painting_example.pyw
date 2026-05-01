from gamesR2simple import (
    BaseGameWindow,
    run,
    MouseEvents,
    set_update_order,
    UpdateOrder
)
from gamesR2simple.areas import BaseArea, CircleArea, Line, RectArea
from gamesR2simple.utilities import Button, SameOptionsBar, Slider

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
    def setup(self):
        self.create_window("Painting example", 800, 400)
        self.window.set_maximized()

        self.color = (255, 0, 0)
        
        self.shape = "circ"
        self.size = 65
        self.shape_changed = False
        
        self.width, self.height = self.window.get_size()
        self.option_height = self.height // (len(colors) + 2)
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
            {
                "color": (100, 100, 100),
                "area": RectArea(self.width / 2 - 45, 10, 30, 30),
                "value": "rect"
            },
            {
                "color": (100, 100, 100),
                "area": CircleArea(self.width / 2 + 45, 10, 15, "topleft"),
                "value": "circ"
            },
            item_type = BaseArea,
            starting_index = 1
        )
        self.slider = Slider(
            range(1, 100),
            Line(
                200,
                self.height - 25,
                self.width - 200,
                self.height - 25
            ),
            CircleArea,
            (0, 255, 255),
            slider_default_index=50,
            radius=15
        )
        #self.set_bg = Button(RectArea)

        #Events should draw first, so they don't go over the GUI
        set_update_order(UpdateOrder.EVENTS_FIRST)
        
        self.events.add_mouse_event(MouseEvents.L_CLICK, self._draw_square)
        self.events.add_mouse_event(MouseEvents.L_DRAG, self._draw_square)

        self.events.add_utility_mouse_event(
            *self.color_selec.enter_click_data(
                MouseEvents.L_CLICK,
                self._set_color
            )
        )
        self.events.add_utility_scroll_event(
            *self.color_selec.enter_scroll_data(self._set_color)
        )

        self.events.add_utility_mouse_event(
            *self.shape_selec.enter_click_data(
                MouseEvents.L_CLICK,
                self._set_shape
            )
        )

        self.events.add_utility_mouse_event(
            *self.slider.enter_click_data(
                MouseEvents.L_CLICK,
                self._set_size
            )
        )
        self.events.add_utility_mouse_event(
            *self.slider.enter_drag_data(
                MouseEvents.L_DRAG,
                self._set_size
            )
        )

    def _set_color(self, i):
        self.color = colors[i]
        self.shape_changed = True

    def _set_size(self, size):
        self.size = size
        self.shape_changed = True

    def _set_shape(self, shape):
        self.shape = shape
        self.shape_changed = True

    def _draw_square(self, x, y):
        if not self.shape_changed:
            self.window.set_color(*self.color)
            half = self.size // 2
            if self.shape == "rect":
                self.window.fill_rect(x - half, y - half, self.size, self.size)
            else:
                self.draw.area(CircleArea(x, y, half))
        else:
            self.shape_changed = False

    def update(self):
        self.window.set_color(0, 0, 0)
        self.window.fill_rect(0, 0, self.width, 50)
        self.window.fill_rect(0, self.height - 50, self.width, 50)
        self.window.fill_rect(self.width - 50, 0, 50, self.height)

        #Draw utilities
        self.draw.option_bar(self.color_selec)
        self.draw.option_bar(self.shape_selec)
        self.draw.slider(self.slider)

        #Draw an outline around the current selections
        self.window.set_color(153, 153, 153)
        self.window.stroke_rect(
            self.width - 30,
            self.option_height * (self.color_selec.i + 1),
            15,
            self.option_height
        )
        self.draw.outline_area(self.shape_selec.get_mapping()["area"])

        #Save the screen
        self.window.save()

run()
