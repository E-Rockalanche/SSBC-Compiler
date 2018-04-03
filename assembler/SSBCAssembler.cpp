#include "SSBCAssembler.hpp"

SSBCAssembler::SSBCAssembler(int argc, const char** argv){
	dout("SSBCAssembler()");
	for(int i = 1; i < argc; i++){
		if(argv[i] == string("-o")){
			assert(++i < argc, "Output file flag given with no filename");
			setOutputFilename(argv[i]);
		}else if (argv[i] == string("-w")){
			setWarnings();
		}else if (argv[i] == string("-c")){
			setComments();
		}else{
			addInputFile(argv[i]);
		}
	}

	tokenizer.setLang(new SSBCLang());

	labels.define("ASM", ASM);
	labels.setGlobal("ASM");
	labels.define("ASM2", ASM2);
	labels.setGlobal("ASM2");
	labels.define("PSW", PSW);
	labels.setGlobal("PSW");
	labels.define("PORT_A", PORT_A);
	labels.setGlobal("PORT_A");
	labels.define("PORT_B", PORT_B);
	labels.setGlobal("PORT_B");
	labels.define("PORT_C", PORT_C);
	labels.setGlobal("PORT_C");
	labels.define("PORT_D", PORT_D);
	labels.setGlobal("PORT_D");
}

void SSBCAssembler::setWarnings(bool set){
	dout("Warnings = " << (set ? "true" : "false"));
	warnings = set;
}

void SSBCAssembler::setComments(bool set){
	dout("Comments = " << (set ? "true" : "false"));
	outputComments = set;
}

void SSBCAssembler::setOutputFilename(string filename){
	dout("Output filename = " << filename);
	outputFilename = filename;
}

void SSBCAssembler::addInputFile(string filename){
	dout("Adding input file: " << filename);
	inputFiles.push_back(filename);
}

bool SSBCAssembler::assemble(){
	dout("assemble()");
	if (inputFiles.size() == 0){
		cout << "No files given to assemble\n";
		return false;
	}

	if (outputFilename == ""){
		cout << "No output filename given\n";
		return false;
	}

	dout("leaving room for " << numASMRegisters << " ASM registers");
	for(int i = 0; i < numASMRegisters; i++){
		binary.write8bit(PUSHIMM);
		binary.write8bit(0);
	}

	dout("leaving room for jump to start statement");
	for(int i = 0; i < 8; i++){
		binary.write8bit(NOOP);
	}

	errors = 0;

	for(unsigned int i = 0; i < inputFiles.size(); i++){
		assembleFile(inputFiles[i]);
	}

	checkForUndefinedReferences();

	if (errors == 0){
		writeToFile();
		return true;
	}else{
		cout << "Assembly failed. See errors above\n";
		return false;
	}
}

void SSBCAssembler::assembleFile(string filename){
		dout("assembling file " << filename);

		tokens.clear();
		index = 0;
		tokenizer.tokenize(filename, &tokens);
		while(index < tokens.size()){
			statement();
		}

		dout("clearing local labels");
		labels.clearLocal();
}

void SSBCAssembler::writeToFile(){
	dout("writeToFile(" << outputFilename << ")");
	ofstream fout(outputFilename);
	assert(!fout.fail(), "Cannot open " + outputFilename);
	for(unsigned int i = 0; i < binary.size(); i++){
		fout << binary[i].to_string() << getComment(i) << '\n';
	}
	fout.close();
}

string SSBCAssembler::getComment(unsigned int i){
	if (i < comments.size()){
		return comments[i];
	}
	return "";
}

void SSBCAssembler::checkForUndefinedReferences(){
	dout("Checking for undefined references");
	LabelList::UndefinedList undefinedList = labels.getUndefinedReferences();
	char numString[32];
	for(unsigned int i = 0; i < undefinedList.size(); i++){
		error("Undefined reference: " + undefinedList[i].first
			+ string(" at 0x") + itoa(undefinedList[i].second, numString, 16));
	}
}

