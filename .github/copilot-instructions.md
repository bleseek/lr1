**Overview**
- **Purpose:** Small C project that implements a custom tangent (`custom_tan`) and validates it with simple unit-style checks in `main.c`.
- **Design note:** `custom_tan` in `math_func.c` uses range-reduction + Taylor series expansions for sin/cos and returns `sin/cos`. Keep numerical-error and epsilon semantics intact.

**Build & Run**
- **Primary quick command:** compile both sources with MinGW/g++:

```bash
g++ -g main.c math_func.c -o main.exe
./main.exe
```
- **VS Code task:** there's a generated build task named "C/C++: g++.exe сборка активного файла" (uses `C:/MinGW/bin/g++.exe`). Use the task to build the active file; note it compiles only the active editor file by default.
- **Artifacts:** project root and `output/` folder may hold results; tests print pass/fail to stdout and the program returns `0` on success, `-1` if any test fails.

**Key files to inspect**
- `main.c` — test harness; `run_tests()` compares `custom_tan(x, eps)` to `tan(x)` from `<math.h>`.
- `math_func.c` — implementation of `custom_tan`; contains range reduction (`fmod`, adjust by `M_PI/2`) and two Taylor-series loops.
- `math_func.h` — public declaration: `double custom_tan(double x, double epsilon);`.
- `CppProperties.json` — project configuration used by the editor/IntelliSense.

**Code patterns & conventions (project-specific)**
- Single small module pattern: header declares one public function, implementation file defines it; tests live in `main.c` rather than a separate test framework.
- Numeric API: functions accept an `epsilon` parameter (error tolerance). Keep that parameter and its semantics (used as stopping criterion in series loops).
- Do not change function signatures without updating `main.c` tests.

**When making changes**
- If you modify `custom_tan` implementation, add/adjust entries in the `tests[]` array inside `run_tests()` in `main.c` to cover edge cases (near ±π/2, periodic reductions, very small/large x).
- Keep range-reduction logic in mind: series assume |x| ≤ π/2 after reduction; preserve or improve reduction correctness before changing series math.
- Preserve use of `_USE_MATH_DEFINES` and `#include <math.h>` where `M_PI` is used.

**Examples**
- To add a test for near-pole behavior, add a test case in `main.c`:

```c
{M_PI/2 - 1e-6, 1e-6}
```

- To run a quick single-file compile from VS Code, open `main.c`, then run the build task; to build both files from terminal, run the `g++` command above.

**Integration points & external deps**
- Relies only on standard C library `<math.h>`; MinGW (or any libc/libm) is required to build and run.
- No external test frameworks or CI configs discovered in the repo.

**What to avoid**
- Don't remove `epsilon` or alter its semantics without updating test thresholds in `main.c`.
- Avoid changing header guards or macro usage (`_USE_MATH_DEFINES`) that enable `M_PI` unless you update includes accordingly.

**Where to look for more context**
- Implementation: [math_func.c](math_func.c)
- Declaration: [math_func.h](math_func.h)
- Test runner: [main.c](main.c)
- Editor config: [CppProperties.json](CppProperties.json)

If any section is unclear or you'd like the file to include additional team conventions (commit message style, branch rules, CI steps), tell me which items to add and I'll update this file.
