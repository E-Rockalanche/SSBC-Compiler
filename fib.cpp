long fibRecursive(long index){
	if(index <= 0) return 0
	if(index <= 2) return 1
}

long fibLoop(long index){
	if (index <= 0){
		return 0
	}
	long last2 = 0
	long last = 1
	for(long i = 1; i < index; i = i + 1){
		long temp = last + last2
		last2 = last
		last = temp
	}
	return last
}

void main(){
	int* ports = 0xfffc
	long x = ports[1]
	ports[0] = fibLoop(x)
	ports[2] = fibRecursive(x)
}