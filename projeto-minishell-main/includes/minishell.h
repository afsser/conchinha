#ifndef MINISHELL_H
# define MINISHELL_H

// Libs
# include "../libs/libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>

# include "tokenizer.h"
# include "parser.h"
# include "debug.h"
# include "ast.h"
# include "execution.h"
# include "builtin.h"

# define LLONG_MAX 9223372036854775807LL

extern volatile sig_atomic_t	g_signal_status;

//Structs
typedef struct s_mini			t_mini;
typedef struct s_token			t_token;
typedef struct s_env			t_env;
typedef struct s_tree			t_tree;
typedef struct s_hdoc			t_hdoc;
typedef struct termios			t_termios;

struct s_mini
{
	char						*line;
	int							backup_fd_in;
	int							exit_status;
	long long int				num_lines;
	t_env						*env_list;
	t_tree						*tree;
	t_hdoc						*hdoc;
	t_termios					term;
};

struct s_hdoc
{
	char						*delimiter;
	char						*filename;
	char						*history_block;
	int							temp_fd;
	int							exit_flag;
	int							suffix_doc;
	int							nb_line_del;
};

void							init_minishell(t_mini *mini, char **envp);
void							update_mini(t_mini *mini);
void							m_init_signals(void);
int								m_update_nb_lines(int num);
int								m_is_input_null(t_mini *mini);
int								m_minishell_on(t_mini *mini);

// Lexical Analysis Functions
t_token							*m_lexical_analysis(t_mini *mini);
int								m_check_line_input(const char *line);
char							*m_clean_qts(char *lexeme);
void							m_sig_int(int signum);

// Parsing Functions
t_token	*m_parse_tokens(t_token **token_list, t_token **parsed_list, t_mini *mini);

void							m_exec_signals(int pid);
int								m_heredoc( t_token **parsed_list, t_mini *mini);
void							m_aux_heredoc(t_hdoc *hdoc, t_token *node, t_mini *mini);
void							m_heredoc_delete_files(t_mini *mini);

#endif
