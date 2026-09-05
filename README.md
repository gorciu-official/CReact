# CReact

It's React, except in C. Write your website (nearly) entirelly in C! More DOM manipulation coming soon(TM).

Inspired by [C for Web](https://github.com/Maqi-x/cfw).

## Syntax

Kinda JSX inspired, but it's C preprocessor and `cpp` has limitations etc, so it look like it, hoke you like it:

```c 
creact_node_t el = CR_ELEMENT(
    "div", CR_ATTRS(),
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
```
