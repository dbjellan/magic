#define INT 0
#define STRING 1
#define TABLE 2
#define FUNCTION 3
#define DOUBLE 4

struct magic_object;
struct magic_context;

typedef struct magic_object m_object;
typedef struct magic_hash_entry m_entry;

m_object* get_identifier(char *identifier);

m_object* make_magic_object(char *string);
m_object* make_magic_object(int value);
m_object* make_magic_object(double value);
void free_magic_object(m_object *obj);
