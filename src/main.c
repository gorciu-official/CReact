#include "tree-builder.h"
#include "renderer.h"

#include <stdio.h>

int main(void) {
    puts(
        "Website powered by CReact, check it out https://github.com/gorciu-official/CReact"
    );

    creact_remove_startup_notice();

    creact_node_t el = CR_ELEMENT(
        "div", CR_ATTRS(
            CR_ATTR("class", "fakeroot")
        ),
        CR_STYLE(
            CR_STYLE_FOR(
                "*",
                CR_STYLE_PAIR("margin", "0")
                CR_STYLE_PAIR("padding", "0")
                CR_STYLE_PAIR("color", "white")
            )
            CR_STYLE_FOR(
                "body",
                CR_STYLE_PAIR("background-color", "black")
                CR_STYLE_PAIR("padding", "20px")
            )
        ), 
        CR_ELEMENT(
            "p", CR_ATTRS(
                CR_ATTR("data-siema", "hi"),
                CR_ATTR("data-siemanko", "mordeczko")
            ), 
            CR_TEXT("siema mordo w <p>")
        ),
        CR_TEXT("siema mordo")
    );
    creact_render(
        "#creact-root",
        (creact_node_t[]){
            el,
            { .type = CREACT_NODE_TYPE_END }
        }
    );
}
