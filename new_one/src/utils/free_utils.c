#include "../../include/executor.h"

void	garbage_removal(t_alloc **alloc)
{
	t_alloc	*list;
	t_alloc	*tmp;

	if (!alloc || !*alloc)
		return ;
	list = *alloc;
	while (list)
	{
		tmp = list->next;
		if (list->allocated)
		{
			free(list->allocated);
			list->allocated = NULL;
		}
		if (list)
		{
			free(list);
			list = NULL;
		}
		list = tmp;
	}
	*alloc = NULL;
}

void free_data(t_data *data)
{	
    garbage_removal(&(data->alloc));
    rl_clear_history();
}

static void remove_from_list(t_alloc **alloc, t_alloc **curr, t_alloc *prev)
{
    if (prev)
        prev->next = (*curr)->next;
    else
        *alloc = (*curr)->next;
}

static void	free_allocated_memory(t_alloc *curr)
{
	if (curr->allocated)
	{
		free(curr->allocated);
		curr->allocated = NULL;
	}
}
static void	free_curr_node(t_alloc *curr)
{
	if (curr)
	{
		free(curr);
		curr = NULL;
	}
}

void ft_free(void *ptr, t_alloc **alloc)
{
    t_alloc *curr;
    t_alloc *prev;

    if (!ptr || !alloc || !*alloc)
        return ;
    curr = *alloc;
    prev = NULL;
    while (curr)
    {
        if (curr->allocated == ptr)
        {
            remove_from_list(alloc, &curr, prev);
            free_allocated_memory(curr);
            free_curr_node(curr);
            break ;
        }
        prev = curr;
        curr = curr->next;
    }
}