# Pseudocode
# INSERTION-SORT(A)
    # for j = 1 to length(A)
        # key = A[j]
        # # Insert A[j] into the sorted sequence A[1.. j-1]
        # i = j - 1
        # while i >= 0 and A[i] > key # Change here for non-increasing order
            # A[i+1] = A[i]
            # i = i - 1
        # A[i+1] = key

def insertion_sort(_array=[], order='ascending'):
    for j in range(1, len(_array)):
        key = _array[j]
        # Insert A[j] into the sorted sequence A[1.. j-1]
        i = j - 1
        if str(order).lower().__eq__('ascending'):
            while i >= 0 and _array[i] > key:
                _array[i+1] = _array[i]
                i = i - 1
            _array[i+1] = key
        else:
            while i >= 0 and _array[i] < key:
                _array[i+1] = _array[i]
                i = i - 1
            _array[i+1] = key
    return _array