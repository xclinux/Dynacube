
int main()
{
	createdir("\\source3");
	while(1);
}
 int createdir(char *name)
 {
    long  res;   
     
    __asm__ __volatile__("pushl %%eax"::"a"(name));
    __asm__ __volatile__("int $0x30"::"a"(19));
    __asm__ __volatile__("popl %ebx");

     __asm__ __volatile__("pushl %eax");
     __asm__ __volatile__("popl %0"::"r"(res));
     return res;        
 }  

