#define INT 0
#define STRING 1
#define TABLE 2
#define FUNCTION 3
#define DOUBLE 4
#define MODULE 5

struct magic_object;
struct magic_context;
struct magic_hash_table;

union magic_value {
    char *as_string;
    int   *as_int;
    double *as_double;
    void *as_function;
    void *as_table;
    void *ptr;
};

struct magic_object {    
    short type;
    union magic_value value;
};

typedef struct magic_object m_object;
typedef struct magic_hash_entry m_entry;
typedef struct magic_state m_state;

m_object* get_identifier(char *identifier);

m_object* make_magic_object(char *string);
m_object* make_magic_object(int value);
m_object* make_magic_object(double value);
void free_magic_object(m_object *obj);
