/* Native IroCounterLoop.c; private packed Windows records. */
typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
typedef struct Pair { U32 lo,hi; } Pair;
typedef union R R;
#pragma pack(push,2)
union R {
 struct {char pad[0xe]; Pair value;} Q0xe;
 struct {char pad[0x10]; Pair value;} Q0x10;
 struct {char pad[0x18]; Pair value;} Q0x18;
 struct {char pad[0x36]; Pair value;} Q0x36;
 struct {char pad[2]; R* value;} P2;
 struct {char pad[4]; R* value;} P4;
 struct {char pad[6]; R* value;} P6;
 struct {char pad[8]; R* value;} P8;
 struct {char pad[0xa]; R* value;} P0xa;
 struct {char pad[0xe]; R* value;} P0xe;
 struct {char pad[0x10]; R* value;} P0x10;
 struct {char pad[0x14]; R* value;} P0x14;
 struct {char pad[0x16]; R* value;} P0x16;
 struct {char pad[0x1a]; R* value;} P0x1a;
 struct {char pad[0x1c]; R* value;} P0x1c;
 struct {char pad[0x1e]; R* value;} P0x1e;
 struct {char pad[0x20]; R* value;} P0x20;
 struct {char pad[0x24]; R* value;} P0x24;
 struct {char pad[0x2a]; R* value;} P0x2a;
 struct {char pad[0x2c]; R* value;} P0x2c;
 struct {char pad[0x2e]; R* value;} P0x2e;
 struct {char pad[0x30]; R* value;} P0x30;
 struct {char pad[0x32]; R* value;} P0x32;
 struct {char pad[0x3e]; R* value;} P0x3e;
 struct {char pad[0x42]; R* value;} P0x42;
 struct {char pad[0x6a]; R* value;} P0x6a;
 struct {char pad[4]; int value;} I4;
 struct {char pad[0xa]; int value;} I0xa;
 struct {char pad[0x16]; int value;} I0x16;
 struct {char pad[0x24]; int value;} I0x24;
 struct { U32 value;} U0;
 struct {char pad[2]; U32 value;} U2;
 struct {char pad[0xa]; U32 value;} U0xa;
 struct { U8 value;} B0;
 struct {char pad[2]; U8 value;} B2;
 struct {char pad[0xd]; U8 value;} B0xd;
 struct {char pad[0x2e]; U8 value;} B0x2e;
 struct {char pad[0x32]; U8 value;} B0x32;
 struct {char pad[0x34]; U8 value;} B0x34;
 struct { U16 value;} W0;
};
#pragma pack(pop)
#define Q(p,o) ((p)->Q##o.value)
#define P(p,o) ((p)->P##o.value)
#define I(p,o) ((p)->I##o.value)
#define U(p,o) ((p)->U##o.value)
#define B(p,o) ((p)->B##o.value)
#define W(p,o) ((p)->W##o.value)
#include <string.h>
extern Pair native_one,native_zero;
extern U8 native_rotation_option,native_loop_option;
extern U32 native_linear_index;
extern R native_int_type;
extern void fn_0045a250(const char*,int),fn_005ed4c0(const char*,...);
extern void fn_005c3330(R*),fn_005c3060(R*),fn_005c3130(R*),fn_005c3210(R*,R*),fn_005a9d80(void),fn_005be430(void),fn_005c6f70(R*),fn_0061d980(void),fn_005bfb20(U32),fn_005c0470(R*,int);
extern U8 fn_004d9440(Pair,Pair),fn_004d9710(Pair,Pair),fn_005b07f0(R*),fn_00453150(R*),fn_005bfe10(R*,R*,int);
extern R *fn_005aeed0(R*,R*),*fn_005acf30(R*,void*),*fn_005a9cc0(void),*fn_005be150(void),*fn_005bd630(int),*fn_005c6a60(R*,R*,R*),*fn_004c5470(int),*fn_005ab970(Pair,R*);
extern void fn_005ad280(void*),fn_005ad1e0(R*,R*,void*),fn_005ad440(R*,R*,R*),fn_005ad400(R*,R*,R*),fn_005ae7b0(R*);
static const char counter_filename[]="IroCounterLoop.c";
static const char bitvector_filename[]="BitVector.h";
static const char log_generate[]="BE to generate induction update\n";
static const char log_remove[]="remove Induction assign during delinearization\n";
static const char log_form[]="IsLoopCounterLoop:No because the loop form is currently unsupported\n";
static const char log_flags[]="IsLoopCounterLoop:No due to prohibited loop flags that are set ";
static const char log_newline[]="\n";
static const char log_count[]="IsLoopCounterLoop:No because can't compute loop's iteration count, or it will overflow\n";
static const char log_final[]="IsLoopCounterLoop:No because can't compute final value of induction, or it will overflow\n";
static const char log_yes[]="Found Counted Loop with header = %d\n";
static inline U8 hasbit(R *bits,U32 bit) { return (bit>>5)<U(bits,0) && (*(U32*)((char*)bits+4+(bit>>5)*4)&(1U<<(bit&31)))!=0; }
void IRO_SetCounterLoopFlags(R *loop)
{
 R *last=P(loop,0x14),*next,*ind,*var,*info,*linear; U8 unreferenced,generate;
 if(!(U(P(last,0x14),2)&0x200))goto done;
 fn_005c3330(loop);if(!P(loop,0x2c))goto done;
 next=P(last,0x30);fn_005ad280((char*)loop+0x3e);Q(loop,0x36)=native_one;
 linear=P(last,0x14);info=P(linear,0x32);
 if(fn_005b07f0(P(info,0xa))) {R *constant=P(P(P(P(last,0x14),0x32),0xa),0x2a);Q(loop,0x36)=Q(constant,0x10);}
 else fn_005acf30(P(info,0xa),(char*)loop+0x3e);
 info=P(P(last,0x14),0x32);if(P(info,0x1a))fn_005acf30(P(info,0x1a),(char*)loop+0x46);
 B(loop,0x34)=1;fn_005bfe10(loop,P(loop,0x2c),native_loop_option);
 ind=P(loop,0x2c);info=P(P(last,0x14),0x32);Q(info,0xe)=Q(ind,0x18);I(info,0x16)=I(ind,0x24);
 fn_0061d980();ind=P(loop,0x2c);info=P(P(last,0x14),0x32);P(info,6)=P(ind,0xe);
 if(U(loop,0)&0x800)goto done;
 var=P(ind,2);
 if(!(U(loop,0)&0x400)) {
 unreferenced=(U(P(ind,0xa),2)&2)==0;generate=0;
 if(var && unreferenced && !B(var,0xd) && B(P(var,4),2)==1 && !fn_00453150(P(var,4)) && hasbit(P(var,8),U(P(next,0x10),0xa))) {generate=1;B(P(P(last,0x14),0x32),0)=1;fn_005ed4c0(log_generate);}
 /* Native valid-loop contract requires var here, including the unreferenced path. */
 if(fn_00453150(P(var,4)) || !unreferenced)goto done;
 if(generate!=1 && hasbit(P(var,8),U(P(next,0x10),0xa)))goto done;
 linear=P(P(loop,0x2c),0xa);
 if(B(linear,0)==2) {fn_005ed4c0(log_remove);B(P(P(loop,0x2c),0xa),0x2e)=1;}
 else if(B(linear,0)==3) {B(linear,0x32)=1;fn_005ed4c0(log_remove);}
 P(P(P(last,0x14),0x32),2)=P(P(loop,0x2c),0xa);
 } else {
  if(var && !B(var,0xd) && B(P(var,4),2)==1 && !fn_00453150(P(var,4)) && hasbit(P(var,8),U(P(next,0x10),0xa))) {B(P(P(last,0x14),0x32),0)=2;fn_005ed4c0(log_generate);}goto done;
 }

done:;
}
void IRO_TransformCounterLoop(R *loop,U8 *changed)
{
 R *back,*label,*node,*linear,*newnode,*entrylabel;R *list[2];U32 bit;R *bits;
 if(*changed || !(U(P(P(loop,0x14),0x14),2)&0x40000))return;
 back=P(loop,0x1c);fn_005ad280(list);label=fn_005a9cc0();entrylabel=label;node=fn_005be150();linear=fn_005bd630(13);
 I(linear,0xa)=native_linear_index++;P(linear,0x3e)=0;P(linear,0x2a)=label;U(linear,2)|=1;P(node,0x10)=P(node,0x14)=linear;P(label,4)=node;
 P(linear,0x3e)=P(P(back,0x14),0x3e);P(P(back,0x14),0x3e)=linear;P(node,0x30)=P(back,0x30);P(back,0x30)=node;
 fn_005acf30(P(loop,0x24),list);fn_005ad400(list[0],list[1],P(node,0x14));fn_005ad280(list);fn_005acf30(P(P(loop,0x10),0x14),list);P(list[1],0x2e)=P(node,0x14);fn_005ad400(list[0],list[1],P(node,0x14));
 B(P(node,0x14),0)=B(P(P(loop,0x10),0x14),0)==10?11:10;U(P(node,0x14),2)|=0x200;newnode=node;
 P(P(P(node,0x14),0x32),0x1e)=P(P(loop,0x10),0x14);
 if(B(P(back,0x14),0)==8)B(P(back,0x14),0)=0;
 label=fn_005a9cc0();P(P(node,0x14),0x2a)=label;node=fn_005be150();linear=fn_005bd630(13);I(linear,0xa)=native_linear_index++;P(linear,0x3e)=0;P(linear,0x2a)=label;U(linear,2)|=1;P(label,4)=node;P(node,0x10)=P(node,0x14)=linear;
 P(linear,0x3e)=P(P(P(loop,0x10),0x14),0x3e);P(P(P(loop,0x10),0x14),0x3e)=linear;P(node,0x30)=P(P(loop,0x10),0x30);P(P(loop,0x10),0x30)=node;
 fn_005ae7b0(P(loop,0x24));B(P(P(loop,0x10),0x14),0)=8;P(P(P(loop,0x10),0x14),0x2a)=entrylabel;U(P(P(loop,0x10),0x14),2)|=0x400;
 P(loop,0x1c)=fn_005c6a60(loop,newnode,back);if(P(loop,0x1c))*changed=1;
 P(loop,0x10)=P(loop,0x14)=newnode;P(loop,0x24)=P(newnode,0x14);
 bit=W(newnode,0);bits=P(loop,8);if((bit>>5)<U(bits,0))*(U32*)((char*)bits+4+(bit>>5)*4)|=1U<<(bit&31);else fn_0045a250(bitvector_filename,82);
 fn_005c6f70(loop);
}
void IRO_AdjustCounterLoopsForLoopDepth(R *loops)
{
 R *loop,*p,*linear,*info,*removed;
 fn_005c3130(loops);
 for(loop=loops;loop;loop=P(loop,0x6a)) {
  if(!(U(loop,0)&0x80000))continue;
  fn_005c3210(loop,loops);
  for(p=loops;p;p=P(p,0x6a)) {
   linear=P(P(p,0x10),0x14);
   if((U(linear,2)&0x200) && I(p,4)>=2) {
    U(linear,2)&=~0x200U;info=P(P(P(p,0x10),0x14),0x32);
    if(!P(info,0x1e))fn_0045a250(counter_filename,340);
    U(P(info,0x1e),2)&=~0x400U;info=P(P(P(p,0x10),0x14),0x32);removed=P(info,2);
    if(removed) {if(B(removed,0)==2)B(removed,0x2e)=0;else if(B(removed,0)==3)B(removed,0x32)=0;P(P(P(P(p,0x10),0x14),0x32),2)=0;}
    info=P(P(P(p,0x10),0x14),0x32);if(P(info,0xa))P(info,0xa)=0;
    info=P(P(P(p,0x10),0x14),0x32);if(P(info,0x16))P(info,0x16)=0;
    info=P(P(P(p,0x10),0x14),0x32);if(P(info,0x1a))P(info,0x1a)=0;
    B(P(P(P(p,0x10),0x14),0x32),0)=0;
   }
  }
 }
 fn_005a9d80();
}
U8 IsLoopCounterLoop(R *loop)
{
 R *ind=P(loop,0x2c),*back,*body;
 if(ind)Q(ind,0x18)=native_zero;
 if(U(loop,0)&0x20c012) {fn_005ed4c0(log_flags);fn_005bfb20(U(loop,0)&0x20c012);fn_005ed4c0(log_newline);return 0;}
 if(P(loop,0x10)!=P(loop,0x14)) goto unsupported;
 back=P(loop,0x1c);if(!back || B(P(back,0x14),0)!=8 || P(back,0x30)!=P(loop,0x20) || P(loop,0x20)==P(loop,0x10)) goto unsupported;
 if(native_loop_option && (!B(loop,0x34) || fn_004d9440(Q(loop,0x36),native_one)))fn_005c0470(loop,native_loop_option);
 if(!B(loop,0x34)) {fn_005ed4c0(log_count);return 0;}
 if(!fn_005bfe10(loop,P(loop,0x2c),native_loop_option)) {fn_005ed4c0(log_final);return 0;}
 return 1;
unsupported:
 fn_005ed4c0(log_form);return 0;
}
void IRO_MarkPossibleCounterLoop(R *loop)
{
 R *info,*ind;
 fn_005c3330(loop);fn_005c3060(loop);if(!IsLoopCounterLoop(loop))goto done;
 U(P(P(loop,0x14),0x14),2)|=0x40000;fn_005ed4c0(log_yes,W(P(loop,0x10),0));
 P(P(P(loop,0x10),0x14),0x32)=fn_004c5470(34);info=P(P(P(loop,0x10),0x14),0x32);
 memset(info,0,34);
 if(fn_004d9440(Q(loop,0x36),native_one))P(P(P(P(loop,0x10),0x14),0x32),0xa)=P(loop,0x42);
 else P(P(P(P(loop,0x10),0x14),0x32),0xa)=fn_005ab970(Q(loop,0x36),&native_int_type);
 {R *start=P(loop,0x10),*induction=P(loop,0x2c);P(P(P(start,0x14),0x32),0x1a)=P(induction,0x2c);}
done:;
}
