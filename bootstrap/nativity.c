#include "base.h"
#include "os.h"

#include "base.c"
#include "os.c"

#include "os/core/entry_point.c"


typedef struct TokenLocation TokenLocation;
struct TokenLocation
{
    u32 start;
    u32 end;
};

typedef enum TokenId : u8
{
    token_invalid,
    token_identifier,
    keyword_unsigned_integer,
    keyword_signed_integer,
    token_hex_literal,
    token_octal_literal,
    token_binary_literal,
    token_decimal_literal,
    token_zero_literal,

    token_string_literal,
    token_character_literal,
    token_intrinsic,
    token_discard,
    // Operators
    first_operator,
    operator_left_parenthesis = first_operator,
    operator_right_parenthesis,
    operator_left_brace,
    operator_right_brace,
    operator_left_bracket,
    operator_right_bracket,
    operator_semicolon,
    operator_at,
    operator_comma,
    operator_dot,
    operator_colon,
    operator_bang,
    operator_optional,
    operator_dollar,
    operator_switch_case,
    operator_backtick,
    operator_backslash,
    // Binary
    operator_assign,
    operator_add,
    operator_minus,
    operator_asterisk,
    operator_div,
    operator_mod,
    operator_bar,
    operator_ampersand,
    operator_xor,
    operator_shift_left,
    operator_shift_right,
    operator_add_assign,
    operator_sub_assign,
    operator_mul_assign,
    operator_div_assign,
    operator_mod_assign,
    operator_or_assign,
    operator_and_assign,
    operator_xor_assign,
    operator_shift_left_assign,
    operator_shift_right_assign,
    operator_compare_equal,
    operator_compare_not_equal,
    operator_compare_less,
    operator_compare_less_equal,
    operator_compare_greater,
    operator_compare_greater_equal,
    last_operator = operator_compare_greater_equal,
    // Fixed keywords
    first_keyword,
    fixed_keyword_const = first_keyword,
    fixed_keyword_var,
    fixed_keyword_void,
    fixed_keyword_noreturn,
    fixed_keyword_comptime,
    fixed_keyword_while,
    fixed_keyword_bool,
    fixed_keyword_true,
    fixed_keyword_false,
    fixed_keyword_fn,
    fixed_keyword_unreachable,
    fixed_keyword_return,
    fixed_keyword_ssize,
    fixed_keyword_usize,
    fixed_keyword_switch,
    fixed_keyword_if,
    fixed_keyword_else,
    fixed_keyword_struct,
    fixed_keyword_enum,
    fixed_keyword_union,
    fixed_keyword_null,
    fixed_keyword_align,
    fixed_keyword_for,
    fixed_keyword_undefined,
    fixed_keyword_break,
    fixed_keyword_test,
    fixed_keyword_try,
    fixed_keyword_catch,
    fixed_keyword_orelse,
    fixed_keyword_error,
    fixed_keyword_and,
    fixed_keyword_or,
    fixed_keyword_bitfield,
    last_keyword = fixed_keyword_bitfield,
} TokenId;

const TokenId operators[] =
{
    operator_left_parenthesis,
    operator_right_parenthesis,
    operator_left_brace,
    operator_right_brace,
    operator_left_bracket,
    operator_right_bracket,
    operator_semicolon,
    operator_at,
    operator_comma,
    operator_dot,
    operator_colon,
    operator_bang,
    operator_optional,
    operator_dollar,
    operator_switch_case,
    operator_backtick,
    operator_backslash,
    // Binary
    operator_assign,
    operator_add,
    operator_minus,
    operator_asterisk,
    operator_div,
    operator_mod,
    operator_bar,
    operator_ampersand,
    operator_xor,
    operator_shift_left,
    operator_shift_right,
    operator_add_assign,
    operator_sub_assign,
    operator_mul_assign,
    operator_div_assign,
    operator_mod_assign,
    operator_or_assign,
    operator_and_assign,
    operator_xor_assign,
    operator_shift_left_assign,
    operator_shift_right_assign,
    operator_compare_equal,
    operator_compare_not_equal,
    operator_compare_less,
    operator_compare_less_equal,
    operator_compare_greater,
    operator_compare_greater_equal,
};
static_assert(last_operator - first_operator + 1 == array_count(operators));