void SSBCAssembler::error(string message){
	errors++;
	cout << "Error: " << message << '\n';
}

void SSBCAssembler::warning(string message){
	if (warnings){
		cout << "Warning: " << message << '\n';
	}
}

#define ROW_COL " (" << currentToken().row() << ", " << currentToken().col()\
	<< ")\n"
void SSBCAssembler::errorAt(string message){
	errors++;
	cout << "Error: " << message << " at " << ROW_COL;
}

void SSBCAssembler::warningAt(string message){
	if (warnings){
		cout << "Warning: " << message << " at " << ROW_COL;
	}
}
void SSBCAssembler::errorNear(string message){
	errors++;
	cout << "Error: " << message << " near " << ROW_COL;
}

void SSBCAssembler::warningNear(string message){
	if (warnings){
		cout << "Warning: " << message << " near " << ROW_COL;
	}
}
#undef ROW_COL

Token SSBCAssembler::nextToken(){
	unsigned int cur = index++;
	if (cur < tokens.size()){
		Token tok = tokens[cur];
		switch(tok.type()){
			case SSBCLang::COMMENT:
			case SSBCLang::COMMENT_BLOCK:
				tok = nextToken();
			default:
				return tok;
				break;
		}
	}
	return endToken();
}

Token SSBCAssembler::currentToken(){
	if (index-1 < tokens.size())
		return tokens[index-1];
	else
		return endToken();
}

Token SSBCAssembler::endToken(){
	Token lastToken = tokens.back();
	return Token(SSBCLang::EOT, "INVALID END", lastToken.row(), lastToken.col()
		+ lastToken.value().size());
}

void SSBCAssembler::statement(){
	switch(nextToken().type()){
		//native instructions
		case SSBCLang::NOOP: noop(); break;
		case SSBCLang::HALT: halt(); break;
		case SSBCLang::PUSHIMM: pushimm(); break;
		case SSBCLang::PUSHEXT: pushext(); break;
		case SSBCLang::POPINH: popinh(); break;
		case SSBCLang::POPEXT: popext(); break;
		case SSBCLang::JNZ: jnz(); break;
		case SSBCLang::JNN: jnn(); break;
		case SSBCLang::ADD: add(); break;
		case SSBCLang::SUB: sub(); break;
		case SSBCLang::NOR: nor(); break;

		//extended instructions
		case SSBCLang::TEST: test(); break;
		case SSBCLang::PUSHIMM16: pushimm16(); break;
		case SSBCLang::PUSHEXT16: pushext16(); break;
		case SSBCLang::POPINH16: popinh16(); break;
		case SSBCLang::POPEXT16: popext16(); break;
		case SSBCLang::JUMP: jump(); break;
		case SSBCLang::JSR: jsr(); break;
		case SSBCLang::CLEAR: clear(); break;
		case SSBCLang::CLEARPSW: clearpsw(); break;
		case SSBCLang::CLONE: clone(); break;
		case SSBCLang::OR: bitwiseOr(); break;
		case SSBCLang::AND: bitwiseAnd(); break;
		case SSBCLang::NOT: bitwiseNot(); break;
		case SSBCLang::NAND: nand(); break;
		case SSBCLang::COMPARE: compare(); break;
		case SSBCLang::INC: inc(); break;
		case SSBCLang::DEC: dec(); break;
		case SSBCLang::SWAP: swap(); break;
		case SSBCLang::MOVE: move(); break;
		case SSBCLang::BTEST: btest(); break;
		case SSBCLang::BSET: bset(); break;
		case SSBCLang::BCLEAR: bclear(); break;

		//directives
		case SSBCLang::START: start(); break;
		case SSBCLang::GLOBAL: global(); break;
		case SSBCLang::FILE: file(); break;
		case SSBCLang::BYTE: byte(); break;
		case SSBCLang::WORD: word(); break;
		case SSBCLang::ARRAY: array(); break;
		case SSBCLang::ASCII: ascii(); break;
		case SSBCLang::ASCIZ: asciz(); break;

		//other
		case SSBCLang::COMMENT:
		case SSBCLang::COMMENT_BLOCK:
			dout("Comment");
			break;

		case SSBCLang::EOT:
			dout("End of tokens");
			break;

		case SSBCLang::IDENTIFIER:
			labelDef();
			break;

		default:
			errorAt("Invalid start of statement token");
			dout("value = \"" << currentToken().value() << "\"");
			dout("type = " << currentToken().type());
	}
}

