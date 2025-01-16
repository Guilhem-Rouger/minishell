/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillot <bguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:45:01 by bguillot          #+#    #+#             */
/*   Updated: 2024/10/08 14:36:06 by bguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_exit_value;

void  signal_handler(int sig)
{
  if (sig == SIGINT)
  {
    ft_putstr_fd("\n", 1);
    print_prompt();
    rl_on_new_line();
  }
  if (sig == SIGQUIT)
  {
    ft_putstr_fd("\n", 1);
    print_prompt();
    rl_on_new_line();
  }
}

void  waiting_command(t_data *data)
{
  char	  *line;

  signal(SIGQUIT, &signal_handler);
  signal(SIGINT, &signal_handler);
  line = NULL;
  while(1)
  {
      if (line)
        free(line);
      line = readline(get_prompt(data));
      if (line == NULL)
      {
        rl_clear_history();
        break ;
      }
      if (!emptyline(line))
        continue;
      add_history(line);
      if (!parsing(line, data))
        continue;
      task_cmd(data);
    clear_tab(data->path);
    clear_2tab(data->args);
    free(data->args);
  }
  clear_all(data);
}

int  main(int argc, char **argv, char **env)
{  
  t_data	data;

  g_exit_value = 0;
  (void)argc;
  (void)argv;
  setup(env, &data);
  waiting_command(&data);
  return (g_exit_value);
}