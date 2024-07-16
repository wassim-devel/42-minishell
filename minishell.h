/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:51:40 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/23 10:28:34 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdbool.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libftprintf/libprint.h"

extern int	g_last_sig;

enum e_type
{
	WORD,
	OPERATOR,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_FILE,
	DELIMITER,
	CMD,
	ARG,
	BUILTIN
};

typedef struct s_envlst
{
	char			*key;
	char			*value;
	int				only_export;
	struct s_envlst	*next;
}	t_envlst;

typedef struct s_wordlst
{
	char				*word;
	int					type;
	struct s_wordlst	*next;
}	t_wordlst;

typedef struct s_processlst
{
	int					pid;
	char				**argv;
	int					fd_in;
	int					fd_out;
	struct s_processlst	*next;
	int					is_piped;
	int					complete;
	int					status;
	int					builtin_index;
}	t_processlst;

typedef struct s_shell
{
	t_envlst		*envlst;
	char			**envarray;
	char			**builtins;
	int				last_status;
	char			*prompt;
	char			*line;
	t_wordlst		*wordlst;
	t_processlst	*processlst;
}	t_shell;

char		*env_get_value(t_envlst *envlst, char *key);
int			env_set_value(t_envlst **envlst, char *keyvalue);
t_envlst	*env_elem_create(char *keyvalue);
int			env_lst_add(t_envlst **envlst, char *keyvalue);
void		env_putvalue(char *keyvalue, char *elem_value);
void		env_putkey(char *keyvalue, char *elem_key);
void		env_destroy(t_envlst *envlst);
t_envlst	*env_lst_copy(char **env);
size_t		env_lst_len(t_envlst *env_list);
char		**env_array_convert(t_envlst *env_list);

void		ft_add_history(char *line);

int			is_blank(char c);
int			is_metacharacter(char c);
bool		check_only_blanks(const char *command_line);
bool		check_letter_before(const char *command_line,
				ssize_t i, bool is_pipe);
bool		check_error(const char *command_line);

size_t		word_len(char *line);
char		*get_word(char **line);
int			add_word(char **line, t_wordlst **word_list);
int			parse_words(char *line, t_wordlst **word_list);
void		spot_operators(t_wordlst *wordlst);
void		spot_words(t_shell *shell);
int			get_redir_files(t_wordlst *wordlst, t_processlst *process);
int			get_args(t_wordlst *wordlst, t_processlst *process,
				t_shell *shell);
char		*retrieve_absolute_path(t_envlst *envlst, const char *executable);
int			parse_cmd(t_shell *shell);

size_t		len_for_variable(const char *str, size_t i);
int			set_flag(const char c, int flag);
char		*grab_variable(const char *str);
size_t		len_of_variables(const char *str);
size_t		len_of_variables_values(const char *s, t_envlst *envlst);
size_t		len_without_quotes(const char *str);
int			expand_line(t_shell *shell);
char		*expand_interr(const char *str, int last_status);
char		*expand_variables(const char *str, t_envlst *envlst);
int			quote_removal(t_wordlst *wordlst);

int			connect_pipe(t_processlst *process_lst, t_processlst *new_process);

int			exec_processlst(t_shell *shell);

void		clean_wordlst(t_wordlst **wordlst);
int			clean_processlst(t_processlst **processlst, t_shell *shell);
int			clean_shell(t_shell *shell);
void		free_envarray(char **envarray);
int			minishell_loop(t_shell *shell);
int			main_signal_handlers(void);
int			heredoc_signal_handler(void);
void		fork_signal_handler(void);
int			exec_signal_handler(void);
void		main_sig_int_handler(int sig);
void		exec_sig_int_handler(int sig);
void		heredoc_sig_int_handler(int sig);
int			void_event(void);
void		wait_job_completion(t_processlst *processlst);

char		**array_convert_for_export(t_envlst *env_list);
int			exec_builtin(t_processlst *processlst, t_shell *shell);
void		bi_echo(const char **args, int fd_out);
int			bi_cd(char **argv, int is_piped, t_envlst **envlst);
int			bi_env(t_envlst *envlst, char **args, int fd_out);
int			bi_exit(t_shell *shell_to_free, char **args, int is_piped);
int			bi_export(char **args, t_envlst **envlst, int is_piped, int fd_out);
int			bi_pwd(int fd_out);
int			bi_unset(char **args, t_envlst **envlst, int is_piped);
#endif