//===========================================================
//                    NATIVE INSTRUCTIONS
//===========================================================

void SSBCAssembler::noop(){
	dout("noop");
	binary.write8bit(NOOP);
	writeComment("noop");
}

void SSBCAssembler::halt(){
	dout("halt");
	binary.write8bit(HALT);
	writeComment("halt");
}

void SSBCAssembler::pushimm(){
	dout("pushimm");
	binary.write8bit(PUSHIMM);
	writeComment("pushimm");
	byteLiteral();
}

void SSBCAssembler::pushext(){
	dout("pushext()");
	binary.write8bit(PUSHEXT);
	writeComment("pushext");
	addressToken();
}

void SSBCAssembler::popinh(){
	dout("popinh");
	binary.write8bit(POPINH);
	writeComment("popinh");
}

void SSBCAssembler::popext(){
	dout("popext");
	binary.write8bit(POPEXT);
	writeComment("popext");
	addressToken();
}

void SSBCAssembler::jnz(){
	dout("jnz");
	binary.write8bit(JNZ);
	writeComment("jnz");
	addressToken();
}

void SSBCAssembler::jnn(){
	dout("jnn");
	binary.write8bit(JNN);
	writeComment("jnn");
	addressToken();
}

void SSBCAssembler::add(){
	dout("add");
	binary.write8bit(ADD);
	writeComment("add");
}

void SSBCAssembler::sub(){
	dout("sub");
	binary.write8bit(SUB);
	writeComment("sub");
}

void SSBCAssembler::nor(){
	dout("nor");
	binary.write8bit(NOR);
	writeComment("nor");
}

//===========================================================
//                   EXTENDED INSTRUCTIONS
//===========================================================

void SSBCAssembler::test(){
	dout("test");
	binary.write8bit(PUSHIMM);
	binary.write8bit(0);
	binary.write8bit(ADD);
}

void SSBCAssembler::pushimm16(){
	dout("pushimm16");
	int value = 0;
	Token token = nextToken();
	switch(token.type()){
		CASE_INTEGER
			value = parseInteger(token);
			break;

		case SSBCLang::IDENTIFIER:
			if (labels.isDefined(token.value())){
				value = labels.getAddress(token.value());
			}else{
				labels.addOccurrence(token.value(), index,
					LabelList::LOW_BITS);
				labels.addOccurrence(token.value(), index+2,
					LabelList::HIGH_BITS);
			}
			break;

		default:
			errorAt("Expected an integer or address");
			return;
	}
	pushimm16(value);
}

void SSBCAssembler::popinh16(){
	popinh();
	popinh();
}

void SSBCAssembler::pushext16(){
	dout("pushext16");
	binary.write8bit(PUSHEXT);
	writeComment("pushext16");
	unsigned int value = getExt16Address();
	binary.write16bit(value + 1);
	binary.write8bit(PUSHEXT);
	binary.write16bit(value);
}

void SSBCAssembler::popext16(){
	dout("popext16");
	binary.write8bit(POPEXT);
	writeComment("popext16");
	unsigned int value = getExt16Address();
	binary.write16bit(value);
	binary.write8bit(POPEXT);
	binary.write16bit(value + 1);
}

void SSBCAssembler::jump(){
	dout("jump");
	clearpsw();
	binary.write8bit(JNZ);
	writeComment("jump");
	addressToken();
}

