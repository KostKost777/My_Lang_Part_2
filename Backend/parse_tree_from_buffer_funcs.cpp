#include <TXLib.h>

#include "../Frontend/dump_funcs.h"
#include "../Frontend/tree_funcs.h"
#include "../Frontend/read_from_file_funcs.h"
#include "basewords_backend.h"
#include "parse_tree_from_buffer_funcs.h"
#include "../Frontend/lexical_analysis.h"
#include "../Frontend/name_table_funcs.h"
#include "../Frontend/hash_funcs.h"

Node* FillNodeDataFromBuffer(char** cur_pos, size_t* size, Node* parent)
{
    assert(cur_pos);

    const int NIL_LEN = 3;

    fprintf(log_file, "<h2>=======Новый вызов функции создания узла=======</h2>\n\n");

    fprintf(log_file, "<strong>BUFFER:</strong> \n|%s|\n\n", *cur_pos);
    fprintf(log_file, "<strong>SIZE:</strong> %llu \n\n", *size);

    SkipSpaces(cur_pos);

    if (**cur_pos == '(')
    {
        fprintf(log_file, "<strong>Обнаружил скобку \"(\"</strong>\n\n");

        *cur_pos += 1;
        fprintf(log_file, "<strong>Пропустил скобку:</strong> \n|%s|\n\n", *cur_pos);

        SkipSpaces(cur_pos);

        Node* node = (Node*)calloc(1, sizeof(Node));
        RaedNode(cur_pos, node);
        node->parent = parent;

        fprintf(log_file, "<strong>Создал новую вершину</strong>\n"
                          "<strong>NODE_PTR:</strong> %p \n"
                          "<strong>TYPE:</strong> |%s| \n"
                          "<strong>BUFFER:</strong> %s \n\n",
                          node, GetNodeTypeName(node), *cur_pos);

        *size += 1;

        fprintf(log_file, "<strong>Увеличил размер SIZE:</strong> %llu \n\n", *size);

        node->left = FillNodeDataFromBuffer(cur_pos, size, node);

        fprintf(log_file, "<strong>Завершил левый узел:</strong> %p \n"
                          "<strong>У этого узла:</strong> %p \n",
                                                node, node);

        node->right = FillNodeDataFromBuffer(cur_pos, size, node);

        fprintf(log_file, "<strong>Завершил правый узел:</strong> %p "
                          "<strong>У этого узла:</strong> %p ",
                                                 node, node);

        SkipSpaces(cur_pos);

        *cur_pos += 1;

        fprintf(log_file, "Пропустил \")\": \n|%s|\n\n", *cur_pos);

        fprintf(log_file, "<strong>Сейчас верну этот указатель %p</strong> \n\n",
                                                                       node);

        return node;
    }

    else if (IsNil(*cur_pos))
    {
        *cur_pos += NIL_LEN;

        fprintf(log_file, "<strong>Пропустил \"nil\":</strong> \n|%s|\n\n", *cur_pos);

        SkipSpaces(cur_pos);

        return NULL;
    }

    return NULL;
}

void RaedNode(char** cur_pos, Node* node)
{
    assert(cur_pos);
    assert(*cur_pos);

    int len = 0;
    int num = 0;

    int status = sscanf(*cur_pos, "%d%n", &num, &len);
    if (status == 1)
    {
        node->type = NUM;
        node->lexeme.num = num;
        fprintf(log_file, "<strong>До пропуска числа:</strong> \n|%s| \n\n", *cur_pos);
        *cur_pos += len;
        fprintf(log_file, "<strong>Пропустил число:</strong> \n|%s| \n\n", *cur_pos);
        return;
    }

    char ident_name[MAX_LEN_OF_WORD] = {};

    sscanf(*cur_pos, "%s%n", ident_name, &len);

    fprintf(log_file, "<strong>Посчитал длину нового имени LEN:</strong> %d\n\n", len);

    fprintf(log_file, "<strong>До пропуска слова:</strong> \n|%s| \n\n", *cur_pos);
    *cur_pos += len;
    fprintf(log_file, "<strong>Пропустил слово:</strong> \n|%s| \n\n", *cur_pos);

    fprintf(log_file, "<strong>Тут же получил имя NAME:</strong> |%s|\n\n", ident_name);

    node->type = GetNodeType(ident_name);
    node->lexeme.str.name = strdup(ident_name);
    node->lexeme.str.hash = GetHash(ident_name);
}

Type GetNodeType(char* ident_name)
{
    size_t hash = GetHash(ident_name);

    for (size_t i = 0; i < NUM_OF_BASEWORDS; ++i)
    {
        //printf("IDENT_NAME: %s   BASEWORD: %s\n", ident_name, basewords_arr[i].name);
        if (basewords_arr[i].hash == hash
            && strcmp(ident_name, basewords_arr[i].name) == 0)
            return basewords_arr[i].type;
    }

    return IDENT;
}

bool IsNil(char* cur_pos)
{
    char checker[4] = {};

    sscanf(cur_pos, "%3s", checker);
    fprintf(log_file, "<strong>Прочитал потенциальный NIL получил:</strong> |%s|\n\n",
                                                                             checker);
    if (strcmp(checker, "nil") == 0)
        return true;

    return false;
}

void SkipSpaces(char** cur_pos)
{
    assert(cur_pos);

    fprintf(log_file, "<strong>Пропускаю все пробельные символы</strong>\n\n");
    fprintf(log_file, "<strong>До пропуска BUFFER:</strong> \n|%s|\n\n", *cur_pos);

    while (isspace(**cur_pos))
        *cur_pos += 1;

    fprintf(log_file, "<strong>После пропуска BUFFER:</strong> \n|%s|\n\n", *cur_pos);
}
