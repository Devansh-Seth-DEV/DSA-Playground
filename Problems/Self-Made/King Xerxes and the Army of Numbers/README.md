# King Xerxes and the Army of Numbers

- `Time Limit: 0.6 second (cpp)`
- `Memory Limit: 64 MB`

## Problem Description

King Xerxes, the ruler of the Great Digital Empire, is preparing a parade of his mighty army. Each soldier in his army has a badge number from 1 to 9. Every year, during the Grand Festival, Xerxes selects a specific digit `x` and commands that exactly `n` soldiers bearing this digit be arranged in a line, forming a single gigantic number.

Xerxes is a man of great discipline and symmetry. He wants the resulting number to be precisely the digit `x` repeated `n` times — nothing more, nothing less. This number is then displayed in golden banners throughout the city.

You, as the Royal Programmer, are given `t` commands from the King. For each command, you must swiftly construct and print the desired number.

---

## Input

- The first line contains an integer `t` — the number of test cases $(1 ≤ t ≤ 10^3)$.
- The next `t` lines each contain two space-separated integers `x` and `n`:
  - `x` — the digit to repeat $(1 ≤ x ≤ 9)$
  - `n` — the number of repetitions $(1 ≤ n ≤ 10^5)$

## Output

For each test case, print the number formed by repeating the digit `x` exactly `n` times, each on a separate line.

## Example

### Input

```bash
3
4 2
5 6
3 23
```

### Output

```bash
44
555555
33333333333333333333333
```


## Explanation

- In the first test case, since `x = 4` and `n = 2`, the result is `44`.
- In the second test case, since `x = 5` and `n = 6`, the result is `555555`.
