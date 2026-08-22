static int Calc(const char *expression)
{
    /* TODO: 在这里实现后缀表达式求值。 */
    int res = 0;
    int stack[50000] = {0};
    int top = 0;
    for(char* p = expression;*p!='\0';)
    {
        char* end = p;
        while(*end !=','&&*end!='\0')
        {
            end++;
        }
        int len = (int)(end - p);
        if(len == 1&&(*p=='+'||*p=='-'||*p=='*'||*p=='/'))
        {
            top--;
            int right = stack[top];
            top--;
            int left = stack[top];
            switch (*p)
            {
            case '+':
                stack[top] = left + right;
                break;
            case '-':
                stack[top] = left - right;
                break;
            case '*':
                stack[top] = left * right;
                break;
            case '/':
                stack[top] = left / right;
                break;
            
            default:
                break;
            }
            top++;
        }
        else
        {
            stack[top] = (int)strtol(p,NULL,10);
            top++;
        }
        if(*end == ',')
        {
            p = end + 1;
        }
        else
        {
            p=end;
        }
    }
    res = stack[--top];
    return res;
}