void SSBCAssembler::jsr(){
	dout("jsr");
	unsigned int address = binary.size() + 12;
	writeComment("jsr", binary.size() + 1);
	pushimm16(address);
	jump();
}

void SSBCAssembler::clear(){
	dout("clear");
	binary.write8bit(PUSHIMM);
	writeComment("clear");
	binary.write8bit(0);
	binary.write8bit(POPEXT);
	addressToken();
}

void SSBCAssembler::clearpsw(){
	dout("clearpsw");
	binary.write8bit(PUSHIMM);
	writeComment("clearpsw");
	binary.write8bit(0);
	binary.write8bit(POPEXT);
	binary.write16bit(PSW);
}

void SSBCAssembler::clone(){
	dout("clone");
	binary.write8bit(POPEXT);
	writeComment("clone");
	binary.write16bit(ASM);
	binary.write8bit(PUSHEXT);
	binary.write16bit(ASM);
	binary.write8bit(PUSHEXT);
	binary.write16bit(ASM);
}

void SSBCAssembler::bitwiseNot(){
	dout("not");
	writeComment("not", binary.size());
	clone();
	nor();
}

void SSBCAssembler::bitwiseOr(){
	dout("or");
	writeComment("or", binary.size());
	nor();
	bitwiseNot();
}

void SSBCAssembler::bitwiseAnd(){
	dout("and");
	writeComment("and", binary.size());
	bitwiseNot();
	binary.write8bit(POPEXT);
	binary.write16bit(ASM2);
	bitwiseNot();
	binary.write8bit(PUSHEXT);
	binary.write16bit(ASM2);
	nor();
}

void SSBCAssembler::nand(){
	dout("nand");
	writeComment("nand", binary.size());
	bitwiseNot();
	binary.write8bit(POPEXT);
	binary.write16bit(ASM2);
	bitwiseNot();
	binary.write8bit(PUSHEXT);
	binary.write16bit(ASM2);
	bitwiseOr();
}

void SSBCAssembler::compare(){
	dout("compare");
	Token compareAgainst = nextToken();
	Token value = nextToken();
	binary.write8bit(PUSHEXT);
	writeComment("compare");
	writeAddress(compareAgainst);
	binary.write8bit(PUSHEXT);
	writeAddress(value);
	binary.write8bit(SUB);
	binary.write8bit(POPINH);
}

void SSBCAssembler::inc(){
	dout("inc");
	binary.write8bit(PUSHEXT);
	writeComment("inc");
	Token addressToken = nextToken();
	writeAddress(addressToken);
	binary.write8bit(PUSHIMM);
	binary.write8bit(1);
	binary.write8bit(ADD);
	binary.write8bit(POPEXT);
	writeAddress(addressToken);
}

void SSBCAssembler::dec(){
	dout("dec");
	binary.write8bit(PUSHIMM);
	writeComment("dec");
	binary.write8bit(1);
	binary.write8bit(PUSHEXT);
	Token addressToken = nextToken();
	writeAddress(addressToken);
	binary.write8bit(SUB);
	binary.write8bit(POPEXT);
	writeAddress(addressToken);
}

void SSBCAssembler::swap(){
	dout("swap");
	Token addr1 = nextToken();
	Token addr2 = nextToken();
	binary.write8bit(PUSHEXT);
	writeComment("swap");
	writeAddress(addr1);
	binary.write8bit(POPEXT);
	binary.write16bit(ASM);
	binary.write8bit(PUSHEXT);
	writeAddress(addr2);
	binary.write8bit(POPEXT);
	writeAddress(addr1);
	binary.write8bit(PUSHEXT);
	binary.write16bit(ASM);
	binary.write8bit(POPEXT);
	writeAddress(addr2);
}

void SSBCAssembler::move(){
	dout("move");
	binary.write8bit(PUSHEXT);
	writeComment("move");
	addressToken();
	binary.write8bit(POPEXT);
	addressToken();
}

