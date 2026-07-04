# Contributing

Thank you for your interest in contributing to TimedAction.

## How to contribute

1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/my-change`).
3. Make your changes.
 4. Run `make ci` to verify compilation, linting, and formatting.
 5. Commit with a clear message.
6. Open a Pull Request.

## Guidelines

- Keep the library compatible with Arduino AVR (C++03).
- Do not introduce runtime dependencies beyond Arduino.h.
- Update CHANGELOG.md for any user-facing changes.
- Update `library.properties` and `TimedAction.h` version for user-facing changes.

## Reporting issues

Open an issue at https://github.com/log0u7/TimedAction/issues with:

- Arduino IDE or CLI version
- Board model
- Minimal reproduction sketch
