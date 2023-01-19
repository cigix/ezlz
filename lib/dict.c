#include "dict.h"

#include <stdlib.h>
#include <string.h>

#define DICT_INITIAL_CAPACITY 512

struct dictionary *init_dict(void)
{
  struct dictionary *dict = malloc(sizeof(struct dictionary));
  if (!dict)
    return NULL;

  dict->capacity = DICT_INITIAL_CAPACITY;
  dict->entries = malloc(sizeof(struct dictionary_entry) * dict->capacity);
  if (!dict->entries)
    return NULL;
  dict->size = 256;

  for (int i = 0; i < 256; ++i)
  {
    dict->entries[i].bytes = malloc(1);
    if (!dict->entries[i].bytes)
      return NULL;
    dict->entries[i].bytes[0] = i;
    dict->entries[i].size = 1;
  }

  return dict;
}

void free_dict(struct dictionary *dict)
{
  for (size_t i = 0; i < dict->size; ++i)
    free(dict->entries[i].bytes);
  free(dict->entries);
  free(dict);
}

int dict_add_entry(struct dictionary *dict, const struct bytes *bytes)
{
  if (dict->size == dict->capacity)
  {
    dict->capacity *= 2;
    dict->entries =
      realloc(dict->entries, sizeof(struct dictionary_entry) * dict->capacity);
    if (!dict->entries)
      return -1;
  }

  size_t i = dict->size++;
  struct dictionary_entry *entry = &dict->entries[i];
  entry->bytes = malloc(bytes->size);
  if (!entry->bytes)
    return -1;
  memcpy(entry->bytes, bytes->bytes, bytes->size);
  entry->size = bytes->size;

  return i;
}

int dict_find(struct dictionary *dict, const uint8_t *bytes, size_t size)
{
  for (size_t i = 0; i < dict->size; ++i)
  {
    if (dict->entries[i].size == size
        && memcmp(dict->entries[i].bytes, bytes, size) == 0)
      return i;
  }
  return -1;
}
