void bubbleSort(int* arr, int arrSize) {
	for(int i = 0; i < arrSize-1; i = i+1) {
		for(int index = 0; index < arrSize-1; index = index+1) {
			if (arr[index] > arr[index+1]) {
				int temp = arr[index]
				arr[index] = arr[index+1]
				arr[index+1] = temp
			}
		}
	}


	bool sorted = 1
	for(int index = 0; index < arrSize-1; index = index+1) {
		if (arr[index] > arr[index+1]) {
			sorted = 0
			break
		}
	}

	int* ports = 0xfffc
	ports[2] = sorted
}

void main() {
	int* ports = 0xfffc

	int[4] arr
	arr[0] = 99
	arr[1] = 78
	arr[2] = 66
	arr[3] = 7

	bubbleSort(arr, 4)

	bool sorted = 1
	for(int index = 0; index < 3; index = index+1) {
		if (arr[index] > arr[index+1]) {
			sorted = 0
			break
		}
	}

	ports[0] = sorted
}