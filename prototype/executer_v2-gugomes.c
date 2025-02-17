/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_v2-gugomes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:13:50 by marvin            #+#    #+#             */
/*   Updated: 2025/02/17 15:07:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/workspace/minishell/inc/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

void		free_array(char **array);
char		**ft_lst_to_array(t_list *lst);
char		*get_command_path(char *cmd, char **env);
static void	handle_error(char **args, char *message, int exit_code);
static void	execute_command(t_command *cmd, char **env);
static void child_process(t_command *cmd, int pipe_fd[2], \
	int input_fd, int has_next, char **env);
static void	execute_pipeline(t_list *commands, char **env);
int			open_file(const char *filepath, int flags);

static void handle_error(char **args, char *message, int exit_code)
{
    ft_putstr_fd(message, 2);
    if (args && args[0])
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(args[0], 2);
    }
    ft_putstr_fd("\n", 2);
    free_array(args);
    exit(exit_code);
}

void free_array(char **array)
{
    int i = 0;
    if (!array)
        return;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

char **ft_lst_to_array(t_list *lst)
{
    char **array;
    int i = 0;
    int size = ft_lstsize(lst);

    array = (char **)malloc(sizeof(char *) * (size + 1));
    if (!array)
        return NULL;
    while (lst)
    {
        array[i] = ft_strdup((char *)lst->content);
        if (!array[i])
        {
            free_array(array);
            return NULL;
        }
        lst = lst->next;
        i++;
    }
    array[i] = NULL;
    return array;
}

char *get_command_path(char *cmd, char **env)
{
    int i;
    char **paths;
    char *full_path;
    char *temp;
    t_env_var *path_var;

    // Convert env array to t_list
    t_list *env_list = extract_env_vars(env);

	if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, F_OK | X_OK) == 0)
            return ft_strdup(cmd);
        return NULL;
    }

    path_var = get_env_var(env_list, "PATH");
    if (!path_var || !path_var->value)
    {
        ft_lstclear(&env_list, free_env_var);
        return cmd;
    }

    paths = ft_split(path_var->value, ':');
    if (!paths)
    {
        ft_lstclear(&env_list, free_env_var);
        return cmd;
    }

    i = 0;
    while (paths[i])
    {
        temp = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(temp, cmd);
        free(temp);
        if (full_path && access(full_path, F_OK | X_OK) == 0)
        {
            free_array(paths);
            ft_lstclear(&env_list, free_env_var);
            return full_path;
        }
        free(full_path);
        i++;
    }
    free_array(paths);
    ft_lstclear(&env_list, free_env_var);
    return cmd;
}

static void	execute_command(t_command *cmd, char **env)
{
    char	**args;
    char	*path;

    args = ft_lst_to_array(cmd->arguments);
    if (!args || !args[0])
        handle_error(args, "ERROR: command not found\n", 127);
    path = get_command_path(args[0], env);
    if (!path)
        handle_error(args, "ERROR: command not found: ", 127);
    if (execve(path, args, env) == -1)
        handle_error(args, "execve failed in execute_command", 127);
    free_array(args);
}

static void child_process(t_command *cmd, int pipe_fd[2], int input_fd, int has_next, char **env)
{
    if (input_fd != STDIN_FILENO)
    {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    if (has_next)
    {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        close(pipe_fd[0]);
    }
    execute_command(cmd, env);
}

static void execute_pipeline(t_list *commands, char **env)
{
    int pipe_fd[2];
    int input_fd = STDIN_FILENO;
    pid_t pid;
    t_command *cmd;
    int has_next;

    while (commands)
    {
        cmd = (t_command *)commands->content;
        has_next = (commands->next != NULL);

        if (has_next && pipe(pipe_fd) == -1)
        {
            perror("pipe failed");
            exit(1);
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0)
        {
            child_process(cmd, pipe_fd, input_fd, has_next, env);
        }
        else
        {
            if (has_next)
            {
                close(pipe_fd[1]);
            }
            if (input_fd != STDIN_FILENO)
            {
                close(input_fd);
            }
            input_fd = has_next ? pipe_fd[0] : STDIN_FILENO;
            commands = commands->next;
        }
    }
    while (wait(NULL) > 0);
}

int	open_file(const char *filepath, int flags)
{
    int fd;

    if (flags == 0)
        fd = open(filepath, O_RDONLY);
    else if (flags == 2)
        fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else
        fd = -1;

    if (fd == -1)
        perror("open failed");

    return fd;
}

int	main(int argc, char **argv, char **env)
{
    t_minish	msh;

    (void)argc;
    (void)argv;
    while (1)
    {
        msh.input = readline("minishell> ");
        if (!msh.input)
            break ;
        msh.tokens = extract_tokens(msh.input);
        if (!is_token_list_valid(msh.tokens))
        {
            ft_lstclear(&msh.tokens, free);
            free(msh.input);
            continue ;
        }
        msh.commands = extract_commands(msh.tokens);
        ft_lstclear(&msh.tokens, free);
        execute_pipeline(msh.commands, env);
        ft_lstclear(&msh.commands, free_command);
        add_history(msh.input);
        free(msh.input);
    }
    return (0);
}