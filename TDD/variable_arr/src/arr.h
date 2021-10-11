#ifndef _ARR_H_
#define _ARR_H_

struct vararr{
	int *arr;
	int len;
};

void vararr_init(struct vararr *arr, int len);
void vararr_deinit(struct vararr *arr);
void vararr_set(struct vararr *arr, int idx, int val);
int vararr_get(struct vararr *arr, int idx);
int vararr_get_len(struct vararr *arr);

#endif
