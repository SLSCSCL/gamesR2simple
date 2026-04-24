from ._callback import Callback
from ._ids import ids
from .._cpp import MouseEvents

def do_nothing(*args):
    pass

class BaseUtility:
    def __init__(self):
        #get an id - the id is an index number for self.events to use
        self._id = ids["id"]
        ids["id"] += 1

    def get_mapping(self):
        return self._mapping

class BaseClickableUtility(BaseUtility):
    def __init__(self):
        super().__init__()
        self._click_callbacks = {
            MouseEvents.L_CLICK: Callback(),
            MouseEvents.R_CLICK: Callback(),
            MouseEvents.WHL_CLICK: Callback()
        }
    
    def enter_click_data(self, event_type, callback = do_nothing):
        match event_type:
            case MouseEvents.L_CLICK:
                cb = self._left_click
            case MouseEvents.R_CLICK:
                cb = self._right_click
            case MouseEvents.WHL_CLICK:
                cb = self._wheel_click
            case _:
                raise ValueError(
                    "The event_type argument must be one of the following " +
                    "values from gamesR2simple.MouseEvents:\n\tL_CLICK\n\t" +
                    "LEFT_CLICK\n\tR_CLICK\n\tRIGHT_CLICK\n\tWHL_CLICK\n\t" +
                    "WHEEL_CLICK"
                )
        self._click_callbacks[event_type].set(callback)
        
        return event_type, cb, self._id

class BaseDragableUtility(BaseUtility):
    def __init__(self):
        super().__init__()
        self._drag_callbacks = {
            MouseEvents.L_DRAG: Callback(),
            MouseEvents.R_DRAG: Callback(),
            MouseEvents.WHL_DRAG: Callback()
        }
    
    def enter_drag_data(self, event_type, callback = do_nothing):
        match event_type:
            case MouseEvents.L_DRAG:
                cb = self._left_drag
            case MouseEvents.R_DRAG:
                cb = self._right_drag
            case MouseEvents.WHL_DRAG:
                cb = self._wheel_drag
            case _:
                raise ValueError(
                    "The event_type argument must be one of the following " +
                    "values from gamesR2simple.MouseEvents:\n\tL_DRAG\n\t" +
                    "LEFT_DRAG\n\tR_DRAG\n\tRIGHT_DRAG\n\tWHL_DRAG\n\t" +
                    "WHEEL_DRAG"
                )
        
        self._drag_callbacks[event_type].set(callback)
        return event_type, cb, self._id

class BaseScrollableUtility(BaseUtility):
    def __init__(self):
        super().__init__()
        self._scroll_callback = Callback()
    
    def enter_scroll_data(self, callback = do_nothing):
        self._scroll_callback.set(callback)
        
        return self._scroll, self._id
