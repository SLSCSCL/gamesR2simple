from .._cpp.quit import q

from ._err_msgs import base_errs
from ._ids import ids
from .errors import EventHandlerNotProvidedError

class BaseUtility:
    def __init__(self):
        #get an id - the id is an index number for self.events to use
        self._id = ids["id"]
        ids["id"] += 1

    def _has_event_handler(self):
        try:
            if self.events:
                return True
        except:
            return False
        
    def register_event_handler(self, event_handler):
        if not self._has_event_handler():
            self.events = event_handler

    def _event_error(self):
        q()
        raise EventHandlerNotProvidedError(base_errs["no_event_handler_err"])

    def get_mapping(self):
        return self._mapping

class BaseClickableUtility(BaseUtility):
    def attach_click_event(self, callback, type_click = "left"):
        if self._has_event_handler():
            if type_click not in ["left", "mid", "right"]:
                q()
                raise TypeError(base_errs["no_such_type_click_err"])
            self.events.add_utility_click_event(
                self._id,
                self._click_callback,
                type_click
            )
            self._callbacks[type_click] = callback
        else:
            self._event_error()

class BaseScrollableUtility(BaseUtility):
    def attach_scroll_event(self, event, callback):
        if self._has_event_handler():
            self.events.verify_event_type(event, "scroll")
            self.events.add_utility_scroll_event(
                self._id,
                "scroll" + event,
                self._scroll_callback
            )
            self._callbacks[event] = callback
        else:
            self._event_error()

class BaseDragableUtility(BaseUtility):
    def attach_drag_event(self, callback, type_click="left"):
        if self._has_event_handler():
            self.events.add_utility_drag_event(
                self._id,
                self._drag_callback,
                type_click
            )
        else:
            self._event_error()
