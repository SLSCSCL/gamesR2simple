o_b_errs = {
    "mapping_key_err":
        "Invalid mapping! Perhaps a key was misspelled or forgotten.",
    "no_action_err": "The action {} does not exist.",
    "no_o_type_err": "The option type {} does not exist.",
    "action_not_none_err": "If the option_type arg is 'image', then the action arg must be None",
    "o_type_not_image": "If the action arg is None, option_type must be 'image'"
}

base_errs = {
    "mapping_type_err": "The mapping must be of type 'list', 'set', 'tuple'",
    "mapping_item_type_err": "Each item in the mapping must be of type 'dict'",
    "no_event_handler_err": "An event handler is required before adding events"
}

slider_errs = {
    "range_type_err":
        "Slider.num_range cannot be of type {}",
}
