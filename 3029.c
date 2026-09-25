#include <string.h>

int minimumTimeToInitialState(char* word, int k) {
    int n = strlen(word);
    int ops = 1;

    // Check after each operation (stepping by k characters)
    for (int i = k; i < n; i += k) {
        // Compare the remaining suffix word[i...] with the prefix word[0...]
        if (strncmp(word + i, word, n - i) == 0) {
            return ops;
        }
        ops++;
    }

    return ops;
}