const TokenId fixed_keywords[] =
{
    fixed_keyword_const,
    fixed_keyword_var,
    fixed_keyword_void,
    fixed_keyword_noreturn,
    fixed_keyword_comptime,
    fixed_keyword_while,
    fixed_keyword_bool,
    fixed_keyword_true,
    fixed_keyword_false,
    fixed_keyword_fn,
    fixed_keyword_unreachable,
    fixed_keyword_return,
    fixed_keyword_ssize,
    fixed_keyword_usize,
    fixed_keyword_switch,
    fixed_keyword_if,
    fixed_keyword_else,
    fixed_keyword_struct,
    fixed_keyword_enum,
    fixed_keyword_union,
    fixed_keyword_null,
    fixed_keyword_align,
    fixed_keyword_for,
    fixed_keyword_undefined,
    fixed_keyword_break,
    fixed_keyword_test,
    fixed_keyword_try,
    fixed_keyword_catch,
    fixed_keyword_orelse,
    fixed_keyword_error,
    fixed_keyword_and,
    fixed_keyword_or,
    fixed_keyword_bitfield,
};
static_assert(last_keyword - first_keyword + 1 == array_count(fixed_keywords));

#define character_lower_cases \
    case 'a':\
    case 'b':\
    case 'c':\
    case 'd':\
    case 'e':\
    case 'f':\
    case 'g':\
    case 'h':\
    case 'i':\
    case 'j':\
    case 'k':\
    case 'l':\
    case 'm':\
    case 'n':\
    case 'o':\
    case 'p':\
    case 'q':\
    case 'r':\
    case 's':\
    case 't':\
    case 'u':\
    case 'v':\
    case 'w':\
    case 'x':\
    case 'y':\
    case 'z'

#define character_upper_cases \
    case 'A':\
    case 'B':\
    case 'C':\
    case 'D':\
    case 'E':\
    case 'F':\
    case 'G':\
    case 'H':\
    case 'I':\
    case 'J':\
    case 'K':\
    case 'L':\
    case 'M':\
    case 'N':\
    case 'O':\
    case 'P':\
    case 'Q':\
    case 'R':\
    case 'S':\
    case 'T':\
    case 'U':\
    case 'V':\
    case 'W':\
    case 'X':\
    case 'Y':\
    case 'Z'

#define alpha_cases character_lower_cases : character_upper_cases

#define decimal_cases \
    case '0':\
    case '1':\
    case '2':\
    case '3':\
    case '4':\
    case '5':\
    case '6':\
    case '7':\
    case '8':\
    case '9'

typedef struct LexerInput LexerInput;
struct LexerInput
{
    String8 source_file;
    Arena* id_arena;
    Arena* location_arena;
    Arena* line_offset_arena;
};

typedef struct Lexer Lexer;
struct Lexer
{
    Arena* id_arena;
    Arena* location_arena;
    Arena* line_offset_arena;
    u32 offset_token;
    u32 offset_line;
    u32 token_count;
    u32 line_count;
};

static void lexer_push_token(Lexer* lexer, TokenId id, TokenLocation location)
{
    *push_array_no_zero(lexer->id_arena, TokenId, 1) = id;
    *push_array_no_zero(lexer->location_arena, TokenLocation, 1) = location;
    lexer->token_count += 1;
}

static void lexer_new_line(Lexer* lexer, u32 line_offset)
{
    *push_array(lexer->line_offset_arena, u32, 1) = line_offset;
    lexer->line_count += 1;
}

typedef struct LexerOutput LexerOutput;
struct LexerOutput
{
    u32 line_offset;
    u32 line_count;
    u32 token_offset;
    u32 token_count;
};

struct TokenIdSlice
{
    u32 offset;
    u32 length;
    u32 thread_id;
};

