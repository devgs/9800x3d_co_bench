# Simple CPU undervolt stress benchmark

This discovery was very usefuly for me, so I've figured that I might as well share it.

It seems that copying a large chunk of **random** bytes is more stressful for CPU than even the venerable `mprime`.

I compile it with: `clang -o stress -std=c++17 -stdlib=libc++ -O3 stress.cpp -lc++`

Then run a test this way:

```
echo "" > stress.log; for i in {0..15}; do (taskset --cpu-list ${i} ./stress ${i} & >> stress.log); done; tail -f stress.log
```

Looking for something like this:

```
 Iteration 0: MISMATCH ON CORE 9
 Iteration 2: MISMATCH ON CORE 1
 Iteration 6: MISMATCH ON CORE 1
 Iteration 11: MISMATCH ON CORE 1
 Iteration 14: MISMATCH ON CORE 1
 Iteration 15: MISMATCH ON CORE 9
 Iteration 17: MISMATCH ON CORE 9
 Iteration 21: MISMATCH ON CORE 15
 Iteration 26: MISMATCH ON CORE 1
 Iteration 35: MISMATCH ON CORE 9
 Iteration 36: MISMATCH ON CORE 9
 Iteration 39: MISMATCH ON CORE 9
```

Identify the most failing core and tweak its undervolt. In my case it was core1 and its HT sibling core9 (1 + 8, I'm running Linux).

Weirdly enough, even thoug I saw core15 (physical core7) and others failing sometimes, when I toned the negative CO down for a core1, issues on all other cores **disappeared**.
It seems like some bad core, when undervolted too much, may affect other pretty stable cores. This allowed me to push other cores pretty high on negative curve.

Currently running stable with CO: -40,-10,-40,-40,-40,-40,-40,-40.
