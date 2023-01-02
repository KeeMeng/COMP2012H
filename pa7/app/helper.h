#ifndef HELPER_H
#define HELPER_H

// Number of letters in the English alphabet
const int NUM_LETTERS = 26;

// Helper macro to "safely" delete a pointer and set it to nullptr
// To use: write SAFE_DELETE(ptr); instead of delete ptr;
#define SAFE_DELETE(X) if (X) { delete X; X = nullptr; }

#endif // HELPER_H