void SSBCAssembler::btest(){
	dout("btest");
	clone();
	writeComment("btest");
	binary.write8bit(PUSHIMM);
	int value = getInteger();
	binary.write8bit(1 << value);
	bitwiseAnd();
	test();
	popinh();
}

void SSBCAssembler::bset(){
	dout("bset");
	binary.write8bit(PUSHIMM);
	writeComment("bset");
	int value = getInteger();
	binary.write8bit(1 << value);
	bitwiseOr();
}

void SSBCAssembler::bclear(){
	dout("bclear");
	binary.write8bit(PUSHIMM);
	writeComment("bclear");
	int value = getInteger();
	binary.write8bit(~(1 << value));
	bitwiseAnd();
}

//===========================================================
//                        DIRECTIVES
//===========================================================

void SSBCAssembler::start(){
	dout("start");
	int startAddress = numASMRegisters*2;
	binary.write8bit(PUSHIMM, startAddress);
	writeComment("clearpsw", startAddress);
	binary.write8bit(0, startAddress + 1);
	binary.write8bit(POPEXT, startAddress + 2);
	binary.write16bit(PSW, startAddress + 3);
	binary.write8bit(JNZ, startAddress + 5);
	writeComment("jump", startAddress + 5);
	binary.write16bit(binary.size(), startAddress + 6);
	writeComment("start", startAddress + 6);
	writeComment("start", binary.size());
}

void SSBCAssembler::global(){
	dout("global");
	Token global = nextToken();
	if (global.type() != SSBCLang::IDENTIFIER){
		errorAt("Expected an identifier");
	}else{
		labels.setGlobal(global.value());
	}
}

void SSBCAssembler::file(){
	dout("file");
	if (nextToken().type() != SSBCLang::STRING){
		errorAt("Expected a string");
	}
}

void SSBCAssembler::byte(){
	dout("byte");
	writeComment("byte", binary.size());
	binary.write8bit(getInteger());
}

void SSBCAssembler::word(){
	dout("word");
	writeComment("word", binary.size());
	binary.write16bit(getInteger());
}

void SSBCAssembler::array(){
	dout("array");
	int length = getInteger();
	if (length <= 0){
		errorAt("Cannot define array of size " + to_string(length));
	}else{
		writeComment("array", binary.size());
		for(int i = 0; i < length; i++){
			binary.write8bit(0);
		}
	}
}

void SSBCAssembler::ascii(){
	dout("ascii");
	writeComment("ascii", binary.size());
	Token str = nextToken();
	if (str.type() != SSBCLang::STRING){
		errorAt("Expected string");
	}else{
		writeAscii(str.value());
	}
}

void SSBCAssembler::asciz(){
	dout("asciz");
	writeComment("asciz", binary.size());
	ascii();
	binary.write8bit(0);
}

//===========================================================
//                          OTHER
//===========================================================

void SSBCAssembler::writeAddress(Token addressToken){
	dout("writeAddress(" << addressToken.value() << ")");
	unsigned int value = 0;
	switch(addressToken.type()){
		CASE_INTEGER
			value = parseInteger(addressToken);
			break;

		case SSBCLang::IDENTIFIER:
			if (labels.isDefined(addressToken.value())){
				value = labels.getAddress(addressToken.value());
			}else{
				labels.addOccurrence(addressToken.value(), binary.size());
			}
			break;

		default:
			error("Expected an address at (" + to_string(addressToken.row())
				+ ", " + to_string(addressToken.col()) + ")");
	}
	binary.write16bit(value);
}

void SSBCAssembler::writeAscii(string str){
	for(int i = 1; i < (int)str.size()-1; i++){
		if (str[i] == '\\'){
			binary.write8bit(parseEscapeChar(str[++i]));
		}else{
			binary.write8bit(str[i]);
		}
	}
}

int SSBCAssembler::parseChar(Token charToken){
	string str = charToken.value();
	dout("parseChar(" << str << ")");
	if (str[1] == '\\'){
		return parseEscapeChar(str[2]);
	}else{
		return str[1];
	}
}