static LexerOutput lex(LexerInput input)
{
    Lexer lexer = {};
    LexerOutput result = {};

    if (input.source_file.length <= UINT32_MAX)
    {
        String8 file = input.source_file;
        u64 line_offset = arena_get_position_without_self(input.line_offset_arena) / sizeof(u32);
        u64 id_offset = arena_get_position_without_self(input.id_arena) / sizeof(TokenId);
        u64 location_offset = arena_get_position_without_self(input.location_arena) / sizeof(TokenLocation);
        check(id_offset == location_offset);

        check(id_offset <= UINT32_MAX);
        check(line_offset <= UINT32_MAX);
        lexer.offset_token = (u32)id_offset;
        lexer.offset_line = (u32)line_offset;
        lexer_new_line(&lexer, 0);

        u32 i = 0;

        while (i < file.length)
        {
            u32 start = i;
            u8 start_ch = file.pointer[start];

            TokenId token_id = token_invalid;

            switch (start_ch)
            {
                alpha_cases: case '_':
                {
                    token_id = token_identifier;

                    while (true)
                    {
                        u8 ch = file.pointer[i];
                        switch (ch)
                        {
                            alpha_cases: decimal_cases: case '_': i += 1; break;
                            default: goto switch_end;
                        }
                    }
                }break;
                case '0':
                {
                    i += 1;

                    switch (file.pointer[i]) {
                        case 'x':
                            {
                                i += 1;
                                token_id = token_hex_literal;

                                while (true)
                                {
                                    u8 ch = file.pointer[i];
                                    switch (ch)
                                    {
                                        case '0':
                                        case '1':
                                        case '2':
                                        case '3':
                                        case '4':
                                        case '5':
                                        case '6':
                                        case '7':
                                        case '8':
                                        case '9':
                                        case 'a':
                                        case 'b':
                                        case 'c':
                                        case 'd':
                                        case 'e':
                                        case 'f':
                                        case 'A':
                                        case 'B':
                                        case 'C':
                                        case 'D':
                                        case 'E':
                                        case 'F':
                                            i += 1;
                                            break;
                                        default:
                                            goto switch_end;
                                    }
                                }
                            } break;
                        case 'o': 
                            {
                                i += 1;
                                token_id = token_octal_literal;

                                while (true)
                                {
                                    u8 ch = file.pointer[i];
                                    switch (ch)
                                    {
                                        case '0':
                                        case '1':
                                        case '2':
                                        case '3':
                                        case '4':
                                        case '5':
                                        case '6':
                                        case '7':
                                            i += 1;
                                            break;
                                        default:
                                            goto switch_end;
                                    }
                                }
                            } break;
                        case 'b':
                            {
                                i += 1;
                                token_id = token_binary_literal;

                                while (true)
                                {
                                    u8 ch = file.pointer[i];
                                    switch (ch)
                                    {
                                        case '0':
                                        case '1':
                                            i += 1;
                                            break;
                                        default:
                                            goto switch_end;
                                    }
                                }
                            } break;
                        case '0': 
                        case '1': 
                        case '2': 
                        case '3': 
                        case '4': 
                        case '5': 
                        case '6': 
                        case '7': 
                        case '8': 
                        case '9': 
                            trap();
                        default:
                            token_id = token_zero_literal;
                            break;
                    }
                } break;
                // Decimal case
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                {
                    token_id = token_decimal_literal;

                    while (true)
                    {
                        u8 ch = file.pointer[i];
                        switch (ch)
                        {
                            case '0':
                            case '1':
                            case '2':
                            case '3':
                            case '4':
                            case '5':
                            case '6':
                            case '7':
                            case '8':
                            case '9':
                                i += 1;
                                break;
                            default:
                                goto switch_end;
                        }
                    }
                } break;
                case '\'': 
                {
                    token_id = token_character_literal;

                    i += 1;
                    i += (file.pointer[i] == '\\') + 1;
                    i += 1;
                } break;
                case '#': 
                {
                    token_id = token_intrinsic;

                    i += 1;

                    while (true)
                    {
                        u8 ch = file.pointer[i];
                        switch (ch)
                        {
                            alpha_cases: case '_': i += 1; break;
                            default: goto switch_end;
                        }
                    }
                } break;
                case '"':
                {
                    token_id = token_string_literal;
                    i += 1;

                    while (true)
                    {
                        u8 ch = file.pointer[i];
                        switch (ch)
                        {
                            case '\n': trap();
                            case '\\': i += 2; break;
                            case '"': i += 1; goto switch_end;
                            default: i += 1; break;
                        }
                    }
                }break;
                case '+':
                {
                    i += 1;
                    u8 next_char = file.pointer[i];
                    switch (next_char)
                    {
                        case '=': i += 1; token_id = operator_add_assign; break;
                        default: token_id = operator_add; break;
                    }
                } break;
                case '-':
                {
                    i += 1;
                    u8 next_char = file.pointer[i];
                    switch (next_char)
                    {
                        case '=': i += 1; token_id = operator_sub_assign; break;
                        default: token_id = operator_minus; break;
                    }
                } break;
                case '*':
                {
                    i += 1;
                    u8 next_char = file.pointer[i];
                    switch (next_char)
                    {
                        case '=': i += 1; token_id = operator_mul_assign; break;
                        default: token_id = operator_asterisk; break;
                    }
                } break;
                case '/':
                {
                    i += 1;
                    u8 next_char = file.pointer[i];
                    switch (next_char)
                    {
                        case '=': i += 1; token_id = operator_div_assign; break;
                        case '/': while (file.pointer[i] != '\n')
                        {
                            i += 1;
                        } continue;
                        default: token_id = operator_div; break;
                    }
                } break;
                case '%':
                {
                    i += 1;
                    u8 next_char = file.pointer[i];
                    switch (next_char)
                    {
                        case '=': i += 1; token_id = operator_mod_assign; break;
                        default: token_id = operator_mod; break;
                    }
                } break;
                case '|':
                {
                    i += 1;
                    u8 next_char = file.pointer[i];
                    switch (next_char)
                    {
                        case '=': i += 1; token_id = operator_or_assign; break;
                        default: token_id = operator_bar; break;
                    }
                } break;
                case '&':
                {
                    i += 1;
                    u8 next_char = file.pointer[i];
                    switch (next_char)
                    {
                        case '=': i += 1; token_id = operator_and_assign; break;
                        default: token_id = operator_ampersand; break;
                    }
                } break;
                case '^':
                {
                    i += 1;
                    u8 next_char = file.pointer[i];
                    switch (next_char)
                    {
                        case '=': i += 1; token_id = operator_xor_assign; break;
                        default: token_id = operator_xor; break;
                    }
                } break;
                case '<':
                {
                    i += 1;

                    switch (file.pointer[i])
                    {
                        case '<':
                            {
                                i += 1;

                                switch (file.pointer[i])
                                {
                                    case '=': i += 1; token_id = operator_shift_left_assign; break;
                                    default: token_id = operator_shift_left; break;
                                }
                            } break;
                        case '=': i += 1; token_id = operator_compare_less_equal; break;
                        default: token_id = operator_compare_less; break;
                    }
                } break;
                case '>':
                {
                    i += 1;

                    switch (file.pointer[i])
                    {
                        case '>':
                            {
                                i += 1;

                                switch (file.pointer[i])
                                {
                                    case '=': i += 1; token_id = operator_shift_right_assign; break;
                                    default: token_id = operator_shift_right; break;
                                }
                            } break;
                        case '=': i += 1; token_id = operator_compare_greater_equal; break;
                        default: token_id = operator_compare_greater; break;
                    }
                } break;
                case '!':
                {
                    i += 1;

                    switch (file.pointer[i])
                    {
                        case '=': i += 1; token_id = operator_compare_not_equal; break;
                        default: token_id = operator_bang; break;
                    }
                } break;
                case '=':
                {
                    i += 1;
                    u8 next_char = file.pointer[i];
                    switch (next_char)
                    {
                        case '=': i += 1; token_id = operator_compare_equal; break;
                        case '>': i += 1; token_id = operator_switch_case; break;
                        default: token_id = operator_assign; break;
                    }
                } break;
                case '\\': token_id = operator_backslash; i += 1; break;
                case ';': token_id = operator_semicolon; i += 1; break;
                case ':': token_id = operator_colon; i += 1; break;
                case ',': token_id = operator_comma; i += 1; break;
                case '.': token_id = operator_dot; i += 1; break;
                case '{': token_id = operator_left_brace; i += 1; break;
                case '}': token_id = operator_right_brace; i += 1; break;
                case '[': token_id = operator_left_bracket; i += 1; break;
                case ']': token_id = operator_right_bracket; i += 1; break;
                case '(': token_id = operator_left_parenthesis; i += 1; break;
                case ')': token_id = operator_right_parenthesis; i += 1; break;
                case '\n':
                {
                    i += 1;
                    lexer_new_line(&lexer, i);
                } continue;
                case ' ': case '\t': case '\r': i += 1; continue;
                default: trap();
            }

switch_end:
            check(token_id != token_invalid);
            lexer_push_token(&lexer, token_id, (TokenLocation) {
                .start = start,
                .end = i,
            });
        }

#if BUILD_MODE_DEBUG
        i = 0;
        u32 new_line_count = 1;
        while (i < file.length)
        {
            u8 ch = file.pointer[i];
            new_line_count += ch == '\n';
            i += 1;
        }

        check(new_line_count == lexer.line_count);
#endif
    }

    return result;
}

