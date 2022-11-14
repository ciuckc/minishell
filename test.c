#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "src/utils/libft/libft.h"

bool	st_test(char *str)
{
	char	*ms_test;
	char	*bash_test;

	ms_test = ft_strjoin("./minishell ", str);
	bash_test = ft_strjoin("bash -c ", str);
	if (system(ms_test) == system(bash_test))
		return (true);
	return (false);
}

int	main(void)
{
	char	**tests;

	tests = (char *[]){"\"exit 0\"", \
	"\"exit 42\"", "\"exit -255\"", \
	"\"exit +255\"", "\"exit 42 53 68\"", \
	"\"exit 259\"", "\"exit 555555555555555555\"", \
	"\"exit -4\"", "\" exit 2a dfg\"", \
	"\"exit 2.2 3 3\"", "\"exit 222,03\"", \
	"\"exit wrong\"", "\" exit wrong_command\"", \
	"\"exit cat\"", "\"|\"", \
	"\"exit --5\"", "\"exit ++5\"", NULL};
	while (*tests)
	{
		if (!st_test(*tests))
			printf("error: where test is %s\n", *tests);
		else
			printf("ok: where test is %s\n", *tests);
		tests++;
	}
}
