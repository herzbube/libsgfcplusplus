# Coding guidelines

## Naming

- Class names start with an uppercase letter.
- Method names start with an uppercase letter.
- Variable names start with a lowercase letter.
- Member variable names do **not** have a prefix (e.g. "_"); use the keyword `this` to distinguish them from variables that are local to a method.
- Getter/setter methods should be named after the member variable they encapsulate (e.g. the `firstChild` member variable should have a `GetFirstChild` and `SetFirstChild` getter/setter).
- Find good names for variables, methods and classes; don't hesitate to use long names; never (!) use abbreviations; don't use i, j, k for loop variables.

## Indentation and formatting

- Spaces, no tabs.
- 2 spaces per indentation level.
- Opening/closing braces are placed on their own line.
- No space is used to separate opening/closing paranthesis from the expression they surround.
- Operators (e.g. "+" in string concatenations) are separated by spaces from their operands.
- Pointers: No space between the type name and the asterisk; e.g. `Foo* foo`, not `Foo *foo`.
- Use braces liberally to improve readability, but don't hesitate to omit them in long `if`- or `switch`-clauses that use only one-line statements. Readability is the most important aspect here - sometimes the right use of braces can create a visual pattern that immediately tells the reader how the program flows.

## Preprocessor

- No preprocessor macros unless absolutely necessary.

## Header files

- Use `#pragma once`. This pragma is well supported by all major compilers and vastly preferrable over preprocessor macro guards.
- Only one type (class, struct, enumeration) per header file.
- No inline code in header files.
- Avoid including header files in other header files, whenever possible use forward declarations.

## Code structure

- Only one variable declaration per line.
- Only one statement per line; long statements (e.g. method invocations with many parameters) may span multiple lines.
- Lines should not be longer than 80 characters; for comment lines this limit is much stricter than for lines of code.
- Never **EVER** use side-effects, e.g.
  - Don't place ++/-- operators in the same line as an assignment.
  - Don't test a condition and make an assignment at the same time.

## C++ language features

- Absolutely **no** multiple inheritance, except where it's needed for implementing interfaces.
- Declare methods `const` unless there is a reason not to.
- Always use `override` to declare overrides.
- No templates unless there is a good reason to.
- Throw exceptions by value so that the caller does not have to deal with memory management in the exception handler (e.g. `throw std::invalid_argument()` not `throw new std::invalid_argument()`).

## Other stuff

- Everything should be documented with Doxygen documentation blocks; exceptions are possible but should remain rare.
- See the [Library design and working principles](Principles.md) document for overarching topics that should inform changes to the library and new development.
