#include <stdlib.h>
#include "arr.h"

void vararr_init(struct vararr *arr, int len)
{
	if(arr == NULL){
		return;
	}

	arr->arr = (int*)malloc(sizeof(int)*len);
	arr->len = len;
}

void vararr_deinit(struct vararr *arr)
{
	if(arr == NULL){
		return;
	}

	free(arr->arr);
}

void vararr_set(struct vararr *arr, int idx, int val)
{
	if(arr == NULL){
		return;
	}

	if(idx >= arr->len){
		while(arr->len < idx){
			arr->len += 128;
		}
		realloc(arr->arr, sizeof(int)*arr->len);
	}
	arr->arr[idx] = val;
}

int vararr_get(struct vararr *arr, int idx)
{
	if(arr == NULL){
		return 0;
	}

	return arr->arr[idx];
}

int vararr_get_len(struct vararr *arr)
{
	if(arr == NULL){
		return 0;
	}

	return arr->len;
}
