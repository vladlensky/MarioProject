#ifndef JEUSTATE_H
#define JEUSTATE_H

#include "GameState.h"

state_t * JS_get();

static char *FirstLevelMap[] = {
        "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
        "0                                                                                    w                                                               0",
        "0                   w                                  w                   w                                                                         0",
        "0                                      w                                       kk                                                                    0",
        "0                                                                             k  k                                                                   0",
        "0                                                                             k                w                                                     0",
        "0                                                                       r     k                                                                      0",
        "0                                                                      rr     k  k                                                                   0",
        "0                                                                     rrr      kk                                                                    0",
        "0                    kkckk                                           rrrr                                                                            0",
        "0                                      t0                           rrrrr                                                                            0",
        "0G                                     00              t0          rrrrrr            G                                                               0",
        "0           d    g       d             00              00         rrrrrrr                                                                            0",
        "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
        "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
};

#endif
