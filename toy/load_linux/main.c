extern char rom_start;
extern char rom_end;

int main(void)
{
	char *p = (char*)&rom_start;
	char *addr = (char*)0x20000000;
	
	while((int)p<(int)rom_end){
		*addr = *p;
		if(*addr == '\n'){
			return 0xff;
		}
		addr++;
		p++;
	}
	return 0x78;
}
