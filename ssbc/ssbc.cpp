#include "ssbc.hpp"

SSBC::SSBC(){
	dout("SSBC()");
	halt_bit = false;
	fault_bit = false;
	break_bit = false;
}

void SSBC::reset(){
	dout("reset");
	stack_pointer = SP_START;
	program_counter = PC_START;
	halt_bit = false;
	fault_bit = false;
	break_bit = false;
	memory[PSW] = 0;
}

void SSBC::load(const char* filename){
	dout("loading program");
	ifstream fin;
	fin.open(filename);
	if (fin.fail()){
		cout << "Error: cannot open file " << filename << '\n';
		return;
	}

	string byte;
	string comment;
	unsigned int n = 0;
	while(!fin.eof()){
		if (n >= PSW){
			cout << "Error: Program is too large to load\n";
			return;
		}
		fin >> byte;
		getline(fin, comment);
		#if(DEBUG)
			comments.push_back(comment);
		#endif
		memory[n] = stoi(byte, NULL, 2);
		n++;
	}
}

void SSBC::run(){
	reset();
	dout("running program");
	do{
		if (program_counter > SP_START){
			fault("program counter too large");
			return;
		}
		#if(DEBUG)
			if (program_counter < comments.size())
				cout << comments[program_counter] << '\n';
		#endif
		switch(memory[program_counter]){
			case NOOP:
				noop();
			break;

			case HALT:
				halt();
			break;

			case PUSHIMM:
				pushimm();
			break;

			case PUSHEXT:
				pushext();
			break;

			case POPINH:
				popinh();
			break;

			case POPEXT:
				popext();
			break;

			case JNZ:
				jnz();
			break;

			case JNN:
				jnn();
			break;

			case ADD:
				add();
			break;

			case SUB:
				sub();
			break;

			case NOR:
				nor();
			break;

			default:
				fault("invalid opcode");
		}
	}while(!halt_bit && !fault_bit && !break_bit);
}

uint SSBC::readAddress(){
	uint address = ((uint)(static_cast<uchar>(memory[program_counter+1])) << 8)
		| (static_cast<uchar>(memory[program_counter+2]));
	return address;
}

void SSBC::setPSW(){
	uint result_addr = stack_pointer + 2;
	uint psw = 0;
	if (memory[result_addr] == 0){
		psw = (1 << Z_BIT);
		dout("psw Z bit set");
	}else if (memory[result_addr] < 0){
		psw = (1 << N_BIT);
		dout("psw N bit set");
	}
	memory[PSW] = psw;
}

void SSBC::noop(){
	dout("noop");
	program_counter++;
}

void SSBC::halt(){
	dout("halt");
	halt_bit = true;
}

void SSBC::pushimm(){
	if (stack_pointer == 0){
		fault("stack pointer underflow in pushimm");
		return;
	}
	memory[stack_pointer] = memory[program_counter+1];

	dout("pushimm " << (int)memory[stack_pointer] << " : "
		<< (char)memory[stack_pointer]);

	stack_pointer--;
	program_counter += 2;
}

void SSBC::pushext(){
	if (stack_pointer == 0){
		fault("stack pointer underflow in pushext");
		return;
	}
	
	uint address = readAddress();
	memory[stack_pointer] = memory[address];

	dout("pushext " << getAddressName(address) << ": "
		<< (int)memory[stack_pointer] << " : "
		<< (char)memory[stack_pointer]);

	stack_pointer--;
	program_counter += 3;
}

void SSBC::popinh(){
	dout("popinh");
	if (stack_pointer >= SP_START){
		fault("Stack pointer overflow in popinh");
		return;
	}
	stack_pointer++;
	program_counter++;
}

void SSBC::popext(){
	if (stack_pointer >= SP_START){
		fault("Cannot popext");
		return;
	}
	uint address = readAddress();
	stack_pointer++;
	memory[address] = memory[stack_pointer];
	dout("popext " << getAddressName(address) << ": " << (int)memory[address]
		<< " : " << (char)memory[stack_pointer]);
	
	program_counter += 3;
}

void SSBC::jnz(){
	dout("jnz");
	jnbit(Z_BIT);
}

void SSBC::jnn(){
	dout("jnn");
	jnbit(N_BIT);
}

void SSBC::jnbit(uint bit){
	uint address = readAddress();
	if (memory[PSW] & (1 << bit)){
		dout("no jump");
		program_counter += 3;
	}else{
		dout("jumped to " << address);
		program_counter = address;
	}
}

void SSBC::add(){
	dout("add");
	char result = memory[stack_pointer + 1] + memory[stack_pointer + 2];

	dout((int)memory[stack_pointer + 1] << " + "
		<< (int)memory[stack_pointer + 2] << " = " << (int)result);

	memory[stack_pointer + 2] = result;
	setPSW();
	stack_pointer++;
	program_counter++;
}

void SSBC::sub(){
	dout("sub");
	char result = memory[stack_pointer + 1] - memory[stack_pointer + 2];

	dout((int)memory[stack_pointer + 1] << " - "
		<< (int)memory[stack_pointer + 2] << " = " << (int)result);

	memory[stack_pointer + 2] = result;
	setPSW();
	stack_pointer++;
	program_counter++;
}

void SSBC::nor(){
	dout("nor");
	char result = ~(memory[stack_pointer + 1] | memory[stack_pointer + 2]);
	
	dout((int)memory[stack_pointer + 1] << " nor "
		<< (int)memory[stack_pointer + 2] << " = " << (int)result);

	memory[stack_pointer + 2] = result;
	stack_pointer++;
	program_counter++;
}

void SSBC::fault(const char* message){
	fault_bit = 1;
	cout << "fault: " << message << " at " << program_counter << '\n';
}

void SSBC::writeToPortB(char value){
	memory[PORTB] = value;
}

void SSBC::writeToPortD(char value){
	memory[PORTD] = value;
}

char SSBC::readFromPortA(){
	return memory[PORTA];
}

char SSBC::readFromPortC(){
	return memory[PORTC];
}

string SSBC::getAddressName(uint address){
	switch(address){
		case PSW: return "PSW";
		case PORTA: return "PORT A";
		case PORTB: return "PORT B";
		case PORTC: return "PORT C";
		case PORTD: return "PORT D";
		default: return to_string(address);
	}
}