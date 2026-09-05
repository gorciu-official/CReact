#pragma once

#include "nodes.h"

#define CR_ATTR(attr_name, attr_value) \
    ((creact_element_attribute_t){ \
        .name = (attr_name), \
        .value = (attr_value) \
    })

#define CR_ATTRS(...) \
    ((creact_element_attributes_t){ \
        .attr = (creact_element_attribute_t[]){ __VA_ARGS__ }, \
        .size = sizeof((creact_element_attribute_t[]){ __VA_ARGS__ }) / \
                sizeof(creact_element_attribute_t) \
    })

#define CR_ELEMENT(el_name, el_attr, ...) \
    ((creact_node_t){ \
        .type = CREACT_NODE_TYPE_ELEMENT, \
        .element = &(creact_element_t){ \
            .name = (el_name), \
            .attributes = (el_attr), \
            .children = (creact_node_t[]){ \
                __VA_OPT__(__VA_ARGS__,) \
                { .type = CREACT_NODE_TYPE_END } \
            } \
        } \
    })

#define CR_TEXT(str) \
    ((creact_node_t){ \
        .type = CREACT_NODE_TYPE_TEXT, \
        .text = &(creact_text_t){ \
            .content = (str) \
        } \
    })

#define CR_STYLE_PAIR(name, value) \
    name " : " value " ; \n "

#define CR_STYLE_FOR(el_selector, el_styles) \
    el_selector " { " el_styles " } \n "

#define CR_STYLE(...) \
    CR_ELEMENT("style", CR_ATTRS(), CR_TEXT(__VA_ARGS__))
