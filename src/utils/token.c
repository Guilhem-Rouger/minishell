#include "../../include/minishell.h"

int	choose_token(t_list *lst, t_token *token)
{
	if (lst->str[0] == '|')
		return (PIPE);
	if (ft_lstlast(lst) != lst)
	{
		if (lst->str[0] == '>' && lst->next->str[0] == '>')
			return (APPEND);
		if (lst->str[0] == '<' && lst->next->str[0] == '<')
			return (HEREDOC);
	}
	if (lst->str[0] == '<')
		return (INPUT);
	if (lst->str[0] == '>')
		return (TRUNC);
	if (lst->str[0] == '-')
		return (PARAM);
	if (token != NULL)
	{
		if (token->type == PIPE)
			return (CMD);
		else
			return (ARG);
	}
	return (CMD);
}

bool	token_setup(t_data *data)
{
	t_list	*it;
	char	*str_to_use;
	int		toktok;

	it = data->cmd;
	if (!data->cmd)
		return (FALSE);
	data->token = NULL;
	while (it)
	{
		toktok = choose_token(it, last_token(data->token));
		if (toktok == HEREDOC || toktok == APPEND)
		{
			str_to_use = ft_strjoin(ft_strdup(it->str), it->next->str);
			token_add_back(&(data->token), token_create(str_to_use, toktok));
			it = it->next->next;
		}
		else
		{
			str_to_use = ft_strdup(it->str);
			token_add_back(&(data->token), token_create(str_to_use, toktok));
			it = it->next;
		}
	}
	return (TRUE);
}
