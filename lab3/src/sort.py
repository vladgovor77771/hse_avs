def binary_search_location(arr, item, low, high):
    while low <= high:
        mid = low + (high - low) // 2
        if item == arr[mid]:
            return mid + 1
        elif item > arr[mid]:
            high = mid - 1
        else:
            low = mid + 1

    return low


def sort_array_of_encoded_strings_desc(ess):
    keys = list(map(lambda x: x.common_func(), ess))
    i = j = loc = selected = 0
    for i in range(1, len(ess)):
        j = i - 1
        selected = keys[i]
        selected_es = ess[i]
        loc = binary_search_location(keys, selected, 0, i)
        while j >= loc:
            keys[j + 1] = keys[j]
            ess[j + 1] = ess[j]
            j -= 1
        keys[j + 1] = selected
        ess[j + 1] = selected_es
