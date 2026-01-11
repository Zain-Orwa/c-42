#include <stdio.h>
#include <stdlib.h>

/* function to find separations */
int is_separation(char c, char *charset){
	int i;
	
	i = 0;
	while (charset[i]){
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

/* function to count words in the array string */
int count_words_in_string(char *str, char *charset){
	int i;
	int count;

	if (!str || !charset)
		return (0);

	i = 0;
	count = 0;
	while (str[i]){
		while (str[i] && is_separation(str[i], charset))
			i++;

		if (str[i] && !is_separation(str[i], charset))
		{
			count++;
			while (str[i] && !is_separation(str[i], charset))
				i++;
		}
	}
	return (count);
}

/* function to copy from the string to the allocated memory */
char *ft_strncpy(char *dst, char *src, int size){
	int i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/* ft_split: Split string by charset */
char **ft_split(char *str, char *charset) {
    int   i;      // Index for scanning the original string
    int   j;      // Index for result array (current word position)
    int   len;    // Length of current word
    int   words;  // Total number of words found
    int   start;  // Starting index of current word in str
    char  **result; // Result: array of strings (char** = pointer to string pointers)

    if (!str || !charset)
        return (NULL);

    // STEP 1: Count how many words we have
    words = count_words_in_string(str, charset);

    // STEP 2: Allocate the OUTER ARRAY (array of string pointers)
    // We need space for: words pointers + 1 NULL terminator pointer
    // result is char** (pointer to char*) so we allocate char* sized blocks
    // result[j] is equivalent to *(result + j) - accessing j-th pointer slot
    result = (char**)malloc(sizeof(char*) * (words + 1));
    if (!result)
        return (NULL);

    i = 0;  // Start scanning from beginning of str
    j = 0;  // Start filling result from index 0

    // STEP 3: Extract each word
    while (j < words) {
        // Skip any separator characters
        while (str[i] && is_separation(str[i], charset))
            i++;

        // If we found the beginning of a word
        if (str[i] && !is_separation(str[i], charset)) {
            start = i;  // Remember where word starts
            len = 0;    // Reset word length counter

            // Measure the word length
            while (str[i] && !is_separation(str[i], charset)) {
                len++;  // Count this character
                i++;    // Move to next character in str
            }

            // STEP 4: Allocate memory for THIS SPECIFIC WORD
            // result[j] accesses the j-th slot in the pointer array
            // Equivalent to: *(result + j) = malloc(...)
            // We allocate: len characters + 1 for null terminator
            result[j] = (char*)malloc(sizeof(char) * (len + 1));
            if (!result[j])
                return (NULL);

            // STEP 5: Copy the word into the newly allocated memory
            // &str[start] gives us address of first character of the word
            // len tells how many characters to copy
            ft_strncpy(result[j], &str[start], len);
            // Note: result[j] here is same as *(result + j)
            // ft_strncpy receives the actual pointer to word's memory

            j++;  // Move to next slot in result array
            // j++ means: next time we'll access result[j] which is *(result + j)
            // where j is now increased by 1
        }
    }

    // STEP 6: NULL-terminate the array of pointers
    // Set the last element to NULL, marking end of array
    // result[j] where j == words (after loop) is *(result + words) = NULL
    result[j] = NULL;

    return (result);
}

void	print_split_result(char **result)
{
	int	i;

	if (!result)
	{
		printf("Result is NULL\n");
		return;
	}

	i = 0;
	while (result[i])
	{
		printf("result[%d] = \"%s\"\n", i, result[i]);
		i++;
	}
	printf("result[%d] = NULL (terminator)\n", i);
}

void	free_split_result(char **result)
{
	int	i;

	if (!result)
		return;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

int	main(void)
{
	char	**result;

	printf("=== Test 1: Basic split ===\n");
	result = ft_split("hello,world,test", ",");
	print_split_result(result);
	free_split_result(result);

	printf("\n=== Test 2: Multiple separators ===\n");
	result = ft_split("hello world!test-program", " !-");
	print_split_result(result);
	free_split_result(result);

	printf("\n=== Test 3: Empty string ===\n");
	result = ft_split("", ",");
	print_split_result(result);
	free_split_result(result);

	printf("\n=== Test 4: Only separators ===\n");
	result = ft_split(",,,,", ",");
	print_split_result(result);
	free_split_result(result);

	printf("\n=== Test 5: No separators ===\n");
	result = ft_split("hello", ",");
	print_split_result(result);
	free_split_result(result);

	printf("\n=== Test 6: Multiple consecutive separators ===\n");
	result = ft_split("hello,,,world,,test", ",");
	print_split_result(result);
	free_split_result(result);

	printf("\n=== Test 7: Separators at start and end ===\n");
	result = ft_split(",hello,world,", ",");
	print_split_result(result);
	free_split_result(result);

	printf("\n=== Test 8: Complex charset ===\n");
	result = ft_split("a+b-c*d/e", "+-*/");
	print_split_result(result);
	free_split_result(result);

	return (0);
}


