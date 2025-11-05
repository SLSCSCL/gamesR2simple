from ._base_option_bar import BaseOptionBar, q
from ._err_msgs import o_b_errs
from .errors import (
    MappingKeyError,
    ActionNotNoneError,
    OptionTypeNotImageError,
    NoExistingOptionError,
    NoExistingActionError
)

class OptionBar(BaseOptionBar):
    def m_k_err(self):
        q()
        raise MappingKeyError(
            o_b_errs["mapping_key_err"]
        ) from None
    
    def draw(self, draw, item):
        try: #is it filled?
            draw.fill_style = item["fill_style"]
        except KeyError: #is it stroked?
            try:
                draw.stroke_style = item["stroke_style"]
            except KeyError:
                try: # it must be an image
                    draw.image(item["image"], item["x"], item["y"])
                except KeyError:
                    #the programmer is mucking about - teach'em
                    self.m_k_err()
            else:
                try: #is it a stroked rect?
                    draw.stroke_rect(
                        item["x"],
                        item["y"],
                        item["width"],
                        item["height"]
                    )
                except KeyError:
                    try: #it must be an area
                        draw.stroke_area(item["area"])
                    except KeyError:
                        #the programmer is mucking about - teach'em
                        self.m_k_err()
        else:
            try: #is it a filled rect?
                draw.fill_rect(
                    item["x"],
                    item["y"],
                    item["width"],
                    item["height"]
                )
            except KeyError:
                try: #it must be an area
                    draw.fill_area(item["area"])
                except KeyError:
                    #the programmer is mucking about - teach'em
                    self.m_k_err()

class SameOptionsBar(BaseOptionBar):
    def __init__(self, mapping, option_type, action = None):
        super().__init__(mapping)
        valid = {
            "actions": ("fill", "stroke", None),
            "o_types": ("rect", "area", "image")
        }
        if action not in valid["actions"]:
            q()
            raise NoExistingActionError(
                o_b_errs["no_action_err"].format(action)
            )
        elif option_type not in valid["o_types"]:
            q()
            raise NoExistingActionError(
                o_b_errs["no_o_type_err"].format(option_type)
            )
        del valid
        
        if option_type == "image":
            if action != None:
                q()
                raise ActionNotNoneError(
                    o_b_errs["action_not_none_err"]
                )
            self._action = "image"
            self._color = None
            return
        elif action == None and option_type != "image":
            raise OptionTypeNotImage(
                o_b_errs["o_type_not_image"]
            )

        self._action = f"{option_type}_{action}"
        self._color = f"{option_type}_style"
            
    def draw(self, draw, item):
        if self._color:
            eval(f"draw.{self._color} = item['{self._color}']")
            eval(f"item.pop({self._color})")
        eval(f"draw.{self._action}(**item)")