typedef enum TokenIndex : u32
{
    token_index_invalid = 0xffffffff,
} TokenIndex;

typedef enum NodeIndex : u32
{
    node_index_invalid = 0xffffffff,
} NodeIndex;

typedef enum NodeId : u32
{
    foo = 0,
} NodeId;

typedef struct Node Node;
struct Node
{
    NodeId id;
    TokenIndex token;
    NodeIndex left;
    NodeIndex right;
};

typedef struct Parser Parser;
struct Parser
{
    TokenIndex token_index;
    LexerOutput lexer_output;
    String8 source_file;
    Arena* node_arena;
    Arena* arena;
};

static b32 parser_has_tokens(Parser* parser)
{
    return parser->token_index < parser->lexer_output.token_offset + parser->lexer_output.token_count;
}

static TokenId parser_peek_token(Parser* parser)
{
    check(parser_has_tokens(parser));
    unused(parser);
    trap();
}

static void parse_file_type(Parser* parser)
{
    if (parser_has_tokens(parser))
    {
        // TokenIndex token_index = parser->token_index;
        // TokenId token_id = fixed_keyword_struct;
        // TODO:
        while (parser_has_tokens(parser) & (parser_peek_token(parser) != operator_right_brace))
        {
            trap();
        }
    }
    else
    {
        trap();
    }
}

