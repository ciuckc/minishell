/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashmap.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 00:34:18 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/23 19:00:15 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# include <stdlib.h>
# include <stdbool.h>

# define DEFAULT_HASH_TABLE_SIZE 128
# define HASH_TABLE_512 512
# define HASH_TABLE_1024 1024

/**
 * @brief Used for the Hashing function. Check out the FNV-1a and FNV-1 hash
 * function. This is the offset seed that we use, so we don't get a lot of 
 * collisions.
 */
# define FNV_OFFSET 0x811c9dc5
/**
 * @brief Used for the Hashing function. Check out the FNV-1a and FNV-1 hash
 * function. The prime is purely mathematically calculated idk.
 */
# define FNV_PRIME 0x01000193

/**
 * @brief Default container that has information about the stored data
 * @param next pointer to the previous added container. Points to NULL if
 * it's the first or last one. If you need to iterate through the list, pass
 * this struct through an iterator function so we don't lose the HEAD of 
 * the list.
 * @param prev previous visited node
 * @param data The literal the that is stored inside this container.
 * @param key_string The string which was hashed in order to associate the 
 * data with it.
 * @param hash The hash that was generated after the string in order to index
 * our container in the hash table.
 */
typedef struct s_container
{
	struct s_container	*next;
	struct s_container	*prev;
	char				*key_str;
	void				*data;
	u_int32_t			hash;
	u_int32_t			items;
}	t_container;

/**
 * @brief Hash map table, everything will be added in the double ptr table.
 * @param containers How big is our table.
 * @param entries How much of it was filled.
 */
typedef struct s_table
{
	t_container	**table;
	u_int32_t	containers;
	u_int32_t	entries;
}	t_table;

/**
 * @brief Initializes n(containers). If value is 0, then it's
 * automatically initialized to the default table size -> 128.
 * @param containers How many containers should be initialized
 * @return t_table* -> table and t_container **[LEN] are malloc'ed
 */
t_table		*init_table(u_int32_t containers);

/**
 * @brief Hashes the key and inserts the data that comes with it in the array.
 * If there is a colision all the collision items will be chained in the 
 * container, through the next pointer.
 * @param key the string which is hashed.
 * @param data the actual data that we store.
 * @param hash_table the hash table which contains all the containers.
 * @return t_container* to the last added item.
 */
t_container	*insert_in_table(char *key, void *data, t_table **hash_table);

/**
 * @brief Creates a 32 bit hash out of a sequence of bytes using the FNV-1A
 * hashing algorithm.
 * @param string The string that gets hashed.
 * @return u_int32_t hash value (needs to be modulo'ed by how many t_table 
 * ->containers we have, in order to acces the array of containers).
 */
u_int32_t	hash_string(char *string);

/**
 * @brief Searches for the data related to the key provided in the hash table. 
 * If the data searched for is not found, it returns NULL. 
 * @param key The string key that we use to search for our data.
 * @param hash_map Where we search.
 * @return t_container* Pointer to the container which holds the actual data.
 */
t_container	*item_search(char *key, t_table *hash_map);

/**
 * @brief Frees the item associated with the key. It returns a void * 
 * to the data that we used to have in the container so we can either 
 * free it or use it for later.
 * @param key The string key that we use to search for our data.
 * @param map Where we search.
 * @return void* to the place where we hold our data. Return NULL if
 * it didn't find that item.
 */
void		*remove_item(char *key, t_table **map);

/**
 * @brief Frees all the inserted containers. Frees the t_table as well. !!!It
 * doesn't free the data and keys associated with each container!!!.
 * @param map Freeing everything in here.
 */
void		remove_all(t_table *map);

#endif
