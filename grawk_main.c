// grawk_main.c
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grawk.h"

static void usage(const char *prog) {
  fprintf(stderr, "Usage: %s [-ivq] pattern < STDIN\n", prog);
  exit(1);
}

int main(int argc, char **argv) {
  grawk_opts_t opts = {0};
  const char *pattern = NULL;

  int i;
  for (i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      for (const char *c = argv[i] + 1; *c; ++c) {
        switch (*c) {
          case 'i': opts.ignore_case = 1; break;
          case 'v': opts.invert_match = 1; break;
          case 'q': opts.quiet = 1; break;
          default: usage(argv[0]);
        }
      }
    } else {
      pattern = argv[i];
      break;
    }
  }

  if (!pattern) usage(argv[0]);

  grawk_t *g = grawk_init();
  awk_pat_t *pat = grawk_build_pattern(pattern);
  if (!g || !pat) {
    fprintf(stderr, "error: failed to compile pattern\n");
    return 2;
  }

  grawk_set_options(g, &opts);
  grawk_set_pattern(g, pat);

  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  while ((nread = getline(&line, &len, stdin)) != -1) {
    if (line[nread - 1] == '\n') line[nread - 1] = '\0';
    if (grawk_match(g, line)) {
      if (!opts.quiet) puts(line);
    } else if (opts.invert_match && !opts.quiet) {
      puts(line);
    }
  }
  free(line);
  grawk_free(g);
  return 0;
}
