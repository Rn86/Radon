#ifndef RN_LIST_H_INCLUDED
#define RN_LIST_H_INCLUDED

#include <Radon/RnTypes.h>

RN_HANDLE(RnList)

RnResult RN_API RnListCreate(RnUInt initialSize, RnUInt itemSize, HRnList * phList);
RnResult RN_API RnListDelete(HRnList hList);
RnResult RN_API RnListAdd(HRnList hList, RnUInt size, void * pItem, RnUInt * pIndex);
RnResult RN_API RnListRemove(HRnList hList, RnUInt index);
RnResult RN_API RnListGet(HRnList hList, RnUInt index, void * pItem);
RnResult RN_API RnListIndexOf(HRnList hList, void * pItem);

#endif // RN_LIST_H_INCLUDED
