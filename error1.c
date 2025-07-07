#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define isnum(wr) (wr >= 48 && wr <= 57)
struct map
{
    char call[20];
    char def[20];
};
struct wordformat
{
    char *input;
    int cur;
};
struct maparr
{
    struct map ar[1000];
    int cur;
    int head;
    int end;
};
enum type1 
{
    add1=1,sub1,mul1,add2,sub2,mul2,mov,start,sbrstart,endsbr,gr,le,eq,neq,geeq,leeq,unconb,bralink,store,load,lshift,rshift,leshift,reshift,endall,rt
};
struct trtype
{
    enum type1 tans;
    int count_reg;
    int define;
};
struct trtypearr
{
    struct trtype arr[1000];
    int dcur;
};
struct str
{
    char arr[500];
    int cur;
};
enum type
{
    reg32 = 1,reg64 = 2,mem = 3,imm = 4,imm64 = 5,arr = 6,signarr = 7,ob = 8,cb=9,rtr=10,slashn=11,op=12,funname=13,num=14,bcall=15,bname=16,blink=17,comb,compsign,shift
};
struct codeerror
{
    char eword[100];
    int col;
    int erline;
    int ecode;
};
struct maparr s;
struct maparr fun;
struct codeerror finderror;
struct trtypearr n;
struct str oper;
struct str defname;
struct str bsname;
struct str funame;
struct str linkname;
struct str trans;
struct wordformat transv;
struct wordformat bdname;
struct wordformat fudname;
struct wordformat callname;
struct wordformat link;
char temp[100];
char f[50];
char fname[20];
char brname[20];
int i=0;
int k=0;
void defbitset(struct trtypearr *b)
{
    b->arr[b->dcur].define=1;
}
void append(struct str *b,char word[])
{
    int i=0;
    while(word[i]!='\0' && word[i]!=32)
    {
        b->arr[b->cur]=word[i];
        i++;
        b->cur++;
    }
    b->arr[b->cur]=' ';
    b->cur++;
}
void append2(struct str *b,char word[])
{
    int i=0;
    while(word[i]!='\0' && word[i]!=32)
    {
        b->arr[b->cur]=word[i];
        i++;
        b->cur++;
    }
}
char* concat(char d[],char s[])
{
    int j=0;
    int i=1;
    while(s[i]!='\0')
    {
        f[j]=s[i];
        j++;
        i++;
    }
    f[j]='_';
    j++;
    i=1;
    while(d[i]!='\0')
    {
        f[j]=d[i];
        j++;
        i++;
    }
    f[j]='\0';
    return f;
}
void connect(struct trtypearr *b,enum type a)
{
    b->arr[b->dcur].tans=a;
}
void add(char a[], char c[], struct maparr *s)
{
    if (s->head == -1)
    {
        strcpy(s->ar[s->cur].call, a);
        strcpy(s->ar[s->cur].def, c);
        s->head = s->cur;
        s->end = s->cur;
        s->cur++;
    }
    else
    {
        strcpy(s->ar[s->cur].call, a);
        strcpy(s->ar[s->cur].def, c);
        s->end = s->cur;
        s->cur++;
    }
}
int length(char a[])
{
    int i = 0;
    int count = 0;
    while (a[i] != '\0')
    {
        count++;
        i++;
    }
    return count;
}
int equals(char a[], char b[])
{
    int output = 0;
    int i = 0;
    int sum = 0;
    if (length(a) == length(b))
    {
        while (i < length(a))
        {
            sum = sum + a[i] - b[i];
            i++;
        }
        if (sum == 0)
        {
            output = 1;
        }
    }
    else
    {
        output = 0;
    }
    return output;
}
char *nw(struct wordformat *b)
{
    int i = 0;
    while (b->input[b->cur] != ' ' && b->input[b->cur] != '\0')
    {
        temp[i] = b->input[b->cur];
        i++;
        b->cur++;
        finderror.col++;
    }
    temp[i] = '\0';
    strcpy(finderror.eword, temp);
    b->cur++;
    finderror.col++;
    return temp;
}
int type(char a[], int b)
{
    int output = 0;
    int len = length(a);
    if (a[0] == 'w')
    {
        if (((a[1] >= 48 && a[1] <= 57) && a[2] == '\0') || (a[1] == 51 && (a[2] >= 48 && a[2] <= 50)) || ((a[1] >= 48 && a[1] <= 50) && (a[2] >= 48 && a[2] <= 57)) && (a[3] == '\0'))
        {
            output = reg32;
            append(&oper,a);
            i++;
        }
    }
    else if (a[0] == 'x')
    {
        if (((a[1] >= 48 && a[1] <= 57) && a[2] == '\0') || (a[1] == 51 && (a[2] >= 48 && a[2] <= 50)) || ((a[1] >= 48 && a[1] <= 50) && (a[2] >= 48 && a[2] <= 57)) && (a[3] == '\0'))
        {
            output = reg64;
            append(&oper,a);
            i++;
        }
    }
    else if (equals(a, "mem"))
    {
        output = mem;
    }
    else if (a[0] == '#' && b == 0)
    {
        append(&oper,a);
        i++;
        int i = 1;
        int len = length(a);
        while (i < len)
        {
            if (isnum(a[i]))
            {
                output = imm;
            }
            else
            {
                output = 0;
                break;
            }
            i++;
        }
    }
    else if (a[0] == '#' && b == 1)
    {
        int i = 1;
        int len = length(a);
        int temp = 0;
        while (i < len)
        {
            if (isnum(a[i]))
            {
                temp = temp * 10 + (a[i] - 48);
            }
            else
            {
                output = 0;
                break;
            }
            i++;
        }
        if (temp % 8 == 0)
        {
            output = imm64;
        }
    }
    else if (equals(a, "<-"))
    {
        output = arr;
        connect(&n,mov);
    }
    else if (equals(a, "+<-") || equals(a, "-<-") || equals(a, "*<-"))
    {
        if(equals(a, "+<-"))
        {
            connect(&n,add2);
        }
        else if(equals(a, "-<-"))
        {
            connect(&n,sub2);
        }
        else
        {
            connect(&n,mul2);
        }
        output = signarr;
    }
    else if (equals(a, "("))
    {
        output = ob;
    }
    else if (equals(a, ")"))
    {
        connect(&n,endsbr);
        output = cb;
    }
    else if (equals(a, "\n"))
    {
        output = slashn;
        finderror.col = 0;
        finderror.erline++;
        n.arr[n.dcur].count_reg=i;
        n.dcur++;
        i=0;
    }
    else if (equals(a, "+") || equals(a, "-") || equals(a, "*"))
    {
        if(equals(a, "+"))
        {
            connect(&n,add1);
        }
        else if(equals(a,"-"))
        {
            connect(&n,sub1);
        }
        else
        {
            connect(&n,mul1);
        }
        output = op;
    }
    else if (equals(a, "return"))
    {
        connect(&n,rt);
        output = rtr;
    }
    else if (a[0] == '$')
    {
        if (a[1] >= 97 && a[1] <= 122)
        {
            int i = 2;
            while (i < len)
            {
                if ((a[i] >= 97 && a[i] <= 122) || (a[i] >= 48 && a[i] <= 57))
                {
                    output = funname;
                }
                else
                {
                    output = 0;
                    break;
                }
                i++;
            }
        }
    }
    else if (isnum(a[0]))
    {
        int i = 1;
        output = num;
        while (a[i] != '\0')
        {
            if (!isnum(a[i]))
            {
                output = 0;
                break;
            }
            i++;
        }
    }
    else if (equals(a, "b"))
    {
        connect(&n,unconb);
        output = bcall;
    }
    else if (a[0] == 58)
    {
        if (a[1] >= 97 && a[1] <= 122)
        {
            int i = 2;
            while (i < len)
            {
                if ((a[i] >= 97 && a[i] <= 122) || (a[i] >= 48 && a[i] <= 57))
                {
                    output = bname;
                }
                else
                {
                    output = 0;
                    break;
                }
                i++;
            }
        }
    }
    else if (equals(a, "bl"))
    {
        connect(&n,bralink);
        output = blink;
    }
    else if(equals(a,"CB"))
    {
        output=comb;
    }
    else if(equals(a,"<") || equals(a,">") || equals(a,"==") || equals(a,"!=") || equals(a,"<=") || equals(a,">="))
    {
        if(equals(a,"<")){connect(&n,le); }
        else if(equals(a,">")){connect(&n,gr);}
        else if(equals(a,"==")){connect(&n,eq);}
        else if(equals(a,"!=")){connect(&n,neq);}
        else if(equals(a,"<=")){connect(&n,geeq);}
        else if(equals(a,">=")){connect(&n,leeq);}
        output=compsign;
    }
    else if(equals(a,"<<<-") || equals(a,">><-") || equals(a,"<<") || equals(a,">>"))
    {
        if(equals(a,"<<<-")){connect(&n,lshift);}
        else if(equals(a,"<<")){connect(&n,leshift);}
        else if(equals(a,">><-")){connect(&n,rshift);}
        else if(equals(a,">>")){connect(&n,reshift);}
        output=shift;
    }
    return output;
}
int chk_instruction(struct wordformat *b, int ans)
{
    int output = 0;
    int a = 1;
    if (ans == 1)
    {
        ans = type(nw(b), a);
        if (ans == 6)
        {
            ans = type(nw(b), a);
            if (ans == 1)
            {
                ans = type(nw(b), a);
                if (ans == 12)
                {
                    ans = type(nw(b), !a);
                    if (ans == 1)
                    {
                        ans = type(nw(b), a);
                        if (ans == 11)
                        {                     
                            output = 1;
                        }
                    }
                    else if (ans == 4)
                    {
                        if (type(nw(b), a) == 11)
                        {
                            output = 1;
                        }
                    }
                }
                else if(ans==20)
                {
                    ans=type(nw(b),!a);
                    if(ans==1)
                    {
                        ans=type(nw(b),a);
                        if(ans==11)
                        {
                            output=1;
                        }
                    }
                    else if(ans==4)
                    {
                        ans=type(nw(b),a);
                        if(ans==11)
                        {
                            output=1;
                        }
                    }
                }
                else if (ans == 11)
                {
                    output = 1;
                }
            }
            else if (ans == 3)
            {
                connect(&n,load);
                ans = type(nw(b), a);
                if (ans == 2)
                {
                    ans = type(nw(b), a);
                    if (ans == 5)
                    {
                        output=1;
                    }
                }
            }
            else if (ans == 4)
            {
                ans = type(nw(b), a);
                if (ans == 12)
                {
                    ans = type(nw(b), a);
                    if (ans == 1)
                    {
                        ans = type(nw(b), a);
                        if (ans == 11)
                        {
                            output = 1;
                        }
                    }
                    else if (ans == 4)
                    {
                        ans = type(nw(b), a);
                        if (ans == 11)
                        {
                            output = 1;
                        }
                    }
                }
            }
        }
        else if (ans == 7)
        {
            ans = type(nw(b), a);
            if (ans == 1)
            {
                ans = type(nw(b), a);
                if (ans == 11)
                {
                    output = 1;
                }
            }
            else if (ans == 4)
            {
                ans = type(nw(b), a);
                if (ans == 11)
                {
                    output = 1;
                }
            }
        }
        else if(ans == 20)
        {
            ans=type(nw(b),!a);
            if(ans==1)
            {
                ans=type(nw(b),a);
                if(ans==11)
                {
                    output=1;
                }
            }
            else if(ans==4)
            {
                ans=type(nw(b),a);
                if(ans==11)
                {
                    output=1;
                }
            }
        }
    }
    else if (ans == 2)
    {
        ans = type(nw(b), a);
        if (ans == 6)
        {
            ans = type(nw(b),!a);
            if (ans == 2)
            {
                ans = type(nw(b), a);
                if (ans == 12)
                {
                    ans = type(nw(b), !a);
                    if (ans == 2)
                    {
                        ans = type(nw(b), a);
                        if (ans == 11)
                        {
                            output = 1;
                        }
                    }
                    else if (ans == 4)
                    {
                        if (type(nw(b), a) == 11)
                        {
                            output = 1;
                        }
                    }
                }
                else if(ans==20)
                {
                    ans=type(nw(b),!a);
                    if(ans==1)
                    {
                        ans=type(nw(b),a);
                        if(ans==11)
                        {
                            output=1;
                        }
                    }
                    else if(ans==4)
                    {
                        ans=type(nw(b),a);
                        if(ans==11)
                        {
                            output=1;
                        }
                    }
                }
                else if (ans == 11)
                {
                    output = 1;
                }
            }
            else if (ans == 3)
            {
                connect(&n,load);
                ans = type(nw(b), a);
                if (ans == 2)
                {
                    ans = type(nw(b), a);
                    if (ans == 5)
                    {
                        ans = type(nw(b), a);
                        if (ans == 11)
                        {
                            output = 1;
                        }
                    }
                }
            }
            else if (ans == 4)
            {
                ans = type(nw(b), a);
                if (ans == 12)
                {
                    ans = type(nw(b), a);
                    if (ans == 2)
                    {
                        ans = type(nw(b), a);
                        if (ans == 11)
                        {
                            output = 1;
                        }
                    }
                    else if (ans == 4)
                    {
                        ans = type(nw(b), a);
                        if (ans == 11)
                        {
                            output = 1;
                        }
                    }
                }
                else if(ans==11)
                {
                    output=1;
                }
            }
        }
        else if (ans == 7)
        {
            ans = type(nw(b),!a);
            if (ans == 2)
            {
                ans = type(nw(b), a);
                if (ans == 11)
                {
                    output = 1;
                }
            }
            else if (ans == 4)
            {
                ans = type(nw(b), a);
                if (ans == 11)
                {
                    output = 1;
                }
            }
        }
        else if(ans == 20)
        {
            ans=type(nw(b),!a);
            if(ans==1)
            {
                ans=type(nw(b),a);
                if(ans==11)
                {
                    output=1;
                }
            }
            else if(ans==4)
            {
                ans=type(nw(b),a);
                if(ans==11)
                {
                    output=1;
                }
            }
        }
    }
    else if (ans == 3)
    {
        ans = type(nw(b), a);
        if (ans == 2)
        {
            ans = type(nw(b), a);
            if (ans == 5)
            {
                ans = type(nw(b), a);
                if (ans == 6)
                {
                    connect(&n,store);
                    ans = type(nw(b), !a);
                    if (ans == 1)
                    {
                        ans = type(nw(b), a);
                        if (ans == 11)
                        {
                            output = 1;
                        }
                    }
                    else if (ans == 2)
                    {
                        ans = type(nw(b), a);
                        if (ans == 11)
                        {
                            output = 1;
                        }
                    }
                    else if (ans == 4)
                    {
                        ans = type(nw(b), a);
                        if (ans == 11)
                        {
                            output = 1;
                        }
                    }
                }
            }
        }
    }
    else if (ans == 10)
    {
        ans=type(nw(b),a);
        if(ans==11)
        {
            output = 1;
        }
    }
    return output;
}
int checkcall_inst(struct wordformat *b, struct maparr *s)
{
    char strtemp[50];
    int output = 0;
    int ans;
    strcpy(strtemp, nw(b));
    strcpy(brname,strtemp);
    int temp = s->head;
    if (type(strtemp, 0) == 16 || type(strtemp,0)==13)
    {
        while (temp <= s->end && output == 0)
        {
            if (equals(s->ar[temp].def, strtemp))
            {
                if (equals(s->ar[temp].call, "NULL"))
                {
                    strcpy(s->ar[temp].call, strtemp);
                }
                output=1;
            }
            temp++;
        }
        if (output == 0)
        {
            add(strtemp, "NULL", s);
            output=1;
        }
    }
    return output;
}
int checkdef_inst(char str[], struct maparr *s)
{
    int temp;
    int output = 0;
    temp=s->head;
    while (temp <= s->end)
    {
        if (equals(s->ar[temp].call, str) && output == 0)
        {
            if (equals(s->ar[temp].def, "NULL"))
            {
                strcpy(s->ar[temp].def, str);
            }
            output = 1;
        }
        else if(equals(s->ar[temp].def,str))
        {
            return output;
        }
        temp++;
    }
    if (output == 0)
    {
        add("NULL", str, s);
        output = 1;
    }
    return output;
}
int checkcond_inst(struct wordformat *b)
{
    int output=0;
    finderror.ecode=201;
    char temp[20];
    int ans=type(nw(b),0);
    if(ans==1)
    {
        ans=type(nw(b),0);
        if(ans==19)
        {
            ans=type(nw(b),0);
            if(ans==1 || ans==4)
            {
                if(checkcall_inst(b,&s))
                {
                    append(&bsname,concat(brname,fname));
                    ans=type(nw(b),0);
                    if(ans==11)
                    {
                        output=1;
                    }
                }
            }
        }
    }
    else if(ans==2)
    {
        ans=type(nw(b),0);
        if(ans==19)
        {
            ans=type(nw(b),0);
            if(ans==2 || ans==4)
            {
                if(checkcall_inst(b,&s))
                {
                    append(&bsname,concat(brname,fname));
                    output=1;
                }
            }
        }
    }
    else if(ans==4)
    {
        ans=type(nw(b),0);
        if(ans==19)
        {
            ans=type(nw(b),0);
            if(ans==2 || ans==1)
            {
                if(checkcall_inst(b,&s))
                {
                    append(&bsname,concat(brname,fname));
                    output=1;
                }
            }
        }
    }
}
int chk_allinstruction(struct wordformat *b) // handle all instructions
{
    int output = 1;
    int ans = 0;
    char temp[20];
    int flag=0;
    int i=0;
    while (ans != 9 && output == 1)
    {
        strcpy(temp, nw(b));
        ans = type(temp, 0);
        if (ans == 1 || ans == 2 || ans == 13 || ans==10 || ans ==3)
        {
            if (chk_instruction(b, ans) == 0)
            {
                output = 0;
                finderror.ecode = 201;
            }
        }
        else if (ans == 15)
        {
            if (checkcall_inst(b, &s) == 1)
            {
                append(&bsname,concat(brname,fname));
                ans=type(nw(b),0);
                if(ans==11)
                {
                    output=1;
                }
                else 
                {
                    finderror.ecode = 201;
                    output=0;
                }
            }
            else
            {
                output = 0;
                finderror.ecode = 201;
            }
        }
        else if (temp[0] == 58 )
        {
            append(&defname,concat(temp,fname));
            defbitset(&n);
            if (checkdef_inst(temp, &s) == 0)
            {   
                output=0;
            }
        }
        else if (ans == 17)
        {
            if (checkcall_inst(b, &fun) == 1)
            {
                append(&linkname,concat(brname,"__str"));
                ans=type(nw(b),0);
                if(ans==11)
                {
                    output=1;
                }
                else 
                {
                    finderror.ecode = 201;
                    output=0;
                }
            }
            else
            {
                output = 0;
                finderror.ecode = 201;
            }
        }
        else if(ans == 18)
        {
            if(checkcond_inst(b)==0)
            {
                output=0;
            }
        }
    }
    return output;
}
int check()
{
    int output = 0;
    int hello = s.head;
    if (hello >= 0)
    {
        while (hello <= s.end)
        {
            if (equals(s.ar[hello].def, "NULL"))
            {
                finderror.ecode = 203;
                strcpy(finderror.eword, s.ar[hello].call);
                output = 0;
                return output;
            }
            else
            {
                output = 1;
            }
            hello++;
        }
    }
    else
    {
        output = 1;
    }
    s.head = s.cur;
    s.end = s.cur;
    return output;
}
int check_subroutine(struct wordformat *b, int ans)
{
    int output = 0;
    int a = 0;
    char tempstr[50];
    finderror.ecode = 201;
    if (ans == 8)
    {
        strcpy(tempstr,nw(b));
        ans = type(tempstr, a);
        if (ans == 13)
        {
            connect(&n,sbrstart);
            append(&funame,concat(tempstr,"___sbr"));
            strcpy(fname,tempstr);
            finderror.ecode=204;
            if(checkdef_inst(tempstr,&fun))
            {
                finderror.ecode=201;
                ans = type(nw(b), a);
                if (ans == 14)
                {   
                    ans = type(nw(b), a);
                    if (ans == 11)
                    {
                        if (chk_allinstruction(b))
                        {
                            ans = type(nw(b), a);
                            if (ans == 11)
                            {
                                if (check())
                                {
                                    output = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return output;
}
int checkfun()
{
    int output=1;
    int start=0;
    finderror.ecode=205;
    while(start<=fun.end && output!=0)
    {
        if(equals(fun.ar[start].def,"NULL") && (!equals(fun.ar[start].call,"NULL")))
        {
            strcpy(finderror.eword,fun.ar[start].call);
            output=0;
        } 
        start++;
    }
    return output;
}
int check_allsubroutine(struct wordformat *b)
{
    int output = 1;
    int ans = 0;
    while (ans != 9 && output == 1)
    {
        ans = type(nw(b), 0);
        if (ans == 8)
        {
            if (check_subroutine(b, ans) == 0)
            {
                output = 0;
            }
        }
    }
    return output;
}
int checkfirst(struct maparr* s,char temp[])
{
    int i=s->head;
    int output=0;
    finderror.ecode=206;
    strcpy(finderror.eword,temp);
    while(i<=s->end)
    {
        if(equals(s->ar[i].def,temp) && output==0)
        {
            output=1;
            return output;
        }
        i++;
    }
    return output;
}
int check_syntax(struct wordformat *b)
{
    int output = 0;
    int ans = type(nw(b), 0);
    finderror.ecode = 201;
    char temp[20];
    if (ans == 8)
    {
        strcpy(temp,nw(b));
        ans = type(temp, 0);
        if (ans == 13)
        {
            connect(&n,start);
            append(&funame,concat(temp,"___sbr"));
            ans = type(nw(b), 0);
            if (ans == 11)
            {
                if (check_allsubroutine(b))
                {
                    connect(&n,endall);
                    n.dcur++;
                    if(checkfun())
                    {
                        if(checkfirst(&fun,temp))
                        {
                            output = 1;
                        }
                    }
                }
            }
        }
    }
    return output;
}
void translate(struct trtypearr *b)
{
    int j=1;
    int ans=b->arr[k].tans;
    char temp[20];
    if(b->arr[k].define==1)
    {
        append2(&trans,nw(&bdname));
        append2(&trans,":");
        append(&trans,"\n");
    }
    if(ans==1 || ans==2 || ans == 3)
    {
        append(&trans,"\t");
        if(ans==1)
        {
            append(&trans,"ADD");
        }
        else if(ans==2)
        {
            append(&trans,"SUB");
        }
        else if(ans==3)
        {
            append(&trans,"MUL");
        }
        append2(&trans,nw(&transv));
        append2(&trans,",");
        while(j<b->arr[k].count_reg)
        {
            append2(&trans,",");
            strcpy(temp,nw(&transv));
            append2(&trans,temp);
            j++;
        }
        append(&trans,"\n");       
    }
    else if(ans==4 || ans==5 || ans == 6)
    {
        append(&trans,"\t");
        if(ans==4)
        {
            append(&trans,"ADD");
        }
        else if(ans==5)
        {
            append(&trans,"SUB");
        }
        else if(ans==6)
        {
            append(&trans,"MUL");
        }
        strcpy(temp,nw(&transv));
        append2(&trans,temp);
        append2(&trans,",");
        append2(&trans,temp);
        while(j<b->arr[k].count_reg)
        {
            append2(&trans,",");
            strcpy(temp,nw(&transv));
            append2(&trans,temp);
            j++;
        }
        append2(&trans,"\n");      
    }
    else if(ans==7)
    {
        append(&trans,"\t");
        int j=1;
        append(&trans,"mov");
        strcpy(temp,nw(&transv));
        append2(&trans,temp);
        while(j<b->arr[k].count_reg)
        {
            append2(&trans,",");
            strcpy(temp,nw(&transv));
            append2(&trans,temp);
            j++;
        }
        append2(&trans,"\n");
    }
    else if(ans==8)
    {
	append(&trans,".section");
	append(&trans,".text\n");
        append(&trans,".global");
	append2(&trans,"_start\n");
        append2(&trans,"_start:\n");
        append2(&trans,"\t");
        append(&trans,"bl");
        append(&trans,nw(&fudname));
        append2(&trans,"\n");
	append(&trans,"\tmov");
	append2(&trans,"w8,#93\n");
	append(&trans,"\tsvc");
	append2(&trans,"#0\n\tret\n");
    }
    else if(ans==9)
    {
        append2(&trans,nw(&fudname));
        append(&trans,":");
        append2(&trans,"\n");
        append(&trans,"\tstr");
        append(&trans,"lr,[sp,#-8]!\n");
        append(&trans,"\tstr");
        append(&trans,"fp,[sp,#-8]!\n");
        append(&trans,"\tmov"); 
        append(&trans,"fp,sp");
        append2(&trans,"\n");
    }
    else if(ans==10)
    {
        append(&trans,"\tb");
        append2(&trans,"ret_ret\n");
    }
    else if(ans==11 || ans==12 || ans==13 || ans==14 || ans==15 || ans==16)
    {
        append(&trans,"\t");
        append(&trans,"cmp");
        strcpy(temp,nw(&transv));
        append2(&trans,temp);
        while(j<b->arr[k].count_reg)
        {
            append2(&trans,",");
            strcpy(temp,nw(&transv));
            append2(&trans,temp);
            j++;
        }
        append(&trans,"\n");
        append(&trans,"\t");
        if(ans==11)
        {
            append(&trans,"bgt");
        }
        else if(ans==12)
        {
            append(&trans,"blt");
        }
        else if(ans==13)
        {
            append(&trans,"beq");
        }
        else if(ans==14)
        {
            append(&trans,"bne");
        }
        else if(ans==15)
        {
            append(&trans,"bge");
        }
        else if(ans==16)
        {
            append(&trans,"ble");
        }
        append2(&trans,nw(&callname));
        append2(&trans,"\n");
    }
    else if(ans==17)
    {
        append2(&trans,"\t");
        append(&trans,"b");
        append(&trans,nw(&callname));
        append(&trans,"\n");
    }
    else if(ans==18)
    {
        append2(&trans,"\t");
        append(&trans,"bl");
        append(&trans,nw(&link));
        append(&trans,"\n");   
    }
    else if(ans==19)
    {
        append(&trans,"\t");
        append(&trans,"ldr");
        nw(&transv);
        append2(&trans,nw(&transv));
        append2(&trans,",");
        append(&trans,"[fp],#8");
        append(&trans,"\n");
    }
    else if(ans==20)
    {
        append(&trans,"\t");
        append(&trans,"str");
        append2(&trans,nw(&transv));
        append2(&trans,",");
        append(&trans,"[fp,-#8]");
        append(&trans,"\n");
    }
    else if(ans==21)
    {
        append(&trans,"\t");
        append(&trans,"lsl");
        strcpy(temp,nw(&transv));
        append2(&trans,temp);
        append2(&trans,",");
        append2(&trans,temp);
        append2(&trans,",");
        append2(&trans,nw(&transv));
        append2(&trans,"\n");
    }
    else if(ans==22)
    {
        append(&trans,"\t");
        append(&trans,"lsr");
        strcpy(temp,nw(&transv));
        append2(&trans,temp);
        append2(&trans,",");
        append2(&trans,temp);
        append2(&trans,",");
        append2(&trans,nw(&transv));
        append2(&trans,"\n");   
    }
    else if(ans==23)
    {
        append(&trans,"\t");
        append(&trans,"lsl");
        append2(&trans,nw(&transv));
        append2(&trans,",");
        append2(&trans,nw(&transv));
        append2(&trans,",");
        append2(&trans,nw(&transv));
        append2(&trans,"\n");
    }
    else if(ans==24)
    {
        append(&trans,"\t");
        append(&trans,"lsr");
        append2(&trans,nw(&transv));
        append2(&trans,",");
        append2(&trans,nw(&transv));
        append2(&trans,",");
        append2(&trans,nw(&transv));
        append2(&trans,"\n");
    }
    else if(ans==25)
    {
	append(&trans,"");
	append(&trans,"ret_ret:\n");
        append(&trans,"\tmov");
        append2(&trans,"sp,fp\n");
        append(&trans,"\tldr");
        append2(&trans,"fp,[sp],#8\n");
        append(&trans,"\tldr");
        append2(&trans,"fp,[sp],#8\n");
        append2(&trans,"\tret\n");
    }
    else if(ans==26)
    {
        append(&trans,"\tret\n");
    }
    k++;
}
int main()
{
    struct wordformat b;
    FILE *fptr;
    FILE *fptr1;
    fptr1=fopen("input","r");
    fptr = fopen("ans.s", "w");
    char line[2000]; 
    while (fgets(line, sizeof(line), fptr1)) {
        int f=0;
    }
    s.head = -1;
    s.end = -1;
    s.cur = 0;
    fun.head=-1;
    fun.end=-1;
    fun.cur=0;
    finderror.col = 0;
    finderror.erline = 1;
    b.cur = 0;
    char a[] = "( $div \n ( $div 0 \n x1 <- #110 \n x2 <- #10 \n :divide CB x1 < x2 :nodivide \n x1 -<- x2 \n x0 +<- #1 \n b :divide \n :nodivide return \n ) \n )";
    strcpy(b.input ,line);
    int c = check_syntax(&b);
    if (!c)
    {
        if (finderror.ecode == 201)
        {
            printf("error at line no %d,%d\n", finderror.erline, finderror.col);
            printf("near %s", finderror.eword);
        }
        else if (finderror.ecode == 202)
        {
            printf("error at line no %d,%d\n", finderror.erline, finderror.col);
            printf("Branch Overloading %s", finderror.eword);
        }
        else if (finderror.ecode == 203)
        {
            printf("Branch Not Found = %s", finderror.eword);
        }
        else if(finderror.ecode == 204)
        {
            printf("error at line no %d,%d\n", finderror.erline, finderror.col);
            printf("function Overloading %s", finderror.eword);
        }
        else if(finderror.ecode == 205)
        {
            printf("implicit declration of function name %s", finderror.eword);
        }
        else if(finderror.ecode == 206)
        {
            printf("Main Function '%s' Not Found",finderror.eword);
        }
    }
    else
    {
        transv.cur=0;
        bdname.cur=0;
        fudname.cur=0;
        transv.input=oper.arr;
        callname.input=bsname.arr;
        bdname.input=defname.arr;
        fudname.input=funame.arr;
        link.input=linkname.arr;
        for(int i=0;i<n.dcur;i++)
        {
            translate(&n);
        }
        fputs(trans.arr,fptr);
    };
    return 0;
}
