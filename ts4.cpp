/**
 *  This example demonstrate how we can use peg_parser::parser to define a
 * simple command-line calculator. The parser supports the basic operators `+`,
 * `-`, `*`, `/`, `^` as well as using and assigning variables via `=`.
 *
 *  Note, that The grammar is defined in a left-recursive way. While this is
 * easiest to implement, it recomended to rewrite left-recursive grammars
 * sequentially for optimal performance.
 */

#include "tick.h"

int main() {
  tick::tick_run();
  return 0;
}
