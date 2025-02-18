/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilhem <guilhem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:35:05 by grouger           #+#    #+#             */
/*   Updated: 2025/02/12 16:56:28 by guilhem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef    MINISHELL_H
# define   MINISHELL_H
#ifndef    BUFFER_SIZE
# define   BUFFER_SIZE 10
# endif

extern int g_exit_value;

# define   bool unsigned int
# define   TRUE 1
# define   FALSE 0


# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../libft/libft.h"
// typedef struct s_token 

typedef struct s_token {
  char *str;
  int type;
  bool dq;
  bool sq;
  char *path;
  char **arg;
  bool  builtins;
  struct s_token *prev;
  struct s_token *next;
  struct s_data *data;
} t_token;

// typedef struct s_data 


typedef struct s_data {
  struct s_env  *env;
  char   *line;
  int     fd_in;
  int     fd_out;
  char    *user;
  char    *prompt;
  bool    dq;
  bool    sq;
  int     p_index; //FULL BUGER: pas le bon index
  char    *minishell_path;
  char    **path; //path de je ne sais pas quoi
  int     nb_path; //nombre de path
  char    **list_path; // liste des path ??
  struct s_list *cmd; 
  struct s_token *token;
  char           ***args; // ??
  int     pipe_nbr;
  int     ope_nbr;
  int     id_pipe; //???
  int     pipe[2]; //pipe mais buger je pense
}      t_data;

// typedef struct s_data 

typedef struct s_split {
  bool  in_quote;
  char  c;
  char  quote_char;
} t_split;

typedef struct s_quote {
  bool  in_quote;
  char  quote_char;
  size_t   j;
  size_t   i;
  size_t   start;
} t_quote;

//typedef struct s_env

typedef struct s_env {
  char *str;
  int index;
  int first_value;
  struct s_env *prev;
  struct s_env *next;
} t_env;

//fonction
void  starting_message(void);
void  setup(char **env, t_data *data);
bool  parsing(char *line, t_data *data );
bool check_line(char *line);
void  path_setup(char **env, t_data *data);
void  env_setup(char **env, t_data *data);
bool  spliting_cmd(char *line, t_data *data);
bool check_endother(char *line);
void  list_path_setup(t_data *data);
void  signal_setup(void);
bool  emptyline(char *line);
void  print_prompt(void);
char  *get_prompt(t_data *data);
int ft_strtablen(char ***tab);
//utils
void print_data(t_data *data);
int     tablen(char **tab);
int     is_dollar(char *str);
int     countarg(t_token *token);
//t_env   *get_env_var(char *var, t_data *data);
char    *replace_var(char *str);
char    **env_to_tab(t_env *env);
bool    other_cmd(t_token *token);
char    *var_end(char *str, char *var, char *end, char *temp);
t_token  *next_cmd(t_token *token);
char	*create_token(const char *start, const char *end);
char	*get_next_line(int fd);
int	    ft_isalphalen(char *str);

//built-in
void	 echo_command(char **args);
void	 cd_command(char **args, t_data *data);
bool   do_var_exist(t_data *data, char *var);
void	 export_command(char **args, t_data *data);
void   unset_command(char **args, t_data *data);
void	 free_env(t_env *env);
void   pwd_command(void);
void	 exit_command(t_data *data);
void   env_command(char **args, t_data *data);

//quote
char **quote_fusion(char **tab, t_data *data);
bool quote_check(char *line);

//Token
t_token *token_create(char *str, int token);
t_token *last_token(t_token *lst);
bool    token_setup(t_data *data);
bool token_verif(t_token *token);
void   setup_arg(t_token *token);
bool lastredir_check(t_token *token);
void    token_add_back(t_token **lst, t_token *tok);
void	  token_clear(t_token **lst, void (*del)(void *));
void    token_quote(char *str, t_token *new);

//ft_split
void	*ft_calloc(size_t nm, size_t n);
char	**ft_split(char *str, char *charset);
char **split_quote(const char *line, t_quote *q);
char **split_sep(char **input, const char *sep);
void	split_1(char *start, int *j, char **result, t_split *s);
char *split_2(char *start, bool in_quotes);
//lib
char	*ft_strnstr(const char *str, const char *srch, size_t n);
void	ft_bzero(void *s, size_t n);
char	*ft_itoa(int n);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
int	  ft_isalpha(int c);
int	  ft_isascii(int c);
char	*ft_strstr(const char *str, const char *srch);

//
void	env_add_back(t_env **lst, t_env *neew);
t_env *env_create(char *str, int index);
t_env *last_env(t_env *lst);
void	env_clear(t_env **lst);
int is_pid(char *str);
char *replace_pid(char *str);
void clear_all(t_data *data);
void clear_single(t_data *data);
int	count_replace(char *str);
int next_dollar(char *str);
int is_exitcode(char *str);
char *replace_exitcode(char *str);
void clear_tab(char **tab);
void clear_2tab(char ***tab);


//Exec
bool task_cmd(t_data *data);
bool	exec_cmd(t_data *data, t_token *token);
bool 	exec_pipe(t_data *data, t_token *token);
bool exec_all(t_token *token, t_data *data);
bool exect_builtin(char **args, t_data *data);
void change_pipe(t_data *data, int in, int out, int status);
bool ifbuiltin(char **args);


//Operator
int	ft_trunc(char **args);
int	ft_append(char **args);
int operator_choice(char **tab, int *fd);
void  count_operator(t_data *data);

# define INPUT 1    //"<"
# define HEREDOC 2 //"<<"
# define TRUNC 3   //">"
# define APPEND 4  //">>"
# define PIPE 5    //"|"
# define CMD 6     //"|"
# define ARG 7     //"|"
# define PARAM 8

# define RESET \033[036m

# define BLACK \033[0;336m
# define RED \033[0;31m
# define GREEN \033[0;32m
# define YELLOW \033[0;93m
# define BLUE \033[0;34m
# define PURPLE \033[0;35m
# define CYAN \033[0;36m
# define White \033[0;37m

#endif