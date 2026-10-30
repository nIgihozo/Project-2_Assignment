#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STUDENT_ID "54321"
#define MAX_WORD 50

// Data Structure that are Required
typedef struct {
    char word[MAX_WORD];
    int count;
} Wordstat;

// Prototype Functions
void count_words(char *text, Wordstat **stats, int *distinct, int *total);
void longest_word(char *text, Wordstat **stats, int *distinct, int *total);
void most_frequent(char *text, Wordstat **stats, int *distinct, int *total);
void display_word_stats(char *text, Wordstat **stats, int *distinct, int *total);
void sort_word_stats(char *text, Wordstat **stats, int *distinct, int *total);
void search_word(char *text, Wordstat **stats, int *distinct, int *total);
void custom_analysis(char *text, Wordstat **stats, int *distinct, int *total);
void generate_summary_report(char *text, Wordstat **stats, int *distinct, int *total);
void inspect_memory(char *text, Wordstat **stats, int *distinct, int *total);

// Helper Functions
void parse_text(char *text, Wordstat **stats, int *distinct, int *total){
    *distinct = 0;
    *total = 0;
    if (!text || strlen(text) == 0) return;

    char temp[MAX_WORD];
    int t_index = 0;
    char *ptr = text;

    while (*ptr) {
        if (isalpha((unsigned char)*ptr)) {
            if (t_index < MAX_WORD - 1) {
                temp[t_index++] = tolower((unsigned char)*ptr);
            }
        } else {
            if (t_index > 0) {
                temp[t_index] = '\0';
                (*total)++;
                int found = 0;
                for (int i = 0; i < *distinct; i++) {
                    if (strcmp((*stats)[i].word, temp) == 0) {
                        (*stats)[i].count++;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    Wordstat *new_stats = realloc(*stats, (*distinct + 1) * sizeof(Wordstat));
                    if (new_stats) {
                        *stats = new_stats;
                        strcpy((*stats)[*distinct].word, temp);
                        (*stats)[*distinct].count = 1;
                        (*distinct)++;
                    }
                }
                t_index = 0;
            }
        }
        ptr++;
    }
    
}

int main(void) {
    
    char *default_text = 
    "The artificial intelligence is changing the contemporary world at an unparalleled speed."
    "Whether it is the healthcare and education sectors or the financial and transport industries,"
    "machine learning algorithms optimize processes and facilitate innovations on an unparalleled scale."
    "As the software development experts keep moving technological limits,"
    "the analysis of language characteristics and text structures becomes more and more important"
    "for natural language processing tasks. With the help of word frequency analysis,"
    "sentence complexity measurement, and lexical richness estimation,"
    "the developers can design even smarter algorithms that would be capable of understanding human language.";

    // Allocate dynamic buffer for the text
    size_t text_length = strlen(default_text) + 1;
    char *text = malloc(text_length);
    if (!text) {
        printf("Failed to allocate memory for text.\n");
        return 1;
    }
    strcpy(text, default_text);

    int distinct = 0;
    int total = 0;
    Wordstat *stats = NULL;

    // Initial parse
    parse_text(text, &stats, &distinct, &total);

    // Function point Arrays
    void(*operations[])(char *, Wordstat **, int *, int *) = {
        count_words,
        longest_word,
        most_frequent,
        display_word_stats,
        sort_word_stats,
        search_word,
        custom_analysis,
        generate_summary_report,
        inspect_memory
    };

    int choice;
    do {
        printf("\n===== OUTPUT HEADER =====\n");
        printf("Student ID: %s\n", STUDENT_ID);
        printf("Project: Text Mining Analyzer\n");
        printf("Source: 'The AI Revolution'(Tech Insight Journal)\n");
        printf("Custom Analysis: Lexical Diversity Score\n");
        printf("\n=========================================\n");
        printf("1. Count Words\n");
        printf("2. Find Longest Word\n");
        printf("3. Find Most Frequent Word\n");
        printf("4. Display Word Statistics\n");
        printf("5. Sort Word Statistics\n");
        printf("6. Search Word\n");
        printf("7. Custom Analysis\n");
        printf("8. Generate Summary Report\n");
        printf("9. Inspect Memory\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number between 0 and 9.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        if (choice >= 1 && choice <= 9) {
            operations[choice - 1](text, &stats, &distinct, &total);
        } else if (choice == 10) {
            printf("Exiting program...\n");
        } else {
            printf("Choice is out of range. Please try again.\n");
        }
        } while (choice != 10);

        // Free all the allocated memory
        free(text);
        free(stats);
        return 0;
}


// Required Operations
void count_words(char *text, Wordstat **stats, int *distinct, int *total) {
    printf("\nTotal Words: %d\n", *total);
}

void longest_word(char *text, Wordstat **stats, int *distinct, int *total) {
    if (*distinct == 0) return;
    char *longest = (*stats)[0].word;
    for (int i = 1; i < *distinct; i++) {
        if (strlen((*stats)[i].word) > strlen(longest)) {
            longest = (*stats)[i].word;
        }
    }
    printf("\nLongest Word: %s (Length: %zu characters)\n", longest, strlen(longest));
}

void most_frequent(char *text, Wordstat **stats, int *distinct, int *total) {
    if (*distinct == 0) return;
    Wordstat top = (*stats)[0];
    for (int i = 1; i < *distinct; i++) {
        if ((*stats)[i].count > top.count) {
            top = (*stats)[i];
        }
    }
    printf("\nMost Frequent Word: %s (Frequency: %d)\n", top.word, top.count);
}

void display_word_stats(char *text, Wordstat **stats, int *distinct, int *total) {
    if (*distinct == 0) return;
    printf("\n%-20s | %-10s\n", "Word", "Frequency");
    printf("--------------------------------\n");
    for (int i = 0; i < *distinct; i++) {
        printf("%-20s | %-10d\n", (*stats)[i].word, (*stats)[i].count);
    }
}

int cmp_freq(const void *a, const void *b) {
    return ((Wordstat *)b)->count - ((Wordstat *)a)->count; // Descending order
}

void sort_word_stats(char *text, Wordstat **stats, int *distinct, int *total) {
    qsort(*stats, *distinct, sizeof(Wordstat), cmp_freq);
   display_word_stats(text, stats, distinct, total);
}

void search_word(char *text, Wordstat **stats, int *distinct, int *total) {
    char search[MAX_WORD];
    printf("\nEnter word to search: ");
    scanf(" %49s", search);
    for (int i = 0; search[i]; i++) search[i] = tolower(search[i]);
    for (int i = 0; i < *distinct; i++) {
        if (strcmp((*stats)[i].word, search) == 0) {
            printf("Found: %s (Frequency: %d)\n", (*stats)[i].word, (*stats)[i].count);
            return;
        }
    }
    printf("Word '%s' not found.\n", search);
}

// Custom Analysis
void custom_analysis(char *text, Wordstat **stats, int *distinct, int *total) {
    if (*total == 0) return;
    float diversity_score = ((float)*distinct / *total) * 100.0f;
    printf("CUSTOM ANALYSIS: LEXICAL DIVERSITY SCORE\n");
    printf("Formula: (Distinct Words / Total Words) * 100\n");
    printf("Result: %.2f%%\n", diversity_score);
}

void generate_summary_report(char *text, Wordstat **stats, int *distinct, int *total) {
    if (*total == 0) {
        printf("\nNo words to summarize.\n");
        return;
    }

    int char_sum = 0;
    for (int i = 0; i < *distinct; i++) {
        char_sum += strlen((*stats)[i].word) * (*stats)[i].count;
    }
    float avg_word_length = (float)char_sum / *total;

    printf("\n================ SUMMARY REPORT ================\n");
    printf("Total Words: %d\n", *total);
    printf("Distinct Words: %d\n", *distinct);
    printf("Average Word Length: %.2f characters\n", avg_word_length);
    custom_analysis(text, stats, distinct, total);
}

// Memory Adress Inspectations
void inspect_memory(char *text, Wordstat **stats, int *distinct, int *total) {
    printf("\nMemory Inspection:\n");
    printf("Text Buffer Address: %p\n", (void *)text);
    printf("Word Statistics Array Address: %p\n", (void *)*stats);
    if (*distinct > 0) {
        printf("Selected word-start entry 0: %p\n", (void *)&((*stats)[0]));
    }
}