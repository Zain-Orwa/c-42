#include <stdio.h>
#include <stdlib.h>

int is_separation(char c, char *charset){
	int i;

  i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}


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

int ft_strlen(char *str){
	int len;

	len = 0;
	while (str[len])
		len++;

	return (len);
}

int count_words_in_str(char *str, char *charset){
	int i;
	int count;

	if (!str || !charset)
		return (0);

	i = 0;
  count = 0;
	while (str[i])
	{
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

/* ft_split: Split string by charset */
char **ft_split(char *str, char *charset){
    int   i;           // Index for scanning the original string
    int   j;           // Index for result array (current word position)
    int   word_len;    // Length of current word
    int   word_start;  // Starting index of current word in str
    int   words_count; // Total number of words found
    char **result;     // Result: array of strings (char** = pointer to string pointers)

    if (!str || !charset)
        return (NULL);

    // STEP 1: Count how many words we have in the input string
    words_count = count_words_in_str(str, charset);

    // STEP 2: Allocate the OUTER ARRAY (array of string pointers)
    // We need space for: words_count pointers + 1 NULL terminator pointer
    result = (char**)malloc(sizeof(char*) * (words_count + 1));
    if (!result)
        return (NULL);

    i = 0;  // Start scanning from beginning of str
    j = 0;  // Start filling result from index 0

    // STEP 3: Extract each word
    while (j < words_count)
    {
        // Skip any separator characters
        while (str[i] && is_separation(str[i], charset))
            i++;

        // If we found the beginning of a word
        if (str[i] && !is_separation(str[i], charset))
        {
            word_start = i;  // Remember where the word starts
            word_len = 0;    // Reset word length counter

            // Measure the word length
            while (str[i] && !is_separation(str[i], charset))
            {
                word_len++;  // Count this character
                i++;         // Move to next character in str so the loop continue for the whole word//
            }

            // STEP 4: Allocate memory for THIS SPECIFIC WORD
            // We allocate: word_len characters + 1 for the null terminator
            result[j] = (char*)malloc(sizeof(char) * (word_len + 1));
            if (!result[j])
            {
                // Cleanup on allocation failure without extra variable
                while (j--)
                    free(result[j]);
                free(result);
                return (NULL);
            }

            // STEP 5: Copy the word into the newly allocated memory
            // &str[word_start] gives us address of first character of the word
            // word_len tells how many characters to copy
            ft_strncpy(result[j], &str[word_start], word_len);

            j++;  // Move to next slot in result array
        }
    }

    // STEP 6: NULL-terminate the array of pointers
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
