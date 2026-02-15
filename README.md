# How Oxide Works

This project implements a modern multi-phase compiler architecture.
The compiler takes a single **entry file** (compilation root), recursively resolves all imports, analyzes the program, lowers it into an intermediate representation, optimizes it, and produces a native executable using **LLVM**.

The pipeline follows the same structural philosophy used in production compilers:
frontend → semantic analysis → IR → optimization → code generation.

## High Level Pipeline

```
Entry File
   ↓
Source Manager (module discovery)
   ↓
Lexer
   ↓
Parser → AST
   ↓
Semantic Analysis
   ↓
LLVM IR Generation
   ↓
LLVM Optimization Passes
   ↓
Machine Code Emission
   ↓
Executable
```

### 1. Driver & Compilation Session

The driver is responsible for orchestrating the build:

Responsibilities:

- Parse CLI arguments
- Locate entry file
- Recursively load imported modules
- Create a compilation session
- Run all compilation stages in order

The compiler does **not** require listing every source file.
Instead, the entry file acts as the _root of the module graph_.

### 2. Source Manager (Module System)

Before compilation begins, the compiler builds a dependency graph.

Tasks:

- Canonicalize file paths
- Cache loaded files
- Prevent duplicate compilation
- Map character positions → line/column for diagnostics

This phase determines the full set of translation units.

### 3. Lexical Analysis (Lexer)

The lexer converts raw text into tokens.

Example:

```
int x = 10 + 20;
```

Becomes:

```
INT IDENTIFIER EQUAL NUMBER PLUS NUMBER SEMICOLON
```

The lexer does **no syntax checking** — only classification.

### 4. Parsing → Abstract Syntax Tree (AST)

The parser consumes tokens and builds a structured tree representation.

Example AST:

```
BinaryExpr(+)
 ├── Number(10)
 └── Number(20)
```

The AST represents the _structure_ of the program, not its meaning.

### 5. Semantic Analysis

This is where the compiler understands the program.

Checks performed:

- Variable declarations
- Type checking
- Function resolution
- Scope resolution
- Constant evaluation
- Import validation

Output:
A fully validated program ready for lowering.

If this stage succeeds → program is logically correct.

### 6. Lowering to LLVM IR

The AST is converted into LLVM Intermediate Representation.

LLVM IR is a typed, SSA-based low-level language.

Example:
Source:

```
int x = 10 + 20;
```

LLVM IR (conceptual):

```
%1 = add i32 10, 20
store i32 %1, ptr %x
```

Why this matters:

- Platform independent
- Optimizable
- Mature backend ecosystem

At this point the frontend is complete.

### 7. Optimization Passes

Instead of implementing optimizations manually, the compiler delegates to LLVM’s pass pipeline.

Typical optimizations:

- Constant folding
- Dead code elimination
- Inlining
- Loop optimization
- Strength reduction
- Register promotion (mem2reg)

These dramatically improve performance without extra compiler complexity.

### 8. Code Generation (Backend)

LLVM converts IR into target machine instructions.

Steps:

1. Instruction selection
2. Register allocation
3. Scheduling
4. Object file emission

Output formats:

- ELF (Linux)
- COFF (Windows)
- Mach-O (macOS)

### 9. Linking

Finally, the object file is linked into an executable.

This stage resolves:

- external functions
- runtime
- standard libraries

### Why Use LLVM

Benefits:

- Industrial strength optimizations
- Multi-architecture support
- No need to write assembler generators
- Future JIT support possible
- Enables LSP tooling easily

Your compiler therefore focuses on:

> language design and correctness — not hardware details.

## Summary

| Stage             | Purpose                  |
| ----------------- | ------------------------ |
| Driver            | Orchestrates compilation |
| Source Manager    | Builds module graph      |
| Lexer             | Text → tokens            |
| Parser            | Tokens → AST             |
| Semantic Analysis | Validates meaning        |
| IR Generation     | AST → LLVM IR            |
| Optimization      | Improve performance      |
| Codegen           | Machine instructions     |
| Linking           | Final executable         |

## Mental Model

Think of the compiler as three layers:

**Frontend**
Understands the language.

**Middleend**
Improves the program.

**Backend**
Targets the CPU.

LLVM replaces the entire backend and most of the middleend.
