#pragma once

#include <stddef.h>

typedef enum creact_node_type {
    CREACT_NODE_TYPE_TEXT,
    CREACT_NODE_TYPE_ELEMENT,
    CREACT_NODE_TYPE_END
} creact_node_type_t;

typedef struct creact_node creact_node_t;

typedef struct creact_element_attribute {
    char* name;
    char* value;
} creact_element_attribute_t;

typedef struct creact_element_attributes {
    creact_element_attribute_t* attr;
    size_t size;
} creact_element_attributes_t;

typedef struct creact_element {
    char* name;
    creact_element_attributes_t attributes;
    creact_node_t* children;
} creact_element_t;

typedef struct creact_text {
    char* content;
} creact_text_t;

struct creact_node {
    creact_node_type_t type;

    union {
        creact_element_t* element;
        creact_text_t* text;
    };
};
