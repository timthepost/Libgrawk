// libgrawk_tests.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grawk.h"

static int total = 0;
static int passed = 0;

#define TEST(name, expr) do { \
  total++; \
  if (expr) { \
    passed++; \
    printf("ok %d - %s\n", total, name); \
  } else { \
    printf("not ok %d - %s\n", total, name); \
  } \
} while (0)

int main(void) {
  printf("1..5\n");

  grawk_t *g = grawk_init();
  TEST("init grawk_t not null", g != NULL);

  grawk_opts_t opts = { .ignore_case = 1 };
  grawk_set_options(g, &opts);

  awk_pat_t *pat = grawk_build_pattern("foo");
  TEST("built pattern not null", pat != NULL);

  grawk_set_pattern(g, pat);
  TEST("set pattern", g->pat == pat);

  TEST("case-insensitive match", grawk_match(g, "FOO") == 1);
  TEST("case-insensitive no match", grawk_match(g, "bar") == 0);

  grawk_free(g);
  return (passed == total) ? 0 : 1;
}
