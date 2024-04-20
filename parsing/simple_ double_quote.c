

int	ft_simple_quote(char *str)
{
	int	i;
	int n;

	n = 0;
	i = 0;
	while (str[i])
	{
		if (str[i]== '\'')
			n++;
		i++;
	}
	if (n % 2== 0)
		return (0);
	return (1);
}

int	ft_double_quote(char *str)
{
	int	i;
	int n;

	n = 0;
	i = 0;
	while (str[i])
	{
		if (str[i]== '\"')
			n++;
		i++;
	}
	if (n % 2== 0)
		return (0);
	return (1);
}
