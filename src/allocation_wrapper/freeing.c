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
			free(list->allocated);
		free(list);
		list = tmp;
	}
	*alloc = NULL;
}

static void	remove_from_list(t_alloc **alloc, t_alloc **list, t_alloc *prev)
{
	if (prev)
		prev->next = (*list)->next;
	else
		*alloc = (*list)->next;
}

static void	free_allocated_memory(t_alloc *list)
{
	if (list && list->allocated)
	{
		free(list->allocated);
		list->allocated = NULL;
	}
}

static void	free_list_node(t_alloc *list)
{
	if (list)
		free(list);
}

void	ft_free(void *ptr, t_alloc **alloc)
{
	t_alloc	*list;
	t_alloc	*prev;

	if (!ptr || !alloc || !*alloc)
		return ;
	list = *alloc;
	prev = NULL;
	while (list)
	{
		if (list->allocated == ptr)
		{
			remove_from_list(alloc, &list, prev);
			free_allocated_memory(list);
			free_list_node(list);
			break ;
		}
		prev = list;
		list = list->next;
	}
}
