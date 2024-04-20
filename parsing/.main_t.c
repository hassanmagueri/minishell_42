#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_export{
	char *key;
	char *value;
}   t_export;

void set_var(t_export *pairs, int num_pairs, char *key, char *value)
{
	int i = 0;

	while ( i < num_pairs)
	{
		if (strcmp(pairs[i].key, key) == 0)
		{
			free(pairs[i].value);
			pairs[i].value = strdup(value);
			return;
		}
		i++;
	}

	pairs[num_pairs].key = strdup(key);
	pairs[num_pairs].value = strdup(value);
}

char *get_var(t_export *pairs, int num_pairs, char *key)
{
	int i = 0;
	while ( i < num_pairs)
	{
		if (strcmp(pairs[i].key, key) == 0)
			return pairs[i].value;
		i++;
	}
	return (NULL);
}

void add_variables_to_environment(t_export *pairs, int num_pairs)
{
	int i = 0;
    while ( i < num_pairs)
	{
        if (setenv(pairs[i].key, pairs[i].value, 1) != 0)
            perror("Error setting environment variable");
		i++;
	}
}
