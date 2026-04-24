from ._base_utilities import BaseClickableUtility, BaseScrollableUtility

def _do_nothing(arg=None):
    pass

class BaseOptionBar(BaseClickableUtility, BaseScrollableUtility):
    def __init__(self, mapping, starting_index):
        super().__init__()
        #Verify that the mapping is valid
        if not isinstance(mapping, (list, tuple)):
            raise TypeError(
                "The 'mapping' parameter of an option bar should be of " +
                "type 'list' or 'tuple'"
            )
        for item in mapping:
            if type(item) != dict:
                raise TypeError(
                    "Each item for the mapping of an option bar should " +
                    "be of type 'dict', 'list', or 'tuple'"
                )

        self._mapping = mapping
        self._max, self.i = len(mapping) - 1, starting_index

    def _get_param(self):
        return self.i \
               if "value" not in self._mapping[self.i] \
               else self._mapping[self.i]["value"]
    
    def _scroll(self, delta):
        if (delta > 0 and self.i > 0) or \
           (delta < 0 and self.i < self._max):
            self.i -= delta
        self._scroll_callback(self._get_param())