int SSBCAssembler::parseEscapeChar(char escapeChar){
	dout("parseEscapeChar(" << escapeChar << ")");
	char c = 0;
	switch(escapeChar){
		case 'a': c = '\a'; break;
		case 'b': c = '\b'; break;
		case 'f': c = '\f'; break;
		case 'n': c = '\n'; break;
		case 'r': c = '\r'; break;
		case 't': c = '\t'; break;
		case 'v': c = '\v'; break;
		case '\\': c = '\\'; break;
		case '\'': c = '\''; break;
		case '"': c = '"'; break;
		default:
			errorAt(string("Invalid escape character: ") + escapeChar);
	}
	return c;
}

void SSBCAssembler::pushimm16(unsigned int value){
	binary.write8bit(PUSHIMM);
	binary.write8bit(value & 255);
	binary.write8bit(PUSHIMM);
	binary.write8bit(value >> 8);
}

void SSBCAssembler::identifier(){
	dout("identifier");
	Token token = currentToken();
	if (token.type() != SSBCLang::IDENTIFIER){
		errorAt("Expected an identifier");
	}else{
		int offset = 0;
		if (nextToken().type() == SSBCLang::PLUS){
			dout("plus offset");
			offset = getInteger();
			if (offset < 0){
				errorAt("address offsets must not be negative");
				offset = 0;
			}
		}else{
			dout("no offset to address");
			index--;
		}
		if (labels.isDefined(token.value())){
			int address = labels.getAddress(token.value());
			dout(token.value() << " is defined as " << address);
			writeComment(token.value()+"+"+to_string(offset), binary.size());
			binary.write16bit(address + offset);
		}else{
			dout("adding occurrence of " << token.value());
			labels.addOccurrence(token.value(), binary.size(), offset);
			binary.write16bit(0);
		}
	}
}

void SSBCAssembler::byteLiteral(){
	dout("byte literal");
	Token token = nextToken();
	switch(token.type()){
		case SSBCLang::LOW_BITS:
			highLowAddress(false);
			break;

		case SSBCLang::HIGH_BITS:
			highLowAddress(true);
			break;

		default:
			int num = parseInteger(token);
			binary.write8bit(num);
			writeComment(to_string(num));
	}
}

void SSBCAssembler::highLowAddress(bool high){
	Token token = nextToken();
	if (token.type() != SSBCLang::IDENTIFIER){
		error("Expected an identifier");
	}else{
		if (labels.isDefined(token.value())){
			int address = labels.getAddress(token.value());
			binary.write8bit((high ? address >> 8 : address) & 255);
			writeComment((high ? "<" : ">") + token.value());
		}else{
			dout("adding occurrence of " + token.value());
			labels.addOccurrence(token.value(), binary.size(),
				high ? LabelList::HIGH_BITS : LabelList::LOW_BITS);
			binary.write8bit(0);
		}
	}
}

int SSBCAssembler::getInteger(){
	return parseInteger(nextToken());
}

int SSBCAssembler::parseInteger(Token integerToken){
	string value = integerToken.value();
	int num = 0;
	switch(integerToken.type()){
		case SSBCLang::HEXADECIMAL:
			num = stoi(value.erase(0, 2), NULL, 16);
			break;

		case SSBCLang::DECIMAL:
			num = stoi(value);
			break;
			
		case SSBCLang::OCTAL:
			num = stoi(value, NULL, 8);
			break;
			
		case SSBCLang::BINARY:
			num = stoi(value.erase(0, 2), NULL, 2);
			break;

		case SSBCLang::CHAR:
			num = parseChar(integerToken);
			break;
			
		default:	
			error("Expected an integer");
			dout("value = " << value);
	}
	return num;
}

