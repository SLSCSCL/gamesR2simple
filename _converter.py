from math import floor
from warnings import warn

class Converter:
    tables = {
        "hex": {
            "a": 10, "b": 11, "c": 12, "d": 13, "e": 14, "f": 15
        },
        "dec": {
            "10": "a", "11": "b", "12": "c", "13": "d", "14": "e", "15": "f"
        }
    }

    def __init__(self):
        for num in range(10):
            self.tables["hex"][str(num)] = num
            self.tables["dec"][str(num)] = str(num)

    def hex_to_rgb(self, h: str):
        if type(h) != str:
            raise TypeError(
                "Cannot parse color with type " +
                str(type(h)).replace("<class ", "").replace(">", "")
            )
        if len(h) > 7:
            warn(
                "Converter.hex_to_rgb will not give you an alpha value." +
                " Use Converter.hex_to_rgba to get an alpha value"
            )
        #setup the hex value
        h = list(h.lower())
        if h[0] == "#":
            h.pop(0)

        #calculate the result and send the color as a tuple
        result = [self.tables["hex"][h[i]] + self.tables["hex"][h[i + 1]] * 16
                  for i in range(0, len(h), 2)]
        return (result[0], result[1], result[2])

    def rgb_to_hex(self, rgb: "list | tuple"):
        if not isinstance(rgb, (list, tuple)):
            raise TypeError(
                "First argument to Converter.rgb_to_hex must be of type list or tuple"
            )
        hex_vals = []
        for value in rgb:
            if type(value) != int:
                raise TypeError(
                    "All items in the list | tuple must be of type 'int'"
                )
            hex_vals.append(self.tables["dec"][str(value % 16)])
            hex_vals.append(self.tables["dec"][str(floor(value / 16))])
        return "#" + "".join(hex_vals)
convert = Converter()
