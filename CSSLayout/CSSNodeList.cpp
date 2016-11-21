/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include "CSSNodeList.h"

extern CSSMalloc gCSSMalloc;
extern CSSRealloc gCSSRealloc;
extern CSSFree gCSSFree;

struct CSSNodeList {
  uint32_t capacity;
  uint32_t count;
  CSSNodeRef *items;
};

CSSNodeListRef CSSNodeListNew(const uint32_t initialCapacity) {
  // BEGIN_UNITY @joce 10-26-2016 CompileForVS2010
  //const CSSNodeListRef list = gCSSMalloc(sizeof(struct CSSNodeList));
  const CSSNodeListRef list = (CSSNodeListRef)gCSSMalloc(sizeof(struct CSSNodeList));
  // END_UNITY
  CSS_ASSERT(list != NULL, "Could not allocate memory for list");

  list->capacity = initialCapacity;
  list->count = 0;
  // BEGIN_UNITY @joce 10-26-2016 CompileForVS2010
  //list->items = gCSSMalloc(sizeof(CSSNodeRef) * list->capacity);
  list->items = (CSSNodeRef*)gCSSMalloc(sizeof(CSSNodeRef) * list->capacity);
  // END_UNITY
  CSS_ASSERT(list->items != NULL, "Could not allocate memory for items");

  return list;
}

void CSSNodeListFree(const CSSNodeListRef list) {
  if (list) {
    gCSSFree(list->items);
    gCSSFree(list);
  }
}

uint32_t CSSNodeListCount(const CSSNodeListRef list) {
  if (list) {
    return list->count;
  }
  return 0;
}

void CSSNodeListAdd(CSSNodeListRef *listp, const CSSNodeRef node) {
  if (!*listp) {
    *listp = CSSNodeListNew(4);
  }
  CSSNodeListInsert(listp, node, (*listp)->count);
}

void CSSNodeListInsert(CSSNodeListRef *listp, const CSSNodeRef node, const uint32_t index) {
  if (!*listp) {
    *listp = CSSNodeListNew(4);
  }
  CSSNodeListRef list = *listp;

  if (list->count == list->capacity) {
    list->capacity *= 2;
    // BEGIN_UNITY @joce 10-26-2016 CompileForVS2010
    //list->items = gCSSRealloc(list->items, sizeof(CSSNodeRef) * list->capacity);
    list->items = (CSSNodeRef*)gCSSRealloc(list->items, sizeof(void *) * list->capacity);
    // END_UNITY
    CSS_ASSERT(list->items != NULL, "Could not extend allocation for items");
  }

  for (uint32_t i = list->count; i > index; i--) {
    list->items[i] = list->items[i - 1];
  }

  list->count++;
  list->items[index] = node;
}

CSSNodeRef CSSNodeListRemove(const CSSNodeListRef list, const uint32_t index) {
  // BEGIN_UNITY @joce 10-26-2016 CompileForVS2010
  //const CSSNodeRef removed = list->items[index];
  const CSSNodeRef removed = (CSSNodeRef)list->items[index];
  // END_UNITY
  list->items[index] = NULL;

  for (uint32_t i = index; i < list->count - 1; i++) {
    list->items[i] = list->items[i + 1];
    list->items[i + 1] = NULL;
  }

  list->count--;
  return removed;
}

CSSNodeRef CSSNodeListDelete(const CSSNodeListRef list, const CSSNodeRef node) {
  for (uint32_t i = 0; i < list->count; i++) {
    if (list->items[i] == node) {
      return CSSNodeListRemove(list, i);
    }
  }

  return NULL;
}

CSSNodeRef CSSNodeListGet(const CSSNodeListRef list, const uint32_t index) {
  if (CSSNodeListCount(list) > 0) {
    // BEGIN_UNITY @joce 10-26-2016 CompileForVS2010
    //return list->items[index];
    return (CSSNodeRef)list->items[index];
    // END_UNITY
  }

  return NULL;
}
