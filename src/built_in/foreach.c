/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** foreach
*/

#include "../../include/struct.h"

static int init_foreach_ctx(struct foreach_ctx *ctx, tcsh_t *term,
    char **argv, bool *error)
{
    (void)term;
    ctx->action = take_action(error, "end");
    if (*error == true)
        return my_cmd_error(": end not found.\n", "foreach", ALT_EXIT);
    ctx->values = my_str_to_word_array(argv[1], " ()\n\t");
    if (ctx->values == NULL)
        return ALT_EXIT;
    if (!foreach_is_valid_name(argv[0]))
        return my_cmd_error(": Variable name must begin with a letter.\n",
            "set", ALT_EXIT);
    return SUCCESS_EXIT;
}

static int foreach_cleanup(struct foreach_ctx *ctx, int res)
{
    free_array(ctx->values);
    free_array(ctx->action);
    return res;
}

int in_for(tcsh_t *term, char **argv, bool *error)
{
    struct foreach_ctx ctx = {0};
    int res = init_foreach_ctx(&ctx, term, argv, error);

    if (res != SUCCESS_EXIT)
        return foreach_cleanup(&ctx, res);
    for (int i = 0; ctx.values[i] != NULL; i++) {
        res = my_set(term, (char *[]){argv[0], "=", ctx.values[i], NULL});
        if (res == SUCCESS_EXIT)
            res = foreach_execute_actions(term, ctx.action);
        if (res != SUCCESS_EXIT)
            break;
    }
    return foreach_cleanup(&ctx, res);
}

int my_foreach(tcsh_t *term, char **argv)
{
    int len = len_array(argv);
    bool error = false;

    if (len < 2)
        return my_cmd_error(": Too few arguments.\n", "foreach", ALT_EXIT);
    if (len > 2)
        return my_cmd_error(": Words not parenthesized.\n",
            "foreach", ALT_EXIT);
    if (correct_name(argv[0], "foreach") != SUCCESS_EXIT)
        return ALT_EXIT;
    return in_for(term, argv, &error);
}
