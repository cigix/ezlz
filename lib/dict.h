#pragma once

#include <stddef.h>
#include <stdint.h>

#include "bytes.h"

struct dictionary_entry
{
  uint8_t *bytes;
  size_t size;
};

struct dictionary
{
  struct dictionary_entry *entries;
  size_t size;
  size_t capacity;
};

/* Allocate a new dict with some prefilled entries. Return NULL in case of
** error. */
struct dictionary *init_dict(void);

/* Free a dict and its underlying buffers. */
void free_dict(struct dictionary *);

/* Add a new entry in the dict. May reallocate the existing entries. The bytes
** are duplicated. Return -1 in case of error, the position otherwise. */
int dict_add_entry(struct dictionary *, uint8_t const *, size_t);

/* Get the position for a an entry, or -1 if no entries are found. */
int dict_find(struct dictionary *, const uint8_t *, size_t);

/* Get the entry for a position, or NULL if the entry does not exist. */
struct dictionary_entry const *dict_get(struct dictionary *, size_t);
