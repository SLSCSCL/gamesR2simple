import pygame

#used in the Events class:
from ._combinations import KeyCombination, MouseKeyCombination
from .._legends import keys, pressed_keys, pressed_btns

#errors
from ._error_msgs import event_errs
from .errors import *

_event_types = [
    "up",
    "scrollup",
    "down",
    "scrolldown",
    "move"
]

def _do_nothing(arg = None):
    pass

class Events:
    """An interface to add and handle events"""
    def __init__(self, game):
        self.game = game
        self.events = { #dict of lists of dicts to hold events
            "quit": [],
            "keydown": [],
            "keyup": [],
            "key_combinations": [],
            "key_mouse_combinations": [],
            "mousedown": _do_nothing,
            "mouseup": _do_nothing,
            "mousemove": [],
            "mousemiddledown": _do_nothing,
            "mousemiddleup": _do_nothing,
            "mouserightup": _do_nothing,
            "mouserightdown": _do_nothing,
            "mousescrollup": _do_nothing,
            "mousescrolldown": _do_nothing,
            "utilities": [],
            "utility_key_combinations": [],
            "utility_key_mouse_combinations": [],
        }

    def verify_event_type(self, event_type, event):
        """Make sure that the event type exists"""
        if event_type not in _event_types:
            self.game.destroy(error=True) #close the game window
            raise NoExistingEventTypeError(
                f"No such event '{event + event_type}'"
            )
    
    def _verify_key_exists(self, key):
        """Verify that a given key exists"""
        if key not in keys.values():
            self.game.destroy(error=True)
            raise NoExistingEventError("No such event")

    def _verify_keys_exist(self, key1, key2, key3):
        """Verify that given keys exist"""
        events = [key1]
        if key2:
            events.append(key2)
            if key3:
                events.append(key3)

        for key in events:
            self._verify_key_exists(key)
    
    def add_key_event(
            self,
            event_type: "up | down",
            event: "value from the keys dict",
            func: "callback function"
        ):
        """Add an event"""
        #check the event
        self._verify_key_exists(event)
        self.verify_event_type(event_type, "key")
        
        #end the method if the event has already been added to the key-events
        for e in self.events["key" + event_type]:
            if e["event"] == event:
                return

        for e in self.events["quit"]:
            if e["event"] == event:
                self.game.destroy(error=True)
                raise CannotOverrideEventBehaviorError(
                    event_errs["overridden_event"].format("Key", "quit")
                )

        #if everything passed, add the event
        self.events["key" + event_type].append({
            "event": event,
            "callback": func
        })

    def add_key_combination(self, key1, key2, callback, key3 = None):
        """Add a multiple-key event"""
        self._verify_keys_exist(key1, key2, key3)
        self.events["key_combinations"].append(
            KeyCombination(key1, key2, key3, callback)
        )

    def add_mouse_key_combination(
        self,
        key1,
        callback,
        key2 = None,
        key3 = None
    ):
        """Add a mouse-key event-combination"""
        self._verify_keys_exist(key1, key2, key3)
        self.events["key_mouse_combinations"].append(
            MouseKeyCombination(key1, key2, key3, callback)
        )
    
    def _add_mouse_event_helper(
        self,
        event_type,
        callback,
        req_click,
        req_m_click,
        req_r_click
    ):
        """Add a mouse event"""
        self.verify_event_type(event_type, "mouse")

        if event_type != "move":
            #There can only be one mouse event of event_type
            self.events["mouse" + event_type] = callback
        else:
            event = {
                "callback": callback,
                "req_l_click": req_click,
                "req_m_click": req_m_click,
                "req_r_click": req_r_click
            }
            if event not in self.events["mousemove"]:
                self.events["mousemove"].append(event)

    def add_mouse_event(
        self,
        event_type,
        callback,
        type_click="left"
    ):
        """Add a mouse event"""
        self._add_mouse_event_helper(
            event_type,
            callback,
            type_click == "left",
            type_click == "middle",
            type_click == "right"
        )

    def _set_default_utility(self, u_id):
        if len(self.events["utilities"]) - 1 != u_id:
            self.events["utilities"].append({
                "leftclick": _do_nothing,
                "midclick": _do_nothing,
                "rightclick": _do_nothing,
                "drag": [],
                "scrollup": _do_nothing,
                "scrolldown": _do_nothing,
                "keys": []
            })

    def add_utility_click_event(self, u_id, callback, type_click="left"):
        self._set_default_utility(u_id)
        self.events["utilities"][u_id][type_click + "click"] = callback

    def add_utility_scroll_event(self, u_id, event_type, callback):
        self._set_default_utility(u_id)
        self.events["utilities"][u_id]["scroll" + event_type] = callback

    def add_utility_drag_event(self, u_id, callback, type_click="left"):
        self._set_default_utility(u_id)
        events = self.events["utilities"][u_id]["drag"]
        event = {
            "callback": callback,
            "req_l_click": type_click == "left",
            "req_m_click": type_click == "mid",
            "req_r_click": type_click == "right"
        }
        if event not in events:
            events.append(event)

    def add_utility_key_combo(self, u_id, key1, key2, callback, key3 = None):
        combo = KeyCombination(key1, key2, key3, callback)
        for c in self.events["key_combinations"]:
            if combo == c:
                self.game.destroy(error=True)
                raise CannotOverrideEventBehaviorError(
                    event_errs["overridden_event"].format(
                        "Utility key-combinations",
                        "key-combinations"
                    )
                )
        events = self.events["utility_key_combinations"]
        for c in events:
            if combo == c:
                return
        events.append(combo)
        
    def add_utility_mouse_key_combo(
        self,
        u_id,
        key1,
        callback,
        key2 = None,
        key3 = None
    ):
        combo = MouseKeyCombination(key1, key2, key3, callback)
        for c in self.events["key_combinations"]:
            if combo == c:
                self.game.destroy(error=True)
                raise CannotOverrideEventBehaviorError(
                    event_errs["overridden_event"].format(
                        "Utility key-combinations",
                        "key-combinations"
                    )
                )
        events = self.events["utility_key_combinations"]
        for c in events:
            if combo == c:
                return
        events.append(combo)

    def add_quit_event(self, event, on_quit=_do_nothing):
        """Add a quit event"""
        for evnt in ["up", "down"]:
            for e in self.events["key" + evnt]:
                if e["event"] == event:
                    self.game.destroy(error=True)
                    raise CannotOverrideEventBehaviorError(
                        event_errs["overridden_event"].format("Quit", "key")
                    )
        e = {
            "event": event,
            "on_quit": on_quit
        }
        if e not in self.events["quit"]:
            self.events["quit"].append(e)

    def check_events(self):
        """Check the events"""
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.game.destroy()
                return
            if event.type == pygame.KEYDOWN:
                if self._check_quit_events(event):
                    self.game.destroy()
                    return
                pressed_keys[event.key] = True
                self._check_key_events(event, "down")
                self._check_key_combinations()
            elif event.type == pygame.KEYUP:
                pressed_keys[event.key] = False
                self._check_key_events(event, "up")
            elif event.type == pygame.MOUSEBUTTONDOWN:
                self._check_mousedown_events()
                self._check_mouse_key_combinations()
            elif event.type == pygame.MOUSEBUTTONUP:
                self._check_mouseup_events(event)
            elif event.type == pygame.MOUSEWHEEL:
                self._check_scroll_events(event.y)
            elif event.type == pygame.MOUSEMOTION:
                self._check_mousemove_events()

    def _check_key_events(self, event, event_type):
        """Check the key events"""
        for e in self.events["key" + event_type]:
            if event.key == e["event"]:
                e["callback"]()
                
    def _check_key_combinations(self):
        self._check_key_combinations_helper(self.events["key_combinations"])
        events = self.events["utility_key_combinations"]
        for u_id in range(len(events)):
            for combo in events[u_id]["combinations"]:
                self._check_key_combination(combo)
                
    def _check_key_combinations_helper(self, combos):
        for combo in combos:
            if pressed_keys[combo.key1] and pressed_keys[combo.key2]:
                if combo.size == 2:
                    combo.callback()
                    continue
                if pressed_keys[combo.key3]:
                    combo.callback()
                    
    def _send_mouse_pos(self, callback, extra_str = ""):
        try:
            callback(pygame.mouse.get_pos())
        except TypeError:
            self.game.destroy(error=True)
            raise RequiredArgumentMissingError(
                event_errs["mouse_e_callback_arg_undef"].format(extra_str)
            ) from None

    def _check_mouse_key_combinations(self):
        self._check_mouse_key_combinations_helper(
            self.events["key_mouse_combinations"]
        )
        events = self.events["utility_key_mouse_combinations"]
        for u_id in range(len(events)):
            self.check_mouse_key_combinations_helper(
                events[u_id]["combinations"]
            )
    
    def _check_mouse_key_combinations_helper(self, combos):
        for combo in combos:
            if pressed_keys[combo.key1]:
                if combo.size > 1:
                    if pressed_keys[combo.key2]:
                        if combo.size == 3:
                            if pressed_keys[combo.key3]:
                                self._send_mouse_pos(combo.callback, "-key")
                                continue
                        self._send_mouse_pos(combo.callback, "-key")
                        continue
                self._send_mouse_pos(combo.callback, "-key")

    def _send_utility_click_pos(self, click):
        u_events = self.events["utilities"]
        for u_id in range(len(u_events)):
            self._send_mouse_pos(
                self.events["utilities"][u_id][click + "click"]
            )

    def _check_mousedown_events(self):
        """Check the mousedown events"""
        state = pygame.mouse.get_pressed(3)
        if state[0] and not pressed_btns["left"]:
            pressed_btns["left"] = True
            self._send_mouse_pos(self.events["mousedown"])
            self._send_utility_click_pos("left")
        
        if state[1] and not pressed_btns["mid"]:
            pressed_btns["mid"] = True
            self._send_mouse_pos(self.events["mousemiddledown"])
            self._send_utility_click_pos("mid")
        
        if state[2] and not pressed_btns["right"]:
            pressed_btns["right"] = True
            self._send_mouse_pos(self.events["mouserightdown"])
            self._send_utility_click_pos("right")

    def _check_mousemove_events(self):
        self._check_mousemove_events_helper(self.events["mousemove"])
        events = self.events["utilities"]
        for u_id in range(len(events)):
            self._check_mousemove_events_helper(events[u_id]["drag"])

    def _check_mousemove_events_helper(self, events):
        for event in events:
            if event["req_l_click"] and pressed_btns["left"]:
                self._send_mouse_pos(event["callback"])
            elif event["req_m_click"] and pressed_btns["mid"]:
                self._send_mouse_pos(event["callback"])
            elif event["req_r_click"] and pressed_btns["right"]:
                self._send_mouse_pos(event["callback"])

    def _check_scroll_events(self, state):
        """Check the scroll events"""
        if state == 1:
            self.events["mousescrollup"]()
            self._send_utility_scroll_events("up")
        elif state == -1:
            self.events["mousescrolldown"]()
            self._send_utility_scroll_events("down")

    def _send_scrollup_events(self):
        """Send the scrollup events"""
        self.events["mousescrollup"]()

    def _send_utility_scroll_events(self, event):
        u_events = self.events["utilities"]
        for u_id in range(len(u_events)):
            u_events[u_id]["scroll" + event]
    
    def _check_mouseup_events(self, event):
        """Check the mouseup events"""
        state = event.button
        if state == 1 and pressed_btns["left"]:
            pressed_btns["left"] = False
            self.events["mouseup"]()
        
        if state == 2 and pressed_btns["mid"]:
            pressed_btns["mid"] = False
            self.events["mousemiddleup"]()
        
        if state == 3 and pressed_btns["right"]:
            pressed_btns["right"] = False
            self.events["mouserightup"]()

    def _check_quit_events(self, event):
        """Check the quit events"""
        for e in self.events["quit"]:
            if e["event"] == event.key:
                e["on_quit"]()
                return True
        return False
