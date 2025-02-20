#include "../include/minishell.h"


// Fonction pour afficher toutes les données de la structure t_data
void print_data(t_data *data) {

	/*Affiche l'environnemnt de la struct */
    //printf("Environment Variables:\n");
    //t_env *env = data->env;
    //while (env) {
    //    printf("  %s\n", env->str);
    //    env = env->next;
    //}


	/* le prompte en entier */
    printf("Line: %s\n", data->line);

	/* les file descriptors */ 
    printf("File Descriptor In: %d\n", data->fd_in);
    printf("File Descriptor Out: %d\n", data->fd_out);

	/* les variables */
    printf("User: %s\n", data->user); //user
    printf("Prompt: %s\n", data->prompt);//prompt AVEC LE READLINE
  //  printf("Double Quote: %s\n", data->dq ? "true" : "false"); //double quote ?
  //  printf("Single Quote: %s\n", data->sq ? "true" : "false"); //single quote ?
    printf("Pipe Index: %d\n", data->p_index); //pipe index //FULL BUGER
    printf("Minishell Path: %s\n", data->minishell_path); //minishell path

    printf("Paths:\n"); //path ?? 
    for (int i = 0; i < data->nb_path; i++) {
        printf("  %s\n", data->path[i]);
    }

    printf("List Paths:\n"); //list path ??
    for (int i = 0; i < data->nb_path; i++) {
        printf("  %s\n", data->list_path[i]);
    }

    printf("Number of Pipes: %d\n", data->pipe_nbr); //nombre de pipe
    printf("Number of Operators: %d\n", data->ope_nbr); //nombre de redirections
    printf("ID Pipe: %d\n", data->id_pipe); //id pipe ??
    printf("Pipe: [%d, %d]\n", data->pipe[0], data->pipe[1]); //pipe ??
    printf("Commands:\n");

    /*Affiche les commandes de la struct list */
    t_list *cmd = data->parsing;
    while (cmd) {
        printf("  %s\n", cmd->str);
        cmd = cmd->next;
    }

    /*Affiche les arguments de la struct token*/
    printf("Tokens:\n");
    t_token *token = data->token;
    int i = 0;
    while (token) {
        printf("  String: %s\n", token->str);
        printf("  Type: %d\n", token->type);
        printf("  Double Quote: %s\n", token->dq ? "true" : "false");
        printf("  Single Quote: %s\n", token->sq ? "true" : "false");
        printf("  Builtin: %s\n", token->builtins ? "true" : "false");
        if (token->arg)
        {
            while (token->arg[i])
            {
                printf("  Arg%d: %s\n", i, token->arg[i]);
                i++;
            }
        }
        printf("   Path: %s\n", token->path);
        token = token->next;
    }

    printf("CMD:\n");
    t_cmd *cmdd = data->cmd;
    i = 0;
    while (cmdd) {
        i = 0;
        printf("  String: %s\n", cmdd->cmd);
        printf("  Builtin: %s\n", cmdd->is_built ? "true" : "false");
        while (cmdd->argv[i])
        {
            printf("  Arg%d: %s\n", i, cmdd->argv[i]);
            i++;
        }
        cmdd = cmdd->next;
    }


    // Assuming cmd and token are lists, you might want to iterate and print them as well
    // This part is left as an exercise as it depends on the structure of s_list and s_token
}