static Parser parse(Arena* arena, LexerOutput lexer_output, String8 source_file)
{
    unused(arena);
    unused(source_file);
    Arena* node_arena = arena_allocate(megabytes(64));
    Parser parser = (Parser){
        .lexer_output = lexer_output,
        .source_file = source_file,
        .node_arena = node_arena,
    };
    parse_file_type(&parser);

    return parser;
}

void entry_point(CommandLine* command_line)
{
    unused(command_line);
    ArenaTemporary scratch = thread_begin_scratch_arena(0, 0);
    Arena* general_arena = arena_allocate(gigabytes(1));
    Arena* token_id_arena = arena_allocate(gigabytes(1));
    Arena* token_location_arena = arena_allocate(gigabytes(1));
    Arena* line_offset_arena = arena_allocate(gigabytes(1));
    //Arena* node_arena = arena_allocate(gigabytes(1));
    String8 file = str8_literal("test/standalone/first/main.nat");
    String8 file_content = os_file_read_all(general_arena, file); 
    LexerOutput lexer_output = lex((LexerInput) {
                .source_file = file_content,
                .id_arena = token_id_arena,
                .location_arena = token_location_arena,
                .line_offset_arena = line_offset_arena,
            });
    Parser parser = parse(scratch.arena, lexer_output, file_content);
    unused(parser);
}
