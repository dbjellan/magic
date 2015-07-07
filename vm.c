
#define JNZ     0x1
#define JMP     0x2
#define ADD     0x3
#define SUB     0x4
#define MULT    0x5
#define PUSH    0x6
#define POP     0x7
#define CMP     0x8
#define AND     0x9
#define OR      0xa
#define NOT     0xb
#define NEG     0xc
#define CALL    0xd

struct vm_instruction {
    short code;
    void *arg;
};

struct vm_module {
    struct vm_instruction *instructions;  
    short int ip;
};

struct vm_module* new_vm_module() {

}