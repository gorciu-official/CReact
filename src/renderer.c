#include <emscripten.h>
#include "creact/renderer.h"

EM_JS(void, creact_remove_startup_notice, (), {
    document.querySelectorAll('[data-creact-remove-on-startup=true]').forEach((el) => el.remove());
});

EM_JS(int, js_get_root, (const char* selector), {
    const el = document.querySelector(UTF8ToString(selector));

    if (!el) {
        console.error("Root element not found");
        return 0;
    }

    if (!Module._dom_nodes) {
        Module._dom_nodes = [null];
    }

    const handle = Module._dom_nodes.length;
    Module._dom_nodes.push(el);

    return handle;
});

EM_JS(int, js_create_element, (const char* name), {
    const el = document.createElement(UTF8ToString(name));

    if (!Module._dom_nodes) {
        Module._dom_nodes = [null];
    }

    const handle = Module._dom_nodes.length;
    Module._dom_nodes.push(el);

    return handle;
});

EM_JS(int, js_create_text, (const char* content), {
    const text = document.createTextNode(UTF8ToString(content));

    if (!Module._dom_nodes) {
        Module._dom_nodes = [null];
    }

    const handle = Module._dom_nodes.length;
    Module._dom_nodes.push(text);

    return handle;
});

EM_JS(void, js_set_attribute, (int node, const char* name, const char* value), {
    Module._dom_nodes[node].setAttribute(
        UTF8ToString(name),
        UTF8ToString(value)
    );
});

EM_JS(void, js_append_child, (int parent, int child), {
    Module._dom_nodes[parent].appendChild(
        Module._dom_nodes[child]
    );
});

static void render_children(creact_node_t* nodes, int parent) {
    creact_node_t* node = nodes;

    while (node->type != CREACT_NODE_TYPE_END) {
        switch (node->type) {
        case CREACT_NODE_TYPE_TEXT: {
            int text = js_create_text(
                node->text->content
            );

            js_append_child(parent, text);
            break;
        }

        case CREACT_NODE_TYPE_ELEMENT: {
            int element = js_create_element(node->element->name);

            for (size_t i = 0; i < node->element->attributes.size; i++) {
                creact_element_attribute_t* attr = &node->element->attributes.attr[i];
                js_set_attribute(element, attr->name, attr->value);
            }

            render_children(node->element->children, element);

            js_append_child(parent, element);

            break;
        }

        case CREACT_NODE_TYPE_END:
            break;
        }

        node++;
    }
}

void creact_render(const char* selector, creact_node_t* root) {
    int parent = js_get_root(selector);

    if (!parent) {
        return;
    }

    render_children(root, parent);
}
