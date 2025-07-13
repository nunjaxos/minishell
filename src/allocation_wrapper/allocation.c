#include "../../include/executor.h"

void	*ft_malloc(size_t size, t_alloc **alloc)
{
	void	*allocated = malloc(size);
	if (!allocated)
		return (NULL);
	add_alloc(allocated, alloc);
	return (allocated);
}

void	add_alloc(void *allocated, t_alloc **alloc)
{
	t_alloc	*list;
	t_alloc	*new_alloc;

	if (!alloc || !allocated)
		return ;
	new_alloc = malloc(sizeof(t_alloc));
	if (!new_alloc)
		return ;
	new_alloc->allocated = allocated;
	new_alloc->next = NULL;

	if (!*alloc)
		*alloc = new_alloc;
	else
	{
		list = *alloc;
		while (list->next)
			list = list->next;
		list->next = new_alloc;
	}
}
