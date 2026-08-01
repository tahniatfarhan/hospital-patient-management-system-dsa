# Security & Memory Safety Policy

## Memory Safety & RAII

This C++ project adheres to standard **Resource Acquisition Is Initialization (RAII)** memory management practices:

1. **Tree Node Cleanup:** `BST` and `AVLTree` destructors recursively release dynamic heap allocations (`new BSTNode`, `new AVLNode`) on destruction, preventing memory leaks.
2. **Input Stream Sanitization:** Terminal input routines clear stream error states (`std::cin.clear()`) and flush stream buffers to prevent numeric buffer overflow loops on invalid input.
3. **Const Correctness:** Read-only methods and parameter references use `const` qualifiers to prevent accidental state mutation.

## Reporting Vulnerabilities

If you discover a memory leak, dynamic pointer bug, or buffer vulnerability, please email **tahniatfarhan@gmail.com**.
