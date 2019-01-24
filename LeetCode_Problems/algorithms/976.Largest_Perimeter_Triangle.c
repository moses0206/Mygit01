void swap_int(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void quick_sort(int *a, int left, int right) {
    if(left >= right) return;
    int i = left + 1;
    int p = left;
    for(; i <= right; i++) {
        if(a[left] < a[i]) {
            p++;
            swap_int(&a[p], &a[i]);
        }
    }
    swap_int(&a[left], &a[p]);
    quick_sort(a, left, p-1);
    quick_sort(a, p+1, right);
    return;
}

int largestPerimeter(int* A, int ASize) {
    quick_sort(A, 0, ASize-1);
    int i = 0;
    for(; i < ASize - 2; i++) {
        if(A[i] - A[i+1] < A[i+2]) return A[i] + A[i+1] + A[i+2];
    }
    return 0;
}