unsigned int SSBCAssembler::getExt16Address(){
	dout("getExt16Address()");
	unsigned int value = 0;
	Token token = nextToken();
	switch(token.type()){
		CASE_INTEGER
			value = parseInteger(token);
			break;

		case SSBCLang::IDENTIFIER:
			if (labels.isDefined(token.value())){
				value = labels.getAddress(token.value());
			}else{
				labels.addOccurrence(token.value(), binary.size());
				labels.addOccurrence(token.value(), binary.size() + 3,
					LabelList::ADD_ONE);
			}
			break;

		default:
			error("Expected an integer or address");
	}
	return value;
}

void SSBCAssembler::addressToken(){
	dout("addressToken()");
	int num;
	switch(nextToken().type()){
		CASE_INTEGER
			num = parseInteger(currentToken());
			binary.write16bit(num);
			break;

		case SSBCLang::IDENTIFIER:
			identifier();
			break;

		case SSBCLang::BLANK_ADDRESS:
			blankAddress();
			break;

		default:
			error("Expecting an address");
	}
}

void SSBCAssembler::blankAddress(){
	dout("blankAddress()");
	//optional label
	if (nextToken().type() == SSBCLang::IDENTIFIER){
		labelDef();
	}
	if (nextToken().type() == SSBCLang::WORD){
		word();
	}else{
		errorAt("Expected word declaration");
	}
}

void SSBCAssembler::labelDef(){
	dout("labelDef()");
	Token token = currentToken();
	if (token.type() != SSBCLang::IDENTIFIER){
		errorAt("Expected an identifier");
	}else{
		defineLabelAsCurrentAddress(token.value());
		if (nextToken().type() != SSBCLang::COLON){
			errorAt("Expected colon after label");
		}
	}
}

void SSBCAssembler::defineLabelAsCurrentAddress(string label){
	dout("defining label \"" << label << "\"");
	if (labels.isDefined(label)){
		labelDefError(label);
	}else{
		replaceLabelOccurrences(label);
		labels.define(label, binary.size());
	}
	writeComment(label, binary.size());
}

void SSBCAssembler::labelDefError(string label){
	error("Label " + label + " is already defined");
	int address = labels.getAddress(label);
	cout << "\tdefined as " << address << '\n';
}

void SSBCAssembler::replaceLabelOccurrences(string label){
	dout("replacing occurrences of " << label
		<< " with " << binary.size());
	LabelList::OccurrenceList occurrences;
	occurrences = labels.getOccurrences(label);
	for(unsigned int i = 0; i < occurrences.size(); i++){
		pair<unsigned int, int> p = occurrences[i];
		replaceLabelOccurrence(label, p.first, (int)p.second);
	}
}

void SSBCAssembler::replaceLabelOccurrence(string label, unsigned int address,
		int option){
	unsigned int value = binary.size();
	switch(option){
		case LabelList::NONE:
			dout("writing value into address " << address);
			binary.write16bit(value, address);
			writeComment(label, address);
			break;

		case LabelList::HIGH_BITS:
			dout("writing high bits into address " << address);
			binary.write8bit((value >> 8) & 255, address);
			writeComment("<" + label, address);
			break;

		case LabelList::LOW_BITS:
			dout("writing low bits into address " << address);
			binary.write8bit(value & 255, address);
			writeComment(">" + label, address);
			break;

		case LabelList::ADD_ONE:
			dout("writing value + 1 into address " << address);
			binary.write16bit(value + 1, address);
			writeComment(label + " + " + to_string(1), address);
			break;

		default:
			int offset = option;
			dout("writing value + " << offset << " into address " << address);
			binary.write16bit(value + offset, address);
			writeComment(label + " + " + to_string(offset), address);
			break;
	}
}

void SSBCAssembler::writeComment(string comment){
	writeComment(comment, binary.size() - 1);
}

void SSBCAssembler::writeComment(string comment, unsigned int address){
	if (outputComments){
		if (comments.size() <= address){
			comments.resize(address + 1, "");
		}
		comments[address] += " " + comment;
	}
}