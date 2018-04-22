int fib(int index){
	{
		long garbage = 0
		int also_garbage = 1
	}
	{
		int garbagio = 2
		long lon_garbage = 3
	}
	if (index <= 0) return 0
	if (index <= 2) return 1
	return fib(index - 1) + fib(index - 2)
}

void main(){
	int* ports
	ports = 0xfffc

	ports[0] = fib(ports[1])
}