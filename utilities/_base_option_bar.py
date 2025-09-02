import sys

from .._cpp.quit import q

from .._legends import pressed_btns
from ._base_utilities import BaseClickableUtility, BaseScrollableUtility
from ._err_msgs import base_errs

def _do_nothing(arg=None):
    pass

class BaseOptionBar(BaseClickableUtility, BaseScrollableUtility):
    def __init__(self, mapping, event_handler=None):
        super().__init__()
        if not isinstance(mapping, (list, set, tuple)):
            q()
            raise TypeError(base_errs["mapping_type_err"])
        for item in mapping:
            if type(item) != dict:
                raise TypeError(base_errs["mapping_item_type_err"])

        self._mapping = mapping
        self._max, self._i = len(mapping) - 1, 0
        self.events = event_handler #add the event handler
        self._callbacks = { #event holder
            "left": _do_nothing,
            "mid": _do_nothing,
            "right": _do_nothing,
            "scrollup": _do_nothing,
            "scrolldown": _do_nothing,
            "keyoptionup": [_do_nothing],
            "keyoptiondown": [_do_nothing]
        }
        
    def _do_click_event(self, i):
        if pressed_btns["left"]:
            self._callbacks["left"](i)
        elif pressed_btns["mid"]:
            self._callbacks["mid"](i)
        elif pressed_btns["right"]:
            self._callbacks["right"](i)

    def _click_callback(self, mouse_pos):
        for i in range(len(self._mapping)):
            option = self._mapping[i]
            x, y = mouse_pos
            try: #is it a filled or stroked rect?
                if x >= option["x"] and x <= option["x"] + option["width"] and\
                   y >= option["y"] and y <= option["y"] + option["height"]:
                    self._do_click_event(i)
                    return
            except KeyError:
                try: #is it an image?
                    img = option["image"]
                    if x >= option["x"] and x <= option["x"] + img.width and \
                       y >= option["y"] and y <= option["y"] + img.height:
                        self._do_click_event(i)
                except KeyError:
                    try:
                        if option["area"].collision(mouse_pos):
                            self._do_click_event(i)
                    except KeyError:
                        #the programmer is mucking about - teach'em
                        #this should only run in the base class OptionBar
                        self.m_k_err()

    def _scroll_callback(self, direction):
        if direction == 1:
            self._callbacks["scrollup"]
        else:
            self._callbacks["scrolldown"]
