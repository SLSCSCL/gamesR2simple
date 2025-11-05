from ..areas import *
from ._base_utilities import BaseDragableUtility
from ._err_msgs import slider_errs

X_AXIS, Y_AXIS = 0, 1
CENTER, FRONT, END = -1, -2, -3

class Range(range):
    """Like range, except used for floating point numbers"""
    def __init__(self, start, stop=None, step=1):
        if stop is None:
            self.start, self.stop = 0, start
        else:
            self.start, self.stop, self.step = start, stop, step
        for n in range(int(abs(self.start - self.stop) / step)):
            self.append(self.start + step * n)

class Slider(BaseDragableUtility):
    def __init__(
        self,
        num_range,
        sliding_area,
        slider_area_type,
        slider_init_vals,
        slide_direction = X_AXIS,
        slider_anchor = CENTER,
        styling=None
    ):
        super().__init__()
        if not isinstance(num_range, range):
            if not isinstance(num_range, (float, int)):
                raise TypeError(slider_errs["range_type_err"].format(
                    str(type(num_range))
                    .removeprefix("<class ")
                    .removesuffix(">")
                ))
            if type(num_range) == int:
                _range = range(num_range)
            else:
                _range = Range(num_range)
                
        self._range = num_range

        self._dir = slide_direction
        self._sliding_area = sliding_area
        
        self._values = [n for n in _range]
        if slide_direction == X:
            self._pix_step = sliding_area._width / self._range.step
        elif slide_direction == Y:
            self._pix_step = sliding_area._height / self._range.step
        self._slider_area = slider_area

    def _check_range(self, num, min_, max_):
        #round the value
        if num > self._values[-1]:
            return self._values[-1]
        elif num < self._values[0]:
            return self._values[0]
        up, down = 0, 0
        for i in range(len(self._values)):
            if self._values[i] > num:
                up = self._values[i]
                down = self._values[i - 1]
                break
        if up - num <= num - down:
            num = up
        else:
            num = down
        
        if num <= min_:
            return min_
        if num >= max_:
            return max_
        return num

    def _drag_callback(self, mouse_pos):
        if self.slider_area.collision(mouse_pos):
            if self._dir == X:
                self.slider_area.set_coords(
                    self._check_range(
                        mouse_pos[0],
                        self.sliding_area._x,
                        self.sliding_area._x + self.sliding_area._width
                    ),
                    self.slider_area._y
                )
            else:
                self.slider_area.set_coords(
                    self.slider_area._x,
                    self._check_range(
                        mouse_pos[1],
                        self.sliding_area._y,
                        self.sliding_area._y + self.sliding_area._height                )
                )

    def get_value(self):
        for i in range(len(self._values)):
            if self._dir == X:
                if 
